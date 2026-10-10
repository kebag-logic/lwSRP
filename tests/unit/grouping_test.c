/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Grouped MRPDU encoding: one Message per AttributeType, one single-value
 * VectorAttribute per declaration in ascending FirstValue order, and one
 * EndMark per Message (IEEE 802.1Q-2018 10.8.1.2, 10.8.2). Transmitted bytes
 * are graded against goldens and the independent test-side decoder.
 */
#include <cgreen/cgreen.h>
#include <string.h>
#include "shish_lan/mmrp.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"
#include "ports/timer.h"
#include "mrpdu_decoder.h"

Describe(Grouping);
BeforeEach(Grouping) {}
AfterEach(Grouping) {}

/* Runs of zero octets for the FirstValue of a LeaveAll-only vector. */
#define Z4 0x00, 0x00, 0x00, 0x00
#define Z8 Z4, Z4
#define Z25 Z8, Z8, Z8, 0x00
#define Z34 Z8, Z8, Z8, Z8, 0x00, 0x00

/* Locally administered stream identities. */
#define LISTENER_0 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
#define LISTENER_1 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x01
#define LISTENER_2 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x02

/* Twice the largest capacity used, so planted defects stay inside storage. */
static uint8_t frame[4096];
static size_t frame_len;
static unsigned frames;

static int capture(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx; (void)port;
    assert_that(len, is_less_than(sizeof(frame) + 1u));
    frame_len = len < sizeof(frame) ? len : sizeof(frame);
    memcpy(frame, pdu, frame_len);
    ++frames;
    return 0;
}

static void tick(unsigned count)
{
    while (count--) {
        shlan_timer_tick();
    }
}

/* Byte-exact comparison; a failure reports the first differing octet. */
static void same_bytes(const uint8_t *expected, size_t len)
{
    assert_that(frame_len, is_equal_to(len));
    size_t first = 0;
    while (first < len && first < frame_len && frame[first] == expected[first]) {
        ++first;
    }
    assert_that(first, is_equal_to(len));
}

static void transmit(struct mrp_app *a, size_t capacity)
{
    static uint8_t buffer[4096];
    frames = 0;
    assert_that(mrp_transmit(a, 0, buffer, capacity, capture, NULL), is_equal_to(1));
    assert_that(frames, is_equal_to(1));
}

static void listener(struct mrp_app *a, uint8_t station, uint16_t uid)
{
    struct msrp_stream_id sid = {{0x02, 0x00, 0x00, 0x00, 0x00, station,
                                  (uint8_t)(uid >> 8), (uint8_t)uid}};
    assert_that(msrp_declare_listener(a, 0, &sid, MSRP_LISTENER_DECL_READY), is_equal_to(0));
}

static struct msrp_talker_adv talker_value(uint8_t uid)
{
    struct msrp_talker_adv t = {
        .stream_id = {{0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, uid}},
        .dest_mac = {0x91, 0xe0, 0xf0, 0x00, 0xfe, uid},
        .vlan_id = 2, .max_frame_size = 224, .max_interval_frames = 1,
        .priority_and_rank = 0x60, .accumulated_latency = 2000,
    };
    return t;
}

static void talker(struct mrp_app *a, uint8_t uid)
{
    struct msrp_talker_adv t = talker_value(uid);
    assert_that(msrp_declare_talker(a, 0, &t, true), is_equal_to(0));
}

static void domain(struct mrp_app *a, uint8_t class_id, uint8_t priority)
{
    struct msrp_domain d = {class_id, priority, 2};
    assert_that(mrp_mad_join(a, 0, MSRP_ATTR_TYPE_DOMAIN, &d, false), is_equal_to(0));
}

/* Two Listener Ready declarations with New, in one Message. */
static const uint8_t two_listeners[] = {
    0x00,                             /* ProtocolVersion */
    0x03, 0x08, 0x00, 0x1a,           /* Listener, AttributeLength 8, AttributeListLength 26 */
    0x00, 0x01, LISTENER_0, 0x00, 0x80,
    0x00, 0x01, LISTENER_1, 0x00, 0x80,
    0x00, 0x00,                       /* AttributeList EndMark */
    0x00, 0x00,                       /* MRPDU EndMark */
};

