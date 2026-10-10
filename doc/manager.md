<!-- SPDX-License-Identifier: Apache-2.0 -->
# Manager guide

Use lwSRP to explore protocol integration and attribute handling in C firmware.
The current library is an early implementation base.
It is not a complete bridge, reservation engine, or certified protocol stack.
Use the matrix below to scope engineering work and acceptance evidence.

## Implementation status

Each row links the relevant standard area and implementation evidence.
The status describes inspected code, not demonstrated standards conformance.
The [state graphs](developer.md#state-machines) were checked against the normative tables.
Their default transitions match the tables; the optional profile change and implementation differences appear below.

| Standard area | Present in code | Missing or limited | Evidence |
| --- | --- | --- | --- |
| [IEEE 802.1Q-2018, clause 10.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Declarations, registration indications, and transactional output. | The host supplies frame transport. | [State engine](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Optional propagation callbacks and 32-bit port masks. | No topology gating; VLAN and MAC callbacks are unset. | [Core](../src/core/mrp_mad.c), [VLAN](../src/modules/mvrp.c), [MAC](../src/modules/mmrp.c). |
| [IEEE 802.1Q-2018, clause 10.5](https://standards.ieee.org/ieee/802.1Q/6844/) | Application identifiers and destination addresses. | The host selects the interface and adds Ethernet framing. | [Application interface](../src/include/shish_lan/mrp.h), [address tests](../tests/unit/integration_test.c). |
| [IEEE 802.1Q-2018, clause 10.7.5.20](https://standards.ieee.org/ieee/802.1Q/6844/) | Received LeaveAll reaches only its message type on the ingress port. | The participant LeaveAll timer is shared across types, as specified. | [Receive handler](../src/core/mrp_mad.c#L1069), [isolation tests](../tests/unit/integration_test.c). |
| [IEEE 802.1Q-2018, clause 10.7.7, Table 10-3](https://standards.ieee.org/ieee/802.1Q/6844/) | Graphs and implemented declaration paths match the selected table transitions. | Optional vector packing is omitted. Additional participant modes are not selectable. | [Comparison](developer.md#applicant-declarations), [Applicant handler](../src/core/mrp_mad.c#L506). |
| [IEEE 802.1Q-2018, clause 10.7.8, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/) | Graph matches the displayed transitions; local New does not register peers. Ordinary unchanged LV Join recovery stops aging without duplicate indications. Failed Flush reservations retain a value snapshot across ticks, incoming registrations, local declarations, and cross-port propagation. | Exhaustive state-path testing remains incomplete. | [Comparison](developer.md#registrar), [Registrar table](../src/core/mrp_mad.c#L325), [retry contract](integrator.md#transmit-and-retry). |
| [Milan v1.2, clause 4.2.7.2.2](https://milanav.com/milan-faqs/) | Opt-in MSRP received Leave in IN enters MT and indicates withdrawal immediately. LV retains its deadline. | Default builds retain the generic table. This option does not imply complete profile conformance. | [Build setting](integrator.md#milan-received-leave), [profile tests](../tests/unit/milan_test.c). |
| [IEEE 802.1Q-2018, clause 10.7.9, Table 10-5](https://standards.ieee.org/ieee/802.1Q/6844/) | Graph matches the displayed transitions; accepted output sends LeaveAll for every supported type. | Output depends on host polling and transport acceptance. | [Comparison](developer.md#leaveall), [transmit operation](../src/core/mrp_mad.c#L1410). |
| [IEEE 802.1Q-2018, clause 10.7.10, Table 10-6](https://standards.ieee.org/ieee/802.1Q/6844/) | Graph matches the displayed transitions; periodic work uses one second. | Disable additionally disarms the timer. Refused output defers periodic Applicant work. | [Comparison](developer.md#periodictransmission), [handler](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clauses 10.7.4.3, 10.7.4.4, and 10.7.11](https://standards.ieee.org/ieee/802.1Q/6844/) | Configurable timers, randomized LeaveAll, independent periodic timing, and timer unlinking. | Global serialized ticking and suitable seeds remain host responsibilities. | [Timer port](../src/ports/timer.c), [timing tests](../tests/unit/integration_test.c). |
| [IEEE 802.1Q-2018, clause 10.8.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Complete PDU assembly with one Message per attribute type, ascending values, Listener subtype encoding, and fair splitting across bounded payloads. | Each transmitted vector carries one value; packing optimization is absent. | [Assembler](../src/core/mrp_mad.c#L1410), [transmit tests](../tests/unit/transmit_test.c), [grouping tests](../tests/unit/grouping_test.c). |
| [IEEE 802.1Q-2018, clause 10.8.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Structural and decoded-range validation precede indications. Higher versions skip unknown stream messages by list length, VLAN/MAC messages by vector boundaries, and unknown event vectors. | Allocation failure can leave earlier valid values applied. | [Parser](../src/core/mrp_pdu.c), [receive tests](../tests/unit/receive_test.c). |
| [IEEE 802.1Q-2018, clauses 10.9–10.12](https://standards.ieee.org/ieee/802.1Q/6844/) | MAC and service codecs with host callbacks. | No filtering database, mode enforcement, or propagation policy. | [MAC adapter](../src/modules/mmrp.c). |
| [IEEE 802.1Q-2018, clause 11.2](https://standards.ieee.org/ieee/802.1Q/6844/) | VLAN codec and registration callbacks. | No VLAN table, database flush, or propagation policy. | [VLAN adapter](../src/modules/mvrp.c). |
| [IEEE 802.1Q-2018, clauses 35.2.1.3, 35.2.2.4, 35.2.2.8, and 35.2.2.9](https://standards.ieee.org/ieee/802.1Q/6844/) | Domain, Talker Advertise, Talker Failed, and Listener values with vector offsets. | No resource admission or hardware reservation. | [Stream adapter](../src/modules/msrp.c), [value tests](../tests/unit/msrp_values_test.c). |
| [IEEE 802.1Q-2018, clause 35.2.2.1 and Table 8-1](https://standards.ieee.org/ieee/802.1Q/6844/) | Stream destination is 01-80-C2-00-00-0E. | Ethernet framing remains in the host adapter. | [Destination constant](../src/modules/msrp.c#L415), [address tests](../tests/unit/integration_test.c). |
| [IEEE 802.1Q-2018, clause 35.2.2.7.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Listener subtype vectors are encoded and decoded; Ignore creates no registration. | Network interoperability remains unverified. | [Codec](../src/core/mrp_pdu.c), [assembler](../src/core/mrp_mad.c#L1410). |
| [IEEE 802.1Q-2018, clause 35.2.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Local declaration wrappers. | Full stream registration and attachment service primitives are absent. | [Stream interface](../src/include/shish_lan/msrp.h). |
| [IEEE 802.1Q-2018, clause 35.2.4](https://standards.ieee.org/ieee/802.1Q/6844/) | Talker flooding and Listener propagation toward registered Talkers. Retained ports replay queued propagation in order. | No topology gating, bandwidth checks, or hardware reservation. | [Stream policy](../src/modules/msrp.c#L138). |
| [IEEE 802.1Q-2018, clause 35.2.6](https://standards.ieee.org/ieee/802.1Q/6844/) | Received Join replaces opposite Talker registrations in IN or LV, with Leave before Join. Changed Listener and Talker values indicate and propagate in IN and LV. | Changed Listeners notify without separate Leave indications. Conflicting New registrations require host precedence policy. | [Value behavior](developer.md#stream-values-and-bounded-interests), [receive tests](../tests/unit/receive_test.c). |

No broader conformance claim follows from these rows.
The [MAC interface comments](../src/include/shish_lan/mmrp.h) disagree with its constants about attribute type numbers.
The [implementation](../src/modules/mmrp.c) uses service type 1 and MAC type 2.
Treat interoperability verification as required work.

## Maturity and evidence

~~~mermaid
flowchart TD
    Review[Inspect implementation] --> Host[Run host checks]
    Host --> Gaps[Resolve protocol gaps]
    Gaps --> Target[Validate target integration]
    Target --> Network[Run interoperability tests]
    Network --> Release[Approve deployment]
~~~

The [host build](../CMakeLists.txt) succeeds.
Its default [unit runner](../tests/unit/main.c) passes 101 tests with 24252 assertions.
The enabled [Milan build](tester.md#test-both-registrar-profiles) passes 101 tests with 24240 assertions.
The [scenario harness](../tests/features/environment.py) passes three scenarios and ten steps through [test bindings](../tests/features/switch_bindings.c).
Both [active-state and inactive-state assertions](../tests/features/steps/switch_steps.py#L27-L37) only repeat the operation and check its return code.
Neither independently reads port state.
A wrong disable binding that calls enable still passes all three scenarios.
Track the coverage defect in [issue #4](https://github.com/kebag-logic/lwSRP/issues/4).
The [tester guide](tester.md#coverage) describes what those checks cover.
There is no measured coverage percentage.

The [integration guide](integrator.md) defines serialized dispatch, persistent retry buffers, and global tick behavior.
The [embedded source-list check](../tests/check_embedded.py) links and exercises switch entry points with a host compiler in both profiles.
Hardware deployment, target builds, and network interoperability remain unverified.
A passing build alone does not establish release readiness.

## Integration scope

The [port work](https://github.com/kebag-logic/lwSRP/issues/10) includes transmit, receive validation, bounded interests, splitting, Domain, and freestanding headers.
These features are implemented and covered by [host tests and planted reversals](tester.md#planted-reversals).
The optional [immediate withdrawal change](https://github.com/kebag-logic/lwSRP/issues/11) adds profile-specific Registrar behavior and independent deadline regressions.
Target execution, bridge policy, and hardware admission remain integration work.

## Plan work by role

| Role | Action | Evidence to request |
| --- | --- | --- |
| Developer | Complete [protocol gaps](developer.md#state-machines). | State transitions, malformed-input cases, and transmit tests. |
| Integrator | Implement [platform boundaries](integrator.md#port-platform-services). | Target build, lifetime checks, and network captures. |
| Tester | Expand [coverage](tester.md#coverage). | Executed assertions and reproducible failure reports. |
| Manager | Review [release scope](https://github.com/kebag-logic/lwSRP/issues/1). | Known gaps, licence readiness, and approval criteria. |

## Licence and contributions

The public-release licence is [Apache License, Version 2.0](../LICENSE).
Read the [notice](../NOTICE).
The [release issue](https://github.com/kebag-logic/lwSRP/issues/1) required the licence and documentation before publication.
The [licence issue](https://github.com/kebag-logic/lwSRP/issues/8) added both files.

Individuals and companies contribute under the same licence.
The [contribution guide](../CONTRIBUTING.md) defines coding rules, checks, and review expectations.
Use the [issue tracker](https://github.com/kebag-logic/lwSRP/issues) to scope work.
Use the [pull request process](../CONTRIBUTING.md#pull-requests) to submit evidence.
