[R903] POSITIVE - exact head 25b5a7400ff618fa1404e452668ed6902daa5f74

# R903-2: delta re-review of PR #21 (issue #20), round 2

Exact head `25b5a7400ff618fa1404e452668ed6902daa5f74`, tree `ba42b8379d4a066580a8a5047083c355d102ae41`.
Delta from the round-1 head `c035764f2d6105fd9598b138112ba01eaa006958`. It has three fix commits, the merge `f7111b27` of `main` `97677fcb`, and one documentation link commit.

**Verdict: POSITIVE.** No BLOCKER, MAJOR or MINOR finding is open. All five lenses are CLEAN.
R904-1-F1 is resolved at this head, and I reproduced it at the round-1 gate.
There are two RESIDUE items, both wording only, and four SUGGESTIONs. None affects the verdict.

## 1. Scope and reconstruction

Order followed:
1. `CONTRIBUTING.md` and `README.md` (the repository has no `AGENTS.md`), then `doc/`.
2. Issue #20: its body, the conformance ruling (issuecomment-7097311763) and the author's two REVIEW READY comments.
3. The PR #21 body and the R903-2 start comment.
4. `git diff c035764f..25b5a740` and the history.
5. The public packet `review-evidence/lwsrp20-r1/author-r2` at `bd72ffb4`.
6. The prior public findings (R904-1 issuecomment-7107320194, R903-1 issuecomment-7108550518). I read these only after my verdict and ledger were written (`receipts/verdict-before-prior-findings.md`).

I read no private author material, lane scratch or other checkout. One unit-framework install exists under an author lane's tmp area, and I did not use it. I built the public framework release 1.6.3 in my own scratch instead (`receipts/environment.txt`).

Authorities:
- IEEE 802.1Q-2018 10.6, 10.7.6.6, 10.7.9, 10.8 NOTE 2, and Tables 10-3, 10-4 and 10-5, as applied by the published ruling.
- Milan v1.2 4.2.7.2.2 and Table 4.3.
- The check's own contract in `tests/check_equivalence.py:1-14`, and `doc/tester.md`.

The brief names 802.1Q-2022 10.7.5 for the Registrar table. The repository and the ruling cite the 2018 edition's Table 10-4, and so do I. The rLA!/txLA! cells used here (IN: start leavetimer, go to LV, no indication; LV and MT: -x-) are the same in both readings.

## 2. Delta checks (brief items 1-6)

### (1) R904-1-F1: the gate's suite-ending judgement

The fix is in `tests/check_equivalence.py:38-92` (`run`, `judge_suite`) and `:206-215`.
- A time limit (`--suite-timeout`) gives `TIMEOUT`. A negative rc names the signal. Any rc other than 0 or 1 fails.
- Exit 0 or 1 needs exactly one `Completed "main":` line. Its failure and exception counts must equal the listed reports, and the rc must agree.
- The candidate may fail only the REVISED assertion, matched by test and message. The base suite may fail nothing.
- A build or setup step that times out returns the truthy `TIMEOUT`, so `main` returns 1. The gate fails closed.

Independent evidence:

| Probe | Result | Receipt |
|---|---|---|
| `judge_suite` on 21 synthetic endings: signals 15 and 9, timeout, rc 2 and 3, no completion line, two completion lines, count mismatches both ways, same test with another message, Exception in the revised test, another test, base failure, nested suite path | 21 of 21 judged correctly | `receipts/probe-judge-suite.txt`, `scripts/probe_judge_suite.py` |
| `tests/check_equivalence_controls.py` at the head, OFF and ON (`--timeout 120`) | 5 of 5 each; the revised control passes with the revised assertion listed | `receipts/controls/head-*.log`, `controls-head-*.json` |
| The same controls with `c035764f`'s `tests/check_equivalence.py` (blob `9d47480c`) | 3 of 5 fail in each profile. signal: gate rc 0, problems []. other-assertion: gate rc 0. timeout: gate rc 2 (no such option). revised and other-test pass | `receipts/controls/oldgate-c035764f-*.log`, `controls-old-*.json` |
| Hang inside a forked test child, gate `--suite-timeout 30` | Gate rc 1, "candidate unit suite: timed out after 30 s"; one test child is left orphaned (see S2) | `receipts/probe-child-hang/` |

