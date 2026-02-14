#include <string.h>
#include "sim_adapter.h"
#include "ports/alloc.h"

#define SIM_MAX_PORTS 48

struct sim_priv {
    int port_state[SIM_MAX_PORTS]; /* 1 = enabled, 0 = disabled */
};

static int sim_connect(struct shlan_switch *sw)
{
    struct sim_priv *p = sw->priv;
    memset(p->port_state, 0, sizeof(p->port_state));
    return 0;
}

static void sim_disconnect(struct shlan_switch *sw)
{
    (void)sw;
}

static int sim_port_enable(struct shlan_switch *sw, uint8_t port_id)
{
    if (port_id >= SIM_MAX_PORTS) return -1;
    ((struct sim_priv *)sw->priv)->port_state[port_id] = 1;
    return 0;
}

static int sim_port_disable(struct shlan_switch *sw, uint8_t port_id)
{
    if (port_id >= SIM_MAX_PORTS) return -1;
    ((struct sim_priv *)sw->priv)->port_state[port_id] = 0;
    return 0;
}

static const struct shlan_switch_ops sim_ops = {
    .connect      = sim_connect,
    .disconnect   = sim_disconnect,
    .port_enable  = sim_port_enable,
    .port_disable = sim_port_disable,
};

struct shlan_switch *shlan_sim_adapter_create(void)
{
    struct shlan_switch *sw = shlan_malloc(sizeof(*sw));
    struct sim_priv     *p  = shlan_calloc(1, sizeof(*p));
    if (!sw || !p) { shlan_free(sw); shlan_free(p); return NULL; }
    sw->ops  = &sim_ops;
    sw->priv = p;
    return sw;
}

void shlan_sim_adapter_destroy(struct shlan_switch *sw)
{
    if (!sw) return;
    shlan_free(sw->priv);
    shlan_free(sw);
}
