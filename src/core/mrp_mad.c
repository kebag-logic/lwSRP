/*
 * MRP Attribute Declaration (MAD) state machine implementation.
 * IEEE 802.1Q-2018, §10.7 — Tables 10-3 through 10-6.
 *
 * Four state machines per MRP Participant (one Participant per port):
 *   a) Applicant   — per-Attribute (Table 10-3)
 *   b) Registrar   — per-Attribute (Table 10-4)
 *   c) LeaveAll    — per-Participant (Table 10-5)
 *   d) PeriodicTransmission — per-Participant (Table 10-6)
 */

#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/alloc.h"

/* ------------------------------------------------------------------ */
/* Internal types                                                       */
/* ------------------------------------------------------------------ */

/* §10.7.6.1 — what message to place in the next MRPDU transmission */
enum tx_msg {
    TX_MSG_NONE  = 0,
    TX_MSG_NEW,    /* §10.7.6.2 sN  */
    TX_MSG_JOIN,   /* §10.7.6.3 sJ  (JoinIn if Reg=IN, JoinMt otherwise) */
    TX_MSG_LEAVE,  /* §10.7.6.4 sL  */
    TX_MSG_IN,     /* §10.7.6.5 s   (In if Reg=IN, Mt otherwise)          */
};

/* Per-attribute instance: one Applicant SM + one Registrar SM */
struct mrp_attr_inst {
    uint8_t              attr_type;
    uint8_t              attr_val[32]; /* max attribute value size */
    enum mrp_appl_state  appl;         /* Applicant state          */
    enum mrp_reg_state   reg;          /* Registrar state          */
    uint32_t             leave_cs;     /* leavetimer countdown (cs) */
    enum tx_msg          pending_tx;   /* message scheduled for next tx */
    struct mrp_attr_inst *next;
};

/* Per-port MRP Participant state */
struct mrp_port_state {
    enum mrp_la_state    la;          /* LeaveAll SM state (Table 10-5) */
    enum mrp_pt_state    pt;          /* PeriodicTransmission SM state  */
    uint32_t             la_cs;       /* leavealltimer countdown (cs)   */
    uint32_t             pt_cs;       /* periodictimer countdown (cs)   */
    bool                 tx_pending;  /* transmission opportunity needed */
    struct mrp_attr_inst *attrs;      /* linked list of attribute instances */
};

/* Private data hanging off struct mrp_app */
struct mrp_priv {
    uint8_t              n_ports;
    struct mrp_port_state ports[]; /* flexible array */
};

/* ------------------------------------------------------------------ */
/* Applicant state machine — Table 10-3                                */
/* ------------------------------------------------------------------ */

/*
 * Entry format: {tx_msg, next_appl_state}
 * MRP_APPL_STATE_COUNT means "no transition" (stay in current state).
 */
struct appl_entry {
    enum tx_msg         tx;
    enum mrp_appl_state ns;
};
#define _X  { TX_MSG_NONE, MRP_APPL_STATE_COUNT }  /* no action, no state change */
#define _S(m, s) { (m), (s) }

/*
 * appl_table[event][state] — §10.7.7, Table 10-3.
 * Columns: VO, VP, VN, AN, AA, QA, LA, AO, QO, AP, QP, LO
 */
