/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/mmrp.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/timer.h"

Describe(Integration);
BeforeEach(Integration) {}
AfterEach(Integration) {}

Ensure(Integration, every_application_uses_its_standard_destination)
{
    struct mmrp_ctx mac = {0};
    struct mvrp_ctx vlan = {0};
    struct msrp_ctx stream = {0};
    struct mrp_app *apps[] = {
        mmrp_app_create(1, &mac), mvrp_app_create(1, &vlan),
        msrp_app_create(1, &stream),
    };
    const uint8_t expected[][6] = {
        {0x01, 0x80, 0xc2, 0, 0, 0x20},
        {0x01, 0x80, 0xc2, 0, 0, 0x21},
        {0x01, 0x80, 0xc2, 0, 0, 0x0e},
    };
    for (unsigned n = 0; n < 3; ++n) {
        assert_that(apps[n], is_non_null);
        assert_that(memcmp(apps[n]->ops->group_addr, expected[n], 6), is_equal_to(0));
        mrp_app_destroy(apps[n]);
    }
}

/* Build one wire message independently of the production transmit path. */
static size_t message(const struct mrp_app_ops *ops, uint8_t type,
                      bool leaveall, uint8_t *pdu)
{
    unsigned alen = ops->attr_len(type);
    bool msrp = ops->ethertype == MRP_ETHERTYPE_MSRP;
    bool subtype = ops->attr_has_subtype && ops->attr_has_subtype(type);
    unsigned header = msrp ? 5 : 3;
    unsigned events = leaveall ? 0 : 1 + subtype;
    unsigned list = 2 + alen + events + 2;
    memset(pdu, 0, 64);
    pdu[1] = type;
    pdu[2] = (uint8_t)alen;
    if (msrp) {
        pdu[4] = (uint8_t)list;
    }
    pdu[header] = leaveall ? 0x20 : 0;
    pdu[header + 1] = leaveall ? 0 : 1;
    if (!leaveall && subtype) {
        pdu[header + 2 + alen + 1] = 128; /* Listener Ready. */
    }
    return header + list + 2;
}

struct states {
    enum mrp_appl_state appl[5];
    enum mrp_reg_state reg[5];
};

static void snapshot(void *ctx, const struct mrp_attr_status *status)
{
    struct states *states = ctx;
    states->appl[status->attr_type] = status->appl;
    states->reg[status->attr_type] = status->reg;
}

static void check_leaveall_scope(struct mrp_app *prototype, unsigned types)
{
    struct mrp_app_ops ops = *prototype->ops;
    ops.map_join = NULL;
    ops.map_leave = NULL;
    for (unsigned selected = 1; selected <= types; ++selected) {
        struct mrp_app *app = mrp_app_create(&ops, 2);
        uint8_t pdu[64];
        for (unsigned port = 0; port < 2; ++port) {
            for (unsigned type = 1; type <= types; ++type) {
                size_t len = message(&ops, (uint8_t)type, false, pdu);
                assert_that(mrp_rx(app, (uint8_t)port, pdu, len), is_equal_to(0));
            }
        }
        struct states before[2] = {0}, after[2] = {0};
        for (unsigned port = 0; port < 2; ++port) {
            assert_that(mrp_attr_visit(app, (uint8_t)port, snapshot, &before[port]), is_equal_to(types));
        }
        size_t len = message(&ops, (uint8_t)selected, true, pdu);
        assert_that(mrp_rx(app, 0, pdu, len), is_equal_to(0));
        for (unsigned port = 0; port < 2; ++port) {
            assert_that(mrp_attr_visit(app, (uint8_t)port, snapshot, &after[port]), is_equal_to(types));
            for (unsigned type = 1; type <= types; ++type) {
                assert_that(before[port].appl[type], is_equal_to(MRP_APPL_STATE_VO));
                assert_that(before[port].reg[type], is_equal_to(MRP_REG_STATE_IN));
                if (port == 0 && type == selected) {
                    assert_that(after[port].appl[type], is_equal_to(MRP_APPL_STATE_LO));
                    assert_that(after[port].reg[type], is_equal_to(MRP_REG_STATE_LV));
                } else {
                    assert_that(after[port].appl[type], is_equal_to(before[port].appl[type]));
                    assert_that(after[port].reg[type], is_equal_to(before[port].reg[type]));
                }
            }
        }
        mrp_app_destroy(app);
    }
}

