/* SPDX-License-Identifier: Apache-2.0 */
/*
 * MSRP application adapter — IEEE 802.1Q-2018, §35.
 *
 * Three attribute types (§35.2.1):
 *   Type 1: Talker Advertise  (25 octets)
 *   Type 2: Talker Failed     (34 octets = 25 + 9)
 *   Type 3: Listener          (8-octet stream ID + FourPackedType declaration)
 *
 * MSRP differs from MVRP/MMRP:
 *   - AttributeListLength IS present in the Message header (§10.8.2.4).
 *   - Listener attributes carry a FourPackedEvents subtype vector after
 *     the ThreePackedEvents (§35.2.2.7.2): attr_has_subtype tells
 *     mrpdu_parse to decode it, and the declaration type arrives as the
 *     9th attr_val octet (see msrp_join_ind).
 *   - EtherType: 0x22EA.
 *
 * Talker attribute values are converted between wire big-endian and the
 * host-endian struct msrp_talker_adv fields here (encode/decode_attr).
 */

#include "shish_lan/error.h"
#include <stdint.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"
#include "shish_lan/msrp.h"

/* ------------------------------------------------------------------ */
/* Attribute sizes (§35.2.1)                                           */
/* ------------------------------------------------------------------ */

#define MSRP_ATTR_LEN_TALKER_ADV    25u
#define MSRP_ATTR_LEN_TALKER_FAILED 34u
#define MSRP_ATTR_LEN_DOMAIN         4u
#define MSRP_ATTR_LEN_LISTENER       8u  /* stream ID only; decl in FourPacked */

/* ------------------------------------------------------------------ */
/* struct mrp_app_ops callbacks                                             */
/* ------------------------------------------------------------------ */

static void msrp_join_ind(struct mrp_app *app, uint8_t port_id,
                          uint8_t attr_type, const void *attr_val, bool is_new)
{
    struct msrp_ctx *ctx = (struct msrp_ctx *)app->ops->ctx;

    switch (attr_type) {
    case MSRP_ATTR_TYPE_DOMAIN:
        if (ctx->on_domain) {
            ctx->on_domain(ctx, port_id, attr_val, is_new);
        }
        break;
    case MSRP_ATTR_TYPE_TALKER_ADV:
        if (ctx->on_talker_advertise) {
            ctx->on_talker_advertise(ctx, port_id,
                                     (const struct msrp_talker_adv *)attr_val,
                                     is_new);
        }
        break;
    case MSRP_ATTR_TYPE_TALKER_FAILED:
        if (ctx->on_talker_failed) {
            ctx->on_talker_failed(ctx, port_id,
                                  (const struct msrp_talker_failed *)attr_val,
                                  is_new);
        }
        break;
    case MSRP_ATTR_TYPE_LISTENER: {
        /*
         * Listener attr_val = stream_id (8 bytes) || decl byte.
         * The declaration type was decoded from FourPackedEvents and
         * stored as the 9th byte by decode_attr.
         */
        const uint8_t *v = (const uint8_t *)attr_val;
        struct msrp_stream_id sid;
        memcpy(sid.bytes, v, 8);
        enum msrp_listener_decl decl = (enum msrp_listener_decl)v[8];
        if (ctx->on_listener) {
            ctx->on_listener(ctx, port_id, &sid, decl, is_new);
        }
        break;
    }
    default:
        break;
    }

    /* MAP propagation is handled by mrp_app_ops.map_join — see msrp_map_join. */
}

static void msrp_leave_ind(struct mrp_app *app, uint8_t port_id,
                           uint8_t attr_type, const void *attr_val)
{
    struct msrp_ctx *ctx = (struct msrp_ctx *)app->ops->ctx;
    if (ctx->on_leave) {
        ctx->on_leave(ctx, port_id, attr_type, attr_val);
    }
    /* MAP propagation is handled by mrp_app_ops.map_leave — see msrp_map_leave. */
}

/* ------------------------------------------------------------------ */
/* MAP policy — §35.2.3                                                */
/* ------------------------------------------------------------------ */

/*
 * Build a bitmask of every port except src_port.
 */
static uint32_t all_ports_except(const struct mrp_app *app, uint8_t src_port)
{
    uint8_t  n    = mrp_app_n_ports(app);
    uint32_t mask = 0;
    for (uint8_t p = 0; p < n && p < 32u; p++) {
        if (p != src_port) {
            mask |= (1u << p);
        }
    }
    return mask;
}

