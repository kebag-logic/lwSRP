<!-- SPDX-License-Identifier: Apache-2.0 -->
# Developer guide

Use this guide to change protocol behavior or add an application.
Read the [architecture](architecture.md) and [coding rules](../CONTRIBUTING.md#coding-rules) first.
Run the [host checks](tester.md#run-the-suites) before and after changes.

## Code map

| Boundary | Source | Responsibility |
| --- | --- | --- |
| Public MRP API | [MRP interface](../src/include/shish_lan/mrp.h) | Application callbacks, events, state names, and observation. |
| Declaration engine | [MRP state implementation](../src/core/mrp_mad.c) | State transitions, timers, attribute storage, and propagation. |
| Wire codec | [Codec interface](../src/include/shish_lan/mrp_pdu.h), [implementation](../src/core/mrp_pdu.c) | Payload parsing and small encoding helpers. |
| VLAN application | [VLAN interface](../src/include/shish_lan/mvrp.h), [implementation](../src/modules/mvrp.c) | VLAN values and registration callbacks. |
| MAC application | [MAC interface](../src/include/shish_lan/mmrp.h), [implementation](../src/modules/mmrp.c) | MAC and service values. |
| Stream application | [Stream interface](../src/include/shish_lan/msrp.h), [implementation](../src/modules/msrp.c) | Domain, Talker, and Listener values, plus propagation policy. |
| Platform services | [Allocation](../src/ports/alloc.h), [timers](../src/ports/timer.h) | Replaceable platform boundaries. |
| Switch control | [Switch operations](../src/include/shish_lan/switch.h), [register queue](../src/include/shish_lan/switch_ctrl.h) | Independent hardware integration surfaces. |
| Host tests | [Runner](../tests/unit/main.c), [codec suite](../tests/unit/mrp_pdu_test.c), [scenario bindings](../tests/features/switch_bindings.c), [steps](../tests/features/steps/switch_steps.py) | Protocol assertions and switch-operation scenarios. |

The layers use ports and adapters.
The [mrp_app_ops](../src/include/shish_lan/mrp.h) interface separates application meaning from protocol events.
The [send callback](../src/include/shish_lan/mrp.h) supplies frame transport.
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
Port timers drive Join spacing, LeaveAll, and periodic events.
Each attribute has its own Leave timer.
Each attribute stores up to 48 bytes.
The [parser](../src/core/mrp_pdu.c) uses a 64-byte temporary value buffer.
Keep decoded values within both limits.

The [attr_len](../src/include/shish_lan/mrp.h) callback gives the wire length.
The optional [attr_mem_len](../src/include/shish_lan/mrp.h) callback gives the stored length.
The [stream adapter](../src/modules/msrp.c) uses host-endian Talker structures and nine stored bytes for Listeners.
The [attr_cmp](../src/include/shish_lan/mrp.h) callback defines identity.
Received declarations refresh matching identities.
Withdrawal and aging retain the last registered value.

The [host context](../src/include/shish_lan/mrp.h) remains caller-owned.
Keep it valid for the application lifetime.
Use [mrp_reclaim](../src/core/mrp_mad.c#L1038) to release undeclared, unregistered, quiescent attributes.
It unlinks their timers and refuses reclamation during a prepared transmission.
Read the [lifetime contract](integrator.md#lifetime-and-concurrency) before destroying an application.

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
Evidence: [declaration rows](../src/core/mrp_mad.c#L155) and [Applicant handler](../src/core/mrp_mad.c#L503).

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
The [transmit operation](../src/core/mrp_mad.c#L1258) applies these transitions after the host accepts the payload.

Comparison: matches the table for the displayed transitions, including the Registrar condition.
Transmission assumes sufficient frame space, as required by [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, note 7](https://standards.ieee.org/ieee/802.1Q/6844/).

The [Applicant handler](../src/core/mrp_mad.c#L503) implements the Registrar condition and corrected declaration transitions.
The [event dispatcher](../src/core/mrp_mad.c#L699) requests transmission for anxious and leaving states.
The [transactional assembler](../src/core/mrp_mad.c#L1258) preserves state when a required value cannot fit.
Optional packing actions are omitted; each encoded vector carries one value.

### Applicant observation

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [receive-event rows](../src/core/mrp_mad.c#L204).

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
Local Join moves AO to AP and QO to QP in the [Applicant table](../src/core/mrp_mad.c#L146).

The [Applicant handler](../src/core/mrp_mad.c#L503) checks the configured point-to-point condition.
Received JoinIn leaves LA unchanged.
Received In quiets AA only on point-to-point links.
The conditions follow [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, notes 3–5](https://standards.ieee.org/ieee/802.1Q/6844/).

### Applicant withdrawal

Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [withdrawal row](../src/core/mrp_mad.c#L169) and [transmit rows](../src/core/mrp_mad.c#L176).

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
The [transmit rows](../src/core/mrp_mad.c#L176) now match those displayed transitions.
Full payloads defer omitted values and request another Join-spaced opportunity.
A LeaveAll transmission uses the separate full-payload event for omitted values.
The [transmit tests](../tests/unit/transmit_test.c) check fairness across a split population.
The configured link condition supports full participants and their point-to-point behavior.
New-Only and Applicant-Only modes are not selectable.
Their additional restrictions remain outside this implementation.
Reference: [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3, notes 1–4 and 12](https://standards.ieee.org/ieee/802.1Q/6844/).

### Registrar

Reference: [IEEE 802.1Q-2018, clause 10.7.8, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [Registrar table](../src/core/mrp_mad.c#L322) and [indication handler](../src/core/mrp_mad.c#L613).

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
Comparison: matches the default table for the displayed state transitions.
The graph omits indication and timer actions.
The [Registrar table](../src/core/mrp_mad.c#L322) also enters LV on transmit-with-LeaveAll.
Its [re-declaration row](../src/core/mrp_mad.c#L384) does the same.
Local Join and Leave events do not change Registrar state.

Local New, Join, and Leave do not register a peer.
Received JoinIn and JoinMt in LV stop the Leave timer and enter IN.
They issue no additional Join indication or propagation callback, matching the table.
The [recovery regression](../tests/unit/review_test.c) checks both events and cancellation beyond the original deadline.
Evidence: [Registrar Join rows](../src/core/mrp_mad.c#L350).

The optional [milan_rapid_leave](../src/include/shish_lan/mrp.h) changes only received Leave in IN.
The [Registrar handler](../src/core/mrp_mad.c#L613) selects this transition before applying the normal indication and propagation actions.
The option is copied at application creation; its default is false.
The [MSRP build setting](integrator.md#milan-received-leave) enables it for stream applications.
VLAN and MAC applications retain the default table.

~~~mermaid
stateDiagram-v2
    direction LR
    IN --> MT: rLv / Lv
    IN --> LV: rLA / start timer
    LV --> LV: rLv / no restart
    LV --> MT: timer / Lv
~~~

Comparison: matches [Milan v1.2, clause 4.2.7.2.2](https://milanav.com/milan-faqs/) for the modified transition.
The specification link opens the publisher's access guidance.
This comparison uses consolidated revision 1.2.
The action Lv means a Leave indication.
The other displayed transitions follow [IEEE 802.1Q-2018, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/).
No Leave timer starts during the immediate transition.
An already leaving registration keeps its deadline and produces one indication when that deadline expires.
The [profile tests](../tests/unit/milan_test.c) check Talker Advertise, Talker Failed, and Listener registrations using a five-second interval.

Received LeaveAll affects only the message's type on its ingress port.
This matches [IEEE 802.1Q-2018, clause 10.7.5.20](https://standards.ieee.org/ieee/802.1Q/6844/).
The [receive handler](../src/core/mrp_mad.c#L1004) also restarts the shared participant LeaveAll timer.
The [integration tests](../tests/unit/integration_test.c) check both state machines across every supported multi-type application.

### LeaveAll

Reference: [IEEE 802.1Q-2018, clause 10.7.9, Table 10-5](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [la_event](../src/core/mrp_mad.c#L739).

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

The [transmit operation](../src/core/mrp_mad.c#L1258) emits one LeaveAll vector for each supported attribute type.
Acceptance makes the participant Passive and delivers local LeaveAll events.
Refusal preserves the pending payload and does not age registrations through an unsent LeaveAll.
The [timer draw](../src/core/mrp_mad.c#L733) lies strictly between the configured interval and 1.5 times that interval.
The interval rule is in [IEEE 802.1Q-2018, clause 10.7.4.3](https://standards.ieee.org/ieee/802.1Q/6844/).
An active state alone does not prove that a frame was sent.

### PeriodicTransmission

Reference: [IEEE 802.1Q-2018, clause 10.7.10, Table 10-6](https://standards.ieee.org/ieee/802.1Q/6844/).
Evidence: [pt_event](../src/core/mrp_mad.c#L779) and [mrp_set_periodic](../src/core/mrp_mad.c#L1078).

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

The [periodic handler](../src/core/mrp_mad.c#L779) uses 100 centiseconds, independently of Join spacing.
This matches [IEEE 802.1Q-2018, clause 10.7.4.4](https://standards.ieee.org/ieee/802.1Q/6844/).
Disable additionally disarms the timer; the table only changes state.
During a refused transmission, periodic work is deferred until acceptance.
Registrar Leave timers continue independently.
Read the [timer integration sequence](integrator.md#drive-time) before using this API.

## Deferred propagation

The [propagation queue](../src/core/mrp_mad.c) owns a copied value and operation for each destination.
It reserves entries before issuing the corresponding Registrar indication.
Available ports apply queued operations immediately; retained ports replay them after their prepared output commits.
Replay preserves event order and stops without discarding work when destination allocation fails.
The [multiport regressions](../tests/unit/review_test.c) cover source reclamation and delayed timer withdrawals.
The [integration contract](integrator.md#transmit-and-retry) defines polling and lifetime requirements.

## Stream values and bounded interests

The [stream codec](../src/modules/msrp.c) supports Domain, Talker Advertise, Talker Failed, and Listener values.
Domain offsets increment class and priority while preserving VID.
Reference: [IEEE 802.1Q-2018, clause 35.2.2.9](https://standards.ieee.org/ieee/802.1Q/6844/).
Talker and Listener offsets increment the StreamID unique-ID field.
Talker destination addresses also increment.
Reference: [IEEE 802.1Q-2018, clause 35.2.2.8](https://standards.ieee.org/ieee/802.1Q/6844/).
Vector increments must fit their fields; overflow rejects the complete payload before any indication.
Domain class and priority limits are checked for every value.
The [boundary tests](../tests/unit/review_test.c) include legal maxima and malformed earlier and later messages.
The [Domain callback](../src/include/shish_lan/msrp.h) follows existing context members to preserve their order.

The [receive filter](../src/include/shish_lan/mrp.h) runs after complete validation and before allocation.
Rejecting values bounds storage to the end station's interests.
It does not suppress LeaveAll for retained values of the message's type.
Changed registered Listener declarations notify the host without duplicate unchanged Join indications.
Local Listener changes use the New path, including from a quiet Applicant.

Received JoinIn or JoinMt replaces an opposite Talker registration with the same StreamID on the same port.
Conflicting New registrations remain distinguishable for host precedence policy.
Changed Listener declarations update the stored value and notify the host without a separate Leave indication.
That callback sequence differs from the replacement sequence in [IEEE 802.1Q-2018, clause 35.2.6](https://standards.ieee.org/ieee/802.1Q/6844/).
The [receive tests](../tests/unit/receive_test.c) pin the implemented behavior.

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
Its vector decoder increments stream identities and Domain fields.
Include multi-value wire cases when extending it.

## Add an adapter

Implement the [switch operations](../src/include/shish_lan/switch.h) and allocate a handle with adapter state.
Use the [simulation adapter](../src/modules/sim_adapter.c) as a lifecycle example.
There is no generic switch factory despite the interface comment.
Define your own create and destroy operations.
Follow the [integration sequences](integrator.md#switch-adapter-sequence) for initialization and teardown.

Hardware register access can use the [queue interface](../src/include/shish_lan/switch_ctrl.h).
Include its [implementation](../src/core/switch_ctrl.c) explicitly in the platform build.
Supply frame transport through the [send callback](../src/include/shish_lan/mrp.h).
PDU assembly belongs to the [protocol transmit operation](../src/core/mrp_mad.c).
