# lwSRP Architecture

lwSRP (lightweight Shish-Lan Soft MRP) is a C implementation of the IEEE 802.1Q-2018
Multiple Registration Protocol (MRP) base and its three standard application adapters:
MVRP, MMRP, and MSRP. The library targets embedded bridge and switch firmware but is
also fully exercisable in simulation on a standard workstation.

See `doc/architecture.drawio` for visual diagrams (Layer Architecture, Rx Data Flow,
MSRP MAP Propagation, and Data Structures).

---

## Table of Contents

1. [Directory Layout](#1-directory-layout)
2. [Layered Architecture](#2-layered-architecture)
3. [MRP Base — State Machines](#3-mrp-base--state-machines)
4. [MRPDU Codec](#4-mrpdu-codec)
5. [The `mrp_app_ops` Vtable](#5-the-mrp_app_ops-vtable)
6. [MAP Propagation Design](#6-map-propagation-design)
7. [MRP Applications](#7-mrp-applications)
8. [Switch Abstraction](#8-switch-abstraction)
9. [Allocation Port](#9-allocation-port)
10. [Testing](#10-testing)
11. [Known TODOs and Future Work](#11-known-todos-and-future-work)

---

## 1. Directory Layout

```
lwSRP/
├── CMakeLists.txt                 Build definition (shared lib + tests)
├── build.sh                       Convenience build wrapper
├── behave.ini                     BDD test runner configuration
│
├── doc/
│   ├── architecture.drawio        Visual architecture diagrams (4 pages)
│   └── architecture.md            This document
│
├── src/
│   ├── core/
│   │   ├── mrp_mad.c              MRP state machines and public base API
│   │   ├── mrp_pdu.c              MRPDU encode/decode
│   │   └── switch_ctrl.c         Lock-free MPSC register queue
│   │
│   ├── include/shish_lan/
│   │   ├── mrp.h                  MRP base public API + mrp_app_ops vtable
│   │   ├── mrp_pdu.h              PDU utilities (pack/unpack helpers, encode/parse)
│   │   ├── mvrp.h                 MVRP application public API
│   │   ├── mmrp.h                 MMRP application public API
│   │   ├── msrp.h                 MSRP application public API
│   │   ├── switch.h               Abstract switch operations vtable
│   │   └── switch_ctrl.h          Register queue interface
│   │
│   ├── modules/
│   │   ├── mvrp.c                 MVRP adapter implementation
│   │   ├── mmrp.c                 MMRP adapter implementation
│   │   ├── msrp.c                 MSRP adapter + §35.2.3 MAP rules
│   │   ├── sim_adapter.c          In-memory simulation adapter
│   │   └── sim_adapter.h          Simulation adapter header
│   │
│   └── ports/
│       ├── alloc.h                Allocator / printf abstraction declarations
│       └── alloc.c                Default implementation (stdlib malloc/printf)
│
└── tests/
    ├── unit/
    │   ├── mrp_pdu_test.c         cgreen unit tests for PDU pack/unpack
    │   └── placeholder.c
    └── features/
        ├── switch.feature          BDD scenarios (Gherkin)
        ├── environment.py          behave environment hooks
        └── steps/
            └── switch_steps.py    Python/ctypes step definitions
```

---

## 2. Layered Architecture

The library is organized in strict layers following a Ports and Adapters pattern.
Each boundary is an abstract interface (vtable); concrete implementations plug in
from below without touching the layer above.

```
┌──────────────────────────────────────────────────────────────┐
│                   Application Layer                          │
│          MVRP            MMRP            MSRP                │
│   (mvrp.c / mvrp.h) (mmrp.c / mmrp.h) (msrp.c / msrp.h)   │
└────────────────────────┬─────────────────────────────────────┘
                         │  struct mrp_app_ops  (mrp.h)
┌────────────────────────┴─────────────────────────────────────┐
│                     MRP Base                                 │
│     MAD state machines (mrp_mad.c)  PDU codec (mrp_pdu.c)   │
└────────────────────────┬─────────────────────────────────────┘
                         │
┌────────────────────────┴─────────────────────────────────────┐
│               Switch Abstraction                             │
│   struct shlan_switch_ops (switch.h)                         │
│   struct shlan_ctrl_queue (switch_ctrl.h)                    │
└────────────────────────┬─────────────────────────────────────┘
                         │
┌────────────────────────┴─────────────────────────────────────┐
│                Concrete Adapters                             │
│   sim_adapter.c (simulation)   hw_adapter.c (hardware, TBD) │
└──────────────────────────────────────────────────────────────┘
```

Allocation and I/O are similarly abstracted via `ports/alloc.h` so embedded targets
can substitute their own heap and logging without modifying any library source file.

---

## 3. MRP Base — State Machines

All state machine logic lives in `src/core/mrp_mad.c`. This is the largest and most
complex file in the library.

### 3.1 Public Handle

```c
/* mrp.h */
struct mrp_app {
    const struct mrp_app_ops *ops;  /* application vtable */
    void                     *priv; /* internal state (struct mrp_priv *) */
};
```

`struct mrp_app` is an opaque handle. Callers receive it from `mrp_app_create()` and
pass it to every MRP base API function.

### 3.2 Internal Data Structures

These types are private to `mrp_mad.c`.

#### Per-attribute instance

```c
struct mrp_attr_inst {
    uint8_t              attr_type;
    uint8_t              attr_val[32]; /* max attribute value storage */
    enum mrp_appl_state  appl;         /* Applicant state machine state */
    enum mrp_reg_state   reg;          /* Registrar state machine state */
    uint32_t             leave_cs;     /* leavetimer countdown (centiseconds) */
    enum tx_msg          pending_tx;   /* message scheduled for next PDU */
    struct mrp_attr_inst *next;        /* singly-linked list per port */
};
```

One instance exists for every unique `(attr_type, attr_val)` pair that has been
declared or received on a port. Instances are heap-allocated and chained on
`mrp_port_state.attrs`.

#### Per-port participant state

```c
struct mrp_port_state {
    enum mrp_la_state    la;          /* LeaveAll SM state */
    enum mrp_pt_state    pt;          /* PeriodicTransmission SM state */
    uint32_t             la_cs;       /* leavealltimer countdown */
    uint32_t             pt_cs;       /* periodictimer countdown */
    bool                 tx_pending;  /* transmission opportunity needed */
    struct mrp_attr_inst *attrs;      /* head of attribute instance list */
};
```

#### Private application state

```c
struct mrp_priv {
    uint8_t              n_ports;
    struct mrp_port_state ports[]; /* flexible array, one entry per port */
};
```

`struct mrp_priv` is allocated by `mrp_app_create()` as a single block
(`sizeof(struct mrp_priv) + n_ports * sizeof(struct mrp_port_state)`).

#### Pending transmit message type (internal)

```c
enum tx_msg {
    TX_MSG_NONE  = 0,
    TX_MSG_NEW,    /* §10.7.6.2 sN  */
    TX_MSG_JOIN,   /* §10.7.6.3 sJ  (JoinIn or JoinMt depending on Registrar) */
    TX_MSG_LEAVE,  /* §10.7.6.4 sL  */
    TX_MSG_IN,     /* §10.7.6.5 s   (In or Mt depending on Registrar) */
};
```

### 3.3 The Four State Machines

Each MRP Participant manages four state machines. Three are per-port (LeaveAll,
PeriodicTransmission) or per-attribute (Applicant, Registrar). All transitions are
encoded as static lookup tables.

#### a) Applicant State Machine — §10.7.7 Table 10-3

Tracks the local declaration state for one attribute on one port.

```
States (enum mrp_appl_state):
  MRP_APPL_STATE_VO   Very anxious Observer: not declaring, no JoinIn seen
  MRP_APPL_STATE_VP   Very anxious Passive:  declaring, not yet sent Join
  MRP_APPL_STATE_VN   Very anxious New:      new decl pending
  MRP_APPL_STATE_AN   Anxious New:           sent one New
  MRP_APPL_STATE_AA   Anxious Active:        sent Join, not quietened
  MRP_APPL_STATE_QA   Quiet Active:          sent Join, confirmed
  MRP_APPL_STATE_LA   Leaving Active:        Leave pending
  MRP_APPL_STATE_AO   Anxious Observer:      not decl, saw one JoinIn
  MRP_APPL_STATE_QO   Quiet Observer:        not decl, saw two JoinIns
  MRP_APPL_STATE_AP   Anxious Passive:       declaring, observer-level msgs
  MRP_APPL_STATE_QP   Quiet Passive:         declaring, quiet observer msgs
  MRP_APPL_STATE_LO   Leaving Observer:      saw Leave / LeaveAll
```

The table is:

```c
static const struct appl_entry appl_table[MRP_EVENT_COUNT][MRP_APPL_STATE_COUNT];
```

Each entry `{tx_msg, next_state}` carries the message to schedule and the state to
transition to. A sentinel value `MRP_APPL_STATE_COUNT` in `next_state` means "no
transition" (stay in current state). The `TX_MSG_NONE` value means "no transmission
action".

#### b) Registrar State Machine — §10.7.8 Table 10-4

Tracks whether remote participants have registered the attribute.

```
States (enum mrp_reg_state):
  MRP_REG_STATE_IN   Registered (at least one peer declares it)
  MRP_REG_STATE_LV   Leaving (leavetimer running)
  MRP_REG_STATE_MT   Empty (no peer declaration)
```

```c
static const struct reg_entry reg_table[MRP_EVENT_COUNT][MRP_REG_STATE_COUNT];
```

Each entry carries `{next_reg_state, reg_ind}` where `reg_ind` is one of:

```
REG_IND_NONE  — no indication
REG_IND_NEW   — fire join_ind(is_new=true)
REG_IND_JOIN  — fire join_ind(is_new=false)
REG_IND_LV    — fire leave_ind
```

The Registrar is the only machine that drives `join_ind` and `leave_ind` callbacks.
The Applicant is purely local.

#### c) LeaveAll State Machine — §10.7.9 Table 10-5

One per port. Controls mass-deregistration behavior.

```
States (enum mrp_la_state):
  MRP_LA_STATE_ACTIVE   leavealltimer running; sends LeaveAll in PDU
  MRP_LA_STATE_PASSIVE  waiting for leavealltimer
```

Transitions on `MRP_EVENT_LEAVEALLTIMER` and `MRP_EVENT_RLA` (received LeaveAll).

#### d) PeriodicTransmission State Machine — §10.7.10 Table 10-6

One per port. Controls periodic re-announcement.

```
States (enum mrp_pt_state):
  MRP_PT_STATE_ACTIVE   periodictimer running; fires PERIODIC event on expiry
  MRP_PT_STATE_PASSIVE  periodic transmission disabled
```

Controlled via `mrp_set_periodic(app, port_id, bool enable)`.

### 3.4 Events

```c
enum mrp_event {
    MRP_EVENT_BEGIN,          /* initialise / reinitialise            §10.7.5.1 */
    MRP_EVENT_NEW,            /* MAD_Join.request (is_new=true)       §10.7.5.4 */
    MRP_EVENT_JOIN,           /* MAD_Join.request (is_new=false)      §10.7.5.5 */
    MRP_EVENT_LV,             /* MAD_Leave.request                    §10.7.5.6 */
    MRP_EVENT_TX,             /* tx opportunity, no LeaveAll          §10.7.5.7 */
    MRP_EVENT_TXLA,           /* tx opportunity, with LeaveAll        §10.7.5.8 */
    MRP_EVENT_TXLAF,          /* tx opportunity, LA + PDU full        §10.7.5.9 */
    MRP_EVENT_RNEW,           /* received New                         §10.7.5.14 */
    MRP_EVENT_RJOININ,        /* received JoinIn                      §10.7.5.15 */
    MRP_EVENT_RJOINMT,        /* received JoinMt                      §10.7.5.16 */
    MRP_EVENT_RIN,            /* received In                          §10.7.5.18 */
    MRP_EVENT_RMT,            /* received Mt                          §10.7.5.19 */
    MRP_EVENT_RLV,            /* received Lv                          §10.7.5.17 */
    MRP_EVENT_RLA,            /* received LeaveAll                    §10.7.5.20 */
    MRP_EVENT_FLUSH,          /* port: Root/Alt → Designated          §10.7.5.2 */
    MRP_EVENT_REDECLARE,      /* port: Designated → Root/Alt          §10.7.5.3 */
    MRP_EVENT_PERIODIC,       /* periodictimer fired                  §10.7.5.10 */
    MRP_EVENT_LEAVETIMER,     /* leavetimer expired                   §10.7.5.21 */
    MRP_EVENT_LEAVEALLTIMER,  /* leavealltimer expired                §10.7.5.22 */
    MRP_EVENT_PERIODICTIMER,  /* periodictimer expired                §10.7.5.23 */
};
```

### 3.5 Timer Defaults

```c
#define MRP_JOIN_TIME_CS      20u    /* JoinTime     — centiseconds */
#define MRP_LEAVE_TIME_CS     60u    /* LeaveTime    — centiseconds */
#define MRP_LEAVEALL_TIME_CS  1000u  /* LeaveAllTime — centiseconds */
```

`mrp_tick(app, port_id)` must be called at ≤1 cs resolution. It decrements all
countdown counters and fires the corresponding `MRP_EVENT_LEAVETIMER`,
`MRP_EVENT_LEAVEALLTIMER`, or `MRP_EVENT_PERIODICTIMER` events when any counter
reaches zero.

### 3.6 Public MRP Base API

All functions are declared in `src/include/shish_lan/mrp.h`.

```c
/* Lifecycle */
struct mrp_app *mrp_app_create(const struct mrp_app_ops *ops, uint8_t n_ports);
void            mrp_app_destroy(struct mrp_app *app);

/* Query */
uint8_t  mrp_app_n_ports(const struct mrp_app *app);
uint32_t mrp_attr_registered_ports(const struct mrp_app *app,
                                   uint8_t attr_type, const void *attr_val);

/* Local declaration */
int  mrp_mad_join(struct mrp_app *app, uint8_t port_id,
                  uint8_t attr_type, const void *attr_val, bool is_new);
int  mrp_mad_leave(struct mrp_app *app, uint8_t port_id,
                   uint8_t attr_type, const void *attr_val);

/* Receive path */
int  mrp_rx(struct mrp_app *app, uint8_t port_id,
            const uint8_t *pdu, size_t pdu_len);

/* Timer tick */
void mrp_tick(struct mrp_app *app, uint8_t port_id);

/* Topology events */
void mrp_port_role_change(struct mrp_app *app, uint8_t port_id, bool flush);

/* Periodic transmission control */
void mrp_set_periodic(struct mrp_app *app, uint8_t port_id, bool enable);
```

`mrp_attr_registered_ports` returns a `uint32_t` bitmask where bit N is set if port N
has `Registrar == IN` for the given attribute. It is intended for use inside
`map_join` / `map_leave` callbacks.

---

## 4. MRPDU Codec

Implemented in `src/core/mrp_pdu.c`. The public interface is `src/include/shish_lan/mrp_pdu.h`.

### 4.1 Wire Format

Per §10.8.1.2 BNF:

```
MRPDU           ::= ProtocolVersion, Message {, Message}, EndMark
Message         ::= AttributeType, AttributeLength
                    [, AttributeListLength], AttributeList
AttributeList   ::= VectorAttribute {, VectorAttribute}, EndMark
VectorAttribute ::= VectorHeader, FirstValue {, Vector}
VectorHeader    ::= (LeaveAllEvent * 8192) + NumberOfValues  [2 octets]
Vector          ::= ThreePackedEvents {, ThreePackedEvents}
                  | FourPackedEvents  {, FourPackedEvents}
EndMark SHORT   ::= 0x0000
```

Key differences between MSRP and MVRP/MMRP:
- `AttributeListLength` is present in the Message header for MSRP (§10.8.2.4);
  absent for MVRP and MMRP.
- Listener attributes in MSRP use FourPackedEvents; all others use ThreePackedEvents.

### 4.2 Event Packing

#### ThreePackedEvents — §10.8.2.10.1

Three `AttributeEvent` values packed into one octet:

```c
static inline uint8_t mrp_three_pack(uint8_t e1, uint8_t e2, uint8_t e3)
{
    return (uint8_t)(((e1 * 6u + e2) * 6u) + e3);
}
static inline void mrp_three_unpack(uint8_t b, uint8_t *e1, uint8_t *e2, uint8_t *e3)
{
    *e3 = b % 6u;  b /= 6u;
    *e2 = b % 6u;  b /= 6u;
    *e1 = b;
}
```

#### FourPackedEvents — §10.8.2.10.2

Four `FourPackedType` values packed into one octet (used by MSRP Listener):

```c
static inline uint8_t mrp_four_pack(uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4)
{
    return (uint8_t)(((e1 * 64u + e2) * 16u) + (e3 * 4u) + e4);
}
static inline void mrp_four_unpack(uint8_t b, uint8_t *e1, uint8_t *e2,
                                   uint8_t *e3, uint8_t *e4)
{
    *e4 = b % 4u;  b /= 4u;
    *e3 = b % 4u;  b /= 4u;
    *e2 = b % 4u;  b /= 4u;
    *e1 = b;
}
```

#### VectorHeader — §10.8.2.8

```c
/* VectorHeader = (LeaveAllEvent << 13) | NumberOfValues */
#define MRP_VH_LEAVEALL_SHIFT 13u
#define MRP_VH_NVALUES_MASK   0x1FFFu

static inline uint16_t mrp_vh_encode(uint8_t la_event, uint16_t n_values);
static inline uint8_t  mrp_vh_la(uint16_t vh);
static inline uint16_t mrp_vh_nv(uint16_t vh);
```

### 4.3 Encode Functions

The encode side is intentionally minimal — it encodes one VectorAttribute at a time:

```c
/* Write ProtocolVersion byte */
int mrpdu_encode_begin(uint8_t *buf, size_t buf_len, uint8_t proto_version);

/* Write trailing EndMark (0x0000) */
int mrpdu_encode_end(uint8_t *buf, size_t buf_len);

/* Encode one VectorAttribute: VectorHeader + FirstValue + one ThreePacked byte */
int mrpdu_encode_vector(uint8_t *buf, size_t buf_len,
                        uint8_t la_event,
                        enum mrp_attr_event attr_event,
                        const uint8_t *first_value, uint8_t fv_len);
```

The Message header (`AttributeType`, `AttributeLength`, and for MSRP
`AttributeListLength`) is the caller's responsibility to write around calls to
`mrpdu_encode_vector`.

### 4.4 Parse Function

```c
typedef void (*mrpdu_on_attr_fn)(void *ctx, uint8_t attr_type,
                                 enum mrp_attr_event attr_event,
                                 const void *attr_val);
typedef void (*mrpdu_on_leaveall_fn)(void *ctx, uint8_t attr_type);

int mrpdu_parse(const uint8_t *pdu, size_t pdu_len,
                const struct mrp_app_ops *ops,
                mrpdu_on_attr_fn on_attr,
                mrpdu_on_leaveall_fn on_leaveall,
                void *ctx);
```

`mrpdu_parse` iterates over every Message and VectorAttribute. For each decoded
`(attr_type, attr_event, attr_val)` triple it calls `on_attr`. For each VectorAttribute
carrying a LeaveAll it calls `on_leaveall`. The `ops` pointer is used to detect MSRP
(for the `AttributeListLength` field) and to call `ops->decode_attr` to compute the
concrete attribute value from `FirstValue + vector offset`.

### 4.5 AttributeEvent Values

```c
enum mrp_attr_event {
    MRP_ATTR_EVENT_NEW    = 0,
    MRP_ATTR_EVENT_JOININ = 1,
    MRP_ATTR_EVENT_IN     = 2,
    MRP_ATTR_EVENT_JOINMT = 3,
    MRP_ATTR_EVENT_MT     = 4,
    MRP_ATTR_EVENT_LV     = 5,
};
```

---

## 5. The `mrp_app_ops` Vtable

`struct mrp_app_ops` in `src/include/shish_lan/mrp.h` is the sole boundary between the
MRP base and any application. Each MRP adapter (MVRP, MMRP, MSRP) fills in a static
constant of this type and passes it to `mrp_app_create`.

```c
struct mrp_app_ops {
    /* MAD_Join.indication — §10.7.6.12 (is_new=true) / §10.7.6.13 (false) */
    void    (*join_ind)(struct mrp_app *app, uint8_t port_id,
                        uint8_t attr_type, const void *attr_val, bool is_new);

    /* MAD_Leave.indication — §10.7.6.14 */
    void    (*leave_ind)(struct mrp_app *app, uint8_t port_id,
                         uint8_t attr_type, const void *attr_val);

    /* MAP policy — §10.3 (see Section 6) */
    uint32_t (*map_join) (const struct mrp_app *app, uint8_t src_port,
                          uint8_t attr_type, const void *attr_val);
    uint32_t (*map_leave)(const struct mrp_app *app, uint8_t src_port,
                          uint8_t attr_type, const void *attr_val);

    /* Encode FirstValue into buf — §10.8.2.7 */
    int     (*encode_attr)(uint8_t attr_type, const void *attr_val,
                           uint8_t *buf, size_t buf_len);

    /* Decode attribute value from buf given FirstValue + vector offset */
    int     (*decode_attr)(uint8_t attr_type, uint32_t offset,
                           const uint8_t *buf, size_t buf_len,
                           void *attr_val_out);

    /* Return FirstValue field length in octets for attr_type */
    uint8_t (*attr_len)(uint8_t attr_type);

    /* Compare two attribute values; return 0 if equal */
    int     (*attr_cmp)(uint8_t attr_type, const void *a, const void *b);

    uint16_t ethertype;      /* §10.5 Table 10-2 */
    uint8_t  proto_version;  /* §10.8.2.1 — always 0 */
    uint8_t  group_addr[6];  /* §10.5 Table 10-1 multicast MAC */
    void    *ctx;            /* opaque application context returned in callbacks */
};
```

Summary of each field:

| Field | Direction | Description |
|---|---|---|
| `join_ind` | base → app | Attribute registered (Registrar transitions to IN) |
| `leave_ind` | base → app | Attribute deregistered (Registrar leaves IN) |
| `map_join` | base → app | Return port bitmask to re-declare on after join |
| `map_leave` | base → app | Return port bitmask to withdraw from after leave |
| `encode_attr` | base → app | Serialize attribute value for MRPDU FirstValue |
| `decode_attr` | base → app | Deserialize FirstValue + offset into attribute value |
| `attr_len` | base → app | Byte length of FirstValue for a given attr_type |
| `attr_cmp` | base → app | Equality check for attribute instance lookup |
| `ethertype` | config | EtherType for outgoing/incoming frames |
| `proto_version` | config | Protocol version byte (0 per §10.8.2.1) |
| `group_addr` | config | Destination multicast MAC address |
| `ctx` | config | Application-specific context pointer |

NULL `map_join` / `map_leave` callbacks mean end-station behaviour — no cross-port
propagation.

---

## 6. MAP Propagation Design

MAP (MRP Attribute Propagation) is the mechanism by which a bridge port that receives
a registration on one port re-declares that attribute on other ports, propagating it
across the bridge fabric. Without MAP, attributes received on port 0 would be visible
only to port 0's state machine; no other port would know about them.

### 6.1 Where MAP is Applied

MAP is applied inside `mrp_mad.c` in the `reg_event()` function, immediately after
each Registrar indication fires:

```c
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
```

### 6.2 MAP Helpers

```c
static void map_apply_join(struct mrp_app *app, uint8_t src_port,
                           uint8_t attr_type, const void *attr_val)
{
    if (!app->ops->map_join) { return; }
    uint32_t ports = app->ops->map_join(app, src_port, attr_type, attr_val);
    if (!ports) { return; }
    uint8_t n = priv_of(app)->n_ports;
    for (uint8_t p = 0; p < n && p < 32u; p++) {
        if (ports & (1u << p)) {
            mrp_mad_join(app, p, attr_type, attr_val, false);
        }
    }
}
```

`map_apply_leave` is symmetric, calling `mrp_mad_leave` on each set port bit.

### 6.3 Loop Prevention

MAP always passes `is_new=false` to `mrp_mad_join`. This drives `MRP_EVENT_JOIN`
rather than `MRP_EVENT_NEW`. Looking at the Registrar table:

- If the attribute is already IN on the target port (because another peer declared it),
  the Registrar ignores a JOIN event — no indication fires, no further MAP call.
- If the attribute is MT on the target port, the Registrar transitions to IN and fires
  `REG_IND_JOIN` (not `REG_IND_NEW`). This then triggers `map_apply_join` again —
  but the `map_join` callback on the target port will return a bitmask excluding
  `src_port`, so propagation terminates at the boundary of the bridge.

The invariant is: MAP propagation from port A causes `join_ind` on ports B, C, …
which in turn triggers MAP from each of those ports — but because each `map_join`
excludes its own `src_port`, the source port is never re-visited, and since all ports
are finite the loop terminates.

### 6.4 Port Bitmask

The bitmask is a `uint32_t`, limiting MAP to a maximum of 32 ports. Bit N represents
port N. This is adequate for all standard bridge configurations.

### 6.5 RSTP Integration (Future)

Per §10.3, MAP must only propagate to Designated ports. When RSTP is integrated, the
bitmask returned by `map_join` / `map_leave` must be gated on port role so that only
Designated ports are included. Root and Alternate ports must be excluded to prevent
bridging loops. This is marked with TODO comments in `msrp.c` and `mrp.h`.

---

## 7. MRP Applications

### 7.1 MVRP — Multiple VLAN Registration Protocol

**Standard:** IEEE 802.1Q-2018 §11.2

**Files:** `src/modules/mvrp.c`, `src/include/shish_lan/mvrp.h`

| Property | Value |
|---|---|
| EtherType | 0x88F5 |
| Group MAC | 01-80-C2-00-00-21 |
| Attribute types | 1 (VID) |
| Value size | 2 octets (big-endian VID, 12-bit) |
| `is_new` | Used — triggers FDB flush per §11.2.5 |
| MAP | Flood to all ports except source |

**Attribute encoding:** VID values increment across vector offsets (standard integer
big-endian increment), so a single VectorAttribute can announce a range of VIDs.

**Context callbacks:**

```c
struct mvrp_ctx {
    void (*on_vlan_registered)  (struct mvrp_ctx *, uint8_t port_id,
                                 uint16_t vid, bool is_new);
    void (*on_vlan_deregistered)(struct mvrp_ctx *, uint8_t port_id,
                                 uint16_t vid);
};
```

**API:**

```c
struct mrp_app *mvrp_app_create(uint8_t n_ports, struct mvrp_ctx *ctx);
void            mvrp_app_destroy(struct mrp_app *app);
int  mvrp_declare (struct mrp_app *app, uint8_t port_id, uint16_t vid);
int  mvrp_withdraw(struct mrp_app *app, uint8_t port_id, uint16_t vid);
```

---

### 7.2 MMRP — Multiple MAC Registration Protocol

**Standard:** IEEE 802.1Q-2018 §10.9–10.12

**Files:** `src/modules/mmrp.c`, `src/include/shish_lan/mmrp.h`

| Property | Value |
|---|---|
| EtherType | 0x88F6 |
| Group MAC | 01-80-C2-00-00-20 |
| Attribute types | 1 (Service), 2 (MAC address) |
| Value sizes | 1 octet (SVC), 6 octets (MAC) |
| `is_new` | Never used — §10.3 NOTE |
| MAP | Flood to all ports except source |
| Mode | Extended Filtering Mode only |

**Attribute encoding:**
- Type 2 (MAC): values increment across vector offsets (big-endian 6-byte addition).
- Type 1 (Service): each value is independent; offset is ignored.

**Context callbacks:**

```c
struct mmrp_ctx {
    void (*on_mac_registered)    (struct mmrp_ctx *, uint8_t port_id,
                                  const struct mmrp_mac *mac);
    void (*on_mac_deregistered)  (struct mmrp_ctx *, uint8_t port_id,
                                  const struct mmrp_mac *mac);
    void (*on_svc_registered)    (struct mmrp_ctx *, uint8_t port_id,
                                  uint8_t svc);
    void (*on_svc_deregistered)  (struct mmrp_ctx *, uint8_t port_id,
                                  uint8_t svc);
};
```

**API:**

```c
struct mrp_app *mmrp_app_create(uint8_t n_ports, struct mmrp_ctx *ctx);
void            mmrp_app_destroy(struct mrp_app *app);
int  mmrp_declare_mac (struct mrp_app *app, uint8_t port_id,
                       const struct mmrp_mac *mac);
int  mmrp_withdraw_mac(struct mrp_app *app, uint8_t port_id,
                       const struct mmrp_mac *mac);
int  mmrp_declare_svc (struct mrp_app *app, uint8_t port_id, uint8_t svc);
int  mmrp_withdraw_svc(struct mrp_app *app, uint8_t port_id, uint8_t svc);
```

---

### 7.3 MSRP — Multiple Stream Reservation Protocol

**Standard:** IEEE 802.1Q-2018 §35 (AVB/TSN stream reservation)

**Files:** `src/modules/msrp.c`, `src/include/shish_lan/msrp.h`

| Property | Value |
|---|---|
| EtherType | 0x22EA |
| Group MAC | 91-E0-F0-00-0E-80 |
| Attribute types | 3 |
| `AttributeListLength` | Present in Message header (unlike MVRP/MMRP) |
| Listener events | FourPackedEvents (not ThreePacked) |

#### Attribute Types

**Type 1 — Talker Advertise (25 octets)**

Announces a data stream and its characteristics.

```c
struct msrp_talker_adv {
    struct msrp_stream_id stream_id;            /* 8 octets */
    uint8_t               data_frame_params[2]; /* dest MAC + VLAN priority */
    uint16_t              max_frame_size;        /* octets */
    uint16_t              max_interval_frames;   /* frames per class interval */
    uint8_t               priority_and_rank;
    uint32_t              accumulated_latency;   /* nanoseconds */
};
```

**Type 2 — Talker Failed (34 octets)**

Extends Talker Advertise to include failure information from a bridge that could not
reserve resources.

```c
struct msrp_talker_failed {
    struct msrp_talker_adv talker;          /* 25 octets */
    uint8_t                failure_info[9]; /* bridge ID + failure code */
};
```

**Type 3 — Listener (8 octets on wire + declaration byte)**

Announces listener interest and reservation status for a stream. The stream is
identified by 8-byte StreamID; the declaration type is conveyed via FourPackedEvents.

```c
enum msrp_listener_decl {
    MSRP_LISTENER_DECL_IGNORE        = 0,
    MSRP_LISTENER_DECL_ASKING_FAILED = 1,
    MSRP_LISTENER_DECL_READY         = 2,
    MSRP_LISTENER_DECL_READY_FAILED  = 3,
};
```

Internally the library stores a Listener attribute as 9 bytes: the 8-byte StreamID
followed by the declaration byte decoded from the FourPackedEvents field.

#### MAP Rules — §35.2.3

MSRP implements the most complex MAP policy:

```c
static uint32_t msrp_map_join(const struct mrp_app *app, uint8_t src_port,
                              uint8_t attr_type, const void *attr_val)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:
    case MSRP_ATTR_TYPE_TALKER_FAILED:
        return all_ports_except(app, src_port);

    case MSRP_ATTR_TYPE_LISTENER: {
        uint32_t talker_ports =
            mrp_attr_registered_ports(app, MSRP_ATTR_TYPE_TALKER_ADV,    attr_val) |
            mrp_attr_registered_ports(app, MSRP_ATTR_TYPE_TALKER_FAILED,  attr_val);
        return talker_ports & all_ports_except(app, src_port);
    }

    default:
        return 0u;  /* Domain / unknown: not propagated */
    }
}
```

Rules:
- **Talker Advertise / Failed:** flood to every port except the ingress port. This
  ensures all bridge ports learn about available streams.
- **Listener:** propagate only toward the talker. The target set is the intersection
  of (ports where a Talker for that StreamID is registered) with (all ports except
  the ingress port). This routes the listener declaration back toward the stream source
  along the existing talker path.
- **Domain (type 4) / Unknown:** not propagated. Domain attributes are per-port
  administrative state.

For `msrp_map_leave`, the Listener case intentionally uses `all_ports_except` rather
than looking up the current talker set. This avoids a stale-talker-set problem: if
the Talker deregistered before the Listener, `mrp_attr_registered_ports` would return
0, leaving orphaned MAP declarations on other ports. Calling `mrp_mad_leave`
unconditionally is safe because `mrp_mad_leave` is a no-op when the attribute is not
registered on a port.

#### Stream ID Matching

`msrp_attr_cmp` compares only the first 8 bytes (the StreamID) regardless of attribute
type. This allows `msrp_map_join` to pass a Listener's `attr_val` pointer directly to
`mrp_attr_registered_ports` with a Talker type: the StreamID occupies the same leading
8 bytes in all three attribute value layouts.

#### Context Callbacks

```c
struct msrp_ctx {
    void (*on_talker_advertise)(struct msrp_ctx *, uint8_t port_id,
                                const struct msrp_talker_adv *, bool is_new);
    void (*on_talker_failed)   (struct msrp_ctx *, uint8_t port_id,
                                const struct msrp_talker_failed *, bool is_new);
    void (*on_listener)        (struct msrp_ctx *, uint8_t port_id,
                                const struct msrp_stream_id *,
                                enum msrp_listener_decl, bool is_new);
    void (*on_leave)           (struct msrp_ctx *, uint8_t port_id,
                                uint8_t attr_type, const void *attr_val);
};
```

#### API

```c
struct mrp_app *msrp_app_create(uint8_t n_ports, struct msrp_ctx *ctx);
void            msrp_app_destroy(struct mrp_app *app);
int  msrp_declare_talker  (struct mrp_app *, uint8_t port_id,
                            const struct msrp_talker_adv *, bool is_new);
int  msrp_declare_listener(struct mrp_app *, uint8_t port_id,
                            const struct msrp_stream_id *,
                            enum msrp_listener_decl decl);
int  msrp_withdraw_talker  (struct mrp_app *, uint8_t port_id,
                             const struct msrp_stream_id *);
int  msrp_withdraw_listener(struct mrp_app *, uint8_t port_id,
                             const struct msrp_stream_id *);
```

---

## 8. Switch Abstraction

Two independent abstraction layers decouple the protocol library from switch hardware.

### 8.1 Switch Operations — `switch.h`

```c
struct shlan_switch_ops {
    int  (*connect)     (struct shlan_switch *sw);
    void (*disconnect)  (struct shlan_switch *sw);
    int  (*port_enable) (struct shlan_switch *sw, uint8_t port_id);
    int  (*port_disable)(struct shlan_switch *sw, uint8_t port_id);
};

struct shlan_switch {
    const struct shlan_switch_ops *ops;
    void                          *priv; /* adapter-private data */
};
```

Inline forwarding wrappers (`shlan_connect`, `shlan_disconnect`, `shlan_port_enable`,
`shlan_port_disable`) hide the vtable dispatch from call sites.

### 8.2 Register Queue — `switch_ctrl.h`

Provides a lock-free MPSC (Multiple-Producer, Single-Consumer) queue for submitting
register read/write transfers to a single driver task.

**Transfer descriptor:**

```c
enum shlan_ctrl_op {
    SHLAN_CTRL_READ  = 0,
    SHLAN_CTRL_WRITE = 1,
};

struct shlan_ctrl_xfer {
    enum shlan_ctrl_op  op;
    uint32_t            reg;     /* register address */
    uint32_t            data;    /* write value / read result */
    bool                linked;  /* true = atomic chain with next transfer */
    void (*done)(struct shlan_ctrl_xfer *xfer, int err); /* completion callback */
    _Atomic(struct shlan_ctrl_xfer *) q_next;            /* queue internal */
};
```

**Queue:**

```c
struct shlan_ctrl_queue {
    _Atomic(struct shlan_ctrl_xfer *) q_tail;
    struct shlan_ctrl_xfer           *q_head;
    struct shlan_ctrl_xfer            q_stub; /* embedded sentinel node */
};
```

**Algorithm:** Dmitry Vyukov's intrusive MPSC node-based queue. `q_tail` is updated
by producers with an atomic exchange; only the single consumer reads `q_head`. No
spinlock or interrupt disable is needed for `shlan_ctrl_enqueue`.

**Atomic chains:** Setting `linked = true` on a transfer binds it atomically with the
next queued transfer. The dispatcher brackets the chain with `begin_atomic` /
`end_atomic` hardware callbacks (chip-select hold for SPI, repeated START for I²C, etc.).

**Hardware adapter operations:**

```c
struct shlan_ctrl_ops {
    int  (*read)        (void *ctx, uint32_t reg, uint32_t *data);
    int  (*write)       (void *ctx, uint32_t reg,  uint32_t  data);
    void (*begin_atomic)(void *ctx);
    void (*end_atomic)  (void *ctx);
};
```

**Dispatcher:** `shlan_ctrl_dispatch(queue, ops, ctx)` drains the queue in FIFO order,
executing reads and writes through the adapter ops and invoking each `done` callback.

---

## 9. Allocation Port

All heap operations and diagnostic output in the library go through wrappers declared
in `src/ports/alloc.h`:

```c
void *shlan_malloc(size_t size);
void *shlan_calloc(size_t nmemb, size_t size);
void  shlan_free(void *ptr);
int   shlan_printf(const char *fmt, ...);
```

The default implementation in `src/ports/alloc.c` calls `malloc`, `calloc`, `free`,
and `printf` from the C standard library. Embedded targets or test harnesses replace
the translation unit with an alternative implementation — no call sites need changing.

---

## 10. Testing

### 10.1 Unit Tests — cgreen

`tests/unit/mrp_pdu_test.c` covers the PDU helper functions exhaustively using the
cgreen test framework. Nine test cases verify:

- `mrp_three_pack` / `mrp_three_unpack` round-trips across the full 0–5 event range
- `mrp_four_pack` / `mrp_four_unpack` round-trips across the full 0–3 range
- `mrp_vh_encode` / `mrp_vh_la` / `mrp_vh_nv` encode and decode correctness
- `mrpdu_encode_vector` output byte layout
- `mrpdu_parse` with a hand-crafted single-attribute MVRP PDU

These tests have no external dependencies beyond cgreen and the library itself. They
are built and run via CMake / ctest:

```sh
cmake -B build && cmake --build build && ctest --test-dir build
```

### 10.2 BDD Tests — behave

`tests/features/switch.feature` defines integration scenarios in Gherkin. The Python
step definitions in `tests/features/steps/switch_steps.py` load `libshlan.so` via
`ctypes` and call through the public C API.

The BDD harness runs entirely in simulation using `sim_adapter.c` — an in-memory
adapter that models port state, frame forwarding, and register accesses without
hardware. This allows full end-to-end coverage of scenarios such as:

- Talker Advertise received on port 0 floods to all other ports
- Listener declaration routes back to the port where the Talker is registered
- VID registration propagates across all ports

Run with:

```sh
behave tests/features/
```

---

## 11. Known TODOs and Future Work

### MSRP Listener FourPackedEvents decoding

`mrpdu_parse` in `mrp_pdu.c` currently uses `mrp_three_unpack` for all attribute
types, including MSRP Listener attributes. MSRP Listener attributes use
`FourPackedEvents` (§35.2.1.4 / §10.8.2.10.2), not ThreePacked. The parser must
detect the MSRP Listener attribute type and call `mrp_four_unpack` instead. This is
marked with a NOTE comment at the top of `msrp.c` and in `mrp_pdu.c`.

The encode side (`mrpdu_encode_vector`) similarly only writes ThreePacked bytes and
will need a FourPacked variant for Listener attributes.

### RSTP port-role gating

Per §10.3, MAP propagation must be restricted to Designated ports. When RSTP is
integrated, the `map_join` and `map_leave` callbacks in each application must gate
the returned port bitmask on RSTP port role. Root and Alternate ports must be
excluded to prevent bridging loops. TODO comments are present in `msrp.c` and `mrp.h`.

### Hardware adapter

Only `sim_adapter.c` (simulation) is currently implemented. A `hw_adapter.c` backed
by the register queue in `switch_ctrl.c` is needed for production use. The
`shlan_switch_ops` and `shlan_ctrl_ops` vtables define the interface it must satisfy.