So the planted positive control (`revised`) passes at both gates. The SIGTERM control, which is R904-1's probe, is accepted by the old gate (rc 0) and rejected at the fix.
Only the revised assertion is exempt. The `other-assertion` control (the observer drops txLAF!) fails the revised test's second assertion, and the head rejects it with "not revised".
The author's receipts agree: `author-r2/receipts/lwsrp/controls/{fix,head,c035764f}-{OFF,ON}/controls.json`.

At the old gate, the timeout control fails only because the option does not exist. On a real hang, that gate's `subprocess.run(..., timeout=600)` raised an uncaught `TimeoutExpired`, giving a nonzero exit. It never accepted a hang (see RESIDUE R1).

### (2) The merge turn `f7111b27`

| Check | Result | Receipt |
|---|---|---|
| Recomputed `git merge-tree 7b2f0b6 97677fc` | Only `doc/tester.md` conflicts; `doc/manager.md` and `tests/check_reversals.py` auto-merge | `receipts/merge/merge-tree.txt` |
| The automatic merge tree compared with `f7111b27` | Every file identical except `doc/tester.md`. There the only differences are the two conflict hunks | `receipts/merge/automerge-vs-merge.txt`, `conflict-resolution.diff` |
| Main's side: normalized per-file diff `08ee86e..97677fc` against `7b2f0b6..f7111b2` | Identical for `tests/check_reversals.py`, `tests/features/environment.py` and `tests/features/steps/switch_steps.py`. The two docs differ only through the other side's lines | `receipts/merge/main-side.txt` |
| Branch side: `08ee86e..7b2f0b6` against `97677fc..f7111b2` | Identical for every file except the two docs; `src/core/mrp_mad.c` is identical | `receipts/merge/branch-side.txt` |
| Conflict resolution | It keeps the branch's unit row (108 tests, 27199 assertions, ten suites) and main's scenario row ("... and reads the simulated port flags"). It keeps both reversal paragraphs, with the total at 110 | `conflict-resolution.diff` |
| `doc/manager.md` | Main's text replaces the stale "Neither independently reads port state" lines; the branch's counts are kept | `git show --cc f7111b2` |
| `tests/check_reversals.py` | 110 cases, 110 unique labels (main 99+7, branch +4) | parsed at the head |

Nothing of `main` is lost or reverted. `25b5a740` changes only `doc/tester.md:96`, where it adds a link. The PR is reported MERGEABLE and CLEAN.

### (3) The new checks

The new no-Leave-indication checks are `tests/unit/own_leaveall_test.c:269-275,287,315,359-360,413-414`. The new reversal is `own-leaveall-registrar-indication` (`tests/check_reversals.py:142-144,314`).
- I ran the reversal myself in both profiles, and it was killed. It fails the required `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently` plus 13 other received-LeaveAll, Flush and allocation tests, because it plants the shared rLA! row. This matches the author's `registrar-indication-probe/`.
- Extra probe: I planted an Lv indication in the Registrar's txLA! IN cell instead. It fails both new `leaves == 0` assertions, in the fitting test and the omitted test. So each new assertion is load-bearing. The fitting test's assertion is pinned through the txLA! cell, not the rLA! cell (see R2 and S4). Receipt: `receipts/reversals/probe-txla-indication-*.log`.
- Main's seven scenario reversals: all were killed in both profiles. Each failed exactly its named scenarios and showed its expected assertion words. Receipt: `receipts/reversals/subset-*.log` (11 delta cases, plus a restored build, unit and scenario run with rc 0).
- The author's full run gives 110 of 110 killed per profile, with baseline and restored scenarios at rc 0 (`author-r2/receipts/lwsrp/reversals/rev-*.log`).

### (4) Compiled sources unchanged