static const struct appl_entry appl_table[MRP_EVENT_COUNT][MRP_APPL_STATE_COUNT] = {
    /* MRP_EVENT_BEGIN */
    {
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* MRP_EVENT_NEW */
    {   /* VO       VP       VN       AN       AA       QA  */
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _X,
        _X, _X, _X,
        /* LA       AO       QO       AP       QP       LO */
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
    },
    /* MRP_EVENT_JOIN */
    {   /* VO       VP       VN       AN       AA       QA */
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X, _X, _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        /* LA       AO       QO       AP       QP       LO */
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_QP),
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
    },
    /* MRP_EVENT_LV */
    {   /* VO       VP       VN       AN       AA       QA */
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_LA),
        _S(TX_MSG_NONE, MRP_APPL_STATE_LA), _S(TX_MSG_NONE, MRP_APPL_STATE_LA), _S(TX_MSG_NONE, MRP_APPL_STATE_LA),
        /* LA       AO       QO       AP       QP       LO */
        _X, _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_QO), _X,
    },
    /* MRP_EVENT_TX — §10.7.5.7 */
    {   /* VO:  optional In/Mt */
        _S(TX_MSG_IN,   MRP_APPL_STATE_VO),
        /* VP: send Join → AA */
        _S(TX_MSG_JOIN, MRP_APPL_STATE_AA),
        /* VN: send New → AN */
        _S(TX_MSG_NEW,  MRP_APPL_STATE_AN),
        /* AN: send New → QA (§10.7 note 8: QA if Reg=IN, else AA) */
        _S(TX_MSG_NEW,  MRP_APPL_STATE_QA),
        /* AA: send Join (optional) — §10.7 note 6 */
        _S(TX_MSG_JOIN, MRP_APPL_STATE_QA),
        /* QA: optional In/Mt, stay QA */
        _S(TX_MSG_IN,   MRP_APPL_STATE_QA),
        /* LA: send Leave */
        _S(TX_MSG_LEAVE, MRP_APPL_STATE_LO),
        /* AO: optional In/Mt */
        _S(TX_MSG_IN,   MRP_APPL_STATE_AO),
        /* QO: optional In/Mt */
        _S(TX_MSG_IN,   MRP_APPL_STATE_QO),
        /* AP: send Join → QA */
        _S(TX_MSG_JOIN, MRP_APPL_STATE_QA),
        /* QP: optional In/Mt */
        _S(TX_MSG_IN,   MRP_APPL_STATE_QP),
        /* LO: send In/Mt */
        _S(TX_MSG_IN,   MRP_APPL_STATE_VO),
    },
    /* MRP_EVENT_TXLA — §10.7.5.8 (tx with LeaveAll) */
    {   /* VO: optional → LO */
        _S(TX_MSG_IN,    MRP_APPL_STATE_LO),
        /* VP: send something → LO */
        _S(TX_MSG_JOIN,  MRP_APPL_STATE_LO),
        /* VN: send New → AN (still need to declare) */
        _S(TX_MSG_NEW,   MRP_APPL_STATE_AN),
        /* AN: send New → VP (§10.7 note 9) */
        _S(TX_MSG_NEW,   MRP_APPL_STATE_VP),
        /* AA: send Join → VP (§10.7 note 9) */
        _S(TX_MSG_JOIN,  MRP_APPL_STATE_VP),
        /* QA: send Join, stay QA */
        _S(TX_MSG_JOIN,  MRP_APPL_STATE_QA),
        /* LA: optional → LO */
        _S(TX_MSG_LEAVE, MRP_APPL_STATE_LO),
        /* AO: optional → LO */
        _S(TX_MSG_IN,    MRP_APPL_STATE_LO),
        /* QO: optional → LO */
        _S(TX_MSG_IN,    MRP_APPL_STATE_LO),
        /* AP: send Join → QA */
        _S(TX_MSG_JOIN,  MRP_APPL_STATE_QA),
        /* QP: optional → LO */
        _S(TX_MSG_IN,    MRP_APPL_STATE_LO),
        /* LO: optional → LO */
        _S(TX_MSG_IN,    MRP_APPL_STATE_LO),
    },
    /* MRP_EVENT_TXLAF — §10.7.5.9 (tx, LeaveAll, PDU full — no room) */
    {   /* VO→LO  VP→VP  VN→VN  AN→VN  AA→VP  QA→VP */
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        /* LA→LO  AO→LO  QO→LO  AP→VP  QP→—  LO→— */
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _X, _X,
    },
    /* MRP_EVENT_RNEW */
    { _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X },
    /* MRP_EVENT_RJOININ */
    {   /* VO→AO  VP→AP  VN       AN       AA→QA    QA */
        _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_AP),
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QA), _X,
        /* LA→QO  AO→QO  QO       AP→QP    QP       LO */
        _S(TX_MSG_NONE, MRP_APPL_STATE_QO), _S(TX_MSG_NONE, MRP_APPL_STATE_QO),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QP), _X, _X,
    },
    /* MRP_EVENT_RJOINMT */
    {   /* VO  VP  VN  AN  AA (stay)  QA→AA */
        _X, _X, _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AA), _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        /* LA  AO (stay)  QO→AO  AP (stay)  QP→AP  LO→VO */
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_AO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_AP),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* MRP_EVENT_RIN */
    {   /* VO  VP  VN  AN  AA→QA (§10.7 note 5: only if point-to-point)  QA */
        _X, _X, _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QA), _X,
        _X, _X, _X, _X, _X, _X,
    },
    /* MRP_EVENT_RMT — same as RJOINMT for Applicant */
    {   _X, _X, _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AA), _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_AO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_AP),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* MRP_EVENT_RLV — received Leave */
    {   /* VO→LO  VP  VN→VN  AN→VP  AA→VP  QA (§10.7 note 10) */
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
        /* LA→LO  AO→LO  QO→LO  AP→VP  QP→VP  LO */
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* MRP_EVENT_RLA — received LeaveAll: same as RLV for Applicant */
    {   _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* MRP_EVENT_FLUSH — Flush! (Root/Alt → Designated) */
    { _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X },
    /* MRP_EVENT_REDECLARE — Re-declare! (Designated → Root/Alt) */
    {   _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* MRP_EVENT_PERIODIC — §10.7.5.10, §10.7.6.7 */
    {   _X, _X, _X, _X,
        /* AA: request another tx */
        _S(TX_MSG_JOIN, MRP_APPL_STATE_AA), _X, _X, _X, _X,
        /* AP: request another tx */
        _S(TX_MSG_JOIN, MRP_APPL_STATE_AP),
        _X, _X,
    },
    /* MRP_EVENT_LEAVETIMER — handled by Registrar SM only */
    { _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X },
    /* MRP_EVENT_LEAVEALLTIMER — handled by LeaveAll SM only */
    { _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X },
    /* MRP_EVENT_PERIODICTIMER — handled by PeriodicTransmission SM only */
    { _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X, _X },
};

#undef _X
#undef _S

/* ------------------------------------------------------------------ */
/* Registrar state machine — Table 10-4                                */
/* ------------------------------------------------------------------ */

enum reg_ind {
    REG_IND_NONE,
    REG_IND_NEW,
    REG_IND_JOIN,
    REG_IND_LV,
};

enum reg_timer {
    REG_TIMER_NONE,
    REG_TIMER_START,
    REG_TIMER_STOP,
};

struct reg_entry {
    enum reg_ind       ind;
    enum reg_timer     timer;
    enum mrp_reg_state ns;
};

#define _RX { REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_COUNT }
#define _RE(i, t, s) { (i), (t), (s) }

/*
 * reg_table[event][state] — Table 10-4.
 * Columns: IN, LV, MT
 * MRP_REG_STATE_COUNT = no state change.
 */
static const struct reg_entry reg_table[MRP_EVENT_COUNT][MRP_REG_STATE_COUNT] = {
    /* MRP_EVENT_BEGIN */
    {
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_MT),
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_MT),
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_MT),
    },
    /* MRP_EVENT_NEW — §10.7 Table 10-4 rNew! row */
    {
        _RE(REG_IND_NEW,  REG_TIMER_NONE, MRP_REG_STATE_IN),  /* IN: New; IN          */
        _RE(REG_IND_NEW,  REG_TIMER_STOP, MRP_REG_STATE_IN),  /* LV: New, Stop; IN    */
        _RE(REG_IND_NEW,  REG_TIMER_NONE, MRP_REG_STATE_IN),  /* MT: New; IN          */
    },
    /* MRP_EVENT_JOIN — ignored by Registrar (handled by Applicant) */
    { _RX, _RX, _RX },
    /* MRP_EVENT_LV — ignored */
    { _RX, _RX, _RX },
    /* MRP_EVENT_TX — Registrar ignores tx events */
    { _RX, _RX, _RX },
    /* MRP_EVENT_TXLA */
    {   /* IN: start leavetimer → LV */
        _RE(REG_IND_NONE, REG_TIMER_START, MRP_REG_STATE_LV),
        _RX, _RX,
    },
    /* MRP_EVENT_TXLAF */
    { _RX, _RX, _RX },
    /* MRP_EVENT_RNEW — same as rNew! in Table 10-4 */
    {
        _RE(REG_IND_NEW,  REG_TIMER_NONE, MRP_REG_STATE_IN),
        _RE(REG_IND_NEW,  REG_TIMER_STOP, MRP_REG_STATE_IN),
        _RE(REG_IND_NEW,  REG_TIMER_NONE, MRP_REG_STATE_IN),
    },
    /* MRP_EVENT_RJOININ || MRP_EVENT_RJOINMT — Table 10-4 rJoinIn!||rJoinMt! row */
    {
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_IN),  /* IN: stay IN          */
        _RE(REG_IND_JOIN, REG_TIMER_STOP, MRP_REG_STATE_IN),  /* LV: Stop, Join; IN   */
        _RE(REG_IND_JOIN, REG_TIMER_NONE, MRP_REG_STATE_IN),  /* MT: Join; IN         */
    },
    /* MRP_EVENT_RJOINMT — same entry as RJOININ for Registrar */
    {
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_IN),
        _RE(REG_IND_JOIN, REG_TIMER_STOP, MRP_REG_STATE_IN),
        _RE(REG_IND_JOIN, REG_TIMER_NONE, MRP_REG_STATE_IN),
    },
    /* MRP_EVENT_RIN — ignored by Registrar */
    { _RX, _RX, _RX },
    /* MRP_EVENT_RMT — ignored by Registrar */
    { _RX, _RX, _RX },
    /* MRP_EVENT_RLV — Table 10-4 rLv!||rLA!||Re-declare! row */
    {
        _RE(REG_IND_NONE, REG_TIMER_START, MRP_REG_STATE_LV), /* IN: Start leavetimer; LV */
        _RX,                                /* LV: -x-                  */
        _RX,                                /* MT: -x-                  */
    },
    /* MRP_EVENT_RLA — same as RLV for Registrar */
    {
        _RE(REG_IND_NONE, REG_TIMER_START, MRP_REG_STATE_LV),
        _RX,
        _RX,
    },
    /* MRP_EVENT_FLUSH — Table 10-4 Flush! row */
    {
        _RE(REG_IND_LV, REG_TIMER_NONE, MRP_REG_STATE_MT),    /* IN: Lv; MT            */
        _RE(REG_IND_LV, REG_TIMER_NONE, MRP_REG_STATE_MT),    /* LV: Lv; MT            */
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_MT),  /* MT: stay MT           */
    },
    /* MRP_EVENT_REDECLARE — same as RLV for Registrar */
    {
        _RE(REG_IND_NONE, REG_TIMER_START, MRP_REG_STATE_LV),
        _RX,
        _RX,
    },
    /* MRP_EVENT_PERIODIC — ignored */
    { _RX, _RX, _RX },
    /* MRP_EVENT_LEAVETIMER — Table 10-4 leavetimer! row */
    {
        _RX,                                /* IN: -x-               */
        _RE(REG_IND_LV, REG_TIMER_NONE, MRP_REG_STATE_MT),    /* LV: Lv; MT            */
        _RE(REG_IND_NONE, REG_TIMER_NONE, MRP_REG_STATE_MT),  /* MT: stay MT           */
    },
    /* MRP_EVENT_LEAVEALLTIMER — ignored by Registrar */
    { _RX, _RX, _RX },
    /* MRP_EVENT_PERIODICTIMER — ignored by Registrar */
    { _RX, _RX, _RX },
};
#undef _RX
#undef _RE

