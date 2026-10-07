/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHISH_LAN_MRP_H
#define SHISH_LAN_MRP_H

/*
 * Multiple Registration Protocol (MRP) — IEEE 802.1Q-2018, Clause 10
 *
 * MRP is a generic, many-to-many attribute registration protocol.
 * Each MRP application (MMRP §10.9, MVRP §11.2, MSRP §35) plugs in by
 * providing an struct mrp_app_ops vtable.  The MRP base supplies the four state
 * machines (§10.7): Applicant, Registrar, LeaveAll, PeriodicTransmission.
 *
 * Layering:
 *   MRP application (MVRP / MMRP / MSRP)
 *        |  MAD_Join/Leave.request  ↑  MAD_Join/Leave.indication
 *        v                          |
 *   MAD (MRP Attribute Declaration) — §10.2, §10.7
 *        |  MAP  (between bridge ports)
 *        v
 *   LLC / port TX/RX
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ------------------------------------------------------------------ */
/* §10.7.7 Applicant state machine states — Table 10-3                 */
/* ------------------------------------------------------------------ */
enum mrp_appl_state {
    MRP_APPL_STATE_VO = 0, /* Very anxious Observer: not declaring, no JoinIn seen  */
    MRP_APPL_STATE_VP,     /* Very anxious Passive: declaring, not yet sent Join     */
    MRP_APPL_STATE_VN,     /* Very anxious New: new decl pending, not yet sent       */
    MRP_APPL_STATE_AN,     /* Anxious New: sent one New                              */
    MRP_APPL_STATE_AA,     /* Anxious Active: sent Join, not quietened               */
    MRP_APPL_STATE_QA,     /* Quiet Active: sent Join, have JoinIn confirmation      */
    MRP_APPL_STATE_LA,     /* Leaving Active: Leave pending                          */
    MRP_APPL_STATE_AO,     /* Anxious Observer: not decl, saw one JoinIn             */
    MRP_APPL_STATE_QO,     /* Quiet Observer: not decl, saw two JoinIns              */
    MRP_APPL_STATE_AP,     /* Anxious Passive: declaring, observer-level msgs rcvd   */
    MRP_APPL_STATE_QP,     /* Quiet Passive: declaring, quiet observer msgs rcvd     */
    MRP_APPL_STATE_LO,     /* Leaving Observer: saw Leave / LeaveAll                 */
    MRP_APPL_STATE_COUNT
};

/* ------------------------------------------------------------------ */
/* §10.7.8 Registrar state machine states — Table 10-4                 */
/* ------------------------------------------------------------------ */
enum mrp_reg_state {
    MRP_REG_STATE_IN = 0, /* Registered                                            */
    MRP_REG_STATE_LV,     /* Leaving: leavetimer running, will expire to MT        */
    MRP_REG_STATE_MT,     /* Empty: not registered                                 */
    MRP_REG_STATE_COUNT
};

/* ------------------------------------------------------------------ */
/* §10.7.9 LeaveAll state machine — Table 10-5                         */
/* ------------------------------------------------------------------ */
enum mrp_la_state {
    MRP_LA_STATE_ACTIVE = 0, /* leavealltimer running; requests tx on entry       */
    MRP_LA_STATE_PASSIVE,    /* waiting                                           */
};

/* ------------------------------------------------------------------ */
/* §10.7.10 PeriodicTransmission state machine — Table 10-6            */
/* ------------------------------------------------------------------ */
enum mrp_pt_state {
    MRP_PT_STATE_ACTIVE = 0, /* periodictimer running                             */
    MRP_PT_STATE_PASSIVE,    /* periodic transmission disabled                    */
};

