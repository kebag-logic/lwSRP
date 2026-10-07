/* SPDX-License-Identifier: Apache-2.0 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "ports/timer.h"
#include "shish_lan/mvrp.h"

Describe(TimerLifetime);
BeforeEach(TimerLifetime) {}
AfterEach(TimerLifetime) {}
static void expired(void *arg)
{
    ++*(unsigned *)arg;
}

Ensure(TimerLifetime, remove_head_middle_tail_and_reinitialize)
{
    unsigned fired = 0;
    struct shlan_timer a, b, c;
    shlan_timer_init(&a, expired, &fired);
    shlan_timer_init(&b, expired, &fired);
    shlan_timer_init(&c, expired, &fired);
    shlan_timer_arm(&a, 1);
    shlan_timer_arm(&b, 1);
    shlan_timer_arm(&c, 1);
    shlan_timer_remove(&b);
    shlan_timer_remove(&a);
    shlan_timer_remove(&c);
    shlan_timer_remove(&c);
    shlan_timer_tick();
    assert_that(fired, is_equal_to(0));
    shlan_timer_init(&a, expired, &fired);
    shlan_timer_arm(&a, 1);
    shlan_timer_tick();
    assert_that(fired, is_equal_to(1));
    shlan_timer_remove(&a);
}

Ensure(TimerLifetime, destroy_with_live_attribute_timers_then_tick)
{
    struct mvrp_ctx ctx = {0};
    for (unsigned n = 0; n < 4; ++n) {
        struct mrp_app *app = mvrp_app_create(2, &ctx);
        assert_that(app, is_non_null);
        assert_that(mvrp_declare(app, 0, 2), is_equal_to(0));
        assert_that(mvrp_declare(app, 1, 3), is_equal_to(0));
        mvrp_app_destroy(app);
        for (unsigned tick = 0; tick < 1100; ++tick) {
            shlan_timer_tick();
        }
    }
}

TestSuite *timer_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, TimerLifetime, remove_head_middle_tail_and_reinitialize);
    add_test_with_context(s, TimerLifetime, destroy_with_live_attribute_timers_then_tick);
    return s;
}