/*
 * msrp_map_join — §35.2.3 propagation rules on registration.
 *
 * Talker Advertise / Talker Failed (§35.2.3 bridge component):
 *   Flood to every port except the port of registration.
 *
 * Listener (§35.2.3):
 *   Propagate only toward the talker — re-declare on every port where the
 *   Talker Advertise or Talker Failed for the same StreamID is registered
 *   (Registrar IN), excluding the port the Listener arrived on.
 *   This routes the listener declaration back toward the stream source.
 *
 * Domain (type 4) and any unknown attribute types:
 *   Not propagated — domain attributes are per-port administrative state
 *   and must not be relayed between ports.
 *
 * TODO: once RSTP is integrated, gate the returned bitmask on port role
 *       so that only Designated ports are included (§10.3, MAP domain).
 */
static uint32_t msrp_map_join(const struct mrp_app *app, uint8_t src_port,
                              uint8_t attr_type, const void *attr_val)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:
    case MSRP_ATTR_TYPE_TALKER_FAILED:
        return all_ports_except(app, src_port);

    case MSRP_ATTR_TYPE_LISTENER: {
        /*
         * The StreamID occupies the first 8 bytes of every MSRP attribute
         * value, so passing attr_val directly to mrp_attr_registered_ports
         * with a Talker type works: attr_cmp compares the first 8 bytes.
         */
        uint32_t talker_ports =
            mrp_attr_registered_ports(app, MSRP_ATTR_TYPE_TALKER_ADV,    attr_val) |
            mrp_attr_registered_ports(app, MSRP_ATTR_TYPE_TALKER_FAILED,  attr_val);
        return talker_ports & all_ports_except(app, src_port);
    }

    default:
        return 0u;
    }
}

/*
 * msrp_map_leave — §35.2.3 propagation rules on deregistration.
 *
 * Talker Advertise / Talker Failed:
 *   Withdraw from every port except src_port.
 *
 * Listener:
 *   Withdraw from every port except src_port.  mrp_mad_leave is a no-op
 *   when the attribute is not declared on a port, so it is safe to call
 *   unconditionally — avoids a stale-talker-set problem if the talker
 *   deregistered before the listener.
 *
 * Domain / unknown:
 *   Not withdrawn.
 */
static uint32_t msrp_map_leave(const struct mrp_app *app, uint8_t src_port,
                               uint8_t attr_type, const void *attr_val)
{
    (void)attr_val;
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:
    case MSRP_ATTR_TYPE_TALKER_FAILED:
    case MSRP_ATTR_TYPE_LISTENER:
        return all_ports_except(app, src_port);

    default:
        return 0u;
    }
}

/* Wire field helpers: MRPDU FirstValue fields are big-endian (§10.8.2.7). */
static void be16_put(uint8_t *b, uint16_t v)
{
    b[0] = (uint8_t)(v >> 8);
    b[1] = (uint8_t)v;
}

static uint16_t be16_get(const uint8_t *b)
{
    return (uint16_t)(((uint16_t)b[0] << 8) | b[1]);
}

static void be32_put(uint8_t *b, uint32_t v)
{
    b[0] = (uint8_t)(v >> 24);
    b[1] = (uint8_t)(v >> 16);
    b[2] = (uint8_t)(v >> 8);
    b[3] = (uint8_t)v;
}

static uint32_t be32_get(const uint8_t *b)
{
    return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) |
           ((uint32_t)b[2] << 8) | b[3];
}

/*
 * Talker Advertise FirstValue layout (§35.2.1.3, 25 octets):
 *   StreamID 8 | DataFrameParameters 8 (DA 6, VID 2) |
 *   TSpec 4 (MaxFrameSize 2, MaxIntervalFrames 2) |
 *   PriorityAndRank 1 | AccumulatedLatency 4
 */
static void talker_to_wire(const struct msrp_talker_adv *t, uint8_t *b)
{
    memcpy(&b[0], t->stream_id.bytes, 8);
    memcpy(&b[8], t->dest_mac, 6);
    be16_put(&b[14], t->vlan_id);
    be16_put(&b[16], t->max_frame_size);
    be16_put(&b[18], t->max_interval_frames);
    b[20] = t->priority_and_rank;
    be32_put(&b[21], t->accumulated_latency);
}

static void talker_from_wire(const uint8_t *b, struct msrp_talker_adv *t)
{
    memcpy(t->stream_id.bytes, &b[0], 8);
    memcpy(t->dest_mac, &b[8], 6);
    t->vlan_id             = be16_get(&b[14]);
    t->max_frame_size      = be16_get(&b[16]);
    t->max_interval_frames = be16_get(&b[18]);
    t->priority_and_rank   = b[20];
    t->accumulated_latency = be32_get(&b[21]);
}

