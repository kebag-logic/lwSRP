/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/mmrp.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "ports/timer.h"

Describe(Milan);
static unsigned joins, leaves;
static uint8_t expected_type;
static const uint8_t stream_id[8] = {1, 2, 3, 4, 5, 6, 7, 8};
BeforeEach(Milan) { joins = leaves = 0; }
AfterEach(Milan) {}

static void tick(unsigned count)
{
    while (count--) {
        shlan_timer_tick();
    }
}

static void talker_join(struct msrp_ctx *ctx, uint8_t port,
                        const struct msrp_talker_adv *value, bool is_new)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(is_new, is_true);
    assert_that(memcmp(value->stream_id.bytes, stream_id, 8), is_equal_to(0));
    ++joins;
}

static void failed_join(struct msrp_ctx *ctx, uint8_t port,
                        const struct msrp_talker_failed *value, bool is_new)
{
    talker_join(ctx, port, &value->talker, is_new);
}

static void listener_join(struct msrp_ctx *ctx, uint8_t port,
                          const struct msrp_stream_id *value,
                          enum msrp_listener_decl decl, bool is_new)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(is_new, is_true);
    assert_that(memcmp(value->bytes, stream_id, 8), is_equal_to(0));
    assert_that(decl, is_equal_to(MSRP_LISTENER_DECL_READY));
    ++joins;
}

static void stream_leave(struct msrp_ctx *ctx, uint8_t port,
                          uint8_t type, const void *value)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(type, is_equal_to(expected_type));
    assert_that(memcmp(value, stream_id, 8), is_equal_to(0));
    if (type == MSRP_ATTR_TYPE_LISTENER) {
        /* A withdrawal must report the stored Ready value. */
        assert_that(((const uint8_t *)value)[8], is_equal_to(MSRP_LISTENER_DECL_READY));
    }
    ++leaves;
}

static struct msrp_ctx stream_ctx = {
    .on_talker_advertise = talker_join,
    .on_talker_failed = failed_join,
    .on_listener = listener_join,
    .on_leave = stream_leave,
};

/* Literal wire fields keep these checks independent of the transmit encoder. */
static void receive_stream(struct mrp_app *app, uint8_t type,
                            enum mrp_attr_event event, bool leaveall)
{
    uint8_t pdu[48] = {0};
    unsigned alen = type == MSRP_ATTR_TYPE_LISTENER ? 8 :
                    type == MSRP_ATTR_TYPE_TALKER_ADV ? 25 : 34;
    unsigned list = 2 + alen + 1 + (type == MSRP_ATTR_TYPE_LISTENER) + 2;
    pdu[1] = type;
    pdu[2] = (uint8_t)alen;
    pdu[4] = (uint8_t)list;
    pdu[5] = leaveall ? 0x20 : 0;
    pdu[6] = 1;
    memcpy(pdu + 7, stream_id, 8);
    pdu[7 + alen] = (uint8_t)(event * 36);
    if (type == MSRP_ATTR_TYPE_LISTENER) {
        pdu[8 + alen] = event == MRP_ATTR_EVENT_LV ? 64 : 128;
    }
    assert_that(mrp_rx(app, 0, pdu, 5 + list + 2), is_equal_to(0));
}

static void snapshot(void *ctx, const struct mrp_attr_status *status)
{
    *(enum mrp_reg_state *)ctx = status->reg;
}

static void check_state(struct mrp_app *app, enum mrp_reg_state expected)
{
    enum mrp_reg_state state = MRP_REG_STATE_COUNT;
    assert_that(mrp_attr_visit(app, 0, snapshot, &state), is_equal_to(1));
    assert_that(state, is_equal_to(expected));
}

static void configure(struct mrp_app *app)
{
    assert_that(app, is_non_null);
    assert_that(mrp_port_configure(app, 0, 20, 500, 10000, 1, true), is_equal_to(0));
    mrp_set_periodic(app, 0, false);
    joins = leaves = 0;
}

static struct mrp_app *stream_app(bool rapid)
{
    struct mrp_app *prototype = msrp_app_create(1, &stream_ctx);
    assert_that(prototype, is_non_null);
    struct mrp_app_ops ops = *prototype->ops;
    msrp_app_destroy(prototype);
    ops.milan_rapid_leave = rapid;
    struct mrp_app *app = mrp_app_create(&ops, 1);
    configure(app);
    /* Creation copies the option along with the callbacks. */
    ops.milan_rapid_leave = !rapid;
    assert_that(app->ops->milan_rapid_leave, is_equal_to(rapid));
    return app;
}

static void register_stream(struct mrp_app *app, uint8_t type)
{
    expected_type = type;
    receive_stream(app, type, MRP_ATTR_EVENT_NEW, false);
    check_state(app, MRP_REG_STATE_IN);
    assert_that(joins, is_equal_to(1));
    assert_that(leaves, is_equal_to(0));
}

static void immediate_leave(struct mrp_app *app, uint8_t type)
{
    register_stream(app, type);
    receive_stream(app, type, MRP_ATTR_EVENT_LV, false);
    /* The indication and transition happen before receive returns, without ticks. */
    assert_that(leaves, is_equal_to(1));
    check_state(app, MRP_REG_STATE_MT);
    receive_stream(app, type, MRP_ATTR_EVENT_LV, false);
    tick(500);
    assert_that(leaves, is_equal_to(1));
    check_state(app, MRP_REG_STATE_MT);
}

Ensure(Milan, talker_leave_in_is_immediate)
{
    for (uint8_t type = MSRP_ATTR_TYPE_TALKER_ADV; type <= MSRP_ATTR_TYPE_TALKER_FAILED; ++type) {
        struct mrp_app *app = stream_app(true);
        immediate_leave(app, type);
        msrp_app_destroy(app);
    }
}

