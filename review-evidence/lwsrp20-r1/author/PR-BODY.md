Give each Applicant one event at its own LeaveAll, and send the LeaveAll's rLA! to Registrars only

Closes #20

Base: `main` at `08ee86e8`. Head: `20-own-leaveall-lv` at `c035764f`.

## Why

A Listener withdrawn just after the board's own LeaveAll was never sent as Lv. On a committed LeaveAll MRPDU,
`mrp_transmit` gave each attribute txLA! (QA stays QA, the Join is sent) or txLAF!, and then broadcast the local
rLA! to every Applicant and Registrar. That rLA! took QA to VP, so a later Lv! took VP to VO with no message.
The talker side then kept the registration that rode in the LeaveAll MRPDU until its own LeaveAll and LeaveTime.

The conformance ruling on #20 rules this a defect (IEEE 802.1Q-2018):
- Table 10-3: txLA! from QA sends sJ and keeps QA; txLAF! from QA goes to VP, as rLA! does. An rLA! after txLA!
  makes the two rows indistinguishable.
- 10.6: an Applicant minimizes state changes for attributes redeclared in the LeaveAll PDU.
- 10.8 NOTE 2 and 10.7.9: the LeaveAll precedes the messages it provokes.
- Table 10-3 note 9 does not apply, since a Join was sent after the LeaveAll.

Required: at an own-LeaveAll opportunity each Applicant takes exactly one of txLA! (its message fits) or txLAF!
(omitted), and no later rLA!. Registrars and the LeaveAll machine still take the LeaveAll (10.7.6.6; Table 10-4
"rLv! || rLA! || txLA!"; Table 10-5).

## What

`src/core/mrp_mad.c`:
- `sla_registrars` (new): a committed LeaveAll MRPDU's rLA! goes to every Registrar of the participant and to no
  Applicant. It is reported through the observer as rLA!, with the Applicant state unchanged.
- `mrp_transmit`: calls it in place of the Applicant and Registrar broadcast. The commit is otherwise unchanged:
  txLA! for each selected attribute, txLAF! for each omitted one, then the LeaveAll machine goes Passive.
- `la_event`: its `tx!` case, a second copy of the same broadcast, is removed. No caller passed tx!; Table 10-5's
  tx! cell is the commit above. Its two unused parameters go with it.

No public header changes. The received-LeaveAll path is unchanged: a peer's LeaveAll still gives rLA! to the
Applicants and Registrars of its type.

Every caller of the local rLA! broadcast, and the effect on each:

| Caller | Before | Now |
|---|---|---|
| `mrp_transmit`, a committed LeaveAll MRPDU (all three applications) | rLA! to every Applicant and Registrar after txLA! or txLAF! | rLA! to every Registrar; no Applicant |
| `la_event`, `tx!` case | Unreachable copy of the same broadcast | Removed |
| `rx_on_leaveall`, a received LeaveAll | rLA! to the type's Applicants and Registrars | Unchanged |
| `mrp_port_role_change` | Flush! or Re-declare!, and leavealltimer! on Flush! | Unchanged |

The three applications (VLAN, MAC, stream) share this one commit path, so each gets the change. On the wire:
- A value whose Join fitted the LeaveAll MRPDU stays QA, so the two Joins the local rLA! used to send after each
  LeaveAll (VP, then AA) are no longer sent.
- A withdrawal after the LeaveAll MRPDU now sends Lv at the next opportunity.
- A value left out of a full LeaveAll MRPDU, and a withdrawal before it, behave as before.

## Tests

The new [LeaveAll suite](tests/unit/own_leaveall_test.c) follows the ruling's rows, on a stream participant with a
peer's Talker Advertise and Domain:

| Ruling row | Test | At 08ee86e8 | At this head |
|---|---|---|---|
| Fitting attribute | `a_declaration_that_fits_the_leaveall_pdu_stays_quiet` | Fails: QA went to VP, both Joins resent | Passes |
| Withdrawal | `a_withdrawal_after_the_leaveall_pdu_sends_its_leave` | Fails: VP went to VO, no Lv | Passes |
| Omitted attribute | `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently` | Passes | Passes |
| Lv! before the LeaveAll | `a_withdrawal_before_the_leaveall_pdu_sends_no_join` | Passes | Passes |

Two more tests drive one VLAN into each of the twelve Applicant states on shared media. They grade every state's
txLA! cell with a fitting MRPDU and its txLAF! cell with a full one, including the message sent and the
Registrar's LV. The txLA! test fails at `08ee86e8` for VP, VN, AN, AA, QA, AP and QP.

