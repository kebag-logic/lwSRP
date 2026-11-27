/* SPDX-License-Identifier: Apache-2.0 */

#include <cgreen/cgreen.h>
#include "shish_lan/mrp.h"

TestSuite *mrp_pdu_suite(void);
TestSuite *timer_suite(void);
TestSuite *msrp_values_suite(void);
TestSuite *receive_suite(void);
TestSuite *transmit_suite(void);
TestSuite *integration_suite(void);
TestSuite *milan_suite(void);
TestSuite *boundaries_suite(void);
TestSuite *grouping_suite(void);
TestSuite *own_leaveall_suite(void);
TestSuite *end_station_suite(void);
#if LWSRP_ATTR_KEY
TestSuite *key_suite(void);
#endif

int main(void)
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, mrp_pdu_suite());
    add_suite(suite, timer_suite());
    add_suite(suite, msrp_values_suite());
    add_suite(suite, receive_suite());
    add_suite(suite, transmit_suite());
    add_suite(suite, integration_suite());
    add_suite(suite, milan_suite());
    add_suite(suite, boundaries_suite());
    add_suite(suite, grouping_suite());
    add_suite(suite, own_leaveall_suite());
    add_suite(suite, end_station_suite());
#if LWSRP_ATTR_KEY
    add_suite(suite, key_suite());
#endif
    TestReporter *reporter = create_text_reporter();
    int result = run_test_suite(suite, reporter);
    destroy_test_suite(suite);
    destroy_reporter(reporter);
    return result;
}
