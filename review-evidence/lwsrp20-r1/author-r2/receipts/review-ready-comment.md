[A832] REVIEW READY

Head `25b5a740` on `20-own-leaveall-lv`: five commits after the reviewed `c035764f`, one of them the merge of `main` at `97677fcb`. Not pushed; the updated PR body is with the manager. No compiled source changes since `c035764f`.

**R904-1-F1 (equivalence gate accepted a suite ended by SIGTERM): fixed.** `tests/check_equivalence.py` now judges how each unit suite ended before reading its log. A signal, a time limit (`--suite-timeout`) or any exit other than 0 or the runner's 1 fails. Exit 0 or 1 needs one completion line whose counts match the listed failures. The candidate may fail only the listed revised assertion, matched by its message (R903-1-S3).

The reviewer's probe is now `tests/check_equivalence_controls.py`. It runs five planted controls in scratch clones. The check must accept the genuine revised failure. It must reject SIGTERM or a hang after the complete suite output, another assertion of the revised test, and another test's failure. Each must also find no decoded difference. Both profiles pass 5 of 5 at the head. Against the gate at `c035764f`, the signal, time-limit and other-assertion controls fail in both profiles.

**R903-1 suggestions.** S1 (observer wording), S3 and S4 are applied. For S4, the own-LeaveAll tests now require no Leave indication at the LeaveAll, and a reversal gives the Registrar's rLA! cell one; it is killed. S2 is proposed in the body as "Refs #20", for the manager to decide. S5 concerns the consumer's twin grade and is left to the pin bump.

**Merge.** Only `doc/tester.md` conflicted. Both texts' facts are kept: this change's unit counts, `main`'s scenario row, and both reversal paragraphs, at 110 reversals.

**Gates at the merged head.** The unit target passes 108 tests (27199 and 27187 assertions). CTest, scenarios, codec, sanitizers with two compilers, freestanding, embedded and strict compiles pass. So do 110 of 110 reversals per profile, the equivalence check (0 decoded differences), coverage (unchanged) and the documentation checks.

**Consumer** (milan-fpga `dev-soft-core` `854bd723` with this pin, scratch clone). `main`'s later commits change only lwSRP's tests and documents. The firmware images are byte-identical to those built with `c035764f`. The firmware gate's four shards pass. The own-LeaveAll reproduction at 8x8/1if sends all 387 withdrawals as Lv within 190 ms (240 ms bound), and the peer deregisters on each. The CPU service budget passes at 1x1/1if and 8x8/1if. No pass exceeds the 2 ms share, and every MRPDU leaves within 2.5 ms (49 ms bound). Load, flip and the image ledger pass.
