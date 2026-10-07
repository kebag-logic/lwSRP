/* SPDX-License-Identifier: Apache-2.0 */
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

#include "shish_lan/error.h"
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
static void on_join_timer(void *arg);

/* Per-attribute instance: one Applicant SM + one Registrar SM */
struct mrp_attr_inst {
    uint8_t              attr_type;
    /* Largest in-memory value (struct msrp_talker_failed) with margin;
     * see attr_store_len(). */
    _Alignas(max_align_t) uint8_t attr_val[48];
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
    uint32_t join_cs;
    uint32_t leave_cs;
    uint32_t leaveall_cs;
    uint32_t join_wait;
    uint32_t random;
    bool point_to_point;
    bool in_send;
    bool periodic_owed;
    bool prepared_la;
    uint8_t *prepared_pdu;
    size_t prepared_len;
    struct mrp_attr_inst *attrs;      /* linked list of attribute instances */
    /* LeaveAll timer: fires MRP_EVENT_LEAVEALLTIMER on expiry */
    struct shlan_timer          la_timer;
    /* PeriodicTransmission timer: fires MRP_EVENT_PERIODICTIMER on expiry */
    struct shlan_timer          pt_timer;
    struct shlan_timer          join_timer;
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
    /* BEGIN: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_BEGIN] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* NEW: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_NEW] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _X,
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
    },
    /* JOIN: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_JOIN] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X, _X,
        _X, _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_AA), _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_QP),
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
    },
    /* LV: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_LV] = {
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_VO), _S(TX_MSG_NONE, MRP_APPL_STATE_LA),
        _S(TX_MSG_NONE, MRP_APPL_STATE_LA), _S(TX_MSG_NONE, MRP_APPL_STATE_LA), _S(TX_MSG_NONE, MRP_APPL_STATE_LA),
        _X, _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_QO), _X,
    },
    /* TX: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_TX] = {
        _X, _S(TX_MSG_JOIN, MRP_APPL_STATE_AA), _S(TX_MSG_NEW, MRP_APPL_STATE_AN),
        _S(TX_MSG_NEW, MRP_APPL_STATE_QA), _S(TX_MSG_JOIN, MRP_APPL_STATE_QA), _X,
        _S(TX_MSG_LEAVE, MRP_APPL_STATE_VO), _X, _X,
        _S(TX_MSG_JOIN, MRP_APPL_STATE_QA), _X, _S(TX_MSG_IN, MRP_APPL_STATE_VO),
    },
    /* TXLA: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_TXLA] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_IN, MRP_APPL_STATE_AA), _S(TX_MSG_NEW, MRP_APPL_STATE_AN),
        _S(TX_MSG_NEW, MRP_APPL_STATE_QA), _S(TX_MSG_JOIN, MRP_APPL_STATE_QA), _S(TX_MSG_JOIN, MRP_APPL_STATE_QA),
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_JOIN, MRP_APPL_STATE_QA), _S(TX_MSG_JOIN, MRP_APPL_STATE_QA), _X,
    },
    /* TXLAF: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_TXLAF] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VN),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* RNEW: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RNEW] = {
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
    },
    /* RJOININ: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RJOININ] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_AO), _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _X,
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QA), _X,
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QO), _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_QP), _X, _X,
    },
    /* RJOINMT: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RJOINMT] = {
        _X, _X, _X,
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AO),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* RIN: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RIN] = {
        _X, _X, _X,
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_QA), _X,
        _X, _X, _X,
        _X, _X, _X,
    },
    /* RMT: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RMT] = {
        _X, _X, _X,
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AO),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _S(TX_MSG_NONE, MRP_APPL_STATE_VO),
    },
    /* RLV: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RLV] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* RLA: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_RLA] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* FLUSH: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_FLUSH] = {
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
    },
    /* REDECLARE: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_REDECLARE] = {
        _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _X, _X,
        _S(TX_MSG_NONE, MRP_APPL_STATE_VN), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP),
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_LO), _S(TX_MSG_NONE, MRP_APPL_STATE_LO),
        _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _S(TX_MSG_NONE, MRP_APPL_STATE_VP), _X,
    },
    /* PERIODIC: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_PERIODIC] = {
        _X, _X, _X,
        _X, _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AA),
        _X, _X, _X,
        _X, _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _X,
    },
    /* LEAVETIMER: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_LEAVETIMER] = {
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
    },
    /* LEAVEALLTIMER: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_LEAVEALLTIMER] = {
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
    },
    /* PERIODICTIMER: VO VP VN AN AA QA LA AO QO AP QP LO */
    [MRP_EVENT_PERIODICTIMER] = {
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
        _X, _X, _X,
    },
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
    /* Local New never registers a peer. */
    { _RX, _RX, _RX },
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
static void appl_event(struct mrp_attr_inst *ai, enum mrp_event ev, bool p2p)
{
    if ((p2p && ev == MRP_EVENT_RJOININ &&
         (ai->appl == MRP_APPL_STATE_VO || ai->appl == MRP_APPL_STATE_VP)) ||
        (!p2p && ev == MRP_EVENT_RIN)) {
        return;
    }
    const struct appl_entry *e = &appl_table[ev][ai->appl];
    if (ev == MRP_EVENT_TX && ai->appl == MRP_APPL_STATE_AN &&
        ai->reg != MRP_REG_STATE_IN) {
        ai->appl = MRP_APPL_STATE_AA;
    } else if (e->ns != MRP_APPL_STATE_COUNT) {
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
    case REG_TIMER_START: shlan_timer_arm(&ai->leave_timer, priv_of(app)->ports[port_id].leave_cs); break;
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

    appl_event(ai, ev, ps->point_to_point);
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

static uint32_t leaveall_draw(struct mrp_port_state *ps)
{
    ps->random = ps->random * 1664525u + 1013904223u;
    return ps->leaveall_cs + 1u + ps->random % (ps->leaveall_cs / 2u - 1u);
}

static void la_event(struct mrp_app *app, struct mrp_port_state *ps,
                     enum mrp_event ev, uint8_t port_id)
{
    switch (ev) {
    case MRP_EVENT_BEGIN:
        ps->la = MRP_LA_STATE_PASSIVE;
        shlan_timer_arm(&ps->la_timer, leaveall_draw(ps));
        break;

    case MRP_EVENT_TX:
        if (ps->la == MRP_LA_STATE_ACTIVE) {
            /* sLA: send LeaveAll, reset timer, go Passive */
            ps->la = MRP_LA_STATE_PASSIVE;
            shlan_timer_arm(&ps->la_timer, leaveall_draw(ps));
            /* Also generate rLA! for all local Applicant/Registrar SMs */
            broadcast_event(app, ps, MRP_EVENT_RLA, port_id);
        }
        break;

    case MRP_EVENT_RLA:
        ps->la = MRP_LA_STATE_PASSIVE;
        shlan_timer_arm(&ps->la_timer, leaveall_draw(ps));
        break;

    case MRP_EVENT_LEAVEALLTIMER:
        /* Timer expired → Active, request tx so sLA can fire */
        ps->la = MRP_LA_STATE_ACTIVE;
        shlan_timer_arm(&ps->la_timer, leaveall_draw(ps)); /* restart for next cycle */
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
        shlan_timer_arm(&ps->pt_timer, 100u);
        break;

    case MRP_EVENT_PERIODICTIMER:
        if (ps->pt == MRP_PT_STATE_ACTIVE) {
            shlan_timer_arm(&ps->pt_timer, 100u); /* restart */
            /* Generate periodic! for all Applicant SMs */
            if (ps->prepared_pdu) {
                ps->periodic_owed = true;
            } else {
                broadcast_event(app, ps, MRP_EVENT_PERIODIC, port_id);
            }
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

static void on_join_timer(void *arg)
{
    struct mrp_port_timer_arg *a = arg;
    struct mrp_port_state *ps = &priv_of(a->app)->ports[a->port_id];
    ps->join_wait = 0;
}

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
        ps->join_cs = MRP_JOIN_TIME_CS;
        ps->leave_cs = MRP_LEAVE_TIME_CS;
        ps->leaveall_cs = MRP_LEAVEALL_TIME_CS;
        ps->random = 1u + p;
        ps->timer_arg.app     = app;
        ps->timer_arg.port_id = p;
        shlan_timer_init(&ps->la_timer, on_la_timer, &ps->timer_arg);
        shlan_timer_init(&ps->pt_timer, on_pt_timer, &ps->timer_arg);
        shlan_timer_init(&ps->join_timer, on_join_timer, &ps->timer_arg);
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
        shlan_timer_remove(&priv->ports[p].la_timer);
        shlan_timer_remove(&priv->ports[p].pt_timer);
        shlan_timer_remove(&priv->ports[p].join_timer);
        struct mrp_attr_inst *a = priv->ports[p].attrs;
        while (a) {
            struct mrp_attr_inst *next = a->next;
            shlan_timer_remove(&a->leave_timer);
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
    if (!app || port_id >= priv_of(app)->n_ports || (priv_of(app)->ports[port_id].in_send || priv_of(app)->ports[port_id].prepared_pdu)) {
        return -SHLAN_ERROR_INVALID;
    }

    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];
    struct mrp_attr_inst  *ai   = get_or_create_attr(app, ps, port_id, attr_type, attr_val);
    if (!ai) return -SHLAN_ERROR_NO_MEMORY;

    deliver_event(app, ps, ai, is_new ? MRP_EVENT_NEW : MRP_EVENT_JOIN, port_id);
    ps->tx_pending = true;
    return 0;
}

int mrp_mad_leave(struct mrp_app *app, uint8_t port_id,
                  uint8_t attr_type, const void *attr_val)
{
    if (!app || port_id >= priv_of(app)->n_ports || (priv_of(app)->ports[port_id].in_send || priv_of(app)->ports[port_id].prepared_pdu)) {
        return -SHLAN_ERROR_INVALID;
    }

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
    int                    error;
};

static void rx_on_attr(void *raw_ctx, uint8_t attr_type,
                       enum mrp_attr_event attr_event, const void *attr_val)
{
    struct rx_ctx        *rc = (struct rx_ctx *)raw_ctx;
    struct mrp_attr_inst *ai = get_or_create_attr(rc->app, rc->ps,
                                              rc->port_id, attr_type, attr_val);
    if (!ai) {
        rc->error = -SHLAN_ERROR_NO_MEMORY;
        return;
    }

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
    la_event(rc->app, rc->ps, MRP_EVENT_RLA, rc->port_id);
    for (struct mrp_attr_inst *a = rc->ps->attrs; a; a = a->next) {
        if (a->attr_type == attr_type) {
            deliver_event(rc->app, rc->ps, a, MRP_EVENT_RLA, rc->port_id);
        }
    }
}

int mrp_rx(struct mrp_app *app, uint8_t port_id,
           const uint8_t *pdu, size_t pdu_len)
{
    if (!app || port_id >= priv_of(app)->n_ports || (priv_of(app)->ports[port_id].in_send || priv_of(app)->ports[port_id].prepared_pdu)) {
        return -SHLAN_ERROR_INVALID;
    }

    struct mrp_priv       *priv = priv_of(app);
    struct mrp_port_state *ps   = &priv->ports[port_id];

    struct rx_ctx ctx = { .app = app, .ps = ps, .port_id = port_id };
    int r = mrpdu_parse(pdu, pdu_len, app->ops,
                        rx_on_attr, rx_on_leaveall, &ctx);
    return r < 0 ? r : ctx.error;
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
        shlan_timer_arm(&ps->pt_timer, 100u);
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
        return -SHLAN_ERROR_INVALID;
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
        return -SHLAN_ERROR_INVALID;
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


int mrp_port_configure(struct mrp_app *app, uint8_t port_id,
                        uint32_t join_cs, uint32_t leave_cs,
                        uint32_t leaveall_cs, uint32_t seed, bool point_to_point)
{
    if (!app || port_id >= priv_of(app)->n_ports || join_cs == 0 ||
        leave_cs < join_cs * 2u + 6u || leaveall_cs < 4u ||
        leaveall_cs > 0x7fffffffu || join_cs > 100000u) {
        return -SHLAN_ERROR_INVALID;
    }
    struct mrp_port_state *ps = &priv_of(app)->ports[port_id];
    if (ps->attrs || ps->in_send) {
        return -SHLAN_ERROR_INVALID;
    }
    ps->join_cs = join_cs;
    ps->leave_cs = leave_cs;
    ps->leaveall_cs = leaveall_cs;
    ps->random = seed;
    ps->point_to_point = point_to_point;
    shlan_timer_arm(&ps->la_timer, leaveall_draw(ps));
    return 0;
}

static enum mrp_attr_event wire_event(enum tx_msg msg, enum mrp_reg_state reg)
{
    switch (msg) {
    case TX_MSG_NEW: return MRP_ATTR_EVENT_NEW;
    case TX_MSG_LEAVE: return MRP_ATTR_EVENT_LV;
    case TX_MSG_JOIN: return reg == MRP_REG_STATE_IN ? MRP_ATTR_EVENT_JOININ : MRP_ATTR_EVENT_JOINMT;
    default: return reg == MRP_REG_STATE_IN ? MRP_ATTR_EVENT_IN : MRP_ATTR_EVENT_MT;
    }
}

static int tx_vector(const struct mrp_app_ops *ops, uint8_t type,
                      const void *value, enum mrp_attr_event event, bool la,
                      bool empty, uint8_t *buf, size_t cap)
{
    uint8_t len = ops->attr_len(type);
    bool msrp = ops->ethertype == MRP_ETHERTYPE_MSRP;
    bool subtype = ops->attr_has_subtype && ops->attr_has_subtype(type);
    size_t hdr = msrp ? 4u : 2u;
    size_t list = 2u + len + (empty ? 0u : 1u + subtype) + 2u;
    if (cap < hdr + list || len == 0) {
        return -SHLAN_ERROR_NO_BUFFER;
    }
    buf[0] = type; buf[1] = len;
    if (msrp) {
        buf[2] = (uint8_t)(list >> 8); buf[3] = (uint8_t)list;
    }
    uint8_t *v = buf + hdr;
    v[0] = la ? 0x20 : 0; v[1] = empty ? 0 : 1;
    if (empty) {
        memset(v + 2, 0, len);
    } else {
        int r = ops->encode_attr(type, value, v + 2, len);
        if (r != len) {
            return -SHLAN_ERROR_INVALID;
        }
        v[2u + len] = mrp_three_pack((uint8_t)event, 0, 0);
        if (subtype) {
            const uint8_t *bytes = value;
            v[3u + len] = mrp_four_pack(bytes[len], 0, 0, 0);
        }
    }
    buf[hdr + list - 2] = 0; buf[hdr + list - 1] = 0;
    return (int)(hdr + list);
}

int mrp_transmit(struct mrp_app *app, uint8_t port_id,
                 uint8_t *pdu, size_t capacity, mrp_send_fn send, void *ctx)
{
    if (!app || port_id >= priv_of(app)->n_ports || !pdu || !send || capacity < 3) {
        return -SHLAN_ERROR_INVALID;
    }
    struct mrp_port_state *ps = &priv_of(app)->ports[port_id];
    if (ps->in_send) {
        return -SHLAN_ERROR_INVALID;
    }
    if (!ps->prepared_pdu && (!ps->tx_pending || ps->join_wait)) {
        return 0;
    }
    bool la = ps->prepared_pdu ? ps->prepared_la : ps->la == MRP_LA_STATE_ACTIVE;
    enum mrp_event event = la ? MRP_EVENT_TXLA : MRP_EVENT_TX;
    size_t off = ps->prepared_len;
    if (!ps->prepared_pdu) {
        off = 1;
        unsigned flagged = 0;
        pdu[0] = app->ops->proto_version;
        for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next) {
            const struct appl_entry *e = &appl_table[event][a->appl];
            if (e->tx == TX_MSG_NONE) {
                continue;
            }
            bool flag = la && !(flagged & (1u << a->attr_type));
            int n = tx_vector(app->ops, a->attr_type, a->attr_val,
                              wire_event(e->tx, a->reg), flag, false,
                              pdu + off, capacity - off - 2u);
            if (n < 0) {
                return n;
            }
            off += (size_t)n;
            flagged |= 1u << a->attr_type;
        }
        if (la) {
            unsigned last = app->ops->ethertype == MRP_ETHERTYPE_MSRP ? 4u : 1u;
            for (unsigned type = 1; type <= last; ++type) {
                if (!(flagged & (1u << type))) {
                    int n = tx_vector(app->ops, (uint8_t)type, NULL, MRP_ATTR_EVENT_MT,
                                      true, true, pdu + off, capacity - off - 2u);
                    if (n < 0) {
                        return n;
                    }
                    off += (size_t)n;
                }
            }
        }
        if (off == 1) {
            ps->tx_pending = false;
            return 0;
        }
        pdu[off++] = 0; pdu[off++] = 0;
        ps->prepared_pdu = pdu;
        ps->prepared_len = off;
        ps->prepared_la = la;
    }
    ps->in_send = true;
    int r = send(ctx, port_id, ps->prepared_pdu, ps->prepared_len);
    ps->in_send = false;
    if (r != 0) {
        return r;
    }
    ps->prepared_pdu = NULL;
    ps->prepared_len = 0;
    ps->tx_pending = false;
    for (struct mrp_attr_inst *a = ps->attrs; a; a = a->next) {
        deliver_event(app, ps, a, event, port_id);
        switch (a->appl) {
        case MRP_APPL_STATE_VN: case MRP_APPL_STATE_AN:
        case MRP_APPL_STATE_AA: case MRP_APPL_STATE_LA:
        case MRP_APPL_STATE_VP: case MRP_APPL_STATE_AP:
        case MRP_APPL_STATE_LO:
            ps->tx_pending = true;
            break;
        default:
            break;
        }
    }
    if (la) {
        ps->la = MRP_LA_STATE_PASSIVE;
    }
    if (ps->periodic_owed) {
        ps->periodic_owed = false;
        broadcast_event(app, ps, MRP_EVENT_PERIODIC, port_id);
        ps->tx_pending = true;
    }
    if (ps->la == MRP_LA_STATE_ACTIVE) {
        ps->tx_pending = true;
    }
    ps->join_wait = ps->join_cs;
    shlan_timer_arm(&ps->join_timer, ps->join_cs);
    return 1;
}