static int msrp_encode_attr(uint8_t attr_type, const void *attr_val,
                            uint8_t *buf, size_t buf_len)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_DOMAIN: {
        const struct msrp_domain *d = attr_val;
        if (buf_len < MSRP_ATTR_LEN_DOMAIN) {
            return -SHLAN_ERROR_NO_BUFFER;
        }
        buf[0] = d->class_id;
        buf[1] = d->priority;
        be16_put(buf + 2, d->vid);
        return MSRP_ATTR_LEN_DOMAIN;
    }
    case MSRP_ATTR_TYPE_TALKER_ADV:
        if (buf_len < MSRP_ATTR_LEN_TALKER_ADV) return -SHLAN_ERROR_NO_BUFFER;
        talker_to_wire((const struct msrp_talker_adv *)attr_val, buf);
        return MSRP_ATTR_LEN_TALKER_ADV;

    case MSRP_ATTR_TYPE_TALKER_FAILED: {
        const struct msrp_talker_failed *tf = attr_val;
        if (buf_len < MSRP_ATTR_LEN_TALKER_FAILED) return -SHLAN_ERROR_NO_BUFFER;
        talker_to_wire(&tf->talker, buf);
        memcpy(buf + MSRP_ATTR_LEN_TALKER_ADV, tf->failure_info, 9);
        return MSRP_ATTR_LEN_TALKER_FAILED;
    }

    case MSRP_ATTR_TYPE_LISTENER:
        if (buf_len < MSRP_ATTR_LEN_LISTENER) return -SHLAN_ERROR_NO_BUFFER;
        memcpy(buf, attr_val, MSRP_ATTR_LEN_LISTENER);
        return MSRP_ATTR_LEN_LISTENER;

    default:
        return -SHLAN_ERROR_INVALID;
    }
}

/* IEEE 802.1Q-2018 35.2.2.8: increment Unique ID and destination MAC. */
static void increment_stream(uint8_t *b, unsigned count, uint32_t offset)
{
    for (unsigned n = count; n > 0; --n) {
        offset += b[n - 1];
        b[n - 1] = (uint8_t)offset;
        offset >>= 8;
    }
}

static int msrp_decode_attr(uint8_t attr_type, uint32_t offset,
                            const uint8_t *buf, size_t buf_len,
                            void *attr_val_out)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_DOMAIN: {
        struct msrp_domain *d = attr_val_out;
        if (buf_len != MSRP_ATTR_LEN_DOMAIN || offset > 255u - buf[0] ||
            buf[1] > 7u || offset > 7u - buf[1]) {
            return -SHLAN_ERROR_INVALID;
        }
        d->class_id = (uint8_t)(buf[0] + offset);
        d->priority = (uint8_t)(buf[1] + offset);
        d->vid = be16_get(buf + 2);
        return MSRP_ATTR_LEN_DOMAIN;
    }
    case MSRP_ATTR_TYPE_TALKER_ADV:
    case MSRP_ATTR_TYPE_TALKER_FAILED: {
        struct msrp_talker_adv *t = attr_val_out;
        unsigned len = attr_type == MSRP_ATTR_TYPE_TALKER_ADV ?
                       MSRP_ATTR_LEN_TALKER_ADV : MSRP_ATTR_LEN_TALKER_FAILED;
        if (buf_len != len) {
            return -SHLAN_ERROR_INVALID;
        }
        talker_from_wire(buf, t);
        increment_stream(t->stream_id.bytes + 6, 2, offset);
        increment_stream(t->dest_mac, 6, offset);
        if (attr_type == MSRP_ATTR_TYPE_TALKER_FAILED) {
            struct msrp_talker_failed *tf = attr_val_out;
            memcpy(tf->failure_info, buf + MSRP_ATTR_LEN_TALKER_ADV, 9);
        }
        return (int)len;
    }
    case MSRP_ATTR_TYPE_LISTENER:
        if (buf_len != MSRP_ATTR_LEN_LISTENER) {
            return -SHLAN_ERROR_INVALID;
        }
        memcpy(attr_val_out, buf, MSRP_ATTR_LEN_LISTENER);
        increment_stream((uint8_t *)attr_val_out + 6, 2, offset);
        return MSRP_ATTR_LEN_LISTENER;
    default:
        return -SHLAN_ERROR_INVALID;
    }
}

static uint8_t msrp_attr_len(uint8_t attr_type)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_DOMAIN:        return MSRP_ATTR_LEN_DOMAIN;
    case MSRP_ATTR_TYPE_TALKER_ADV:    return MSRP_ATTR_LEN_TALKER_ADV;
    case MSRP_ATTR_TYPE_TALKER_FAILED: return MSRP_ATTR_LEN_TALKER_FAILED;
    case MSRP_ATTR_TYPE_LISTENER:      return MSRP_ATTR_LEN_LISTENER;
    default: return 0;
    }
}

