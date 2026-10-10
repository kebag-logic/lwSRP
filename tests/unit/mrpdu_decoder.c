/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Test-side MRPDU reader. Clause references are IEEE 802.1Q-2018.
 * The library parser is deliberately not used here.
 */

#include "mrpdu_decoder.h"

#include <string.h>

/* Table 10-2: the MSRP EtherType; 35.2.2.4 Table 35-1: the Listener type. */
#define DECODER_MSRP_ETHERTYPE 0x22EAu
#define DECODER_MSRP_LISTENER 3u

struct mrpdu_profile mrpdu_profile_for(uint16_t ethertype)
{
    struct mrpdu_profile profile = {false, 0};
    if (ethertype == DECODER_MSRP_ETHERTYPE) {
        /* 35.2.2.6 and 35.2.2.7.2. */
        profile.list_length = true;
        profile.four_packed_type = DECODER_MSRP_LISTENER;
    }
    return profile;
}

/* 10.8.1.1: the lower-numbered octet is the most significant. */
static unsigned octets(const uint8_t *at)
{
    return (unsigned)at[0] << 8 | at[1];
}

/* Read the AttributeList of one Message from off up to end (10.8.1.2 d, e). */
static int read_list(const uint8_t *pdu, size_t *at, size_t end,
                     const struct mrpdu_profile *profile, struct mrpdu_decoded *out,
                     struct mrpdu_message *m)
{
    size_t off = *at;
    while (off < end) {
        if (end - off < 2) {
            return -1;
        }
        unsigned header = octets(pdu + off);
        if (header == 0) {
            /* 10.8.2.9: an EndMark closes the AttributeList. */
            m->end_mark = true;
            ++out->end_marks;
            off += 2;
            break;
        }
        /* 10.8.2.8 a, b: LeaveAllEvent * 8192 + NumberOfValues. A null
         * LeaveAllEvent with no values would read as the EndMark (10.8.2.8 g). */
        unsigned leave_all = header / 8192u;
        unsigned values = header % 8192u;
        if (leave_all > 1u) {
            return -1; /* 10.8.2.6 reserves other values. */
        }
        size_t three = (values + 2u) / 3u;
        size_t four = profile->four_packed_type == m->type ? (values + 3u) / 4u : 0;
        size_t need = 2u + m->length + three + four;
        if (need > end - off) {
            return -1; /* 10.8.3.4 b: an incomplete VectorAttribute */
        }
        if (out->vectors == MRPDU_DECODER_VECTORS) {
            return -1;
        }
        struct mrpdu_vector *v = &out->vector[out->vectors++];
        v->offset = off;
        v->type = m->type;
        v->length = m->length;
        v->leave_all = leave_all;
        v->values = values;
        v->first_value = pdu + off + 2;
        v->three = v->first_value + m->length;
        v->four = four ? v->three + three : NULL;
        for (size_t k = 0; k < three; ++k) {
            if (v->three[k] > 215u) {
                return -1; /* 10.8.2.5: AttributeEvent is 0 through 5 */
            }
        }
        ++m->vectors;
        off += need;
    }
    *at = off;
    /* 10.8.1.2 d: one or more VectorAttributes. */
    return m->vectors ? 0 : -1;
}

int mrpdu_decode(const uint8_t *pdu, size_t len, const struct mrpdu_profile *profile,
                 struct mrpdu_decoded *out)
{
    memset(out, 0, sizeof(*out));
    if (!pdu || len < 1) {
        return -1;
    }
    out->version = pdu[0];
    size_t off = 1;
    while (off < len) {
        if (len - off < 2) {
            return -1;
        }
        if (octets(pdu + off) == 0) {
            /* 10.8.1.2 b: the MRPDU EndMark. AttributeType 0 is reserved (10.8.2.2). */
            ++out->end_marks;
            out->pdu_end_mark = true;
            out->trailing = len - off - 2u;
            break;
        }
        if (out->messages == MRPDU_DECODER_MESSAGES) {
            return -1;
        }
        struct mrpdu_message *m = &out->message[out->messages++];
        m->offset = off;
        m->type = pdu[off];
        m->length = pdu[off + 1];
        m->first_vector = out->vectors;
        off += 2;
        if (m->type == 0 || m->length == 0) {
            return -1; /* 10.8.1.2: both are nonzero */
        }
        size_t end = len;
        if (profile->list_length) {
            if (len - off < 2) {
                return -1;
            }
            m->has_list_length = true;
            m->list_length = octets(pdu + off);
            off += 2;
            if (m->list_length > len - off) {
                return -1;
            }
            end = off + m->list_length;
        }
        if (read_list(pdu, &off, end, profile, out, m) < 0) {
            return -1;
        }
        /* Without AttributeListLength the EndMark alone is the boundary. */
        if (profile->list_length && off != end) {
            return -1;
        }
    }
    /* 10.8.1.2 b: one or more Messages; f: the PDU end acts as an EndMark. */
    return out->messages ? 0 : -1;
}

unsigned mrpdu_event(const struct mrpdu_vector *v, unsigned n)
{
    unsigned packed = v->three[n / 3u];
    switch (n % 3u) {
    case 0:
        return packed / 36u;
    case 1:
        return packed / 6u % 6u;
    default:
        return packed % 6u;
    }
}

unsigned mrpdu_four_packed(const struct mrpdu_vector *v, unsigned n)
{
    if (!v->four) {
        return 0;
    }
    return (v->four[n / 4u] >> (6u - 2u * (n % 4u))) & 3u;
}
