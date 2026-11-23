#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Merged (OFF + ON profile) line and branch coverage of src/core/mrp_mad.c,
and of the lines of one function, from gcov JSON.

Usage: gcov_merge.py <function-name> <gcda> [<gcda> ...]
A line counts as covered if any profile executed it; a branch (line, index)
counts as taken if any profile took it.
"""
import json
import subprocess
import sys
from pathlib import Path


def load(gcda):
    gcda = Path(gcda).resolve()
    out = subprocess.run(["gcov", "--json-format", "--stdout", "-b", str(gcda)],
                         cwd=gcda.parent, capture_output=True, text=True, check=True).stdout
    docs = [json.loads(line) for line in out.splitlines() if line.strip().startswith("{")]
    for doc in docs:
        for f in doc["files"]:
            if f["file"].endswith("src/core/mrp_mad.c"):
                return f
    raise SystemExit(f"no mrp_mad.c record in {gcda}")


def main():
    func = sys.argv[1]
    lines, branches, span = {}, {}, None
    for gcda in sys.argv[2:]:
        f = load(gcda)
        for fn in f["functions"]:
            if fn["name"] == func:
                span = (fn["start_line"], fn["end_line"])
        for ln in f["lines"]:
            n = ln["line_number"]
            lines[n] = lines.get(n, False) or ln["count"] > 0
            for i, br in enumerate(ln.get("branches", [])):
                key = (n, i)
                branches[key] = branches.get(key, False) or br["count"] > 0
    lc = sum(lines.values()); bc = sum(branches.values())
    print(f"mrp_mad.c merged: lines {lc}/{len(lines)} = {100.0 * lc / len(lines):.2f} %; "
          f"branches taken {bc}/{len(branches)} = {100.0 * bc / len(branches):.2f} %")
    if span:
        fl = {k: v for k, v in lines.items() if span[0] <= k <= span[1]}
        fb = {k: v for k, v in branches.items() if span[0] <= k[0] <= span[1]}
        print(f"{func} (lines {span[0]}-{span[1]}): lines {sum(fl.values())}/{len(fl)}; "
              f"branches taken {sum(fb.values())}/{len(fb)}")
    else:
        print(f"{func}: not present")


if __name__ == "__main__":
    main()
