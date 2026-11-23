# HANDOFF r1: [A832] lwSRP #20, the own-LeaveAll withdrawal race

Status: **REVIEW READY** (17:15 CET 2026-11-23). On #20: TAKEN (issuecomment-7097328174), REVIEW READY
(issuecomment-7106824505).
lwSRP head `c035764f`: the fix, tests and docs; every lwSRP gate rc 0.
Parent scratch, committed locally and never pushed: `58e20464` (pin bump), `edc9167f` (the host reproduction).
Every parent gate the brief names is done and holds at both points, including the harness through the board's own
LeaveAll. Nothing of this lane is running. Five open points below; none blocks this change.
ETA: none (done). The on-wire bench run is the manager's after merge.

Lane: `$LANES/lwsrp20`, branch `20-own-leaveall-lv` from `08ee86e8` (origin kebag-logic/lwSRP, checked
before the first commit). Scratch: `$VALIDATION_STORAGE/lwsrp20-a832`. Parent scratch:
`$VALIDATION_STORAGE/scratch/lwsrp20-parent`, branch `lwsrp20-consumer` from `854bd723`. Receipts: `receipts/INDEX.md`.

## lwSRP commits (one-line, no trailers)

- `7eed7e5` Give each Applicant one event at its own LeaveAll and send its rLA! to Registrars only
- `c035764` Document the own-LeaveAll events, the LeaveAll suite and the new counts

## The fix (`src/core/mrp_mad.c` at `c035764f`)

- `:774` `sla_registrars`: the committed sLA's rLA! to every Registrar and no Applicant (10.7.6.6, Table 10-4),
  reported through the observer as rLA! with the Applicant unchanged. Called at `:1533` in place of the Applicant and
  Registrar broadcast. Each Applicant keeps exactly one of txLA! or txLAF! (Table 10-3); the LeaveAll machine goes
  Passive as before (Table 10-5).
- `:795` `la_event`: the `tx!` case, an unreachable second copy of the broadcast, is removed with its two unused
  parameters (four call sites).
- Callers of the local rLA! broadcast, and the effect on each:

| Caller | Effect |
|---|---|
| `mrp_transmit`, committed LeaveAll MRPDU (MVRP, MMRP and MSRP share it) | Applicants no longer take rLA!; Registrars do. Fitted values stay quiet (the two Joins the rLA! caused are gone); a later withdrawal sends Lv |
| `la_event` `tx!` | Unreachable; removed |
| `rx_on_leaveall` (received LeaveAll), `mrp_port_role_change` | Unchanged |
| lwSRP's hosted Linux build (`libshlan.so`, unit target, scenarios) and its bare-metal side (freestanding, embedded source list) | Built and passing in both profiles |
| Parent bare-metal RV32 image (`srp_mbx.c`, its observer `moved()`) and its host builds (GoogleTest arms, the twin's split half, the budget harness's simulated CPU) | Same code; Registrar-only rLA! transitions owe no pass and free nothing; all gates below pass |

## Step (1): tests first

The head's tests on the `08ee86e8` sources (`receipts/lwsrp/tests-first/`): exactly five tests fail, 38 assertions,
both profiles.

| Ruling row | Test | At 08ee86e8 | At c035764f |
|---|---|---|---|
| Fitting attribute (replaces "QA -> QA -> VP") | `review_test.c` `committed_leaveall_gives_each_applicant_one_leaveall_event` | FAIL: VID 3 VP | PASS |
| Fitting attribute, the S1 board | `own_leaveall_test.c` `a_declaration_that_fits_the_leaveall_pdu_stays_quiet` | FAIL (9): VP; both Joins resent | PASS |
| Withdrawal | `a_withdrawal_after_the_leaveall_pdu_sends_its_leave` | FAIL (6): VO, no Lv | PASS |
| Omitted attribute | `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently` | PASS (today's behaviour is the ruling's) | PASS |
| Lv! before the LeaveAll | `a_withdrawal_before_the_leaveall_pdu_sends_no_join` | PASS (likewise) | PASS |
| Every state, txLA! row | `a_leaveall_pdu_that_fits_gives_each_applicant_its_txla_cell` | FAIL (20) | PASS |
| Every state, txLAF! row | `a_full_leaveall_pdu_gives_each_omitted_applicant_its_txlaf_cell` | PASS | PASS |
| Observer report | `review_test.c` `full_leaveall_reports_each_required_transition` | FAIL (2) | PASS |

## Step (3): lwSRP's gates at c035764f (all rc 0)

