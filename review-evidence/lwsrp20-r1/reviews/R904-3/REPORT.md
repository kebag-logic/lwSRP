[R904] POSITIVE - exact head 25b5a7400ff618fa1404e452668ed6902daa5f74

R904-2-F1 is CLOSED. The live Checks paragraph matches the required outcome, the immutable packet has an explicit superseding correction, and the head is unchanged. All five lenses are CLEAN within this narrow re-check. No new finding, suggestion or wording residue is raised.

This is R904-3 for [issue #20](https://github.com/kebag-logic/lwSRP/issues/20) / [PR #21](https://github.com/kebag-logic/lwSRP/pull/21). The [public review start](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7115524116) identifies the exact head. Its tree remains `ba42b8379d4a066580a8a5047083c355d102ae41`. Per the assigned scope, R904-2's other verdicts stand; this review does not repeat its campaigns or broaden acceptance.

Reconstruction followed the supplied instructions, CONTRIBUTING.md, README and guides, frozen issue acceptance and public comments, interfaces, requested diff/history, then published receipts. No repository or ancestor AGENTS.md was present. The independent diff pass preceded reading the public R904-2 finding. No other reviewer's report, private author material or prohibited directory was read. No source modification or remote write occurred.

The [frozen ruling](https://github.com/kebag-logic/lwSRP/issues/20#issuecomment-7097311763) remains the conformance authority. Its local LeaveAll event order and physical acceptance are unchanged. Relevant interfaces and observer contracts remain in `src/include/shish_lan/mrp.h`, `doc/integrator.md:150` and `doc/developer.md:274`. The requested `c035764f..25b5a740` diff and history were inspected for context; the source delta since R904-2 is empty.

**Closed finding: R904-2-F1 — MINOR — Tests, Docs.**

- **Artifact:** live PR Checks paragraph, lines 116–118 in [the captured body](receipts/pr-live-body.md); archived `author-r2/PR-BODY.md:116`.
- **Authority/evidence:** [R904-2 required outcome](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7115497125), retained in [prior-finding.txt](receipts/prior-finding.txt); both old-profile control records and timeout logs.
- **Original impact:** the old text attributed false acceptance and a decoded comparison to an invocation that never executed its suites. This was a test-result defect, not wording-only residue.
- **Required outcome:** distinguish the successful fix/head controls from the old timeout invocation; correct the live body and explicitly supersede the immutable body.
- **Verification:** PASS. The live paragraph equals the required text after removing Markdown backticks and folding line breaks. The entire live body also equals the archived corrected body under the same normalization. Only one paragraph differs between the original and corrected archived bodies.

The corrected text is:

> At the fix and merged head, all five controls produce zero decoded differences. Against `c035764f`, signal and other-assertion expose false acceptance. The timeout control exits 2 before execution because the old gate lacks `--suite-timeout`; it supplies no decoded comparison.

The [superseding note](https://github.com/kebag-logic/lwSRP/blob/c7a0e2a035de64dd25b45b37b7f6b78b7ceacbf1/review-evidence/lwsrp20-r1/author-r2-corr/CORRECTION.md) explicitly identifies the immutable paragraph and unchanged source head. Both old-profile `controls.json` files record timeout `gate_rc: 2`, null results, and no completion line. Both timeout logs reject `--suite-timeout 480`. The signal and other-assertion controls record false acceptance, as the corrected paragraph says.

The full live body was examined for another claim about that old invocation. None remains. The Checks table is expressly scoped to this head. The timeout control table states required behavior; the corrected paragraph states what happened at the old gate. The separate equivalence result concerns `9197193e`; the later `08ee86e8` comparison and consumer image comparison are different evidence. None supplies or implies a measurement from the old timeout invocation.

**Evidence verification.** [verify_review.py](verify_review.py) completed with exit 0. It retrieves the live body and head, checks the correction, audits both profiles, and verifies checkout integrity. [verification.json](receipts/verification.json), [control-audit.json](receipts/control-audit.json), and [body-claim-locations.json](receipts/body-claim-locations.json) record the checks.

All 25 selected public artifacts match their `published_sha256` entries at archive `c7a0e2a035de64dd25b45b37b7f6b78b7ceacbf1`. These include both bodies, the correction, identity and consumer pin evidence, and old/fix/head control receipts. Both fix and head matrices report all five controls passing. Their timeout result files report zero decoded differences, and their candidate logs contain suite completion. These are audited published executions, not new executions by this reviewer.

The archive commit's verification record says `unsigned`; no detached signature was present in its published tree. Content integrity is verified, but signer authentication is not claimed. This preserves the R904-2 limitation. See [archive-integrity.json](receipts/archive-integrity.json).

**Reviewer-owned ledger.** CLEAN applies to F1's correction and carried dependencies, not hardware or final merge-candidate acceptance.

| Lens | CLEAN/UNCLEAN | Examined artifacts | Covering round | Exact head |
|---|---|---|---|---|
| Conformance | CLEAN | Frozen ruling; unchanged public interfaces; live event-order and “Refs #20” scope; correction adds no clause claim | R904-2 carried; R904-3 scope check | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| RTL | CLEAN | Identical head/tree; empty compiled-input diff; published identity and consumer patch pin; no implementation change | R904-2 carried; R904-3 identity check | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Robustness | CLEAN | Unchanged abnormal-exit logic and controls; fix/head timeout completion and rejection receipts; correction changes no execution behavior | R904-2 carried; R904-3 receipt spot-check | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Tests | CLEAN | Both old timeout logs and control matrices; fix/head matrices and timeout comparisons; full live-body result attribution; F1 closed | R904-2 carried; R904-3 F1 closure | 25b5a7400ff618fa1404e452668ed6902daa5f74 |
| Docs | CLEAN | CONTRIBUTING.md; README/guides; live Checks paragraph; original/corrected bodies; superseding note; complete body claim audit | R904-2 carried; R904-3 F1 closure | 25b5a7400ff618fa1404e452668ed6902daa5f74 |

**Prior dispositions carried forward.** The [R904-2 ledger](https://github.com/kebag-logic/lwSRP/pull/21#issuecomment-7115497125) resolved R904-1-F1 and recorded R903-1-S1 through S4 as applied. Those dispositions stand at the identical head. R903-1-S5 remains a consumer suggestion: model txLAF! for omitted values or enforce the no-full-PDU assumption at the pin bump. The library merge-conflict duty remains resolved. Parent timing-grade, timer-interpretation, ROM and physical duties remain pending as previously recorded. These inherited items are not new findings. There is no source-comment delta, so this round introduces no comment-label residue.

**Real limits and pending manager duties.** No manager source bank ran at this head, and none is inferred. Source-head execution evidence belongs to the author receipts. No new build, mutation campaign, hosted job or physical run was needed for this prose-and-evidence correction. This review accepts no skipped context as executed evidence.

The manager owns hosted/local acceptance and the final current-dev candidate's builder/native banks, with receipts published on the PR. The supplied composition uses source base `c035764f2d6105fd9598b138112ba01eaa006958` and live dev `e275d7950ef3385753e6a15d2e191ba855b171ed`. Source receipts do not substitute for that candidate. Recheck CPU limits, the zero-margin ROM image, exact consumer pin and associated documentation there. Retain the consumer comparison suggestion and pre-existing parent timing and timer-interpretation duties.

Physical calibration is **NOT RUN**. Host reproductions and field skips are not hardware proof. Frozen physical withdrawal and uninterrupted-registration acceptance remain outstanding; issue #20 remains separate from this source review's positive verdict.

All 67 tracked blobs and executable modes match the exact head. The index equals the assigned tree and the checkout is clean. This library has no submodule gitlinks; the published consumer patch pins the required full head. See [checkout-integrity.json](receipts/checkout-integrity.json). No restoration was needed because no source bytes changed. Disposable material is confined to `scratch/` and excluded from publication. Only this report and files listed in MANIFEST.sha256 are publishable.

R904-3 FINISHED
