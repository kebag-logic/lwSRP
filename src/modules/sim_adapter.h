#ifndef SHISH_LAN_SIM_ADAPTER_H
#define SHISH_LAN_SIM_ADAPTER_H

#include "shish_lan/switch.h"

/*
 * Software-simulation adapter — used in BDD tests so no real hardware
 * is required. Returns the same struct shlan_switch interface as the hw adapter.
 */
struct shlan_switch *shlan_sim_adapter_create(void);
void            shlan_sim_adapter_destroy(struct shlan_switch *sw);

#endif /* SHISH_LAN_SIM_ADAPTER_H */
