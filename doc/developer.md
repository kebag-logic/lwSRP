<!-- SPDX-License-Identifier: Apache-2.0 -->
# Developer guide

Use this guide to change protocol behavior or add an application.
Read the [architecture](architecture.md) and [coding rules](../CONTRIBUTING.md#coding-rules) first.
Run the [codec tests](tester.md#run-the-existing-codec-tests) before and after changes.

## Code map

| Boundary | Source | Responsibility |
| --- | --- | --- |
| Public MRP API | [MRP interface](../src/include/shish_lan/mrp.h) | Application callbacks, events, state names, and observation. |
| Declaration engine | [MRP state implementation](../src/core/mrp_mad.c) | State transitions, timers, attribute storage, and propagation. |
| Wire codec | [Codec interface](../src/include/shish_lan/mrp_pdu.h), [implementation](../src/core/mrp_pdu.c) | Payload parsing and small encoding helpers. |
| VLAN application | [VLAN interface](../src/include/shish_lan/mvrp.h), [implementation](../src/modules/mvrp.c) | VLAN values and registration callbacks. |
| MAC application | [MAC interface](../src/include/shish_lan/mmrp.h), [implementation](../src/modules/mmrp.c) | MAC and service values. |
| Stream application | [Stream interface](../src/include/shish_lan/msrp.h), [implementation](../src/modules/msrp.c) | Talker and Listener values, plus propagation policy. |
| Platform services | [Allocation](../src/ports/alloc.h), [timers](../src/ports/timer.h) | Replaceable platform boundaries. |
| Switch control | [Switch operations](../src/include/shish_lan/switch.h), [register queue](../src/include/shish_lan/switch_ctrl.h) | Independent hardware integration surfaces. |

The layers use ports and adapters.
The [mrp_app_ops](../src/include/shish_lan/mrp.h) interface separates application meaning from protocol events.
It does not provide a frame transport.
The [switch operations](../src/include/shish_lan/switch.h) interface does not transport MRPDUs either.

## Data structures

~~~mermaid
flowchart TD
    App[Application handle] --> Ops[Copied callbacks]
    Ops --> Context[Borrowed host context]
    App --> Private[Private state]
    Private --> Port[Port array]
    Port --> Timers[LeaveAll and periodic timers]
    Port --> List[Attribute list]
    List --> Value[Value and identity]
    List --> Machines[Applicant and Registrar]
    List --> Leave[Leave timer]
~~~

The [application handle](../src/include/shish_lan/mrp.h) owns a copied callback table and private state.
The [private structures](../src/core/mrp_mad.c) allocate a flexible port array and linked attribute lists.
Each attribute stores up to 48 bytes.
The [parser](../src/core/mrp_pdu.c) uses a 64-byte temporary value buffer.
Keep decoded values within both limits.

The [attr_len](../src/include/shish_lan/mrp.h) callback gives the wire length.
The optional [attr_mem_len](../src/include/shish_lan/mrp.h) callback gives the stored length.
The [stream adapter](../src/modules/msrp.c) uses host-endian Talker structures and nine stored bytes for Listeners.
The [attr_cmp](../src/include/shish_lan/mrp.h) callback defines identity.
Existing values are refreshed when that identity matches.

The [host context](../src/include/shish_lan/mrp.h) remains caller-owned.
Keep it valid for the application lifetime.
Attribute instances remain allocated until destruction.
Read the [timer lifetime limitation](integrator.md#lifetime-and-concurrency) before destroying an application.

## State machines

The reference is [IEEE 802.1Q-2018, clause 10.7](https://standards.ieee.org/ieee/802.1Q/6844/).
Applicant and Registrar state belong to each attribute on each port.
LeaveAll and PeriodicTransmission state belong to each port.
The [implementation](../src/core/mrp_mad.c) uses two lookup tables and two event handlers.

The graphs below show selected event paths from the implementation.
They omit unchanged transitions and keep separate event families readable.
They are not a complete conformance model.
Independent comparison with the normative tables remains necessary.

### Applicant declarations

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [Applicant table and event handler](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    [*] --> VO: Begin
    VO --> VP: Join
    VO --> VN: New
    VN --> AN: tx / New
    AN --> QA: tx / New
    VP --> AA: tx / Join
    AA --> QA: tx / Join
    QA --> AA: Join
~~~

These abbreviations name [Applicant states](../src/include/shish_lan/mrp.h).
VO means Very anxious Observer; VP means Very anxious Passive.
VN means Very anxious New; AN means Anxious New.
AA means Anxious Active; QA means Quiet Active.
Transmit labels describe scheduled messages, not emitted frames.

The [Applicant handler](../src/core/mrp_mad.c) applies table entries without Registrar or point-to-point conditions.
Its comments describe conditions that the code does not enforce.
In particular, the shown AN transmit transition always reaches QA.
Do not treat the graph as proof of the normative conditional behavior.

### Applicant observation

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [receive-event rows](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    direction LR
    VO --> AO: rJoinIn
    AO --> QO: rJoinIn
    QO --> AO: rJoinMt
    VP --> AP: rJoinIn
    AP --> QP: rJoinIn
    QP --> AP: rJoinMt
~~~

AO means Anxious Observer; QO means Quiet Observer.
AP means Anxious Passive; QP means Quiet Passive.
These names come from the [state enum](../src/include/shish_lan/mrp.h).
The prefix r marks a received event.
Local Join moves AO to AP and QO to QP in the [Applicant table](../src/core/mrp_mad.c).

### Applicant withdrawal

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [withdrawal and transmit rows](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    VN --> LA: Leave
    AN --> LA: Leave
    AA --> LA: Leave
    QA --> LA: Leave
    LA --> LO: tx / Leave
    LO --> VO: tx / In or Mt
~~~

LA means Leaving Active; LO means Leaving Observer.
See the [state enum](../src/include/shish_lan/mrp.h) for all twelve states.
No public operation currently drives the complete transmit cycle.

### Registrar

Reference: [IEEE 802.1Q-2018, clause 10.7.8, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [Registrar table](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    [*] --> MT: Begin
    MT --> IN: rNew or rJoin
    IN --> IN: rNew
    IN --> LV: rLv or rLA
    LV --> IN: rNew or rJoin
    LV --> MT: leave timer
    IN --> MT: Flush
    LV --> MT: Flush
~~~

IN means registered; LV means leaving; MT means empty.
The prefix r marks reception; Join includes JoinIn and JoinMt.
The [Registrar handler](../src/core/mrp_mad.c) issues registration and deregistration callbacks.
It also enters LV on re-declaration and transmit-with-LeaveAll events.
Local Join and Leave events do not change Registrar state.
The implementation routes local New through the same registration row as received New.

### LeaveAll

Reference: [IEEE 802.1Q-2018, clause 10.7.9, Table 10-5](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [la_event](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    direction LR
    [*] --> Passive: Begin
    Passive --> Active: timer
    Active --> Passive: tx or rLA
~~~

The [handler](../src/core/mrp_mad.c) restarts its timer on expiry and reception.
Expiry requests transmission, including when already active.
Reception returns either state to Passive.
Its transmit branch also restarts the timer and broadcasts a local LeaveAll event.
That branch lacks a public transmit caller.
An active state therefore does not prove that a LeaveAll frame was sent.

### PeriodicTransmission

Reference: [IEEE 802.1Q-2018, clause 10.7.10, Table 10-6](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [pt_event and mrp_set_periodic](../src/core/mrp_mad.c).

~~~mermaid
stateDiagram-v2
    direction LR
    [*] --> Active: Begin
    Active --> Active: timer
    Active --> Passive: disable
    Passive --> Active: enable
~~~

The [implementation](../src/core/mrp_mad.c) rearms the periodic timer at 20 centiseconds.
Begin and enable arm the timer; disable stops it.
It broadcasts a periodic event and marks transmission pending.
It does not emit a frame.
Read the [timer integration sequence](integrator.md#drive-time) before using this API.

## Add an application

~~~mermaid
flowchart TD
    Identity[Define identity] --> Codec[Encode and decode]
    Codec --> Indicate[Handle indications]
    Indicate --> Policy[Choose propagation]
    Policy --> Create[Create application]
    Create --> Verify[Exercise events]
~~~

1. Define attribute types, wire lengths, and in-memory layouts beside a [public application interface](../src/include/shish_lan/mvrp.h).
2. Implement [encode_attr, decode_attr, attr_len, and attr_cmp](../src/include/shish_lan/mrp.h).
3. Provide [attr_mem_len](../src/include/shish_lan/mrp.h) when wire and stored sizes differ.
4. Provide [attr_has_subtype](../src/include/shish_lan/mrp.h) when reception includes a subtype vector.
5. Implement [join_ind and leave_ind](../src/include/shish_lan/mrp.h) with a valid host context.
6. Set optional [map_join and map_leave](../src/include/shish_lan/mrp.h) callbacks only when propagation is required.
7. Set protocol identifiers and call [mrp_app_create](../src/core/mrp_mad.c).
8. Add the application to the appropriate [build source list](../CMakeLists.txt).
9. Add meaningful [tests](tester.md#coverage) for values, malformed payloads, timers, and state transitions.

Return propagation masks using at most 32 bits.
The [VLAN](../src/modules/mvrp.c) and [MAC](../src/modules/mmrp.c) adapters currently leave propagation callbacks unset.
The [stream adapter](../src/modules/msrp.c) supplies them, but lacks topology filtering.
It ignores vector offsets when decoding stream values.
Include multi-value wire cases when extending it.

## Add an adapter

Implement the [switch operations](../src/include/shish_lan/switch.h) and allocate a handle with adapter state.
Use the [simulation adapter](../src/modules/sim_adapter.c) as a lifecycle example.
There is no generic switch factory despite the interface comment.
Define your own create and destroy operations.
Follow the [integration sequences](integrator.md#switch-adapter-sequence) for initialization and teardown.

Hardware register access can use the [queue interface](../src/include/shish_lan/switch_ctrl.h).
Include its [implementation](../src/core/switch_ctrl.c) explicitly in the platform build.
Add frame transport and transmit assembly separately.
Neither operation is supplied by the current switch interface.
