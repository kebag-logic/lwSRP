/* SPDX-License-Identifier: Apache-2.0 */

#include "shish_lan/switch.h"

/* ctypes needs external symbols for the public header's inline helpers. */
int shlan_test_connect(struct shlan_switch *sw)
{
    return shlan_connect(sw);
}

void shlan_test_disconnect(struct shlan_switch *sw)
{
    shlan_disconnect(sw);
}

int shlan_test_port_enable(struct shlan_switch *sw, uint8_t port_id)
{
    return shlan_port_enable(sw, port_id);
}

int shlan_test_port_disable(struct shlan_switch *sw, uint8_t port_id)
{
    return shlan_port_disable(sw, port_id);
}
