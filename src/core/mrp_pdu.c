/* SPDX-License-Identifier: Apache-2.0 */
/*
 * MRPDU encode / decode — IEEE 802.1Q-2018 §10.8.
 *
 * Format recap (§10.8.1.2):
 *   MRPDU         = ProtocolVersion, Message {, Message}, EndMark
 *   Message       = AttributeType, AttributeLength
 *                   [, AttributeListLength], AttributeList
 *   AttributeList = VectorAttribute {, VectorAttribute}, EndMark
 *   VectorAttribute = VectorHeader, FirstValue {, Vector}
 */

#include "shish_lan/error.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"

/* ------------------------------------------------------------------ */
/* Helpers                                                              */
/* ------------------------------------------------------------------ */

static int put_u8(uint8_t *buf, size_t len, uint8_t v)
{
    if (len < 1) {
        return -SHLAN_ERROR_NO_BUFFER;
    }
    buf[0] = v;
    return 1;
}

static int put_u16be(uint8_t *buf, size_t len, uint16_t v)
{
    if (len < 2) {
        return -SHLAN_ERROR_NO_BUFFER;
    }
    buf[0] = (uint8_t)(v >> 8);
    buf[1] = (uint8_t)(v & 0xFF);
    return 2;
}

static int get_u16be(const uint8_t *buf, size_t len, uint16_t *out)
{
    if (len < 2) {
        return -SHLAN_ERROR_INVALID;
    }
    *out = (uint16_t)((buf[0] << 8) | buf[1]);
    return 2;
}

/* ------------------------------------------------------------------ */
/* mrpdu_encode_begin — §10.8.2.1                                      */
/* ------------------------------------------------------------------ */

int mrpdu_encode_begin(uint8_t *buf, size_t buf_len, uint8_t proto_version)
{
    return put_u8(buf, buf_len, proto_version);
}

/* ------------------------------------------------------------------ */
/* mrpdu_encode_end — §10.8.2.9                                        */
/* ------------------------------------------------------------------ */

int mrpdu_encode_end(uint8_t *buf, size_t buf_len)
{
    return put_u16be(buf, buf_len, MRP_ENDMARK);
}

/* ------------------------------------------------------------------ */
/* mrpdu_encode_vector — encode one VectorAttribute (§10.8.2.8)        */
/* ------------------------------------------------------------------ */

int mrpdu_encode_vector(uint8_t *buf, size_t buf_len,
                        uint8_t la_event,
                        enum mrp_attr_event attr_event,
                        const uint8_t *first_value, uint8_t fv_len)
{
    if (fv_len == 0 || !first_value) {
        return -SHLAN_ERROR_INVALID;
    }

    /* VectorHeader: 2 octets */
    uint16_t vh = mrp_vh_encode(la_event, 1u);
    size_t need = 2u /* VH */ + fv_len + 1u /* one ThreePacked byte */;
    if (buf_len < need) {
        return -SHLAN_ERROR_NO_BUFFER;
    }

    int off = 0;
    int r;

    r = put_u16be(buf + off, buf_len - (size_t)off, vh);
    if (r < 0) return r;
    off += r;

    memcpy(buf + off, first_value, fv_len);
    off += fv_len;

    /*
     * Pack the single event into a ThreePacked byte.
     * Remaining two slots are padded with Mt (4), which is a no-op
     * for recipients when NumberOfValues == 1.
     */
    buf[off++] = mrp_three_pack((uint8_t)attr_event, 4u, 4u);

    return off;
}

/* ------------------------------------------------------------------ */
/* mrpdu_parse — §10.8.3                                               */
/* ------------------------------------------------------------------ */

/* Validate the complete PDU before delivering any event. IEEE 802.1Q
 * 10.8.3 supplies the length and vector rules. Higher-version extensions
 * are skipped at their Message or VectorAttribute boundary (10.8.3.5). */