Ensure(Grouping, two_listener_values_share_one_message)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listener(a, 0x20, 0);
    listener(a, 0x20, 1);
    transmit(a, 1500);
    same_bytes(two_listeners, sizeof(two_listeners));
    msrp_app_destroy(a);
}

Ensure(Grouping, domain_classes_share_one_message_in_ascending_order)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    domain(a, 5, 2); /* SR class B */
    domain(a, 6, 3); /* SR class A */
    transmit(a, 1500);
    static const uint8_t expected[] = {
        0x00,
        0x04, 0x04, 0x00, 0x10,       /* Domain, AttributeLength 4, AttributeListLength 16 */
        0x00, 0x01, 0x05, 0x02, 0x00, 0x02, 0x6c, /* class B, JoinMt */
        0x00, 0x01, 0x06, 0x03, 0x00, 0x02, 0x6c, /* class A, JoinMt */
        0x00, 0x00,
        0x00, 0x00,
    };
    same_bytes(expected, sizeof(expected));
    msrp_app_destroy(a);
}

Ensure(Grouping, talker_and_listener_messages_follow_attribute_type_order)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listener(a, 0x20, 0);
    talker(a, 0);
    listener(a, 0x20, 1);
    talker(a, 1);
    transmit(a, 1500);
    static const uint8_t expected[] = {
        0x00,
        0x01, 0x19, 0x00, 0x3a,       /* Talker Advertise, AttributeLength 25, AttributeListLength 58 */
        0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        0x91, 0xe0, 0xf0, 0x00, 0xfe, 0x00, 0x00, 0x02, 0x00, 0xe0, 0x00, 0x01,
        0x60, 0x00, 0x00, 0x07, 0xd0, 0x00,
        0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01,
        0x91, 0xe0, 0xf0, 0x00, 0xfe, 0x01, 0x00, 0x02, 0x00, 0xe0, 0x00, 0x01,
        0x60, 0x00, 0x00, 0x07, 0xd0, 0x00,
        0x00, 0x00,
        0x03, 0x08, 0x00, 0x1a,       /* Listener */
        0x00, 0x01, LISTENER_0, 0x00, 0x80,
        0x00, 0x01, LISTENER_1, 0x00, 0x80,
        0x00, 0x00,
        0x00, 0x00,
    };
    same_bytes(expected, sizeof(expected));
    msrp_app_destroy(a);
}

Ensure(Grouping, leaveall_flags_every_stream_type_including_empty_ones)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listener(a, 0x20, 1);
    tick(1500); /* The LeaveAll timer expires inside (1000, 1500) cs. */
    transmit(a, 1500);
    static const uint8_t expected[] = {
        0x00,
        0x01, 0x19, 0x00, 0x1d,       /* Talker Advertise: LeaveAll only */
        0x20, 0x00, Z25,
        0x00, 0x00,
        0x02, 0x22, 0x00, 0x26,       /* Talker Failed: LeaveAll only */
        0x20, 0x00, Z34,
        0x00, 0x00,
        0x03, 0x08, 0x00, 0x18,       /* Listener: LeaveAll, then the declaration */
        0x20, 0x00, Z8,
        0x00, 0x01, LISTENER_1, 0x00, 0x80,
        0x00, 0x00,
        0x04, 0x04, 0x00, 0x08,       /* Domain: LeaveAll only */
        0x20, 0x00, Z4,
        0x00, 0x00,
        0x00, 0x00,
    };
    same_bytes(expected, sizeof(expected));
    msrp_app_destroy(a);
}