Ensure(Integration, msrp_leaveall_changes_only_the_message_type_and_port)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    check_leaveall_scope(app, 4);
    msrp_app_destroy(app);
}

Ensure(Integration, mmrp_leaveall_changes_only_the_message_type_and_port)
{
    struct mmrp_ctx ctx = {0};
    struct mrp_app *app = mmrp_app_create(1, &ctx);
    check_leaveall_scope(app, 2);
    mmrp_app_destroy(app);
}

static unsigned indications;
static void domain_indication(struct msrp_ctx *ctx, uint8_t port,
                              const struct msrp_domain *domain, bool is_new)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(domain->class_id, is_equal_to(6));
    assert_that(domain->priority, is_equal_to(3));
    assert_that(domain->vid, is_equal_to(2));
    assert_that(is_new, is_true);
    ++indications;
}

Ensure(Integration, domain_receive_calls_the_appended_callback)
{
    struct msrp_ctx ctx = {.on_domain = domain_indication};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t pdu[] = {0, 4, 4, 0, 9, 0, 1, 6, 3, 0, 2, 0, 0, 0, 0, 0};
    indications = 0;
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    assert_that(indications, is_equal_to(1));
    msrp_app_destroy(app);
}

Ensure(Integration, a_malformed_later_message_has_no_earlier_indications)
{
    struct msrp_ctx ctx = {.on_domain = domain_indication};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t pdu[] = {0, 4, 4, 0, 9, 0, 1, 6, 3, 0, 2, 0, 0, 0,
                      3, 8, 0, 14, 0, 1};
    indications = 0;
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_less_than(0));
    assert_that(indications, is_equal_to(0));
    assert_that(mrp_attr_visit(app, 0, NULL, NULL), is_equal_to(0));
    msrp_app_destroy(app);
}

static void tick(unsigned count)
{
    while (count--) {
        shlan_timer_tick();
    }
}

static int accept(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx; (void)port; (void)pdu; (void)len;
    return 0;
}

Ensure(Integration, periodic_is_one_second_independent_of_join_time)
{
    struct mvrp_ctx ctx = {0};
    struct mrp_app *app = mvrp_app_create(1, &ctx);
    uint8_t pdu[64];
    assert_that(mrp_port_configure(app, 0, 5, 60, 1000, 1, true), is_equal_to(0));
    assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(1));
    tick(5);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(1));
    tick(94);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(0));
    tick(1);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(1));
    mrp_set_periodic(app, 0, false);
    tick(100);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(0));
    mrp_set_periodic(app, 0, true);
    tick(99);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(0));
    tick(1);
    assert_that(mrp_transmit(app, 0, pdu, sizeof(pdu), accept, NULL), is_equal_to(1));
    mvrp_app_destroy(app);
}

Ensure(Integration, leaveall_draws_are_inside_the_required_interval)
{
    struct mvrp_ctx ctx = {0};
    unsigned previous = 0;
    const unsigned seeds[] = {1, 2, 3, 168};
    for (unsigned index = 0; index < sizeof(seeds) / sizeof(seeds[0]); ++index) {
        unsigned seed = seeds[index];
        struct mrp_app *app = mvrp_app_create(1, &ctx);
        enum mrp_la_state la;
        assert_that(mrp_port_configure(app, 0, 20, 60, 1000, seed, false), is_equal_to(0));
        tick(1000);
        assert_that(mrp_port_status(app, 0, &la, NULL), is_equal_to(0));
        assert_that(la, is_equal_to(MRP_LA_STATE_PASSIVE));
        unsigned elapsed = 1000;
        do {
            tick(1);
            ++elapsed;
            mrp_port_status(app, 0, &la, NULL);
        } while (la == MRP_LA_STATE_PASSIVE && elapsed < 1500);
        assert_that(la, is_equal_to(MRP_LA_STATE_ACTIVE));
        assert_that(elapsed, is_greater_than(1000));
        assert_that(elapsed, is_less_than(1500));
        assert_that(elapsed, is_not_equal_to(previous));
        previous = elapsed;
        mvrp_app_destroy(app);
    }
}

