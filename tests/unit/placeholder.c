/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>

TestSuite *mrp_pdu_suite(void);
TestSuite *timer_suite(void);

int main(void)
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, mrp_pdu_suite());
    add_suite(suite, timer_suite());
    return run_test_suite(suite, create_text_reporter());
}
