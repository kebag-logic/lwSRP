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
| Host tests | [Runner](../tests/unit/main.c), [codec suite](../tests/unit/mrp_pdu_test.c), [scenario bindings](../tests/features/switch_bindings.c), [steps](../tests/features/steps/switch_steps.py) | Codec assertions and switch-operation scenarios. |

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
    Port --> List[Attribute list]
    Port --> Timers[Port timers]
    List --> Value[Value and identity]
    List --> Machines[Applicant and Registrar]
    List --> Leave[Leave timer]
~~~

The [application handle](../src/include/shish_lan/mrp.h) owns a copied callback table and private state.
The [private structures](../src/core/mrp_mad.c) allocate a flexible port array and linked attribute lists.
Port timers drive LeaveAll and periodic events; each attribute has its own Leave timer.
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

The graphs below show selected paths checked against the normative tables.
Each comparison states its scope and links implementation differences.
They describe full participants unless a condition says otherwise.
They omit other event paths and most unchanged transitions.
They are not a complete conformance model or evidence of tested behavior.

### Applicant declarations

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [declaration rows](../src/core/mrp_mad.c#L125-L174) and [Applicant handler](../src/core/mrp_mad.c#L496-L506).

~~~mermaid
stateDiagram-v2
    [*] --> VO: Begin
    VO --> VP: Join
    VO --> VN: New
    VN --> AN: tx / New
    AN --> QA: tx / New, Registrar IN
    AN --> AA: tx / New, Registrar not IN
    VP --> AA: tx / Join
    AA --> QA: tx / Join
    QA --> QA: Join
~~~

These abbreviations name [Applicant states](../src/include/shish_lan/mrp.h).
VO means Very anxious Observer; VP means Very anxious Passive.
VN means Very anxious New; AN means Anxious New.
AA means Anxious Active; QA means Quiet Active.
Transmit labels describe required protocol actions.
The [implementation](../src/core/mrp_mad.c#L496-L506) only records pending messages.

Comparison: matches the table for the displayed transitions, including the Registrar condition.
Transmission assumes sufficient frame space, as required by [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, note 7](https://standards.ieee.org/ieee/802.1Q/6844/).

| Implementation difference | Code evidence |
| --- | --- |
| Transmitting from AN always reaches QA; the Registrar condition is absent. | [Transmit row](../src/core/mrp_mad.c#L156-L157). |
| Join moves QA to AA; the table keeps QA. Join leaves LA unchanged; the table requires AA. | [Join row](../src/core/mrp_mad.c#L133-L140). |
| New leaves AA, QA, and LA unchanged; the table requires VN. | [New row](../src/core/mrp_mad.c#L125-L132). |
| Transmission from QA schedules In or Mt; the table permits an optional Join. | [Transmit row](../src/core/mrp_mad.c#L160-L161). |

The [Applicant handler](../src/core/mrp_mad.c#L496-L506) has no frame-space check or transmit-opportunity request on state entry.
No public operation completes the transmit cycle.

### Applicant observation

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [receive-event rows](../src/core/mrp_mad.c#L213-L239).

~~~mermaid
stateDiagram-v2
    direction LR
    VO --> AO: rJoinIn, shared
    AO --> QO: rJoinIn
    QO --> AO: rJoinMt
    VP --> AP: rJoinIn, shared
    AP --> QP: rJoinIn
    QP --> AP: rJoinMt
~~~

AO means Anxious Observer; QO means Quiet Observer.
AP means Anxious Passive; QP means Quiet Passive.
These names come from the [state enum](../src/include/shish_lan/mrp.h).
The prefix r marks a received event.
Shared means the point-to-point subset is disabled and the operational MAC is not point-to-point.
Comparison: matches the table for the displayed transitions with that condition.
Local Join moves AO to AP and QO to QP in the [Applicant table](../src/core/mrp_mad.c#L133-L140).

| Implementation difference | Code evidence |
| --- | --- |
| The VO and VP receive transitions ignore the shared-link condition. | [Receive row](../src/core/mrp_mad.c#L213-L220), [handler](../src/core/mrp_mad.c#L496-L506). |
| Received JoinIn moves LA to QO; the table keeps LA. | [Receive row](../src/core/mrp_mad.c#L217-L219). |
| Received In moves AA to QA without the required operational point-to-point condition. | [Received In row](../src/core/mrp_mad.c#L229-L233). |

The conditions come from [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, notes 3–5](https://standards.ieee.org/ieee/802.1Q/6844/).

### Applicant withdrawal

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [withdrawal row](../src/core/mrp_mad.c#L141-L148) and [transmit rows](../src/core/mrp_mad.c#L149-L210).

~~~mermaid
stateDiagram-v2
    VN --> LA: Leave
    AN --> LA: Leave
    AA --> LA: Leave
    QA --> LA: Leave
    LA --> VO: tx / Leave
    LO --> VO: tx / In or Mt
~~~

LA means Leaving Active; LO means Leaving Observer.
See the [state enum](../src/include/shish_lan/mrp.h) for all twelve states.
Comparison: matches the table for the displayed transitions when the frame has space.
The [implementation](../src/core/mrp_mad.c#L162-L163) instead sends LA to LO on ordinary transmission.

Other recovery paths also differ from [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).

| Event | Implementation difference | Code evidence |
| --- | --- | --- |
| Transmit with LeaveAll | VP enters LO, not AA, and schedules Join instead of In or Mt. | [VP entry](../src/core/mrp_mad.c#L178-L179). |
| Transmit with LeaveAll | AN and AA enter VP, not QA. | [AN and AA entries](../src/core/mrp_mad.c#L182-L185). |
| Transmit with LeaveAll | LA schedules Leave instead of optional In or Mt. | [LA entry](../src/core/mrp_mad.c#L188-L189). |
| Transmit with LeaveAll | QP enters LO with In or Mt; the table requires QA with Join. | [QP entry](../src/core/mrp_mad.c#L196-L197). |
| Full frame with LeaveAll | QP stays QP instead of entering VP. | [Full-frame row](../src/core/mrp_mad.c#L201-L210). |
| Received Leave, LeaveAll, or re-declaration | AN enters VP instead of VN; QA stays QA instead of entering VP; LA enters LO instead of staying LA. | [Recovery rows](../src/core/mrp_mad.c#L240-L261). |
| Periodic event | QA and QP remain quiet instead of becoming AA and AP. AA and AP schedule Join without a table action. | [Periodic row](../src/core/mrp_mad.c#L262-L269). |

Participant variants also require event filtering and state restrictions.
The [unconditional handler](../src/core/mrp_mad.c#L496-L506) does not implement those rules.
Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, notes 1–4 and 12](https://standards.ieee.org/ieee/802.1Q/6844/).

### Registrar

Reference: [IEEE 802.1Q-2018, clause 10.7.8, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [Registrar table](../src/core/mrp_mad.c#L312-L396) and [indication handler](../src/core/mrp_mad.c#L551-L583).

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
Comparison: matches the table for the displayed state transitions.
The graph omits indication and timer actions.
The [Registrar table](../src/core/mrp_mad.c#L331-L335) also enters LV on transmit-with-LeaveAll.
Its [re-declaration row](../src/core/mrp_mad.c#L378-L383) does the same.
Local Join and Leave events do not change Registrar state.

| Implementation difference | Code evidence |
| --- | --- |
| Local New drives registration, although the table defines received New only. | [Local New row](../src/core/mrp_mad.c#L319-L324), [event delivery](../src/core/mrp_mad.c#L615-L626). |
| Received Join in LV emits an extra Join indication. The table stops the Leave timer and enters IN without that indication. | [Join rows](../src/core/mrp_mad.c#L344-L355), [callback](../src/core/mrp_mad.c#L572-L575). |
| Received LeaveAll delivers rLA! across all attribute types on the port. It affects both Applicants and Registrars. | [Receive handler](../src/core/mrp_mad.c#L836-L842), [issue #7](https://github.com/kebag-logic/lwSRP/issues/7). |

The extra indication also invokes propagation policy.
The standard limits received LeaveAll to the message's attribute type: [IEEE 802.1Q-2018, clause 10.7.5.20](https://standards.ieee.org/ieee/802.1Q/6844/).
A Listener LeaveAll therefore also moves Talker registrations from IN to LV in the current implementation.
The [parser](../src/core/mrp_pdu.c#L155-L156) delivers LeaveAll once per marked vector.

### LeaveAll

Reference: [IEEE 802.1Q-2018, clause 10.7.9, Table 10-5](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [la_event](../src/core/mrp_mad.c#L640-L674).

~~~mermaid
stateDiagram-v2
    direction LR
    [*] --> Passive: Begin
    Passive --> Active: timer
    Active --> Passive: tx or rLA
    Active --> Active: timer
    Passive --> Passive: rLA
~~~

Comparison: matches the table for the displayed state transitions.
Begin resets either state to Passive.
Begin, reception, and expiry restart the timer; expiry requests transmission.
Active transmission requires a LeaveAll message and local LeaveAll processing.

| Implementation difference | Code evidence |
| --- | --- |
| Active transmission restarts the timer; the table does not specify that action. | [Transmit branch](../src/core/mrp_mad.c#L649-L657). |
| Transmission broadcasts a local event but sends no LeaveAll message. It lacks a public caller. | [Transmit branch](../src/core/mrp_mad.c#L649-L657), [public operations](../src/core/mrp_mad.c#L736-L883). |
| The timer interval is fixed instead of randomized. | [Timer arming](../src/core/mrp_mad.c#L640-L669). |

The interval rule is in [IEEE 802.1Q-2018, clause 10.7.4.3](https://standards.ieee.org/ieee/802.1Q/6844/).
An active state does not prove that a LeaveAll frame was sent.

### PeriodicTransmission

Reference: [IEEE 802.1Q-2018, clause 10.7.10, Table 10-6](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [pt_event](../src/core/mrp_mad.c#L680-L701) and [mrp_set_periodic](../src/core/mrp_mad.c#L872-L883).

~~~mermaid
stateDiagram-v2
    direction LR
    [*] --> Active: Begin
    Active --> Active: timer
    Active --> Passive: disable
    Passive --> Active: enable
~~~

Comparison: matches the table for the displayed state transitions.
Begin activates either state and arms the timer.
Enable arms the timer when Passive; Active expiry rearms it and generates a periodic event.

| Implementation difference | Code evidence |
| --- | --- |
| The periodic interval is 20 centiseconds instead of one second. | [Begin and expiry](../src/core/mrp_mad.c#L684-L694), [enable](../src/core/mrp_mad.c#L876-L878). |
| Disable additionally stops the timer; the table only changes state. | [Disable branch](../src/core/mrp_mad.c#L879-L882). |

The interval is specified by [IEEE 802.1Q-2018, clause 10.7.4.4](https://standards.ieee.org/ieee/802.1Q/6844/).
The [expiry handler](../src/core/mrp_mad.c#L689-L695) broadcasts the periodic event and marks transmission pending.
The [Applicant periodic row](../src/core/mrp_mad.c#L262-L269) then diverges as listed above.
No frame is emitted.
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
