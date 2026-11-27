/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHLAN_PORTS_TIMER_H
#define SHLAN_PORTS_TIMER_H

/*
 * Centisecond callback timer module for lwSRP.
 *
 * Each timer is a struct shlan_timer that holds its own callback and
 * argument.  Timers register with the module once via shlan_timer_init();
 * after that, the platform drives them by calling shlan_timer_tick() once
 * per centisecond.
 *
 * Timers that expire in the same tick fire latest registration first. A
 * timer armed by a callback during a tick counts that tick too when it
 * registered before the timer whose callback runs, so a one-centisecond arm
 * of such a timer fires in the same tick. With LWSRP_TIMER_SLOTS a tick
 * visits only the timers that expire in it: each armed timer waits in the
 * wheel slot of the tick it expires in.
 *
 * To port to an OS timer service: replace timer.c with an implementation
 * that maps shlan_timer_arm/disarm to OS one-shot timers.
 * shlan_timer_tick() becomes a no-op in that case because callbacks are
 * fired by the OS instead.
 */

#include <stdint.h>

/*
 * Wheel slots, a power of two, or 0 for the list walk. With 0 every tick
 * walks every registered timer, counting each armed one down, in four words
 * a timer; with slots a tick visits only its own slot's timers, in eight.
 * A timer due further ahead waits whole turns of the wheel in its slot; the
 * tick that reaches the slot skips it. Both fire the same callbacks in the
 * same ticks and order. Build every translation unit with the same value.
 * Reason: a tick's work does not grow with the registered timers.
 * Requirements: the MRP timers and their values (IEEE 802.1Q-2018, clauses
 * 10.7.4 and 10.7.11). Issues: kebag-logic/milan-fpga#872 and #977, part of
 * #665.
 */
#ifndef LWSRP_TIMER_SLOTS
#define LWSRP_TIMER_SLOTS 0u
#endif

struct shlan_timer {
    void (*cb)(void *arg); /* callback invoked on expiry          */
    void  *arg;             /* opaque argument passed back to cb  */

    /* Module-internal fields — do not access outside timer.c */
#if LWSRP_TIMER_SLOTS == 0
    uint32_t            cs;
    struct shlan_timer *link;
#else
    uint32_t             cs;    /* the tick it expires in, while armed  */
    struct shlan_timer  *link;  /* next timer in its slot, while armed  */
    struct shlan_timer **at;    /* the link that holds it; NULL: idle   */
    uint64_t             order; /* registration number; 0: unregistered */
#endif
};

/*
 * shlan_timer_init — bind cb/arg and register the timer in the module.
 * Must be called exactly once per timer instance before any other call.
 */
void shlan_timer_init(struct shlan_timer *t, void (*cb)(void *arg), void *arg);

/*
 * shlan_timer_arm — start or restart the timer.
 * The callback fires after centiseconds centiseconds.
 * Zero disarms it. A timer that is not registered never fires.
 */
void shlan_timer_arm(struct shlan_timer *t, uint32_t centiseconds);

/* Unlink before releasing storage. No timer may be removed during a tick. */
void shlan_timer_remove(struct shlan_timer *t);

/*
 * shlan_timer_disarm — cancel a running timer.
 * The callback will not fire until the timer is rearmed.
 */
void shlan_timer_disarm(struct shlan_timer *t);

/*
 * shlan_timer_tick — advance all registered timers by one centisecond.
 * Expired timers have their callback invoked before this returns.
 * Call once per centisecond from the platform tick handler.
 */
void shlan_timer_tick(void);

#endif /* SHLAN_PORTS_TIMER_H */
