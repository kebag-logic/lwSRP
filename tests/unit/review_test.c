/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/mmrp.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/timer.h"
#include "shish_lan/error.h"
#include "fault_alloc.h"

Describe(Boundaries);
static unsigned joins, leaves, maps, decoded, leavealls;
static unsigned indicated_value;
BeforeEach(Boundaries)
{
    joins = leaves = maps = decoded = leavealls = 0;
    allocation_fail_after(0);
    assert_that(allocation_live(), is_equal_to(0));
}
AfterEach(Boundaries)
{
    allocation_fail_after(0);
    assert_that(allocation_live(), is_equal_to(0));
}
static void tick(unsigned n)
{
    while (n--) {
        shlan_timer_tick();
    }
}
static void joined(struct mrp_app *a, uint8_t p, uint8_t t, const void *v, bool n)
{
    (void)a; (void)p; (void)n; ++joins;
    if (t == MSRP_ATTR_TYPE_LISTENER) {
        indicated_value = ((const uint8_t *)v)[8];
    } else if (t == MSRP_ATTR_TYPE_TALKER_ADV) {
        /* Only stream tests inspect this captured value. */
        indicated_value = 0;
    }
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
static size_t stream_pdu(uint8_t *pdu, bool listener, unsigned value,
                         unsigned event, bool leave_all)
{
    size_t len = listener ? 21 : 37;
    memset(pdu, 0, len);
    pdu[1] = listener ? 3 : 1;
    pdu[2] = listener ? 8 : 25;
    pdu[4] = listener ? 14 : 30;
    pdu[5] = leave_all ? 0x20 : 0;
    pdu[6] = 1; pdu[14] = 1;
    if (listener) {
        pdu[15] = (uint8_t)(36 * event);
        pdu[16] = (uint8_t)(value << 6);
    } else {
        pdu[23] = (uint8_t)(value >> 8); pdu[24] = (uint8_t)value;
        pdu[32] = (uint8_t)(36 * event);
    }
    return len;
}
struct stream_state {
    unsigned value;
    enum mrp_reg_state reg;
    enum mrp_appl_state appl;
};
static void stream_snapshot(void *ctx, const struct mrp_attr_status *s)
{
    struct stream_state *st = ctx;
    if (s->attr_type == MSRP_ATTR_TYPE_TALKER_ADV) {
        st->value = ((const struct msrp_talker_adv *)s->attr_val)->max_frame_size;
    } else if (s->attr_type == MSRP_ATTR_TYPE_LISTENER) {
        st->value = ((const uint8_t *)s->attr_val)[8];
    } else {
        return;
    }
    st->reg = s->reg; st->appl = s->appl;
}
static struct stream_state stream_state(struct mrp_app *a, uint8_t port)
{
    struct stream_state st = {0};
    mrp_attr_visit(a, port, stream_snapshot, &st);
    return st;
}
static uint32_t stream_targets(const struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)t; (void)v; ++maps;
    return p == 0 ? 6u : 0;
}
static void stream_joined(struct mrp_app *a, uint8_t p, uint8_t t, const void *v, bool n)
{
    joined(a, p, t, v, n);
    if (t == MSRP_ATTR_TYPE_TALKER_ADV) {
        indicated_value = ((const struct msrp_talker_adv *)v)->max_frame_size;
    }
}
static struct mrp_app *stream_bridge(void)
{
    struct mrp_app *base = application(2, 1, true);
    struct mrp_app_ops ops = *base->ops;
    ops.join_ind = stream_joined;
    ops.map_join = stream_targets; ops.map_leave = stream_targets;
    mrp_app_destroy(base);
    struct mrp_app *a = mrp_app_create(&ops, 3);
    for (uint8_t p = 0; p < 3; ++p) {
        assert_that(mrp_port_configure(a, p, 20, 60, 10000, 1, true), is_equal_to(0));
        mrp_set_periodic(a, p, false);
    }
    return a;
}
static void changed_after_leaveall(bool transmitted)
{
    for (unsigned listener = 0; listener < 2; ++listener) {
        for (unsigned event = 1; event <= 3; event += 2) {
            struct mrp_app *a = stream_bridge();
            uint8_t pdu[64], tx[256];
            unsigned old = listener ? 2 : 100, next = listener ? 1 : 200;
            size_t len = stream_pdu(pdu, listener, old, event, false);
            joins = leaves = maps = 0;
            if (transmitted) {
                assert_that(mrp_port_configure(a, 0, 20, 60, 1000, 1, true), is_equal_to(0));
            }
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            if (transmitted) {
                tick(1500);
                assert_that(mrp_transmit(a, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
            } else {
                /* A LeaveAll-only message enters LV without renewing the value. */
                pdu[5] = 0x20; pdu[6] = 0;
                pdu[4] = listener ? 12 : 29;
                len = listener ? 19 : 36;
                memset(pdu + 7 + pdu[2], 0, 4);
                assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            }
            assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_LV));
            len = stream_pdu(pdu, listener, next, event, false);
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            assert_that(joins, is_equal_to(2));
            assert_that(indicated_value, is_equal_to(next));
            assert_that(maps, is_equal_to(2));
            assert_that(leaves, is_equal_to(0));
            assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_IN));
            assert_that(stream_state(a, 1).value, is_equal_to(next));
            assert_that(stream_state(a, 2).value, is_equal_to(next));
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            tick(60);
            assert_that(joins, is_equal_to(2));
            assert_that(leaves, is_equal_to(0));
            mrp_app_destroy(a);
        }
    }
}
Ensure(Boundaries, changed_values_after_received_leaveall_are_indicated_and_propagated)
{
    changed_after_leaveall(false);
}
Ensure(Boundaries, changed_values_after_transmitted_leaveall_are_indicated_and_propagated)
{
    changed_after_leaveall(true);
}
Ensure(Boundaries, unknown_stream_layout_uses_attribute_list_length)
{
    uint8_t pdu[] = {1,9,1,0,8,0,1,7,36,0,0,0xaa,0xbb,
                    3,8,0,14,0,1,1,2,3,4,5,6,0,1,36,128,0,0,0,0};
    struct mrp_app *a = application(2, 1, false);
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    assert_that(joins, is_equal_to(1));
    assert_that(indicated_value, is_equal_to(2));
    mrp_app_destroy(a);
    a = application(2, 1, false); pdu[0] = 0;
    unchanged_rejection(a, pdu, sizeof(pdu));
    mrp_app_destroy(a);
}
Ensure(Boundaries, unknown_generic_messages_reject_zero_attribute_length)
{
    uint8_t pdu[] = {1,9,0,0,1,0,0,0,1,2,0,1,0,2,0,0,0,0,0};
    for (unsigned kind = 0; kind < 2; ++kind) {
        struct mrp_app *a = application(kind, 1, false);
        uint8_t mac[] = {1,9,0,0,1,0,0,0,1,1,0,1,0,0,0,0,0,0};
        unchanged_rejection(a, kind == 0 ? pdu : mac, kind == 0 ? sizeof(pdu) : sizeof(mac));
        mrp_app_destroy(a);
    }
}
Ensure(Boundaries, changed_value_allocation_failure_preserves_retry)
{
    for (unsigned listener = 0; listener < 2; ++listener) {
        for (unsigned lv = 0; lv < 2; ++lv) {
            struct mrp_app *a = stream_bridge();
            unsigned old = listener ? 2 : 100, next = listener ? 1 : 200;
            uint8_t pdu[64]; size_t len = stream_pdu(pdu, listener, old, 1, false);
            joins = leaves = 0;
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            len = stream_pdu(pdu, listener, next, 1, lv);
            allocation_fail_after(2); /* Partial reservation must be discarded. */
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(-SHLAN_ERROR_NO_MEMORY));
            assert_that(joins, is_equal_to(1));
            assert_that(indicated_value, is_equal_to(old));
            assert_that(stream_state(a, 0).value, is_equal_to(old));
            assert_that(stream_state(a, 0).reg, is_equal_to(lv ? MRP_REG_STATE_LV : MRP_REG_STATE_IN));
            assert_that(stream_state(a, 1).value, is_equal_to(old));
            assert_that(stream_state(a, 2).value, is_equal_to(old));
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            assert_that(joins, is_equal_to(2));
            assert_that(stream_state(a, 0).value, is_equal_to(next));
            assert_that(stream_state(a, 1).value, is_equal_to(next));
            assert_that(stream_state(a, 2).value, is_equal_to(next));
            mrp_app_destroy(a);
        }
    }
}
Ensure(Boundaries, reservation_failure_is_reported_without_partial_publication)
{
    struct mrp_app *a = stream_bridge();
    assert_that(mrp_port_configure(a, 0, 20, 60, 10000, 1, false), is_equal_to(0));
    uint8_t pdu[64], tx[256]; size_t len = stream_pdu(pdu, false, 100, 1, false);
    allocation_fail_after(3); /* Source instance, first reservation, then fail. */
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(-SHLAN_ERROR_NO_MEMORY));
    assert_that(joins, is_equal_to(0)); assert_that(maps, is_equal_to(0));
    assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_MT));
    assert_that(stream_state(a, 0).appl, is_equal_to(MRP_APPL_STATE_VO));
    for (uint8_t p = 1; p < 3; ++p) {
        assert_that(mrp_transmit(a, p, tx, sizeof(tx), accept, NULL), is_equal_to(0));
        assert_that(mrp_attr_visit(a, p, NULL, NULL), is_equal_to(0));
    }
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    assert_that(joins, is_equal_to(1));
    assert_that(stream_state(a, 1).value, is_equal_to(100));
    assert_that(stream_state(a, 2).value, is_equal_to(100));
    mrp_app_destroy(a);
}
Ensure(Boundaries, timer_allocation_failure_rolls_back_and_retries)
{
    struct mrp_app *a = stream_bridge();
    uint8_t pdu[64]; size_t len = stream_pdu(pdu, false, 100, 1, false);
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    /* LeaveAll plus Mt starts the IEEE deadline in both profiles. */
    stream_pdu(pdu, false, 100, 4, true);
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    tick(59); allocation_fail_after(2); tick(1);
    assert_that(leaves, is_equal_to(0));
    assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_LV));
    tick(1);
    assert_that(leaves, is_equal_to(1));
    assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_MT));
    assert_that(stream_state(a, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
    assert_that(stream_state(a, 2).appl, is_equal_to(MRP_APPL_STATE_VO));
    mrp_app_destroy(a);
}
static void retain_target(struct mrp_app *a, uint8_t *tx, size_t len)
{
    struct msrp_domain d = {6,3,2};
    assert_that(mrp_mad_join(a, 1, 4, &d, true), is_equal_to(0));
    assert_that(mrp_transmit(a, 1, tx, len, refuse, NULL), is_less_than(0));
}
Ensure(Boundaries, failed_commit_replay_is_retried_by_the_next_poll)
{
    struct mrp_app *a = stream_bridge();
    uint8_t pdu[64], tx[256], saved[256];
    retain_target(a, tx, sizeof(tx)); memcpy(saved, tx, sizeof(tx));
    size_t len = stream_pdu(pdu, false, 100, 1, false);
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    allocation_fail_after(1);
    assert_that(mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    assert_that(memcmp(tx, saved, sizeof(tx)), is_equal_to(0));
    assert_that(stream_state(a, 1).value, is_equal_to(0));
    (void)mrp_transmit(a, 1, tx, sizeof(tx), accept, NULL);
    assert_that(stream_state(a, 1).value, is_equal_to(100));
    mrp_app_destroy(a);
}
Ensure(Boundaries, destroy_releases_all_queued_allocations)
{
    size_t before = allocation_live();
    struct mrp_app *a = stream_bridge();
    uint8_t pdu[64], tx[256]; retain_target(a, tx, sizeof(tx));
    size_t len = stream_pdu(pdu, false, 100, 1, false);
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    mrp_app_destroy(a);
    assert_that(allocation_live(), is_equal_to(before));
}
static unsigned join_seen, leave_seen;
static uint32_t join_after_indication(const struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v;
    join_seen = joins;
    return joins ? 2u : 0;
}
static uint32_t leave_after_indication(const struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v;
    leave_seen = leaves;
    return leaves ? 2u : 0;
}
Ensure(Boundaries, propagation_policy_observes_completed_host_indications)
{
    struct mrp_app *base = application(0, 1, false);
    struct mrp_app_ops ops = *base->ops;
    ops.map_join = join_after_indication; ops.map_leave = leave_after_indication;
    mrp_app_destroy(base);
    struct mrp_app *a = mrp_app_create(&ops, 2);
    uint8_t pdu[] = {0,1,2,0,1,0,2,0,0,0,0,0};
    join_seen = leave_seen = 0;
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    assert_that(join_seen, is_equal_to(1));
    assert_that(mrp_attr_visit(a, 1, NULL, NULL), is_equal_to(1));
    pdu[7] = 180;
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    tick(60);
    assert_that(leave_seen, is_equal_to(1));
    assert_that(state(a, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
    mrp_app_destroy(a);
}
Ensure(Boundaries, flush_allocation_failures_retry_withdrawal_on_the_next_tick)
{
    for (unsigned lv = 0; lv < 2; ++lv) {
        for (unsigned fault = 0; fault <= 3; ++fault) {
            struct mrp_app *a = stream_bridge();
            uint8_t pdu[64];
            size_t len = stream_pdu(pdu, false, 100, 1, false);
            joins = leaves = maps = 0;
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            if (lv) {
                stream_pdu(pdu, false, 100, 4, true);
                assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            }
            allocation_fail_after(fault);
            mrp_port_role_change(a, 0, true);
            assert_that(leaves, is_equal_to(fault ? 0 : 1));
            assert_that(stream_state(a, 0).reg,
                        is_equal_to(fault ? MRP_REG_STATE_LV : MRP_REG_STATE_MT));
            if (fault) {
                /* Exhaustion on a second dispatch must retain the withdrawal. */
                allocation_fail_after(fault);
                tick(1);
                assert_that(leaves, is_equal_to(0));
                assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_LV));
            }
            allocation_fail_after(0);
            tick(1);
            assert_that(leaves, is_equal_to(1));
            assert_that(maps, is_equal_to(2));
            assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_MT));
            assert_that(stream_state(a, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
            assert_that(stream_state(a, 2).appl, is_equal_to(MRP_APPL_STATE_VO));
            len = stream_pdu(pdu, false, 100, 1, false);
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            tick(2);
            assert_that(joins, is_equal_to(2));
            assert_that(leaves, is_equal_to(1));
            assert_that(stream_state(a, 0).reg, is_equal_to(MRP_REG_STATE_IN));
            mrp_app_destroy(a);
            assert_that(allocation_live(), is_equal_to(0));
        }
    }
}

static unsigned indication_order[8], indication_count;
static void ordered_join(struct mrp_app *a, uint8_t p, uint8_t t, const void *v, bool n)
{
    joined(a, p, t, v, n);
    if (indication_count < 8) {
        indication_order[indication_count++] = t;
    }
}
static void ordered_leave(struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    left(a, p, t, v);
    if (indication_count < 8) {
        indication_order[indication_count++] = 10u + t;
    }
}
struct typed_state {
    uint8_t type;
    unsigned sid;
    struct status state;
};
static void typed_snapshot(void *ctx, const struct mrp_attr_status *s)
{
    struct typed_state *st = ctx;
    if (s->attr_type == st->type && ((const uint8_t *)s->attr_val)[7] == st->sid) {
        st->state.appl = s->appl;
        st->state.reg = s->reg;
        ++st->state.count;
    }
}
static struct status typed_state(struct mrp_app *a, uint8_t port, uint8_t type, unsigned sid)
{
    struct typed_state st = {.type = type, .sid = sid};
    mrp_attr_visit(a, port, typed_snapshot, &st);
    return st.state;
}
static size_t talker_pdu(uint8_t *pdu, unsigned type)
{
    size_t len = stream_pdu(pdu, false, 100, 1, false);
    if (type == MSRP_ATTR_TYPE_TALKER_FAILED) {
        memset(pdu + 32, 0, 14);
        pdu[1] = 2; pdu[2] = 34; pdu[4] = 39;
        pdu[40] = 1; pdu[41] = 36;
        len = 46;
    }
    return len;
}
Ensure(Boundaries, replacement_allocation_failures_keep_leave_before_join)
{
    for (unsigned old_type = 1; old_type <= 2; ++old_type) {
        for (unsigned fault = 0; fault <= 9; ++fault) {
            struct mrp_app *base = stream_bridge();
            struct mrp_app_ops ops = *base->ops;
            ops.join_ind = ordered_join; ops.leave_ind = ordered_leave;
            mrp_app_destroy(base);
            struct mrp_app *a = mrp_app_create(&ops, 3);
            uint8_t pdu[64], tx[256];
            size_t len = talker_pdu(pdu, old_type);
            assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            indication_count = 0;
            unsigned next_type = 3u - old_type;
            len = talker_pdu(pdu, next_type);
            /* New instance, three Leave reservations, three Join reservations,
             * and two destination instances: sweep every allocation. */
            allocation_fail_after(fault);
            int r = mrp_rx(a, 0, pdu, len);
            allocation_fail_after(0);
            assert_that(r, is_equal_to(fault > 0 && fault <= 7 ? -SHLAN_ERROR_NO_MEMORY : 0));
            if (fault > 0 && fault <= 4) {
                assert_that(indication_count, is_equal_to(0));
            }
            if (r < 0) {
                assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
            }
            for (uint8_t p = 1; p < 3; ++p) {
                assert_that(mrp_transmit(a, p, tx, sizeof(tx), accept, NULL), is_greater_than(-1));
                assert_that(typed_state(a, p, (uint8_t)next_type, 1).count, is_equal_to(1));
            }
            tick(1);
            assert_that(indication_count, is_equal_to(2));
            assert_that(indication_order[0], is_equal_to(10u + old_type));
            assert_that(indication_order[1], is_equal_to(next_type));
            assert_that(typed_state(a, 0, (uint8_t)old_type, 1).reg, is_equal_to(MRP_REG_STATE_MT));
            assert_that(typed_state(a, 0, (uint8_t)next_type, 1).reg, is_equal_to(MRP_REG_STATE_IN));
            mrp_app_destroy(a);
            assert_that(allocation_live(), is_equal_to(0));
        }
    }
}
Ensure(Boundaries, reservation_failure_stops_later_receive_messages)
{
    for (unsigned fault = 2; fault <= 4; ++fault) {
        struct mrp_app *a = stream_bridge();
        uint8_t pdu[80], second[64];
        size_t len = stream_pdu(pdu, false, 100, 1, false);
        size_t next = stream_pdu(second, false, 200, 1, false);
        second[14] = 2;
        memcpy(pdu + len - 2, second + 1, next - 1);
        len += next - 3;
        joins = 0;
        allocation_fail_after(fault);
        assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(-SHLAN_ERROR_NO_MEMORY));
        assert_that(joins, is_equal_to(0));
        for (uint8_t p = 0; p < 3; ++p) {
            assert_that(typed_state(a, p, 1, 2).count, is_equal_to(0));
        }
        assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
        assert_that(joins, is_equal_to(2));
        assert_that(typed_state(a, 1, 1, 2).count, is_equal_to(1));
        assert_that(typed_state(a, 2, 1, 2).count, is_equal_to(1));
        mrp_app_destroy(a);
    }
}
Ensure(Boundaries, propagation_obeys_talker_and_listener_policy_masks)
{
    struct mrp_app *a = application(2, 3, true);
    for (uint8_t p = 0; p < 3; ++p) {
        assert_that(mrp_port_configure(a, p, 20, 60, 10000, 1, true), is_equal_to(0));
    }
    uint8_t pdu[64];
    size_t len = stream_pdu(pdu, false, 100, 1, false);
    assert_that(mrp_rx(a, 0, pdu, len), is_equal_to(0));
    assert_that(typed_state(a, 0, 1, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
    assert_that(typed_state(a, 1, 1, 1).appl, is_equal_to(MRP_APPL_STATE_VP));
    assert_that(typed_state(a, 2, 1, 1).appl, is_equal_to(MRP_APPL_STATE_VP));
    len = stream_pdu(pdu, true, 2, 1, false);
    assert_that(mrp_rx(a, 2, pdu, len), is_equal_to(0));
    assert_that(typed_state(a, 0, 3, 1).appl, is_equal_to(MRP_APPL_STATE_VP));
    assert_that(typed_state(a, 1, 3, 1).count, is_equal_to(0));
    assert_that(typed_state(a, 2, 3, 1).appl, is_equal_to(MRP_APPL_STATE_VO));
    mrp_app_destroy(a);
}
Ensure(Boundaries, applications_without_policy_do_not_reserve_propagation)
{
    struct mrp_app *a = application(0, 3, true);
    uint8_t pdu[] = {0,1,2,0,1,0,2,36,0,0,0,0};
    allocation_fail_after(2); /* The source instance is the only allocation. */
    assert_that(mrp_rx(a, 0, pdu, sizeof(pdu)), is_equal_to(0));
    allocation_fail_after(0);
    assert_that(joins, is_equal_to(1));
    assert_that(state(a, 0).reg, is_equal_to(MRP_REG_STATE_IN));
    allocation_fail_after(1); /* Withdrawal must also allocate nothing. */
    mrp_port_role_change(a, 0, true);
    allocation_fail_after(0);
    assert_that(leaves, is_equal_to(1));
    assert_that(state(a, 0).reg, is_equal_to(MRP_REG_STATE_MT));
    assert_that(mrp_attr_visit(a, 1, NULL, NULL), is_equal_to(0));
    assert_that(mrp_attr_visit(a, 2, NULL, NULL), is_equal_to(0));
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
    add_test_with_context(s, Boundaries, changed_values_after_received_leaveall_are_indicated_and_propagated);
    add_test_with_context(s, Boundaries, changed_values_after_transmitted_leaveall_are_indicated_and_propagated);
    add_test_with_context(s, Boundaries, unknown_stream_layout_uses_attribute_list_length);
    add_test_with_context(s, Boundaries, unknown_generic_messages_reject_zero_attribute_length);
    add_test_with_context(s, Boundaries, changed_value_allocation_failure_preserves_retry);
    add_test_with_context(s, Boundaries, reservation_failure_is_reported_without_partial_publication);
    add_test_with_context(s, Boundaries, timer_allocation_failure_rolls_back_and_retries);
    add_test_with_context(s, Boundaries, failed_commit_replay_is_retried_by_the_next_poll);
    add_test_with_context(s, Boundaries, destroy_releases_all_queued_allocations);
    add_test_with_context(s, Boundaries, propagation_policy_observes_completed_host_indications);
    add_test_with_context(s, Boundaries, flush_allocation_failures_retry_withdrawal_on_the_next_tick);
    add_test_with_context(s, Boundaries, replacement_allocation_failures_keep_leave_before_join);
    add_test_with_context(s, Boundaries, reservation_failure_stops_later_receive_messages);
    add_test_with_context(s, Boundaries, propagation_obeys_talker_and_listener_policy_masks);
    add_test_with_context(s, Boundaries, applications_without_policy_do_not_reserve_propagation);
    return s;
}
