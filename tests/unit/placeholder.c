#include <cgreen/cgreen.h>

/* Unit tests for core/ internals go here.
 * BDD scenarios live in tests/features/ and are run with behave. */

int main(void)
{
    TestSuite *suite = create_test_suite();
    return run_test_suite(suite, create_text_reporter());
}