Ensure(Grouping, vlan_leaveall_message_carries_the_declared_vectors)
{
    struct mvrp_ctx ctx = {0};
    struct mrp_app *a = mvrp_app_create(1, &ctx);
    assert_that(mvrp_declare(a, 0, 2), is_equal_to(0));
    assert_that(mvrp_declare(a, 0, 3), is_equal_to(0));
    tick(1500);
    transmit(a, 1500);
    static const uint8_t expected[] = {
        0x00,
        0x01, 0x02,                   /* VID, AttributeLength 2; no AttributeListLength */
        0x20, 0x00, 0x00, 0x00,       /* LeaveAll */
        0x00, 0x01, 0x00, 0x02, 0x90, /* VID 2, Mt */
        0x00, 0x01, 0x00, 0x03, 0x90, /* VID 3, Mt */
        0x00, 0x00,
        0x00, 0x00,
    };
    same_bytes(expected, sizeof(expected));
    mvrp_app_destroy(a);
}

/* Per-value Messages would need 39 octets for the same two values. */
Ensure(Grouping, a_message_that_fits_exactly_is_not_split)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listener(a, 0x20, 0);
    listener(a, 0x20, 1);
    transmit(a, sizeof(two_listeners));
    same_bytes(two_listeners, sizeof(two_listeners));
    msrp_app_destroy(a);
}

Ensure(Grouping, one_octet_short_moves_a_vector_to_a_second_pdu)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listener(a, 0x20, 0);
    listener(a, 0x20, 1);
    static const uint8_t newest[] = {
        0x00, 0x03, 0x08, 0x00, 0x0e, 0x00, 0x01, LISTENER_1, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    };
    static const uint8_t omitted[] = {
        0x00, 0x03, 0x08, 0x00, 0x0e, 0x00, 0x01, LISTENER_0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    };
    transmit(a, sizeof(two_listeners) - 1u);
    same_bytes(newest, sizeof(newest));
    tick(20);
    transmit(a, sizeof(two_listeners) - 1u);
    same_bytes(omitted, sizeof(omitted));
    msrp_app_destroy(a);
}

/* The PDU's value vectors, after checking every grouped-form rule. */
static unsigned graded(const struct mrp_app *a, const uint8_t *pdu, size_t len, unsigned *flagged)
{
    static struct mrpdu_decoded d;
    struct mrpdu_profile profile = mrpdu_profile_for(a->ops->ethertype);
    unsigned last = a->ops->ethertype == MRP_ETHERTYPE_MSRP ? 4u :
                    a->ops->ethertype == MRP_ETHERTYPE_MMRP ? 2u : 1u;
    unsigned values = 0;
    *flagged = 0;
    assert_that(mrpdu_decode(pdu, len, &profile, &d), is_equal_to(0));
    assert_that(d.pdu_end_mark, is_true);
    assert_that(d.trailing, is_equal_to(0));
    assert_that(d.end_marks, is_equal_to(d.messages + 1u));
    for (size_t m = 0; m < d.messages; ++m) {
        const struct mrpdu_message *msg = &d.message[m];
        assert_that(msg->end_mark, is_true);
        if (m > 0) {
            assert_that(msg->type, is_greater_than(d.message[m - 1u].type));
        }
        const struct mrpdu_vector *previous = NULL;
        for (size_t k = 0; k < msg->vectors; ++k) {
            const struct mrpdu_vector *v = &d.vector[msg->first_vector + k];
            if (k == 0 && v->leave_all) {
                assert_that(v->values, is_equal_to(0));
                assert_that(msg->type, is_less_than(last + 1u));
                ++*flagged;
                continue;
            }
            assert_that(v->leave_all, is_equal_to(0));
            assert_that(v->values, is_equal_to(1));
            if (previous) {
                assert_that(memcmp(previous->first_value, v->first_value, v->length),
                            is_less_than(0));
            }
            previous = v;
            ++values;
        }
    }
    assert_that(*flagged == 0 || *flagged == last, is_true);
    return values;
}

