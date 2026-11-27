/* SPDX-License-Identifier: Apache-2.0 */
/*
 * One random life of an MRP application, printed as a trace: every received
 * PDU and its result, every local declaration and withdrawal, every
 * transmit opportunity with each offered PDU's octets and the send result,
 * ticks, reclamation, role changes, periodic switching, every indication,
 * propagation decision, receive-filter call and observed transition, and
 * after each step a digest of every attribute instance's state and value.
 * tests/check_differential.py builds it against a base revision's sources
 * and against the checkout's; both traces must be byte-identical.
 *
 * The application is chosen by the seed: MSRP, MVRP or MMRP through their
 * modules, on one to three ports, or a test application whose FirstValue
 * is one octet of a two-octet value, so different instances encode the same
 * FirstValue and a Message's order of equal values shows, whose key
 * collides across values, and whose encoder refuses one value, so a build
 * fails partway; the transmit buffer's digest follows every opportunity. Its
 * AttributeTypes are spread over the 256: a word boundary of the assembler's
 * type set (31, 32), empty words between, and 255. Values come from small sets, so lookups,
 * replacements and keys meet often. Allocation and send refusals are
 * planted by the seed.
 *
 * usage: mad_trace <seed> <steps>
 * Build with -DTRACE_ATTR_KEY when mrp.h has attr_key; it is used where LWSRP_ATTR_KEY builds it.
 */
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ports/alloc.h"
#include "ports/timer.h"
#include "shish_lan/mmrp.h"
#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"
#include "shish_lan/msrp.h"
#include "shish_lan/mvrp.h"

enum kind { KIND_MSRP, KIND_MVRP, KIND_MMRP, KIND_TIE, KINDS };
static const char *const kind_names[KINDS] = {"msrp", "mvrp", "mmrp", "tie"};

static uint32_t rng;
static enum kind kind;
static struct mrp_app *app;
static uint8_t n_ports;
static uint64_t digest;
static unsigned long allocations, releases, live;
static uint32_t fail_every;   /* refuse every fail_every-th allocation; 0 never */
static uint32_t refuse_every; /* refuse every refuse_every-th send; 0 never */
static unsigned long sends;

static uint32_t draw(uint32_t n)
{
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng % n;
}

static void hex(const char *tag, const void *bytes, size_t n)
{
    const uint8_t *b = bytes;
    printf("%s", tag);
    for (size_t k = 0; k < n; ++k) {
        printf("%02x", b[k]);
    }
}

static void mix(const void *bytes, size_t n)
{
    const uint8_t *b = bytes;
    for (size_t k = 0; k < n; ++k) {
        digest = (digest ^ b[k]) * UINT64_C(0x100000001b3);
    }
}

/* ---- the allocation port, with planted refusals -------------------- */

void *shlan_malloc(size_t size)
{
    return shlan_calloc(1, size);
}

void *shlan_calloc(size_t nmemb, size_t size)
{
    ++allocations;
    if (fail_every && allocations % fail_every == 0u) {
        printf("  alloc refused\n");
        return NULL;
    }
    void *p = calloc(nmemb, size);
    if (p) {
        ++live;
    }
    return p;
}

void shlan_free(void *ptr)
{
    if (ptr) {
        ++releases;
        --live;
    }
    free(ptr);
}

int shlan_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("  print ");
    int r = vprintf(fmt, ap);
    va_end(ap);
    return r;
}

/* ---- values ---------------------------------------------------------- */

static size_t value_len(uint8_t type)
{
    return app->ops->attr_mem_len ? app->ops->attr_mem_len(type) : app->ops->attr_len(type);
}

/* A StreamID of one talker: few UniqueIDs, whose low octet repeats. */
static void stream_id(uint8_t *id)
{
    static const uint8_t mac[6] = {0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x10u};
    memcpy(id, mac, sizeof(mac));
    id[6] = (uint8_t)draw(3);
    id[7] = (uint8_t)draw(12);
}

/* ---- the test application ------------------------------------------ */

static void tie_join(struct mrp_app *a, uint8_t port, uint8_t type, const void *value, bool is_new)
{
    (void)a;
    hex("  join ", value, 2);
    printf(" type %u port %u new %u\n", type, port, is_new);
}

