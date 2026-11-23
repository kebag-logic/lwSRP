# HANDOFF r2: [A832] lwSRP #20 / PR #21, round 2

Status: **REVIEW READY** (23:05 CET 2026-11-23). lwSRP head `25b5a7400ff618fa1404e452668ed6902daa5f74` on
`20-own-leaveall-lv`, **local, not pushed** (the manager pushes; the PR still shows `c035764f` until then).
Every lwSRP gate and every parent gate the brief names passes at the merged head. Nothing of this lane is running.
On #20: one `[A832] REVIEW READY` comment (link in the last section).
Outputs: `REVIEW-READY.md` (the delta from `c035764f`), `PR-BODY.md` (the full proposed body), `receipts/INDEX.md`.
Parent scratch `$VALIDATION_STORAGE/scratch/lwsrp20-parent`, branch `lwsrp20-consumer`: `a9fff7ba` (pin `25b5a740`),
committed locally, never pushed.

## Brief items

| # | Item | Outcome |
|---|---|---|
| 1 | R904-1-F1 MINOR: the gate accepted a candidate suite ended by SIGTERM | Fixed in `8caa6aba`. A signal, a time limit or an unknown exit status fails; exit 0 or 1 needs one consistent completion line. The reviewer's probe is now `tests/check_equivalence_controls.py`, which fails at `c035764f`'s gate and passes at the fix, with a planted control (`revised`) |
| 2 | Merge turn | `f7111b27`: one merge of `main` `97677fcb`. The only conflict, `doc/tester.md`, keeps both texts' facts; 110 reversals. All lwSRP gates re-run (below) |
| 3 | Parent consumer gate at the merged head | All pass; images byte-identical to `c035764f`'s (below) |
| 4 | R903-1 suggestions | S1, S3, S4 applied; S2 applied in the proposed body (reversible); S5 left for the pin bump (reason below) |

## lwSRP commits since c035764f (one-line, no trailers)

- `8caa6aba` Fail the equivalence check on a suite ended by a signal or a time limit, and exempt only the revised assertion
- `8ca2c3a8` Require no Leave indication at the own LeaveAll and plant one in the Registrar's rLA! row
- `7b2f0b6e` Document the suite-ending rule, its controls, the Leave indication checks and the new counts
- `f7111b27` Merge main into the own-LeaveAll branch
- `25b5a740` Link the Registrar table that the Leave indication sentence cites (the reference checker found it unlinked after the merge)

`git diff c035764f 25b5a740 -- src CMakeLists.txt zephyr Kconfig.zephyr build.sh` is empty.

## (1) The fix and its regression

`tests/check_equivalence.py`, `judge_suite`, at the head:
- `--suite-timeout` (default 600 s): a suite killed at the limit gives "timed out after N s". Any command's
  `TimeoutExpired` is now caught and reported, not raised.
- A negative status gives "ended by signal N (NAME)". Any status other than 0 or 1 fails as `rc=N`.
- Exit 0 or 1 needs exactly one `Completed "main":` line. Its failure and exception counts must equal the listed
  reports, and the status must agree with them.
- The candidate may fail only REVISED assertions, matched by test name and message
  (`Expected [local_rla] to [equal] [1]`). The base must not fail at all.

