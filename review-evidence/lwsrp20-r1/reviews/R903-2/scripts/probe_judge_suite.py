# SPDX-License-Identifier: Apache-2.0
"""Grade tests/check_equivalence.py's judge_suite on synthetic suite endings.

Usage: python3 -I probe_judge_suite.py <lwSRP checkout>
Each case states whether the gate must accept (problem None) or reject it.
"""
import importlib.util, sys
from pathlib import Path

spec = importlib.util.spec_from_file_location("eq", Path(sys.argv[1]) / "tests/check_equivalence.py")
eq = importlib.util.module_from_spec(spec); spec.loader.exec_module(eq)
R = "full_leaveall_reports_each_required_transition"
HEAD = 'Running "main" (87 tests)...\n  "mrp_pdu_suite": 1690 passes in 13ms.\n'
def rep(test, msg, kind="Failure", line=347):
    return f"/x/tests/unit/review_test.c:{line}: {kind}: boundaries_suite -> {test} \n\t{msg}\n\t\tactual value:\t\t\t[0]\n\n"
REV = rep(R, "Expected [local_rla] to [equal] [1]")
DONE0 = 'Completed "main": 19901 passes in 127ms.\n'
DONE1 = 'Completed "main": 19900 passes, 1 failure in 127ms.\n'
DONE2 = 'Completed "main": 19899 passes, 2 failures in 127ms.\n'
DONEX = 'Completed "main": 19900 passes, 1 failure, 1 exception in 127ms.\n'
cases = [
    # name, suite, rc, log, accept
    ("clean pass", "candidate", 0, HEAD + DONE0, True),
    ("revised only", "candidate", 1, HEAD + REV + DONE1, True),
    ("revised, signal 15", "candidate", -15, HEAD + REV + DONE1, False),
    ("revised, signal 9", "candidate", -9, HEAD + REV + DONE1, False),
    ("revised, timeout", "candidate", eq.TIMEOUT, HEAD + REV + DONE1, False),
    ("rc 2", "candidate", 2, HEAD + DONE0, False),
    ("rc 3 after revised", "candidate", 3, HEAD + REV + DONE1, False),
    ("rc 0 without completion line", "candidate", 0, HEAD, False),
    ("rc 1 without completion line", "candidate", 1, HEAD + REV, False),
    ("rc 0 with one report", "candidate", 0, HEAD + REV + DONE1, False),
    ("rc 1 with no report", "candidate", 1, HEAD + DONE0, False),
    ("two completion lines", "candidate", 1, HEAD + REV + DONE1 + DONE1, False),
    ("completion counts 2, one report", "candidate", 1, HEAD + REV + DONE2, False),
    ("completion counts 1, two reports", "candidate", 1, HEAD + REV + REV + DONE1, False),
    ("revised test, other message", "candidate", 1, HEAD + rep(R, "Expected [omitted_txlaf] to [equal] [1]") + DONE1, False),
    ("revised test, exception", "candidate", 1, HEAD + rep(R, "Test terminated with signal: Segmentation fault", "Exception") + DONEX.replace("1 failure, ", ""), False),
    ("other test fails", "candidate", 1, HEAD + rep("other_test", "Expected [local_rla] to [equal] [1]") + DONE1, False),
    ("revised plus exception elsewhere", "candidate", 1, HEAD + REV + rep("t2", "Test terminated", "Exception") + DONEX, False),
    ("base fails revised", "base", 1, HEAD + REV + DONE1, False),
    ("base clean", "base", 0, HEAD + DONE0, True),
    ("nested suite path in report", "candidate", 1, HEAD + "/x/r.c:1: Failure: main -> boundaries_suite -> " + R + " \n\tExpected [local_rla] to [equal] [1]\n" + DONE1, False),
]
bad = 0
for name, suite, rc, log, accept in cases:
    revised, problem = eq.judge_suite(suite, rc, log, 600)
    ok = (problem is None) == accept
    bad += not ok
    print(f"{'OK ' if ok else 'BAD'} {name}: rc={rc} -> revised={revised} problem={problem}")
print(f"cases: {len(cases)}; wrong: {bad}")
sys.exit(int(bool(bad)))
