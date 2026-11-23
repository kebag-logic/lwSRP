# SPDX-License-Identifier: Apache-2.0
"""Run a chosen subset of tests/check_reversals.py's CASES, judged by its own rules.

Usage: python3 -I probe_reversals_subset.py <lwSRP checkout> <work dir> <cgreen prefix> <OFF|ON> <label>...
Copies the checkout's CMakeLists.txt, src and tests into the work dir; never edits the checkout.
For unit cases it also lists every failing test, so a plant's whole kill set is visible.
"""
import importlib.util, os, re, shutil, subprocess, sys
from pathlib import Path

root, work, prefix, milan = Path(sys.argv[1]), Path(sys.argv[2]), Path(sys.argv[3]), sys.argv[4]
labels = sys.argv[5:]
spec = importlib.util.spec_from_file_location("rev", root / "tests/check_reversals.py")
rev = importlib.util.module_from_spec(spec); spec.loader.exec_module(rev)
work.mkdir(parents=True)
src = work / "source"; src.mkdir()
for n in ("CMakeLists.txt", "src", "tests"):
    (shutil.copytree if (root / n).is_dir() else shutil.copy2)(root / n, src / n)
build = work / "build"
env = dict(os.environ, LD_LIBRARY_PATH=str(prefix / "lib"), SHLAN_LIBRARY=str(build / "libshlan.so"))
def run(cmd):
    r = subprocess.run(cmd, cwd=src, env=env, capture_output=True, text=True, timeout=300)
    return r.returncode, r.stdout + r.stderr
assert run(["cmake", "-S", str(src), "-B", str(build), "-DCMAKE_BUILD_TYPE=Release",
            f"-DCMAKE_PREFIX_PATH={prefix}", f"-DLWSRP_MILAN={milan}"])[0] == 0
bcmd = ["cmake", "--build", str(build), "--parallel", "4"]
ucmd = [str(build / "unit_tests")]
scmd = [sys.executable, "-m", "behave", "--no-color", "tests/features"]
assert run(bcmd)[0] == 0 and run(ucmd)[0] == 0 and run(scmd)[0] == 0, "baseline"
cases = {c[0]: c for c in rev.CASES}
bad = 0
for label in labels:
    _, name, old, new, check = cases[label]
    path = src / name; original = path.read_text()
    assert original.count(old) == 1, f"{label}: target count {original.count(old)}"
    path.write_text(original.replace(old, new))
    try:
        brc, _ = run(bcmd)
        if brc:
            print(f"FAIL {label}: build"); bad += 1; continue
        if check == "unit":
            rc, out = run(ucmd)
            failing = sorted(set(re.findall(r"(?:Failure|Exception): \S+ -> (\S+)", out)))
            req = rev.REQUIRED_FAILURES.get(label, [])
            killed = rc != 0 and failing and all(t in failing for t in req)
            print(f"{'KILLED' if killed else 'FAIL'} {label}: rc={rc}; required {req}; failing {failing}")
        else:
            rc, out = run(scmd)
            want, words = rev.SCENARIO_FAILURES[label]
            got = rev.failed_scenarios(out)
            killed = rc != 0 and got == want and words in out
            print(f"{'KILLED' if killed else 'FAIL'} {label}: rc={rc}; failing {sorted(got)}; wanted {sorted(want)}; words {'found' if words in out else 'missing'}")
        bad += not killed
    finally:
        path.write_text(original)
assert run(bcmd)[0] == 0 and run(ucmd)[0] == 0 and run(scmd)[0] == 0, "restored"
print(f"restored build, unit and scenarios rc 0; cases {len(labels)}; not killed {bad}")
sys.exit(int(bool(bad)))
