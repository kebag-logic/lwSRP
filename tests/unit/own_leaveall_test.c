/* SPDX-License-Identifier: Apache-2.0 */
/*
 * The participant's own LeaveAll (issue #20). At a transmit opportunity with
 * LeaveAll, each Applicant takes exactly one of txLA! (its message fits) or
 * txLAF! (it is omitted), and no later rLA!. The sLA's rLA! still reaches
 * every Registrar, and the LeaveAll machine goes Passive (IEEE 802.1Q-2018
 * 10.7.6.6, Tables 10-3, 10-4 and 10-5). Transmitted PDUs are read with the
 * test-side decoder, which shares no code with the library parser.
 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "ports/timer.h"
#include "fault_alloc.h"
#include "mrpdu_decoder.h"

Describe(OwnLeaveAll);
BeforeEach(OwnLeaveAll)
{
    allocation_fail_after(0);
    assert_that(allocation_live(), is_equal_to(0));
}
AfterEach(OwnLeaveAll)
{
    assert_that(allocation_live(), is_equal_to(0));
}

#define JOIN_CS 20u
#define ABSENT 99u

/* AttributeEvent values (IEEE 802.1Q-2018 10.8.2.5). */
enum wire {
    WIRE_NEW = 0,
    WIRE_JOIN_IN,
    WIRE_IN,
    WIRE_JOIN_MT,
    WIRE_MT,
    WIRE_LV,
};

static uint8_t sent[2048];
static size_t sent_len;
static unsigned sends;
static struct mrpdu_decoded pdu;

static int capture(void *ctx, uint8_t port, const uint8_t *data, size_t len)
{
    (void)ctx; (void)port;
    assert_that(len, is_less_than(sizeof(sent) + 1u));
    sent_len = len < sizeof(sent) ? len : sizeof(sent);
    memcpy(sent, data, sent_len);
    ++sends;
    return 0;
}

static void tick(unsigned count)
{
    while (count--) {
        shlan_timer_tick();
    }
}

/* One transmit opportunity that must send exactly one MRPDU; it is decoded. */
static void send_one(struct mrp_app *a, size_t capacity)
{
    static uint8_t buffer[2048];
    sends = 0;
    assert_that(mrp_transmit(a, 0, buffer, capacity, capture, NULL), is_equal_to(1));
    assert_that(sends, is_equal_to(1));
    struct mrpdu_profile profile = mrpdu_profile_for(a->ops->ethertype);
    assert_that(mrpdu_decode(sent, sent_len, &profile, &pdu), is_equal_to(0));
}

static void send_none(struct mrp_app *a)
{
    static uint8_t buffer[2048];
    sends = 0;
    assert_that(mrp_transmit(a, 0, buffer, sizeof(buffer), capture, NULL), is_equal_to(0));
    assert_that(sends, is_equal_to(0));
}

/* The AttributeEvent the last PDU carries for one value, or ABSENT. */
static unsigned event_of(uint8_t type, const uint8_t *value, size_t len)
{
    for (size_t n = 0; n < pdu.vectors; ++n) {
        const struct mrpdu_vector *v = &pdu.vector[n];
        if (v->type == type && v->values == 1u && v->length == len &&
            memcmp(v->first_value, value, len) == 0) {
            return mrpdu_event(v, 0);
        }
    }
    return ABSENT;
}

static unsigned four_packed_of(uint8_t type, const uint8_t *value, size_t len)
{
    for (size_t n = 0; n < pdu.vectors; ++n) {
        const struct mrpdu_vector *v = &pdu.vector[n];
        if (v->type == type && v->values == 1u && memcmp(v->first_value, value, len) == 0) {
            return mrpdu_four_packed(v, 0);
        }
    }
    return ABSENT;
}

/* The bit set of AttributeTypes the last PDU flags LeaveAll. */
static unsigned leave_all_types(void)
{
    unsigned types = 0;
    for (size_t n = 0; n < pdu.vectors; ++n) {
        if (pdu.vector[n].leave_all == 1u) {
            assert_that(pdu.vector[n].values, is_equal_to(0));
            types |= 1u << pdu.vector[n].type;
        }
    }
    return types;
}

