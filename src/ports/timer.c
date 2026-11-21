/* SPDX-License-Identifier: Apache-2.0 */
#include <stdbool.h>
#include <stddef.h>

#include "timer.h"

_Static_assert((LWSRP_TIMER_SLOTS & (LWSRP_TIMER_SLOTS - 1u)) == 0u && LWSRP_TIMER_SLOTS != 0u,
               "LWSRP_TIMER_SLOTS must be a power of two");

/* The tick count the module starts at. Its arithmetic is modulo 2^32, so
 * a check may start it just short of the wrap; behaviour does not depend
 * on it. */
#ifndef LWSRP_TIMER_EPOCH
#define LWSRP_TIMER_EPOCH 0u
#endif

/*
 * The timers once lived in one list, latest registration first, and each
 * tick walked all of it, counting every armed timer down and firing each
 * that reached zero. This module keeps that walk's behaviour without the
 * walk. A timer armed for n centiseconds outside a tick expires in the
 * n-th tick from now; the timers of one tick fire latest registration
 * first; and a timer armed by a callback during a tick counts that tick
 * too when the walk had not reached it yet, that is, when it registered
 * before the timer whose callback runs.
 */
static struct shlan_timer *g_slot[LWSRP_TIMER_SLOTS];
static struct shlan_timer *g_due;      /* this tick's timers yet to fire, latest registration first */
static uint32_t            g_now = LWSRP_TIMER_EPOCH; /* the ticks begun */
static uint64_t            g_order;    /* the registrations made */
static uint64_t            g_cursor;   /* the registration whose callback runs; 0 outside a tick */

static void link_at(struct shlan_timer **at, struct shlan_timer *t)
{
    t->link = *at;
    if (t->link) {
        t->link->at = &t->link;
    }
    *at = t;
    t->at = at;
}

static void unlink_timer(struct shlan_timer *t)
{
    *t->at = t->link;
    if (t->link) {
        t->link->at = t->at;
    }
    t->at = NULL;
}

/* Place t among this tick's timers yet to fire, by its registration. */
static void link_due(struct shlan_timer *t)
{
    struct shlan_timer **at = &g_due;
    while (*at && (*at)->order > t->order) {
        at = &(*at)->link;
    }
    link_at(at, t);
}

/* Two lists, each latest registration first, as one; only links are kept. */
static struct shlan_timer *merge(struct shlan_timer *a, struct shlan_timer *b)
{
    struct shlan_timer *head = NULL, **tail = &head;
    while (a && b) {
        struct shlan_timer **from = a->order > b->order ? &a : &b;
        *tail = *from;
        tail = &(*from)->link;
        *from = (*from)->link;
    }
    *tail = a ? a : b;
    return head;
}

/*
 * A list, latest registration first, by its runs merged pairwise; a slot
 * holds its timers in arming order, newest first, so the timers of one
 * burst of arms form one run. Only links are kept.
 */
static struct shlan_timer *sort_due(struct shlan_timer *list)
{
    struct shlan_timer *pending[8] = {NULL};
    while (list) {
        struct shlan_timer *run = list;
        list = list->link;
        run->link = NULL;
        if (list && list->order > run->order) {
            /* Rising registrations: reverse them as they come. */
            while (list && list->order > run->order) {
                struct shlan_timer *next = list->link;
                list->link = run;
                run = list;
                list = next;
            }
        } else {
            struct shlan_timer *last = run;
            while (list && list->order < last->order) {
                last->link = list;
                last = list;
                list = list->link;
                last->link = NULL;
            }
        }
        unsigned k = 0;
        while (k + 1u < sizeof(pending) / sizeof(pending[0]) && pending[k]) {
            run = merge(pending[k], run);
            pending[k++] = NULL;
        }
        pending[k] = pending[k] ? merge(pending[k], run) : run;
    }
    struct shlan_timer *out = NULL;
    for (unsigned k = 0; k < sizeof(pending) / sizeof(pending[0]); ++k) {
        if (pending[k]) {
            out = out ? merge(pending[k], out) : pending[k];
        }
    }
    return out;
}

void shlan_timer_init(struct shlan_timer *t, void (*cb)(void *arg), void *arg)
{
    t->cb    = cb;
    t->arg   = arg;
    t->cs    = 0;
    t->link  = NULL;
    t->at    = NULL;
    t->order = ++g_order;
}

void shlan_timer_arm(struct shlan_timer *t, uint32_t centiseconds)
{
    if (t->at) {
        unlink_timer(t);
    }
    if (centiseconds == 0u || t->order == 0u) {
        return;
    }
    /* The walk in progress had yet to reach a timer registered before the
     * one whose callback runs: it counts this tick too. */
    const bool ahead = t->order < g_cursor;
    t->cs = g_now + centiseconds - (ahead ? 1u : 0u);
    if (ahead && t->cs == g_now) {
        link_due(t);
    } else {
        link_at(&g_slot[t->cs % LWSRP_TIMER_SLOTS], t);
    }
}

void shlan_timer_disarm(struct shlan_timer *t)
{
    if (t->at) {
        unlink_timer(t);
    }
}

void shlan_timer_tick(void)
{
    ++g_now;
    struct shlan_timer **at = &g_slot[g_now % LWSRP_TIMER_SLOTS];
    struct shlan_timer *taken = NULL;
    while (*at) {
        struct shlan_timer *t = *at;
        if (t->cs != g_now) {
            at = &t->link;
            continue;
        }
        unlink_timer(t);
        t->link = taken;
        taken = t;
    }
    g_due = sort_due(taken);
    for (struct shlan_timer **due = &g_due; *due; due = &(*due)->link) {
        (*due)->at = due;
    }
    while (g_due) {
        struct shlan_timer *t = g_due;
        unlink_timer(t);
        g_cursor = t->order;
        t->cb(t->arg);
    }
    g_cursor = 0;
}

void shlan_timer_remove(struct shlan_timer *t)
{
    if (t->order == 0u) {
        return;
    }
    if (t->at) {
        unlink_timer(t);
    }
    t->cs = 0;
    t->link = NULL;
    t->order = 0;
}
