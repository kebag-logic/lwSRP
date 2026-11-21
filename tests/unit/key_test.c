/* SPDX-License-Identifier: Apache-2.0 */
/*
 * The attribute key (mrp.h attr_key) is a lookup prefilter only. Each pair of
 * applications here differs in attr_key alone: one keyed as created, one with
 * NULL. Both take the same random sequence of received PDUs, local
 * declarations, withdrawals, timer ticks and transmissions. Their indications,
 * attribute states and transmitted PDUs must match after every step.
 * StreamIDs and VIDs are drawn so different values often share a key octet.
 */
#include <cgreen/cgreen.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/mrp_pdu.h"
#include "ports/timer.h"
#if LWSRP_ATTR_KEY

Describe(Key);
BeforeEach(Key) {}
AfterEach(Key) {}

struct key_run {
    struct mrp_app *app;
    uint64_t hash;
    unsigned joins;
    unsigned leaves;
    unsigned sent;
};

static struct key_run runs[2];
static uint32_t seed;

static uint32_t draw(uint32_t n)
{
    seed = seed * 1664525u + 1013904223u;
    return (seed >> 8) % n;
}

static void mix(struct key_run *r, const void *bytes, size_t len)
{
    const uint8_t *b = bytes;
    for (size_t k = 0; k < len; ++k) {
        r->hash = (r->hash ^ b[k]) * UINT64_C(0x100000001b3);
    }
}

static struct key_run *run_of(const struct mrp_app *app)
{
    return app == runs[0].app ? &runs[0] : &runs[1];
}

static size_t value_len(const struct mrp_app *app, uint8_t type)
{
    return app->ops->attr_mem_len ? app->ops->attr_mem_len(type) : app->ops->attr_len(type);
}

static void joined(struct mrp_app *app, uint8_t port, uint8_t type, const void *value, bool is_new)
{
    struct key_run *r = run_of(app);
    const uint8_t head[3] = {1u, type, (uint8_t)(port + (is_new ? 2u : 0u))};
    mix(r, head, sizeof(head));
    mix(r, value, value_len(app, type));
    ++r->joins;
}

static void left(struct mrp_app *app, uint8_t port, uint8_t type, const void *value)
{
    struct key_run *r = run_of(app);
    const uint8_t head[3] = {2u, type, port};
    mix(r, head, sizeof(head));
    mix(r, value, value_len(app, type));
    ++r->leaves;
}

static int sent(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    struct key_run *r = ctx;
    const uint8_t head[2] = {3u, port};
    mix(r, head, sizeof(head));
    mix(r, pdu, len);
    ++r->sent;
    return 0;
}

static void visited(void *ctx, const struct mrp_attr_status *st)
{
    struct key_run *r = ctx;
    const uint8_t head[4] = {4u, st->attr_type, (uint8_t)st->appl, (uint8_t)st->reg};
    mix(r, head, sizeof(head));
    mix(r, st->attr_val, r->app->ops->attr_len(st->attr_type));
}

/* A StreamID from one talker: UniqueIDs whose last octet repeats across
 * three high octets, so keys collide between different streams. */
static void stream_id(uint8_t *id)
{
    const uint8_t mac[6] = {0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x10u};
    memcpy(id, mac, sizeof(mac));
    id[6] = (uint8_t)draw(3);
    id[7] = (uint8_t)draw(12);
}

/* One MSRP message with one vector of up to five values (IEEE 802.1Q-2018
 * 35.2.2), its FirstValue drawn from a small set of each field. */
