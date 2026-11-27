/* SPDX-License-Identifier: Apache-2.0 */
/*
 * The end-station switches' observable rules (doc/integrator.md, kebag-logic/milan-fpga#977).
 * Registered in every build; each expectation follows the build's switches.
 *
 * LWSRP_ONE_PORT_MAP: propagation goes only to the MAP context's other ports (IEEE 802.1Q-2018, clause 10.3).
 * At one port the option reserves no target and calls no policy, so a refused reservation no longer refuses the
 * receive: the default build refuses it, the option applies the event. Two or more ports are unchanged.
 *
 * LWSRP_LEAN_TX: the assembler passes over a word of the open AttributeType set with no type left in it. Messages
 * for types spread over the 256 (word boundaries, empty words between, type 255) must all be sent, in type order
 * (10.8.1.2), in every build.
 */
#include <cgreen/cgreen.h>
#include <stdint.h>
#include <string.h>
#include "shish_lan/mrp.h"
#include "shish_lan/mvrp.h"
#include "shish_lan/error.h"
#include "ports/timer.h"
#include "fault_alloc.h"
#include "mrpdu_decoder.h"

#ifndef LWSRP_ONE_PORT_MAP
#define LWSRP_ONE_PORT_MAP 0
#endif

Describe(EndStation);
static unsigned joins, leaves, policy_calls;
BeforeEach(EndStation)
{
    joins = leaves = policy_calls = 0;
    allocation_fail_after(0);
    assert_that(allocation_live(), is_equal_to(0));
}
AfterEach(EndStation)
{
    allocation_fail_after(0);
    assert_that(allocation_live(), is_equal_to(0));
}

static void tick(unsigned n)
{
    while (n--) {
        shlan_timer_tick();
    }
}

/* ---- one-port MAP work ------------------------------------------------ */

static void joined(struct mrp_app *a, uint8_t p, uint8_t t, const void *v, bool n)
{
    (void)a; (void)p; (void)t; (void)v; (void)n; ++joins;
}
static void left(struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v; ++leaves;
}
/* A policy naming no port: what any policy can name at one port (10.3). */
static uint32_t policy(const struct mrp_app *a, uint8_t p, uint8_t t, const void *v)
{
    (void)a; (void)p; (void)t; (void)v; ++policy_calls; return 0;
}

/* The VLAN application with a propagation policy for Join and Leave. */
static struct mrp_app *vlan_with_policy(uint8_t ports)
{
    struct mvrp_ctx vlan = {0};
    struct mrp_app *prototype = mvrp_app_create(1, &vlan);
    struct mrp_app_ops ops = *prototype->ops;
    mrp_app_destroy(prototype);
    ops.join_ind = joined; ops.leave_ind = left; ops.ctx = NULL;
    ops.map_join = policy; ops.map_leave = policy;
    return mrp_app_create(&ops, ports);
}

static enum mrp_reg_state registrar;
static void visit_registrar(void *ctx, const struct mrp_attr_status *s)
{
    (void)ctx; registrar = s->reg;
}
static enum mrp_reg_state registrar_of(struct mrp_app *a)
{
    registrar = MRP_REG_STATE_COUNT;
    (void)mrp_attr_visit(a, 0, visit_registrar, NULL);
    return registrar;
}

/* One VID 2 vector: New, or Lv (events * 36, 10.8.2.10.1). */
static uint8_t vid_new[] = {0, 1, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0};
static uint8_t vid_lv[] = {0, 1, 2, 0, 1, 0, 2, 180, 0, 0, 0, 0};

/*
 * A receive allocates its new attribute, then one propagation target a port (doc/integrator.md, transmit and
 * retry). The second allocation is the first port's reservation.
 */
#define RESERVATION_ALLOCATION 2u