/* ------------------------------------------------------------------ */
/* Internal helpers                                                     */
/* ------------------------------------------------------------------ */

static struct mrp_priv *priv_of(struct mrp_app *app)
{
    return (struct mrp_priv *)app->priv;
}

static struct mrp_attr_inst *find_attr(struct mrp_port_state *ps, const struct mrp_app_ops *ops,
                                   uint8_t type, const void *val)
{
    for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next)
        if (a->attr_type == type && ops->attr_cmp(type, a->attr_val, val) == 0)
            return a;
    return NULL;
}

static struct mrp_attr_inst *get_or_create_attr(struct mrp_port_state *ps,
                                            const struct mrp_app_ops *ops,
                                            uint8_t type, const void *val)
{
    struct mrp_attr_inst *a = find_attr(ps, ops, type, val);
    if (a) return a;

    a = shlan_calloc(1, sizeof(*a) + ops->attr_len(type));
    if (!a) return NULL;

    a->attr_type = type;
    memcpy(a->attr_val, val, ops->attr_len(type));
    a->appl       = MRP_APPL_STATE_VO;
    a->reg        = MRP_REG_STATE_MT;
    a->pending_tx = TX_MSG_NONE;
    a->next       = ps->attrs;
    ps->attrs     = a;
    return a;
}

