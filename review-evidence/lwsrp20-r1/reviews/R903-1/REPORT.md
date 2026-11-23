[R903] POSITIVE - exact head c035764f2d6105fd9598b138112ba01eaa006958

# R903-1: independent review of kebag-logic/lwSRP PR #21 (issue #20)

- Head `c035764f2d6105fd9598b138112ba01eaa006958`, tree `7f9bd6070b209cd246a9459104c1b1e531fa25da`; two commits on the parent's pin `08ee86e812a0eb5e1dc6cd61b494d8baf3491348`.
- Role: internal independent reviewer, cleared context, own clone. Round 1.
- Public review start: kebag-logic/lwSRP PR #21, issuecomment-7106925008.
- Verdict: **POSITIVE**. I found no BLOCKER, MAJOR or MINOR finding. All five lenses are CLEAN. I record five SUGGESTIONs (no verdict effect) and the merge-turn and pin-bump duties that remain open.

## 1. What I reconstructed, and in what order

1. `CONTRIBUTING.md` (there is no `AGENTS.md`), `README.md` and `doc/*.md`. Rules applied: braces on every body, tagged and prefixed enums, documentation sentences of 25 words or fewer, linked references, one-line commit subjects with no body or trailers.
2. Issue #20 body and its three comments: the conformance ruling (issuecomment-7097311763, DEFECT), TAKEN, and REVIEW READY. Frozen acceptance:
   - four unit rows;
   - on the wire at 8x8/1if, a withdrawal 5-200 ms after the board's LeaveAll, on every input, with the Lv out within 240 ms (Milan v1.2 Table 4.3) and the talker deregistering (4.2.7.2.2);
   - with no withdrawal, no deregistration across LeaveAlls.
3. Authorities: IEEE 802.1Q-2018 10.6, 10.7.6.6, 10.7.9, 10.8 NOTE 2, and Tables 10-3/10-4/10-5, as the ruling quotes them. Interfaces: `src/include/shish_lan/mrp.h`, and the observer contract in `doc/integrator.md`.
4. The diff `08ee86e8..c035764f` (13 files, +812/-74) and its history. Both commits are one-line subjects with no body or trailer (`receipts/comment-rule-scan.txt`).
5. Public evidence: kebag-logic/lwSRP `1d2c1ef6…/review-evidence/lwsrp20-r1` (251 files), the PR body, and the issue's REVIEW READY comment.
6. Prior public review findings on PR #21: **none exist at this head**. The PR's only comments are two "independent review started" notices (this review and one other). I have nothing to resolve or retain. I read no other reviewer's report.

## 2. Findings

No open MINOR, MAJOR or BLOCKER. No RESIDUE. The comment-rule scan of every added source, test and documentation line found no lane label, lane name, review round, reviewer ID or issue-comment ID (`receipts/comment-rule-scan.txt`).

| ID | Severity | Lenses | Where | Authority / evidence | Impact | Required outcome | Verification |
|---|---|---|---|---|---|---|---|
| R903-1-S1 | SUGGESTION | Docs | `doc/integrator.md:150-151` | Observer behaviour at the head: a fitted value's Registrar goes IN->LV under txLA! (`src/core/mrp_mad.c:1512`, Table 10-4 txLA! cell). Only omitted values' Registrars move under the local rLA! (`sla_registrars`, `:774-782`). | The text is true, but "Its local rLA! then reports Registrar changes only" can be read as "every LeaveAll Registrar change arrives as rLA!". | Optional wording: "An accepted LeaveAll reports each Applicant change as txLA! or txLAF!, and a fitted value's Registrar change as txLA!. Its local rLA! then reports the remaining Registrar changes, with the Applicant state unchanged." | Reading; the sentence checker stays at 0 findings. |
| R903-1-S2 | SUGGESTION | Conformance, Docs | PR #21 body, "Closes #20" | Issue #20 acceptance says "reproduced in a unit test and on the board". The evidence is unit tests plus a host-level two-station run of the board's SRP adapter (`srp_own_leaveall.cpp`). The author's handoff states the on-wire bench run is the manager's, after merge. | Merging auto-closes #20 before its on-board criterion has a receipt. | Manager's choice: write "Refs #20", or keep #20 open until the bench receipt, or record that the host-level reproduction meets "on the board". | Issue state after merge; bench receipt linked on #20. |
| R903-1-S3 | SUGGESTION | Tests | `tests/check_equivalence.py:27-31,154-162` | The REVISED exemption matches by test name. The expected failure is that test's `local_rla == 1` assertion (`receipts/equiv-OFF.log`, base `review_test.c:347`). A later failure of the same test's `omitted_txlaf == 1` assertion would be exempt too. My negative control (a wire-neutral plant that fails other base tests) still exits 1 (`receipts/equiv-negative.log`). | The check is narrower for that one base test only. The head's own suite still runs its replacement. | Optional: require the exempt failure to be the `local_rla` assertion (file:line or message). | Plant a defect that breaks only `omitted_txlaf`; the check must exit 1. |
| R903-1-S4 | SUGGESTION | Robustness | `src/core/mrp_mad.c:778-779` | `sla_registrars` discards `reg_event`'s result, relying on "No rLA! cell indicates". That holds for the Table 10-4 rLA! row (`:375-380`) and for Milan's swap, which is limited to rLv! (`:626-629`). | If a later profile gave rLA! an indication, a reservation failure would be silently dropped. | Optional: a reversal that gives the rLA! row an indication and must fail a named test, or a compile-time check on that row. | Reversal runner. |
| R903-1-S5 | SUGGESTION | Conformance, RTL (consumer twin) | Proposed pin-bump patch, `author/receipts/parent/twin-grade-ruling/twin-grade-ruling.diff` (milan-fpga `tb/verilator/milan_dp/twin_mrp.py`) | The proposal grades every attribute of a LeaveAll frame as txLA!, and treats an absent attribute as "sent nothing". The ruling gives an omitted (full-PDU) value txLAF!. | This is correct while the twin never fills an MRPDU, but it would misgrade a txLAF! omission. | At the pin bump: model txLAF! for omitted values, or state and check the no-full-MRPDU assumption. | The twin's 16 plants and both halves' captures, as in the author's run. |