static void tie_leave(struct mrp_app *a, uint8_t port, uint8_t type, const void *value)
{
    (void)a;
    hex("  leave ", value, 2);
    printf(" type %u port %u\n", type, port);
}

static uint32_t tie_map(const struct mrp_app *a, uint8_t port, uint8_t type, const void *value)
{
    (void)type; (void)value;
    uint32_t all = (1u << mrp_app_n_ports(a)) - 1u;
    uint32_t mask = all & ~(1u << port);
    printf("  map from %u: %x\n", port, mask);
    return mask;
}

static int tie_encode(uint8_t type, const void *value, uint8_t *buf, size_t len)
{
    (void)type;
    /* One value cannot be encoded, so a Message's build fails partway. */
    if (len < 1u || ((const uint8_t *)value)[0] == 23u) {
        return -1;
    }
    buf[0] = ((const uint8_t *)value)[0];
    return 1;
}

static int tie_decode(uint8_t type, uint32_t offset, const uint8_t *buf, size_t len, void *out)
{
    (void)type;
    if (len < 1u || buf[0] + offset > 255u) {
        return -1;
    }
    uint8_t *v = out;
    v[0] = (uint8_t)(buf[0] + offset);
    v[1] = 0u;
    return 1;
}

/* The test application's AttributeTypes: 2 and 129 carry a subtype. */
static const uint8_t tie_types[] = {1u, 2u, 31u, 32u, 129u, 255u};

static bool tie_type(uint8_t type)
{
    for (size_t k = 0; k < sizeof(tie_types); ++k) {
        if (tie_types[k] == type) {
            return true;
        }
    }
    return false;
}

static uint8_t tie_len(uint8_t type)
{
    return tie_type(type) ? 1u : 0u;
}

static uint8_t tie_mem_len(uint8_t type)
{
    return tie_type(type) ? 2u : 0u;
}

static int tie_cmp(uint8_t type, const void *a, const void *b)
{
    (void)type;
    return memcmp(a, b, 2);
}

static bool tie_subtype(uint8_t type)
{
    return type == 2u || type == 129u;
}

static bool tie_replaces(uint8_t old_type, const void *old_value, uint8_t new_type, const void *new_value)
{
    return old_type != new_type && ((const uint8_t *)old_value)[0] == ((const uint8_t *)new_value)[0];
}

#if defined(TRACE_ATTR_KEY) && defined(LWSRP_ATTR_KEY) && LWSRP_ATTR_KEY
static uint8_t tie_key(uint8_t type, const void *value)
{
    (void)type;
    return ((const uint8_t *)value)[0] & 0x13u;
}
#endif

static struct mrp_app *tie_create(uint8_t ports)
{
    struct mrp_app_ops ops = {0};
    ops.join_ind = tie_join;
    ops.leave_ind = tie_leave;
    ops.map_join = tie_map;
    ops.map_leave = tie_map;
    ops.encode_attr = tie_encode;
    ops.decode_attr = tie_decode;
    ops.attr_len = tie_len;
    ops.attr_cmp = tie_cmp;
    ops.attr_has_subtype = tie_subtype;
    ops.attr_mem_len = tie_mem_len;
    ops.attr_replaces = tie_replaces;
#if defined(TRACE_ATTR_KEY) && defined(LWSRP_ATTR_KEY) && LWSRP_ATTR_KEY
    ops.attr_key = tie_key;
#endif
    ops.milan_rapid_leave = draw(2) != 0u;
    ops.ethertype = MRP_ETHERTYPE_MMRP;
    ops.proto_version = 0u;
    return mrp_app_create(&ops, ports);
}

/* ---- module contexts -------------------------------------------------- */

static void on_talker_advertise(struct msrp_ctx *c, uint8_t port, const struct msrp_talker_adv *t, bool is_new)
{
    (void)c;
    hex("  talker ", t->stream_id.bytes, 8);
    hex(" da ", t->dest_mac, 6);
    printf(" vid %u size %u frames %u pr %u lat %u port %u new %u\n", t->vlan_id, t->max_frame_size,
           t->max_interval_frames, t->priority_and_rank, (unsigned)t->accumulated_latency, port, is_new);
}

static void on_talker_failed(struct msrp_ctx *c, uint8_t port, const struct msrp_talker_failed *t, bool is_new)
{
    (void)c;
    hex("  failed ", t->talker.stream_id.bytes, 8);
    hex(" info ", t->failure_info, 9);
    printf(" port %u new %u\n", port, is_new);
}

