/* SPDX-License-Identifier: Apache-2.0 */
/* Switch port dispatch, shared by C and foreign-function callers. */
#include "shish_lan/switch.h"

int shlan_connect(struct shlan_switch *sw)
{
    return sw->ops->connect(sw);
}

void shlan_disconnect(struct shlan_switch *sw)
{
    sw->ops->disconnect(sw);
}

int shlan_port_enable(struct shlan_switch *sw, uint8_t port_id)
{
    return sw->ops->port_enable(sw, port_id);
}

int shlan_port_disable(struct shlan_switch *sw, uint8_t port_id)
{
    return sw->ops->port_disable(sw, port_id);
}