Ensure(Grouping, an_ethernet_mtu_carries_124_listener_vectors_in_one_message)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    for (uint16_t uid = 1; uid <= 125; ++uid) {
        listener(a, 0x20, uid);
    }
    /* 1 + 4 + 124 * 12 + 2 + 2 = 1497 octets; a 125th vector needs 1509. */
    static uint8_t expected[1497];
    size_t at = 0;
    expected[at++] = 0x00;
    expected[at++] = 0x03; expected[at++] = 0x08;
    expected[at++] = 0x05; expected[at++] = 0xd2; /* AttributeListLength 1490 */
    for (uint16_t uid = 2; uid <= 125; ++uid) {
        const uint8_t vector[] = {0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x20,
                                  (uint8_t)(uid >> 8), (uint8_t)uid, 0x00, 0x80};
        memcpy(expected + at, vector, sizeof(vector));
        at += sizeof(vector);
    }
    at += 4; /* AttributeList and MRPDU EndMarks are zero. */
    assert_that(at, is_equal_to(sizeof(expected)));
    transmit(a, 1500);
    same_bytes(expected, sizeof(expected));
    /* Only the omitted vector moves; it leads the next opportunity. */
    tick(20);
    transmit(a, 1500);
    unsigned flagged;
    assert_that(graded(a, frame, frame_len, &flagged), is_equal_to(124));
    assert_that(frame[5 + 9], is_equal_to(1));
    msrp_app_destroy(a);
}

static void sweep(struct mrp_app *a, const size_t capacities[4], void (*change)(struct mrp_app *, unsigned))
{
    unsigned sent = 0, vectors = 0, leavealls = 0;
    for (unsigned n = 0; n < 160; ++n) { /* 3200 cs spans two LeaveAll periods. */
        change(a, n);
        static uint8_t buffer[4096];
        frames = 0;
        int r = mrp_transmit(a, 0, buffer, capacities[n % 4u], capture, NULL);
        assert_that(r, is_greater_than(-1));
        if (r == 1) {
            unsigned flagged;
            vectors += graded(a, frame, frame_len, &flagged);
            leavealls += flagged != 0;
            ++sent;
        }
        tick(20);
    }
    assert_that(sent, is_greater_than(40));
    assert_that(vectors, is_greater_than(sent));
    assert_that(leavealls, is_greater_than(1));
}

static void stream_changes(struct mrp_app *a, unsigned n)
{
    struct msrp_stream_id gone = {{LISTENER_2}};
    struct msrp_talker_adv t = talker_value(1);
    switch (n) {
    case 0:
        listener(a, 0x20, 2); talker(a, 3); domain(a, 6, 3); listener(a, 0x20, 0);
        talker(a, 1); listener(a, 0x30, 7); domain(a, 5, 2); talker(a, 2);
        break;
    case 1: {
        struct msrp_talker_failed failed = {talker_value(9), {0, 0, 0, 0, 0, 0, 0, 1, 2}};
        assert_that(mrp_mad_join(a, 0, MSRP_ATTR_TYPE_TALKER_FAILED, &failed, true), is_equal_to(0));
        break;
    }
    case 40:
        assert_that(msrp_withdraw_listener(a, 0, &gone), is_equal_to(0));
        break;
    case 80:
        assert_that(msrp_withdraw_talker(a, 0, &t.stream_id), is_equal_to(0));
        break;
    default:
        break;
    }
}

Ensure(Grouping, every_stream_pdu_keeps_one_ordered_message_per_type)
{
    struct msrp_ctx ctx = {0};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    static const size_t capacities[4] = {1500, 200, 140, 120};
    sweep(a, capacities, stream_changes);
    msrp_app_destroy(a);
}

static void vlan_changes(struct mrp_app *a, unsigned n)
{
    static const uint16_t vids[] = {7, 3, 5, 2, 4};
    if (n < 5) {
        assert_that(mvrp_declare(a, 0, vids[n]), is_equal_to(0));
    } else if (n == 60) {
        assert_that(mvrp_withdraw(a, 0, 5), is_equal_to(0));
    }
}

