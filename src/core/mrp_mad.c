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
#include "ports/timer.h"

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

/*
 * Callback argument types for port- and attribute-level timers.
 * Embedded directly in the state structs to avoid separate heap allocation.
 */

struct mrp_port_timer_arg {
    struct mrp_app *app;
    uint8_t         port_id;
};

/* mrp_attr_inst is defined below; the pointer in mrp_attr_timer_arg only
 * requires a forward declaration here. */
struct mrp_attr_inst;

struct mrp_attr_timer_arg {
    struct mrp_app       *app;
    struct mrp_attr_inst *ai;
    uint8_t               port_id;
};

/* Forward declarations — bodies follow the state machine functions. */
static void on_la_timer(void *arg);
static void on_pt_timer(void *arg);
static void on_leave_timer(void *arg);

/* Per-attribute instance: one Applicant SM + one Registrar SM */
struct mrp_attr_inst {
    uint8_t              attr_type;
    /* Largest in-memory value (struct msrp_talker_failed) with margin;
     * see attr_store_len(). */
    uint8_t              attr_val[48];
    enum mrp_appl_state  appl;         /* Applicant state          */
    enum mrp_reg_state   reg;          /* Registrar state          */
    enum tx_msg          pending_tx;   /* message scheduled for next tx */
    struct mrp_attr_inst *next;
    /* Leave timer: fires MRP_EVENT_LEAVETIMER into the Registrar SM on expiry */
    struct shlan_timer          leave_timer;
    struct mrp_attr_timer_arg   leave_timer_arg;
};

/* Per-port MRP Participant state */
struct mrp_port_state {
    enum mrp_la_state    la;          /* LeaveAll SM state (Table 10-5) */
    enum mrp_pt_state    pt;          /* PeriodicTransmission SM state  */
    bool                 tx_pending;  /* transmission opportunity needed */
    struct mrp_attr_inst *attrs;      /* linked list of attribute instances */
    /* LeaveAll timer: fires MRP_EVENT_LEAVEALLTIMER on expiry */
    struct shlan_timer          la_timer;
    /* PeriodicTransmission timer: fires MRP_EVENT_PERIODICTIMER on expiry */
    struct shlan_timer          pt_timer;
    /* Shared callback arg for la_timer and pt_timer (same app + port_id) */
    struct mrp_port_timer_arg   timer_arg;
};

/* Private data hanging off struct mrp_app */
struct mrp_priv {
    uint8_t              n_ports;
    /* Optional transition observer (mrp_set_observer) */
    void               (*obs_fn)(void *ctx, const struct mrp_transition *t);
    void                *obs_ctx;
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

uint8_t mrp_app_n_ports(const struct mrp_app *app)
{
    return priv_of((struct mrp_app *)app)->n_ports;
}

uint32_t mrp_attr_registered_ports(const struct mrp_app *app,
                                   uint8_t attr_type, const void *attr_val)
{
    const struct mrp_priv *priv = priv_of((struct mrp_app *)app);
    uint32_t mask = 0;
    for (uint8_t p = 0; p < priv->n_ports && p < 32u; p++) {
        const struct mrp_port_state *ps = &priv->ports[p];
        for (const struct mrp_attr_inst *a = ps->attrs; a; a = a->next) {
            if (a->attr_type == attr_type &&
                app->ops->attr_cmp(attr_type, a->attr_val, attr_val) == 0 &&
                a->reg == MRP_REG_STATE_IN) {
                mask |= (1u << p);
                break;
            }
        }
    }
    return mask;
}

static struct mrp_attr_inst *find_attr(struct mrp_port_state *ps, const struct mrp_app_ops *ops,
                                   uint8_t type, const void *val)
{
    for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next)
        if (a->attr_type == type && ops->attr_cmp(type, a->attr_val, val) == 0)
            return a;
    return NULL;
}

/*
 * Stored value length: the in-memory representation the app's
 * decode_attr produces (attr_mem_len), falling back to the wire
 * FirstValue length when the two are identical.
 */
static size_t attr_store_len(const struct mrp_app_ops *ops, uint8_t type)
{
    size_t n = ops->attr_mem_len ? ops->attr_mem_len(type)
                                 : ops->attr_len(type);

    if (n > sizeof(((struct mrp_attr_inst *)0)->attr_val)) {
        n = sizeof(((struct mrp_attr_inst *)0)->attr_val);
    }
    return n;
}

