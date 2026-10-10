# SPDX-License-Identifier: Apache-2.0
"""Show that grouping changes only the MRPDU layout, never the decoded events.

The base revision's own unit suite is the scenario set. It is built twice in a
new scratch directory: with the base sources, and with this checkout's sources.
Both runs preload tests/unit/transmit_trace.c, which decodes every offered
MRPDU with the test-side decoder (IEEE 802.1Q-2018 10.8.1.2 and 10.8.2).
Each transmit opportunity must return the same result and offer PDUs whose
decoded events are equal. The checkout's PDUs must also have the grouped form.
"""

import argparse
from collections import OrderedDict
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
BASE = "9197193e47a6bb1c45a56d90a18c1784123aba44"


def run(label, command, work, env=None, cwd=None):
    result = subprocess.run(command, cwd=cwd, env=env, capture_output=True, text=True, timeout=600)
    (work / f"{label}.log").write_text(result.stdout + result.stderr)
    print(f"{label}: rc={result.returncode}", flush=True)
    return result.returncode


def read_trace(path):
    """Group records by test, then by transmit opportunity."""
    tests = OrderedDict()
    if not path.exists():
        return tests
    for line in path.read_text().splitlines():
        fields = line.split("\t")
        calls = tests.setdefault(fields[1], OrderedDict())
        call = calls.setdefault(int(fields[2]), {"sends": []})
        if fields[0] == "S":
            call["sends"].append({"rc": int(fields[6]), "bytes": fields[8], "layout": fields[9],
                                  "events": fields[10].split()})
        else:
            call.update({"ethertype": fields[3], "capacity": int(fields[5]),
                         "result": int(fields[6])})
    return tests


def grouped(send):
    """The issue #17 form: one Message per type in type order, one EndMark each,
    LeaveAll ahead of a type's values, and values in ascending FirstValue order."""
    if send["layout"] == "undecodable":
        return False
    messages, end_marks, trailing = send["layout"].split(";")
    types = [int(m.split("x")[0]) for m in messages.split(",")]
    if types != sorted(set(types)) or int(end_marks[1:]) != len(types) + 1 or trailing != "T0":
        return False
    last = {}
    for token in send["events"]:
        if token.startswith("LA"):
            if int(token[2:]) in last:
                return False
            last[int(token[2:])] = ""
            continue
        kind, value, _ = token.split(":", 2)
        first, offset = value.split("+")
        if offset != "0" or first <= last.get(int(kind), ""):
            return False
        last[int(kind)] = first
    return True


