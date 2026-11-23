# REVIEW READY: [A832] lwSRP #20, the own-LeaveAll withdrawal race

**lwSRP head `c035764f2d6105fd9598b138112ba01eaa006958`** on `20-own-leaveall-lv`, from `08ee86e8` (origin kebag-logic/lwSRP;
local, not pushed). PR body: `PR-BODY.md` (to `main`, "Closes #20"). Parent scratch (never pushed):
`$VALIDATION_STORAGE/scratch/lwsrp20-parent`, branch `lwsrp20-consumer` = `854bd723` + `58e20464` (pin bump) + `edc9167f` (the
host reproduction). Receipts: `receipts/INDEX.md`.

## The fix (`src/core/mrp_mad.c`, at the cause)

- At a committed LeaveAll MRPDU each Applicant takes exactly one of txLA! (fits) or txLAF! (omitted), as before, and no
  later rLA!. The sLA's rLA! now goes to every Registrar and no Applicant (`sla_registrars`, `:774`, called at
  `:1533`). Registrars that txLA! already moved stay LV ("-x-", no leavetimer restart). The LeaveAll machine is
  unchanged (Passive at the commit). IEEE 802.1Q-2018 10.7.6.6, Tables 10-3, 10-4, 10-5.
- `la_event`'s `tx!` case, an unreachable second copy of the same broadcast, is removed with its two unused parameters.
- Every caller of the local rLA! broadcast and its effect:
  - `mrp_transmit` (the three applications share it): Applicants no longer take rLA!; Registrars do.
  - `la_event` `tx!`: unreachable; removed.
  - `rx_on_leaveall` (a received LeaveAll), `mrp_port_role_change`: unchanged.
- Targets:
  - lwSRP's hosted Linux build (`libshlan.so`, the unit target, the scenarios) and its bare-metal side (freestanding
    sources, the embedded source list) build and pass in both profiles.
  - In the parent, the bare-metal RV32 split image's SRP adapter (`srp_mbx.c`) calls `mrp_transmit` once per
    participant. Its observer now also sees Registrar-only rLA! transitions (Applicant unchanged). That owes no pass
    and frees nothing (`moved()`). Its host builds (GoogleTest arms, the twin's split half, the budget harness's
    simulated CPU) are the same code.
- On the wire: after each own LeaveAll, a value that fitted no longer sends the two Joins the local rLA! caused (VP,
  then AA). A withdrawal after it sends Lv. Omitted values and a withdrawal before it behave as before.

## Acceptance rows (the ruling)

| Row | Unit test | At 08ee86e8 | Head |
|---|---|---|---|
| Fitting attribute (replaces "QA -> QA -> VP") | `committed_leaveall_gives_each_applicant_one_leaveall_event`, `a_declaration_that_fits_the_leaveall_pdu_stays_quiet` | FAIL | PASS |
| Withdrawal | `a_withdrawal_after_the_leaveall_pdu_sends_its_leave` | FAIL | PASS |
| Omitted attribute | `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently` | PASS (the ruling's row is today's) | PASS |
| Lv! before the LeaveAll | `a_withdrawal_before_the_leaveall_pdu_sends_no_join` | PASS (likewise) | PASS |
| On the wire, 8x8/1if (host-level) | parent `srp_own_leaveall.cpp`: 9 inputs x 43 offsets, 5-200 ms | 351 of 387 never sent as Lv | 387 of 387 Lv within 190 ms; peer deregisters on it |
| On the wire, no withdrawal (host-level) | same suite, 90 s, 5 board and 2 peer LeaveAlls | registered throughout | registered throughout |

Also: every state's txLA! and txLAF! cells (12 states each); the observer's report. The on-wire bench run is the
manager's after merge.

## Gates

HANDOFF-r1.md has the full table with receipts. Summary:
- **lwSRP:** every gate rc 0. Unit target 108 tests in both profiles; sanitizers clean, with their planted control
  reported; 102 of 102 reversals killed; equivalence 0 decoded differences; coverage of the changed code 100 %, no
  file falls; docs.
- **Parent, functional:** the firmware gate's four shards PASS (0 failures; 826, 385 and 543 plant and pin checks);
  the firmware-unit job PASS (coverage ratchet held); twin and twin-plants PASS; the docs workflow's 46 gate steps
  rc 0.
- **Parent, CPU service budget** at 1x1/1if and 8x8/1if (arms A, answering-every-port, answering-later): rc 0 in all
  six legs, and no pass over THE SHARE's 2 ms anywhere (the longest is 164,702 cycles). The board's own LeaveAll is
  included: 8x8/1if's save groups and an `srp` group extended past it at both points.
  - Every timer-owed MRPDU within 2.5 ms of its opportunity (49 ms); the last queued notice within 26.4 ms (130 ms
    stated, 140 ms the owner's).
  - The only misses are `backlog-owed`'s 7 egress-hold rows, within the 8x8/1if ledger, with no new miss.
- **Parent, model checks and images:** load 0.511 at 1x1/1if (0.70) and 0.744 at 8x8/1if (0.75); flip check txL
  47.88 ms (49) and last 127.31 ms; `plat_ledger --self-test` PASS (8x8/1if 58 RAMB36, its ledger 58.0);
  `test_ctrl_memory` PASS.

## Open points for the manager

1. **`srptx` (milan_dp) is red at the base `854bd723`**, before this change: licence 49, hold 59, wire 1108 findings,
   all `[TIME]` "requested transmit opportunity ... after lwSRP last had nothing to send", plus one `[TX]` in hold.
   `srptx-mutants` fails its own control for the same reason. At the head the finding kinds are identical; only that
   one `[TIME]` count rises (MSRP 654 -> 692, MVRP 659 -> 702), because fitted values now stay quiet after a LeaveAll.
   The frames it names leave on the periodic timer's own millisecond; the grade dates the request from lwSRP's last
   idle poll, and the adapter polls only when owed. Not in CI. Proposed: a parent issue for the grade.
2. **The twin's Applicant grade** (`tb/verilator/milan_dp/twin_mrp.py`) models an own LeaveAll as txLA! with rLA!
   before or after, which the ruling rules out. It still passes at this head, since its stimulus has no withdrawal
   within a JoinTime of the split's LeaveAll, but it would grade a correct Lv there as illegal. A 56-line change for
   the pin bump (`receipts/parent/twin-grade-ruling/`) grades both halves' captures with 0 findings and refuses all
   16 plants, once `leave-all-omission`'s expected words lose "or Mt".
3. **ROM margin**: the 8x8/1if platform image's ROM grows 56 octets to 139,264, exactly its two banks; tiles stay
   58.0 (its ledger). The next octet of growth there costs a bank.
4. **LeaveAll timer** (unchanged): it restarts at expiry, not at the sent LeaveAll (10.7.5.20 a) is ambiguous for the
   LeaveAll machine itself). Recorded in lwSRP's `doc/manager.md`; no change made.
5. The pin bump (`receipts/parent/patches/`): `ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the regenerated boundary
   diagram (+PNG manifest), the prose pins, the new `srp_own_leaveall.cpp` and its arms, and item 2.
