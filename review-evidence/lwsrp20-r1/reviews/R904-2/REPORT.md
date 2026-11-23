[R904] NEGATIVE - exact head 25b5a7400ff618fa1404e452668ed6902daa5f74

The original abnormal-exit finding is resolved. The implementation, strengthened checks and merge pass this delta review. One MINOR remains: the PR misstates the old timeout control's result. This affects Tests and Docs; it does not demonstrate a protocol defect.

Reviewed issue #20 / PR #21, round R904-2, from `c035764f2d6105fd9598b138112ba01eaa006958` to the exact head above. The tree is `ba42b8379d4a066580a8a5047083c355d102ae41`. The [public review start](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7115248127) fixes that scope. The independent verdict and five-lens ledger were written before reading either prior review's findings. No private author material, other checkout, or current-round reviewer report was read. No source edit or GitHub write was made.

Reconstruction followed the supplied instructions, CONTRIBUTING.md, README and guides, issue acceptance and public decisions, interfaces, delta/history, then published executable evidence. No repository or ancestor AGENTS.md was present. The five first-parent commits include merge `f7111b27f44542cb706c3ca4efd538c6503d56c7`, with parents `7b2f0b6e…` and `97677fcb…`.

Authorities are the [frozen acceptance and event-order ruling](https://github.com/kebag-logic/lwSRP/issues/20#issuecomment-7097311763), [scenario acceptance in issue #4](https://github.com/kebag-logic/lwSRP/issues/4), public MRP/switch interfaces, and the integrator's serialized callback contract. The ruling cites IEEE 802.1Q-2018 10.6, 10.7.6.6, 10.7.9, 10.8 NOTE 2 and Tables 10-3/10-4/10-5; Milan v1.2 4.2.7.2.2 and Table 4.3 supply withdrawal acceptance. The [2022 publisher page](https://standards.ieee.org/ieee/802.1q/10323/) was available, but its full normative text was not accessible. The requested 2022 rLA! cross-check therefore rests on the frozen ruling and unchanged implementation table, not an independently obtained complete standard. The round-1 conformance scope is carried forward, not expanded.

The [publication](https://github.com/kebag-logic/lwSRP/tree/bd72ffb4172b86e803a9c953681f550f151bbb88/review-evidence/lwsrp20-r1) was fetched at its exact commit. All 247 published `author-r2/` files match `published_sha256` in its manifest. That commit has no embedded signature, and no detached signature was supplied. Content integrity was verified; signer authentication is not claimed. Below, `packet/` means that publication's `author-r2/` directory.

**R904-2-F1 — MINOR — Tests, Docs — open.**

- **Location:** [PR #21, Checks paragraph](https://github.com/kebag-logic/lwSRP/pull/21); also [packet/PR-BODY.md:116](https://github.com/kebag-logic/lwSRP/blob/bd72ffb4172b86e803a9c953681f550f151bbb88/review-evidence/lwsrp20-r1/author-r2/PR-BODY.md#L116).
- **Defect:** the paragraph says the old gate accepted the signal, timeout and other-assertion controls. Only signal and other-assertion were accepted. In both profiles, the old timeout invocation exits 2 because `--suite-timeout` is unknown. No suite runs and no equivalence result exists for that invocation. The introductory zero-decoded-difference statement must likewise not be read as a measurement from that old timeout invocation.
- **Authority/evidence:** `packet/receipts/lwsrp/controls/c035764f-{OFF,ON}/controls.json` records `gate_rc: 2`, null problems/result, and failure to reach the suite completion line. Both `timeout.log` files reject the option. `packet/HANDOFF-r2.md:49` and `REVIEW-READY.md:38` state the distinction correctly. The live PR was re-read before finalization and still contains the inaccurate sentence. Reviewer receipts: `receipts/old-timeout.log`, `receipts/delta-verification.log`.
- **Impact:** the PR attributes an observed false acceptance to a run that never executed. This changes a test-result claim, so it is MINOR under the supplied rule, rather than wording-only RESIDUE. It does not reopen the fixed signal defect.
- **Required outcome:** replace that paragraph with: “At the fix and merged head, all five controls produce zero decoded differences. Against c035764f, signal and other-assertion expose false acceptance. The timeout control exits 2 before execution because the old gate lacks --suite-timeout; it supplies no decoded comparison.” Apply this to the live PR and proposed body, or publish an explicit superseding correction for the immutable packet.
- **Verification:** compare the corrected claim against both old-profile control records and timeout logs. No source change or broad rerun is required. If an old-gate runtime timeout result is desired instead, obtain it separately and distinguish it from these invocation failures.

No additional open MINOR, MAJOR or BLOCKER was found. No new RESIDUE or separate suggestion is raised. The changed source comments contain no prohibited lane, review-round, reviewer or issue-comment labels. Existing source-comment matters remain outside this delta.

**Prior findings and suggestions, explicitly reconciled.** The public [R904-1 findings](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7107320194) and [R903-1 findings](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7108550518) were read after the independent pass and recorded verdict.

| Prior item | Disposition at this head | Evidence / remaining outcome |
|---|---|---|
| R904-1-F1, MINOR, Tests/Robustness | RESOLVED | `tests/check_equivalence.py:66` rejects abnormal status before parsing exemptions. Signal controls report candidate -15 and gate 1 at fix/head, versus gate 0 previously, in both profiles. |
| R903-1-S1, Docs | APPLIED | `doc/integrator.md:150` distinguishes fitted Registrar txLA! transitions from remaining local rLA! transitions. |
| R903-1-S2, Conformance/Docs | APPLIED | Live PR says “Refs #20” and explains that physical acceptance remains outstanding. |
| R903-1-S3, Tests | APPLIED | The exemption matches the test and exact local_rla assertion message. The other-assertion plant fails at fix/head and was accepted previously. |
| R903-1-S4, Robustness | APPLIED | Zero-Leave assertions at `tests/unit/own_leaveall_test.c:360` and `:414`; the rLA! indication plant fails the named omitted-value test in both profiles. |
| R903-1-S5, Conformance/RTL | RETAINED as a parent suggestion | At the parent pin bump, model txLAF! for omitted values or enforce the no-full-PDU assumption. It concerns the consumer comparison grade, outside this library delta. |
| Prior merge conflict duty | RESOLVED for this library merge | Both parents' tester facts survive; the count is 110 because the new Registrar plant adds one beyond the previously suggested 109. |
| Prior parent timing-grade, timer-ambiguity, ROM and physical duties | RETAINED | Unchanged code does not settle those separate obligations; see limits below. |

**Conformance and implementation.** The diff of `src/`, `CMakeLists.txt`, `zephyr/`, `Kconfig.zephyr` and `build.sh` against round 1 is empty. Runtime interfaces, source lists, state transitions, received-LeaveAll behavior and transactional commit dependencies retain their prior verdicts.

The new Leave counters observe the stream application's actual indication callback after setup. They cover fitting and omitted own-LeaveAll opportunities. The unchanged Registrar rLA! row at `src/core/mrp_mad.c:375` has no indication: IN starts its timer and enters LV; LV and MT have no action. The rapid-withdrawal selection applies only to rLv!. The helper at `:774` remains valid in ignoring that row's indication result. The published plant changes the rLA! IN cell to indicate Leave; the omitted case reports `leaves = 1` instead of zero at line 414 in both profiles. Clean head receipts pass 27,199/27,187 assertions. This strengthens the existing invariant without changing the protocol implementation.

**Robustness and tests.** `judge_suite` rejects every negative status, timeout and exit outside 0/1. Accepted statuses require exactly one completion line, matching listed failure/exception counts and an agreeing exit code. Only the candidate's named revised assertion is exempt; base failures, exceptions, another assertion and another test are rejected.

The reviewer regraded published logs with the exact-head function and ran 156 additional cases covering signals 1–64, unknown positive exits, timeout, missing/duplicate completion, inconsistent counts/status, changed assertion text, base failure and clean completion. This was a focused function-level probe, not a fresh full equivalence build. The published full controls pass 5/5 at both fix and merged head in both profiles. Old signal and other-assertion controls demonstrate the intended regression; the old timeout evidence has the limitation in F1.

The scenario reader checks actual private port flags through the public switch handle. Its source-layout guard matches the unchanged adapter. Connection starts with enabled flags so reset is observable; enable/disable checks every flag; rejected operations must change none; teardown checks unchanged flags. The documented limitations remain honest: an omitted disconnect cannot be observed, and a reconnecting disable can pass the single-enabled-port scenario.

Independent focused builds exercised the switch boundary in both profile settings. Both baselines pass three scenarios and ten steps. Every plant compiles before behavioral grading:

| Plant | Exactly failing scenarios, both profiles |
|---|---|
| Disable dispatch, mapping, next-port | Disable a port |
| Enable dispatch | Enable a port; Disable a port |
| Connect no-op, connect dispatch | All three scenarios |
| Disconnect dispatch | Enable a port |

All expected assertion messages matched. Four lightweight jobs ran concurrently; no full parent bank or heavy build ran. Raw logs, exit files and summary are under `receipts/scenarios/`.

All 102 round-1 reversal definitions remain unchanged. Main's seven scenario additions survive byte-for-byte; the scenario files equal main's. Two main reversal targets already retargeted by round 1 remain retargeted to the corrected helper/signature. No required failure name was removed. All 110 labels are unique and each appears killed exactly once in both published profile logs. The revised assertion exemption is narrower, not looser.

**Merge and documentation.** Both-parent diffs of `f7111b27` were examined and retained in `receipts/merge-*-parent.diff`. The tester merge preserves the 108-test/ten-suite branch counts, main's state-reading scenario row, both reversal paragraphs, scenario limitations and setup guidance. The extra Registrar assertion gives 27,199/27,187 assertions; the combined reversal count is 110. README and manager counts agree. The final commit adds only the Registrar-table link. `src/`, `tests/` and `CMakeLists.txt` at the executed merge equal the published head, supporting execution attribution; documentation checks ran after the link change.

Independent documentation checks pass: 1,074 sentence/fragments, zero over-limit; zero unlinked references; 79 self-check cases. Published final link and graph receipts report 382 local links, 22 external URLs and 29 graphs without failures. Earlier `summary-quick.txt` records failed isolated documentation invocations; dedicated final successful receipts supersede them. The PR's other delta claims match the packet, subject to F1 and the limits here.

**RTL and consumer evidence.** There is no HDL, clock/reset, CDC, bus or memory-layout delta. This lens independently examined the unchanged compiled inputs, consumer pin patch, firmware shards, cycle-budget text, image allocation and carry-forward evidence. No new RTL execution is claimed.

The published consumer is based on `dev-soft-core` `854bd723` plus documented pin/reproduction changes. Its patch selects full lwSRP gitlink `25b5a7400ff618fa1404e452668ed6902daa5f74`. The four firmware shards each have exit 0 and terminal PASS, with 90/826/385/543 successful rows. Shard 0 reports 2,236 cases and 43 SRP host arms, including the two own-LeaveAll arms.

The reviewer recomputed race and MRPDU figures from published text; `receipts/consumer-audit.json` records results. Other explicitly published figures below were spot-checked, not independently rebuilt.

| Evidence | Result and scope |
|---|---|
| 8x8/1if race | 387 unique withdrawals: nine inputs × 43 offsets, 5–200 ms; all sent within 190 ms; every peer departure equals the Lv timestamp. |
| 1x1/1if race | 86 withdrawals; same 190 ms maximum and matching peer departures. |
| No withdrawal | Passing held-registration case over 90 seconds, five board and two peer LeaveAlls; 44 tests pass at each point. |
| Per-pass share | Published summaries: zero of 162,007 / 285,420 work passes over 2 ms. Longest reported passes: 152,972 / 157,621 cycles against 200,000. |
| MRPDU service | Recomputed table maxima 2.438 / 1.581 ms against 49 ms; 8x8 own-LeaveAll rows 0.541, 0.570 and 0.595 ms. |
| Notice arms | Both answering-every-port and answering-later arms report zero budget misses and zero over-share passes at both points. Published last notice is below 27 ms against 130 ms. |
| Recorded exceptions | Seven backlog/held-egress misses at each point remain misses. The 8x8 ledger holds all seven under their ruled figures, with no new miss. |
| Load / flip | Published loads 0.511 ≤ 0.70 and 0.744 ≤ 0.75. 1x1 txL 47.88 ≤ 49 ms, last notice 127.31 ≤ 130 ms. The 8x8 transmit estimate 76.81 ms is held against its 77 ms row. |
| Images | All 20 published comparison rows match round 1. Binaries were not independently rebuilt. Platform 8x8/1if remains 139,264 bytes and 58 memory tiles, with zero ROM margin. |

The service bound follows the [egress-counting ruling](https://github.com/kebag-logic/milan-fpga/issues/894#issuecomment-6867990126). Misses remain governed by the [held-egress decision](https://github.com/kebag-logic/milan-fpga/issues/894#issuecomment-6871343905), [six-row ledger ruling](https://github.com/kebag-logic/milan-fpga/issues/894#issuecomment-6914952893), and [last-row amendment](https://github.com/kebag-logic/milan-fpga/issues/894#issuecomment-6934688411). They are not universal timing success. The approximately 160 ms wait for a running Join timer in the saved LeaveAll window is distinct from service delay after an eligible opportunity.

**Reviewer-owned ledger.** CLEAN is scoped to this delta and carried dependencies; it does not mean physical or final merge-candidate acceptance.

| Lens | CLEAN/UNCLEAN | Examined artifacts | Covering round | Exact head |
|---|---|---|---|---|
| Conformance | CLEAN | Frozen ruling; unchanged core/interfaces; no-indication assertions, Registrar plant, consumer race records | R904-1 carried; R904-2 delta | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| RTL | CLEAN | Empty compiled-input delta; consumer gitlink, firmware shards, service/load/flip/image receipts | R904-1 carried; R904-2 evidence audit | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Robustness | CLEAN | Status/completion logic; 156 status/report probes; published controls; scenario state boundary | R904-2; prior F1 resolved | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Tests | UNCLEAN | Five-control matrices; 110 reversal tally; 16 independent scenario runs; inaccurate timeout-result claim F1 | R904-2 | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Docs | UNCLEAN | Both merge parents; guides/counts; independent checks; packet/live PR comparison and F1 | R904-2 | 25b5a7400ff618fa1404e452668ed6902daa5f74 |

**Real limits and manager duties.** No manager source bank ran at this exact head, and none is inferred. Source consumer execution belongs to the published author receipts. No exact-head workflow runs were returned by the public query; no hosted context is accepted here as executed. Hosted and local-runner acceptance remain the manager's responsibility.

The manager must validate the final current-dev candidate with required builder/native banks and publish its receipts. The supplied composition uses source base `c035764f2d6105fd9598b138112ba01eaa006958` and live dev `e275d7950ef3385753e6a15d2e191ba855b171ed`; the older consumer packet does not substitute for that candidate. Recheck CPU and zero-margin ROM limits there. Carry the exact gitlink, prose/diagram pins, reproduction arms and retained twin-grade suggestion. Retain the pre-existing red parent timing grade as unresolved, and the unchanged LeaveAll timer restart interpretation as previously recorded.

Physical calibration is **NOT RUN**. There was no bench access. Field skips and host simulations are not hardware proof. Frozen physical 8x8/1if withdrawal and uninterrupted-registration acceptance remains outstanding; “Refs #20” appropriately leaves issue closure separate. No full parent, protocol/time-processing, synthesis, builder or container campaign was run by this reviewer. No shared installation or other-checkout edit occurred.

Portable scripts are `verify_delta.py`, `probe_scenarios.py` and `audit_receipts.py`; usage is in their headers. They accept the checkout and extracted public packet paths. Disposable extraction/build trees are exclusively under `scratch/`, which is not publishable. All 67 tracked blobs and executable modes match the assigned head; the index equals its tree, and the checkout has no untracked files. This library has zero submodule gitlinks; the published consumer patch's required full gitlink was checked separately. Only REPORT.md and files listed in MANIFEST.sha256 are publishable.

R904-2 FINISHED