| Control | OFF fix | ON fix | OFF head | ON head | OFF at c035764f | ON at c035764f |
|---|---|---|---|---|---|---|
| revised (planted control: must pass) | PASS | PASS | PASS | PASS | PASS | PASS |
| signal (the reviewer's probe, output flushed first) | PASS | PASS | PASS | PASS | FAIL, gate rc 0 | FAIL, gate rc 0 |
| timeout (`--suite-timeout 480`) | PASS | PASS | PASS | PASS | FAIL, gate rc 2 | FAIL, gate rc 2 |
| other-assertion (S3) | PASS | PASS | PASS | PASS | FAIL, gate rc 0 | FAIL, gate rc 0 |
| other-test (R903's wire-neutral plant) | PASS | PASS | PASS | PASS | PASS | PASS |

At `c035764f` the timeout control fails because that gate has no time-limit option. Its fixed 600 s limit would
have raised an uncaught `TimeoutExpired`, a traceback with rc 1 and no `equivalence.json`. Each planted control
also requires 0 decoded differences. The signal and timeout controls also require the fault to follow the revised
failure and the completion line, so the exit status alone decides.

## (2) The merge

`main` `97677fcb` adds issue #4's work: scenario steps read the simulated port flags, and seven scenario reversals
(99 -> 106). The resolution of the `doc/tester.md` conflict:
- the check table: this branch's unit row (108 tests, 27199 assertions, ten suites) and main's scenario row;
- the reversal text: this branch's five LeaveAll reversals and main's seven scenario reversals; the total is 110,
  equal to the 110 unique cases in the auto-merged `tests/check_reversals.py`.

`doc/manager.md` auto-merged: main's scenario lines with this branch's counts. README shows this branch's count.

## lwSRP gates (receipts `lwsrp/`)

| Gate | Result |
|---|---|
| Build, Debug, both profiles | 0 warnings |
| Unit target | 108 tests; 27199 and 27187 assertions; rc 0 (round 1: 27197 and 27185; +2, the S4 assertions) |
| CTest; scenarios; dry run | 1/1 both; 3 scenarios, 10 steps both builds; dry run validates 3 and 10 |
| Codec, isolated | 9 tests, 1690 assertions |
| Tests first (head tests, `08ee86e8` sources) | Five tests, 38 assertions fail, both profiles: unchanged; the new assertions hold at the base |
| Sanitizers, address and undefined behaviour, gcc 16.2.1 and clang, both profiles | rc 0, 0 reports, runtime symbols present; planted heap overread rc 1, 15 reports |
| Freestanding (both), embedded source list, strict `-Werror` gcc and clang at profile 0 and 1 | rc 0 each |
| Reversals, both profiles | 110 of 110 killed, each once; baseline and restored build, check and scenarios rc 0 |
| Equivalence vs `9197193e`, both profiles | rc 0; 148 opportunities, 138 PDUs, 125 identical, 13 layout-only, 0 different; one REVISED |
| Equivalence controls | 5 of 5, both profiles (table above) |
| Coverage, gcov, both profiles merged | File for file identical to round 1: `mrp_mad.c` 95.54 % lines, 86.78 % branches; `sla_registrars` 6/6, 2/2; library 83.89 % branches |
| Docs | 1074 sentences, 0 over; 0 unlinked; reference self-test 79; 382 local + 22 external links, 0 failures; 29 graphs |
| S4 probe | The rLA! Lv-indication plant fails `a_declaration_omitted_from_a_full_leaveall_pdu_leaves_silently` in both profiles, plus received-LeaveAll and Flush tests; the head passes |

## (3) Parent consumer gate (scratch `a9fff7ba`, lwSRP `25b5a740`; receipts `parent/`)

What `main`'s later commits change for the parent: nothing it compiles. They touch only lwSRP's `tests/`
(`features/`, `check_reversals.py`) and documents. The parent uses no lwSRP test or document path. The pin bump
moves only the gitlink and the pin text. All 20 firmware images (ELF and NVM) that `plat_ledger` builds are
byte-identical to round 1's, built with `c035764f`. So are arm A's tables at both points and the 8x8/1if save-group
logs.

| Gate | Result |
|---|---|
| Firmware gate `--require-rv32 --self-test`, shard 0/4 | rc 0; 90 arms, 2236 cases, 0 failures; 43 SRP host arms, the two own-LeaveAll arms among them |
| Shards 1/4, 2/4, 3/4 | rc 0; 826, 385 and 543 caught, 0 not; the pin controls name `25b5a740` |
| Own-LeaveAll race reproduction, 8x8/1if every input | 44 tests, 0 failures; 387 withdrawals, all sent, worst 190 ms, 0 over 240 ms, the peer deregisters at each Lv; no-withdrawal held: 9 inputs, 90 s, 5 board and 2 peer LeaveAlls |
| Same, 1x1/1if | 44 tests, 0 failures; 86 withdrawals, all within 190 ms |
| CPU budget arm A, 1x1/1if | rc 0; 99 groups, 0 refusals; 0 of 162,007 passes over THE SHARE (longest 152,972); MRPDU worst 2.438 ms (49); 7 misses, all `backlog-owed` egress-hold rows, as before |
| CPU budget arm A, 8x8/1if | rc 0; 98 groups; 0 of 285,420 over THE SHARE (longest 157,621); MRPDU worst 1.581 ms; own LeaveAll 0.541, 0.570, 0.595 ms (49); egress ledger PASS (7 rows under their figures, no new miss); ledger self-test 15 of 15 |
| Own-LeaveAll window, 8x8/1if save groups (`la_window.py`) | Identical to round 1: every pass within THE SHARE; MSRP LeaveAll MRPDU 160.3-160.6 ms after its timer (the running join timer), MVRP 0.42 ms |
| Answering-every-port, both points | rc 0; 16 groups, 0 misses, 0 over THE SHARE (longest 153,966 and 164,702); last notice 20.47 and 26.35 ms (130 stated, 140 the owner's) |
| Answering-later, both points | rc 0; 8 groups, 0 misses, 0 over (longest 156,306 and 158,116); MRPDU 0.938 and 0.950 ms (49); notices within 8.32 ms (20) |
| Harness self-test | rc 0 |
| Load `load_grade.py --check` | PASS: 1x1/1if 0.511 (0.70), 0.508 with tsn-c-stack #32; 8x8/1if 0.744 (0.75) |
| Flip, 1x1/1if | PASS: txL 47.88 ms (49), last 127.31 (130), R4 13.26 (20), R4L 203.48 (238) |
| Flip, 8x8/1if | PASS: THE TRANSMIT's 77 ms against its row 76.81 ms |
| Image ledger `plat_ledger.py --self-test` | PASS, 9 of 9 controls; 8x8/1if ROM 139,264 B at 58 RAMB36 (its ledger); 1x1/1if 126,496 B at 45 |
| `test_ctrl_memory.py` | 0 failures |
| Pin docs: `submodule_boundaries.gen.py --check`, `check_diagram_pngs.py`, `check_submodule_docs.py` | rc 0 each |

Not re-run this round, with reasons: the twin, `srptx` and the docs workflow are outside the brief's list. The
extended `srp` runs past the own LeaveAll are skipped because the images are byte-identical. The 8x8/1if save
groups re-grade the window.

## (4) R903-1 suggestions

- **S1 taken**: `doc/integrator.md`, the reviewer's wording.
- **S2 taken in `PR-BODY.md`**: `Refs #20` with a one-line reason, so merging does not close #20 before its
  on-board receipt. It is the manager's choice; restoring `Closes #20` is a one-word edit.
- **S3 taken**: REVISED matches the assertion's message; the `other-assertion` control fails at `c035764f`'s gate.
- **S4 taken**: two assertions (no Leave indication at the own LeaveAll) and reversal
  `own-leaveall-registrar-indication`. A compile-time check is not possible: C cannot assert on a table's contents.
- **S5 not taken**: it concerns the parent's proposed twin grade (`tb/verilator/milan_dp/twin_mrp.py`), not
  lwSRP or this PR. It belongs to the pin bump's twin-grade change (open point 2 below): model txLAF! for omitted
  values, or check the no-full-MRPDU assumption.

## Open points for the manager (carried from round 1 unless marked)

1. **Push** (new): the five commits are local. After the push, PR #21's mergeability and hosted checks need a look.
   The PR body is `PR-BODY.md`.
2. **Twin Applicant grade** for the pin bump (round 1's 56-line proposal), now with S5: txLAF! for omitted values,
   or an explicit no-full-MRPDU check.
3. **`srptx` red at `854bd723`** before this change: a parent issue for its `[TIME]` grade.
4. **ROM margin**: 8x8/1if is exactly its two banks (139,264 B), unchanged by the merge.
5. **LeaveAll timer** restarts at expiry (recorded in `doc/manager.md`); no change.
6. **Pin bump**: `ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, the diagram and manifest, the prose pins, the reproduction
   test with its arms; `receipts/parent/patches/` holds this round's patch for `25b5a740`. The merge candidate on
   live dev `e275d795` still needs its own banks and ROM re-measure.
7. Cosmetic (new): run from a detached checkout, the controls' `git clone` prints git's detached-HEAD advice. It
   does not affect results; it is left so the head is not moved under the finished gates.
8. Housekeeping (new): the lane repository still lists one scratch worktree, `<scratch>/r2/old-gate` at `c035764f`,
   used to run the regression against the old gate. `git worktree remove` clears it once nobody needs to re-run that.

## Issue comment

[A832] REVIEW READY on #20: issuecomment-7115185098
(https://github.com/kebag-logic/lwSRP/issues/20#issuecomment-7115185098); its text is
`receipts/review-ready-comment.md`.

REVIEW READY 25b5a7400ff618fa1404e452668ed6902daa5f74