static size_t msrp_message(uint8_t *out)
{
    static const uint8_t types[] = {MSRP_ATTR_TYPE_TALKER_ADV, MSRP_ATTR_TYPE_TALKER_FAILED,
                                    MSRP_ATTR_TYPE_LISTENER, MSRP_ATTR_TYPE_DOMAIN};
    const uint8_t type = types[draw(4)];
    const uint8_t alen = runs[0].app->ops->attr_len(type);
    const unsigned n = type == MSRP_ATTR_TYPE_DOMAIN ? 1u : 1u + draw(5);
    uint8_t *v = out + 6;
    memset(v, 0, alen);
    if (type == MSRP_ATTR_TYPE_DOMAIN) {
        v[0] = 6u; v[1] = 3u; v[2] = (uint8_t)draw(2); v[3] = (uint8_t)(2u + draw(2));
    } else {
        stream_id(v);
    }
    if (type == MSRP_ATTR_TYPE_TALKER_ADV || type == MSRP_ATTR_TYPE_TALKER_FAILED) {
        v[8] = 0x91u; v[9] = 0xe0u; v[10] = 0xf0u; v[13] = (uint8_t)draw(2);
        v[15] = 2u; v[16] = 0u; v[17] = 64u; v[19] = 1u; v[20] = 0x70u;
        v[24] = (uint8_t)(1u + draw(2));
        if (type == MSRP_ATTR_TYPE_TALKER_FAILED) {
            v[32] = (uint8_t)draw(2); v[33] = (uint8_t)(1u + draw(2));
        }
    }
    size_t at = 6u + alen;
    for (unsigned k = 0; k < n; k += 3u) {
        out[at++] = (uint8_t)(draw(6) * 36u + (k + 1u < n ? draw(6) * 6u : 0u) + (k + 2u < n ? draw(6) : 0u));
    }
    if (type == MSRP_ATTR_TYPE_LISTENER) {
        for (unsigned k = 0; k < n; k += 4u) {
            out[at++] = (uint8_t)draw(256);
        }
    }
    out[at++] = 0u; out[at++] = 0u;
    const bool leaveall = draw(16) == 0u;
    out[0] = type; out[1] = alen;
    out[2] = (uint8_t)((at - 4u) >> 8); out[3] = (uint8_t)(at - 4u);
    out[4] = (uint8_t)(((leaveall ? 0x2000u : 0u) | n) >> 8); out[5] = (uint8_t)n;
    return at;
}

static size_t msrp_pdu(uint8_t *pdu)
{
    size_t len = 1u;
    pdu[0] = 0u;
    for (unsigned m = 1u + draw(3); m != 0u; --m) {
        len += msrp_message(pdu + len);
    }
    pdu[len++] = 0u; pdu[len++] = 0u;
    return len;
}

/* One MVRP message (IEEE 802.1Q-2018 11.2.3.1): VIDs whose low octet repeats. */
static size_t mvrp_pdu(uint8_t *pdu)
{
    const unsigned n = 1u + draw(5);
    const unsigned vid = draw(3) * 256u + 1u + draw(10);
    size_t at = 0u;
    pdu[at++] = 0u; pdu[at++] = MVRP_ATTR_TYPE_VID; pdu[at++] = MVRP_ATTR_LEN_VID;
    pdu[at++] = (uint8_t)(((draw(16) == 0u ? 0x2000u : 0u) | n) >> 8); pdu[at++] = (uint8_t)n;
    pdu[at++] = (uint8_t)(vid >> 8); pdu[at++] = (uint8_t)vid;
    for (unsigned k = 0; k < n; k += 3u) {
        pdu[at++] = (uint8_t)(draw(6) * 36u + (k + 1u < n ? draw(6) * 6u : 0u) + (k + 2u < n ? draw(6) : 0u));
    }
    pdu[at++] = 0u; pdu[at++] = 0u; pdu[at++] = 0u; pdu[at++] = 0u;
    return at;
}

/* A local declaration's in-memory value, from the same small sets. */
static uint8_t local_value(bool msrp, uint8_t *type, uint8_t *value)
{
    memset(value, 0, 48);
    if (!msrp) {
        *type = MVRP_ATTR_TYPE_VID;
        const unsigned vid = draw(3) * 256u + 1u + draw(10);
        value[0] = (uint8_t)(vid >> 8); value[1] = (uint8_t)vid;
        return 1u;
    }
    *type = draw(2) == 0u ? MSRP_ATTR_TYPE_TALKER_ADV : MSRP_ATTR_TYPE_LISTENER;
    if (*type == MSRP_ATTR_TYPE_TALKER_ADV) {
        struct msrp_talker_adv t = {0};
        stream_id(t.stream_id.bytes);
        t.vlan_id = 2u; t.max_frame_size = 64u; t.max_interval_frames = 1u;
        t.priority_and_rank = 0x70u;
        memcpy(value, &t, sizeof(t));
    } else {
        stream_id(value);
        value[8] = (uint8_t)(1u + draw(3));
    }
    return 1u;
}