## 3. Judgement of the open points

- **The `srptx` leg is red at `854bd723`: pre-existing, not caused by this change.**
  - The published base and head logs carry the same finding kinds: [TIME] "requested transmit opportunity … after lwSRP last had nothing to send", plus one [TX].
  - The head has 1394 [TIME] findings against 1313 at the base. Wire MRPDUs fall from 1459 to 1303 because the extra Joins after each LeaveAll are gone.
  - That shift fits a grade that dates each request from lwSRP's last idle poll.
  - The leg is not in CI. A parent issue is owed (manager).
- **The twin's Applicant grade patch is needed at the pin bump.** The current grade models txLA! with an rLA! before or after it. It would reject a correct Lv sent within a JoinTime of the split's LeaveAll. The published proposal grades both halves with 0 findings and refuses all 16 plants. See S5 for its txLAF! gap.
- **The LeaveAll timer restart (expiry vs send) is not a defect.**
  - `la_event` restarts the leavealltimer at leavealltimer! and at rLA! (`:795-818`), which is the Table 10-5 behaviour the ruling cites. This change does not alter it.
  - The removed `tx!` case, which restarted at send, was unreachable at the base: `git grep` at `08ee86e8` finds no `la_event(…, MRP_EVENT_TX, …)` call.
  - `doc/manager.md` records the reading as a limit. I treat it as a correctly recorded ambiguity.
- **The 8x8/1if ROM now fills exactly two banks.** It grows from 139,208 to 139,264 B (+56) and stays at 58 RAMB36, equal to its 58.0 ledger (`ledger/head.log:34`, `base.log:24`). It holds at `854bd723` with zero margin. The merge candidate on live dev `e275d795` must be measured again (manager).
- **Recorded budget misses: not a finding.** Arm A at both points has 7 MISS rows. All are `backlog-owed` ACMP/AECP egress-hold rows, the misses recorded by milan-fpga #894's ruling. At 8x8/1if they are under their ledger figures (`egress-ledger-8x8-1if.log`). At 1x1/1if they are lower (61.8-63.5 ms) but have no ledger receipt. None of them involves MRP output.

## 4. Lens evidence

### 4.1 Conformance: CLEAN

- **Fitting attribute: QA -txLA!/sJ-> QA, no Applicant rLA!, Registrar IN->LV.**
  - At commit, `mrp_transmit` gives each selected value txLA! and each omitted value txLAF! (`:1509-1515`). It then calls `sla_registrars` (`:1533`), which changes Registrars only and reports them as rLA! with the Applicant unchanged.
  - Pinned by `a_declaration_that_fits_the_leaveall_pdu_stays_quiet`.
  - Also pinned by `review_test.c` `committed_leaveall_gives_each_applicant_one_leaveall_event`. It replaces "QA -> QA -> VP" and checks exact bytes.