/* ------------------------------------------------------------------ */
/* §10.7.5 Protocol events                                             */
/* ------------------------------------------------------------------ */
enum mrp_event {
    MRP_EVENT_BEGIN        = 0,  /* §10.7.5.1  initialise / reinitialise        */
    MRP_EVENT_NEW,               /* §10.7.5.4  MAD_Join.request (new=TRUE)      */
    MRP_EVENT_JOIN,              /* §10.7.5.5  MAD_Join.request (new=FALSE)     */
    MRP_EVENT_LV,                /* §10.7.5.6  MAD_Leave.request                */
    MRP_EVENT_TX,                /* §10.7.5.7  tx opportunity, no LeaveAll      */
    MRP_EVENT_TXLA,              /* §10.7.5.8  tx opportunity, with LeaveAll    */
    MRP_EVENT_TXLAF,             /* §10.7.5.9  tx opportunity, LA + PDU full    */
    MRP_EVENT_RNEW,              /* §10.7.5.14 received New message             */
    MRP_EVENT_RJOININ,           /* §10.7.5.15 received JoinIn message          */
    MRP_EVENT_RJOINMT,           /* §10.7.5.16 received JoinMt message          */
    MRP_EVENT_RIN,               /* §10.7.5.18 received In message              */
    MRP_EVENT_RMT,               /* §10.7.5.19 received Mt message              */
    MRP_EVENT_RLV,               /* §10.7.5.17 received Lv message              */
    MRP_EVENT_RLA,               /* §10.7.5.20 received LeaveAll message        */
    MRP_EVENT_FLUSH,             /* §10.7.5.2  port role: Root/Alt → Designated */
    MRP_EVENT_REDECLARE,         /* §10.7.5.3  port role: Designated → Root/Alt */
    MRP_EVENT_PERIODIC,          /* §10.7.5.10 periodic event from PT SM        */
    MRP_EVENT_LEAVETIMER,        /* §10.7.5.21 leavetimer expired               */
    MRP_EVENT_LEAVEALLTIMER,     /* §10.7.5.22 leavealltimer expired            */
    MRP_EVENT_PERIODICTIMER,     /* §10.7.5.23 periodictimer expired            */
    MRP_EVENT_COUNT
};

/* ------------------------------------------------------------------ */
/* §10.8.2.5 AttributeEvent values encoded in MRPDUs                  */
/* ------------------------------------------------------------------ */
enum mrp_attr_event {
    MRP_ATTR_EVENT_NEW    = 0, /* New (§10.7.6.2 sN)                           */
    MRP_ATTR_EVENT_JOININ = 1, /* JoinIn (§10.7.6.3 sJ, Registrar=IN)         */
    MRP_ATTR_EVENT_IN     = 2, /* In (§10.7.6.5 s, Registrar=IN)              */
    MRP_ATTR_EVENT_JOINMT = 3, /* JoinMt (§10.7.6.3 sJ, Registrar=MT/LV)      */
    MRP_ATTR_EVENT_MT     = 4, /* Mt (§10.7.6.5 s, Registrar=MT/LV)           */
    MRP_ATTR_EVENT_LV     = 5, /* Lv (§10.7.6.4 sL)                           */
};

/* §10.8.2.6 LeaveAllEvent field in VectorHeader */
#define MRP_LA_NULL  0u /* NullLeaveAllEvent */
#define MRP_LA_ALL   1u /* LeaveAll          */

/* ------------------------------------------------------------------ */
/* §10.7.11 Table 10-7 — default timer values (centiseconds)           */
/* ------------------------------------------------------------------ */
#define MRP_JOIN_TIME_CS      20u    /* JoinTime                            */
#define MRP_LEAVE_TIME_CS     60u    /* LeaveTime (60–100)                  */
#define MRP_LEAVEALL_TIME_CS  1000u  /* LeaveAllTime                        */

/* ------------------------------------------------------------------ */
/* §10.5 Table 10-2 — EtherType values                                 */
/* ------------------------------------------------------------------ */
#define MRP_ETHERTYPE_MMRP  0x88F6u
#define MRP_ETHERTYPE_MVRP  0x88F5u
#define MRP_ETHERTYPE_MSRP  0x22EAu

/* §10.5 Table 10-1 — group MAC addresses */
#define MRP_ADDR_MMRP { 0x01u, 0x80u, 0xC2u, 0x00u, 0x00u, 0x20u }
#define MRP_ADDR_MVRP { 0x01u, 0x80u, 0xC2u, 0x00u, 0x00u, 0x21u }

