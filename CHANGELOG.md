<!-- SPDX-License-Identifier: Apache-2.0 -->
# Changelog

## Unreleased

### Build options for an end station's MRP work

[Pull request 22](https://github.com/kebag-logic/lwSRP/pull/22) adds nine build options, each off by default.
They serve [milan-fpga issue 977](https://github.com/kebag-logic/milan-fpga/issues/977) and [issue 872](https://github.com/kebag-logic/milan-fpga/issues/872).
Both are part of [issue 665](https://github.com/kebag-logic/milan-fpga/issues/665).
Each option is a preprocessor switch whose default value is 0.
With every option at 0, the library's objects are byte-identical to the previous revision's at -O0, -O2 and -Os without debug information.
Build every translation unit with the same values.
The [integrator guide](doc/integrator.md#port-platform-services) states each option's cost and contract.

| Option | How it is set | When set |
| --- | --- | --- |
| [LWSRP_TIMER_SLOTS](src/ports/timer.h) | [LWSRP_SCALE](CMakeLists.txt) sets 64. | A tick visits only its wheel slot's timers, in the list walk's order. |
| [LWSRP_ATTR_KEY](src/include/shish_lan/mrp.h) | Set by the lookup buckets, so by LWSRP_SCALE. | Each attribute keeps its attr_key octet, compared before attr_cmp and attr_replaces. |
| [LWSRP_ATTR_BUCKETS](src/core/mrp_mad.c) | LWSRP_SCALE sets 16. | A lookup scans one bucket by key, each bucket in the list's order. |
| [LWSRP_TX_MERGE](src/core/mrp_mad.c) | LWSRP_SCALE sets 1. | Runs of encoded vectors are merged; a strictly descending Message is reversed in place. |
| [LWSRP_ONE_PORT_MAP](src/core/mrp_mad.c) | Defined directly for every source. | A one-port participant reserves no propagation target and calls no map_join or map_leave. |
| [LWSRP_LEAN_VALIDATE](src/core/mrp_pdu.c) | Defined directly for every source. | The parser's validation pass leaves the decoded value unzeroed. |
| [LWSRP_RAPID_REPLACE](src/core/mrp_mad.c) | Defined directly for every source. | A replaced registration that rLv! left MT takes no leave timer event. |
| [LWSRP_LEAN_COPY](src/core/mrp_mad.c) | Defined directly for every source. | Copies stop at what is used: a rewritten Registrar row, a value's stored length, octet stores. |
| [LWSRP_LEAN_TX](src/core/mrp_mad.c) | Defined directly for every source. | An Applicant that tx! leaves unchanged takes none, and empty AttributeType words are passed over. |

LWSRP_SCALE selects only the first four options; it does not select the end-station options.
No option changes a transmitted octet, an indication, an observation, a receive-filter call, or their order.
One exception is allowed: [one-port propagation](doc/integrator.md#one-port-propagation).
With LWSRP_ONE_PORT_MAP, a one-port participant never calls its propagation policy.
A refused reservation then no longer refuses the receive; the event is applied instead.
Three options narrow the [application callback contract](doc/integrator.md#application-callback-contract).
Under LWSRP_LEAN_VALIDATE, decode_attr's result must not depend on its output buffer's prior content.
Under LWSRP_TX_MERGE, encode_attr may run again for a moved vector, so it must depend on its type and value only.
The key and the buckets call attr_cmp and attr_replaces less often.
The [tester guide](doc/tester.md#differential-traces) lists the checks for each option.
