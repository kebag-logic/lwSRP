# [A832] REVIEW READY: lwSRP PR #21 (issue #20), round 2

Head `25b5a7400ff618fa1404e452668ed6902daa5f74` on `20-own-leaveall-lv` (local; not pushed by this lane).
Delta from the reviewed head `c035764f`, which R903-1 and R904-1 reviewed: five commits, one of them the merge with `main` `97677fcb`.

## Commits since c035764f

| Commit | Subject |
|---|---|
| `8caa6aba` | Fail the equivalence check on a suite ended by a signal or a time limit, and exempt only the revised assertion |
| `8ca2c3a8` | Require no Leave indication at the own LeaveAll and plant one in the Registrar's rLA! row |
| `7b2f0b6e` | Document the suite-ending rule, its controls, the Leave indication checks and the new counts |
| `f7111b27` | Merge main into the own-LeaveAll branch (parents `7b2f0b6e`, `97677fcb`) |
| `25b5a740` | Link the Registrar table that the Leave indication sentence cites |

No compiled source changes: `git diff c035764f 25b5a740 -- src CMakeLists.txt zephyr Kconfig.zephyr build.sh` is
empty. The consumer's firmware images are byte-identical to those built with `c035764f`.

## R904-1-F1 (MINOR): fixed

`tests/check_equivalence.py` now judges each unit suite by how it ended, before reading its log (`judge_suite`):

- a time limit (`--suite-timeout`, default 600 s) or a signal fails, whatever the log reports;
- any exit other than 0 or the runner's 1 fails;
- exit 0 or 1 needs exactly one `Completed "main":` line whose failure and exception counts equal the listed reports;
- the candidate may then fail only the listed REVISED assertions. Each entry is now the test and the assertion's
  message, `Expected [local_rla] to [equal] [1]` (R903-1-S3 folded in), not the test name alone.

A command that reaches its time limit is reported instead of raising `TimeoutExpired`.

Regression: `tests/check_equivalence_controls.py`, the reviewer's probe as a check. Each control clones the
checkout, overlays its working tree, plants one change, runs the clone's check, and grades its exit and problem.

| Control | Plant | Required | At the fix (OFF, ON) | At c035764f's gate (OFF, ON) |
|---|---|---|---|---|
| revised | none (the planted control) | rc 0, the revised assertion listed | PASS, PASS | PASS, PASS |
| signal | `timer.c` destructor: flush, then SIGTERM, suite process only | rc 1, "ended by signal 15 (SIGTERM)" | PASS, PASS | **FAIL** (gate rc 0) both |
| timeout | the same, then wait forever; `--suite-timeout 480` | rc 1, "timed out after 480 s" | PASS, PASS | **FAIL** (gate rc 2: no such option) both |
| other-assertion | observer drops txLAF! (S3) | rc 1, "not revised: ... omitted_txlaf" | PASS, PASS | **FAIL** (gate rc 0) both |
| other-test | `mrp_port_status` reports LeaveAll Active (R903's plant) | rc 1, an unrevised test fails | PASS, PASS | PASS, PASS |

Each planted control must also find 0 decoded differences. In the signal and timeout controls, the fault must follow
both the revised failure and the completion line. The rc alone decides there.

## R903-1 suggestions

| ID | Taken | What |
|---|---|---|
| S1 | Yes | `doc/integrator.md`: a fitted value's Registrar change is reported as txLA!; the local rLA! reports the remaining ones |
| S2 | Yes, in the proposed body | `Refs #20` in place of `Closes #20`, so merging does not close #20 before its on-board receipt. Reversible: the manager may restore `Closes` |
| S3 | Yes | REVISED names the assertion's message; the `other-assertion` control pins it |
| S4 | Yes | The fitting and omitted tests assert no Leave indication at the own LeaveAll (+2 assertions per profile). Reversal `own-leaveall-registrar-indication` gives the rLA! row's IN cell an Lv indication; killed in both profiles by the omitted test, as required |
| S5 | No | It concerns the parent's proposed twin grade (`twin_mrp.py`), not lwSRP. It belongs to the pin bump: model txLAF! for omitted values, or check that the twin never fills an MRPDU |

## Merge with main

`main` `97677fcb` (issue #4: scenario steps read the simulated port flags; seven scenario reversals) conflicted only
in `doc/tester.md`, in two hunks:

- the check table: this branch's unit row (108 tests, 27199 assertions, ten suites) with main's scenario row
  ("... and reads the simulated port flags");
- the reversal paragraphs: both kept, total 110. `tests/check_reversals.py` auto-merged with 110 unique cases:
  main's 106 (99 + 7) and this branch's 4 (3 + 1).

`doc/manager.md` auto-merged: main's scenario lines and this branch's counts.

## Gates at the head

All at `f7111b27`, whose `src/`, `tests/` and `CMakeLists.txt` equal `25b5a740`'s. The documentation checks ran at `25b5a740`.

| Gate | Result |
|---|---|
| Build, Debug, both profiles | 0 warnings |
| Unit target | 108 tests; 27199 (default), 27187 (Milan) assertions; rc 0 |
| CTest; scenarios; dry run | 1/1 each; 3 scenarios, 10 steps both builds; dry run 3 and 10 untested |
| Codec, isolated | 9 tests, 1690 assertions |
| Tests first: this head's tests on `08ee86e8`'s sources | Exactly five tests fail, 38 assertions, both profiles (unchanged) |
| Sanitizers, address and undefined behaviour, gcc and clang, both profiles | rc 0, 0 reports, instrumentation symbols present; planted heap overread rc 1, reported |
| Freestanding (both profiles); embedded source list; strict `-Werror` gcc and clang, profile 0 and 1 | rc 0 each |
| Reversals, both profiles | 110 of 110 killed, each label once; restored build, checks and scenarios rc 0 |
| Equivalence against `9197193e`, both profiles | rc 0; 22 scenarios, 148 opportunities, 138 PDUs, 125 identical, 13 layout-only, 0 different; one REVISED |
| Equivalence controls, both profiles | 5 of 5 |
| Coverage, gcov, both profiles merged | Identical to round 1 per file: `mrp_mad.c` 95.54 % lines, 86.78 % branches; `sla_registrars` 6/6, 2/2; library 83.89 % branches |
| Docs: sentences, references and self-test, links (`--github-auth`), graphs | 1074 sentences, 0 over; 0 unlinked; 79 self-test cases; 382 local and 22 external links, 0 failures; 29 graphs |

## Consumer

Scratch milan-fpga `dev-soft-core` `854bd723` + round 1's two commits + `a9fff7ba` (pin `25b5a740`: gitlink,
`ctrl_arms.LWSRP_REV`, `SUBMODULES.md`, prose pins, regenerated boundary diagram and PNG manifest), local only.
Results are in HANDOFF-r2.md; every gate the brief names passes.

## Known cosmetic point

Run from a detached checkout, the controls' `git clone --shared` prints git's detached-HEAD advice once per control.
It does not affect any result.