static void on_listener(struct msrp_ctx *c, uint8_t port, const struct msrp_stream_id *id,
                        enum msrp_listener_decl decl, bool is_new)
{
    (void)c;
    hex("  listener ", id->bytes, 8);
    printf(" decl %u port %u new %u\n", decl, port, is_new);
}

static void on_leave(struct msrp_ctx *c, uint8_t port, uint8_t type, const void *value)
{
    (void)c;
    printf("  leave type %u port %u", type, port);
    hex(" ", value, value_len(type));
    printf("\n");
}

static void on_domain(struct msrp_ctx *c, uint8_t port, const struct msrp_domain *d, bool is_new)
{
    (void)c;
    printf("  domain %u %u %u port %u new %u\n", d->class_id, d->priority, d->vid, port, is_new);
}

static struct msrp_ctx msrp_context = {on_talker_advertise, on_talker_failed, on_listener, on_leave, on_domain};

static void on_vlan_registered(struct mvrp_ctx *c, uint8_t port, uint16_t vid, bool is_new)
{
    (void)c;
    printf("  vlan %u port %u new %u\n", vid, port, is_new);
}

static void on_vlan_deregistered(struct mvrp_ctx *c, uint8_t port, uint16_t vid)
{
    (void)c;
    printf("  vlan gone %u port %u\n", vid, port);
}

static struct mvrp_ctx mvrp_context;

static void on_mac(struct mmrp_ctx *c, uint8_t port, const struct mmrp_mac *mac)
{
    (void)c;
    hex("  mac ", mac->addr, 6);
    printf(" port %u\n", port);
}

static void on_mac_gone(struct mmrp_ctx *c, uint8_t port, const struct mmrp_mac *mac)
{
    (void)c;
    hex("  mac gone ", mac->addr, 6);
    printf(" port %u\n", port);
}

static void on_svc(struct mmrp_ctx *c, uint8_t port, uint8_t svc)
{
    (void)c;
    printf("  svc %u port %u\n", svc, port);
}

static void on_svc_gone(struct mmrp_ctx *c, uint8_t port, uint8_t svc)
{
    (void)c;
    printf("  svc gone %u port %u\n", svc, port);
}

static struct mmrp_ctx mmrp_context = {on_mac, on_mac_gone, on_svc, on_svc_gone};

/* ---- observation ------------------------------------------------------ */

static void observed(void *ctx, const struct mrp_transition *t)
{
    (void)ctx;
    printf("  T port %u type %u ev %s %s>%s %s>%s", t->port_id, t->attr_type, mrp_event_name(t->event),
           mrp_appl_state_name(t->appl_from), mrp_appl_state_name(t->appl_to),
           mrp_reg_state_name(t->reg_from), mrp_reg_state_name(t->reg_to));
    hex(" ", t->attr_val, app->ops->attr_len(t->attr_type));
    printf("\n");
}

static bool filtered(void *ctx, uint8_t port, uint8_t type, const void *value)
{
    (void)ctx;
    const uint8_t *v = value;
    bool take = ((v[0] + v[app->ops->attr_len(type) - 1u] + type + port) % 7u) != 0u;
    printf("  filter port %u type %u %u\n", port, type, take);
    return take;
}

static void visited(void *ctx, const struct mrp_attr_status *st)
{
    (void)ctx;
    const uint8_t head[4] = {st->port_id, st->attr_type, (uint8_t)st->appl, (uint8_t)st->reg};
    mix(head, sizeof(head));
    mix(st->attr_val, value_len(st->attr_type));
}

static int sent(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    (void)ctx;
    ++sends;
    const bool refuse = refuse_every && sends % refuse_every == 0u;
    printf("  send port %u len %zu%s", port, len, refuse ? " refused" : "");
    hex(" ", pdu, len);
    printf("\n");
    return refuse ? -1 : 0;
}

/* ---- received PDUs ---------------------------------------------------- */

static size_t events(uint8_t *out, unsigned n, bool subtype)
{
    size_t at = 0;
    for (unsigned k = 0; k < n; k += 3u) {
        out[at++] = (uint8_t)(draw(6) * 36u + (k + 1u < n ? draw(6) * 6u : 0u) + (k + 2u < n ? draw(6) : 0u));
    }
    if (subtype) {
        for (unsigned k = 0; k < n; k += 4u) {
            out[at++] = (uint8_t)draw(256);
        }
    }
    return at;
}

