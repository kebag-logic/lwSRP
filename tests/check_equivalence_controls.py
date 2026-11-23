# SPDX-License-Identifier: Apache-2.0
"""Require the equivalence check to judge each planted suite ending correctly.

Each control clones this checkout into a new scratch directory, copies its
working tree over the clone, and plants one change in the clone's sources.
It then runs the clone's tests/check_equivalence.py and grades the exit status
and the recorded problems. The original checkout is never edited.

The genuine revised failure must pass. A signal or a timeout after that
failure, another assertion of the revised test, and a failure of another test
must each fail, while every transmit trace still compares identically.
"""

import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
REVISED = "full_leaveall_reports_each_required_transition"
TIMER = "src/ports/timer.c"
MAD = "src/core/mrp_mad.c"
# A fault in the suite process only, after its complete output is written.
# The runner forks each test; the forked children are unaffected.
SHUTDOWN = """
/* Equivalence control: end only the suite process, after its output. */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
static pid_t suite_pid;
__attribute__((constructor)) static void remember_suite_pid(void) { suite_pid = getpid(); }
__attribute__((destructor)) static void end_suite(void)
{
    if (getpid() == suite_pid) {
        fflush(NULL);
        %s
    }
}
"""
# Each control: name, planted file, text to replace (None appends), its
# replacement, and the problem the check must report (None for a pass).
CONTROLS = [
    ("revised", None, None, None, None),
    ("signal", TIMER, None, SHUTDOWN % "raise(SIGTERM);",
     "candidate unit suite: ended by signal 15 (SIGTERM)"),
    ("timeout", TIMER, None, SHUTDOWN % "for (;;) { pause(); }",
     "candidate unit suite: timed out after {timeout} s"),
    ("other-assertion", MAD, "    if (!priv->obs_fn) {\n",
     "    if (ev == MRP_EVENT_TXLAF) { return; }\n    if (!priv->obs_fn) {\n",
     f"candidate unit suite: rc=1; not revised: {REVISED}: Failure 'Expected [omitted_txlaf] to [equal] [1]'"),
    ("other-test", MAD, "        *la = priv->ports[port_id].la;\n", "        *la = MRP_LA_STATE_ACTIVE;\n",
     "candidate unit suite: rc=1"),
]


def prepare(name, work):
    """Clone the checkout, copy its working tree over the clone, and plant."""
    _, path, old, new, _ = next(control for control in CONTROLS if control[0] == name)
    clone = work / f"{name}-source"
    subprocess.run(["git", "clone", "--quiet", "--shared", str(ROOT), str(clone)], check=True)
    for part in ("CMakeLists.txt", "src", "tests"):
        target = clone / part
        if target.is_dir():
            shutil.rmtree(target)
            shutil.copytree(ROOT / part, target, ignore=shutil.ignore_patterns("__pycache__"))
        else:
            shutil.copy2(ROOT / part, target)
    if path:
        source = clone / path
        text = source.read_text()
        if old is None:
            text += new
        elif text.count(old) == 1:
            text = text.replace(old, new)
        else:
            raise SystemExit(f"{name}: the planted text is not unique in {path}")
        source.write_text(text)
    return clone


def failed_tests(suite):
    return {line.split(" -> ", 1)[1].split()[0] for line in suite.splitlines()
            if ": Failure: " in line and " -> " in line}


def grade(name, rc, result, timeout):
    """Return the reasons this control's outcome is wrong."""
    expected = next(control for control in CONTROLS if control[0] == name)[4]
    if result is None:
        return [f"gate rc={rc} without equivalence.json"]
    reasons = []
    problems = result["problems"]
    different = sum(row["different"] for row in result["rows"])
    if different or not result["rows"]:
        reasons.append(f"{different} decoded differences in {len(result['rows'])} scenarios")
    if expected is None:
        if rc != 0 or problems or result["revised"] != [REVISED]:
            reasons.append(f"gate rc={rc}, problems {problems}, revised {result['revised']}")
        return reasons
    expected = expected.format(timeout=timeout)
    if rc != 1 or len(problems) != 1 or not problems[0].startswith(expected):
        reasons.append(f"gate rc={rc}, problems {problems}; wanted rc=1 and one problem '{expected}'")
    return reasons


def run_control(name, args, work):
    clone = prepare(name, work)
    gate = work / name
    command = [sys.executable, "-I", "-B", str(clone / "tests/check_equivalence.py"), "--work-dir", str(gate),
               "--prefix", str(args.prefix), "--milan", args.milan]
    if name == "timeout":
        command += ["--suite-timeout", str(args.timeout)]
    log = work / f"{name}.log"
    with log.open("w") as out:
        rc = subprocess.run(command, cwd=clone, stdout=out, stderr=subprocess.STDOUT,
                            env=dict(os.environ, PYTHONDONTWRITEBYTECODE="1")).returncode
    path = gate / "equivalence.json"
    result = json.loads(path.read_text()) if path.exists() else None
    reasons = grade(name, rc, result, args.timeout)
    suite = gate / "unit-candidate.log"
    suite = suite.read_text() if suite.exists() else ""
    if name in ("signal", "timeout") and (f"-> {REVISED}" not in suite or 'Completed "main":' not in suite):
        reasons.append("the fault did not follow the revised failure and the completion line")
    if name == "other-test" and not failed_tests(suite) - {REVISED}:
        reasons.append("no test other than the revised one failed")
    print(f"{'PASS' if not reasons else 'FAIL'} {name}: gate rc={rc}" +
          "".join(f"; {reason}" for reason in reasons), flush=True)
    return {"control": name, "gate_rc": rc, "problems": result and result["problems"],
            "revised": result and result["revised"], "reasons": reasons}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work-dir", type=Path, required=True)
    parser.add_argument("--prefix", type=Path, required=True, help="unit framework prefix")
    parser.add_argument("--milan", choices=["OFF", "ON"], default="OFF")
    parser.add_argument("--timeout", type=int, default=480,
                        help="suite limit for the timeout control; above a normal suite run")
    parser.add_argument("--only", action="append", choices=[control[0] for control in CONTROLS])
    args = parser.parse_args()
    work = args.work_dir.resolve()
    if work.is_relative_to(ROOT) or work.exists():
        parser.error("Use a new scratch directory outside the checkout")
    work.mkdir(parents=True)
    args.prefix = args.prefix.resolve()
    names = args.only or [control[0] for control in CONTROLS]
    with ThreadPoolExecutor(max_workers=len(names)) as pool:
        results = list(pool.map(lambda name: run_control(name, args, work), names))
    (work / "controls.json").write_text(json.dumps({"milan": args.milan, "controls": results}, indent=2) + "\n")
    failed = [result["control"] for result in results if result["reasons"]]
    print(f"Controls: {len(results)}; failed: {len(failed)}" + (f" ({', '.join(failed)})" if failed else ""))
    return int(bool(failed))


if __name__ == "__main__":
    sys.exit(main())