static int parse_pass(const uint8_t *pdu, size_t len,
                      const struct mrp_app_ops *ops,
                      mrpdu_on_attr_fn on_attr,
                      mrpdu_on_leaveall_fn on_leaveall, void *ctx)
{
    if (!pdu || len < 3 || !ops || !ops->attr_len || !ops->decode_attr) {
        return -SHLAN_ERROR_INVALID;
    }
    bool later = pdu[0] > ops->proto_version;
    size_t off = 1; /* Later versions retain the common message format. */
    while (off + 2 <= len) {
        uint8_t type = pdu[off++];
        uint8_t alen = pdu[off++];
        if (type == 0 && alen == 0) {
            return 0;
        }
        size_t end = len;
        bool msrp = ops->ethertype == MRP_ETHERTYPE_MSRP;
        if (msrp) {
            uint16_t count;
            if (get_u16be(pdu + off, len - off, &count) < 0 || count < 2) {
                return -SHLAN_ERROR_INVALID;
            }
            off += 2;
            end = count > len - off ? len : off + count;
        }
        uint8_t expected = ops->attr_len(type);
        bool unknown = !expected && later;
        if ((!expected && !unknown) || !alen || (expected && expected != alen)) {
            return -SHLAN_ERROR_INVALID;
        }
        bool ended = false;
        bool vector_seen = false;
        while (off + 2 <= end) {
            uint16_t vh = 0;
            (void)get_u16be(pdu + off, end - off, &vh);
            off += 2;
            if (vh == 0) {
                ended = true;
                break;
            }
            unsigned la = mrp_vh_la(vh);
            unsigned count = mrp_vh_nv(vh);
            bool subtype = !unknown && ops->attr_has_subtype && ops->attr_has_subtype(type);
            size_t events = (count + 2u) / 3u;
            size_t subtypes = subtype ? (count + 3u) / 4u : 0;
            size_t need = alen + events + subtypes;
            if (need > end - off) {
                return -SHLAN_ERROR_INVALID;
            }
            const uint8_t *fv = pdu + off;
            const uint8_t *ev = fv + alen;
            const uint8_t *sub = ev + events;
            off += need;
            vector_seen = true;
            bool unknown_event = la > MRP_LA_ALL;
            for (size_t k = 0; k < events; ++k) {
                unknown_event = unknown_event || ev[k] > 215u;
            }
            if (unknown || (later && unknown_event)) {
                continue;
            }
            if (unknown_event) {
                return -SHLAN_ERROR_INVALID;
            }
            if (la && on_leaveall) {
                on_leaveall(ctx, type);
            }
            for (unsigned k = 0; k < count; ++k) {
                uint8_t e[3];
                _Alignas(max_align_t) uint8_t value[64] = {0};
                mrp_three_unpack(ev[k / 3u], &e[0], &e[1], &e[2]);
                int r = ops->decode_attr(type, k, fv, alen, value);
                if (r < 0) {
                    return r; /* The validation pass rejects the complete PDU. */
                }
                if (subtype) {
                    uint8_t decl[4];
                    mrp_four_unpack(sub[k / 4u], &decl[0], &decl[1], &decl[2], &decl[3]);
                    if (decl[k % 4u] == 0) {
                        continue; /* 35.2.2.7.2 Ignore occupies no registrar. */
                    }
                    value[alen] = decl[k % 4u];
                }
                if (on_attr) {
                    on_attr(ctx, type, (enum mrp_attr_event)e[k % 3u], value);
                }
            }
        }
        /* 10.8.1.2(f): the actual PDU end is also an EndMark. */
        if (vector_seen && off == len) {
            return 0;
        }
        if (!ended || (msrp && off != end)) {
            return -SHLAN_ERROR_INVALID;
        }
    }
    return off == len ? 0 : -SHLAN_ERROR_INVALID;
}

int mrpdu_parse(const uint8_t *pdu, size_t len,
                const struct mrp_app_ops *ops,
                mrpdu_on_attr_fn on_attr,
                mrpdu_on_leaveall_fn on_leaveall, void *ctx)
{
    int r = parse_pass(pdu, len, ops, NULL, NULL, NULL);
    if (r < 0) {
        return r;
    }
    return parse_pass(pdu, len, ops, on_attr, on_leaveall, ctx);
}
