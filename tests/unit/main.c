/* SPDX-License-Identifier: Apache-2.0 */

#include <cgreen/cgreen.h>

TestSuite *mrp_pdu_suite(void);

int main(void)
{
    TestSuite *suite = mrp_pdu_suite();
    TestReporter *reporter = create_text_reporter();
    int result = run_test_suite(suite, reporter);
    destroy_test_suite(suite);
    destroy_reporter(reporter);
    return result;
}
