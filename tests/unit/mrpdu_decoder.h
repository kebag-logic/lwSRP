/* SPDX-License-Identifier: Apache-2.0 */
#ifndef LWSRP_TEST_MRPDU_DECODER_H
#define LWSRP_TEST_MRPDU_DECODER_H

/*
 * Test-side MRPDU reader, written from IEEE 802.1Q-2018 10.8.1.2 and 10.8.2.
 * It shares no code or header with the library parser (src/core/mrp_pdu.c),
 * so encoder tests do not grade the encoder with its own counterpart.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MRPDU_DECODER_MESSAGES 64u
#define MRPDU_DECODER_VECTORS 512u

/* What 10.8 leaves to the application (10.8.2.4, 10.8.2.10.2, 35.2.2.6). */
struct mrpdu_profile {
    bool list_length;          /* Messages carry AttributeListLength */
    uint8_t four_packed_type;  /* AttributeType with FourPackedEvents, or 0 */
};

struct mrpdu_vector {
    size_t offset;              /* octet offset of the VectorHeader */
    uint8_t type;               /* AttributeType of the enclosing Message */
    uint8_t length;             /* AttributeLength: FirstValue octets */
    unsigned leave_all;         /* LeaveAllEvent */
    unsigned values;            /* NumberOfValues */
    const uint8_t *first_value;
    const uint8_t *three;       /* ThreePackedEvents */
    const uint8_t *four;        /* FourPackedEvents, or NULL */
};

struct mrpdu_message {
    size_t offset;              /* octet offset of the AttributeType */
    uint8_t type;
    uint8_t length;
    bool has_list_length;
    unsigned list_length;
    size_t first_vector;        /* index of its first vector */
    size_t vectors;
    bool end_mark;              /* the AttributeList ends with an EndMark */
};

struct mrpdu_decoded {
    uint8_t version;
    size_t messages;
    size_t vectors;
    unsigned end_marks;         /* explicit EndMarks of both kinds */
    bool pdu_end_mark;          /* the MRPDU ends with an explicit EndMark */
    size_t trailing;            /* octets after the MRPDU EndMark */
    struct mrpdu_message message[MRPDU_DECODER_MESSAGES];
    struct mrpdu_vector vector[MRPDU_DECODER_VECTORS];
};

/* The profile of an application EtherType (Table 10-2). */
struct mrpdu_profile mrpdu_profile_for(uint16_t ethertype);

/*
 * Decode one MRPDU. Returns 0, or -1 for a PDU that 10.8.3.3 discards or
 * that exceeds the fixed tables above.
 */
int mrpdu_decode(const uint8_t *pdu, size_t len, const struct mrpdu_profile *profile,
                 struct mrpdu_decoded *out);

/* AttributeEvent n of a vector (10.8.2.10.1). */
unsigned mrpdu_event(const struct mrpdu_vector *v, unsigned n);

/* FourPackedType n of a vector (10.8.2.10.2), or 0 when the vector has none. */
unsigned mrpdu_four_packed(const struct mrpdu_vector *v, unsigned n);

#endif
