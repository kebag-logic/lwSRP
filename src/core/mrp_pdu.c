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

#include <errno.h>
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
    if (len < 1) return -ENOBUFS;
    buf[0] = v;
    return 1;
}

static int put_u16be(uint8_t *buf, size_t len, uint16_t v)
{
    if (len < 2) return -ENOBUFS;
    buf[0] = (uint8_t)(v >> 8);
    buf[1] = (uint8_t)(v & 0xFF);
    return 2;
}

static int get_u8(const uint8_t *buf, size_t len, uint8_t *out)
{
    if (len < 1) return -EINVAL;
    *out = buf[0];
    return 1;
}

static int get_u16be(const uint8_t *buf, size_t len, uint16_t *out)
{
    if (len < 2) return -EINVAL;
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
    if (fv_len == 0 || !first_value) return -EINVAL;

    /* VectorHeader: 2 octets */
    uint16_t vh = mrp_vh_encode(la_event, 1u);
    size_t need = 2u /* VH */ + fv_len + 1u /* one ThreePacked byte */;
    if (buf_len < need) return -ENOBUFS;

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

/*
 * Parse a single Message (§10.8.2.2) starting at buf[0].
 * Returns bytes consumed or negative errno.
 * Calls on_attr / on_leaveall for each decoded event.
 */
static int parse_message(const uint8_t *buf, size_t len,
                         const struct mrp_app_ops *ops,
                         mrpdu_on_attr_fn on_attr,
                         mrpdu_on_leaveall_fn on_leaveall,
                         void *ctx)
{
    if (len < 2) return -EINVAL;

    uint8_t  attr_type   = buf[0];
    uint8_t  attr_length = buf[1]; /* FirstValue length in octets */
    size_t   off         = 2;

    /* AttributeListLength present only when ops says so (MSRP) */
    uint16_t attr_list_len = 0;
    bool     has_all_len   = (ops && ops->ethertype == MRP_ETHERTYPE_MSRP);
    if (has_all_len) {
        if (len - off < 2) return -EINVAL;
        uint16_t tmp;
        int r = get_u16be(buf + off, len - off, &tmp);
        if (r < 0) return r;
        attr_list_len = tmp;
        off += 2;
        (void)attr_list_len; /* consumed; used only for bounds in strict mode */
    }

    /* Parse AttributeList: zero or more VectorAttributes, then EndMark */
    while (off + 2 <= len) {
        uint16_t vh;
        int r = get_u16be(buf + off, len - off, &vh);
        if (r < 0) return r;

        /* EndMark terminates AttributeList */
        if (vh == MRP_ENDMARK) { off += 2; break; }
        off += 2;

        uint8_t  la_ev    = mrp_vh_la(vh);
        uint16_t n_values = mrp_vh_nv(vh);

        if (la_ev == MRP_LA_ALL && on_leaveall)
            on_leaveall(ctx, attr_type);

        /* FirstValue must be present */
        if (off + attr_length > len) return -EINVAL;
        const uint8_t *first_val = buf + off;
        off += attr_length;

        /*
         * Vector layout: ceil(n/3) ThreePackedEvents octets carry the
         * AttributeEvents; attribute types with a subtype (the MSRP
         * Listener declaration, §35.2.2.7.2) append ceil(n/4)
         * FourPackedEvents octets after them.
         */
        bool has_subtype = (ops && ops->attr_has_subtype &&
                            ops->attr_has_subtype(attr_type));
        size_t ev_len  = ((size_t)n_values + 2u) / 3u;
        size_t sub_len = has_subtype ? (((size_t)n_values + 3u) / 4u) : 0u;

        if (off + ev_len + sub_len > len) return -EINVAL;
        const uint8_t *ev_bytes  = buf + off;
        const uint8_t *sub_bytes = buf + off + ev_len;
        off += ev_len + sub_len;

        for (uint32_t i = 0; i < n_values; i++) {
            uint8_t e[3];
            mrp_three_unpack(ev_bytes[i / 3u], &e[0], &e[1], &e[2]);
            uint8_t ev = e[i % 3u];

            if (ev > MRP_ATTR_EVENT_LV) continue; /* ignore reserved */

            uint8_t attr_val[64] = {0};
            if (ops && ops->decode_attr) {
                r = ops->decode_attr(attr_type, i,
                                    first_val, attr_length, attr_val);
                if (r < 0) continue;
            } else {
                /* Fallback: increment FirstValue by offset (integer attrs) */
                if (attr_length <= sizeof(attr_val)) {
                    memcpy(attr_val, first_val, attr_length);
                    /* Simple big-endian increment by i */
                    uint32_t carry = i;
                    for (int b = attr_length - 1; b >= 0 && carry; b--) {
                        carry += attr_val[b];
                        attr_val[b] = (uint8_t)carry;
                        carry >>= 8;
                    }
                }
            }

            if (has_subtype) {
                uint8_t s[4];
                size_t  vlen = ops->attr_len ? ops->attr_len(attr_type)
                                             : attr_length;
                mrp_four_unpack(sub_bytes[i / 4u],
                                &s[0], &s[1], &s[2], &s[3]);
                if (vlen < sizeof(attr_val)) {
                    attr_val[vlen] = s[i % 4u];
                }
            }

            if (on_attr) {
                on_attr(ctx, attr_type, (enum mrp_attr_event)ev, attr_val);
            }
        }
    }

    return (int)off;
}

int mrpdu_parse(const uint8_t *pdu, size_t pdu_len,
                const struct mrp_app_ops *ops,
                mrpdu_on_attr_fn on_attr,
                mrpdu_on_leaveall_fn on_leaveall,
                void *ctx)
{
    if (!pdu || pdu_len < 1) return -EINVAL;

    size_t off = 0;

    /* ProtocolVersion (§10.8.2.1) */
    uint8_t version;
    int r = get_u8(pdu + off, pdu_len - off, &version);
    if (r < 0) return r;
    off += (size_t)r;
    /* Version mismatch: log but continue per §10.8.3.3 */
    (void)version;

    /* Parse Messages until EndMark or buffer exhausted */
    while (off + 2 <= pdu_len) {
        /* Peek at next 2 bytes for EndMark */
        uint16_t probe;
        if (get_u16be(pdu + off, pdu_len - off, &probe) < 0) break;
        if (probe == MRP_ENDMARK) break;

        r = parse_message(pdu + off, pdu_len - off,
                          ops, on_attr, on_leaveall, ctx);
        if (r <= 0) return (r == 0) ? -EINVAL : r;
        off += (size_t)r;
    }

    return 0;
}