static void mac_changes(struct mrp_app *a, unsigned n)
{
    struct mmrp_mac mac = {{0x91, 0xe0, 0xf0, 0x01, 0x00, (uint8_t)(9 - n)}};
    if (n < 4) {
        assert_that(mmrp_declare_mac(a, 0, &mac), is_equal_to(0));
    } else if (n == 4) {
        assert_that(mmrp_declare_svc(a, 0, MMRP_SVC_FORWARD_UNREGISTERED), is_equal_to(0));
    } else if (n == 60) {
        mac.addr[5] = 8;
        assert_that(mmrp_withdraw_mac(a, 0, &mac), is_equal_to(0));
    }
}

Ensure(Grouping, every_vlan_and_mac_pdu_keeps_one_ordered_message_per_type)
{
    struct mvrp_ctx vlan = {0};
    struct mrp_app *a = mvrp_app_create(1, &vlan);
    static const size_t vlan_capacities[4] = {1500, 26, 21, 16};
    sweep(a, vlan_capacities, vlan_changes);
    mvrp_app_destroy(a);
    struct mmrp_ctx mac = {0};
    a = mmrp_app_create(1, &mac);
    static const size_t mac_capacities[4] = {1500, 48, 40, 31};
    sweep(a, mac_capacities, mac_changes);
    mmrp_app_destroy(a);
}

/* The same JoinIn registrations in all three encodings 10.8 permits. */
static const uint8_t stream_separate[] = {
    0x00,
    0x03, 0x08, 0x00, 0x0e, 0x00, 0x01, LISTENER_1, 0x24, 0x80, 0x00, 0x00,
    0x03, 0x08, 0x00, 0x0e, 0x00, 0x01, LISTENER_2, 0x24, 0x80, 0x00, 0x00,
    0x04, 0x04, 0x00, 0x09, 0x00, 0x01, 0x05, 0x02, 0x00, 0x02, 0x24, 0x00, 0x00,
    0x04, 0x04, 0x00, 0x09, 0x00, 0x01, 0x06, 0x03, 0x00, 0x02, 0x24, 0x00, 0x00,
    0x00, 0x00,
};
static const uint8_t stream_grouped[] = {
    0x00,
    0x03, 0x08, 0x00, 0x1a,
    0x00, 0x01, LISTENER_1, 0x24, 0x80,
    0x00, 0x01, LISTENER_2, 0x24, 0x80,
    0x00, 0x00,
    0x04, 0x04, 0x00, 0x10,
    0x00, 0x01, 0x05, 0x02, 0x00, 0x02, 0x24,
    0x00, 0x01, 0x06, 0x03, 0x00, 0x02, 0x24,
    0x00, 0x00,
    0x00, 0x00,
};
/* FirstValue + 1 (35.2.2.8, 35.2.2.9): two JoinIn events, two Ready types. */
static const uint8_t stream_packed[] = {
    0x00,
    0x03, 0x08, 0x00, 0x0e, 0x00, 0x02, LISTENER_1, 0x2a, 0xa0, 0x00, 0x00,
    0x04, 0x04, 0x00, 0x09, 0x00, 0x02, 0x05, 0x02, 0x00, 0x02, 0x2a, 0x00, 0x00,
    0x00, 0x00,
};
static const uint8_t vlan_separate[] = {
    0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x02, 0x24, 0x00, 0x00,
    0x01, 0x02, 0x00, 0x01, 0x00, 0x03, 0x24, 0x00, 0x00, 0x00, 0x00,
};
static const uint8_t vlan_grouped[] = {
    0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x02, 0x24, 0x00, 0x01, 0x00, 0x03, 0x24,
    0x00, 0x00, 0x00, 0x00,
};
static const uint8_t vlan_packed[] = {
    0x00, 0x01, 0x02, 0x00, 0x02, 0x00, 0x02, 0x2a, 0x00, 0x00, 0x00, 0x00,
};

