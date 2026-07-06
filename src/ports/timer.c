#include "timer.h"

static struct shlan_timer *g_head;

void shlan_timer_init(struct shlan_timer *t, void (*cb)(void *arg), void *arg)
{
    t->cb   = cb;
    t->arg  = arg;
    t->cs   = 0;
    t->link = g_head;
    g_head  = t;
}

void shlan_timer_arm(struct shlan_timer *t, uint32_t centiseconds)
{
    t->cs = centiseconds;
}

void shlan_timer_disarm(struct shlan_timer *t)
{
    t->cs = 0;
}

void shlan_timer_tick(void)
{
    for (struct shlan_timer *t = g_head; t; t = t->link) {
        if (t->cs == 0) {
            continue;
        }
        if (--t->cs == 0) {
            t->cb(t->arg);
        }
    }
}
