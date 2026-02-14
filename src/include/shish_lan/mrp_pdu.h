#ifndef SHISH_LAN_MRP_PDU_H
#define SHISH_LAN_MRP_PDU_H

/*
 * MRPDU structure and encoding — IEEE 802.1Q-2018 §10.8
 *
 * BNF (§10.8.1.2):
 *   MRPDU            ::= ProtocolVersion, Message {, Message}, EndMark
 *   Message          ::= AttributeType, AttributeLength
 *                        [, AttributeListLength], AttributeList
 *   AttributeList    ::= VectorAttribute {, VectorAttribute}, EndMark
 *   VectorAttribute  ::= VectorHeader, FirstValue {, Vector}
 *   VectorHeader     ::= (LeaveAllEvent * 8192) + NumberOfValues  [2 octets]
 *   Vector           ::= ThreePackedEvents {, ThreePackedEvents}
 *                      | FourPackedEvents  {, FourPackedEvents}
 *   ThreePackedEvents BYTE ::= (((e1 * 6) + e2) * 6) + e3
 *   FourPackedEvents  BYTE ::= (((e1 * 64) + e2) * 16) + (e3 * 4) + e4
 *   EndMark SHORT    ::= 0x0000
 *
 * AttributeEvent values (§10.8.2.5):
 *   New=0, JoinIn=1, In=2, JoinMt=3, Mt=4, Lv=5
 *
 * LeaveAllEvent values (§10.8.2.6):
 *   NullLeaveAllEvent=0, LeaveAll=1
 *
 * AttributeListLength is only present for MSRP (§10.8.2.4); absent for
 * MMRP and MVRP.
 */

#include <stddef.h>
#include <stdint.h>

#include "mrp.h"

/* ------------------------------------------------------------------ */
/* §10.8.2.9 EndMark                                                   */
/* ------------------------------------------------------------------ */
#define MRP_ENDMARK 0x0000u

/* ------------------------------------------------------------------ */
/* VectorHeader bit layout (§10.8.2.8)                                 */
/* VectorHeader = (LeaveAllEvent << 13) | NumberOfValues               */
/* ------------------------------------------------------------------ */
#define MRP_VH_LEAVEALL_SHIFT 13u
#define MRP_VH_NVALUES_MASK   0x1FFFu /* 13-bit NumberOfValues          */

static inline uint16_t mrp_vh_encode(uint8_t la_event, uint16_t n_values)
{
    return (uint16_t)((la_event << MRP_VH_LEAVEALL_SHIFT) |
                      (n_values & MRP_VH_NVALUES_MASK));
}
static inline uint8_t  mrp_vh_la(uint16_t vh)  { return (uint8_t)(vh >> MRP_VH_LEAVEALL_SHIFT); }
static inline uint16_t mrp_vh_nv(uint16_t vh)  { return vh & MRP_VH_NVALUES_MASK; }

/* ------------------------------------------------------------------ */
/* §10.8.2.10.1 ThreePacked encoding                                   */
/* 3 AttributeEvents packed into one octet                             */
/* ------------------------------------------------------------------ */
static inline uint8_t mrp_three_pack(uint8_t e1, uint8_t e2, uint8_t e3)
{
    return (uint8_t)(((e1 * 6u + e2) * 6u) + e3);
}
static inline void mrp_three_unpack(uint8_t b, uint8_t *e1, uint8_t *e2, uint8_t *e3)
{
    *e3 = b % 6u;  b /= 6u;
    *e2 = b % 6u;  b /= 6u;
    *e1 = b;
}

/* ------------------------------------------------------------------ */
/* §10.8.2.10.2 FourPacked encoding (used by MSRP)                     */
/* 4 FourPackedType values packed into one octet                       */
/* ------------------------------------------------------------------ */
static inline uint8_t mrp_four_pack(uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4)
{
    return (uint8_t)(((e1 * 64u + e2) * 16u) + (e3 * 4u) + e4);
}
static inline void mrp_four_unpack(uint8_t b, uint8_t *e1, uint8_t *e2,
                                   uint8_t *e3, uint8_t *e4)
{
    *e4 = b % 4u;  b /= 4u;
    *e3 = b % 4u;  b /= 4u;
    *e2 = b % 4u;  b /= 4u;
    *e1 = b;
}

/* ------------------------------------------------------------------ */
/* MRPDU encode / decode — implemented in src/core/mrp_pdu.c           */
/* ------------------------------------------------------------------ */

/*
 * mrpdu_encode_begin — write ProtocolVersion (§10.8.2.1) into buf.
 * Returns bytes written, or -ENOBUFS.
 */
int mrpdu_encode_begin(uint8_t *buf, size_t buf_len, uint8_t proto_version);

/*
 * mrpdu_encode_end — write trailing EndMark (§10.8.2.9).
 * Returns bytes written, or -ENOBUFS.
 */
int mrpdu_encode_end(uint8_t *buf, size_t buf_len);

/*
 * mrpdu_encode_vector — encode one VectorAttribute for a single attribute
 * value and event.
 *
 * The caller is responsible for framing the Message header
 * (AttributeType, AttributeLength) around calls to this function.
 *
 * Returns bytes written, or -ENOBUFS / -EINVAL.
 */
int mrpdu_encode_vector(uint8_t *buf, size_t buf_len,
                        uint8_t la_event,
                        enum mrp_attr_event attr_event,
                        const uint8_t *first_value, uint8_t fv_len);

/*
 * mrpdu_parse — parse an MRPDU and invoke callbacks for each decoded
 * attribute event.
 *
 * on_attr is called for every decoded (attr_type, attr_event, attr_val) triple.
 * on_leaveall is called once per VectorAttribute that carries LeaveAll.
 *
 * Returns 0 on success, negative errno on malformed PDU (§10.8.3.3).
 */
typedef void (*mrpdu_on_attr_fn)(void *ctx, uint8_t attr_type,
                                 enum mrp_attr_event attr_event,
                                 const void *attr_val);
typedef void (*mrpdu_on_leaveall_fn)(void *ctx, uint8_t attr_type);

int mrpdu_parse(const uint8_t *pdu, size_t pdu_len,
                const struct mrp_app_ops *ops,
                mrpdu_on_attr_fn on_attr,
                mrpdu_on_leaveall_fn on_leaveall,
                void *ctx);

#endif /* SHISH_LAN_MRP_PDU_H */