- **Withdrawal: Lv! -> LA, the next PDU carries Lv, then VO.** `a_withdrawal_after_the_leaveall_pdu_sends_its_leave` checks the Lv and its Ready subtype, then VO, then reclamation.
- **Omitted attribute: txLAF! -> VP, then Lv! -> VO with no Lv and no later Join.** Pinned by `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently`. The omitted Domain's Registrar takes rLA! from IN to LV.
- **Lv! before the LeaveAll: LA -txLA!-> LO, no Join.** Pinned by `a_withdrawal_before_the_leaveall_pdu_sends_no_join`. LO -tx!-> then sends Mt and goes to VO.
- **Every Applicant state.**
  - Two tests grade the txLA! and txLAF! cells of all 12 Applicant states.
  - The txLA! test fails at the base for VP, VN, AN, AA, QA, AP and QP.
  - Those are exactly the states whose txLA! successor (AA, AN or QA) has a moving rLA! cell.
- **Every caller of the old local rLA! broadcast.**
  - At `08ee86e8` there are two: `mrp_transmit:1528`, now Registrar-only, and the unreachable `la_event` `tx!` case, now removed.
  - `rx_on_leaveall` (received LeaveAll, type-scoped) and `mrp_port_role_change` are unchanged.
  - `src/modules/{mmrp,msrp,mvrp}.c`, `switch*.c` and `sim_adapter.c` have no LeaveAll or rLA! path. All three applications share the one commit.
  - Targets: hosted Linux (`libshlan.so`, unit, scenarios), freestanding and embedded, an RV32 strict compile (mine), and the consumer's RV32 image (the author's gate).
  - The consumer's observer now sees Registrar-only rLA! transitions, and its gates pass (author receipts).
- **Milan profile.** The rapid-leave swap is limited to rLv! (`:626`), so the own LeaveAll keeps a timed LV in both profiles. My probe that delivers rLv! in place of rLA! in the Milan build is killed (`receipts/mutant-rlv-ON.log`).
- **Wire behaviour on the consumer.** I re-ran it myself; see §4.2.

### 4.2 RTL (consumer image, simulated CPU, twin): CLEAN

**My re-run of the consumer's race reproduction.**
- Tree: a scratch milan-fpga at `854bd7236792ce1adbd10c43b13a6a5002ad3bb6`, with the published patch 0001 (without its regenerated PNG) and patch 0002 applied.
- Submodules at their gitlinks: tsn-c-stack `715589c1`, protocol-processor `801ef228`, gptp-processor `1616fc8f`.
- lwSRP at the head, or at the base with the pin moved back, as the published base arm did.
- Only `own_leaveall_arms` was run. No bank was run.

| Arm | lwSRP | Withdrawals | Unsent | Worst withdrawal-to-Lv | Over 240 ms | Peer deregisters at the Lv | "held" test | rc |
|---|---|---:|---:|---:|---:|---|---|---:|
| 8x8/1if, 9 inputs x 43 offsets 5-200 ms | `c035764f` | 387 | 0 | 190 ms | 0 | all | PASS | 0 |
| 8x8/1if | `08ee86e8` | 387 | 351 | - | - | - | PASS | 1 (39 of 44 fail) |
| 1x1/1if, 2 inputs x 43 | `c035764f` | 86 | 0 | 190 ms | 0 | all | PASS | 0 |
| 1x1/1if | `08ee86e8` | 86 | 78 | - | - | - | PASS | 1 |

- These match the author's receipts number for number. `receipts/own-la-grade.txt` grades the published logs; `receipts/own-la-grade-rerun.txt` grades mine.
- The reproduction's peer is a real lwSRP MSRP participant with its own pool and Milan rapid leave. Deregistration is taken from the peer's `leave_ind`.

**RV32 object size (mine).**
- Build: RV32I `-Os` with the parent's `RV32_FLAGS`, `-DLWSRP_MILAN=1` and `-Werror -pedantic`, using a host RV32 GCC 14.3.0.
- `mrp_mad.o` text grows from 13,309 to 13,377 B (+68). The `mrp_transmit` frame is 192 B, static, in both.
- This matches the author's `size/sizes.txt` (`receipts/rv32-size.log`).

**Published evidence I examined but did not re-run.**
- Firmware gate shards 0-3: each reports `test_ctrl_firmware: PASS`, rc 0.
- SRP mailbox, receive-recovery and composition suites: 0 failures. Firmware-unit: rc 0 in all five.
- Budget harness arm A, 1x1/1if and 8x8/1if: 0 of 162,007 and 0 of 285,420 passes over THE SHARE (2.000 ms). The own-LeaveAll MRPDU rows are 0.541 and 0.570 ms, against 49 ms.
- Answering-every-port and answering-later arms: 0 misses.
- Loads: 0.511 (ceiling 0.70) and 0.744 (ceiling 0.75).
- Flip check, 1x1/1if: txL 47.88 ms (bound 49), last notice 127.31 ms (bound 130).
- Image ledger: PASS. Twin: 0 findings, all 16 plants refused.