/* One MSRP Message of one vector (IEEE 802.1Q-2018 35.2.2). */
static size_t msrp_message(uint8_t *out)
{
    static const uint8_t types[] = {MSRP_ATTR_TYPE_TALKER_ADV, MSRP_ATTR_TYPE_TALKER_FAILED,
                                    MSRP_ATTR_TYPE_LISTENER, MSRP_ATTR_TYPE_DOMAIN};
    const uint8_t type = types[draw(4)];
    const uint8_t alen = app->ops->attr_len(type);
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
    at += events(out + at, n, type == MSRP_ATTR_TYPE_LISTENER);
    out[at++] = 0u; out[at++] = 0u;
    const bool leaveall = draw(12) == 0u;
    out[0] = type; out[1] = alen;
    out[2] = (uint8_t)((at - 4u) >> 8); out[3] = (uint8_t)(at - 4u);
    out[4] = (uint8_t)(((leaveall ? 0x2000u : 0u) | n) >> 8); out[5] = (uint8_t)n;
    return at;
}

/* One Message of one vector for an application without AttributeListLength. */
static size_t plain_message(uint8_t *out)
{
    uint8_t type, value[6] = {0};
    unsigned n = 1u + draw(5);
    if (kind == KIND_MVRP) {
        type = MVRP_ATTR_TYPE_VID;
        const unsigned vid = draw(3) * 256u + 1u + draw(10);
        value[0] = (uint8_t)(vid >> 8); value[1] = (uint8_t)vid;
    } else if (kind == KIND_MMRP) {
        type = draw(3) == 0u ? MMRP_ATTR_TYPE_SVC : MMRP_ATTR_TYPE_MAC;
        if (type == MMRP_ATTR_TYPE_SVC) {
            value[0] = (uint8_t)draw(2);
            n = 1u + draw(2);
        } else {
            value[0] = 0x01u; value[1] = 0x00u; value[2] = 0x5eu; value[5] = (uint8_t)draw(12);
        }
    } else {
        type = tie_types[draw(sizeof(tie_types))];
        value[0] = (uint8_t)draw(24);
    }
    const uint8_t alen = app->ops->attr_len(type);
    size_t at = 0;
    out[at++] = type; out[at++] = alen;
    const bool leaveall = draw(12) == 0u;
    out[at++] = (uint8_t)(((leaveall ? 0x2000u : 0u) | n) >> 8); out[at++] = (uint8_t)n;
    memcpy(out + at, value, alen);
    at += alen;
    at += events(out + at, n, app->ops->attr_has_subtype && app->ops->attr_has_subtype(type));
    out[at++] = 0u; out[at++] = 0u;
    return at;
}

static size_t random_pdu(uint8_t *pdu)
{
    size_t len = 1u;
    pdu[0] = draw(20) == 0u ? 1u : 0u;
    for (unsigned m = 1u + draw(3); m != 0u; --m) {
        len += kind == KIND_MSRP ? msrp_message(pdu + len) : plain_message(pdu + len);
    }
    pdu[len++] = 0u; pdu[len++] = 0u;
    if (draw(40) == 0u) {
        len -= 1u + draw((unsigned)len - 3u); /* truncated */
    }
    return len;
}

/* ---- local declarations ---------------------------------------------- */