Ensure(EndStation, one_port_refused_reservation_refuses_the_receive_only_in_the_default_build)
{
    struct mrp_app *a = vlan_with_policy(1);
    allocation_fail_after(RESERVATION_ALLOCATION);
    const int r = mrp_rx(a, 0, vid_new, sizeof(vid_new));
#if LWSRP_ONE_PORT_MAP
    /* Nothing is reserved: the refusal is never reached, and the event applies. */
    assert_that(r, is_equal_to(0));
    assert_that(allocation_failures(), is_equal_to(0));
    assert_that(joins, is_equal_to(1));
    assert_that(registrar_of(a), is_equal_to(MRP_REG_STATE_IN));
#else
    /* The refused reservation refuses the receive, with no indication and the Registrar unchanged. */
    assert_that(r, is_equal_to(-SHLAN_ERROR_NO_MEMORY));
    assert_that(allocation_failures(), is_equal_to(1));
    assert_that(joins, is_equal_to(0));
    assert_that(registrar_of(a), is_equal_to(MRP_REG_STATE_MT));
#endif
    assert_that(policy_calls, is_equal_to(0));
    allocation_fail_after(0);
    mrp_app_destroy(a);
}

Ensure(EndStation, one_port_calls_the_policy_only_in_the_default_build)
{
    struct mrp_app *a = vlan_with_policy(1);
    assert_that(mrp_rx(a, 0, vid_new, sizeof(vid_new)), is_equal_to(0));
    assert_that(joins, is_equal_to(1));
    assert_that(policy_calls, is_equal_to(LWSRP_ONE_PORT_MAP ? 0u : 1u));
    assert_that(mrp_rx(a, 0, vid_lv, sizeof(vid_lv)), is_equal_to(0));
    tick(100); /* The leave timer withdraws the registration (Table 10-4). */
    assert_that(leaves, is_equal_to(1));
    assert_that(registrar_of(a), is_equal_to(MRP_REG_STATE_MT));
    assert_that(policy_calls, is_equal_to(LWSRP_ONE_PORT_MAP ? 0u : 2u));
    mrp_app_destroy(a);
}

Ensure(EndStation, two_ports_reserve_refuse_and_call_the_policy_in_every_build)
{
    struct mrp_app *a = vlan_with_policy(2);
    allocation_fail_after(RESERVATION_ALLOCATION);
    assert_that(mrp_rx(a, 0, vid_new, sizeof(vid_new)), is_equal_to(-SHLAN_ERROR_NO_MEMORY));
    assert_that(allocation_failures(), is_equal_to(1));
    assert_that(joins, is_equal_to(0));
    assert_that(policy_calls, is_equal_to(0));
    assert_that(registrar_of(a), is_equal_to(MRP_REG_STATE_MT));
    allocation_fail_after(0);
    /* The retried payload applies, with one policy call for the Join and one for the Leave. */
    assert_that(mrp_rx(a, 0, vid_new, sizeof(vid_new)), is_equal_to(0));
    assert_that(joins, is_equal_to(1));
    assert_that(policy_calls, is_equal_to(1));
    assert_that(registrar_of(a), is_equal_to(MRP_REG_STATE_IN));
    assert_that(mrp_rx(a, 0, vid_lv, sizeof(vid_lv)), is_equal_to(0));
    tick(100);
    assert_that(leaves, is_equal_to(1));
    assert_that(policy_calls, is_equal_to(2));
    mrp_app_destroy(a);
}

/* ---- sparse AttributeTypes -------------------------------------------- */

/* Types of a test application, one octet each: a word boundary (31, 32), empty words between, and type 255. */
static const uint8_t sparse_types[] = {1u, 31u, 32u, 64u, 129u, 224u, 255u};