Ensure(Milan, listener_leave_in_is_immediate)
{
    struct mrp_app *app = stream_app(true);
    immediate_leave(app, MSRP_ATTR_TYPE_LISTENER);
    msrp_app_destroy(app);
}

static void finish_deadline(struct mrp_app *app)
{
    check_state(app, MRP_REG_STATE_LV);
    assert_that(leaves, is_equal_to(0));
    tick(299);
    assert_that(leaves, is_equal_to(0));
    check_state(app, MRP_REG_STATE_LV);
    tick(1);
    assert_that(leaves, is_equal_to(1));
    check_state(app, MRP_REG_STATE_MT);
    tick(500);
    assert_that(leaves, is_equal_to(1));
}

Ensure(Milan, leave_in_lv_keeps_the_original_deadline)
{
    for (uint8_t type = MSRP_ATTR_TYPE_TALKER_ADV; type <= MSRP_ATTR_TYPE_LISTENER; ++type) {
        struct mrp_app *app = stream_app(true);
        register_stream(app, type);
        receive_stream(app, type, MRP_ATTR_EVENT_MT, true);
        check_state(app, MRP_REG_STATE_LV);
        tick(200);
        receive_stream(app, type, MRP_ATTR_EVENT_LV, false);
        finish_deadline(app);
        msrp_app_destroy(app);
    }
}

static void delayed_leave(struct mrp_app *app, uint8_t type)
{
    register_stream(app, type);
    receive_stream(app, type, MRP_ATTR_EVENT_LV, false);
    tick(200);
    receive_stream(app, type, MRP_ATTR_EVENT_LV, false);
    finish_deadline(app);
}

Ensure(Milan, disabled_application_option_preserves_ieee_timing)
{
    for (uint8_t type = MSRP_ATTR_TYPE_TALKER_ADV; type <= MSRP_ATTR_TYPE_LISTENER; ++type) {
        struct mrp_app *app = stream_app(false);
        delayed_leave(app, type);
        msrp_app_destroy(app);
    }
}

Ensure(Milan, msrp_constructor_selects_the_build_profile)
{
    for (uint8_t type = MSRP_ATTR_TYPE_TALKER_ADV; type <= MSRP_ATTR_TYPE_LISTENER; ++type) {
        struct mrp_app *app = msrp_app_create(1, &stream_ctx);
        configure(app);
        assert_that(app->ops->milan_rapid_leave, is_equal_to(LWSRP_MILAN != 0));
        if (LWSRP_MILAN) {
            immediate_leave(app, type);
        } else {
            delayed_leave(app, type);
        }
        msrp_app_destroy(app);
    }
}

static void vlan_leave(struct mvrp_ctx *ctx, uint8_t port, uint16_t vid)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(vid, is_equal_to(2));
    ++leaves;
}

Ensure(Milan, mvrp_keeps_ieee_leave_timing)
{
    struct mvrp_ctx ctx = {.on_vlan_deregistered = vlan_leave};
    struct mrp_app *app = mvrp_app_create(1, &ctx);
    uint8_t pdu[] = {0, 1, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0};
    configure(app);
    assert_that(app->ops->milan_rapid_leave, is_false);
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    check_state(app, MRP_REG_STATE_IN);
    pdu[7] = 5 * 36;
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    tick(200);
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    finish_deadline(app);
    mvrp_app_destroy(app);
}

static void service_leave(struct mmrp_ctx *ctx, uint8_t port, uint8_t svc)
{
    (void)ctx;
    assert_that(port, is_equal_to(0));
    assert_that(svc, is_equal_to(1));
    ++leaves;
}

Ensure(Milan, mmrp_keeps_ieee_leave_timing)
{
    struct mmrp_ctx ctx = {.on_svc_deregistered = service_leave};
    struct mrp_app *app = mmrp_app_create(1, &ctx);
    uint8_t pdu[] = {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
    configure(app);
    assert_that(app->ops->milan_rapid_leave, is_false);
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    check_state(app, MRP_REG_STATE_IN);
    pdu[6] = 5 * 36;
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    tick(200);
    assert_that(mrp_rx(app, 0, pdu, sizeof(pdu)), is_equal_to(0));
    finish_deadline(app);
    mmrp_app_destroy(app);
}

Ensure(Milan, local_withdrawal_keeps_the_peer_registered)
{
    struct mrp_app *app = stream_app(true);
    register_stream(app, MSRP_ATTR_TYPE_LISTENER);
    struct msrp_stream_id sid;
    memcpy(sid.bytes, stream_id, 8);
    assert_that(msrp_declare_listener(app, 0, &sid, MSRP_LISTENER_DECL_READY), is_equal_to(0));
    assert_that(msrp_withdraw_listener(app, 0, &sid), is_equal_to(0));
    tick(500);
    assert_that(leaves, is_equal_to(0));
    check_state(app, MRP_REG_STATE_IN);
    msrp_app_destroy(app);
}

TestSuite *milan_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, Milan, talker_leave_in_is_immediate);
    add_test_with_context(s, Milan, listener_leave_in_is_immediate);
    add_test_with_context(s, Milan, leave_in_lv_keeps_the_original_deadline);
    add_test_with_context(s, Milan, disabled_application_option_preserves_ieee_timing);
    add_test_with_context(s, Milan, msrp_constructor_selects_the_build_profile);
    add_test_with_context(s, Milan, mvrp_keeps_ieee_leave_timing);
    add_test_with_context(s, Milan, mmrp_keeps_ieee_leave_timing);
    add_test_with_context(s, Milan, local_withdrawal_keeps_the_peer_registered);
    return s;
}
