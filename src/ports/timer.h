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
 * To port to an OS timer service: replace timer.c with an implementation
 * that maps shlan_timer_arm/disarm to OS one-shot timers.
 * shlan_timer_tick() becomes a no-op in that case because callbacks are
 * fired by the OS instead.
 */

#include <stdint.h>

struct shlan_timer {
    void (*cb)(void *arg); /* callback invoked on expiry          */
    void  *arg;             /* opaque argument passed back to cb  */

    /* Module-internal fields — do not access outside timer.c */
    uint32_t            cs;
    struct shlan_timer *link;
};

/*
 * shlan_timer_init — bind cb/arg and register the timer in the module.
 * Must be called exactly once per timer instance before any other call.
 */
void shlan_timer_init(struct shlan_timer *t, void (*cb)(void *arg), void *arg);

/*
 * shlan_timer_arm — start or restart the timer.
 * The callback fires after centiseconds centiseconds.
 */
void shlan_timer_arm(struct shlan_timer *t, uint32_t centiseconds);

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