/* Apply one Applicant SM event to an attribute instance. */
static void appl_event(struct mrp_attr_inst *ai, enum mrp_event ev)
{
    const struct appl_entry *e = &appl_table[ev][ai->appl];
    if (e->ns != MRP_APPL_STATE_COUNT)
        ai->appl = e->ns;
    if (e->tx != TX_MSG_NONE)
        ai->pending_tx = e->tx;
}

/* Apply one Registrar SM event; issues MAD indications via ops callbacks. */
static void reg_event(struct mrp_app *app, struct mrp_attr_inst *ai,
                      enum mrp_event ev, uint8_t port_id)
{
    const struct reg_entry *e = &reg_table[ev][ai->reg];

    if (e->ns != MRP_REG_STATE_COUNT)
        ai->reg = e->ns;

    switch (e->timer) {
    case REG_TIMER_START: ai->leave_cs = MRP_LEAVE_TIME_CS; break;
    case REG_TIMER_STOP:  ai->leave_cs = 0; break;
    default: break;
    }

    switch (e->ind) {
    case REG_IND_NEW:
        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, true);
        break;
    case REG_IND_JOIN:
        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, false);
        break;
    case REG_IND_LV:
        app->ops->leave_ind(app, port_id, ai->attr_type, ai->attr_val);
        break;
    default:
        break;
    }
}