def compare(base, candidate):
    rows, problems = [], []
    for test in OrderedDict.fromkeys(list(base) + list(candidate)):
        old, new = base.get(test, {}), candidate.get(test, {})
        row = {"test": test, "opportunities": len(new), "sends": 0, "identical": 0,
               "layout_only": 0, "different": 0}
        if list(old) != list(new):
            problems.append(f"{test}: {len(old)} base and {len(new)} candidate opportunities")
        for index in new:
            a, b = old.get(index, {"sends": []}), new[index]
            if a.get("result") != b.get("result") or len(a["sends"]) != len(b["sends"]):
                problems.append(f"{test} #{index}: result {a.get('result')} -> {b.get('result')}")
            for x, y in zip(a["sends"], b["sends"]):
                row["sends"] += 1
                if x["rc"] != y["rc"] or sorted(x["events"]) != sorted(y["events"]):
                    row["different"] += 1
                    problems.append(f"{test} #{index}: decoded events differ")
                elif x["bytes"] == y["bytes"]:
                    row["identical"] += 1
                else:
                    row["layout_only"] += 1
                if not grouped(y):
                    problems.append(f"{test} #{index}: candidate PDU is not grouped")
        rows.append(row)
    return rows, problems


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work-dir", type=Path, required=True)
    parser.add_argument("--prefix", type=Path, required=True, help="unit framework prefix")
    parser.add_argument("--base", default=BASE, help="revision whose encoder and suite are the reference")
    parser.add_argument("--milan", choices=["OFF", "ON"], default="OFF")
    args = parser.parse_args()
    work = args.work_dir.resolve()
    if work.is_relative_to(ROOT) or work.exists():
        parser.error("Use a new scratch directory outside the checkout")
    work.mkdir(parents=True)
    prefix = args.prefix.resolve()
    trees = {"base": work / "base", "candidate": work / "candidate"}
    archive = work / "base.tar"
    if run("archive", ["git", "-C", str(ROOT), "archive", "-o", str(archive), args.base,
                       "CMakeLists.txt", "src", "tests"], work):
        return 1
    for tree in trees.values():
        tree.mkdir()
        if run(f"extract-{tree.name}", ["tar", "-xf", str(archive), "-C", str(tree)], work):
            return 1
    shutil.rmtree(trees["candidate"] / "src")
    shutil.copytree(ROOT / "src", trees["candidate"] / "src")
    shim = work / "transmit_trace.so"
    if run("shim", ["cc", "-std=gnu11", "-shared", "-fPIC", "-Wall", "-Wextra",
                    f"-I{ROOT / 'src/include'}", f"-I{ROOT / 'tests/unit'}", f"-I{prefix / 'include'}",
                    str(ROOT / "tests/unit/transmit_trace.c"), str(ROOT / "tests/unit/mrpdu_decoder.c"),
                    "-o", str(shim), f"-L{prefix / 'lib'}", "-lcgreen", "-ldl"], work):
        return 1
    traces, suites = {}, {}
    for name, tree in trees.items():
        build = work / f"build-{name}"
        env = os.environ.copy()
        env["LD_LIBRARY_PATH"] = str(prefix / "lib") + os.pathsep + env.get("LD_LIBRARY_PATH", "")
        if run(f"configure-{name}", ["cmake", "-S", str(tree), "-B", str(build), "-DCMAKE_BUILD_TYPE=Debug",
                                     f"-DCMAKE_PREFIX_PATH={prefix}", f"-DLWSRP_MILAN={args.milan}"], work, env) or \
           run(f"build-{name}", ["cmake", "--build", str(build), "--parallel", "2"], work, env):
            return 1
        traces[name] = work / f"{name}.trace"
        env["LD_PRELOAD"] = str(shim)
        env["LWSRP_TRANSMIT_TRACE"] = str(traces[name])
        # Compare even after a failing suite: the trace locates the first difference.
        suites[name] = run(f"unit-{name}", [str(build / "unit_tests")], work, env, cwd=build)
    rows, problems = compare(read_trace(traces["base"]), read_trace(traces["candidate"]))
    problems += [f"{name} unit suite: rc={rc}" for name, rc in suites.items() if rc]
    (work / "equivalence.json").write_text(json.dumps({"base": args.base, "milan": args.milan,
                                                       "rows": rows, "problems": problems}, indent=2) + "\n")
    print("| Scenario | Opportunities | PDUs | Byte-identical | Layout-only | Different |")
    print("| --- | --- | --- | --- | --- | --- |")
    for row in rows:
        print(f"| {row['test']} | {row['opportunities']} | {row['sends']} | {row['identical']} | "
              f"{row['layout_only']} | {row['different']} |")
    totals = {key: sum(row[key] for row in rows)
              for key in ("opportunities", "sends", "identical", "layout_only", "different")}
    print(f"Scenarios: {len(rows)}; opportunities: {totals['opportunities']}; PDUs: {totals['sends']}; "
          f"byte-identical: {totals['identical']}; layout-only: {totals['layout_only']}; "
          f"different: {totals['different']}; problems: {len(problems)}")
    for problem in problems:
        print(f"FAIL {problem}")
    return int(bool(problems) or totals["sends"] == 0)


if __name__ == "__main__":
    sys.exit(main())
