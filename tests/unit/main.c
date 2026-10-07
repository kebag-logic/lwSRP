/* SPDX-License-Identifier: Apache-2.0 */

#include <cgreen/cgreen.h>

TestSuite *mrp_pdu_suite(void);
TestSuite *timer_suite(void);
TestSuite *msrp_values_suite(void);
TestSuite *receive_suite(void);
TestSuite *transmit_suite(void);
TestSuite *integration_suite(void);
TestSuite *milan_suite(void);
TestSuite *boundaries_suite(void);

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
    TestReporter *reporter = create_text_reporter();
    int result = run_test_suite(suite, reporter);
    destroy_test_suite(suite);
    destroy_reporter(reporter);
    return result;
}