/* Values carried by the last PDU, LeaveAll-only vectors excluded. */
static unsigned values_sent(void)
{
    unsigned count = 0;
    for (size_t n = 0; n < pdu.vectors; ++n) {
        count += pdu.vector[n].values;
    }
    return count;
}

static enum mrp_la_state leave_all_state(struct mrp_app *a)
{
    enum mrp_la_state la = MRP_LA_STATE_PASSIVE;
    assert_that(mrp_port_status(a, 0, &la, NULL), is_equal_to(0));
    return la;
}

/* Tick until the LeaveAll machine is Active; 10.7.4.3 bounds the draw. */
static void until_leave_all(struct mrp_app *a)
{
    enum mrp_la_state la = MRP_LA_STATE_PASSIVE;
    for (unsigned waited = 0; waited < 1600u; ++waited) {
        (void)mrp_port_status(a, 0, &la, NULL);
        if (la == MRP_LA_STATE_ACTIVE) {
            break;
        }
        tick(1);
    }
    assert_that(leave_all_state(a), is_equal_to(MRP_LA_STATE_ACTIVE));
}

/* Every observed transition of one LeaveAll opportunity. */
struct seen {
    enum mrp_event event;
    uint8_t type;
    uint8_t value[8];
    enum mrp_appl_state appl_from, appl_to;
    enum mrp_reg_state reg_from, reg_to;
};
static struct seen seen[32];
static unsigned seen_count;

static void record(void *ctx, const struct mrp_transition *t)
{
    (void)ctx;
    assert_that(seen_count, is_less_than(32));
    if (seen_count < 32u) {
        struct seen *s = &seen[seen_count++];
        s->event = t->event;
        s->type = t->attr_type;
        memcpy(s->value, t->attr_val, sizeof(s->value));
        s->appl_from = t->appl_from; s->appl_to = t->appl_to;
        s->reg_from = t->reg_from; s->reg_to = t->reg_to;
    }
}

/* No Applicant moves on rLA!, and none moves twice (exactly one of txLA! or txLAF!). */
static void one_leave_all_event_per_applicant(void)
{
    for (unsigned n = 0; n < seen_count; ++n) {
        if (seen[n].appl_from == seen[n].appl_to) {
            continue;
        }
        assert_that(seen[n].event == MRP_EVENT_TXLA || seen[n].event == MRP_EVENT_TXLAF, is_true);
        for (unsigned m = n + 1u; m < seen_count; ++m) {
            bool same = seen[m].type == seen[n].type &&
                        memcmp(seen[m].value, seen[n].value, sizeof(seen[n].value)) == 0;
            assert_that(same && seen[m].appl_from != seen[m].appl_to, is_false);
        }
    }
}

/* The Applicant changes one value took in the recorded opportunity, and the last one's event. */
static unsigned applicant_moves(uint8_t type, const uint8_t *value, size_t len, enum mrp_event *event)
{
    unsigned moves = 0;
    for (unsigned n = 0; n < seen_count; ++n) {
        if (seen[n].type == type && memcmp(seen[n].value, value, len) == 0 &&
            seen[n].appl_from != seen[n].appl_to) {
            *event = seen[n].event;
            ++moves;
        }
    }
    return moves;
}

