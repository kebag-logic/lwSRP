/* SPDX-License-Identifier: Apache-2.0 */
/*
 * MMRP application adapter — IEEE 802.1Q-2018, §10.9–10.12.
 *
 * Two attribute types (§10.12.1):
 *   Type 1 (SVC): 1-octet service requirement
 *   Type 2 (MAC): 6-octet MAC address
 */

#include "shish_lan/error.h"
#include <stdint.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mmrp.h"

/* ------------------------------------------------------------------ */
/* struct mrp_app_ops callbacks                                             */
/* ------------------------------------------------------------------ */

static void mmrp_join_ind(struct mrp_app *app, uint8_t port_id,
                          uint8_t attr_type, const void *attr_val, bool is_new)
{
    struct mmrp_ctx *ctx = (struct mmrp_ctx *)app->ops->ctx;
    (void)is_new; /* MMRP does not use the "new" declaration (§10.3 NOTE) */

    switch (attr_type) {
    case MMRP_ATTR_TYPE_MAC:
        if (ctx->on_mac_registered)
            ctx->on_mac_registered(ctx, port_id, (const struct mmrp_mac *)attr_val);
        break;
    case MMRP_ATTR_TYPE_SVC:
        if (ctx->on_svc_registered)
            ctx->on_svc_registered(ctx, port_id, *(const uint8_t *)attr_val);
        break;
    default:
        break;
    }
}

static void mmrp_leave_ind(struct mrp_app *app, uint8_t port_id,
                           uint8_t attr_type, const void *attr_val)
{
    struct mmrp_ctx *ctx = (struct mmrp_ctx *)app->ops->ctx;

    switch (attr_type) {
    case MMRP_ATTR_TYPE_MAC:
        if (ctx->on_mac_deregistered)
            ctx->on_mac_deregistered(ctx, port_id, (const struct mmrp_mac *)attr_val);
        break;
    case MMRP_ATTR_TYPE_SVC:
        if (ctx->on_svc_deregistered)
            ctx->on_svc_deregistered(ctx, port_id, *(const uint8_t *)attr_val);
        break;
    default:
        break;
    }
}

static int mmrp_encode_attr(uint8_t attr_type, const void *attr_val,
                            uint8_t *buf, size_t buf_len)
{
    uint8_t alen;
    switch (attr_type) {
    case MMRP_ATTR_TYPE_SVC: alen = MMRP_ATTR_LEN_SVC; break;
    case MMRP_ATTR_TYPE_MAC: alen = MMRP_ATTR_LEN_MAC; break;
    default: return -SHLAN_ERROR_INVALID;
    }
    if (buf_len < alen) {
        return -SHLAN_ERROR_NO_BUFFER;
    }
    memcpy(buf, attr_val, alen);
    return alen;
}

/*
 * decode_attr: SVC is 1 octet (no increment across vector).
 *             MAC is 6 octets; vector offset increments the LSB (§10.12.1).
 */
static int mmrp_decode_attr(uint8_t attr_type, uint32_t offset,
                            const uint8_t *buf, size_t buf_len,
                            void *attr_val_out)
{
    switch (attr_type) {
    case MMRP_ATTR_TYPE_SVC:
        if (buf_len < MMRP_ATTR_LEN_SVC) {
            return -SHLAN_ERROR_INVALID;
        }
        *(uint8_t *)attr_val_out = buf[0]; /* service values not incremented */
        return MMRP_ATTR_LEN_SVC;

    case MMRP_ATTR_TYPE_MAC: {
        if (buf_len < MMRP_ATTR_LEN_MAC) {
            return -SHLAN_ERROR_INVALID;
        }
        uint8_t *out = (uint8_t *)attr_val_out;
        memcpy(out, buf, MMRP_ATTR_LEN_MAC);
        /* Increment 6-octet big-endian MAC by offset */
        uint32_t carry = offset;
        for (int b = MMRP_ATTR_LEN_MAC - 1; b >= 0 && carry; b--) {
            carry += out[b];
            out[b] = (uint8_t)carry;
            carry >>= 8;
        }
        if (carry) {
            return -SHLAN_ERROR_RANGE;
        }
        return MMRP_ATTR_LEN_MAC;
    }
    default:
        return -SHLAN_ERROR_INVALID;
    }
}

static uint8_t mmrp_attr_len(uint8_t attr_type)
{
    switch (attr_type) {
    case MMRP_ATTR_TYPE_SVC: return MMRP_ATTR_LEN_SVC;
    case MMRP_ATTR_TYPE_MAC: return MMRP_ATTR_LEN_MAC;
    default: return 0;
    }
}

static int mmrp_attr_cmp(uint8_t attr_type, const void *a, const void *b)
{
    return memcmp(a, b, mmrp_attr_len(attr_type));
}

static const uint8_t mmrp_group_addr[6] = MRP_ADDR_MMRP;

static const struct mrp_app_ops mmrp_ops_tmpl = {
    .join_ind      = mmrp_join_ind,
    .leave_ind     = mmrp_leave_ind,
    .encode_attr   = mmrp_encode_attr,
    .decode_attr   = mmrp_decode_attr,
    .attr_len      = mmrp_attr_len,
    .attr_cmp      = mmrp_attr_cmp,
    .ethertype     = MRP_ETHERTYPE_MMRP,
    .proto_version = MRP_PROTOCOL_VERSION,
};

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

struct mrp_app *mmrp_app_create(uint8_t n_ports, struct mmrp_ctx *ctx)
{
    struct mrp_app_ops ops = mmrp_ops_tmpl;
    memcpy(ops.group_addr, mmrp_group_addr, 6);
    ops.ctx = ctx;
    return mrp_app_create(&ops, n_ports);
}

void mmrp_app_destroy(struct mrp_app *app)
{
    mrp_app_destroy(app);
}

int mmrp_declare_mac(struct mrp_app *app, uint8_t port_id, const struct mmrp_mac *mac)
{
    return mrp_mad_join(app, port_id, MMRP_ATTR_TYPE_MAC, mac, false);
}

int mmrp_withdraw_mac(struct mrp_app *app, uint8_t port_id, const struct mmrp_mac *mac)
{
    return mrp_mad_leave(app, port_id, MMRP_ATTR_TYPE_MAC, mac);
}

int mmrp_declare_svc(struct mrp_app *app, uint8_t port_id, uint8_t svc)
{
    return mrp_mad_join(app, port_id, MMRP_ATTR_TYPE_SVC, &svc, false);
}

int mmrp_withdraw_svc(struct mrp_app *app, uint8_t port_id, uint8_t svc)
{
    return mrp_mad_leave(app, port_id, MMRP_ATTR_TYPE_SVC, &svc);
}
