#ifndef SHISH_LAN_SWITCH_CTRL_H
#define SHISH_LAN_SWITCH_CTRL_H

/*
 * Queue-based switch register read/write interface.
 *
 * Callers describe register accesses as struct shlan_ctrl_xfer items and
 * submit them to a struct shlan_ctrl_queue.  The queue is a lock-free
 * MPSC (Multiple-Producer, Single-Consumer) list: any number of callers —
 * including interrupt service routines — may call shlan_ctrl_enqueue()
 * concurrently without disabling interrupts.  A single driver task drains
 * the queue by calling shlan_ctrl_dispatch().
 *
 *
 * Atomic chains
 * -------------
 * Setting linked = true on a transfer binds it atomically to the next
 * transfer in the queue.  The dispatcher asserts the bus (via
 * begin_atomic) before the first item in the chain and releases it (via
 * end_atomic) after the last.  The final item in a chain must have
 * linked = false.
 *
 * The producer MUST enqueue all items in a chain in execution order and
 * in rapid succession.  The dispatcher spin-waits briefly if a linked
 * successor is not yet visible; a linked item with no following item
 * will hang the dispatcher permanently.
 *
 *
 * Completion callback constraints
 * --------------------------------
 *  - Invoked from the dispatcher context (single consumer).
 *  - Must not call shlan_ctrl_dequeue() or shlan_ctrl_dispatch().
 *  - Must not re-enqueue the same descriptor from within the callback;
 *    the queue holds internal state on xfer->q_next until the next call
 *    to shlan_ctrl_dequeue() returns a different item.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>

/* ------------------------------------------------------------------ */
/* Transfer descriptor                                                  */
/* ------------------------------------------------------------------ */

enum shlan_ctrl_op {
    SHLAN_CTRL_READ  = 0,   /* register → xfer->data on completion   */
    SHLAN_CTRL_WRITE = 1,   /* xfer->data → register                 */
};

struct shlan_ctrl_xfer {
    enum shlan_ctrl_op  op;
    uint32_t            reg;     /* register address                  */
    uint32_t            data;    /* write value / read result         */
    bool                linked;  /* true → held-bus chain with next   */

    /*
     * Optional completion callback.
     * err == 0 on success, negative errno on failure.
     */
    void (*done)(struct shlan_ctrl_xfer *xfer, int err);

    /*
     * Queue-internal linkage.
     * Must not be read or written by the caller after enqueue.
     */
    _Atomic(struct shlan_ctrl_xfer *) q_next;
};

/*
 * Initialise a descriptor before its first enqueue.
 * May be called again to reconfigure after dequeue has released it.
 */
static inline void
shlan_ctrl_xfer_set(struct shlan_ctrl_xfer *x,
                    enum shlan_ctrl_op op, uint32_t reg, uint32_t data,
                    bool linked,
                    void (*done)(struct shlan_ctrl_xfer *, int))
{
    x->op     = op;
    x->reg    = reg;
    x->data   = data;
    x->linked = linked;
    x->done   = done;
}

/* ------------------------------------------------------------------ */
/* Lock-free MPSC queue                                                 */
/* ------------------------------------------------------------------ */

/*
 * Algorithm: Dmitry Vyukov's intrusive MPSC node-based queue.
 *
 * q_stub is an embedded sentinel; q_head always points to the sentinel
 * (the stub initially, then each previously dequeued xfer in turn).
 * The first pending transfer is always q_head->q_next.
 *
 * Producers atomically swing q_tail with an exchange; the consumer
 * exclusively reads and writes q_head.  No spinlock or interrupt
 * disable is required for enqueue.
 */
struct shlan_ctrl_queue {
    _Atomic(struct shlan_ctrl_xfer *) q_tail;  /* producers update here   */
    struct shlan_ctrl_xfer           *q_head;  /* consumer reads from here */
    struct shlan_ctrl_xfer            q_stub;  /* embedded sentinel node  */
};

/*
 * shlan_ctrl_queue_init — initialise a queue before first use.
 * Must be called exactly once from a single context.
 */
void shlan_ctrl_queue_init(struct shlan_ctrl_queue *q);

/*
 * shlan_ctrl_enqueue — append a transfer to the tail.
 *
 * Re-entrant: safe to call simultaneously from any number of contexts
 * including ISRs, without disabling interrupts.
 *
 * The caller must not access xfer->q_next after this call.
 */
void shlan_ctrl_enqueue(struct shlan_ctrl_queue *q,
                        struct shlan_ctrl_xfer  *xfer);

/*
 * shlan_ctrl_dequeue — remove and return the head transfer.
 *
 * Must be called from a single consumer context only.
 *
 * Returns NULL when the queue is empty, or transiently while a
 * concurrent enqueue is in mid-flight (between the tail exchange and
 * the next-pointer store).  The caller may retry immediately.
 *
 * The returned descriptor's q_next field remains in use by the queue
 * as the new sentinel's link.  Do not write q_next on the returned
 * descriptor until shlan_ctrl_dequeue() has been called again and
 * returned a different (non-NULL) descriptor.
 */
struct shlan_ctrl_xfer *shlan_ctrl_dequeue(struct shlan_ctrl_queue *q);

/* ------------------------------------------------------------------ */
/* Hardware adapter operations                                          */
/* ------------------------------------------------------------------ */

/*
 * Adapter-supplied callbacks used by the dispatcher.
 *
 * begin_atomic / end_atomic bracket a linked chain: the bus is held
 * between them (chip-select asserted for SPI, repeated START for I²C,
 * etc.).  May be no-ops if the hardware does not require it.
 *
 * read and write return 0 on success, negative errno on failure.
 */
struct shlan_ctrl_ops {
    int  (*read)        (void *ctx, uint32_t reg, uint32_t *data);
    int  (*write)       (void *ctx, uint32_t reg,  uint32_t  data);
    void (*begin_atomic)(void *ctx);
    void (*end_atomic)  (void *ctx);
};

/* ------------------------------------------------------------------ */
/* Dispatcher                                                           */
/* ------------------------------------------------------------------ */

/*
 * shlan_ctrl_dispatch — drain the queue, executing transfers via ops.
 *
 * Must be called from the single consumer context.
 *
 * Processes transfers in FIFO order.  Consecutive transfers whose
 * linked flag is true are executed inside a single atomic section:
 *
 *     ops->begin_atomic()
 *     ops->read/write()  ← first transfer  → done callback
 *     ops->read/write()  ← ...             → done callback
 *     ops->read/write()  ← last transfer   → done callback
 *     ops->end_atomic()
 *
 * Returns when the queue is empty.
 */
void shlan_ctrl_dispatch(struct shlan_ctrl_queue    *q,
                         const struct shlan_ctrl_ops *ops,
                         void                        *ctx);

#endif /* SHISH_LAN_SWITCH_CTRL_H */