/* A Registrar change on rLA! that leaves the Applicant unchanged, for one value. */
static bool registrar_took_rla(uint8_t type, const uint8_t *value, size_t len)
{
    for (unsigned n = 0; n < seen_count; ++n) {
        if (seen[n].event == MRP_EVENT_RLA && seen[n].type == type &&
            memcmp(seen[n].value, value, len) == 0) {
            return seen[n].appl_from == seen[n].appl_to &&
                   seen[n].reg_from == MRP_REG_STATE_IN && seen[n].reg_to == MRP_REG_STATE_LV;
        }
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* The stream participant of issue #20                                  */
/* ------------------------------------------------------------------ */

/* Locally administered identities. */
static const uint8_t stream[8] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};
static const uint8_t domain_wire[4] = {6, 3, 0, 2};
static const struct msrp_domain domain = {6, 3, 2};

struct appl_reg {
    enum mrp_appl_state appl;
    enum mrp_reg_state reg;
    bool found;
};
struct probe {
    uint8_t type;
    struct appl_reg state;
};

static void probe_visit(void *ctx, const struct mrp_attr_status *s)
{
    struct probe *p = ctx;
    if (s->attr_type == p->type) {
        p->state.appl = s->appl; p->state.reg = s->reg; p->state.found = true;
    }
}

/* The stream participant holds one value of each type it uses. */
static struct appl_reg of_type(struct mrp_app *a, uint8_t type)
{
    struct probe p = {.type = type};
    mrp_attr_visit(a, 0, probe_visit, &p);
    assert_that(p.state.found, is_true);
    return p.state;
}

static bool holds(struct mrp_app *a, uint8_t type)
{
    struct probe p = {.type = type};
    mrp_attr_visit(a, 0, probe_visit, &p);
    return p.state.found;
}

static void check(struct mrp_app *a, uint8_t type, enum mrp_appl_state appl, enum mrp_reg_state reg)
{
    struct appl_reg s = of_type(a, type);
    assert_that(mrp_appl_state_name(s.appl), is_equal_to_string(mrp_appl_state_name(appl)));
    assert_that(mrp_reg_state_name(s.reg), is_equal_to_string(mrp_reg_state_name(reg)));
}

/*
 * The board of issue #20, at one input: a peer registers its Talker Advertise
 * and its Domain; the participant declares the Domain and a Ready Listener for
 * that stream, and both reach QA. Periodic transmission is off, so only the
 * LeaveAll and the declarations move an Applicant. Returns at LeaveAll Active.
 */
static struct mrp_app *stream_board(void)
{
    static struct msrp_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));
    struct mrp_app *a = msrp_app_create(1, &ctx);
    assert_that(mrp_port_configure(a, 0, JOIN_CS, 60, 1000, 7, true), is_equal_to(0));
    mrp_set_periodic(a, 0, false);
    uint8_t peer[50] = {0,
        1, 25, 0, 30, 0x00, 0x01,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,   /* StreamID */
        0x91, 0xe0, 0xf0, 0x00, 0xfe, 0x00, 0x00, 0x02,   /* DA, VID */
        0x00, 0xe0, 0x00, 0x01, 0x70, 0x00, 0x00, 0x03, 0xe8,
        36, 0, 0,                                          /* JoinIn, EndMark */
        4, 4, 0, 9, 0x00, 0x01, 6, 3, 0, 2, 36, 0, 0,       /* Domain JoinIn */
        0, 0};
    assert_that(mrp_rx(a, 0, peer, sizeof(peer)), is_equal_to(0));
    assert_that(mrp_mad_join(a, 0, MSRP_ATTR_TYPE_DOMAIN, &domain, true), is_equal_to(0));
    struct msrp_stream_id sid;
    memcpy(sid.bytes, stream, sizeof(stream));
    assert_that(msrp_declare_listener(a, 0, &sid, MSRP_LISTENER_DECL_READY), is_equal_to(0));
    /* New, New, then the Listener's JoinMt (Table 10-3: VN, AN, QA or AA by note 8, QA). */
    for (unsigned n = 0; n < 3u; ++n) {
        send_one(a, sizeof(sent));
        tick(JOIN_CS);
    }
    send_none(a);
    check(a, MSRP_ATTR_TYPE_DOMAIN, MRP_APPL_STATE_QA, MRP_REG_STATE_IN);
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_QA, MRP_REG_STATE_MT);
    check(a, MSRP_ATTR_TYPE_TALKER_ADV, MRP_APPL_STATE_VO, MRP_REG_STATE_IN);
    until_leave_all(a);
    seen_count = 0;
    mrp_set_observer(a, record, NULL);
    return a;
}

/* Later Join-spaced opportunities send nothing for the Listener. */
static void listener_quiet(struct mrp_app *a, unsigned opportunities)
{
    static uint8_t buffer[2048];
    struct mrpdu_profile profile = mrpdu_profile_for(a->ops->ethertype);
    for (unsigned n = 0; n < opportunities; ++n) {
        tick(JOIN_CS);
        sends = 0;
        int r = mrp_transmit(a, 0, buffer, sizeof(buffer), capture, NULL);
        assert_that(r == 0 || r == 1, is_true);
        if (r == 1) {
            assert_that(mrpdu_decode(sent, sent_len, &profile, &pdu), is_equal_to(0));
            assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(ABSENT));
        }
    }
}

