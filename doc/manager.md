<!-- SPDX-License-Identifier: Apache-2.0 -->
# Manager guide

Use lwSRP to explore protocol integration and attribute handling in C firmware.
The current library is an early implementation base.
It is not a complete bridge, reservation engine, or certified protocol stack.
Use the matrix below to scope engineering work and acceptance evidence.

## Implementation status

Each row links the relevant standard area and implementation evidence.
The status describes inspected code, not demonstrated standards conformance.
The public standard catalogue does not expose the normative state tables.
Independent table verification remains open.

| Standard area | Present in code | Missing or limited | Evidence |
| --- | --- | --- | --- |
| [IEEE 802.1Q-2018, clause 10.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Declaration requests and registration indications. | No complete network transmit path. | [State engine](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Optional propagation callbacks and 32-bit port masks. | No topology gating; VLAN and MAC callbacks are unset. | [Core](../src/core/mrp_mad.c), [VLAN](../src/modules/mvrp.c), [MAC](../src/modules/mmrp.c). |
| [IEEE 802.1Q-2018, clause 10.5](https://standards.ieee.org/ieee/802.1Q/6844/) | Protocol identifiers and group addresses. | No link-layer send or receive adapter. | [Application interface](../src/include/shish_lan/mrp.h). |
| [IEEE 802.1Q-2018, clause 10.7.7](https://standards.ieee.org/ieee/802.1Q/6844/) | Twelve Applicant states and an event table. | Conditional notes are not enforced; transmit events lack public scheduling. | [Applicant table and handler](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.7.8](https://standards.ieee.org/ieee/802.1Q/6844/) | Three Registrar states, callbacks, and Leave expiry. | Local New also drives registration; protocol coverage is absent. | [Registrar table](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.7.9](https://standards.ieee.org/ieee/802.1Q/6844/) | LeaveAll states and timer events. | No emitted LeaveAll frames. | [LeaveAll handler](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.7.10](https://standards.ieee.org/ieee/802.1Q/6844/) | Periodic enablement and events. | Pending actions are not transmitted. | [Periodic handler](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.7.11](https://standards.ieee.org/ieee/802.1Q/6844/) | Centisecond callback timers. | Fixed intervals; no LeaveAll randomization or timer removal. | [Timer port](../src/ports/timer.c), [state engine](../src/core/mrp_mad.c). |
| [IEEE 802.1Q-2018, clause 10.8.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Vector parsing and basic encoding helpers. | Encoder handles one value and no Listener subtype vector. | [Codec](../src/core/mrp_pdu.c). |
| [IEEE 802.1Q-2018, clause 10.8.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Length checks for several input fields. | Version and stream attribute-list length are ignored; callbacks can precede a later error. | [Parser](../src/core/mrp_pdu.c). |
| [IEEE 802.1Q-2018, clauses 10.9–10.12](https://standards.ieee.org/ieee/802.1Q/6844/) | MAC and service codecs with host callbacks. | No filtering database, mode enforcement, or propagation policy. | [MAC adapter](../src/modules/mmrp.c). |
| [IEEE 802.1Q-2018, clause 11.2](https://standards.ieee.org/ieee/802.1Q/6844/) | VLAN codec and registration callbacks. | No VLAN table, database flush, or propagation policy. | [VLAN adapter](../src/modules/mvrp.c). |
| [IEEE 802.1Q-2018, clause 35.2.1](https://standards.ieee.org/ieee/802.1Q/6844/) | Talker Advertise, Talker Failed, and Listener values. | Domain attributes and resource admission are absent. | [Stream adapter](../src/modules/msrp.c). |
| [IEEE 802.1Q-2018, clause 35.2.2.7.2](https://standards.ieee.org/ieee/802.1Q/6844/) | Listener subtype decoding after event vectors. | Stream decoding ignores vector offsets; subtype encoding is absent. | [Codec](../src/core/mrp_pdu.c), [stream adapter](../src/modules/msrp.c). |
| [IEEE 802.1Q-2018, clause 35.2.3](https://standards.ieee.org/ieee/802.1Q/6844/) | Talker flooding and Listener propagation toward registered Talkers. | No topology gating, bandwidth checks, or hardware reservation. | [Stream propagation policy](../src/modules/msrp.c). |

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
Its configured unit target passes with zero assertions.
The separate [codec suite](../tests/unit/mrp_pdu_test.c) passes nine tests with 1690 assertions through the [documented runner](tester.md#run-the-existing-codec-tests).
The [scenario harness](../tests/features/environment.py) fails before three scenarios because [shlan_connect](../src/include/shish_lan/switch.h) is not exported.
There is no measured coverage percentage.

The [integration guide](integrator.md) documents a timer lifetime defect and global tick behavior.
Hardware deployment, target builds, and network interoperability remain unverified.
A passing build alone does not establish release readiness.

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
The [release issue](https://github.com/kebag-logic/lwSRP/issues/1) requires the separate licence work and documentation before publication.
Licence files are supplied by that separate change.
Verify their presence in the combined release tree.

Individuals and companies contribute under the same licence.
The [contribution guide](../CONTRIBUTING.md) defines coding rules, checks, and review expectations.
Use the [issue tracker](https://github.com/kebag-logic/lwSRP/issues) to scope work.
Use the [pull request process](../CONTRIBUTING.md#pull-requests) to submit evidence.
