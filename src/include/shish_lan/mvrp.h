/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHISH_LAN_MVRP_H
#define SHISH_LAN_MVRP_H

/*
 * Multiple VLAN Registration Protocol (MVRP) — IEEE 802.1Q-2018, §11.2
 *
 * MVRP is an MRP application (§10.2) that registers VLAN membership.
 * Attribute type: one type (value 1) for VID registration.
 * Attribute value: a 12-bit VID encoded as 2 octets (§11.2.3).
 *
 * EtherType: 0x88F5 (Table 10-2)
 * Group MAC:  01-80-C2-00-00-21 (Table 10-1)
 * Protocol version: 0
 *
 * MAP Context: VLAN Context (§10.3.1 b) — one Participant per port.
 * "new" declaration capability: used to flush FDB entries (§11.2.5).
 */

#include <stdint.h>
#include "mrp.h"

/* §11.2.3 — MVRP attribute type value */
#define MVRP_ATTR_TYPE_VID    1u

/* §11.2.3 — FirstValue length for VID attribute (2 octets) */
#define MVRP_ATTR_LEN_VID     2u

/* VID range per 802.1Q §6.8.1 */
#define MVRP_VID_MIN          1u
#define MVRP_VID_MAX          4094u

/*
 * MVRP application context — passed back via ops->ctx.
 * The application updates its VLAN membership table in the callbacks.
 */
struct mvrp_ctx {
    /*
     * Called when a VID is registered on a port (MAD_Join.indication).
     * is_new=true triggers FDB flush for that VID (§11.2.5).
     */
    void (*on_vlan_registered)(struct mvrp_ctx *ctx, uint8_t port_id,
                               uint16_t vid, bool is_new);

    /*
     * Called when a VID is deregistered from a port (MAD_Leave.indication).
     */
    void (*on_vlan_deregistered)(struct mvrp_ctx *ctx, uint8_t port_id,
                                 uint16_t vid);
};

/*
 * mvrp_app_create — create an MVRP MRP application instance.
 * n_ports: number of bridge ports that participate.
 * ctx:     application callbacks (must remain valid for the lifetime of the app).
 */
struct mrp_app *mvrp_app_create(uint8_t n_ports, struct mvrp_ctx *ctx);
void        mvrp_app_destroy(struct mrp_app *app);

/* Declare membership of vid on port_id (wraps mrp_mad_join). */
int mvrp_declare(struct mrp_app *app, uint8_t port_id, uint16_t vid);

/* Withdraw membership of vid on port_id (wraps mrp_mad_leave). */
int mvrp_withdraw(struct mrp_app *app, uint8_t port_id, uint16_t vid);

#endif /* SHISH_LAN_MVRP_H */