static void withdraw_listener(struct mrp_app *a)
{
    struct msrp_stream_id sid;
    memcpy(sid.bytes, stream, sizeof(stream));
    assert_that(msrp_withdraw_listener(a, 0, &sid), is_equal_to(0));
}

/* Ruling row "fitting attribute": the LeaveAll PDU carries the Join; QA stays QA. */
Ensure(OwnLeaveAll, a_declaration_that_fits_the_leaveall_pdu_stays_quiet)
{
    struct mrp_app *a = stream_board();
    send_one(a, sizeof(sent));
    assert_that(leave_all_types(), is_equal_to(0x1e));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(WIRE_JOIN_MT));
    assert_that(four_packed_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(MSRP_LISTENER_DECL_READY));
    assert_that(event_of(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 4), is_equal_to(WIRE_JOIN_IN));
    assert_that(values_sent(), is_equal_to(2));
    /* QA -txLA!/sJ-> QA; the Registrars take the LeaveAll (Table 10-4). */
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_QA, MRP_REG_STATE_MT);
    check(a, MSRP_ATTR_TYPE_DOMAIN, MRP_APPL_STATE_QA, MRP_REG_STATE_LV);
    check(a, MSRP_ATTR_TYPE_TALKER_ADV, MRP_APPL_STATE_LO, MRP_REG_STATE_LV);
    assert_that(leave_all_state(a), is_equal_to(MRP_LA_STATE_PASSIVE));
    one_leave_all_event_per_applicant();
    /* Nothing re-declares the fitted values: LO alone sends its Mt. */
    tick(JOIN_CS);
    send_one(a, sizeof(sent));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(ABSENT));
    assert_that(event_of(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 4), is_equal_to(ABSENT));
    assert_that(values_sent(), is_equal_to(1));
    tick(JOIN_CS);
    send_none(a);
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_QA, MRP_REG_STATE_MT);
    msrp_app_destroy(a);
}

/* Ruling row "withdrawal": Lv! -> LA after the LeaveAll PDU; the next PDU carries Lv. */
Ensure(OwnLeaveAll, a_withdrawal_after_the_leaveall_pdu_sends_its_leave)
{
    struct mrp_app *a = stream_board();
    send_one(a, sizeof(sent));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(WIRE_JOIN_MT));
    /* The capture's case: the withdrawal 120 ms after the LeaveAll PDU. */
    tick(12);
    withdraw_listener(a);
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_LA, MRP_REG_STATE_MT);
    send_none(a);   /* The Join timer still runs (10.7.4.1). */
    tick(JOIN_CS - 12u);
    send_one(a, sizeof(sent));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(WIRE_LV));
    assert_that(four_packed_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(MSRP_LISTENER_DECL_READY));
    assert_that(event_of(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 4), is_equal_to(ABSENT));
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_VO, MRP_REG_STATE_MT);
    /* VO with MT is free (Table 10-3 note 11): the Lv was sent before it went. */
    assert_that(mrp_reclaim(a, 0), is_equal_to(1));
    assert_that(holds(a, MSRP_ATTR_TYPE_LISTENER), is_false);
    tick(JOIN_CS);
    send_none(a);
    msrp_app_destroy(a);
}

/* Ruling row "omitted attribute": txLAF! -> VP; Lv! -> VO, with no Lv and no later Join. */
Ensure(OwnLeaveAll, a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently)
{
    struct mrp_app *a = stream_board();
    /* Room for the four LeaveAll vectors (1 + 33 + 42 + 16 + 12 + 2 octets) and no value. */
    send_one(a, 106);
    assert_that(sent_len, is_equal_to(106));
    assert_that(leave_all_types(), is_equal_to(0x1e));
    assert_that(values_sent(), is_equal_to(0));
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_VP, MRP_REG_STATE_MT);
    /* The omitted Domain's Registrar takes the sLA's rLA! (10.7.6.6). */
    check(a, MSRP_ATTR_TYPE_DOMAIN, MRP_APPL_STATE_VP, MRP_REG_STATE_LV);
    assert_that(registrar_took_rla(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 2), is_true);
    check(a, MSRP_ATTR_TYPE_TALKER_ADV, MRP_APPL_STATE_LO, MRP_REG_STATE_LV);
    one_leave_all_event_per_applicant();
    withdraw_listener(a);
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_VO, MRP_REG_STATE_MT);
    for (unsigned n = 0; n < 2u; ++n) {
        tick(JOIN_CS);
        send_one(a, sizeof(sent));
        assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(ABSENT));
        assert_that(event_of(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 4), is_equal_to(WIRE_JOIN_MT));
    }
    tick(JOIN_CS);
    send_none(a);
    assert_that(mrp_reclaim(a, 0), is_greater_than(0));
    assert_that(holds(a, MSRP_ATTR_TYPE_LISTENER), is_false);
    msrp_app_destroy(a);
}