| Gate | Result | Receipt |
|---|---|---|
| Build, both profiles, Debug | 0 warnings | lwsrp/unit/build-*.log |
| Unit target | 108 tests; 27197 (default) and 27185 (Milan) assertions; 0 failures | lwsrp/unit/ |
| CTest | 1/1, both profiles | lwsrp/unit/ctest-*.log |
| Scenarios; dry run | 3 scenarios, 10 steps, both builds | lwsrp/gates/behave-*.log |
| Codec, isolated | 9 tests, 1690 assertions | lwsrp/gates/codec.log |
| Sanitizers: address and undefined behaviour, gcc 16.2.1 and clang 23.1.5, both profiles | 0 reports; planted heap overread reported (rc 1) | lwsrp/sanitizers/ |
| Freestanding (both profiles); embedded source list; strict `-Werror` gcc and clang | rc 0 each | lwsrp/gates/ |
| Reversals, both profiles | 102 of 102 killed by their named tests | lwsrp/reversals/ |
| Equivalence vs `9197193e`, both profiles | 148 opportunities, 0 decoded events differ; 1 REVISED base test (#20); negative control rc 1 | lwsrp/equivalence/ |
| Behaviour vs `08ee86e8`'s own suite | 619 of 639 opportunities identical; 20 differ, all in two sweeps; the head sends a sub-multiset, the surplus only JoinMt (19 + 22) | lwsrp/equivalence/against-08ee86e8-* |
| Coverage (gcov, both profiles merged) | `mrp_mad.c` lines 93.30 -> 95.54 %, branches 85.32 -> 86.78 %; no file falls; `sla_registrars` 100 % lines and branches | lwsrp/coverage/ |
| Docs: sentences, references (+ self-test), links (`--github-auth`), graphs | 1056 sentences; 0 unlinked; 373 local + 22 external links, 0 failures; 29 graphs, the new one reviewed as PNG | lwsrp/docs/ |
| RV32 `-Os` size and frames | `mrp_mad.o` text 13309 -> 13377 (+68); `mrp_transmit` frame 192, static, unchanged | lwsrp/size/ |

lwSRP has no coverage target of its own and is outside the parent's ratchet: the library was 82.85 % of branches at
the base and is 83.89 % at the head. The changed and added code is fully covered; the rest of the gap is pre-existing
(`switch.c`, `sim_adapter.c`, `alloc.c` are not run by the unit target).

## Step (4): the parent consumer gate (scratch `edc9167f`, lwSRP `c035764f`)

| Gate | Result | Receipt |
|---|---|---|
| Firmware gate `--require-rv32 --self-test --shard k/4` | shard 0: 90 arms, 0 failures (2236 cases; the two new arms among them); 1: 826 of 826 plants caught; 2: 385 caught; 3: 543 (SRP plants and pin controls) | parent/firmware/ |
| Firmware-unit job: tally and RV32 self-tests, saved-state store suites, coverage self-test, coverage ratchet `--check` | rc 0 each; ratchet held | parent/firmware-unit/ |
| Host reproduction, 8x8/1if every input (`srp_own_leaveall.cpp`) | 387 withdrawals (9 x 43 offsets, 5-200 ms): every Lv within 190 ms (bound 240 ms); the peer deregisters on it. At `08ee86e8`: 351 never sent (every offset under 190 ms), 39 of 44 tests fail | parent/own-leaveall/ |
| Host reproduction, 1x1/1if | 86 withdrawals, every Lv within 190 ms. At `08ee86e8`: 78 never sent | same |
| No withdrawal (same suite) | 90 s, 5 board and 2 peer LeaveAlls: every Listener registered at the peer, no Leave indication (both revisions) | same |
| CPU budget harness arm A, 1x1/1if | rc 0; 99 groups, 0 refusals; 0 of 162,007 passes over THE SHARE (longest 152,972 cycles); MRPDU rows worst 2.438 ms (49 ms); 7 misses, all `backlog-owed`'s egress-hold rows | parent/harness/ |
| CPU budget harness arm A, 8x8/1if | rc 0; 98 groups, 0 refusals; 0 of 285,420 over THE SHARE (longest 157,621); MRPDU rows worst 1.581 ms, own LeaveAll rows 0.541 and 0.570 ms (49 ms); egress ledger PASS (7 rows under their figures, no new miss); ledger self-test 15 of 15 | parent/harness/ |
| Harness `answering-every-port`, both points | rc 0; 16 groups each, 0 misses, 0 passes over THE SHARE (longest 153,966 and 164,702); last queued notice 20.5 and 26.4 ms (130 ms stated, 140 ms the owner's) | parent/harness/ |
| Harness `answering-later`, both points | rc 0; 8 groups each, 0 misses, 0 passes over THE SHARE (longest 156,306 and 158,116); `notice-retried` MRPDU rows worst 0.938 and 0.950 ms (49 ms) | parent/harness/ |
| The board's own LeaveAll under the harness: arm A's four 8x8/1if save groups, and the `srp` group extended past it at both points (no arm-A group reaches one at 1x1/1if) | Every pass within THE SHARE. In the second after each LeaveAll timer run-out the longest pass is 155,308 cycles (8x8/1if save groups); extended runs 40,043 (1x1/1if) and 31,349 (8x8/1if), whole runs 53,204 and 44,575. The MVRP LeaveAll MRPDU leaves 0.4 ms after its timer, the MSRP one at the end of the running join timer (160 ms; 10.7.4.1) | parent/harness/own-leaveall-window/ |
| Harness self-test | rc 0 | parent/harness/selftest.log |
| Load gate `load_grade.py --check` | 1x1/1if 0.511 at the pin, 0.508 with tsn-c-stack #32 (0.70) | parent/budget-model/ |
| Flip check, 1x1/1if | PASS; txL 47.88 ms (49), last 127.31 ms (130; 140 the owner's), R4 13.26 (20) | same |
| Flip check, 8x8/1if | PASS; load 0.744 (0.75); THE TRANSMIT's figure 77 ms against its row 76.81 ms | same |
| Images, `plat_ledger.py --self-test` | PASS, 9 of 9 controls. 8x8/1if ROM 139,208 -> 139,264 B (+56), 58 RAMB36 = its ledger 58.0; 1x1/1if 126,432 -> 126,496 B, 45; SRAM unchanged | parent/ledger/ |
| `test_ctrl_memory.py` | PASS, 0 failures | parent/ledger/ |
| Harness images | 1x1/1if 43.0 tiles, 8x8/1if 56.0 (budget 56) | parent/harness/ |
| Twin `make twin`, `make twin-plants` | 0 findings; 16 plants each refused twice | parent/twin/ |
| milan_dp `srptx`, `srptx-plants`, `srptx-mutants` | Red at the base too: open point 1 | parent/twin/, parent/twin-base/ |
| Docs workflow, its 46 gate steps | rc 0 each (em-dash and per-page contents with the pinned Markdown renderer); 4 hosted-runner steps not applicable | parent/docs-gates/ |

## Open points for the manager

1. **`srptx` is red at the base `854bd723`.** Licence 49, hold 59, wire 1108 findings, all `[TIME]` "a requested
   transmit opportunity ... after lwSRP last had nothing to send", plus one `[TX]` in hold. `srptx-mutants` fails its
   own control there for the same reason. At the head the finding kinds are identical; only that `[TIME]` count rises
   (MSRP 654 -> 692, MVRP 659 -> 702), because fitted values now stay quiet after a LeaveAll, leaving more
   periodic frames graded as "requested". The frames named leave on the periodic timer's own millisecond. The grade
   dates the request from lwSRP's last idle poll, and the adapter polls only when owed. Not in CI. Proposed: a parent
   issue for that grade.
2. **The twin's Applicant grade** (`twin_mrp.py`) still models an own LeaveAll as txLA! with rLA! before or after.
   It passes here only because no withdrawal falls within a JoinTime of the split's LeaveAll; it would grade a correct
   Lv there as illegal. The 56-line change for the pin bump (`receipts/parent/twin-grade-ruling/`) grades both
   halves' captures with 0 findings and refuses all 16 plants, once `leave-all-omission`'s words lose "or Mt".
3. **ROM margin**: the 8x8/1if platform image's ROM is now exactly its two banks (139,264 B). Tiles are unchanged
   at 58.0, its ledger; the next octet there costs a bank.
4. **LeaveAll timer** (unchanged): it restarts at expiry, not at the sent LeaveAll. 10.7.5.20 a) is ambiguous for the
   LeaveAll machine itself. Recorded in lwSRP's `doc/manager.md`; no change made.
5. The pin bump needs: `ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the regenerated boundary diagram and PNG manifest, the
   prose pins, `srp_own_leaveall.cpp` with its arms (`receipts/parent/patches/`), and item 2.

REVIEW READY c035764f2d6105fd9598b138112ba01eaa006958