### 4.3 Robustness: CLEAN

- `sla_registrars` walks `ps->attrs` with no indication, map work or allocation. Its observer call follows the existing no-re-entry contract.
- A refused send keeps `prepared_la`. The Registrar rLA! runs only after acceptance (`:1503-1533`).
- **Sanitizers.** Address and undefined-behaviour builds ran with `-fno-sanitize-recover=all`, for gcc and clang in both profiles, and I confirmed the `__asan`/`__ubsan` symbols are present. All pass (27197 and 27185 assertions, rc 0) with no report.
- Freestanding (both profiles) and the embedded source list: rc 0.
- Only S4 remains, as a suggestion.

### 4.4 Tests: CLEAN

| Check (mine) | Result |
|---|---|
| Unit, default and Milan, Debug, 0 warnings | 108 tests; 27197 and 27185 assertions; rc 0. CTest rc 0. Scenarios 3/10 pass. Dry run validates 3 scenarios and 10 steps without executing them. |
| Base suite at `08ee86e8` | 102 tests; 26658 and 26646 assertions; rc 0 |
| Head tests on base sources, both profiles | Exactly 5 tests and 38 assertions fail: fitting (9), withdrawal (6), txLA! cells (20), boundary replacement (1), observer report (2). The omitted and Lv-before rows pass at the base, as the ruling expects. |
| Reversals, both profiles | **102 of 102 killed in each profile (204/204).** Each label is killed exactly once, and the restored builds and checks return rc 0. This includes the four LeaveAll reversals and the edited `committed-local-leaveall` and `received-leaveall-restart`. |
| My extra mutants | rLv! in place of rLA! (Milan): killed by the omitted-attribute test. No observer report from `sla_registrars`: killed by two tests. |
| Equivalence vs `9197193e`, both profiles | rc 0; 22 scenarios, 148 opportunities, 138 PDUs; 125 identical, 13 layout-only, 0 different; one REVISED test. My negative control returns rc 1. |
| Coverage, gcov, OFF+ON merged | `mrp_mad.c` lines 93.30 -> 95.54 %, branches 85.32 -> 86.78 %, identical to the author's figures. `sla_registrars`: 6/6 lines, 2/2 branches. |
| Trace diff vs `08ee86e8`'s own suite (published JSON) | 619 of 639 opportunities identical. In the 20 that differ, the head sends nothing the base did not. It only drops JoinMt: 19 in the stream sweep, 22 in the VLAN and MAC sweep. |

**How the reversals were run.**
- The unmodified runner failed its baseline on this host (`receipts/reversals-*.log`). Its fixed 10 s CTest timeout tripped.
- The cause is scheduler latency: the shared host runs at a load near 150 on 32 cores, so one suite run takes about 140 s wall for 0.45 s of CPU.
- My scratch copies raise only that timeout and the per-command limit, and shard the cases (`scripts/reversal_shards.sh`, `scripts/reversal_labels.sh`).
- Mutations, required failures and the kill rule are unchanged. Each log carries the diff against the head's runner.

### 4.5 Docs: CLEAN

- Doc checks: sentences, references and the reference self-test (79 cases), and links (373 local, 22 external). All have 0 failures and rc 0.
- All 30 distinct `mrp_mad.c#L…` anchors land on the named code (`receipts/doc-anchors.txt`).
- Counts agree across README, `manager.md` and `tester.md`: 108/27197/27185, ten suites, 102 reversals, and the equivalence figures as measured.
- The new graph has 9 nodes.
- The comment-rule scan of added lines finds no lane label, lane name, round, reviewer ID or issue-comment ID.
- I did not render the graphs: the mermaid renderer is not installed here (a limit).
- The `doc/tester.md` conflict with main is a merge-turn duty (§7).

## 5. Reviewer-owned ledger