/* Ruling row "Lv! before the LeaveAll": LA -txLA!-> LO, no Join. */
Ensure(OwnLeaveAll, a_withdrawal_before_the_leaveall_pdu_sends_no_join)
{
    struct mrp_app *a = stream_board();
    withdraw_listener(a);
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_LA, MRP_REG_STATE_MT);
    seen_count = 0;
    send_one(a, sizeof(sent));
    assert_that(leave_all_types(), is_equal_to(0x1e));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(ABSENT));
    assert_that(event_of(MSRP_ATTR_TYPE_DOMAIN, domain_wire, 4), is_equal_to(WIRE_JOIN_IN));
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_LO, MRP_REG_STATE_MT);
    enum mrp_event event = MRP_EVENT_COUNT;
    assert_that(applicant_moves(MSRP_ATTR_TYPE_LISTENER, stream, 8, &event), is_equal_to(1));
    assert_that(mrp_event_name(event), is_equal_to_string(mrp_event_name(MRP_EVENT_TXLA)));
    /* LO -tx!/s-> VO: Mt, never Join or Lv (Table 10-3). */
    tick(JOIN_CS);
    send_one(a, sizeof(sent));
    assert_that(event_of(MSRP_ATTR_TYPE_LISTENER, stream, 8), is_equal_to(WIRE_MT));
    check(a, MSRP_ATTR_TYPE_LISTENER, MRP_APPL_STATE_VO, MRP_REG_STATE_MT);
    listener_quiet(a, 3);
    msrp_app_destroy(a);
}

/* ------------------------------------------------------------------ */
/* Every Applicant state against the txLA! and txLAF! rows              */
/* ------------------------------------------------------------------ */

/*
 * One VLAN per Applicant state, on shared media so that AO, QO, AP and QP
 * occur. Each row is Table 10-3's, written here independently of the library:
 * the state before the LeaveAll opportunity, the Registrar it holds, the
 * message txLA! sends and the state after it, and txLAF!'s state.
 */
struct row {
    uint16_t vid;
    enum mrp_appl_state before;
    enum mrp_reg_state reg;
    unsigned txla_sends;
    enum mrp_appl_state after_txla, after_txlaf;
};
static const struct row rows[] = {
    {2,  MRP_APPL_STATE_VO, MRP_REG_STATE_IN, ABSENT,       MRP_APPL_STATE_LO, MRP_APPL_STATE_LO},
    {3,  MRP_APPL_STATE_VP, MRP_REG_STATE_MT, WIRE_MT,      MRP_APPL_STATE_AA, MRP_APPL_STATE_VP},
    {4,  MRP_APPL_STATE_VN, MRP_REG_STATE_MT, WIRE_NEW,     MRP_APPL_STATE_AN, MRP_APPL_STATE_VN},
    {5,  MRP_APPL_STATE_AN, MRP_REG_STATE_MT, WIRE_NEW,     MRP_APPL_STATE_QA, MRP_APPL_STATE_VN},
    {6,  MRP_APPL_STATE_AA, MRP_REG_STATE_MT, WIRE_JOIN_MT, MRP_APPL_STATE_QA, MRP_APPL_STATE_VP},
    {7,  MRP_APPL_STATE_QA, MRP_REG_STATE_IN, WIRE_JOIN_IN, MRP_APPL_STATE_QA, MRP_APPL_STATE_VP},
    {8,  MRP_APPL_STATE_LA, MRP_REG_STATE_MT, ABSENT,       MRP_APPL_STATE_LO, MRP_APPL_STATE_LO},
    {9,  MRP_APPL_STATE_AO, MRP_REG_STATE_IN, ABSENT,       MRP_APPL_STATE_LO, MRP_APPL_STATE_LO},
    {10, MRP_APPL_STATE_QO, MRP_REG_STATE_IN, ABSENT,       MRP_APPL_STATE_LO, MRP_APPL_STATE_LO},
    {11, MRP_APPL_STATE_AP, MRP_REG_STATE_IN, WIRE_JOIN_IN, MRP_APPL_STATE_QA, MRP_APPL_STATE_VP},
    {12, MRP_APPL_STATE_QP, MRP_REG_STATE_IN, WIRE_JOIN_IN, MRP_APPL_STATE_QA, MRP_APPL_STATE_VP},
    {13, MRP_APPL_STATE_LO, MRP_REG_STATE_MT, ABSENT,       MRP_APPL_STATE_LO, MRP_APPL_STATE_LO},
};
#define ROWS (sizeof(rows) / sizeof(rows[0]))

