/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHISH_LAN_SWITCH_H
#define SHISH_LAN_SWITCH_H

#include <stdint.h>

/* Opaque handle to a switch instance */
struct shlan_switch;

/*
 * Switch operations — the abstract port.
 * Concrete adapters (hw, sim) provide a struct shlan_switch_ops and pass it
 * to shlan_switch_create().
 */
struct shlan_switch_ops {
    int  (*connect)(struct shlan_switch *sw);
    void (*disconnect)(struct shlan_switch *sw);
    int  (*port_enable)(struct shlan_switch *sw, uint8_t port_id);
    int  (*port_disable)(struct shlan_switch *sw, uint8_t port_id);
};

struct shlan_switch {
    const struct shlan_switch_ops *ops;
    void                          *priv; /* adapter-private data */
};

/* Out-of-line entry points also support shared-library callers. */
int shlan_connect(struct shlan_switch *sw);
void shlan_disconnect(struct shlan_switch *sw);
int shlan_port_enable(struct shlan_switch *sw, uint8_t port_id);
int shlan_port_disable(struct shlan_switch *sw, uint8_t port_id);

#endif /* SHISH_LAN_SWITCH_H */