| Lens | Status | Examined artifacts | Covering round | Exact head |
|---|---|---|---|---|
| Conformance | CLEAN | `src/core/mrp_mad.c` 149-405, 618-818, 1074-1146, 1415-1547; base call sites; ruling rows; 12-state cell tests; Milan swap probe; consumer race re-run | R903-1 | c035764f2d6105fd9598b138112ba01eaa006958 |
| RTL | CLEAN | My re-run of the `srp_own_leaveall.cpp` arms (head and base, 8x8/1if and 1x1/1if); RV32 `-Os` sizes and frames; published firmware gate, harness, load, flip, ledger, twin and srptx receipts | R903-1 | c035764f2d6105fd9598b138112ba01eaa006958 |
| Robustness | CLEAN | Address and undefined-behaviour sanitizers, gcc and clang, both profiles; freestanding (both profiles); embedded; retry and commit ordering; `sla_registrars` invariants | R903-1 | c035764f2d6105fd9598b138112ba01eaa006958 |
| Tests | CLEAN | Unit, CTest and behave (both profiles); base suite (both); tests-first (both); 204/204 reversals; 2 extra mutants; equivalence (both) plus a negative control; merged gcov at base and head; trace-diff JSON | R903-1 | c035764f2d6105fd9598b138112ba01eaa006958 |
| Docs | CLEAN | README, architecture, developer, integrator, manager and tester guides; doc checks; 30 anchors; comment-rule scan; commit shape; merge-tree against main | R903-1 | c035764f2d6105fd9598b138112ba01eaa006958 |

## 6. Real limits

- **No hardware, no physical calibration (NOT RUN).** Host-level and simulated results are not hardware proof. The on-wire bench run at 8x8/1if has no receipt.
- **Parent gates not re-run.** The firmware gate shards, CPU budget harness, load and flip models, ledger, twin and srptx rest on the author's published receipts. I re-ran only the own-LeaveAll arms.
- **Budget comparisons.** The 1x1/1if `backlog-owed` misses have no ledger receipt. No harness run at the base pin exists to compare against.
- **Standard text.** No IEEE 802.1Q-2018 text was available locally. Clause and table content comes from the ruling and from the code's tables. The pre-existing txLA!/txLAF! cells (for example, VP's txLA! sending In or Mt) were not re-derived from the standard.
- **Not run.** The Zephyr module build (no SDK here) and the mermaid graph rendering.
- **Local framework.** I built the unit framework myself (cgreen 1.6.5, `4fd4b933`), in scratch.
- **Manager scope.** No manager source bank exists at this head, and I claim none. Hosted and act acceptance belong to the manager.

## 7. Pending manager duties

1. **Merge turn: resolve the `doc/tester.md` conflict with main `97677fcb`.** It is the only conflict (`receipts/merge-with-main.txt`).
   - Keep main's Scenario row ending "and reads the simulated port flags".
   - Keep this PR's unit row: 108 tests, 27197 assertions, ten suites.
   - Keep both reversal paragraphs and set the total to **109**. The auto-merged `tests/check_reversals.py` has 109 cases: main's 106 plus this PR's 3.
   - Then re-check the `doc/manager.md` and README counts, and run the reversals (109) and doc checks on the merge candidate.
2. **Merge turn: build the current-dev candidate banks** (source base `08ee86e8`, live dev `e275d795`). Re-measure the 8x8/1if ROM, which has zero margin at `854bd723`.
3. **Pin bump in milan-fpga.** Update `ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the regenerated boundary diagram and PNG manifest, and the prose pins. Add `srp_own_leaveall.cpp` and its arms, and the twin grade change (S5).
4. **Parent issue** for the srptx `[TIME]` grade, which is already red at `854bd723`.
5. **Issue #20 closure** against its "on the board" criterion, and the on-wire bench run (S2).

## 8. Receipts

Everything below is under `receipts/` and `scripts/` and listed in `MANIFEST.sha256`. Host paths are redacted to `<packet>`, `<clone>` and `<tools>`.

- **Unit and scenarios:** `unit-*`, `base-*`, `first-*`.
- **Sanitizers and freestanding:** `asan-*`, `free-embedded`.
- **Equivalence:** `equiv-*`, `equiv-negative`.
- **Reversals:** `reversals-*` (the unmodified run, stopped by the baseline timeout), `revs-*`, `revl-*`, `revs-shard0-NOTE.txt`, `reversal-tally.txt`.
- **Mutants and coverage:** `mutant-*`, `coverage-*`, `coverage-merged.txt`.
- **Docs:** `docs`, `doc-anchors.txt`, `comment-rule-scan.txt`.
- **RV32 size:** `rv32-size`.
- **Consumer:** `parent-setup`, `parent-own-la-*`, `own-la-grade*.txt`.
- **Merge and clone state:** `merge-with-main.txt`, `clone-integrity.txt`.

**Clone state after the probes.** The clone is at the exact head:
- all 66 blobs re-hashed, with 0 byte or mode mismatches;
- the index equals the HEAD tree, and the status is clean;
- there are no gitlinks (lwSRP has none).

In the parent scratch tree, lwSRP's gitlink is `c035764f`.

R903-1 FINISHED