struct vlan_probe {
    uint8_t value[2];
    struct appl_reg state;
};

static void vlan_visit(void *ctx, const struct mrp_attr_status *s)
{
    struct vlan_probe *p = ctx;
    if (memcmp(s->attr_val, p->value, 2) == 0) {
        p->state.appl = s->appl; p->state.reg = s->reg; p->state.found = true;
    }
}

static struct appl_reg of_vlan(struct mrp_app *a, uint16_t vid)
{
    struct vlan_probe p = {.value = {(uint8_t)(vid >> 8), (uint8_t)vid}};
    mrp_attr_visit(a, 0, vlan_visit, &p);
    assert_that(p.state.found, is_true);
    return p.state;
}

static void receive(struct mrp_app *a, uint16_t vid, enum wire event)
{
    uint8_t rx[] = {0, 1, 2, 0, 1, (uint8_t)(vid >> 8), (uint8_t)vid, (uint8_t)(36u * event), 0, 0, 0, 0};
    assert_that(mrp_rx(a, 0, rx, sizeof(rx)), is_equal_to(0));
}

static void new_vlan(struct mrp_app *a, uint16_t vid)
{
    const uint8_t value[2] = {(uint8_t)(vid >> 8), (uint8_t)vid};
    assert_that(mrp_mad_join(a, 0, MVRP_ATTR_TYPE_VID, value, true), is_equal_to(0));
}

/* Drive each VLAN of the table to its state, then wait for the LeaveAll. */
static struct mrp_app *vlan_states(void)
{
    static struct mvrp_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));
    struct mrp_app *a = mvrp_app_create(1, &ctx);
    assert_that(mrp_port_configure(a, 0, JOIN_CS, 60, 1000, 3, false), is_equal_to(0));
    mrp_set_periodic(a, 0, false);
    assert_that(mvrp_declare(a, 0, 7), is_equal_to(0));
    assert_that(mvrp_declare(a, 0, 8), is_equal_to(0));
    send_one(a, sizeof(sent));                  /* 7, 8: VP -> AA */
    tick(JOIN_CS);
    new_vlan(a, 5);
    assert_that(mvrp_declare(a, 0, 6), is_equal_to(0));
    send_one(a, sizeof(sent));                  /* 7, 8: QA; 5: AN; 6: AA */
    tick(JOIN_CS);
    assert_that(mvrp_withdraw(a, 0, 8), is_equal_to(0));    /* QA -> LA */
    assert_that(mvrp_declare(a, 0, 3), is_equal_to(0));     /* VP */
    new_vlan(a, 4);                                         /* VN */
    receive(a, 7, WIRE_JOIN_IN);                            /* QA, IN */
    receive(a, 2, WIRE_JOIN_MT);                            /* VO, IN */
    receive(a, 9, WIRE_JOIN_IN);                            /* AO */
    receive(a, 10, WIRE_JOIN_IN);
    receive(a, 10, WIRE_JOIN_IN);                           /* QO */
    receive(a, 11, WIRE_JOIN_IN);
    assert_that(mvrp_declare(a, 0, 11), is_equal_to(0));    /* AP */
    receive(a, 12, WIRE_JOIN_IN);
    receive(a, 12, WIRE_JOIN_IN);
    assert_that(mvrp_declare(a, 0, 12), is_equal_to(0));    /* QP */
    receive(a, 13, WIRE_LV);                                /* LO */
    for (unsigned n = 0; n < ROWS; ++n) {
        struct appl_reg s = of_vlan(a, rows[n].vid);
        assert_that(mrp_appl_state_name(s.appl), is_equal_to_string(mrp_appl_state_name(rows[n].before)));
        assert_that(mrp_reg_state_name(s.reg), is_equal_to_string(mrp_reg_state_name(rows[n].reg)));
    }
    until_leave_all(a);
    seen_count = 0;
    mrp_set_observer(a, record, NULL);
    return a;
}