static void local_value(uint8_t *type, uint8_t *value)
{
    memset(value, 0, 48);
    switch (kind) {
    case KIND_MSRP: {
        const uint32_t which = draw(5);
        if (which < 2u) {
            struct msrp_talker_adv t = {0};
            stream_id(t.stream_id.bytes);
            t.dest_mac[0] = 0x91u; t.dest_mac[5] = (uint8_t)draw(3);
            t.vlan_id = 2u; t.max_frame_size = (uint16_t)(64u + 8u * draw(3)); t.max_interval_frames = 1u;
            t.priority_and_rank = 0x70u;
            if (which == 0u) {
                *type = MSRP_ATTR_TYPE_TALKER_ADV;
                memcpy(value, &t, sizeof(t));
            } else {
                struct msrp_talker_failed f = {0};
                f.talker = t;
                f.failure_info[8] = (uint8_t)(1u + draw(3));
                *type = MSRP_ATTR_TYPE_TALKER_FAILED;
                memcpy(value, &f, sizeof(f));
            }
        } else if (which < 4u) {
            *type = MSRP_ATTR_TYPE_LISTENER;
            stream_id(value);
            value[8] = (uint8_t)(1u + draw(3));
        } else {
            struct msrp_domain d = {(uint8_t)(6u + draw(2)), 3u, (uint16_t)(2u + draw(2))};
            *type = MSRP_ATTR_TYPE_DOMAIN;
            memcpy(value, &d, sizeof(d));
        }
        break;
    }
    case KIND_MVRP: {
        const unsigned vid = draw(3) * 256u + 1u + draw(10);
        *type = MVRP_ATTR_TYPE_VID;
        value[0] = (uint8_t)(vid >> 8); value[1] = (uint8_t)vid;
        break;
    }
    case KIND_MMRP:
        if (draw(3) == 0u) {
            *type = MMRP_ATTR_TYPE_SVC;
            value[0] = (uint8_t)draw(2);
        } else {
            *type = MMRP_ATTR_TYPE_MAC;
            value[0] = 0x01u; value[1] = 0x00u; value[2] = 0x5eu; value[5] = (uint8_t)draw(12);
        }
        break;
    default:
        *type = tie_types[draw(sizeof(tie_types))];
        value[0] = (uint8_t)draw(24);
        value[1] = (uint8_t)draw(3);
        break;
    }
}

static int declare(uint8_t port, bool join)
{
    uint8_t type, value[48];
    local_value(&type, value);
    printf("%s port %u type %u", join ? "join" : "leave", port, type);
    hex(" ", value, value_len(type));
    printf("\n");
    if (kind == KIND_MSRP && draw(2)) {
        if (type == MSRP_ATTR_TYPE_TALKER_ADV) {
            struct msrp_talker_adv t;
            memcpy(&t, value, sizeof(t));
            return join ? msrp_declare_talker(app, port, &t, draw(2) != 0u) :
                          msrp_withdraw_talker(app, port, &t.stream_id);
        }
        if (type == MSRP_ATTR_TYPE_LISTENER) {
            struct msrp_stream_id id;
            memcpy(id.bytes, value, 8);
            return join ? msrp_declare_listener(app, port, &id, (enum msrp_listener_decl)value[8]) :
                          msrp_withdraw_listener(app, port, &id);
        }
    }
    if (kind == KIND_MVRP && draw(2)) {
        const uint16_t vid = (uint16_t)(value[0] << 8 | value[1]);
        return join ? mvrp_declare(app, port, vid) : mvrp_withdraw(app, port, vid);
    }
    if (kind == KIND_MMRP && draw(2)) {
        if (type == MMRP_ATTR_TYPE_SVC) {
            return join ? mmrp_declare_svc(app, port, value[0]) : mmrp_withdraw_svc(app, port, value[0]);
        }
        struct mmrp_mac mac;
        memcpy(mac.addr, value, 6);
        return join ? mmrp_declare_mac(app, port, &mac) : mmrp_withdraw_mac(app, port, &mac);
    }
    return join ? mrp_mad_join(app, port, type, value, draw(2) != 0u) : mrp_mad_leave(app, port, type, value);
}

/* ---- the run ---------------------------------------------------------- */