/* Deliver an event to both Applicant and Registrar SMs for one attribute. */
static void deliver_event(struct mrp_app *app, struct mrp_port_state *ps,
                          struct mrp_attr_inst *ai, enum mrp_event ev, uint8_t port_id)
{
    (void)ps;
    appl_event(ai, ev);
    reg_event(app, ai, ev, port_id);
}

/* Broadcast an event to all attributes on a port. */
static void broadcast_event(struct mrp_app *app, struct mrp_port_state *ps,
                             enum mrp_event ev, uint8_t port_id)
{
    for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next)
        deliver_event(app, ps, a, ev, port_id);
}

/* ------------------------------------------------------------------ */
/* LeaveAll state machine — Table 10-5                                 */
/* ------------------------------------------------------------------ */

static void la_event(struct mrp_app *app, struct mrp_port_state *ps,
                     enum mrp_event ev, uint8_t port_id)
{
    switch (ev) {
    case MRP_EVENT_BEGIN:
        ps->la    = MRP_LA_STATE_PASSIVE;
        ps->la_cs = MRP_LEAVEALL_TIME_CS;
        break;

    case MRP_EVENT_TX:
        if (ps->la == MRP_LA_STATE_ACTIVE) {
            /* sLA: send LeaveAll, reset timer, go Passive */
            ps->la    = MRP_LA_STATE_PASSIVE;
            ps->la_cs = MRP_LEAVEALL_TIME_CS;
            /* Also generate rLA! for all local Applicant/Registrar SMs */
            broadcast_event(app, ps, MRP_EVENT_RLA, port_id);
        }
        break;

    case MRP_EVENT_RLA:
        ps->la    = MRP_LA_STATE_PASSIVE;
        ps->la_cs = MRP_LEAVEALL_TIME_CS;
        break;

    case MRP_EVENT_LEAVEALLTIMER:
        /* Timer expired → Active, request tx so sLA can fire */
        ps->la    = MRP_LA_STATE_ACTIVE;
        ps->la_cs = MRP_LEAVEALL_TIME_CS; /* restart for next cycle */
        ps->tx_pending = true;
        break;

    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* PeriodicTransmission state machine — Table 10-6                     */
/* ------------------------------------------------------------------ */

static void pt_event(struct mrp_app *app, struct mrp_port_state *ps,
                     enum mrp_event ev, uint8_t port_id)
{
    switch (ev) {
    case MRP_EVENT_BEGIN:
        ps->pt    = MRP_PT_STATE_ACTIVE;
        ps->pt_cs = MRP_JOIN_TIME_CS;
        break;

    case MRP_EVENT_PERIODICTIMER:
        if (ps->pt == MRP_PT_STATE_ACTIVE) {
            ps->pt_cs = MRP_JOIN_TIME_CS; /* restart */
            /* Generate periodic! for all Applicant SMs */
            broadcast_event(app, ps, MRP_EVENT_PERIODIC, port_id);
            ps->tx_pending = true;
        }
        break;

    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

struct mrp_app *mrp_app_create(const struct mrp_app_ops *ops, uint8_t n_ports)
{
    struct mrp_app     *app      = shlan_calloc(1, sizeof(*app));
    struct mrp_app_ops *ops_copy = shlan_calloc(1, sizeof(*ops_copy));
    struct mrp_priv    *priv     = shlan_calloc(1, sizeof(*priv) +
                               n_ports * sizeof(struct mrp_port_state));
    if (!app || !ops_copy || !priv) {
        shlan_free(app); shlan_free(ops_copy); shlan_free(priv); return NULL;
    }

    *ops_copy  = *ops;   /* deep-copy the vtable */
    app->ops   = ops_copy;
    app->priv  = priv;
    priv->n_ports = n_ports;

    /* Initialise each port's state machines via Begin! */
    for (uint8_t p = 0; p < n_ports; p++) {
        struct mrp_port_state *ps = &priv->ports[p];
        la_event(app, ps, MRP_EVENT_BEGIN, p);
        pt_event(app, ps, MRP_EVENT_BEGIN, p);
    }
    return app;
}

void mrp_app_destroy(struct mrp_app *app)
{
    if (!app) return;
    struct mrp_priv *priv = priv_of(app);
    for (uint8_t p = 0; p < priv->n_ports; p++) {
        struct mrp_attr_inst *a = priv->ports[p].attrs;
        while (a) {
            struct mrp_attr_inst *next = a->next;
            shlan_free(a);
            a = next;
        }
    }
    shlan_free(priv);
    shlan_free((void *)app->ops); /* free the ops_copy allocated in mrp_app_create */
    shlan_free(app);
}

int mrp_mad_join(struct mrp_app *app, uint8_t port_id,
                 uint8_t attr_type, const void *attr_val, bool is_new)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];
    struct mrp_attr_inst  *ai   = get_or_create_attr(ps, app->ops, attr_type, attr_val);
    if (!ai) return -ENOMEM;

    deliver_event(app, ps, ai, is_new ? MRP_EVENT_NEW : MRP_EVENT_JOIN, port_id);
    ps->tx_pending = true;
    return 0;
}

int mrp_mad_leave(struct mrp_app *app, uint8_t port_id,
                  uint8_t attr_type, const void *attr_val)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];
    struct mrp_attr_inst  *ai   = find_attr(ps, app->ops, attr_type, attr_val);
    if (!ai) return 0; /* nothing to withdraw */