static void registrars_took_the_leave_all(struct mrp_app *a)
{
    for (unsigned n = 0; n < ROWS; ++n) {
        enum mrp_reg_state expected = rows[n].reg == MRP_REG_STATE_IN ? MRP_REG_STATE_LV : rows[n].reg;
        assert_that(mrp_reg_state_name(of_vlan(a, rows[n].vid).reg),
                    is_equal_to_string(mrp_reg_state_name(expected)));
    }
}

/* Every state's txLA! cell: message and next state, with no rLA! after it. */
Ensure(OwnLeaveAll, a_leaveall_pdu_that_fits_gives_each_applicant_its_txla_cell)
{
    struct mrp_app *a = vlan_states();
    send_one(a, sizeof(sent));
    assert_that(leave_all_types(), is_equal_to(1u << MVRP_ATTR_TYPE_VID));
    for (unsigned n = 0; n < ROWS; ++n) {
        const uint8_t value[2] = {(uint8_t)(rows[n].vid >> 8), (uint8_t)rows[n].vid};
        assert_that(event_of(MVRP_ATTR_TYPE_VID, value, 2), is_equal_to(rows[n].txla_sends));
        assert_that(mrp_appl_state_name(of_vlan(a, rows[n].vid).appl),
                    is_equal_to_string(mrp_appl_state_name(rows[n].after_txla)));
    }
    registrars_took_the_leave_all(a);
    one_leave_all_event_per_applicant();
    assert_that(leave_all_state(a), is_equal_to(MRP_LA_STATE_PASSIVE));
    mvrp_app_destroy(a);
}

/* Every state's txLAF! cell when no value fits; the Registrars still take rLA!. */
Ensure(OwnLeaveAll, a_full_leaveall_pdu_gives_each_omitted_applicant_its_txlaf_cell)
{
    struct mrp_app *a = vlan_states();
    /* ProtocolVersion, one Message with the LeaveAll vector, and the EndMark. */
    send_one(a, 11);
    assert_that(sent_len, is_equal_to(11));
    assert_that(leave_all_types(), is_equal_to(1u << MVRP_ATTR_TYPE_VID));
    assert_that(values_sent(), is_equal_to(0));
    for (unsigned n = 0; n < ROWS; ++n) {
        assert_that(mrp_appl_state_name(of_vlan(a, rows[n].vid).appl),
                    is_equal_to_string(mrp_appl_state_name(rows[n].after_txlaf)));
    }
    registrars_took_the_leave_all(a);
    one_leave_all_event_per_applicant();
    assert_that(leave_all_state(a), is_equal_to(MRP_LA_STATE_PASSIVE));
    mvrp_app_destroy(a);
}

TestSuite *own_leaveall_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, OwnLeaveAll, a_declaration_that_fits_the_leaveall_pdu_stays_quiet);
    add_test_with_context(s, OwnLeaveAll, a_withdrawal_after_the_leaveall_pdu_sends_its_leave);
    add_test_with_context(s, OwnLeaveAll, a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently);
    add_test_with_context(s, OwnLeaveAll, a_withdrawal_before_the_leaveall_pdu_sends_no_join);
    add_test_with_context(s, OwnLeaveAll, a_leaveall_pdu_that_fits_gives_each_applicant_its_txla_cell);
    add_test_with_context(s, OwnLeaveAll, a_full_leaveall_pdu_gives_each_omitted_applicant_its_txlaf_cell);
    return s;
}