static struct mrp_attr_inst *get_or_create_attr(struct mrp_app *app,
                                            struct mrp_port_state *ps,
                                            uint8_t port_id,
                                            uint8_t type, const void *val)
{
    const struct mrp_app_ops *ops = app->ops;
    struct mrp_attr_inst *a = find_attr(ps, ops, type, val);
    if (a) {
        /*
         * Refresh the stored value: identity (attr_cmp) is unchanged,
         * but the payload may not be — a re-advertised Talker TSpec,
         * a Listener declaration subtype.
         */
        memcpy(a->attr_val, val, attr_store_len(ops, type));
        return a;
    }

    a = shlan_calloc(1, sizeof(*a));
    if (!a) {
        return NULL;
    }

    a->attr_type = type;
    memcpy(a->attr_val, val, attr_store_len(ops, type));
    a->appl       = MRP_APPL_STATE_VO;
    a->reg        = MRP_REG_STATE_MT;
    a->pending_tx = TX_MSG_NONE;
    a->next       = ps->attrs;
    ps->attrs     = a;

    a->leave_timer_arg.app     = app;
    a->leave_timer_arg.ai      = a;
    a->leave_timer_arg.port_id = port_id;
    shlan_timer_init(&a->leave_timer, on_leave_timer, &a->leave_timer_arg);

    return a;
}

/* Apply one Applicant SM event to an attribute instance. */
static void appl_event(struct mrp_attr_inst *ai, enum mrp_event ev)
{
    const struct appl_entry *e = &appl_table[ev][ai->appl];
    if (e->ns != MRP_APPL_STATE_COUNT) {
        ai->appl = e->ns;
    }
    if (e->tx != TX_MSG_NONE) {
        ai->pending_tx = e->tx;
    }
}

/*
 * MAP helpers — apply the port bitmask returned by map_join / map_leave.
 *
 * map_apply_join uses is_new=false (MRP_EVENT_JOIN).  The Registrar SM
 * ignores MRP_EVENT_JOIN, so no join_ind fires on the target ports and
 * there is no indication loop.
 */
static void map_apply_join(struct mrp_app *app, uint8_t src_port,
                           uint8_t attr_type, const void *attr_val)
{
    if (!app->ops->map_join) {
        return;
    }
    uint32_t ports = app->ops->map_join(app, src_port, attr_type, attr_val);
    if (!ports) {
        return;
    }
    uint8_t n = priv_of(app)->n_ports;
    for (uint8_t p = 0; p < n && p < 32u; p++) {
        if (ports & (1u << p)) {
            mrp_mad_join(app, p, attr_type, attr_val, false);
        }
    }
}

static void map_apply_leave(struct mrp_app *app, uint8_t src_port,
                            uint8_t attr_type, const void *attr_val)
{
    if (!app->ops->map_leave) {
        return;
    }
    uint32_t ports = app->ops->map_leave(app, src_port, attr_type, attr_val);
    if (!ports) {
        return;
    }
    uint8_t n = priv_of(app)->n_ports;
    for (uint8_t p = 0; p < n && p < 32u; p++) {
        if (ports & (1u << p)) {
            mrp_mad_leave(app, p, attr_type, attr_val);
        }
    }
}

/* Apply one Registrar SM event; issues MAD indications via ops callbacks. */
static void reg_event(struct mrp_app *app, struct mrp_attr_inst *ai,
                      enum mrp_event ev, uint8_t port_id)
{
    const struct reg_entry *e = &reg_table[ev][ai->reg];

    if (e->ns != MRP_REG_STATE_COUNT) {
        ai->reg = e->ns;
    }

    switch (e->timer) {
    case REG_TIMER_START: shlan_timer_arm(&ai->leave_timer, MRP_LEAVE_TIME_CS); break;
    case REG_TIMER_STOP:  shlan_timer_disarm(&ai->leave_timer);                 break;
    default:                                                                     break;
    }

    switch (e->ind) {
    case REG_IND_NEW:
        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, true);
        map_apply_join(app, port_id, ai->attr_type, ai->attr_val);
        break;
    case REG_IND_JOIN:
        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, false);
        map_apply_join(app, port_id, ai->attr_type, ai->attr_val);
        break;
    case REG_IND_LV:
        app->ops->leave_ind(app, port_id, ai->attr_type, ai->attr_val);
        map_apply_leave(app, port_id, ai->attr_type, ai->attr_val);
        break;
    default:
        break;
    }
}