/* The two runs, step by step; each step's effects on both must hash alike. */
static void differential(struct mrp_app *(*create)(void), bool msrp, unsigned steps)
{
    for (unsigned k = 0; k < 2u; ++k) {
        struct mrp_app *prototype = create();
        assert_that(prototype, is_non_null);
        struct mrp_app_ops ops = *prototype->ops;
        ops.join_ind = joined; ops.leave_ind = left; ops.ctx = NULL;
        ops.map_join = NULL; ops.map_leave = NULL;
        if (k == 1u) {
            assert_that(ops.attr_key, is_non_null);
            ops.attr_key = NULL;
        }
        mrp_app_destroy(prototype);
        runs[k] = (struct key_run){mrp_app_create(&ops, 1), UINT64_C(0xcbf29ce484222325), 0, 0, 0};
        assert_that(runs[k].app, is_non_null);
        assert_that(mrp_port_configure(runs[k].app, 0, 20, 60, 1000, 0x872u, true), is_equal_to(0));
    }
    uint8_t pdu[512], buffer[1500], type, value[48];
    for (unsigned step = 0; step < steps; ++step) {
        const uint32_t what = draw(16);
        const uint32_t ticks = what >= 13u ? 1u + draw(40) : 0u;
        size_t len = what < 8u ? (msrp ? msrp_pdu(pdu) : mvrp_pdu(pdu)) : 0u;
        if (what >= 8u && what < 12u) {
            (void)local_value(msrp, &type, value);
        }
        int result[2] = {0, 0};
        for (unsigned k = 0; k < 2u; ++k) {
            struct key_run *r = &runs[k];
            if (what < 8u) {
                result[k] = mrp_rx(r->app, 0, pdu, len);
            } else if (what < 10u) {
                result[k] = mrp_mad_join(r->app, 0, type, value, true);
            } else if (what < 12u) {
                result[k] = mrp_mad_leave(r->app, 0, type, value);
            } else if (what == 12u) {
                result[k] = mrp_transmit(r->app, 0, buffer, sizeof(buffer), sent, r);
            }
            mix(r, &result[k], sizeof(result[k]));
        }
        for (uint32_t t = 0; t < ticks; ++t) {
            shlan_timer_tick();
        }
        if (what >= 13u) {
            for (unsigned k = 0; k < 2u; ++k) {
                result[k] = mrp_transmit(runs[k].app, 0, buffer, sizeof(buffer), sent, &runs[k]);
                mix(&runs[k], &result[k], sizeof(result[k]));
            }
        }
        for (unsigned k = 0; k < 2u; ++k) {
            mix(&runs[k], &step, sizeof(step));
            (void)mrp_attr_visit(runs[k].app, 0, visited, &runs[k]);
        }
        if (runs[0].hash != runs[1].hash) {
            /* The first step whose effects differ, as the failure's actual value. */
            assert_that(step, is_equal_to(steps));
            break;
        }
    }
    assert_that(runs[0].hash == runs[1].hash, is_true);
    assert_that(runs[0].joins, is_equal_to(runs[1].joins));
    assert_that(runs[0].leaves, is_equal_to(runs[1].leaves));
    assert_that(runs[0].sent, is_equal_to(runs[1].sent));
    assert_that(runs[0].joins, is_greater_than(steps / 20u));
    assert_that(runs[0].leaves, is_greater_than(steps / 40u));
    assert_that(runs[0].sent, is_greater_than(steps / 40u));
    for (unsigned k = 0; k < 2u; ++k) {
        mrp_app_destroy(runs[k].app);
        runs[k].app = NULL;
    }
}

static struct msrp_ctx msrp_context;
static struct mvrp_ctx mvrp_context;

static struct mrp_app *msrp_prototype(void)
{
    return msrp_app_create(1, &msrp_context);
}

static struct mrp_app *mvrp_prototype(void)
{
    return mvrp_app_create(1, &mvrp_context);
}

Ensure(Key, msrp_keyed_lookups_match_unkeyed_lookups)
{
    seed = 0x872u;
    differential(msrp_prototype, true, 4000u);
}

Ensure(Key, mvrp_keyed_lookups_match_unkeyed_lookups)
{
    seed = 0x873u;
    differential(mvrp_prototype, false, 4000u);
}

TestSuite *key_suite(void)
{
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Key, msrp_keyed_lookups_match_unkeyed_lookups);
    add_test_with_context(suite, Key, mvrp_keyed_lookups_match_unkeyed_lookups);
    return suite;
}
#else
/* Built without LWSRP_ATTR_KEY, the MAD keeps no key: nothing to compare. */
TestSuite *key_suite(void)
{
    return create_test_suite();
}
#endif
