/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/msrp.h"
Describe(MsrpValues);
BeforeEach(MsrpValues) {}
AfterEach(MsrpValues) {}
Ensure(MsrpValues, domain_and_vector_offsets_match_wire_fields)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    assert_that(a, is_non_null);
    const uint8_t da[6] = {1,128,194,0,0,14};
    assert_that(memcmp(a->ops->group_addr, da, 6), is_equal_to(0));
    const uint8_t domain_wire[4] = {5,2,0,2};
    struct msrp_domain domain;
    assert_that(a->ops->decode_attr(4, 1, domain_wire, 4, &domain), is_equal_to(4));
    assert_that(domain.class_id, is_equal_to(6));
    assert_that(domain.priority, is_equal_to(3));
    assert_that(domain.vid, is_equal_to(2));
    uint8_t out[34];
    assert_that(a->ops->encode_attr(4, &domain, out, sizeof(out)), is_equal_to(4));
    assert_that(out[0], is_equal_to(6));
    assert_that(out[1], is_equal_to(3));
    assert_that(out[3], is_equal_to(2));
    uint8_t wire[34] = {0};
    wire[5] = 7; wire[6] = 0x12; wire[7] = 0xff;
    wire[12] = 0x34; wire[13] = 0xff; wire[33] = 9;
    struct msrp_talker_failed failed;
    assert_that(a->ops->decode_attr(2, 2, wire, 34, &failed), is_equal_to(34));
    assert_that(failed.talker.stream_id.bytes[5], is_equal_to(7));
    assert_that(failed.talker.stream_id.bytes[6], is_equal_to(0x13));
    assert_that(failed.talker.stream_id.bytes[7], is_equal_to(1));
    assert_that(failed.talker.dest_mac[4], is_equal_to(0x35));
    assert_that(failed.talker.dest_mac[5], is_equal_to(1));
    assert_that(failed.failure_info[8], is_equal_to(9));
    uint8_t listener[9] = {0};
    assert_that(a->ops->decode_attr(3, 2, wire, 8, listener), is_equal_to(8));
    assert_that(listener[6], is_equal_to(0x13));
    assert_that(listener[7], is_equal_to(1));
    assert_that(a->ops->decode_attr(4, 6, domain_wire, 4, &domain), is_less_than(0));
    msrp_app_destroy(a);
}
Ensure(MsrpValues, domain_callback_preserves_existing_member_order)
{
    assert_that(offsetof(struct msrp_ctx,on_talker_advertise),is_equal_to(0));
    assert_that(offsetof(struct msrp_ctx,on_domain),is_greater_than(offsetof(struct msrp_ctx,on_leave)));
}
TestSuite *msrp_values_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, MsrpValues, domain_and_vector_offsets_match_wire_fields);
    add_test_with_context(s, MsrpValues, domain_callback_preserves_existing_member_order);
    return s;
}
