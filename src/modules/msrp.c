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
 *   - Listener attributes use FourPackedEvents rather than ThreePackedEvents.
 *   - EtherType: 0x22EA.
 *
 * NOTE: Listener FourPackedEvents are NOT yet decoded in mrpdu_parse()
 *       (mrp_pdu.c uses ThreePacked for all types).  A future patch should
 *       detect MSRP Listener attrs and switch to mrp_four_unpack().
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"
#include "shish_lan/msrp.h"

/* ------------------------------------------------------------------ */
/* Attribute sizes (§35.2.1)                                           */
/* ------------------------------------------------------------------ */

#define MSRP_ATTR_LEN_TALKER_ADV    25u
#define MSRP_ATTR_LEN_TALKER_FAILED 34u
#define MSRP_ATTR_LEN_LISTENER       8u  /* stream ID only; decl in FourPacked */

/* ------------------------------------------------------------------ */
/* struct mrp_app_ops callbacks                                             */
/* ------------------------------------------------------------------ */

static void msrp_join_ind(struct mrp_app *app, uint8_t port_id,
                          uint8_t attr_type, const void *attr_val, bool is_new)
{
    struct msrp_ctx *ctx = (struct msrp_ctx *)app->ops->ctx;

    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:
        if (ctx->on_talker_advertise)
            ctx->on_talker_advertise(ctx, port_id,
                                     (const struct msrp_talker_adv *)attr_val,
                                     is_new);
        break;
    case MSRP_ATTR_TYPE_TALKER_FAILED:
        if (ctx->on_talker_failed)
            ctx->on_talker_failed(ctx, port_id,
                                  (const struct msrp_talker_failed *)attr_val,
                                  is_new);
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
        if (ctx->on_listener)
            ctx->on_listener(ctx, port_id, &sid, decl, is_new);
        break;
    }
    default:
        break;
    }
}

static void msrp_leave_ind(struct mrp_app *app, uint8_t port_id,
                           uint8_t attr_type, const void *attr_val)
{
    struct msrp_ctx *ctx = (struct msrp_ctx *)app->ops->ctx;
    if (ctx->on_leave)
        ctx->on_leave(ctx, port_id, attr_type, attr_val);
}

static int msrp_encode_attr(uint8_t attr_type, const void *attr_val,
                            uint8_t *buf, size_t buf_len)
{
    uint8_t alen;
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:    alen = MSRP_ATTR_LEN_TALKER_ADV;    break;
    case MSRP_ATTR_TYPE_TALKER_FAILED: alen = MSRP_ATTR_LEN_TALKER_FAILED;  break;
    case MSRP_ATTR_TYPE_LISTENER:      alen = MSRP_ATTR_LEN_LISTENER;       break;
    default: return -EINVAL;
    }
    if (buf_len < alen) return -ENOBUFS;
    memcpy(buf, attr_val, alen);
    return alen;
}

/*
 * decode_attr: stream attributes identified by StreamID are not "incremented"
 * across vector offsets — each value in a vector is independent (§35.2.1).
 * We therefore ignore offset and parse attr_val directly.
 */
static int msrp_decode_attr(uint8_t attr_type, uint32_t offset,
                            const uint8_t *buf, size_t buf_len,
                            void *attr_val_out)
{
    (void)offset;
    uint8_t alen;
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:    alen = MSRP_ATTR_LEN_TALKER_ADV;    break;
    case MSRP_ATTR_TYPE_TALKER_FAILED: alen = MSRP_ATTR_LEN_TALKER_FAILED;  break;
    case MSRP_ATTR_TYPE_LISTENER:      alen = MSRP_ATTR_LEN_LISTENER;       break;
    default: return -EINVAL;
    }
    if (buf_len < alen) return -EINVAL;
    memcpy(attr_val_out, buf, alen);
    return alen;
}

static uint8_t msrp_attr_len(uint8_t attr_type)
{
    switch (attr_type) {
    case MSRP_ATTR_TYPE_TALKER_ADV:    return MSRP_ATTR_LEN_TALKER_ADV;
    case MSRP_ATTR_TYPE_TALKER_FAILED: return MSRP_ATTR_LEN_TALKER_FAILED;
    case MSRP_ATTR_TYPE_LISTENER:      return MSRP_ATTR_LEN_LISTENER;
    default: return 0;
    }
}

static int msrp_attr_cmp(uint8_t attr_type, const void *a, const void *b)
{
    /* Stream identity is determined by StreamID (first 8 bytes for all types) */
    (void)attr_type;
    return memcmp(a, b, sizeof(struct msrp_stream_id));
}

static const struct mrp_app_ops msrp_ops_tmpl = {
    .join_ind      = msrp_join_ind,
    .leave_ind     = msrp_leave_ind,
    .encode_attr   = msrp_encode_attr,
    .decode_attr   = msrp_decode_attr,
    .attr_len      = msrp_attr_len,
    .attr_cmp      = msrp_attr_cmp,
    .ethertype     = MRP_ETHERTYPE_MSRP,
    .proto_version = MRP_PROTOCOL_VERSION,
    /* group_addr: MSRP uses 91:E0:F0:00:0E:80 per 802.1Q Table 10-1 */
    .group_addr    = { 0x91u, 0xE0u, 0xF0u, 0x00u, 0x0Eu, 0x80u },
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