static unsigned listeners_seen, listener_uids, domains_seen, domain_classes, vlans_seen;

static void on_listener(struct msrp_ctx *ctx, uint8_t port, const struct msrp_stream_id *sid,
                        enum msrp_listener_decl decl, bool is_new)
{
    (void)ctx; (void)port; (void)is_new;
    assert_that(decl, is_equal_to(MSRP_LISTENER_DECL_READY));
    ++listeners_seen;
    listener_uids |= 1u << sid->bytes[7];
}

static void on_domain(struct msrp_ctx *ctx, uint8_t port, const struct msrp_domain *d, bool is_new)
{
    (void)ctx; (void)port; (void)is_new;
    assert_that(d->priority, is_equal_to(d->class_id == 6 ? 3 : 2));
    assert_that(d->vid, is_equal_to(2));
    ++domains_seen;
    domain_classes |= 1u << d->class_id;
}

static void on_vlan(struct mvrp_ctx *ctx, uint8_t port, uint16_t vid, bool is_new)
{
    (void)ctx; (void)port; (void)is_new;
    vlans_seen |= 1u << vid;
}

static void registers(const uint8_t *stream, size_t stream_len, const uint8_t *vlan, size_t vlan_len)
{
    struct msrp_ctx ctx = {.on_listener = on_listener, .on_domain = on_domain};
    struct mrp_app *a = msrp_app_create(1, &ctx);
    listeners_seen = listener_uids = domains_seen = domain_classes = 0;
    assert_that(mrp_rx(a, 0, stream, stream_len), is_equal_to(0));
    assert_that(listeners_seen, is_equal_to(2));
    assert_that(listener_uids, is_equal_to((1u << 1) | (1u << 2)));
    assert_that(domains_seen, is_equal_to(2));
    assert_that(domain_classes, is_equal_to((1u << 5) | (1u << 6)));
    assert_that(mrp_attr_visit(a, 0, NULL, NULL), is_equal_to(4));
    msrp_app_destroy(a);
    struct mvrp_ctx vctx = {.on_vlan_registered = on_vlan};
    struct mrp_app *v = mvrp_app_create(1, &vctx);
    vlans_seen = 0;
    assert_that(mrp_rx(v, 0, vlan, vlan_len), is_equal_to(0));
    assert_that(vlans_seen, is_equal_to((1u << 2) | (1u << 3)));
    mvrp_app_destroy(v);
}

Ensure(Grouping, received_values_in_separate_messages_register)
{
    registers(stream_separate, sizeof(stream_separate), vlan_separate, sizeof(vlan_separate));
}

Ensure(Grouping, received_values_grouped_in_one_message_register)
{
    registers(stream_grouped, sizeof(stream_grouped), vlan_grouped, sizeof(vlan_grouped));
}

Ensure(Grouping, received_values_packed_in_one_vector_register)
{
    registers(stream_packed, sizeof(stream_packed), vlan_packed, sizeof(vlan_packed));
}

