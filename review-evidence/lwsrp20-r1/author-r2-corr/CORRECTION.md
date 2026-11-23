# Correction to author-r2/PR-BODY.md (R904-2-F1)

This note supersedes the Checks paragraph of `author-r2/PR-BODY.md` (line 116). The live PR #21 body carries the corrected text:

> At the fix and merged head, all five controls produce zero decoded differences. Against `c035764f`, signal and
> other-assertion expose false acceptance. The timeout control exits 2 before execution because the old gate lacks
> `--suite-timeout`; it supplies no decoded comparison.

Source head unchanged: `25b5a7400ff618fa1404e452668ed6902daa5f74`. Evidence: `receipts/lwsrp/controls/c035764f-{OFF,ON}/controls.json` (`gate_rc: 2`).
