<!-- SPDX-License-Identifier: Apache-2.0 -->
# Integrator guide

Use this guide to connect platform services and plan hardware integration.
Start with the [scope matrix](manager.md#implementation-status).
The library validates received payloads and assembles transactional output.
Your adapter supplies Ethernet transport, admission policy, and hardware integration.

## Build choices

The [root build definition](../CMakeLists.txt) selects between host and embedded module builds.

| Setting | Current behavior |
| --- | --- |
| Host build | Produces a shared library with applications, ports, and simulation. |
| C language | Requires [C11 draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf). |
| [CMAKE_BUILD_TYPE](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html) set to Debug | Adds compiler debugging information through [CMake](https://cmake.org/cmake/help/latest/). |
| Export compile commands | Enabled by the [build definition](../CMakeLists.txt). |
| Unit dependency found | Builds the [unit runner](../tests/unit/main.c) with eight suites. |
| Unit dependency absent | Host configuration fails. Headers and library are required. |
| [ZEPHYR_BASE](../CMakeLists.txt) defined | Selects the module branch and returns before host configuration. |
| [CONFIG_LWSRP](../Kconfig.zephyr) enabled | Builds protocol sources and default allocation and timer ports. |
| [LWSRP_MILAN](../CMakeLists.txt) enabled | Selects immediate MSRP withdrawal on received Leave in IN. Defaults to OFF. |

There are no project options for hardware selection or coverage.
The [register queue](../src/core/switch_ctrl.c) is absent from both source lists.
The [build wrapper](../build.sh) only creates an environment and sets variables inside its process.
It does not build the library.
Use the [quick start commands](../README.md#quick-start).

## Milan received Leave

Enable [LWSRP_MILAN](../CMakeLists.txt) when building MSRP for the Milan profile.
The setting applies to both host and embedded module builds.
For direct source builds, define [LWSRP_MILAN](../src/include/shish_lan/msrp.h) as 1 when compiling the stream application.
Rebuild the library and consumers after changing the public [application operations](../src/include/shish_lan/mrp.h) layout.
Follow the [profile test commands](tester.md#test-both-registrar-profiles) to check the selected behavior.

The [MSRP constructor](../src/modules/msrp.c) copies the selected option into each application.
Custom applications opt in through [milan_rapid_leave](../src/include/shish_lan/mrp.h) before calling [mrp_app_create](../src/core/mrp_mad.c).
Zero-initialized operations retain the default [IEEE 802.1Q-2018, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/) behavior.
The standard VLAN and MAC constructors leave the option disabled.

~~~mermaid
sequenceDiagram
    participant Host
    participant Core as MSRP state
    Host->>Core: Receive Leave while IN
    Core->>Core: Enter MT
    Core-->>Host: Leave indication
    Note over Host,Core: Completed before receive returns
~~~

This sequence implements [Milan v1.2, clause 4.2.7.2.2](https://milanav.com/milan-faqs/).
It applies to an explicit received Leave in IN.
A Leave received in LV preserves the original Leave timer deadline.
Received LeaveAll still starts normal aging from IN.
Local withdrawal does not remove a peer registration.
The option does not select timer values or establish complete Milan conformance.
Keep indication handlers within the [serialized callback contract](#lifetime-and-concurrency).

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
The [timer interface](../src/ports/timer.h) defines initialization, one-shot arming, cancellation, removal, and ticking.
A fixed pool can replace the default heap.
Allocation failure returns a negative result.
Earlier received attributes may remain applied when a later allocation fails.

## Create and declare

~~~mermaid
sequenceDiagram
    participant Host
    participant App as Application
    participant Core as State
    participant Timer as Timers
    Host->>App: Create application
    App->>Core: Allocate state
    Core->>Timer: Arm port timers
    App-->>Host: Handle or null
    Host->>Core: Configure port
    Host->>App: Declare a value
    App->>Core: Apply local event
    Core-->>Host: Status code
~~~

Use zero-based port identifiers within the created port count.
Validate them before calls; some [MRP operations](../src/core/mrp_mad.c) assume valid handles and ports.
Limit propagation to 32 ports.
Keep a non-null callback context alive throughout the application lifetime.
Check creation for null and declarations for negative results.
Call [mrp_port_configure](../src/include/shish_lan/mrp.h) before creating any attribute state.
Set Join, Leave, LeaveAll, a random seed, and the point-to-point condition.

| Application | Create | Declare | Withdraw |
| --- | --- | --- | --- |
| VLAN | [mvrp_app_create](../src/modules/mvrp.c) | [mvrp_declare](../src/modules/mvrp.c) | [mvrp_withdraw](../src/modules/mvrp.c) |
| MAC | [mmrp_app_create](../src/modules/mmrp.c) | [mmrp_declare_mac or mmrp_declare_svc](../src/modules/mmrp.c) | [mmrp_withdraw_mac or mmrp_withdraw_svc](../src/modules/mmrp.c) |
| Stream | [msrp_app_create](../src/modules/msrp.c) | [msrp_declare_talker or msrp_declare_listener](../src/modules/msrp.c) | [msrp_withdraw_talker or msrp_withdraw_listener](../src/modules/msrp.c) |

VLAN identifiers must be between 1 and 4094.
The [receive decoder](../src/modules/mvrp.c) checks this range; the declaration wrapper does not.
The [MAC adapter](../src/modules/mmrp.c) accepts MAC addresses or service requirements.
The [stream interface](../src/include/shish_lan/msrp.h) defines Talker structures and Listener declaration values.
Declare Domain through [mrp_mad_join](../src/include/shish_lan/mrp.h) with [MSRP_ATTR_TYPE_DOMAIN](../src/include/shish_lan/msrp.h).
Local declarations request transmission without calling the transport.
Call the [Listener declaration wrapper](../src/include/shish_lan/msrp.h) on changes, rather than on every poll.

## Receive and observe

~~~mermaid
sequenceDiagram
    participant Host
    participant Core as State
    participant Codec
    participant Policy as Callbacks
    Host->>Core: Submit payload
    Core->>Codec: Validate payload
    Codec->>Codec: Parse vectors
    Codec->>Core: Decoded events
    Core->>Policy: Check interest
    Core->>Core: Find or allocate
    Core->>Core: Reserve possible targets
    Core->>Policy: Indicate registration
    Core->>Policy: Select propagation ports
    Core->>Core: Queue and replay targets
    Core->>Host: Observe transition
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

The [parser](../src/core/mrp_pdu.c) validates the complete wire structure and decoded application ranges before delivering state-changing events.
It checks vector lengths, packed events, stream message boundaries, and vector arithmetic.
A complete vector may end at the actual payload boundary without explicit EndMarks.
Higher protocol versions skip unknown stream messages to the advertised list boundary, regardless of their vector layout.
Unknown VLAN and MAC messages use advertised value lengths and vector boundaries through the EndMark.
Unrecognized events discard their vector; subsequent supported content still applies.
This follows [IEEE 802.1Q-2018, clauses 10.8.3.5 and 35.2.2](https://standards.ieee.org/ieee/802.1Q/6844/).
Current-version unknown types and reserved events reject the complete payload.
Invalid decoded ranges and overflowing vector increments also reject the complete payload, in both profiles.
Ignored Listener subtypes produce no attribute indication.
Allocation errors can still leave earlier valid values applied.

Received LeaveAll reaches only the message's type on the ingress port.
The [handler](../src/core/mrp_mad.c) also restarts the participant LeaveAll timer.
This follows [IEEE 802.1Q-2018, clause 10.7.5.20](https://standards.ieee.org/ieee/802.1Q/6844/).
Set [mrp_set_rx_filter](../src/include/shish_lan/mrp.h) to retain only relevant end-station values before allocation.
The filter does not suppress LeaveAll for existing values.
Call [mrp_reclaim](../src/include/shish_lan/mrp.h) outside callbacks to release undeclared, unregistered, quiescent values.
It leaves state intact during prepared transmission.

## Transmit and retry

~~~mermaid
sequenceDiagram
    participant Dispatcher as Serialized loop
    participant Core as State
    participant Driver as Frame transport
    Dispatcher->>Core: Poll persistent buffer
    Core->>Driver: Offer complete payload
    alt Accepted
        Driver-->>Core: Zero
        Core->>Core: Commit transmitted state
        Core-->>Dispatcher: One
    else Refused
        Driver-->>Core: Negative result
        Core->>Core: Retain exact buffer
        Core-->>Dispatcher: Negative result
        Dispatcher->>Core: Retry after driver progress
    end
~~~

Call [mrp_transmit](../src/include/shish_lan/mrp.h) for each port on every loop pass.
A zero result means no opportunity is due.
A result of one means the transport accepted a complete PDU.
A negative result reports refusal or an assembly error.
The [send callback](../src/include/shish_lan/mrp.h) returns zero only after accepting all bytes.
It must copy or take responsibility for the payload before returning zero.

Keep one persistent buffer per port with retained output.
After refusal, leave its bytes unchanged and retry until acceptance.
Queue incoming payloads and local declarations for that port while output is retained.
The core rejects those operations during retention.
Defer topology changes, reconfiguration, and destruction until the retained output has been resolved.
Continue global ticks; Registrar Leave timers still expire.
Periodic Applicant work waits until acceptance.

Internal [propagation](../src/core/mrp_mad.c) uses a separate FIFO per destination port.
Each queued operation owns its value copy, independent of source buffers and reclaimed source registrations.
The core replays these operations after committing accepted output, before the next transmission.
This preserves registration and timer-driven withdrawal order while the host continues servicing other ports.
The queue drains during later polls if destination allocation temporarily fails.
Size allocation capacity for the propagation accumulated during transport refusal.
Each indication with propagation policy first reserves one entry per possible target, up to 32 entries.
The host indication precedes policy selection; unused entries are freed.
A reservation failure preserves the prior source value and state without issuing the corresponding indication.
Retry the received payload after allocation becomes available.
Earlier completed events in that payload remain applied.
Receive reports allocation failures; a timer withdrawal retries allocation on the next tick.
Destroying the application releases remaining queued operations.

~~~mermaid
sequenceDiagram
    participant Source as Source port
    participant Queue as Destination queue
    participant Target as Retained port
    Source->>Queue: Copy propagated Join
    Source->>Queue: Copy propagated Leave
    Target->>Target: Accept retained output
    Target->>Queue: Replay FIFO
    Queue->>Target: Apply Join then Leave
    Target->>Target: Schedule next output
~~~

The [assembler](../src/core/mrp_mad.c#L1285) splits populations across Join-spaced opportunities.
Previously omitted attributes precede repeated declarations.
Size the buffer for the largest single message and the application's LeaveAll preamble.
Insufficient space for any required value returns the [no-buffer error](../src/include/shish_lan/error.h).
Do not treat successful local declaration as proof of network transmission.

The host adds Ethernet headers and selects the physical interface.
Use the application's [group address and EtherType](../src/include/shish_lan/mrp.h).
The [stream destination](../src/modules/msrp.c#L415) is 01-80-C2-00-00-0E.
It matches [IEEE 802.1Q-2018, clause 35.2.2.1 and Table 8-1](https://standards.ieee.org/ieee/802.1Q/6844/).
The [address regression](../tests/unit/integration_test.c) also pins the MAC and VLAN destinations.

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
Deliver every elapsed centisecond, including ticks coalesced by the platform.

The [timer defaults](../src/include/shish_lan/mrp.h) are Join 20, Leave 60, and LeaveAll 1000 centiseconds.
The Mark II profile uses Leave 500 centiseconds through [mrp_port_configure](../src/include/shish_lan/mrp.h).
Combine this interval with the [Milan received-Leave option](#milan-received-leave) for immediate explicit withdrawals.
The [periodic handler](../src/core/mrp_mad.c#L801) uses 100 centiseconds independently of Join spacing.
LeaveAll draws lie strictly between its configured interval and 1.5 times that interval.
The rules are in [IEEE 802.1Q-2018, clauses 10.7.4.3 and 10.7.4.4](https://standards.ieee.org/ieee/802.1Q/6844/).
Supply different seeds where independent participants need different timing.
See the [state comparison](developer.md#state-machines) for remaining limits.

Use [mrp_set_periodic](../src/include/shish_lan/mrp.h) to enable or disable periodic events on a port.
Use [mrp_port_role_change](../src/include/shish_lan/mrp.h) to deliver Flush or Re-declare events.
These calls do not implement topology discovery or propagation filtering.

## Lifetime and concurrency

~~~mermaid
sequenceDiagram
    participant Host
    participant Core as State
    participant Timer as Timers
    Host->>Core: Withdraw local declarations
    Host->>Core: Poll withdrawal
    Host->>Core: Stop application accesses
    Host->>Core: Destroy application
    Core->>Timer: Unlink owned timers
    Note over Host,Timer: Other applications can keep ticking
~~~

Call the matching [application destroy operation](../src/include/shish_lan/mrp.h) only after all callbacks and accesses have stopped.
The [destructor](../src/core/mrp_mad.c#L901) unlinks all owned timers before releasing storage.
Other applications may continue ticking afterward.
Destruction itself does not transmit withdrawals.
Complete any required network withdrawal before teardown.

Serialize receive, declaration, transmit, timer, reclamation, and destruction operations.
One dispatcher owns the process-global timer list and allocator.
The [protocol state](../src/core/mrp_mad.c) and [timer list](../src/ports/timer.c) provide no locks.
Transport callbacks, indications, observers, and filters must never synchronously reenter the owning application.
Queue future work instead.
The firmware adapter owns debug and release enforcement of this contract.
The core's send guard is not a general reentrancy check.
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
The [dispatch implementation](../src/core/switch.c) exports these operations for C and foreign-function callers.
The host [scenario bindings](../tests/features/switch_bindings.c) export separate test entry points that call these public operations.
The [scenario setup](../tests/features/environment.py) loads those bindings.

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
The module builds protocol sources, [switch dispatch](../src/core/switch.c), and default platform ports.
It supplies no application entry point, network driver, or board example.
Target execution has not been verified here.

For bare metal, compile the [state engine](../src/core/mrp_mad.c), [codec](../src/core/mrp_pdu.c), and [timer service](../src/ports/timer.c).
Include the [switch dispatch implementation](../src/core/switch.c) when using the public switch interface.
Add the selected [stream](../src/modules/msrp.c), [VLAN](../src/modules/mvrp.c), or [MAC](../src/modules/mmrp.c) applications.
Provide the [allocation and print ports](../src/ports/alloc.h), and omit their hosted implementation and the simulated switch.
The core uses fixed-width types, alignment, and memory operations.
It does not require hosted allocation or error headers.
The [freestanding check](../tests/check_freestanding.py) verifies strict host compilation and header dependencies.
The [embedded source-list check](../tests/check_embedded.py) links the actual module list and exercises switch dispatch in both profiles.
These host checks do not replace a target build or linker check.

Read the [serialized lifetime contract](#lifetime-and-concurrency) and [transmit contract](#transmit-and-retry) before connecting interrupts or DMA.
Schedule receive and timer work onto the same dispatcher.
Validate target timing, frame ownership, and network interoperability before deployment.
