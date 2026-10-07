/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/mmrp.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/timer.h"

Describe(Boundaries);
static unsigned joins, leaves, maps, decoded, leavealls;
BeforeEach(Boundaries) { joins = leaves = maps = decoded = leavealls = 0; }
AfterEach(Boundaries) {}
static void tick(unsigned n)
{
    while (n--) {
        shlan_timer_tick();
    }
}
static void joined(struct mrp_app *a, uint8_t p, uint8_t t, const void *v, bool n)
{
    (void)a; (void)p; (void)t; (void)v; (void)n; ++joins;
}
static void left(struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v; ++leaves;
}
static uint32_t mapped(const struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v; ++maps; return 0;
}
static struct mrp_app *application(unsigned kind, unsigned ports, bool propagate)
{
    struct msrp_ctx stream = {0}; struct mvrp_ctx vlan = {0}; struct mmrp_ctx mac = {0};
    struct mrp_app *prototype = kind == 0 ? mvrp_app_create(1, &vlan) :
        kind == 1 ? mmrp_app_create(1, &mac) : msrp_app_create(1, &stream);
    struct mrp_app_ops ops = *prototype->ops;
    ops.join_ind = joined; ops.leave_ind = left; ops.ctx = NULL;
    if (!propagate) {
        ops.map_join = mapped; ops.map_leave = NULL;
    }
    mrp_app_destroy(prototype);
    return mrp_app_create(&ops, (uint8_t)ports);
}
static void attribute(void *ctx, uint8_t t, enum mrp_attr_event e, const void *v)
{
    (void)ctx; (void)t; (void)e; (void)v; ++decoded;
}
static void leaveall(void *ctx, uint8_t t)
{
    (void)ctx; (void)t; ++leavealls;
}
static void unchanged_rejection(struct mrp_app *a, uint8_t *pdu, size_t len)
{
    unsigned before = joins;
    assert_that(mrpdu_parse(pdu, len, a->ops, attribute, leaveall, NULL), is_less_than(0));
    assert_that(decoded + leavealls, is_equal_to(0));
    assert_that(mrp_rx(a, 0, pdu, len), is_less_than(0));
    assert_that(joins, is_equal_to(before));
    assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(0));
}
Ensure(Boundaries, application_errors_reject_the_whole_pdu)
{
    struct mrp_app *a = application(2, 1, false);
    uint8_t invalid_first[] = {0,4,4,0,9,0,1,5,8,0,2,0,0,0,
                              3,8,0,14,0,1,1,2,3,4,5,6,0,1,0,128,0,0,0,0};
    unchanged_rejection(a, invalid_first, sizeof(invalid_first));
    uint8_t invalid_last[] = {0,3,8,0,14,0x20,1,1,2,3,4,5,6,0,1,0,128,0,0,
                             4,4,0,9,0,1,5,8,0,2,0,0,0,0,0};
    unchanged_rejection(a, invalid_last, sizeof(invalid_last));
    uint8_t domain[] = {0,4,4,0,9,0,2,5,7,0,2,0,0,0,0,0};
    unchanged_rejection(a, domain, sizeof(domain));
    domain[7] = 255; domain[8] = 6;
    unchanged_rejection(a, domain, sizeof(domain));
    domain[7] = 254;
    assert_that(mrp_rx(a, 0, domain, sizeof(domain)), is_equal_to(0));
    assert_that(joins, is_equal_to(2));
    mrp_app_destroy(a);
}
Ensure(Boundaries, stream_vectors_cannot_wrap_identity_or_destination)
{
    for (uint8_t type = 1; type <= 3; ++type) {
        unsigned alen = type == 1 ? 25 : type == 2 ? 34 : 8;
        unsigned list = 2 + alen + 1 + (type == 3) + 2;
        uint8_t pdu[48] = {0};
        pdu[1] = type; pdu[2] = (uint8_t)alen; pdu[4] = (uint8_t)list;
        pdu[6] = 2; pdu[13] = 255; pdu[14] = 255;
        if (type == 3) {
            pdu[16] = 160; /* Both Listener values Ready. */
        }
        struct mrp_app *a = application(2, 1, false);
        unchanged_rejection(a, pdu, 7 + list);
        pdu[14] = 254;
        assert_that(mrp_rx(a, 0, pdu, 7 + list), is_equal_to(0));
        assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(2));
        mrp_app_destroy(a);
        if (type != 3) {
            a = application(2, 1, false);
            pdu[13] = pdu[14] = 0;
            memset(pdu + 15, 255, 6);
            unchanged_rejection(a, pdu, 7 + list);
            pdu[20] = 254;
            assert_that(mrp_rx(a, 0, pdu, 7 + list), is_equal_to(0));
            assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(2));
            mrp_app_destroy(a);
        }
    }
}
Ensure(Boundaries, vlan_and_mac_vector_ranges_are_atomic)
{
    uint8_t vlan[] = {0,1,2,0,2,15,254,0,0,0,0,0};
    struct mrp_app *a = application(0, 1, false);
    unchanged_rejection(a, vlan, sizeof(vlan));
    vlan[5] = 255; vlan[6] = 255;
    unchanged_rejection(a, vlan, sizeof(vlan));
    vlan[5] = 15; vlan[6] = 253;
    assert_that(mrp_rx(a, 0, vlan, sizeof(vlan)), is_equal_to(0));
    assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(2));
    mrp_app_destroy(a);
    uint8_t mac[] = {0,2,6,0,2,255,255,255,255,255,255,0,0,0,0,0};
    a = application(1, 1, false);
    unchanged_rejection(a, mac, sizeof(mac));
    mac[10] = 254;
    assert_that(mrp_rx(a, 0, mac, sizeof(mac)), is_equal_to(0));
    assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(2));
    mrp_app_destroy(a);
}
Ensure(Boundaries, later_versions_skip_unknown_messages_in_every_application)
{
    uint8_t vlan[] = {1,9,1,0,1,7,0,0,0,1,2,0,1,0,2,0,0,0,0,0};
    uint8_t mac[] = {1,9,2,0,1,7,8,0,0,0,2,6,0,1,1,2,3,4,5,6,0,0,0,0,0};
    uint8_t stream[] = {1,9,1,0,6,0,1,7,0,0,0,3,8,0,14,0,1,1,2,3,4,5,6,0,1,0,128,0,0,0,0};
    uint8_t *pdus[] = {vlan, mac, stream};
    size_t sizes[] = {sizeof(vlan), sizeof(mac), sizeof(stream)};
    for (unsigned kind = 0; kind < 3; ++kind) {
        struct mrp_app *a = application(kind, 1, false);
        joins = 0;
        assert_that(mrp_rx(a, 0, pdus[kind], sizes[kind]), is_equal_to(0));
        assert_that(joins, is_equal_to(1));
        assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(1));
        mrp_app_destroy(a);
        a = application(kind, 1, false);
        pdus[kind][0] = 0;
        unchanged_rejection(a, pdus[kind], sizes[kind]);
        mrp_app_destroy(a);
    }
}
Ensure(Boundaries, later_versions_skip_unknown_events_but_current_versions_reject_them)
{
    for (unsigned kind = 0; kind < 3; ++kind) {
        uint8_t vlan[] = {1,1,2,0,1,0,9,216,0,1,0,2,0,0,0,0,0};
        uint8_t mac[] = {1,1,1,0,1,1,216,0,1,0,0,0,0,0,0};
        uint8_t stream[] = {1,3,8,0,26,0,1,1,2,3,4,5,6,0,9,216,128,
                           0,1,1,2,3,4,5,6,0,2,0,128,0,0,0,0};
        uint8_t *pdu = kind == 0 ? vlan : kind == 1 ? mac : stream;
        size_t len = kind == 0 ? sizeof(vlan) : kind == 1 ? sizeof(mac) : sizeof(stream);
        for (unsigned event = 216; event <= 255; ++event) {
            unsigned event_at = kind == 0 ? 7 : kind == 1 ? 6 : 15;
            pdu[event_at] = (uint8_t)event;
            struct mrp_app *a = application(kind, 1, false);
            joins = 0;
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            assert_that(joins, is_equal_to(1));
            assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(1));
            mrp_app_destroy(a);
            a = application(kind, 1, false); pdu[0] = 0;
            unchanged_rejection(a, pdu, len);
            mrp_app_destroy(a); pdu[0] = 1;
        }
    }
}
Ensure(Boundaries, reserved_leaveall_events_are_rejected_atomically)
{
    uint8_t pdu[] = {0,1,2,0,1,0,2,0,0,0,1,2,0,1,0,3,0,0,0,0,0};
    for (unsigned la = 2; la <= 7; ++la) {
        struct mrp_app *a = application(0, 1, false);
        pdu[12] = (uint8_t)(la << 5);
        unchanged_rejection(a, pdu, sizeof(pdu));
        mrp_app_destroy(a);
    }
}
struct status {
    enum mrp_appl_state appl;
    enum mrp_reg_state reg;
    unsigned count;
};
static void snapshot(void *ctx, const struct mrp_attr_status *s)
{
    struct status *st = ctx;
    if (s->attr_type == 1) {
        st->appl = s->appl; st->reg = s->reg; ++st->count;
    }
}
static struct status state(struct mrp_app *a, uint8_t p)
{
    struct status st = {0};
    mrp_attr_visit(a, p, snapshot, &st);
    return st;
}
static int accept(void *ctx, uint8_t p, const uint8_t *data, size_t len)
{
    (void)ctx; (void)p; (void)data; (void)len; return 0;
}
static int refuse(void *ctx, uint8_t p, const uint8_t *data, size_t len)
{
    (void)ctx; (void)p; (void)data; (void)len; return -1;
}
Ensure(Boundaries, retained_ports_replay_propagated_join_and_timer_leave_in_order)
{
    for (unsigned withdrawal = 0; withdrawal < 2; ++withdrawal) {
        struct mrp_app *a = application(2, 2, true);
        uint8_t talker[37] = {0,1,25,0,30,0,1}; talker[14] = 1;
        uint8_t tx[256], saved[256];
        struct msrp_domain domain = {6,3,2};
        for (uint8_t p = 0; p < 2; ++p) {
            assert_that(mrp_port_configure(a, p, 20, 60, 10000, 1, true), is_equal_to(0));
            mrp_set_periodic(a, p, false);
        }
        if (withdrawal) {
            assert_that(mrp_rx(a, 0, talker, sizeof(talker)), is_equal_to(0));
            assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
            tick(20);
            assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
            tick(20);
            assert_that(state(a, 1).appl, is_equal_to(MRP_APPL_STATE_QA));
        }
        assert_that(mrp_mad_join(a, 1, 4, &domain, true), is_equal_to(0));
        memset(tx, 0, sizeof(tx));
        assert_that(mrp_transmit(a, 1, tx, sizeof(tx), refuse, NULL), is_less_than(0));
        memcpy(saved, tx, sizeof(tx));
        if (!withdrawal) {
            assert_that(mrp_rx(a, 0, talker, sizeof(talker)), is_equal_to(0));
            assert_that(state(a, 1).count, is_equal_to(0));
        } else {
            talker[5] = 0x20; talker[32] = 144;
            assert_that(mrp_rx(a, 0, talker, sizeof(talker)), is_equal_to(0));
            tick(60); /* Timer-driven withdrawal in both profiles. */
            assert_that(state(a, 1).appl, is_equal_to(MRP_APPL_STATE_QA));
            assert_that(mrp_reclaim(a, 0), is_equal_to(1));
        }
        assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
        assert_that(memcmp(saved, tx, sizeof(tx)), is_equal_to(0));
        assert_that(state(a, 1).count, is_equal_to(1));
        assert_that(state(a, 1).appl, is_equal_to(withdrawal ? MRP_APPL_STATE_LA : MRP_APPL_STATE_VP));
        tick(20);
        assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
        assert_that(state(a, 1).appl, is_equal_to(withdrawal ? MRP_APPL_STATE_VO : MRP_APPL_STATE_AA));
        mrp_app_destroy(a);
    }
}
Ensure(Boundaries, queued_propagation_owns_values_and_survives_source_reclamation)
{
    struct mrp_app *a = application(2, 2, true);
    uint8_t tx[256]; struct msrp_domain domain = {6,3,2};
    assert_that(mrp_mad_join(a, 1, 4, &domain, true), is_equal_to(0));
    assert_that(mrp_transmit(a, 1, tx, sizeof(tx), refuse, NULL), is_less_than(0));
    uint8_t pdu[37] = {0,1,25,0,30,0,1}; pdu[14] = 1;
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    mrp_port_role_change(a, 0, true); /* Queue Join, then Leave. */
    assert_that(mrp_reclaim(a, 0), is_equal_to(1));
    pdu[14] = 2;
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    memset(pdu, 255, sizeof(pdu));
    assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    assert_that(state(a, 1).count, is_equal_to(2));
    /* The last visited Talker is the withdrawn first identity. */
    assert_that(state(a, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
    mrp_app_destroy(a);
}
Ensure(Boundaries, registrar_recovery_stops_aging_without_duplicate_join_or_map)
{
    for (unsigned join = 1; join <= 3; join += 2) {
        struct mrp_app *a = application(0, 1, false);
        uint8_t pdu[] = {0,1,2,0,1,0,2,0,0,0,0,0};
        joins = maps = leaves = 0;
        assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
        pdu[7] = 180;
        assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
        assert_that(state(a, 0).reg, is_equal_to(MRP_REG_STATE_LV));
        tick(30); pdu[7] = (uint8_t)(36 * join);
        assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
        assert_that(state(a, 0).reg, is_equal_to(MRP_REG_STATE_IN));
        tick(60);
        assert_that(state(a, 0).reg, is_equal_to(MRP_REG_STATE_IN));
        assert_that(joins, is_equal_to(1)); assert_that(maps, is_equal_to(1));
        assert_that(leaves, is_equal_to(0));
        mrp_app_destroy(a);
    }
}
Ensure(Boundaries, committed_leaveall_delivers_local_receive_and_omitted_events)
{
    struct mrp_app *a = application(0, 1, false);
    uint8_t tx[20];
    mrp_set_periodic(a, 0, false);
    for (uint16_t vid = 2; vid < 4; ++vid) {
        assert_that(mvrp_declare(a, 0, vid), is_equal_to(0));
    }
    /* Both applicants reach QA before a LeaveAll that fits just one value. */
    uint8_t large[128];
    assert_that(mrp_transmit(a, 0, large, sizeof(large), accept, NULL), is_equal_to(1));
    tick(20);
    assert_that(mrp_transmit(a, 0, large, sizeof(large), accept, NULL), is_equal_to(1));
    tick(1500);
    assert_that(mrp_transmit(a, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    /* Selected QA -> QA -> VP by local rLA; omitted QA -> VP by txLAF. */
    assert_that(state(a, 0).appl, is_equal_to(MRP_APPL_STATE_VP));
    mrp_app_destroy(a);
}
static unsigned local_rla, omitted_txlaf;
static void events(void *ctx, const struct mrp_transition *t)
{
    (void)ctx;
    if (t->event == MRP_EVENT_RLA) { ++local_rla; }
    if (t->event == MRP_EVENT_TXLAF) { ++omitted_txlaf; }
}
Ensure(Boundaries, full_leaveall_reports_each_required_transition)
{
    struct mrp_app *a = application(0, 1, false);
    uint8_t tx[20], large[128];
    mrp_set_periodic(a, 0, false);
    assert_that(mvrp_declare(a, 0, 2), is_equal_to(0));
    assert_that(mvrp_declare(a, 0, 3), is_equal_to(0));
    assert_that(mrp_transmit(a, 0, large, sizeof(large), accept, NULL), is_equal_to(1));
    tick(20);
    assert_that(mrp_transmit(a, 0, large, sizeof(large), accept, NULL), is_equal_to(1));
    tick(1500);
    local_rla = omitted_txlaf = 0; mrp_set_observer(a, events, NULL);
    assert_that(mrp_transmit(a, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    assert_that(local_rla, is_equal_to(1));
    assert_that(omitted_txlaf, is_equal_to(1));
    mrp_app_destroy(a);
}
Ensure(Boundaries, leaving_observer_is_retained_until_its_pending_transmission)
{
    struct mrp_app *a = application(0, 1, false);
    uint8_t pdu[] = {0,1,2,0,1,0,2,180,0,0,0,0}, tx[64];
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    assert_that(state(a, 0).appl, is_equal_to(MRP_APPL_STATE_LO));
    assert_that(mrp_reclaim(a, 0), is_equal_to(0));
    assert_that(mrp_transmit(a, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    assert_that(mrp_reclaim(a, 0), is_equal_to(1));
    mrp_app_destroy(a);
}
Ensure(Boundaries, received_leaveall_restarts_the_participant_deadline)
{
    struct mrp_app *a = application(0, 1, false);
    assert_that(mrp_port_configure(a, 0, 20, 60, 1000, 1, false), is_equal_to(0));
    tick(900);
    uint8_t pdu[] = {0,1,2,0x20,0,0,0,0,0,0,0};
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    tick(999);
    enum mrp_la_state la;
    mrp_port_status(a, 0, &la, NULL);
    assert_that(la, is_equal_to(MRP_LA_STATE_PASSIVE));
    tick(500); mrp_port_status(a, 0, &la, NULL);
    assert_that(la, is_equal_to(MRP_LA_STATE_ACTIVE));
    mrp_app_destroy(a);
}
TestSuite *boundaries_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, Boundaries, application_errors_reject_the_whole_pdu);
    add_test_with_context(s, Boundaries, stream_vectors_cannot_wrap_identity_or_destination);
    add_test_with_context(s, Boundaries, vlan_and_mac_vector_ranges_are_atomic);
    add_test_with_context(s, Boundaries, later_versions_skip_unknown_messages_in_every_application);
    add_test_with_context(s, Boundaries, later_versions_skip_unknown_events_but_current_versions_reject_them);
    add_test_with_context(s, Boundaries, reserved_leaveall_events_are_rejected_atomically);
    add_test_with_context(s, Boundaries, retained_ports_replay_propagated_join_and_timer_leave_in_order);
    add_test_with_context(s, Boundaries, queued_propagation_owns_values_and_survives_source_reclamation);
    add_test_with_context(s, Boundaries, registrar_recovery_stops_aging_without_duplicate_join_or_map);
    add_test_with_context(s, Boundaries, committed_leaveall_delivers_local_receive_and_omitted_events);
    add_test_with_context(s, Boundaries, full_leaveall_reports_each_required_transition);
    add_test_with_context(s, Boundaries, leaving_observer_is_retained_until_its_pending_transmission);
    add_test_with_context(s, Boundaries, received_leaveall_restarts_the_participant_deadline);
    return s;
}
