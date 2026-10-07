<!-- SPDX-License-Identifier: Apache-2.0 -->
# Integrator guide

Use this guide to connect platform services and plan hardware integration.
Start with the [scope matrix](manager.md#implementation-status).
The current library supports state and receive-path experiments.
It cannot yet provide complete network registration or resource reservation.

## Build choices

The [root build definition](../CMakeLists.txt) selects between host and embedded module builds.

| Setting | Current behavior |
| --- | --- |
| Host build | Produces a shared library with applications, ports, and simulation. |
| C language | Requires C11. |
| [CMAKE_BUILD_TYPE](../CMakeLists.txt) set to Debug | Adds compiler debugging information through [CMake](https://cmake.org/cmake/help/latest/). |
| Export compile commands | Enabled by the [build definition](../CMakeLists.txt). |
| Unit dependency found | Adds a single [empty test runner](../tests/unit/placeholder.c). |
| Unit dependency absent | Adds no unit target. Configuration still succeeds. |
| [ZEPHYR_BASE](../CMakeLists.txt) defined | Selects the module branch and returns before host configuration. |
| [CONFIG_LWSRP](../Kconfig.zephyr) enabled | Builds protocol sources and default allocation and timer ports. |

There are no project options for hardware selection, coverage, or transmit assembly.
The [register queue](../src/core/switch_ctrl.c) is absent from both source lists.
The [build wrapper](../build.sh) only creates an environment and sets variables inside its process.
It does not build the library.
Use the [quick start commands](../README.md#quick-start).

## Port platform services

| Service | Replace or drive | Contract |
| --- | --- | --- |
| Allocation | [Allocation implementation](../src/ports/alloc.c) | Supply allocation, zeroed allocation, and matching release. |
| Printing | [shlan_printf](../src/ports/alloc.h) | Preserve formatted output and return behavior. |
| Timing | [Timer implementation](../src/ports/timer.c) | Advance once per centisecond, or supply an equivalent callback service. |

Replace each default translation unit in your platform build.
Do not link duplicate definitions.
The [allocation interface](../src/ports/alloc.h) declares [shlan_malloc, shlan_calloc, and shlan_free](../src/ports/alloc.h).
The default implementation uses the C library.
The [timer interface](../src/ports/timer.h) defines initialization, one-shot arming, cancellation, and ticking.

## Create and declare

~~~mermaid
sequenceDiagram
    participant Host
    participant App as Protocol application
    participant Core as MRP state
    participant Timer as Timer service
    Host->>App: Create with ports and callbacks
    App->>Core: Copy operations and allocate state
    Core->>Timer: Register and arm port timers
    App-->>Host: Handle or null
    Host->>App: Declare a value
    App->>Core: Apply local event
    Core-->>Host: Status code
~~~

Use zero-based port identifiers within the created port count.
Validate them before calls; most [MRP operations](../src/core/mrp_mad.c) do not check bounds.
Limit propagation to 32 ports.
Keep a non-null callback context alive throughout the application lifetime.
Check creation for null and declarations for negative results.

| Application | Create | Declare | Withdraw |
| --- | --- | --- | --- |
| VLAN | [mvrp_app_create](../src/modules/mvrp.c) | [mvrp_declare](../src/modules/mvrp.c) | [mvrp_withdraw](../src/modules/mvrp.c) |
| MAC | [mmrp_app_create](../src/modules/mmrp.c) | [mmrp_declare_mac or mmrp_declare_svc](../src/modules/mmrp.c) | [mmrp_withdraw_mac or mmrp_withdraw_svc](../src/modules/mmrp.c) |
| Stream | [msrp_app_create](../src/modules/msrp.c) | [msrp_declare_talker or msrp_declare_listener](../src/modules/msrp.c) | [msrp_withdraw_talker or msrp_withdraw_listener](../src/modules/msrp.c) |

VLAN identifiers must be between 1 and 4094.
The [receive decoder](../src/modules/mvrp.c) checks this range; the declaration wrapper does not.
The [MAC adapter](../src/modules/mmrp.c) accepts MAC addresses or service requirements.
The [stream interface](../src/include/shish_lan/msrp.h) defines Talker structures and Listener declaration values.
Local declarations update state without sending frames.

## Receive and observe

~~~mermaid
sequenceDiagram
    participant Host
    participant Core as MRP state
    participant Codec
    participant Policy as Host callbacks
    Host->>Core: Submit payload and ingress port
    Core->>Codec: Parse attribute vectors
    Codec->>Core: Deliver decoded events
    Core->>Policy: Registration indication
    Core->>Core: Apply optional propagation
    Core->>Host: Report state transition
    Core-->>Host: Parse result
~~~

Pass an MRPDU payload to [mrp_rx](../src/core/mrp_mad.c), starting at the protocol version byte.
Strip Ethernet framing and select the matching application first.
The [application interface](../src/include/shish_lan/mrp.h) supplies protocol identifiers.
The library does not receive network frames itself.

Register [mrp_set_observer](../src/include/shish_lan/mrp.h) before events when transition records are needed.
Use [mrp_attr_visit](../src/include/shish_lan/mrp.h) for current attribute state.
Use [mrp_port_status](../src/include/shish_lan/mrp.h) for LeaveAll and periodic state.
The observer reports changed Applicant or Registrar states only.
Callbacks run synchronously.
Copy values that must survive the callback.

The [parser](../src/core/mrp_pdu.c) can deliver earlier events before rejecting later malformed data.
A negative return does not roll back state.
The parser ignores protocol version differences and does not enforce the stream attribute-list length.
Validate untrusted inputs and review the [coverage gaps](tester.md#coverage).

## Drive time

~~~mermaid
sequenceDiagram
    participant Platform
    participant Timer as Global timer list
    participant Core as All applications
    loop Once per centisecond
        Platform->>Timer: Advance one tick
        Timer->>Core: Run expired callbacks
        Core->>Core: Apply events and rearm
    end
~~~

Call [shlan_timer_tick](../src/ports/timer.c) once per centisecond for the whole library.
Alternatively, one call to [mrp_tick](../src/core/mrp_mad.c) advances that same global list.
Do not call both.
Do not call the latter once per port or application.
It ignores its arguments and advances all timers.

The [defaults](../src/include/shish_lan/mrp.h) use 20 centiseconds for periodic events, 60 for Leave, and 1000 for LeaveAll.
The [implementation](../src/core/mrp_mad.c) uses fixed intervals and does not randomize LeaveAll.
Reference: [IEEE 802.1Q-2018, clause 10.7.11](https://standards.ieee.org/ieee/802.1Q/6844/).

Use [mrp_set_periodic](../src/include/shish_lan/mrp.h) to enable or disable periodic events on a port.
Use [mrp_port_role_change](../src/include/shish_lan/mrp.h) to deliver Flush or Re-declare events.
These calls do not implement topology discovery or propagation filtering.

## Lifetime and concurrency

~~~mermaid
sequenceDiagram
    participant Host
    participant Core as MRP state
    participant Timer as Global timer service
    Host->>Core: Withdraw local declarations
    Note over Host,Core: Withdrawal does not send a frame
    Host->>Timer: Stop all future ticks and callbacks
    Host->>Core: Destroy application
    Note over Host,Timer: Current timer list retains freed links
~~~

Call the matching [application destroy operation](../src/include/shish_lan/mrp.h) only after all callbacks and accesses have stopped.
The [destructor](../src/core/mrp_mad.c) frees embedded timers without unlinking them from the [global list](../src/ports/timer.c).
Any later tick can access freed memory.
Avoid application destruction and recreation while the timer service remains usable.
A timer lifetime fix is required for dynamic deployment.

Serialize receive, declaration, timer, and destruction operations.
The [protocol state](../src/core/mrp_mad.c) and [timer list](../src/ports/timer.c) provide no locks.
Keep callbacks short and avoid reentry into the same application.
Do not mistake the separate register queue's concurrency contract for protocol thread safety.

## Switch adapter sequence

~~~mermaid
sequenceDiagram
    participant Host
    participant Adapter
    Host->>Adapter: Create
    Adapter-->>Host: Switch handle
    Host->>Adapter: Connect
    Host->>Adapter: Enable or disable port
    Adapter-->>Host: Status code
    Host->>Adapter: Disconnect
    Host->>Adapter: Destroy
~~~

Use [shlan_sim_adapter_create](../src/modules/sim_adapter.c) and [shlan_sim_adapter_destroy](../src/modules/sim_adapter.c) for simulation.
Call [shlan_connect, shlan_port_enable, shlan_port_disable, and shlan_disconnect](../src/include/shish_lan/switch.h) through the switch handle.
These wrappers are inline C functions.
They are not exported entry points for dynamic foreign-function loading.

| Simulation provides | A real adapter must provide |
| --- | --- |
| 48 in-memory port flags. | Hardware port configuration and error handling. |
| Connection resets flags. | Hardware initialization and shutdown. |
| Range checks for port operations. | Platform limits and synchronization. |
| No forwarding or register model. | Frame transport and any register bus access. |

The [simulation implementation](../src/modules/sim_adapter.c) supplies only the left column.
No real adapter is included.

## Register queue sequence

~~~mermaid
sequenceDiagram
    participant Producer
    participant Queue
    participant Driver as Single consumer
    participant Bus
    Producer->>Queue: Enqueue descriptor
    Driver->>Queue: Dispatch
    Driver->>Bus: Read or write
    Bus-->>Driver: Result
    Driver->>Producer: Completion callback
~~~

Initialize with [shlan_ctrl_queue_init](../src/include/shish_lan/switch_ctrl.h).
Prepare descriptors with [shlan_ctrl_xfer_set](../src/include/shish_lan/switch_ctrl.h), then call [shlan_ctrl_enqueue](../src/include/shish_lan/switch_ctrl.h).
One consumer calls [shlan_ctrl_dispatch](../src/include/shish_lan/switch_ctrl.h) with hardware callbacks.
Follow the [descriptor lifetime and linked-chain contract](../src/include/shish_lan/switch_ctrl.h).
A missing linked successor can block dispatch forever.
Do not reuse a descriptor until a later dequeue releases its queue link.

## Embedded module and bare metal

The [Zephyr module](../zephyr/module.yml) points to the [root build definition](../CMakeLists.txt) and [configuration](../Kconfig.zephyr).
Add the repository through the platform's [module mechanism](https://docs.zephyrproject.org/latest/develop/modules.html).
Enable [CONFIG_LWSRP](../Kconfig.zephyr) in the application configuration.
The module builds protocol sources with default platform ports.
It supplies no application entry point, network driver, or board example.
Target execution has not been verified here.

A dedicated bare-metal port is planned.
The [documentation assignment](https://github.com/kebag-logic/lwSRP/issues/1#issuecomment-6030336537) identifies that separate work.
No dedicated tracking issue or pull request was available during this review.
For a custom integration, select the protocol sources from the [module source list](../CMakeLists.txt).
Provide allocation, printing, and serialized timing.
Resolve the lifetime and transmit gaps before production use.