/* Listener declarations ride the FourPackedEvents subtype vector. */
static bool msrp_attr_has_subtype(uint8_t attr_type)
{
    return attr_type == MSRP_ATTR_TYPE_LISTENER;
}

/*
 * In-memory sizes: talker attributes decode into host-endian structs,
 * the listener value is the 8-byte StreamID plus the declaration octet.
 */
static uint8_t msrp_attr_mem_len(uint8_t attr_type)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_DOMAIN:        return sizeof(struct msrp_domain);
    case MSRP_ATTR_TYPE_TALKER_ADV:    return sizeof(struct msrp_talker_adv);
    case MSRP_ATTR_TYPE_TALKER_FAILED: return sizeof(struct msrp_talker_failed);
    case MSRP_ATTR_TYPE_LISTENER:      return MSRP_ATTR_LEN_LISTENER + 1u;
    default: return 0;
    }
}

static int msrp_attr_cmp(uint8_t attr_type, const void *a, const void *b)
{
    /* Stream identity is determined by StreamID (first 8 bytes for all types) */
    if (attr_type == MSRP_ATTR_TYPE_DOMAIN) {
        return memcmp(a, b, sizeof(struct msrp_domain));
    }
    return memcmp(a, b, sizeof(struct msrp_stream_id));
}

static bool msrp_attr_replaces(uint8_t old_type, const void *old_value,
                               uint8_t new_type, const void *new_value)
{
    return ((old_type == MSRP_ATTR_TYPE_TALKER_ADV && new_type == MSRP_ATTR_TYPE_TALKER_FAILED) ||
            (old_type == MSRP_ATTR_TYPE_TALKER_FAILED && new_type == MSRP_ATTR_TYPE_TALKER_ADV)) &&
           memcmp(old_value,new_value,sizeof(struct msrp_stream_id)) == 0;
}

static const struct mrp_app_ops msrp_ops_tmpl = {
    .join_ind         = msrp_join_ind,
    .leave_ind        = msrp_leave_ind,
    .map_join         = msrp_map_join,
    .map_leave        = msrp_map_leave,
    .encode_attr      = msrp_encode_attr,
    .decode_attr      = msrp_decode_attr,
    .attr_len         = msrp_attr_len,
    .attr_cmp         = msrp_attr_cmp,
    .attr_has_subtype = msrp_attr_has_subtype,
    .attr_mem_len     = msrp_attr_mem_len,
    .attr_replaces    = msrp_attr_replaces,
    .ethertype        = MRP_ETHERTYPE_MSRP,
    .proto_version    = MRP_PROTOCOL_VERSION,
    /* IEEE 802.1Q-2018 35.2.2: nearest bridge group address. */
    .group_addr       = { 0x01u, 0x80u, 0xC2u, 0x00u, 0x00u, 0x0Eu },
};

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

struct mrp_app *msrp_app_create(uint8_t n_ports, struct msrp_ctx *ctx)
{
    struct mrp_app_ops ops = msrp_ops_tmpl;
    ops.ctx = ctx;
    return mrp_app_create(&ops, n_ports);
}

void msrp_app_destroy(struct mrp_app *app)
{
    mrp_app_destroy(app);
}

int msrp_declare_talker(struct mrp_app *app, uint8_t port_id,
                        const struct msrp_talker_adv *attr, bool is_new)
{
    return mrp_mad_join(app, port_id, MSRP_ATTR_TYPE_TALKER_ADV,
                        attr, is_new);
}

int msrp_declare_listener(struct mrp_app *app, uint8_t port_id,
                          const struct msrp_stream_id *stream_id,
                          enum msrp_listener_decl decl)
{
    /* Pack stream_id + decl byte into a 9-byte attr value */
    uint8_t val[9];
    memcpy(val, stream_id->bytes, 8);
    val[8] = (uint8_t)decl;
    return mrp_mad_join(app, port_id, MSRP_ATTR_TYPE_LISTENER, val, false);
}

int msrp_withdraw_talker(struct mrp_app *app, uint8_t port_id,
                         const struct msrp_stream_id *stream_id)
{
    /* Only the StreamID portion is used for matching (attr_cmp) */
    uint8_t val[MSRP_ATTR_LEN_TALKER_ADV] = {0};
    memcpy(val, stream_id->bytes, 8);
    return mrp_mad_leave(app, port_id, MSRP_ATTR_TYPE_TALKER_ADV, val);
}

int msrp_withdraw_listener(struct mrp_app *app, uint8_t port_id,
                           const struct msrp_stream_id *stream_id)
{
    uint8_t val[9] = {0};
    memcpy(val, stream_id->bytes, 8);
    return mrp_mad_leave(app, port_id, MSRP_ATTR_TYPE_LISTENER, val);
}