    deliver_event(app, ps, ai, MRP_EVENT_LV, port_id);
    ps->tx_pending = true;
    return 0;
}

/* Callback context passed into mrpdu_parse() */
struct rx_ctx {
    struct mrp_app        *app;
    struct mrp_port_state *ps;
    uint8_t                port_id;
};

static void rx_on_attr(void *raw_ctx, uint8_t attr_type,
                       enum mrp_attr_event attr_event, const void *attr_val)
{
    struct rx_ctx        *rc = (struct rx_ctx *)raw_ctx;
    struct mrp_attr_inst *ai = get_or_create_attr(rc->ps, rc->app->ops,
                                              attr_type, attr_val);
    if (!ai) return;

    /* Map wire AttributeEvent → internal MRP event */
    enum mrp_event ev;
    switch (attr_event) {
    case MRP_ATTR_EVENT_NEW:    ev = MRP_EVENT_RNEW;    break;
    case MRP_ATTR_EVENT_JOININ: ev = MRP_EVENT_RJOININ; break;
    case MRP_ATTR_EVENT_IN:     ev = MRP_EVENT_RIN;     break;
    case MRP_ATTR_EVENT_JOINMT: ev = MRP_EVENT_RJOINMT; break;
    case MRP_ATTR_EVENT_MT:     ev = MRP_EVENT_RMT;     break;
    case MRP_ATTR_EVENT_LV:     ev = MRP_EVENT_RLV;     break;
    default: return;
    }
    deliver_event(rc->app, rc->ps, ai, ev, rc->port_id);
}