/*
 * Report an Applicant/Registrar state change to the registered observer.
 * Called with the states captured before the event was applied.
 */
static void observe(struct mrp_app *app, const struct mrp_attr_inst *ai,
                    enum mrp_event ev, uint8_t port_id,
                    enum mrp_appl_state appl_from, enum mrp_reg_state reg_from)
{
    struct mrp_priv *priv = priv_of(app);

    if (!priv->obs_fn) {
        return;
    }
    if (ai->appl == appl_from && ai->reg == reg_from) {
        return; /* the event changed nothing */
    }

    struct mrp_transition t = {
        .port_id   = port_id,
        .attr_type = ai->attr_type,
        .attr_val  = ai->attr_val,
        .event     = ev,
        .appl_from = appl_from,
        .appl_to   = ai->appl,
        .reg_from  = reg_from,
        .reg_to    = ai->reg,
    };
    priv->obs_fn(priv->obs_ctx, &t);
}

/* Deliver an event to both Applicant and Registrar SMs for one attribute. */
static void deliver_event(struct mrp_app *app, struct mrp_port_state *ps,
                          struct mrp_attr_inst *ai, enum mrp_event ev, uint8_t port_id)
{
    enum mrp_appl_state appl_from = ai->appl;
    enum mrp_reg_state  reg_from  = ai->reg;

    (void)ps;
    appl_event(ai, ev);
    reg_event(app, ai, ev, port_id);
    observe(app, ai, ev, port_id, appl_from, reg_from);
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
        ps->la = MRP_LA_STATE_PASSIVE;
        shlan_timer_arm(&ps->la_timer, MRP_LEAVEALL_TIME_CS);
        break;

    case MRP_EVENT_TX:
        if (ps->la == MRP_LA_STATE_ACTIVE) {
            /* sLA: send LeaveAll, reset timer, go Passive */
            ps->la = MRP_LA_STATE_PASSIVE;
            shlan_timer_arm(&ps->la_timer, MRP_LEAVEALL_TIME_CS);
            /* Also generate rLA! for all local Applicant/Registrar SMs */
            broadcast_event(app, ps, MRP_EVENT_RLA, port_id);
        }
        break;

    case MRP_EVENT_RLA:
        ps->la = MRP_LA_STATE_PASSIVE;
        shlan_timer_arm(&ps->la_timer, MRP_LEAVEALL_TIME_CS);
        break;

    case MRP_EVENT_LEAVEALLTIMER:
        /* Timer expired → Active, request tx so sLA can fire */
        ps->la = MRP_LA_STATE_ACTIVE;
        shlan_timer_arm(&ps->la_timer, MRP_LEAVEALL_TIME_CS); /* restart for next cycle */
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
        ps->pt = MRP_PT_STATE_ACTIVE;
        shlan_timer_arm(&ps->pt_timer, MRP_JOIN_TIME_CS);
        break;