In the [boundary suite](tests/unit/review_test.c), `committed_leaveall_gives_each_applicant_one_leaveall_event`
replaces the "QA -> QA -> VP" expectation, and `full_leaveall_reports_each_required_transition` now requires no
Applicant change on rLA!. Both fail at `08ee86e8`.

Reproduce the first column with this head's tests on the base sources: `git checkout 08ee86e8 -- src`, then build
and run the unit target. In both profiles exactly five tests fail (38 assertions).

## Checks

| Check | Result |
| --- | --- |
| Unit target, default and Milan builds | Exit 0; 108 tests, 27197 and 27185 assertions; 0 warnings |
| CTest; scenarios; scenario dry run | Exit 0; three scenarios and ten steps in both builds |
| Sanitizers (address and undefined behaviour), two compilers, both builds | Exit 0, no report; a planted heap overread is reported |
| Freestanding (both profiles), embedded source list, strict `-Werror` compiles | Exit 0 |
| Reversals, both profiles | 102 of 102 killed by their named tests |
| Equivalence against `9197193e`, both profiles | Exit 0; 148 opportunities, 0 decoded events differ; 1 revised base test |
| Documentation: sentences, references and self-test, links, graphs | Exit 0; 373 local links, 22 external, 0 failures; 29 graphs |

Four reversals cover this change: the Applicant rLA! restored, rLA! applied before txLA!, the Registrar rLA!
dropped, and txLA! given to omitted values. Each must fail its named LeaveAll tests.

`tests/check_equivalence.py` runs the base revision's own suite with this checkout's sources. That suite's
`full_leaveall_reports_each_required_transition` expected one local rLA! transition, the behaviour #20 removes.
The check now lists it as revised by #20 and may fail only that test; every opportunity is still compared.
With a planted defect that fails another base test, the check still exits 1.

Against `08ee86e8`'s own suite, 619 of 639 transmit opportunities decode identically. The 20 that differ are in the
two capacity sweeps that cross LeaveAll periods. Across them this head sends a sub-multiset of the base's events,
and every event it no longer sends is a JoinMt: 19 in the stream sweep, 22 in the VLAN and MAC sweep.

Line coverage of `src/core/mrp_mad.c` goes from 93.30 % to 95.54 %, and branch coverage from 85.32 % to 86.78 %.
No file's coverage falls. The new function is fully covered.

## Consumer

`kebag-logic/milan-fpga` at `dev-soft-core` `854bd723`, with this head as its lwSRP gitlink. The pin bump updates
`ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the boundary diagram and the prose pins. A host-level reproduction runs
the board's SRP adapter against an lwSRP talker-side peer:

| Point | Withdrawals 5 to 200 ms after the board's own LeaveAll | With `08ee86e8` | With this head |
|---|---|---|---|
| 8x8/1if, every input | 387 (9 inputs, 43 offsets) | 351 never sent as Lv (every offset under 190 ms) | Every Lv within 190 ms; the peer deregisters on it |
| 1x1/1if | 86 | 78 never sent as Lv | Every Lv within 190 ms |

With no withdrawal, over 90 s with five of the board's LeaveAlls and two of the peer's, every Listener stays
registered at the peer, with no Leave indication.

The consumer's own gates pass with this pin:
- its firmware gate (every suite, and every control, AECP and SRP planted defect caught) and its coverage ratchet;
- its CPU service budget at 1x1/1if and 8x8/1if: no pass over its 2 ms share; every timer-owed MRPDU, the own
  LeaveAll's included, within 2.5 ms of its opportunity (bound 49 ms); the last queued notice within 27 ms (bound
  130 ms);
- its load and flip checks, its image ledger, its two-placement comparison, and its documentation gates.

At `-Os` for RV32, `mrp_mad.c`'s object grows by 68 octets. The 8x8/1if platform image grows by 56 octets, to
139,264, which fills its two ROM banks exactly; its tiles stay at 58.0, its ledger.

## Review notes

- `sla_registrars` delivers rLA! to Registrars that txLA! already moved too. Table 10-4 gives both events one
  cell, and from LV it is "-x-", so the second changes nothing and restarts no leavetimer.
- The LeaveAll machine is unchanged: Passive at the commit, its leavealltimer still drawn at expiry.
- The observer contract adds one case: an accepted LeaveAll reports Registrar-only changes as rLA!
  ([integrator guide](doc/integrator.md)).