static void rx_on_leaveall(void *raw_ctx, uint8_t attr_type)
{
    struct rx_ctx *rc = (struct rx_ctx *)raw_ctx;
    (void)attr_type;
    la_event(rc->app, rc->ps, MRP_EVENT_RLA, rc->port_id);
    broadcast_event(rc->app, rc->ps, MRP_EVENT_RLA, rc->port_id);
}

int mrp_rx(struct mrp_app *app, uint8_t port_id,
           const uint8_t *pdu, size_t pdu_len)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];

    struct rx_ctx ctx = { .app = app, .ps = ps, .port_id = port_id };
    return mrpdu_parse(pdu, pdu_len, app->ops,
                       rx_on_attr, rx_on_leaveall, &ctx);
}

void mrp_tick(struct mrp_app *app, uint8_t port_id)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];

    /* leavealltimer */
    if (ps->la_cs > 0 && --ps->la_cs == 0)
        la_event(app, ps, MRP_EVENT_LEAVEALLTIMER, port_id);

    /* periodictimer */
    if (ps->pt_cs > 0 && --ps->pt_cs == 0)
        pt_event(app, ps, MRP_EVENT_PERIODICTIMER, port_id);

    /* leavetimer per attribute */
    for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next) {
        if (a->leave_cs > 0 && --a->leave_cs == 0)
            reg_event(app, a, MRP_EVENT_LEAVETIMER, port_id);
    }
}

void mrp_port_role_change(struct mrp_app *app, uint8_t port_id, bool flush)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];
    enum mrp_event    ev   = flush ? MRP_EVENT_FLUSH : MRP_EVENT_REDECLARE;
    broadcast_event(app, ps, ev, port_id);
    if (flush)
        la_event(app, ps, MRP_EVENT_LEAVEALLTIMER, port_id); /* §10.7.5.22 */
}

void mrp_set_periodic(struct mrp_app *app, uint8_t port_id, bool enable)
{
    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];
    if (enable && ps->pt == MRP_PT_STATE_PASSIVE) {
        ps->pt    = MRP_PT_STATE_ACTIVE;
        ps->pt_cs = MRP_JOIN_TIME_CS;
    } else if (!enable && ps->pt == MRP_PT_STATE_ACTIVE) {
        ps->pt = MRP_PT_STATE_PASSIVE;
    }
}