    case MRP_EVENT_PERIODICTIMER:
        if (ps->pt == MRP_PT_STATE_ACTIVE) {
            shlan_timer_arm(&ps->pt_timer, MRP_JOIN_TIME_CS); /* restart */
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
/* Timer callbacks                                                      */
/* ------------------------------------------------------------------ */

static void on_la_timer(void *arg)
{
    struct mrp_port_timer_arg *a  = (struct mrp_port_timer_arg *)arg;
    struct mrp_port_state     *ps = &priv_of(a->app)->ports[a->port_id];
    la_event(a->app, ps, MRP_EVENT_LEAVEALLTIMER, a->port_id);
}

static void on_pt_timer(void *arg)
{
    struct mrp_port_timer_arg *a  = (struct mrp_port_timer_arg *)arg;
    struct mrp_port_state     *ps = &priv_of(a->app)->ports[a->port_id];
    pt_event(a->app, ps, MRP_EVENT_PERIODICTIMER, a->port_id);
}

static void on_leave_timer(void *arg)
{
    struct mrp_attr_timer_arg *a = (struct mrp_attr_timer_arg *)arg;
    enum mrp_appl_state appl_from = a->ai->appl;
    enum mrp_reg_state  reg_from  = a->ai->reg;

    reg_event(a->app, a->ai, MRP_EVENT_LEAVETIMER, a->port_id);
    observe(a->app, a->ai, MRP_EVENT_LEAVETIMER, a->port_id,
            appl_from, reg_from);
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

    /* Initialise each port's timers and state machines via Begin! */
    for (uint8_t p = 0; p < n_ports; p++) {
        struct mrp_port_state *ps = &priv->ports[p];
        ps->timer_arg.app     = app;
        ps->timer_arg.port_id = p;
        shlan_timer_init(&ps->la_timer, on_la_timer, &ps->timer_arg);
        shlan_timer_init(&ps->pt_timer, on_pt_timer, &ps->timer_arg);
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
    struct mrp_attr_inst  *ai   = get_or_create_attr(app, ps, port_id, attr_type, attr_val);
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
    struct mrp_attr_inst *ai = get_or_create_attr(rc->app, rc->ps,
                                              rc->port_id, attr_type, attr_val);
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
    (void)app;
    (void)port_id;
    shlan_timer_tick();
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
        ps->pt = MRP_PT_STATE_ACTIVE;
        shlan_timer_arm(&ps->pt_timer, MRP_JOIN_TIME_CS);
    } else if (!enable && ps->pt == MRP_PT_STATE_ACTIVE) {
        ps->pt = MRP_PT_STATE_PASSIVE;
        shlan_timer_disarm(&ps->pt_timer);
    }
}

/* ------------------------------------------------------------------ */
/* Introspection and observability                                      */
/* ------------------------------------------------------------------ */

void mrp_set_observer(struct mrp_app *app,
                      void (*fn)(void *ctx, const struct mrp_transition *t),
                      void *ctx)
{
    struct mrp_priv *priv = priv_of(app);

    priv->obs_fn  = fn;
    priv->obs_ctx = ctx;
}

int mrp_attr_visit(const struct mrp_app *app, uint8_t port_id,
                   void (*visit)(void *ctx, const struct mrp_attr_status *st),
                   void *ctx)
{
    const struct mrp_priv *priv = priv_of((struct mrp_app *)app);
    int count = 0;

    if (port_id >= priv->n_ports) {
        return -EINVAL;
    }

    for (const struct mrp_attr_inst *a = priv->ports[port_id].attrs;
         a; a = a->next) {
        if (visit) {
            struct mrp_attr_status st = {
                .port_id   = port_id,
                .attr_type = a->attr_type,
                .attr_val  = a->attr_val,
                .appl      = a->appl,
                .reg       = a->reg,
            };
            visit(ctx, &st);
        }
        count++;
    }
    return count;
}

int mrp_port_status(const struct mrp_app *app, uint8_t port_id,
                    enum mrp_la_state *la, enum mrp_pt_state *pt)
{
    const struct mrp_priv *priv = priv_of((struct mrp_app *)app);

    if (port_id >= priv->n_ports) {
        return -EINVAL;
    }
    if (la) {
        *la = priv->ports[port_id].la;
    }
    if (pt) {
        *pt = priv->ports[port_id].pt;
    }
    return 0;
}

/* §10.7.7 / §10.7.8 state abbreviations and §10.7.5 event names */
static const char *const appl_state_names[MRP_APPL_STATE_COUNT] = {
    "VO", "VP", "VN", "AN", "AA", "QA", "LA", "AO", "QO", "AP", "QP", "LO",
};

static const char *const reg_state_names[MRP_REG_STATE_COUNT] = {
    "IN", "LV", "MT",
};

static const char *const event_names[MRP_EVENT_COUNT] = {
    "Begin!", "New!", "Join!", "Lv!", "tx!", "txLA!", "txLAF!",
    "rNew!", "rJoinIn!", "rJoinMt!", "rIn!", "rMt!", "rLv!", "rLA!",
    "Flush!", "Re-declare!", "periodic!", "leavetimer!", "leavealltimer!",
    "periodictimer!",
};

const char *mrp_appl_state_name(enum mrp_appl_state s)
{
    if ((unsigned int)s >= MRP_APPL_STATE_COUNT) {
        return "?";
    }
    return appl_state_names[s];
}

const char *mrp_reg_state_name(enum mrp_reg_state s)
{
    if ((unsigned int)s >= MRP_REG_STATE_COUNT) {
        return "?";
    }
    return reg_state_names[s];
}

const char *mrp_event_name(enum mrp_event ev)
{
    if ((unsigned int)ev >= MRP_EVENT_COUNT) {
        return "?";
    }
    return event_names[ev];
}
