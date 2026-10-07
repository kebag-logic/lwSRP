/* SPDX-License-Identifier: Apache-2.0 */
#include "shish_lan/switch.h"
static unsigned calls;
static int connect_port(struct shlan_switch *sw)
{
    (void)sw; calls |= 1u; return 11;
}
static void disconnect_port(struct shlan_switch *sw)
{
    (void)sw; calls |= 2u;
}
static int enable_port(struct shlan_switch *sw, uint8_t port)
{
    (void)sw; calls |= 4u; return port + 10;
}
static int disable_port(struct shlan_switch *sw, uint8_t port)
{
    (void)sw; calls |= 8u; return port + 20;
}
int main(void)
{
    const struct shlan_switch_ops ops = {connect_port, disconnect_port, enable_port, disable_port};
    struct shlan_switch sw = {&ops, 0};
    if (shlan_connect(&sw) != 11 || shlan_port_enable(&sw, 3) != 13 || shlan_port_disable(&sw, 7) != 27) {
        return 1;
    }
    shlan_disconnect(&sw);
    return calls != 15u;
}