/* §10.8.2.1 — protocol version encoded in MRPDU octet 1 */
#define MRP_PROTOCOL_VERSION 0u

/* ------------------------------------------------------------------ */
/* MRP application vtable (Ports & Adapters boundary)                  */
/* ------------------------------------------------------------------ */
struct mrp_app;

struct mrp_app_ops {
    /*
     * MAD_Join.indication — §10.7.6.12 (is_new=true) / §10.7.6.13 (false).
     * Called when attr_type/attr_val becomes registered on port_id.
     */
    void    (*join_ind)(struct mrp_app *app, uint8_t port_id,
                        uint8_t attr_type, const void *attr_val, bool is_new);

    /*
     * MAD_Leave.indication — §10.7.6.14.
     * Called when attr_type/attr_val is deregistered from port_id.
     */
    void    (*leave_ind)(struct mrp_app *app, uint8_t port_id,
                         uint8_t attr_type, const void *attr_val);

    /*
     * MAP policy — §10.3.  Optional; set to NULL for end-station behaviour.
     *
     * map_join:  called after join_ind fires on src_port.  Return a bitmask
     *            of ports to re-declare the attribute on (bit N = port N).
     *            Return 0 to suppress all propagation.
     *
     * map_leave: called after leave_ind fires on src_port.  Return a bitmask
     *            of ports to withdraw the attribute from.
     *
     * The MRP base applies the bitmask by calling mrp_mad_join / mrp_mad_leave
     * with is_new=false so the Registrar SM on target ports is not disturbed
     * and there is no indication loop.
     *
     * Note: bitmask limits MAP to ≤ 32 ports.
     *
     * TODO: once RSTP is integrated, implementations must gate propagation on
     * port role — only Designated ports should be included in the returned
     * bitmask (§10.3, MAP domain membership).
     */
    uint32_t (*map_join)(const struct mrp_app *app, uint8_t src_port,
                         uint8_t attr_type, const void *attr_val);
    uint32_t (*map_leave)(const struct mrp_app *app, uint8_t src_port,
                          uint8_t attr_type, const void *attr_val);

    /*
     * Encode FirstValue into buf — §10.8.2.7.
     * Returns bytes written, or negative errno.
     */
    int     (*encode_attr)(uint8_t attr_type, const void *attr_val,
                           uint8_t *buf, size_t buf_len);

    /*
     * Decode attribute value from buf given FirstValue + vector offset — §10.8.2.7.
     * Returns bytes consumed, or negative errno.
     */
    int     (*decode_attr)(uint8_t attr_type, uint32_t offset,
                           const uint8_t *buf, size_t buf_len,
                           void *attr_val_out);

    /*
     * Return FirstValue field length in octets for attr_type — §10.8.2.3.
     */
    uint8_t (*attr_len)(uint8_t attr_type);

    /*
     * Compare two attribute values; return 0 if equal.
     * Used for state machine instance lookup.
     */
    int     (*attr_cmp)(uint8_t attr_type, const void *a, const void *b);

    /*
     * Optional (may be NULL): return true for attribute types whose
     * VectorAttribute carries a FourPackedEvents subtype vector after
     * the ThreePackedEvents — the MSRP Listener declaration type
     * (§35.2.2.7.2). When true, mrpdu_parse decodes both vectors and
     * appends the subtype value as one extra octet after the
     * attr_len(attr_type) FirstValue octets in attr_val, and the MAD
     * stores that octet with the attribute instance.
     */
    bool    (*attr_has_subtype)(uint8_t attr_type);

    /*
     * Optional (may be NULL): in-memory size of a decoded attribute
     * value — what decode_attr writes and the indication callbacks
     * receive — when it differs from the wire FirstValue length
     * attr_len(attr_type): a host-endian struct, an appended subtype
     * octet. NULL means the two are identical.
     */
    uint8_t (*attr_mem_len)(uint8_t attr_type);