Ensure(Grouping, test_decoder_reads_the_three_forms_and_rejects_bad_ones)
{
    static struct mrpdu_decoded d;
    struct mrpdu_profile stream = mrpdu_profile_for(MRP_ETHERTYPE_MSRP);
    struct mrpdu_profile vlan = mrpdu_profile_for(MRP_ETHERTYPE_MVRP);
    assert_that(mrpdu_decode(stream_separate, sizeof(stream_separate), &stream, &d), is_equal_to(0));
    assert_that(d.messages, is_equal_to(4));
    assert_that(d.vectors, is_equal_to(4));
    assert_that(d.end_marks, is_equal_to(5));
    assert_that(mrpdu_decode(stream_grouped, sizeof(stream_grouped), &stream, &d), is_equal_to(0));
    assert_that(d.messages, is_equal_to(2));
    assert_that(d.vectors, is_equal_to(4));
    assert_that(d.message[0].list_length, is_equal_to(26));
    assert_that(d.end_marks, is_equal_to(3));
    assert_that(mrpdu_decode(stream_packed, sizeof(stream_packed), &stream, &d), is_equal_to(0));
    assert_that(d.vectors, is_equal_to(2));
    assert_that(d.vector[0].values, is_equal_to(2));
    assert_that(mrpdu_event(&d.vector[0], 0), is_equal_to(1));
    assert_that(mrpdu_event(&d.vector[0], 1), is_equal_to(1));
    assert_that(mrpdu_four_packed(&d.vector[0], 0), is_equal_to(2));
    assert_that(mrpdu_four_packed(&d.vector[0], 1), is_equal_to(2));
    assert_that(mrpdu_four_packed(&d.vector[1], 0), is_equal_to(0));
    assert_that(mrpdu_decode(vlan_grouped, sizeof(vlan_grouped), &vlan, &d), is_equal_to(0));
    assert_that(d.messages, is_equal_to(1));
    assert_that(d.vectors, is_equal_to(2));
    /* 10.8.1.2 f: the end of the PDU acts as the final EndMark. */
    assert_that(mrpdu_decode(vlan_grouped, sizeof(vlan_grouped) - 2u, &vlan, &d), is_equal_to(0));
    assert_that(d.pdu_end_mark, is_false);
    assert_that(d.end_marks, is_equal_to(1));
    uint8_t bad[sizeof(vlan_grouped)];
    memcpy(bad, vlan_grouped, sizeof(bad));
    bad[7] = 216; /* 10.8.2.5: no seventh AttributeEvent value */
    assert_that(mrpdu_decode(bad, sizeof(bad), &vlan, &d), is_equal_to(-1));
    memcpy(bad, vlan_grouped, sizeof(bad));
    bad[4] = 0; /* The header reads as an EndMark: an empty AttributeList (10.8.1.2 d). */
    assert_that(mrpdu_decode(bad, sizeof(bad), &vlan, &d), is_equal_to(-1));
    memcpy(bad, vlan_grouped, sizeof(bad));
    bad[3] = 0x40; /* 10.8.2.6: LeaveAllEvent 2 is reserved */
    assert_that(mrpdu_decode(bad, sizeof(bad), &vlan, &d), is_equal_to(-1));
    /* 10.8.3.4 b: an incomplete VectorAttribute discards the PDU. */
    assert_that(mrpdu_decode(vlan_grouped, 11, &vlan, &d), is_equal_to(-1));
    uint8_t empty[] = {0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00};
    assert_that(mrpdu_decode(empty, sizeof(empty), &vlan, &d), is_equal_to(-1));
}

TestSuite *grouping_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, Grouping, two_listener_values_share_one_message);
    add_test_with_context(s, Grouping, domain_classes_share_one_message_in_ascending_order);
    add_test_with_context(s, Grouping, talker_and_listener_messages_follow_attribute_type_order);
    add_test_with_context(s, Grouping, leaveall_flags_every_stream_type_including_empty_ones);
    add_test_with_context(s, Grouping, vlan_leaveall_message_carries_the_declared_vectors);
    add_test_with_context(s, Grouping, a_message_that_fits_exactly_is_not_split);
    add_test_with_context(s, Grouping, one_octet_short_moves_a_vector_to_a_second_pdu);
    add_test_with_context(s, Grouping, an_ethernet_mtu_carries_124_listener_vectors_in_one_message);
    add_test_with_context(s, Grouping, every_stream_pdu_keeps_one_ordered_message_per_type);
    add_test_with_context(s, Grouping, every_vlan_and_mac_pdu_keeps_one_ordered_message_per_type);
    add_test_with_context(s, Grouping, received_values_in_separate_messages_register);
    add_test_with_context(s, Grouping, received_values_grouped_in_one_message_register);
    add_test_with_context(s, Grouping, received_values_packed_in_one_vector_register);
    add_test_with_context(s, Grouping, test_decoder_reads_the_three_forms_and_rejects_bad_ones);
    return s;
}
