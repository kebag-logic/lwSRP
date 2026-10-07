<!-- SPDX-License-Identifier: Apache-2.0 -->
# Architecture

This page gives developers and integrators a map of the current boundaries.
Start with the [developer guide](developer.md) for extension work.
Use the [integrator guide](integrator.md) for platform work.

## Ports and adapters

~~~mermaid
flowchart TD
    Host[Host policy] --> Apps[Protocol applications]
    Apps --> Vtable[Application callbacks]
    Vtable --> MAD[Declaration state]
    MAD --> Codec[PDU codec]
    MAD --> Clock[Timer port]
    MAD --> Heap[Allocation port]
    Host --> Switch[Switch operations]
    Switch --> Sim[Simulation adapter]
    Driver[Future hardware driver] -.-> Queue[Register queue]
~~~

The [application callbacks](../src/include/shish_lan/mrp.h) connect applications to the [declaration state](../src/core/mrp_mad.c).
The [codec](../src/core/mrp_pdu.c) parses payloads and provides encoding helpers.
The [timer port](../src/ports/timer.h) and [allocation port](../src/ports/alloc.h) isolate platform services.

The [switch operations](../src/include/shish_lan/switch.h) control ports independently of MRP.
The [simulation adapter](../src/modules/sim_adapter.c) implements those operations in memory.
The [register queue](../src/core/switch_ctrl.c) is separate and excluded from the current [build](../CMakeLists.txt).
No hardware driver connects these pieces yet.

## Receive path

~~~mermaid
flowchart TD
    Payload[MRP payload] --> Parse[Parse vectors]
    Parse --> Decode[Decode value]
    Decode --> State[Apply event]
    State --> Notify[Notify host]
    Notify --> Policy[Choose propagation ports]
    Policy --> Declare[Declare on target ports]
~~~

The host passes payloads to [mrp_rx](../src/core/mrp_mad.c).
The [parser](../src/core/mrp_pdu.c) calls the application's [decode callback](../src/include/shish_lan/mrp.h).
The [state engine](../src/core/mrp_mad.c) then delivers indications and applies propagation policy.
Only the [stream application](../src/modules/msrp.c) currently supplies propagation callbacks.

Propagation updates target Applicants through [mrp_mad_join](../src/core/mrp_mad.c) with the new flag false.
The Registrar ignores that local Join event.
This prevents recursive indications on target ports.
It does not establish network loop safety.

## Missing boundary

~~~mermaid
flowchart LR
    Declare[Local declaration] --> Pending[Pending state]
    Pending -.-> Assembly[Missing transmit assembly]
    Assembly -.-> Frame[Missing frame transport]
~~~

The [state engine](../src/core/mrp_mad.c) stores pending transmit actions.
No public API drains them into frames.
The [encoding helpers](../src/include/shish_lan/mrp_pdu.h) do not complete this boundary.
See the [scope matrix](manager.md#implementation-status) before making interoperability claims.

## Test layout

| Entry | Purpose |
| --- | --- |
| [Unit runner](../tests/unit/main.c) | Codec suite runner. |
| [Scenario bindings](../tests/features/switch_bindings.c) | Switch wrapper bindings. |

Use the [tester guide](tester.md) to run these checks and interpret their limits.
