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
The [codec](../src/core/mrp_pdu.c) validates complete payloads before delivering events.
The [transmit operation](../src/core/mrp_mad.c#L1175) assembles PDUs and commits state after acceptance.
The [timer port](../src/ports/timer.h) and [allocation port](../src/ports/alloc.h) isolate platform services.

The [switch operations](../src/include/shish_lan/switch.h) control ports independently of MRP.
The [simulation adapter](../src/modules/sim_adapter.c) implements those operations in memory.
The [register queue](../src/core/switch_ctrl.c) is separate and excluded from the current [build](../CMakeLists.txt).
No hardware driver connects these pieces yet.

## Receive path

~~~mermaid
flowchart TD
    Payload[MRP payload] --> Validate[Validate complete payload]
    Validate --> Parse[Parse vectors]
    Parse --> Decode[Decode value]
    Decode --> Filter[Check receive interest]
    Filter --> Allocate[Find or allocate state]
    Allocate --> State[Apply event]
    State --> Notify[Notify host]
    Notify --> Policy[Choose propagation ports]
    Policy --> Declare[Declare on target ports]
~~~

The host passes payloads to [mrp_rx](../src/core/mrp_mad.c).
The [parser](../src/core/mrp_pdu.c) calls the application's [decode callback](../src/include/shish_lan/mrp.h).
The [state engine](../src/core/mrp_mad.c) then delivers indications and applies propagation policy.
The [application option](integrator.md#milan-received-leave) selects immediate stream withdrawal for a received Leave in IN.
Its default retains generic timer-based aging.
Only the [stream application](../src/modules/msrp.c) currently supplies propagation callbacks.

Propagation updates target Applicants through [mrp_mad_join](../src/core/mrp_mad.c) with the new flag false.
The Registrar ignores that local Join event.
This prevents recursive indications on target ports.
It does not establish network loop safety.

## Transmit boundary

~~~mermaid
flowchart TD
    Declare[Local or received event] --> Pending[Request transmission]
    Pending --> Poll[Poll after Join delay]
    Poll --> Assemble[Assemble bounded PDU]
    Assemble --> Send[Host send callback]
    Send --> Accept[Accepted: commit states]
    Send --> Refuse[Refused: retain exact bytes]
    Refuse --> Retry[Retry same buffer]
    Retry --> Send
~~~

The host calls [mrp_transmit](../src/core/mrp_mad.c#L1175) on each event-loop pass.
The callback accepts the complete payload or refuses it.
Refused payloads remain in caller-owned storage until acceptance.
The [integration contract](integrator.md#transmit-and-retry) defines buffer ownership and deferred input.
The host adds Ethernet framing and chooses the interface.
The [bounded assembler](../src/core/mrp_mad.c#L1175) serves omitted attributes before repeating earlier ones.
See the [scope matrix](manager.md#implementation-status) before making interoperability claims.

## Test layout

| Entry | Purpose |
| --- | --- |
| [Unit runner](../tests/unit/main.c) | Seven suites for codecs, timers, values, receive, transmit, integration, and profile withdrawal. |
| [Scenario bindings](../tests/features/switch_bindings.c) | Established scenario bindings around exported switch operations. |

Use the [tester guide](tester.md) to run these checks and interpret their limits.