static unsigned leaves;
static void listener_left(struct msrp_ctx *ctx, uint8_t port, uint8_t type, const void *value)
{
    (void)ctx; (void)port; (void)type;
    assert_that(((const uint8_t *)value)[8], is_equal_to(MSRP_LISTENER_DECL_READY));
    ++leaves;
}

static int reject(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx; (void)port; (void)pdu; (void)len;
    return -1;
}

Ensure(Integration, registrar_ages_while_a_transmission_is_retained)
{
    struct msrp_ctx ctx = {.on_leave = listener_left};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t rx[64], tx[128];
    size_t len = message(app->ops, MSRP_ATTR_TYPE_LISTENER, false, rx);
    assert_that(mrp_rx(app, 0, rx, len), is_equal_to(0));
    len = message(app->ops, MSRP_ATTR_TYPE_LISTENER, true, rx);
    assert_that(mrp_rx(app, 0, rx, len), is_equal_to(0));
    struct msrp_talker_adv talker = {0};
    assert_that(msrp_declare_talker(app, 0, &talker, true), is_equal_to(0));
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), reject, NULL), is_less_than(0));
    leaves = 0;
    tick(59);
    assert_that(leaves, is_equal_to(0));
    tick(1);
    assert_that(leaves, is_equal_to(1));
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    msrp_app_destroy(app);
}

Ensure(Integration, local_withdrawal_keeps_the_registered_listener_value)
{
    struct msrp_ctx ctx = {.on_leave = listener_left};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t rx[64];
    struct msrp_stream_id sid = {{0}};
    size_t len = message(app->ops, MSRP_ATTR_TYPE_LISTENER, false, rx);
    assert_that(mrp_rx(app, 0, rx, len), is_equal_to(0));
    assert_that(msrp_withdraw_listener(app, 0, &sid), is_equal_to(0));
    len = message(app->ops, MSRP_ATTR_TYPE_LISTENER, true, rx);
    assert_that(mrp_rx(app, 0, rx, len), is_equal_to(0));
    leaves = 0;
    tick(60);
    assert_that(leaves, is_equal_to(1));
    msrp_app_destroy(app);
}

static void check_applicant(struct mrp_app *app, enum mrp_appl_state expected)
{
    struct states state = {0};
    assert_that(mrp_attr_visit(app, 0, snapshot, &state), is_equal_to(1));
    assert_that(state.appl[1], is_equal_to(expected));
}

Ensure(Integration, applicant_declaration_recovery_and_withdrawal_follow_the_table)
{
    struct mvrp_ctx ctx = {0};
    struct mrp_app *app = mvrp_app_create(1, &ctx);
    uint8_t rx[] = {0, 1, 2, 0, 1, 0, 2, 36, 0, 0, 0, 0};
    uint8_t tx[64];
    assert_that(mrp_rx(app, 0, rx, sizeof(rx)), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_AO);
    assert_that(mrp_rx(app, 0, rx, sizeof(rx)), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_QO);
    assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_QP);
    tick(100);
    check_applicant(app, MRP_APPL_STATE_AP);
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    check_applicant(app, MRP_APPL_STATE_QA);
    assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_QA);
    const uint8_t value[] = {0, 2};
    assert_that(mrp_mad_join(app, 0, 1, value, true), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_VN);
    tick(20);
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    check_applicant(app, MRP_APPL_STATE_AN);
    rx[3] = 0x20;
    rx[7] = 144;
    assert_that(mrp_rx(app, 0, rx, sizeof(rx)), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_VN);
    assert_that(mvrp_withdraw(app, 0, 2), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_LA);
    assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_AA);
    assert_that(mvrp_withdraw(app, 0, 2), is_equal_to(0));
    check_applicant(app, MRP_APPL_STATE_LA);
    tick(20);
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
    check_applicant(app, MRP_APPL_STATE_VO);
    mvrp_app_destroy(app);
}

