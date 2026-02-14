/*
 * MVRP application adapter — IEEE 802.1Q-2018, §11.2.
 *
 * Plugs into the MRP base via struct mrp_app_ops.
 * Attribute type 1: VID (2 octets, big-endian).
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mvrp.h"

/* ------------------------------------------------------------------ */
/* struct mrp_app_ops callbacks                                             */
/* ------------------------------------------------------------------ */

static void mvrp_join_ind(struct mrp_app *app, uint8_t port_id,
                          uint8_t attr_type, const void *attr_val, bool is_new)
{
    struct mvrp_ctx *ctx = (struct mvrp_ctx *)app->ops->ctx;
    if (attr_type != MVRP_ATTR_TYPE_VID || !ctx->on_vlan_registered) return;

    const uint8_t *v = (const uint8_t *)attr_val;
    uint16_t vid = (uint16_t)((v[0] << 8) | v[1]);
    ctx->on_vlan_registered(ctx, port_id, vid, is_new);
}

static void mvrp_leave_ind(struct mrp_app *app, uint8_t port_id,
                           uint8_t attr_type, const void *attr_val)
{
    struct mvrp_ctx *ctx = (struct mvrp_ctx *)app->ops->ctx;
    if (attr_type != MVRP_ATTR_TYPE_VID || !ctx->on_vlan_deregistered) return;

    const uint8_t *v = (const uint8_t *)attr_val;
    uint16_t vid = (uint16_t)((v[0] << 8) | v[1]);
    ctx->on_vlan_deregistered(ctx, port_id, vid);
}

static int mvrp_encode_attr(uint8_t attr_type, const void *attr_val,
                            uint8_t *buf, size_t buf_len)
{
    if (attr_type != MVRP_ATTR_TYPE_VID) return -EINVAL;
    if (buf_len < MVRP_ATTR_LEN_VID) return -ENOBUFS;
    memcpy(buf, attr_val, MVRP_ATTR_LEN_VID);
    return MVRP_ATTR_LEN_VID;
}

/*
 * decode_attr: FirstValue is 2-octet big-endian VID.
 * Attribute at vector offset i = FirstValue + i (§10.8.2.7).
 */
static int mvrp_decode_attr(uint8_t attr_type, uint32_t offset,
                            const uint8_t *buf, size_t buf_len,
                            void *attr_val_out)
{
    if (attr_type != MVRP_ATTR_TYPE_VID) return -EINVAL;
    if (buf_len < MVRP_ATTR_LEN_VID) return -EINVAL;

    uint16_t vid = (uint16_t)(((uint16_t)buf[0] << 8) | buf[1]);
    vid = (uint16_t)(vid + (uint16_t)offset);
    if (vid < MVRP_VID_MIN || vid > MVRP_VID_MAX) return -ERANGE;

    uint8_t *out = (uint8_t *)attr_val_out;
    out[0] = (uint8_t)(vid >> 8);
    out[1] = (uint8_t)(vid & 0xFF);
    return MVRP_ATTR_LEN_VID;
}

static uint8_t mvrp_attr_len(uint8_t attr_type)
{
    (void)attr_type;
    return MVRP_ATTR_LEN_VID;
}

static int mvrp_attr_cmp(uint8_t attr_type, const void *a, const void *b)
{
    (void)attr_type;
    return memcmp(a, b, MVRP_ATTR_LEN_VID);
}

static const uint8_t mvrp_group_addr[6] = MRP_ADDR_MVRP;

static const struct mrp_app_ops mvrp_ops_tmpl = {
    .join_ind      = mvrp_join_ind,
    .leave_ind     = mvrp_leave_ind,
    .encode_attr   = mvrp_encode_attr,
    .decode_attr   = mvrp_decode_attr,
    .attr_len      = mvrp_attr_len,
    .attr_cmp      = mvrp_attr_cmp,
    .ethertype     = MRP_ETHERTYPE_MVRP,
    .proto_version = MRP_PROTOCOL_VERSION,
    /* group_addr and ctx filled at create time */
};

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

struct mrp_app *mvrp_app_create(uint8_t n_ports, struct mvrp_ctx *ctx)
{
    struct mrp_app_ops ops = mvrp_ops_tmpl;
    memcpy(ops.group_addr, mvrp_group_addr, 6);
    ops.ctx = ctx;
    return mrp_app_create(&ops, n_ports); /* mrp_app_create copies ops */
}

void mvrp_app_destroy(struct mrp_app *app)
{
    mrp_app_destroy(app);
}

int mvrp_declare(struct mrp_app *app, uint8_t port_id, uint16_t vid)
{
    uint8_t val[MVRP_ATTR_LEN_VID] = { (uint8_t)(vid >> 8),
                                        (uint8_t)(vid & 0xFF) };
    return mrp_mad_join(app, port_id, MVRP_ATTR_TYPE_VID, val, false);
}

int mvrp_withdraw(struct mrp_app *app, uint8_t port_id, uint16_t vid)
{
    uint8_t val[MVRP_ATTR_LEN_VID] = { (uint8_t)(vid >> 8),
                                        (uint8_t)(vid & 0xFF) };
    return mrp_mad_leave(app, port_id, MVRP_ATTR_TYPE_VID, val);
}