    uint16_t ethertype;      /* §10.5 Table 10-2 */
    uint8_t  proto_version;  /* §10.8.2.1        */
    uint8_t  group_addr[6];  /* §10.5 Table 10-1 */
    void    *ctx;            /* opaque application context passed back in callbacks */
    /* Optional application encoding rule for a received JoinIn/JoinMt:
     * true withdraws a different registered attribute before registering this
     * one (MSRP 35.2.6). Values use the application's in-memory representation.
     */
    bool (*attr_replaces)(uint8_t old_type, const void *old_value,
                          uint8_t new_type, const void *new_value);
    /* Opt in at creation: received Leave in IN issues Leave and enters MT.
     * Milan v1.2 4.2.7.2.2; false preserves IEEE 802.1Q Table 10-4.
     * Other events and the existing LV deadline are unchanged.
     */
    bool milan_rapid_leave;
};

/* Opaque MRP application handle */
struct mrp_app {
    const struct mrp_app_ops *ops;
    void                *priv; /* internal per-port participant state */
};

/* ------------------------------------------------------------------ */
/* MRP base API                                                         */
/* ------------------------------------------------------------------ */

/* Create/destroy an MRP application instance (all ports share one). */
struct mrp_app *mrp_app_create(const struct mrp_app_ops *ops, uint8_t n_ports);
void            mrp_app_destroy(struct mrp_app *app);

/* Poll one transmit opportunity. The send port returns zero only after it
 * accepts all bytes; a refusal leaves every applicant and registrar unchanged.
 * Ports never call back into this application synchronously. Caller storage
 * must fit one message and any LeaveAll preamble; larger populations split
 * across opportunities. A no-buffer result commits no state. Returns 1 for
 * a committed PDU, zero when no opportunity is due, or negative errno. */
/* A refused send retains the exact PDU in the caller's buffer until accepted.
 * Keep that buffer alive and unchanged between retries. While retained, RX and
 * local declarations on this port are refused without side effects: queue and
 * retry them after the transmit. Timers still expire, including registrar Leave.
 * The send function must never call back into MRP synchronously.
 */
/* 10.7 permits limiting state to attributes of immediate interest. A filter
 * runs after complete wire validation, before any allocation. LeaveAll remains
 * applicable to retained attributes. It must not re-enter MRP.
 */
typedef bool (*mrp_rx_filter_fn)(void *ctx, uint8_t port, uint8_t type, const void *value);
void mrp_set_rx_filter(struct mrp_app *app, mrp_rx_filter_fn filter, void *ctx);
/* Reclaim only unregistered, undeclared attributes (Table 10-3 note 11).
 * Call outside callbacks; a prepared transmission prevents reclamation.
 */
unsigned mrp_reclaim(struct mrp_app *app, uint8_t port_id);
typedef int (*mrp_send_fn)(void *ctx, uint8_t port_id,
                           const uint8_t *pdu, size_t len);
int mrp_transmit(struct mrp_app *app, uint8_t port_id,
                 uint8_t *pdu, size_t capacity, mrp_send_fn send, void *ctx);

/* Set protocol timers before declaring attributes. Units are centiseconds.
 * A caller supplies a random seed; LeaveAll draws are strictly inside the
 * IEEE 802.1Q 10.7.4.3 interval. A one-second periodic timer is independent
 * of JoinTime. No port call can synchronously deliver a tick or RX event. */
int mrp_port_configure(struct mrp_app *app, uint8_t port_id,
                        uint32_t join_cs, uint32_t leave_cs,
                        uint32_t leaveall_cs, uint32_t seed, bool point_to_point);

/* Return the number of ports the application was created with. */
uint8_t mrp_app_n_ports(const struct mrp_app *app);

/*
 * Return a bitmask of ports on which attr_type/attr_val is currently
 * registered (Registrar state == IN).  Bit N set means port N has it.
 * Intended for use inside map_join / map_leave callbacks.
 */
uint32_t mrp_attr_registered_ports(const struct mrp_app *app,
                                   uint8_t attr_type, const void *attr_val);

