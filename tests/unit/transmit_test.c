/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include <errno.h>
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/timer.h"
Describe(Transmit);
BeforeEach(Transmit) {}
AfterEach(Transmit) {}
static uint8_t frame[1500];
static size_t frame_len;
static unsigned frames, event_value, left;
static int refuse;
static int send_pdu(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx; (void)port;
    if (refuse) {
        return -ENOBUFS;
    }
    memcpy(frame,pdu,len); frame_len = len; ++frames;
    return 0;
}
static void decoded(void *ctx, uint8_t type, enum mrp_attr_event ev, const void *value)
{
    (void)ctx; (void)type; (void)value; event_value = ev;
}
static void leave_ind(struct msrp_ctx *ctx, uint8_t port, uint8_t type, const void *value)
{
    (void)ctx; (void)port; (void)type; (void)value; ++left;
}
static void tick(unsigned count)
{
    while (count--) {
        shlan_timer_tick();
    }
}
Ensure(Transmit, fresh_ladder_and_refusal_are_transactional)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    assert_that(mrp_port_configure(a,0,20,500,1000,1,true),is_equal_to(0));
    struct msrp_talker_adv talker = {0};
    talker.stream_id.bytes[7] = 1; talker.max_frame_size = 224;
    assert_that(msrp_declare_talker(a,0,&talker,true),is_equal_to(0));
    assert_that(mrp_attr_registered_ports(a,1,&talker),is_equal_to(0));
    uint8_t buffer[1500];
    frames = 0; refuse = 1;
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_less_than(0));
    assert_that(frames,is_equal_to(0));
    refuse = 0;
    const unsigned expected[3] = {0,0,3};
    for (unsigned k = 0; k < 3; ++k) {
        assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
        event_value = 99;
        assert_that(mrpdu_parse(frame,frame_len,a->ops,decoded,0,0),is_equal_to(0));
        assert_that(event_value,is_equal_to(expected[k]));
        tick(19);
        assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(0));
        tick(1);
    }
    assert_that(frames,is_equal_to(3));
    msrp_app_destroy(a);
}
Ensure(Transmit, leaveall_then_withdrawal_retains_until_leave_expiry)
{
    struct msrp_ctx ctx = {.on_leave = leave_ind};
    struct mrp_app *a = msrp_app_create(1,&ctx);
    assert_that(mrp_port_configure(a,0,20,500,1000,1,true),is_equal_to(0));
    uint8_t pdu[] = {0,3,8,0,14,0,1,1,2,3,4,5,6,7,8,0,128,0,0,0,0};
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    pdu[5] = 0x20; pdu[15] = 4 * 36;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    tick(200); pdu[5] = 0; pdu[15] = 5 * 36; left = 0;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    tick(299); assert_that(left,is_equal_to(0));
    tick(1); assert_that(left,is_equal_to(1));
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    tick(501); assert_that(left,is_equal_to(1));
    msrp_app_destroy(a);
}
Ensure(Transmit, refused_pdu_survives_timers_without_aging_unsent_leaveall)
{
    struct msrp_ctx ctx = {.on_leave = leave_ind};
    struct mrp_app *a = msrp_app_create(1,&ctx);
    assert_that(mrp_port_configure(a,0,20,500,1000,1,true),is_equal_to(0));
    uint8_t rx[] = {0,3,8,0,14,0,1,1,2,3,4,5,6,7,8,0,128,0,0,0,0};
    assert_that(mrp_rx(a,0,rx,sizeof(rx)),is_equal_to(0));
    struct msrp_talker_adv talker = {0};
    assert_that(msrp_declare_talker(a,0,&talker,true),is_equal_to(0));
    uint8_t buffer[1500], saved[1500];
    memset(buffer,0,sizeof(buffer)); refuse = 1; left = 0;
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_less_than(0));
    memcpy(saved,buffer,sizeof(saved));
    assert_that(mrp_rx(a,0,rx,sizeof(rx)),is_less_than(0));
    assert_that(msrp_declare_talker(a,0,&talker,false),is_less_than(0));
    assert_that(msrp_withdraw_talker(a,0,&talker.stream_id),is_less_than(0));
    tick(1600);
    assert_that(left,is_equal_to(0));
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_less_than(0));
    assert_that(memcmp(buffer,saved,sizeof(buffer)),is_equal_to(0));
    refuse = 0;
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    assert_that(memcmp(frame,saved,frame_len),is_equal_to(0));
    tick(20);
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    tick(499); assert_that(left,is_equal_to(0));
    tick(1); assert_that(left,is_equal_to(1));
    msrp_app_destroy(a);
}
Ensure(Transmit, receive_redeclare_requests_transmission_without_periodic_wait)
{
    struct mvrp_ctx ctx = {0};
    struct mrp_app *a = mvrp_app_create(1,&ctx);
    assert_that(mvrp_declare(a,0,2),is_equal_to(0));
    uint8_t buffer[1500]; refuse=0;
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    tick(20);
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    tick(20);
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(0));
    uint8_t pdu[] = {0,1,2,0,1,0,2,108,0,0,0,0};
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    tick(20); pdu[3]=0x20; pdu[7]=144;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
    mvrp_app_destroy(a);
}
static unsigned seen[10];
static void segmented(void *ctx, uint8_t type, enum mrp_attr_event ev, const void *value)
{
    (void)ctx;
    const struct msrp_talker_adv *talker=value;
    assert_that(type,is_equal_to(1));
    unsigned n=talker->stream_id.bytes[7];
    assert_that(n,is_less_than(10));
    if (n<10 && ev==MRP_ATTR_EVENT_NEW) {
        ++seen[n];
    }
}
Ensure(Transmit, a_full_pdu_retries_omitted_attributes_before_repeats)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1,&ctx);
    for (unsigned n=0;n<10;++n) {
        struct msrp_talker_adv t={0}; t.stream_id.bytes[7]=(uint8_t)n;
        assert_that(msrp_declare_talker(a,0,&t,true),is_equal_to(0));
        seen[n]=0;
    }
    uint8_t buffer[80]; refuse=0;
    for (unsigned n=0;n<5;++n) {
        assert_that(mrp_transmit(a,0,buffer,sizeof(buffer),send_pdu,0),is_equal_to(1));
        assert_that(mrpdu_parse(frame,frame_len,a->ops,segmented,0,0),is_equal_to(0));
        tick(20);
    }
    for (unsigned n=0;n<10;++n) {
        assert_that(seen[n],is_equal_to(1));
    }
    msrp_app_destroy(a);
}
TestSuite *transmit_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, Transmit, fresh_ladder_and_refusal_are_transactional);
    add_test_with_context(s, Transmit, leaveall_then_withdrawal_retains_until_leave_expiry);
    add_test_with_context(s, Transmit, refused_pdu_survives_timers_without_aging_unsent_leaveall);
    add_test_with_context(s, Transmit, receive_redeclare_requests_transmission_without_periodic_wait);
    add_test_with_context(s, Transmit, a_full_pdu_retries_omitted_attributes_before_repeats);
    return s;
}