`git diff c035764f..25b5a740 -- src CMakeLists.txt zephyr Kconfig.zephyr build.sh` is empty. The author's `lane/identity.txt` agrees.
The round-1 conformance, RTL and runtime-robustness verdicts on `src/core/mrp_mad.c` therefore stand. They covered `sla_registrars:774-782`, the `mrp_transmit` commit, the removed `la_event` tx! case and the unchanged `rx_on_leaveall`.
Nothing they depend on is in this delta. The delta touches only `tests/`, `doc/` and `README.md`.

### (5) Parent consumer gate (from published receipts; no parent access)

Source: `author-r2/receipts/parent/`. The consumer is milan-fpga `dev-soft-core` `854bd723`, plus round 1's two commits, plus `a9fff7ba` pinning `25b5a740`.

| Gate | Receipt | Result |
|---|---|---|
| Firmware gate shards 0-3 | `firmware/summary.txt`, `rc-*` | rc 0 each. 90, 826, 385 and 543 ok lines, 0 not ok. The pin controls name `25b5a740` |
| SRP host tests / own-LeaveAll race | `own-leaveall/grade.txt`, `rc` | 8x8/1if: 387 of 387 withdrawals sent, worst 190 ms, 0 over 240 ms, 0 peers not at the Lv, 43 per input on all 9 inputs. 1x1/1if: 86 of 86 |
| CPU service budget, arm A | `harness/grade-1x1.txt`, `grade-8x8-1if.txt`, `rc-*` | 0 of 162,007 and 0 of 285,420 passes over the 2 ms share (longest 152,972 and 157,621 cycles). MRPDU worst 2.438 and 1.581 ms against 49 ms. Own-LeaveAll MRPDUs at 8x8/1if: 0.541, 0.570 and 0.595 ms |
| Answering-every-port, answering-later | `harness/grade-*-every.txt`, `grade-*-later.txt` | 0 misses. Last notice 20.47 and 26.35 ms against 130 ms |
| Known backlog rows | `harness/egress-ledger-8x8-1if.log` | 8x8/1if: 7 rows, each under its ledger figure, "no new budget miss". 1x1/1if lists the same 7 backlog rows (see Limits) |
| Load, flip | `budget-model/load_check.log` | PASS: 0.511 against 0.70, 0.744 against 0.75 |
| Images | `ledger/images-vs-round1.txt`, `rc-head` | 20 of 20 ELF and NVM images SAME as those built with `c035764f`; ledger self-test rc 0 |

### (6) The R903-1 suggestions and the PR body

- S1: applied with the suggested wording (`doc/integrator.md:150-151`).
- S2: applied as "Refs #20" with its reason in the body. That is right while the on-board criterion has no receipt.
- S3: applied. `REVISED` now holds the message, and the `other-assertion` control pins it.
- S4: applied as a reversal, and I re-ran it (killed).
- S5: left to the pin bump, with a reason. The twin grade is in the consumer, not lwSRP, so I accept that.

The published PR body is byte-identical (after trailing whitespace) to `author-r2/PR-BODY.md`. Its figures match the receipts and my runs:
- unit target: 108 tests; 27199 and 27187 assertions; 0 warnings;
- scenarios: 3 and 10;
- reversals: 110 of 110;
- equivalence: 22 scenarios, 148 opportunities, 138 PDUs, 125 identical, 13 layout-only, 0 different;
- controls: 5 of 5;
- docs: 382 local and 22 external links, 29 graphs;
- coverage: `mrp_mad.c` 95.54 % lines and 86.78 % branches;
- images: byte-identical.

The body's one wrong claim is R1. No check is loosened:
- the gate now has strictly more failure conditions;
- REVISED is narrowed from a test to one assertion;
- no reversal or required failure was removed;
- the scenario steps went from return-code proxies to flag reads.

The privacy and comment-rule scan of all added lines and the PR body found no lane label, review round, reviewer ID, issue-comment ID, host path, or tool or model name. It found no new instance in source or test comments.

## 3. Findings

### Prior public findings

