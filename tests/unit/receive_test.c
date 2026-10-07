/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/msrp.h"
#include "shish_lan/mrp_pdu.h"
Describe(Receive);
BeforeEach(Receive) {}
AfterEach(Receive) {}
static unsigned attributes, leavealls;
static void attr(void *ctx, uint8_t type, enum mrp_attr_event ev, const void *value)
{
    (void)ctx; (void)type; (void)ev; (void)value; ++attributes;
}
static void la(void *ctx, uint8_t type)
{
    (void)ctx; (void)type; ++leavealls;
}
Ensure(Receive, truncation_respects_complete_vectors_and_pdu_end)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    /* One Listener New/Ready, with LeaveAll and both EndMarks. */
    uint8_t pdu[] = {0,3,8,0,14,0x20,1,1,2,3,4,5,6,7,8,0,128,0,0,0,0};
    for (unsigned n = 0; n < sizeof(pdu); ++n) {
        attributes = leavealls = 0;
        if (n == 17 || n == 19) {
            assert_that(mrpdu_parse(pdu,n,a->ops,attr,la,0), is_equal_to(0));
            assert_that(attributes, is_equal_to(1));
            assert_that(leavealls, is_equal_to(1));
        } else {
            assert_that(mrpdu_parse(pdu,n,a->ops,attr,la,0), is_less_than(0));
            assert_that(attributes + leavealls, is_equal_to(0));
        }
    }
    attributes = leavealls = 0;
    assert_that(mrpdu_parse(pdu,sizeof(pdu),a->ops,attr,la,0), is_equal_to(0));
    assert_that(attributes, is_equal_to(1));
    assert_that(leavealls, is_equal_to(1));
    pdu[16] = 0; attributes = leavealls = 0;
    assert_that(mrpdu_parse(pdu,sizeof(pdu),a->ops,attr,la,0), is_equal_to(0));
    assert_that(attributes, is_equal_to(0));
    assert_that(leavealls, is_equal_to(1));
    pdu[15] = 216;
    assert_that(mrpdu_parse(pdu,sizeof(pdu),a->ops,attr,la,0), is_less_than(0));
    pdu[15] = 0; pdu[4] = 12;
    assert_that(mrpdu_parse(pdu,sizeof(pdu),a->ops,attr,la,0), is_less_than(0));
    msrp_app_destroy(a);
}
static unsigned changes, declaration;
static void listener_changed(struct msrp_ctx *ctx, uint8_t port,
                             const struct msrp_stream_id *sid,
                             enum msrp_listener_decl decl, bool is_new)
{
    (void)ctx; (void)port; (void)sid; (void)is_new;
    ++changes; declaration = decl;
}
Ensure(Receive, changed_registered_listener_notifies_without_duplicate_join)
{
    struct msrp_ctx ctx = {.on_listener = listener_changed};
    struct mrp_app *a = msrp_app_create(1,&ctx);
    uint8_t pdu[] = {0,3,8,0,14,0,1,1,2,3,4,5,6,7,8,36,128,0,0,0,0};
    changes = 0;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(changes,is_equal_to(1));
    assert_that(declaration,is_equal_to(MSRP_LISTENER_DECL_READY));
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(changes,is_equal_to(1));
    pdu[16] = 64;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(changes,is_equal_to(2));
    assert_that(declaration,is_equal_to(MSRP_LISTENER_DECL_ASKING_FAILED));
    pdu[15] = 3 * 36; pdu[16] = 192;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(changes,is_equal_to(3));
    assert_that(declaration,is_equal_to(MSRP_LISTENER_DECL_READY_FAILED));
    msrp_app_destroy(a);
}
static bool interest(void *ctx, uint8_t port, uint8_t type, const void *value)
{
    (void)port; (void)type;
    return ((const uint8_t *)value)[7] == *(const uint8_t *)ctx;
}
Ensure(Receive, uninteresting_values_do_not_allocate_and_empty_state_is_reclaimed)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1,&ctx);
    uint8_t pdu[] = {0,3,8,0,14,0,1,1,2,3,4,5,6,7,8,144,128,0,0,0,0};
    uint8_t wanted=9;
    mrp_set_rx_filter(a,interest,&wanted);
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(mrp_attr_visit(a,0,0,0),is_equal_to(0));
    wanted=8;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(mrp_attr_visit(a,0,0,0),is_equal_to(1));
    assert_that(mrp_reclaim(a,0),is_equal_to(1));
    pdu[15]=0;
    assert_that(mrp_rx(a,0,pdu,sizeof(pdu)),is_equal_to(0));
    assert_that(mrp_reclaim(a,0),is_equal_to(0));
    assert_that(mrp_attr_visit(a,0,0,0),is_equal_to(1));
    msrp_app_destroy(a);
}
TestSuite *receive_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, Receive, truncation_respects_complete_vectors_and_pdu_end);
    add_test_with_context(s, Receive, changed_registered_listener_notifies_without_duplicate_join);
    add_test_with_context(s, Receive, uninteresting_values_do_not_allocate_and_empty_state_is_reclaimed);
    return s;
}
