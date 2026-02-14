/*
 * Unit tests for MRPDU encode / decode helpers (§10.8.2.10).
 *
 * Pack/unpack are pure, deterministic functions — perfect for cgreen
 * assertions. Vector encoding is exercised through a minimal round-trip.
 */

#include <cgreen/cgreen.h>
#include <stdint.h>
#include <string.h>

#include "shish_lan/mrp.h"
#include "shish_lan/mrp_pdu.h"

Describe(MrpPdu);
BeforeEach(MrpPdu) {}
AfterEach(MrpPdu)  {}

/* ------------------------------------------------------------------ */
/* ThreePackedEvents: ((e1*6 + e2)*6) + e3                            */
/* ------------------------------------------------------------------ */

Ensure(MrpPdu, three_pack_round_trips_all_legal_triples)
{
    for (uint8_t a = 0; a < 6; a++)
    for (uint8_t b = 0; b < 6; b++)
    for (uint8_t c = 0; c < 6; c++) {
        uint8_t packed = mrp_three_pack(a, b, c);
        uint8_t x, y, z;
        mrp_three_unpack(packed, &x, &y, &z);
        assert_that(x, is_equal_to(a));
        assert_that(y, is_equal_to(b));
        assert_that(z, is_equal_to(c));
    }
}

Ensure(MrpPdu, three_pack_uses_single_byte)
{
    /* Max legal packed value: 5*6*6 + 5*6 + 5 = 215 < 256 */
    uint8_t packed = mrp_three_pack(5, 5, 5);
    assert_that(packed, is_equal_to(215));
}

/* ------------------------------------------------------------------ */
/* FourPackedEvents: (((e1*64) + e2)*16) + (e3*4) + e4                */
/* ------------------------------------------------------------------ */

Ensure(MrpPdu, four_pack_round_trips_all_legal_quadruples)
{
    for (uint8_t a = 0; a < 4; a++)
    for (uint8_t b = 0; b < 4; b++)
    for (uint8_t c = 0; c < 4; c++)
    for (uint8_t d = 0; d < 4; d++) {
        uint8_t packed = mrp_four_pack(a, b, c, d);
        uint8_t w, x, y, z;
        mrp_four_unpack(packed, &w, &x, &y, &z);
        assert_that(w, is_equal_to(a));
        assert_that(x, is_equal_to(b));
        assert_that(y, is_equal_to(c));
        assert_that(z, is_equal_to(d));
    }
}

/* ------------------------------------------------------------------ */
/* VectorHeader: (LeaveAllEvent << 13) | NumberOfValues               */
/* ------------------------------------------------------------------ */

Ensure(MrpPdu, vector_header_encodes_leaveall_and_nvalues)
{
    uint16_t vh = mrp_vh_encode(MRP_LA_ALL, 0x1FFFu);
    assert_that(mrp_vh_la(vh), is_equal_to(MRP_LA_ALL));
    assert_that(mrp_vh_nv(vh), is_equal_to(0x1FFFu));

    vh = mrp_vh_encode(MRP_LA_NULL, 1u);
    assert_that(mrp_vh_la(vh), is_equal_to(MRP_LA_NULL));
    assert_that(mrp_vh_nv(vh), is_equal_to(1u));
}

Ensure(MrpPdu, vector_header_masks_nvalues_to_13_bits)
{
    /* 0x2001 = b10_0000_0000_0001 → top bit must be masked off of NV */
    uint16_t vh = mrp_vh_encode(MRP_LA_NULL, 0x2001u);
    assert_that(mrp_vh_nv(vh), is_equal_to(0x0001u));
}

/* ------------------------------------------------------------------ */
/* MRPDU begin/end framing                                             */
/* ------------------------------------------------------------------ */

Ensure(MrpPdu, encode_begin_writes_protocol_version)
{
    uint8_t buf[1] = {0xFF};
    int n = mrpdu_encode_begin(buf, sizeof(buf), MRP_PROTOCOL_VERSION);
    assert_that(n, is_equal_to(1));
    assert_that(buf[0], is_equal_to(MRP_PROTOCOL_VERSION));
}

Ensure(MrpPdu, encode_end_writes_endmark)
{
    uint8_t buf[2] = {0xAA, 0xBB};
    int n = mrpdu_encode_end(buf, sizeof(buf));
    assert_that(n, is_equal_to(2));
    assert_that(buf[0], is_equal_to(0x00));
    assert_that(buf[1], is_equal_to(0x00));
}

Ensure(MrpPdu, encode_vector_emits_vh_firstvalue_packed)
{
    uint8_t fv[2] = {0x00, 0x64}; /* VID 100 */
    uint8_t out[5] = {0};

    int n = mrpdu_encode_vector(out, sizeof(out),
                                MRP_LA_NULL, MRP_ATTR_EVENT_JOININ,
                                fv, sizeof(fv));
    assert_that(n, is_equal_to(5));

    uint16_t vh = (uint16_t)((out[0] << 8) | out[1]);
    assert_that(mrp_vh_la(vh), is_equal_to(MRP_LA_NULL));
    assert_that(mrp_vh_nv(vh), is_equal_to(1));

    assert_that(out[2], is_equal_to(0x00));
    assert_that(out[3], is_equal_to(0x64));

    /* The event byte: first slot = JoinIn (1), padding slots = Mt (4) */
    uint8_t e1, e2, e3;
    mrp_three_unpack(out[4], &e1, &e2, &e3);
    assert_that(e1, is_equal_to(MRP_ATTR_EVENT_JOININ));
}

Ensure(MrpPdu, encode_vector_rejects_truncated_buffer)
{
    uint8_t fv[2] = {0, 1};
    uint8_t small[3];
    int n = mrpdu_encode_vector(small, sizeof(small),
                                MRP_LA_NULL, MRP_ATTR_EVENT_IN, fv, sizeof(fv));
    assert_that(n, is_less_than(0));
}

TestSuite *mrp_pdu_suite(void)
{
    TestSuite *s = create_test_suite();
    add_test_with_context(s, MrpPdu, three_pack_round_trips_all_legal_triples);
    add_test_with_context(s, MrpPdu, three_pack_uses_single_byte);
    add_test_with_context(s, MrpPdu, four_pack_round_trips_all_legal_quadruples);
    add_test_with_context(s, MrpPdu, vector_header_encodes_leaveall_and_nvalues);
    add_test_with_context(s, MrpPdu, vector_header_masks_nvalues_to_13_bits);
    add_test_with_context(s, MrpPdu, encode_begin_writes_protocol_version);
    add_test_with_context(s, MrpPdu, encode_end_writes_endmark);
    add_test_with_context(s, MrpPdu, encode_vector_emits_vh_firstvalue_packed);
    add_test_with_context(s, MrpPdu, encode_vector_rejects_truncated_buffer);
    return s;
}