| ID | Severity | State at this head | Evidence |
|---|---|---|---|
| R904-1-F1 | MINOR (Tests, Robustness) | **RESOLVED** | Section 2 (1). The SIGTERM control is accepted by `c035764f`'s gate (rc 0) and rejected at the head (rc 1, "ended by signal 15 (SIGTERM)"), in both profiles. Unknown rc and inconsistent completion are also rejected (21 of 21 synthetic). The genuine revised failure still passes |
| R903-1-S1 | SUGGESTION | Applied | `doc/integrator.md:150-151` |
| R903-1-S2 | SUGGESTION | Applied (manager's choice) | PR body line 3: "Refs #20" |
| R903-1-S3 | SUGGESTION | Applied | `tests/check_equivalence.py:31-35,86-88`; the `other-assertion` control |
| R903-1-S4 | SUGGESTION | Applied | `tests/check_reversals.py:142-144,314`, killed in both profiles |
| R903-1-S5 | SUGGESTION | Retained for the pin bump (consumer twin grade) | Outside lwSRP; carried to manager duties |

R904-1's merge-turn note (resolve the `doc/tester.md` conflict and keep both sets of checks) is done (section 2 (2)). R903-1's predicted total of 109 became 110 because this round adds one reversal.

### New findings

**R903-2-R1. RESIDUE.**
- Lenses: Docs.
- Where: PR #21 body, "Tests" section, the sentence after the controls table (body lines 116-117, also `author-r2/PR-BODY.md`).
- Evidence: "Against the gate at `c035764f`, the signal, timeout and other-assertion controls fail in both profiles: that gate accepted them."
  - The old gate did not accept the timeout control. It refused `--suite-timeout` with rc 2 (`receipts/controls/oldgate-c035764f-*.log`).
  - On a real hang, `c035764f`'s `run()` raised an uncaught `TimeoutExpired`, which is a nonzero exit (`git show c035764f:tests/check_equivalence.py`, line 35).
  - The author's handoff and issue comment state this correctly.
- Impact: wording only. Every receipt and figure is right.
- Exact fix: "Against the gate at `c035764f`, the signal and other-assertion controls fail in both profiles, because that gate accepted them. The timeout control fails there because that gate has no `--suite-timeout` option."
- Verification: reading.

**R903-2-R2. RESIDUE.**
- Lenses: Docs.
- Where: `doc/tester.md:96`, and the PR body "Tests" paragraph (body line 66).
- Evidence: "There, rLA! only starts each Registrar's leavetimer (Table 10-4)."
  - In the fitting test, every Registrar is moved by txLA! (IN to LV). The local rLA! then meets LV, which is -x-.
  - Only an omitted value's Registrar is moved by rLA!.
  - My txLA!-row probe fails the fitting test's `leaves == 0`, which confirms which cell that assertion pins (`receipts/reversals/probe-txla-indication-*.log`).
- Impact: wording only. The assertions and the cited table are correct.
- Exact fix: "There, the LeaveAll only starts a Registrar's leavetimer: txLA! for a fitted value, rLA! for an omitted one ([IEEE 802.1Q-2018, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/))." Use the same wording in the PR body.
- Verification: the sentence and reference checkers stay at 0.

**R903-2-S1. SUGGESTION.**
- Lenses: Tests, Robustness.
- Where: `tests/check_equivalence.py:31-35,86-88`.
- Evidence: the exemption matches the test name and the first message line. A second assertion in the same base test with the identical text `Expected [local_rla] to [equal] [1]` would also be exempt. The base `9197193e` is fixed, so the exempt failure's place (`tests/unit/review_test.c:347`) is stable.
- Impact: a very narrow theoretical widening. No such assertion exists today.
- Optional outcome: also match the reported file name and line, or pin the count of exempt reports to one.
- Verification: a synthetic log with the same message at another line must fail.

**R903-2-S2. SUGGESTION.**
- Lenses: Robustness.
- Where: `tests/check_equivalence.py:44-55`.
- Evidence: on a time limit, `subprocess.run` kills only the suite process. With a planted hang in a forked test child, the gate correctly failed (rc 1, "timed out after 30 s"). But the hung child stayed alive, reparented, until I killed it (`receipts/probe-child-hang/`).
- Impact: a stray process on a host after a hung suite. The verdict is unaffected.
- Optional outcome: start the suite with `start_new_session=True` and kill its process group at the limit.
- Verification: repeat the child-hang probe. No `unit_tests` process should remain.

**R903-2-S3. SUGGESTION.**
- Lenses: Robustness.
- Where: `tests/check_equivalence.py:73-75`.
- Evidence: a log with two completion lines is reported as "without the runner's completion line" (`receipts/probe-judge-suite.txt`).
- Impact: a misleading diagnostic only. The outcome is a correct failure.
- Optional outcome: report "with N completion lines, not one".
- Verification: the same synthetic case.

**R903-2-S4. SUGGESTION.**
- Lenses: Tests.
- Where: `tests/check_reversals.py:142-144,314`.
- Evidence: the new reversal pins the rLA! row, which among the own-LeaveAll tests only the omitted test reaches. The fitting test's new `leaves == 0` is pinned only by an Lv on the txLA! row. My probe shows that plant is already killed by both new assertions and by three existing tests (21 failures).
- Impact: none today.
- Optional outcome: add an `own-leaveall-txla-indication` reversal that names `a_declaration_that_fits_the_leaveall_pdu_stays_quiet`. Each new assertion then has a named plant.
- Verification: the reversal runner.

Observation (manager-owned evidence packet, not a PR defect):
- `author-r2/receipts/INDEX.md` lists `parent/firmware/gate-2.log.gz` and `parent/harness/selftest.log.gz`. Commit `bd72ffb4` publishes them as `.log`.
- `tools/penv.sh`'s published bytes are path-redacted, so its index size and hash prefix differ.
- `MANIFEST.json` lists all 247 published files with 0 hash mismatches (`receipts/packet-verify.txt`).
- The packet commits are not signature-verified. GitHub reports them "unsigned", so integrity rests on the manifest hashes.

## 4. Lenses

- **Conformance: CLEAN.** The compiled sources are unchanged, so the round-1 rulings stand (section 2 (4)). The new assertions follow Table 10-4: rLA! or txLA! from IN starts the leavetimer and gives LV with no indication. The other cells are -x-. The S2 closure wording matches issue #20's open on-board criterion.
- **RTL: CLEAN (no HDL in scope).** lwSRP has no RTL. The consumer's 20 images are byte-identical to round 1's. ROM (8x8/1if 139,264 B, exactly two banks), tiles (58) and the CPU-budget receipts are unchanged (section 2 (5)).
- **Robustness: CLEAN.** The gate fails closed on every abnormal ending I tried: 21 synthetic endings, 5 controls times 2 profiles, and a real child hang. R904-1-F1 is resolved. S1 to S3 are optional hardening.
- **Tests: CLEAN.**
  - Head unit target: 108 tests; 27199 (OFF) and 27187 (ON) assertions; rc 0; 0 warnings. CTest rc 0. Scenarios: 3 and 10 in both profiles (`receipts/unit/`).
  - 11 delta reversals were killed in both profiles. Both new assertions are load-bearing.
  - The tests-first, sanitizer and coverage receipts match their claims (`author-r2/receipts/lwsrp/{tests-first,sanitizers,coverage}`).
- **Docs: CLEAN.**
  - Head checks: sentences 1074 with 0 over the limit; 0 unlinked references; reference self-test 79 of 79; local links 382 with 0 failures (external links per the author's `docs/links.log`, 22 with 0 failures); 29 graphs rendered with 0 failures (`receipts/docs/`).
  - The README, manager and tester counts agree with the runs.
  - R1 and R2 are wording RESIDUE.

## 5. Reviewer-owned ledger

| Lens | State | Examined artifacts | Covering round | Exact head |
|---|---|---|---|---|
| Conformance | CLEAN | `git diff c035764f..25b5a740` (no compiled source); `tests/unit/own_leaveall_test.c:269-414`; `src/core/mrp_mad.c:340-380` (Registrar rows, read-only); issue #20 ruling; PR body closure wording | R903-2 (delta); round-1 source verdict carried | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| RTL | CLEAN | No HDL in lwSRP or the delta; `author-r2/receipts/parent/ledger/images-vs-round1.txt`, `firmware/`, `harness/`, `budget-model/` | R903-2 (receipts) | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Robustness | CLEAN | `tests/check_equivalence.py`, `tests/check_equivalence_controls.py`; `receipts/probe-judge-suite.txt`, `receipts/controls/`, `receipts/probe-child-hang/` | R903-2 | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Tests | CLEAN | Unit, CTest and scenarios in both profiles (`receipts/unit/`); `receipts/reversals/`; author reversal, tests-first, sanitizer and coverage receipts; `tests/check_reversals.py` (110 unique) | R903-2 | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Docs | CLEAN (RESIDUE R1, R2) | `doc/tester.md`, `doc/manager.md`, `doc/integrator.md`, `README.md`; merge resolution (`receipts/merge/`); PR body against packet; `receipts/docs/` | R903-2 | 25b5a7400ff618fa1404e452668ed6902daa5f74 |

## 6. Real limits

- **No source bank.** No manager source bank runs at this head, and I do not claim or infer one. The source-head execution evidence is the author's published receipts plus my focused runs above.
- **Consumer gates not re-run.** I did not re-run the parent consumer gates (no parent access). Section 2 (5) is from the published receipts, checked against the manifest.
- **Full reversal campaign not re-run.** I ran 11 delta cases per profile. The 110-case figure is the author's receipt.
- **External links not re-requested.** My link check was local-only.
- **No hosted evidence.** The repository has no hosted workflows, so there are no check runs at this head: the combined status has no contexts. Hosted and act acceptance belong to the manager.
- **Unit-framework version.** My unit-framework build is the public 1.6.3. The author's version is not stated. The runner's output format matched the author's logs.
- **1x1/1if egress ledger not re-run.** At 1x1/1if, the 7 backlog rows were not re-graded by an egress ledger this round (only 8x8/1if was). Because the images are byte-identical, round 1's status for them carries over.
- **Physical calibration not run.** The on-wire acceptance of issue #20 (20 of 20 at 8x8/1if on the board) has no receipt. The host-level reproduction is not hardware proof.
- **Unit test, not the board.** The equivalence controls and reversals prove the gate and the tests, not the board.

## 7. Pending manager duties

1. **Merge turn.** Build the current-dev merge candidate (source base `c035764f`, live dev `e275d795`) with the builder and native banks, and link the receipts on the PR. Re-measure the 8x8/1if ROM, which has zero margin.
2. **Carry RESIDUE R1 and R2** to the residue checklist (PR body and `doc/tester.md:96`).
3. **Pin bump in milan-fpga.** Update `ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the boundary diagram and PNG manifest, and the prose pins. Add the own-LeaveAll reproduction and its arms, and the twin Applicant grade change, including R903-1-S5 (txLAF! for omitted values, or a checked no-full-MRPDU assumption).
4. **Parent issue** for the `srptx` `[TIME]` grade, which is red before this change.
5. **Issue #20.** Keep it open ("Refs #20") until the on-wire bench receipt.
6. **LeaveAll timer restart** at expiry: documented and unchanged; separate adjudication.

## 8. Receipts

Everything is under `receipts/` and `scripts/`, and listed in `MANIFEST.sha256`. Host paths are redacted to `<packet>`, `<clone>` and `$HOME`.
- `scripts/verify_packet.py`, `scripts/probe_judge_suite.py`, `scripts/probe_reversals_subset.py` (portable; run with explicit path arguments).
- `receipts/packet-verify.txt`, `probe-judge-suite.txt`, `controls/`, `unit/`, `reversals/`, `probe-child-hang/`, `docs/`, `merge/`, `clone-integrity.txt`, `environment.txt`, `verdict-before-prior-findings.md`.

**Review clone state after the probes.** All probes ran on scratch copies. The review clone is at the exact head:
- 67 tracked entries re-hashed, with 0 byte or mode mismatches;
- the index equals HEAD;
- the worktree is clean, with no untracked files;
- there are no gitlinks (lwSRP has none, so none are required) (`receipts/clone-integrity.txt`).

R903-2 FINISHED
