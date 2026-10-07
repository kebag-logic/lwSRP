/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>

TestSuite *mrp_pdu_suite(void);

int main(void)
{
    TestSuite *suite = mrp_pdu_suite();
    return run_test_suite(suite, create_text_reporter());
}