static void state_digest(unsigned long step)
{
    digest = UINT64_C(0xcbf29ce484222325);
    for (uint8_t p = 0; p < n_ports; ++p) {
        int count = mrp_attr_visit(app, p, visited, NULL);
        enum mrp_la_state la;
        enum mrp_pt_state pt;
        (void)mrp_port_status(app, p, &la, &pt);
        const int head[3] = {count, (int)la, (int)pt};
        mix(head, sizeof(head));
    }
    printf("S %lu %016llx live %lu\n", step, (unsigned long long)digest, live);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: mad_trace <seed> <steps>\n");
        return 2;
    }
    const unsigned long seed = strtoul(argv[1], NULL, 0);
    rng = (uint32_t)seed * 2654435761u + 7u;
    const unsigned long steps = strtoul(argv[2], NULL, 0);
    kind = (enum kind)(seed % KINDS);
    n_ports = (uint8_t)(1u + draw(kind == KIND_MSRP || kind == KIND_TIE ? 3u : 2u));
    fail_every = draw(3) == 0u ? 40u + draw(200) : 0u;
    refuse_every = draw(2) == 0u ? 2u + draw(6) : 0u;
    const bool filter = draw(2) != 0u;
    printf("seed %lu %s ports %u fail %u refuse %u filter %u\n", seed, kind_names[kind], n_ports, fail_every,
           refuse_every, filter);
    const uint32_t saved_fail = fail_every;
    fail_every = 0u;
    switch (kind) {
    case KIND_MSRP: app = msrp_app_create(n_ports, &msrp_context); break;
    case KIND_MVRP: mvrp_context.on_vlan_registered = on_vlan_registered;
                    mvrp_context.on_vlan_deregistered = on_vlan_deregistered;
                    app = mvrp_app_create(n_ports, &mvrp_context); break;
    case KIND_MMRP: app = mmrp_app_create(n_ports, &mmrp_context); break;
    default:        app = tie_create(n_ports); break;
    }
    if (!app) {
        printf("create failed\n");
        return 1;
    }
    for (uint8_t p = 0; p < n_ports; ++p) {
        const uint32_t join = 2u + draw(20);
        const int r = mrp_port_configure(app, p, join, join * 2u + 6u + draw(80), 40u + draw(1200), draw(1000),
                                         draw(2) != 0u);
        printf("configure %u rc %d\n", p, r);
    }
    mrp_set_observer(app, observed, NULL);
    if (filter) {
        mrp_set_rx_filter(app, filtered, NULL);
    }
    fail_every = saved_fail;
    uint8_t pdu[1600], buffer[2048];
    memset(buffer, 0xa5, sizeof(buffer));
    for (unsigned long step = 0; step < steps; ++step) {
        const uint32_t what = draw(64);
        const uint8_t port = (uint8_t)draw(n_ports);
        int r = 0;
        if (what < 22u) {
            const size_t len = random_pdu(pdu);
            printf("rx port %u", port);
            hex(" ", pdu, len);
            printf("\n");
            r = mrp_rx(app, port, pdu, len);
        } else if (what < 32u) {
            r = declare(port, true);
        } else if (what < 37u) {
            r = declare(port, false);
        } else if (what < 49u) {
            static const size_t capacities[] = {3u, 24u, 60u, 120u, 300u, 1500u, 2048u};
            const size_t capacity = capacities[draw(7)];
            printf("transmit port %u capacity %zu\n", port, capacity);
            r = mrp_transmit(app, port, buffer, capacity, sent, NULL);
            /* The whole buffer, as a failed build leaves it too. */
            digest = UINT64_C(0xcbf29ce484222325);
            mix(buffer, sizeof(buffer));
            printf("buffer %016llx\n", (unsigned long long)digest);
        } else if (what < 58u) {
            const uint32_t n = what < 56u ? 1u + draw(30) : 50u + draw(300);
            printf("tick %u\n", n);
            for (uint32_t k = 0; k < n; ++k) {
                shlan_timer_tick();
            }
        } else if (what < 61u) {
            printf("reclaim port %u\n", port);
            r = (int)mrp_reclaim(app, port);
        } else if (what < 62u) {
            const bool flush = draw(2) != 0u;
            printf("role port %u flush %u\n", port, flush);
            mrp_port_role_change(app, port, flush);
        } else if (what < 63u) {
            const bool enable = draw(2) != 0u;
            printf("periodic port %u %u\n", port, enable);
            mrp_set_periodic(app, port, enable);
        } else {
            uint8_t type, value[48];
            local_value(&type, value);
            printf("registered type %u", type);
            hex(" ", value, value_len(type));
            r = (int)mrp_attr_registered_ports(app, type, value);
            printf("\n");
        }
        printf("rc %d\n", r);
        state_digest(step);
    }
    fail_every = 0u;
    printf("destroy\n");
    switch (kind) {
    case KIND_MSRP: msrp_app_destroy(app); break;
    case KIND_MVRP: mvrp_app_destroy(app); break;
    case KIND_MMRP: mmrp_app_destroy(app); break;
    default:        mrp_app_destroy(app); break;
    }
    for (unsigned k = 0; k < 2000u; ++k) {
        shlan_timer_tick();
    }
    printf("END allocations %lu releases %lu live %lu sends %lu\n", allocations, releases, live, sends);
    return 0;
}
