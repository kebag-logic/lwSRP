#ifndef SHISH_LAN_MSRP_H
#define SHISH_LAN_MSRP_H

/*
 * Multiple Stream Reservation Protocol (MSRP) — IEEE 802.1Q-2018, Clause 35
 *
 * MSRP is an MRP application (§10.2) for AVB/TSN stream reservation.
 * It registers data stream characteristics and reserves bridge resources
 * to provide QoS guarantees.
 *
 * Attribute types (§35.2.1):
 *   Type 1: Talker Advertise  — stream parameters from talker
 *   Type 2: Talker Failed     — stream parameters + failure information
 *   Type 3: Listener          — listener declaration (Ready/PartiallyFailed/Failed)
 *
 * EtherType:       0x22EA (Table 10-2)
 * Protocol version: 0
 * AttributeListLength: PRESENT (unlike MMRP/MVRP — §10.8.2.4)
 *
 * NOTE: Clause 35 was not fully read during initial implementation.
 *       The interface below captures the key attribute types.
 *       FourPackedEvents are used for Listener attributes (§35.2.1.4).
 */

#include <stdint.h>
#include "mrp.h"

/* §35.2.1 MSRP attribute types */
#define MSRP_ATTR_TYPE_TALKER_ADV    1u
#define MSRP_ATTR_TYPE_TALKER_FAILED 2u
#define MSRP_ATTR_TYPE_LISTENER      3u

/* Stream ID: 8-octet identifier (§35.2.1) */
struct msrp_stream_id {
    uint8_t bytes[8];
};

/* §35.2.1 Listener declaration types (FourPackedType) */
enum msrp_listener_decl {
    MSRP_LISTENER_DECL_IGNORE        = 0,
    MSRP_LISTENER_DECL_ASKING_FAILED = 1,
    MSRP_LISTENER_DECL_READY         = 2,
    MSRP_LISTENER_DECL_READY_FAILED  = 3,
};

/* §35.2.1.3 Talker Advertise attribute value (25 octets) */
struct msrp_talker_adv {
    struct msrp_stream_id stream_id;       /* 8 octets */
    uint8_t               data_frame_params[2]; /* destination MAC + VLAN priority */
    uint16_t              max_frame_size;  /* octets */
    uint16_t              max_interval_frames; /* frames per class interval */
    uint8_t               priority_and_rank;
    uint32_t              accumulated_latency; /* ns */
};

/* §35.2.1.4 Talker Failed attribute extends Talker Advertise */
struct msrp_talker_failed {
    struct msrp_talker_adv talker;         /* 25 octets */
    uint8_t                failure_info[9];/* bridge ID + failure code */
};

/*
 * MSRP application context.
 */
struct msrp_ctx {
    void (*on_talker_advertise)(struct msrp_ctx *ctx, uint8_t port_id,
                                const struct msrp_talker_adv *attr, bool is_new);
    void (*on_talker_failed)(struct msrp_ctx *ctx, uint8_t port_id,
                             const struct msrp_talker_failed *attr, bool is_new);
    void (*on_listener)(struct msrp_ctx *ctx, uint8_t port_id,
                        const struct msrp_stream_id *stream_id,
                        enum msrp_listener_decl decl, bool is_new);
    void (*on_leave)(struct msrp_ctx *ctx, uint8_t port_id,
                     uint8_t attr_type, const void *attr_val);
};

struct mrp_app *msrp_app_create(uint8_t n_ports, struct msrp_ctx *ctx);
void        msrp_app_destroy(struct mrp_app *app);

int msrp_declare_talker(struct mrp_app *app, uint8_t port_id,
                        const struct msrp_talker_adv *attr, bool is_new);
int msrp_declare_listener(struct mrp_app *app, uint8_t port_id,
                          const struct msrp_stream_id *stream_id,
                          enum msrp_listener_decl decl);
int msrp_withdraw_talker(struct mrp_app *app, uint8_t port_id,
                         const struct msrp_stream_id *stream_id);
int msrp_withdraw_listener(struct mrp_app *app, uint8_t port_id,
                           const struct msrp_stream_id *stream_id);

#endif /* SHISH_LAN_MSRP_H */