/*
 * MAD_Join.request — §10.2.
 * Declare attr_type/attr_val on port_id.  is_new=true for new declarations
 * (drives the New state machine paths in Table 10-3).
 */
int mrp_mad_join(struct mrp_app *app, uint8_t port_id,
                 uint8_t attr_type, const void *attr_val, bool is_new);

/*
 * MAD_Leave.request — §10.2.
 * Withdraw attr_type/attr_val on port_id.
 */
int mrp_mad_leave(struct mrp_app *app, uint8_t port_id,
                  uint8_t attr_type, const void *attr_val);

/*
 * Feed a received MRPDU into the state machines.
 * Parses §10.8 structure and dispatches per-attribute events.
 */
int mrp_rx(struct mrp_app *app, uint8_t port_id,
           const uint8_t *pdu, size_t pdu_len);

/*
 * Centisecond tick — drive leavetimer, leavealltimer, periodictimer.
 * Call at ≤1 cs resolution (§10.7.11).
 */
void mrp_tick(struct mrp_app *app, uint8_t port_id);

/*
 * Port topology event — drive Flush!/Re-declare! into state machines.
 * flush=true  → §10.7.5.2 Flush! (Root/Alt → Designated).
 * flush=false → §10.7.5.3 Re-declare! (Designated → Root/Alt).
 */
void mrp_port_role_change(struct mrp_app *app, uint8_t port_id, bool flush);

/*
 * Periodic transmission enable/disable — drives periodicEnabled!/periodicDisabled!
 * events into the PeriodicTransmission state machine (§10.7.10, Table 10-6).
 */
void mrp_set_periodic(struct mrp_app *app, uint8_t port_id, bool enable);

/* ------------------------------------------------------------------ */
/* Introspection and observability (debug consoles)                    */
/* ------------------------------------------------------------------ */

/* Snapshot of one attribute instance's per-attribute state machines. */
struct mrp_attr_status {
    uint8_t             port_id;
    uint8_t             attr_type;
    const void         *attr_val;   /* attr_len(attr_type) octets */
    enum mrp_appl_state appl;
    enum mrp_reg_state  reg;
};

/*
 * One Applicant and/or Registrar state change, reported after the event
 * was applied and after any MAD indications fired.
 */
struct mrp_transition {
    uint8_t             port_id;
    uint8_t             attr_type;
    const void         *attr_val;   /* attr_len(attr_type) octets */
    enum mrp_event      event;      /* the event that caused the change */
    enum mrp_appl_state appl_from;
    enum mrp_appl_state appl_to;
    enum mrp_reg_state  reg_from;
    enum mrp_reg_state  reg_to;
};

/*
 * Observe every Applicant/Registrar state change on any port of the app.
 * The callback runs synchronously in state machine context; keep it
 * short and do not call back into the same app from it. One observer
 * per app; fn=NULL clears it.
 *
 * LeaveAll and PeriodicTransmission flip by design on their timers and
 * are not reported here; read their current state with mrp_port_status.
 */
void mrp_set_observer(struct mrp_app *app,
                      void (*fn)(void *ctx, const struct mrp_transition *t),
                      void *ctx);

/*
 * Visit every attribute instance on port_id (newest first). visit=NULL
 * only counts. Returns the number of instances, or negative errno.
 */
int mrp_attr_visit(const struct mrp_app *app, uint8_t port_id,
                   void (*visit)(void *ctx, const struct mrp_attr_status *st),
                   void *ctx);

/* Current LeaveAll / PeriodicTransmission state of a port participant. */
int mrp_port_status(const struct mrp_app *app, uint8_t port_id,
                    enum mrp_la_state *la, enum mrp_pt_state *pt);

/* Short 802.1Q names ("QA", "IN", "rJoinIn!") for console output. */
const char *mrp_appl_state_name(enum mrp_appl_state s);
const char *mrp_reg_state_name(enum mrp_reg_state s);
const char *mrp_event_name(enum mrp_event ev);

#endif /* SHISH_LAN_MRP_H */
