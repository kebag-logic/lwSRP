/* SPDX-License-Identifier: Apache-2.0 */
/*
 * One random life of the timer module, printed as a trace: registrations,
 * arms, disarms, removals and ticks, and every expiry with the tick it fired
 * in. Callbacks arm, disarm and register other timers, and themselves, as
 * lwSRP's own callbacks do, so a tick's order and its arm-during-tick rule
 * show in the trace. tests/check_differential.py builds this file against a
 * base revision's src/ports/timer.c and against the checkout's, and requires
 * the two traces to be byte-identical for every seed.
 *
 * usage: timer_trace <seed> <steps>
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ports/timer.h"

#define TIMERS 48u

static struct shlan_timer timers[TIMERS];
static bool registered[TIMERS];
static uint32_t rng;
static uint32_t now;
static unsigned long fired;
static bool in_tick;

static uint32_t draw(uint32_t n)
{
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng % n;
}

/* Arm lengths: often one or a few centiseconds, some near the wheel's
 * turns, some far. */
static uint32_t length(void)
{
    const uint32_t kind = draw(20);
    if (kind == 0u) {
        return 0u;
    }
    if (kind < 5u) {
        return 1u;
    }
    if (kind < 10u) {
        return 2u + draw(4);
    }
    if (kind < 14u) {
        return 6u + draw(66);
    }
    if (kind < 16u) {
        return 60u + draw(12);
    }
    if (kind < 18u) {
        return 120u + draw(16);
    }
    if (kind < 19u) {
        return 250u + draw(20);
    }
    return 1000u + draw(4000);
}

static void expired(void *arg);

static void register_timer(unsigned n)
{
    shlan_timer_init(&timers[n], expired, &timers[n]);
    registered[n] = true;
}

/* One action on another timer, or on t itself, as a callback takes it. */
static void act(unsigned self)
{
    const unsigned n = draw(4) == 0u ? self : draw(TIMERS);
    const uint32_t what = draw(10);
    if (what < 6u) {
        const uint32_t cs = length();
        printf("  arm %u %u\n", n, cs);
        shlan_timer_arm(&timers[n], cs);
    } else if (what < 8u) {
        printf("  disarm %u\n", n);
        shlan_timer_disarm(&timers[n]);
    } else if (!registered[n]) {
        printf("  init %u\n", n);
        register_timer(n);
    }
}

static void expired(void *arg)
{
    const unsigned n = (unsigned)((struct shlan_timer *)arg - timers);
    ++fired;
    printf("F %u %u%s\n", now, n, in_tick ? "" : " outside a tick");
    for (uint32_t k = draw(4); k != 0u; --k) {
        act(n);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: timer_trace <seed> <steps>\n");
        return 2;
    }
    rng = (uint32_t)strtoul(argv[1], NULL, 0) * 2654435761u + 1u;
    const unsigned long steps = strtoul(argv[2], NULL, 0);
    for (unsigned n = 0; n < TIMERS; ++n) {
        if (draw(2)) {
            register_timer(n);
        }
    }
    for (unsigned long step = 0; step < steps; ++step) {
        const uint32_t what = draw(32);
        const unsigned n = draw(TIMERS);
        if (what < 12u) {
            const uint32_t cs = length();
            printf("arm %u %u\n", n, cs);
            shlan_timer_arm(&timers[n], cs);
        } else if (what < 15u) {
            printf("disarm %u\n", n);
            shlan_timer_disarm(&timers[n]);
        } else if (what < 17u) {
            printf("remove %u\n", n);
            shlan_timer_remove(&timers[n]);
            registered[n] = false;
        } else if (what < 19u) {
            if (!registered[n]) {
                printf("init %u\n", n);
                register_timer(n);
            }
        } else {
            for (uint32_t k = what < 30u ? 1u : 1u + draw(300); k != 0u; --k) {
                ++now;
                in_tick = true;
                shlan_timer_tick();
                in_tick = false;
            }
            printf("ticked to %u\n", now);
        }
    }
    printf("END fired %lu at %u\n", fired, now);
    return 0;
}