Ensure(Integration, applicant_receive_conditions_follow_link_mode)
{
    struct mvrp_ctx ctx = {0};
    for (unsigned p2p = 0; p2p < 2; ++p2p) {
        struct mrp_app *app = mvrp_app_create(1, &ctx);
        uint8_t rx[] = {0, 1, 2, 0, 1, 0, 2, 36, 0, 0, 0, 0};
        assert_that(mrp_port_configure(app, 0, 20, 60, 1000, 1, p2p), is_equal_to(0));
        assert_that(mrp_rx(app, 0, rx, sizeof(rx)), is_equal_to(0));
        check_applicant(app, p2p ? MRP_APPL_STATE_VO : MRP_APPL_STATE_AO);
        mvrp_app_destroy(app);
        app = mvrp_app_create(1, &ctx);
        assert_that(mrp_port_configure(app, 0, 20, 60, 1000, 1, p2p), is_equal_to(0));
        uint8_t tx[64];
        assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
        assert_that(mrp_transmit(app, 0, tx, sizeof(tx), accept, NULL), is_equal_to(1));
        check_applicant(app, MRP_APPL_STATE_AA);
        rx[7] = 72;
        assert_that(mrp_rx(app, 0, rx, sizeof(rx)), is_equal_to(0));
        check_applicant(app, p2p ? MRP_APPL_STATE_QA : MRP_APPL_STATE_AA);
        mvrp_app_destroy(app);
    }
}

static unsigned leaveall_types;
static void received_leaveall(void *ctx, uint8_t type)
{
    (void)ctx;
    leaveall_types |= 1u << type;
}

static int inspect_leaveall(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    const struct mrp_app_ops *ops = ctx;
    assert_that(port, is_equal_to(0));
    assert_that(mrpdu_parse(pdu, len, ops, NULL, received_leaveall, NULL), is_equal_to(0));
    return 0;
}

Ensure(Integration, transmitted_leaveall_includes_every_supported_type)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t tx[128];
    tick(1500);
    leaveall_types = 0;
    assert_that(mrp_transmit(app, 0, tx, sizeof(tx), inspect_leaveall, (void *)app->ops), is_equal_to(1));
    assert_that(leaveall_types, is_equal_to(0x1e));
    enum mrp_la_state la;
    assert_that(mrp_port_status(app, 0, &la, NULL), is_equal_to(0));
    assert_that(la, is_equal_to(MRP_LA_STATE_PASSIVE));
    msrp_app_destroy(app);
}

Ensure(Integration, later_versions_skip_unknown_stream_messages)
{
    struct msrp_ctx ctx = {.on_domain = domain_indication};
    struct mrp_app *app = msrp_app_create(1, &ctx);
    uint8_t pdu[] = {1, 5, 1, 0, 2, 0, 0,
                       4, 4, 0, 9, 0, 1, 6, 3, 0, 2, 0, 0, 0, 0, 0};
    indications = 0;
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    assert_that(indications, is_equal_to(1));
    msrp_app_destroy(app);
}

TestSuite *integration_suite(void)
{
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Integration, every_application_uses_its_standard_destination);
    add_test_with_context(suite, Integration, msrp_leaveall_changes_only_the_message_type_and_port);
    add_test_with_context(suite, Integration, mmrp_leaveall_changes_only_the_message_type_and_port);
    add_test_with_context(suite, Integration, domain_receive_calls_the_appended_callback);
    add_test_with_context(suite, Integration, a_malformed_later_message_has_no_earlier_indications);
    add_test_with_context(suite, Integration, periodic_is_one_second_independent_of_join_time);
    add_test_with_context(suite, Integration, leaveall_draws_are_inside_the_required_interval);
    add_test_with_context(suite, Integration, registrar_ages_while_a_transmission_is_retained);
    add_test_with_context(suite, Integration, local_withdrawal_keeps_the_registered_listener_value);
    add_test_with_context(suite, Integration, applicant_declaration_recovery_and_withdrawal_follow_the_table);
    add_test_with_context(suite, Integration, applicant_receive_conditions_follow_link_mode);
    add_test_with_context(suite, Integration, transmitted_leaveall_includes_every_supported_type);
    add_test_with_context(suite, Integration, later_versions_skip_unknown_stream_messages);
    return suite;
}
