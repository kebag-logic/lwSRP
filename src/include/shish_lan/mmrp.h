#ifndef SHISH_LAN_MMRP_H
#define SHISH_LAN_MMRP_H

/*
 * Multiple MAC Registration Protocol (MMRP) — IEEE 802.1Q-2018, §10.9–10.12
 *
 * MMRP registers two attribute types (§10.12.1):
 *   Type 1: MAC address (individual or group, 6 octets)
 *   Type 2: Service requirement (1 octet)
 *
 * EtherType: 0x88F6 (Table 10-2)
 * Group MAC:  01-80-C2-00-00-20 (Table 10-1)
 * Protocol version: 0
 *
 * MMRP operates only when the bridge is in Extended Filtering Mode (§10.9).
 * MAP Context: Base Spanning Tree Context (§10.3.1 a) for MAC bridges,
 *              VLAN Context for VLAN bridges (§10.12.1.1).
 * "new" declaration capability: NOT used by MMRP (§10.3, NOTE).
 */

#include <stdint.h>
#include "mrp.h"

/* §10.12.1 — MMRP attribute types */
#define MMRP_ATTR_TYPE_SVC  1u  /* Service requirement attribute */
#define MMRP_ATTR_TYPE_MAC  2u  /* MAC address attribute         */

/* FirstValue lengths (§10.12.1) */
#define MMRP_ATTR_LEN_SVC   1u  /* 1 octet  */
#define MMRP_ATTR_LEN_MAC   6u  /* 6 octets */

/*
 * §10.12.1 — Service requirement attribute values.
 * Expressed as control bits in the Static Filtering Entry (SFE) for
 * All Groups / All Unregistered Groups.
 */
#define MMRP_SVC_FORWARD_ALL          0x00u
#define MMRP_SVC_FORWARD_UNREGISTERED 0x01u

/* MAC attribute value */
struct mmrp_mac {
    uint8_t addr[6];
};

/*
 * MMRP application context.
 */
struct mmrp_ctx {
    /*
     * MAC address registered on port — update FDB MAC Address Registration Entry.
     * §10.10.1
     */
    void (*on_mac_registered)(struct mmrp_ctx *ctx, uint8_t port_id,
                              const struct mmrp_mac *mac);

    /* MAC address deregistered — remove FDB entry. */
    void (*on_mac_deregistered)(struct mmrp_ctx *ctx, uint8_t port_id,
                                const struct mmrp_mac *mac);

    /*
     * Service requirement registered — change default Group filtering on port.
     * §10.10.2
     */
    void (*on_svc_registered)(struct mmrp_ctx *ctx, uint8_t port_id,
                              uint8_t svc);

    void (*on_svc_deregistered)(struct mmrp_ctx *ctx, uint8_t port_id,
                                uint8_t svc);
};

struct mrp_app *mmrp_app_create(uint8_t n_ports, struct mmrp_ctx *ctx);
void        mmrp_app_destroy(struct mrp_app *app);

/* Declare group MAC membership on port_id. */
int mmrp_declare_mac(struct mrp_app *app, uint8_t port_id, const struct mmrp_mac *mac);
int mmrp_withdraw_mac(struct mrp_app *app, uint8_t port_id, const struct mmrp_mac *mac);

/* Declare service requirement on port_id. */
int mmrp_declare_svc(struct mrp_app *app, uint8_t port_id, uint8_t svc);
int mmrp_withdraw_svc(struct mrp_app *app, uint8_t port_id, uint8_t svc);

#endif /* SHISH_LAN_MMRP_H */