static bool sparse_type(uint8_t type)
{
    for (size_t k = 0; k < sizeof(sparse_types); ++k) {
        if (sparse_types[k] == type) {
            return true;
        }
    }
    return false;
}
static uint8_t sparse_len(uint8_t type)
{
    return sparse_type(type) ? 1u : 0u;
}
static int sparse_encode(uint8_t type, const void *value, uint8_t *buf, size_t len)
{
    (void)type;
    if (len < 1u) {
        return -1;
    }
    buf[0] = *(const uint8_t *)value;
    return 1;
}
static int sparse_decode(uint8_t type, uint32_t offset, const uint8_t *buf, size_t len, void *out)
{
    (void)type;
    if (len < 1u || buf[0] + offset > 255u) {
        return -1;
    }
    *(uint8_t *)out = (uint8_t)(buf[0] + offset);
    return 1;
}
static int sparse_cmp(uint8_t type, const void *a, const void *b)
{
    (void)type;
    return memcmp(a, b, 1);
}

static uint8_t sent_pdu[1500];
static size_t sent_len;
static int capture(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx; (void)port;
    memcpy(sent_pdu, pdu, len);
    sent_len = len;
    return 0;
}

/* Declare one value (its type's own number) of each type in mask over sparse_types, send, and check the PDU. */
static void sends_each_declared_type(unsigned mask)
{
    struct mrp_app_ops ops = {0};
    ops.join_ind = joined; ops.leave_ind = left;
    ops.encode_attr = sparse_encode; ops.decode_attr = sparse_decode;
    ops.attr_len = sparse_len; ops.attr_cmp = sparse_cmp;
    ops.ethertype = MRP_ETHERTYPE_MMRP; ops.proto_version = 0u;
    struct mrp_app *a = mrp_app_create(&ops, 1);
    uint8_t expected[sizeof(sparse_types)];
    size_t n = 0;
    for (size_t k = 0; k < sizeof(sparse_types); ++k) {
        if (mask & (1u << k)) {
            const uint8_t value = sparse_types[k];
            assert_that(mrp_mad_join(a, 0, sparse_types[k], &value, true), is_equal_to(0));
            expected[n++] = sparse_types[k];
        }
    }
    uint8_t buffer[1500];
    sent_len = 0;
    assert_that(mrp_transmit(a, 0, buffer, sizeof(buffer), capture, NULL), is_equal_to(1));
    struct mrpdu_profile profile = mrpdu_profile_for(ops.ethertype);
    static struct mrpdu_decoded d;
    assert_that(mrpdu_decode(sent_pdu, sent_len, &profile, &d), is_equal_to(0));
    /* One Message a declared type, in AttributeType order, each with its one New value. */
    assert_that(d.messages, is_equal_to(n));
    for (size_t m = 0; m < n && m < d.messages; ++m) {
        assert_that(d.message[m].type, is_equal_to(expected[m]));
        assert_that(d.message[m].vectors, is_equal_to(1));
        const struct mrpdu_vector *v = &d.vector[d.message[m].first_vector];
        assert_that(v->values, is_equal_to(1));
        assert_that(v->first_value[0], is_equal_to(expected[m]));
        assert_that(mrpdu_event(v, 0), is_equal_to(MRP_ATTR_EVENT_NEW));
    }
    mrp_app_destroy(a);
}

Ensure(EndStation, sparse_attribute_types_each_send_one_message_in_type_order)
{
    sends_each_declared_type(0x7fu);              /* all seven */
    sends_each_declared_type(1u << 6);            /* 255 alone, after seven empty words */
    sends_each_declared_type(1u << 2 | 1u << 4);  /* 32 then 129: an empty first word, two empty words between */
    sends_each_declared_type(1u << 1 | 1u << 3);  /* 31 then 64: each the last or first of its word */
    sends_each_declared_type(1u << 5 | 1u << 6);  /* 224 and 255, in the last word */
}

TestSuite *end_station_suite(void)
{
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, EndStation, one_port_refused_reservation_refuses_the_receive_only_in_the_default_build);
    add_test_with_context(suite, EndStation, one_port_calls_the_policy_only_in_the_default_build);
    add_test_with_context(suite, EndStation, two_ports_reserve_refuse_and_call_the_policy_in_every_build);
    add_test_with_context(suite, EndStation, sparse_attribute_types_each_send_one_message_in_type_order);
    return suite;
}
