/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Switch register control — MPSC queue and dispatcher.
 * See include/shish_lan/switch_ctrl.h for interface documentation.
 */

#include <stddef.h>

#include "shish_lan/switch_ctrl.h"

/* ------------------------------------------------------------------ */
/* Queue                                                                */
/* ------------------------------------------------------------------ */

void shlan_ctrl_queue_init(struct shlan_ctrl_queue *q)
{
    atomic_store_explicit(&q->q_stub.q_next, NULL, memory_order_relaxed);
    q->q_head = &q->q_stub;
    atomic_store_explicit(&q->q_tail, &q->q_stub, memory_order_relaxed);
}

/*
 * Enqueue — Dmitry Vyukov MPSC, lock-free:
 *
 *  1. Store NULL into xfer->q_next (no successor yet).
 *  2. Atomically exchange q_tail with xfer.  We now own the link from
 *     prev (the old tail) to xfer exclusively.
 *  3. Publish xfer by storing it into prev->q_next with release
 *     semantics.  The consumer's paired acquire load in dequeue will
 *     then observe all data written to xfer before this call
 *     (op, reg, data, linked, done).
 *
 * Between steps 2 and 3 the queue appears stalled to the consumer:
 * prev->q_next is still NULL.  The consumer handles this by returning
 * NULL and retrying.
 */
void shlan_ctrl_enqueue(struct shlan_ctrl_queue *q,
                        struct shlan_ctrl_xfer  *xfer)
{
    struct shlan_ctrl_xfer *prev;

    atomic_store_explicit(&xfer->q_next, NULL, memory_order_relaxed);

    prev = atomic_exchange_explicit(&q->q_tail, xfer, memory_order_acq_rel);

    atomic_store_explicit(&prev->q_next, xfer, memory_order_release);
}

/*
 * Dequeue — single consumer.
 *
 * q_head is the sentinel: q_stub initially, then each previously
 * returned xfer in turn.  The first pending item is head->q_next.
 *
 * Advancing q_head past the sentinel makes q_next the new sentinel and
 * returns it to the caller, carrying its transfer data intact.
 *
 * Returns NULL when empty, or while a producer is between the tail
 * exchange (step 2) and the next-pointer store (step 3).
 */
struct shlan_ctrl_xfer *shlan_ctrl_dequeue(struct shlan_ctrl_queue *q)
{
    struct shlan_ctrl_xfer *head = q->q_head;
    struct shlan_ctrl_xfer *next =
        atomic_load_explicit(&head->q_next, memory_order_acquire);

    if (!next)
        return NULL;

    q->q_head = next;   /* next becomes the new sentinel */
    return next;        /* next carries the transfer payload */
}

/* ------------------------------------------------------------------ */
/* Dispatcher                                                           */
/* ------------------------------------------------------------------ */

static int run_xfer(struct shlan_ctrl_xfer      *xfer,
                    const struct shlan_ctrl_ops  *ops,
                    void                         *ctx)
{
    if (xfer->op == SHLAN_CTRL_WRITE)
        return ops->write(ctx, xfer->reg, xfer->data);
    else
        return ops->read(ctx, xfer->reg, &xfer->data);
}

/*
 * Process one transfer and, if it opens an atomic chain (linked == true),
 * continue consuming and executing linked successors until one has
 * linked == false, then close the atomic section.
 *
 * Spin-waits for a linked successor that has been announced via
 * exchange but whose next-pointer store has not yet committed.
 */
static void dispatch_one(struct shlan_ctrl_xfer      *first,
                         struct shlan_ctrl_queue     *q,
                         const struct shlan_ctrl_ops *ops,
                         void                        *ctx)
{
    struct shlan_ctrl_xfer *xfer = first;
    bool atomic_open = xfer->linked;

    if (atomic_open && ops->begin_atomic)
        ops->begin_atomic(ctx);

    for (;;) {
        int  err  = run_xfer(xfer, ops, ctx);
        bool last = !xfer->linked;

        if (xfer->done)
            xfer->done(xfer, err);

        if (last)
            break;

        /*
         * This transfer was linked: spin until its successor is visible.
         * A valid caller always enqueues the next item before the dispatcher
         * reaches this point; the wait is expected to be extremely brief.
         */
        struct shlan_ctrl_xfer *next;
        do {
            next = shlan_ctrl_dequeue(q);
        } while (!next);

        xfer = next;
    }

    if (atomic_open && ops->end_atomic)
        ops->end_atomic(ctx);
}

void shlan_ctrl_dispatch(struct shlan_ctrl_queue    *q,
                         const struct shlan_ctrl_ops *ops,
                         void                        *ctx)
{
    struct shlan_ctrl_xfer *xfer;

    while ((xfer = shlan_ctrl_dequeue(q)) != NULL)
        dispatch_one(xfer, q, ops, ctx);
}
