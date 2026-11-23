#!/usr/bin/env python3
"""Line and branch coverage of lwSRP's library sources from gcc's gcov JSON.

Usage: lwsrp_cov.py SRCROOT BUILD [BUILD...] [--functions NAME,NAME] [--json OUT]

Each BUILD is a CMake build directory whose unit_tests ran with --coverage.
Builds are merged per source line: a line is covered when any build ran it,
and an arc when any build took it (the parent's fw_coverage.py rule).
"""
import gzip
import json
import subprocess
import sys
import tempfile
from pathlib import Path


def gcov_json(gcda: Path, cwd: Path):
    with tempfile.TemporaryDirectory() as tmp:
        subprocess.run(["gcov", "--json-format", "--branch-probabilities", str(gcda)],
                       cwd=tmp, check=True, capture_output=True)
        for out in Path(tmp).glob("*.gcov.json.gz"):
            yield json.loads(gzip.decompress(out.read_bytes()))


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    funcs = []
    out_json = None
    for n, a in enumerate(sys.argv):
        if a == "--functions":
            funcs = sys.argv[n + 1].split(",")
        if a == "--json":
            out_json = sys.argv[n + 1]
    args = [a for a in args if a not in funcs and a != out_json]
    root = Path(args[0]).resolve()
    builds = [Path(b).resolve() for b in args[1:]]
    lines = {}      # file -> line -> [count, [arc taken...]]
    fn_ranges = {}  # file -> name -> (start, end)
    for b in builds:
        for gcda in sorted((b / "CMakeFiles" / "shlan.dir").rglob("*.gcda")):
            for doc in gcov_json(gcda, b):
                for f in doc["files"]:
                    name = f["file"]
                    p = Path(name)
                    if not p.is_absolute():
                        p = (Path(doc.get("current_working_directory", b)) / p).resolve()
                    try:
                        rel = str(p.resolve().relative_to(root))
                    except ValueError:
                        continue
                    if not rel.startswith("src/"):
                        continue
                    per = lines.setdefault(rel, {})
                    for fn in f.get("functions", []):
                        fn_ranges.setdefault(rel, {})[fn["demangled_name"]] = (fn["start_line"], fn["end_line"])
                    for ln in f["lines"]:
                        entry = per.setdefault(ln["line_number"], [0, []])
                        entry[0] += ln["count"]
                        arcs = [br["count"] > 0 for br in ln["branches"] if not br.get("throw")]
                        if len(arcs) > len(entry[1]):
                            entry[1] = [x or (i < len(entry[1]) and entry[1][i]) for i, x in enumerate(arcs)]
                        else:
                            entry[1] = [x or (i < len(arcs) and arcs[i]) for i, x in enumerate(entry[1])]
    report = {}
    tl = tc = bl = bc = 0
    print(f"{'file':40s} {'lines':>12s} {'branches':>12s}")
    for rel in sorted(lines):
        per = lines[rel]
        l_total = len(per)
        l_cov = sum(1 for e in per.values() if e[0] > 0)
        b_total = sum(len(e[1]) for e in per.values())
        b_cov = sum(sum(e[1]) for e in per.values())
        report[rel] = {"lines": [l_cov, l_total], "branches": [b_cov, b_total],
                       "uncovered_lines": sorted(n for n, e in per.items() if e[0] == 0),
                       "partial_branch_lines": sorted(n for n, e in per.items() if e[1] and not all(e[1]))}
        tl += l_total; tc += l_cov; bl += b_total; bc += b_cov
        print(f"{rel:40s} {l_cov:5d}/{l_total:<6d} {b_cov:5d}/{b_total:<6d}"
              f" lines {100.0 * l_cov / max(l_total, 1):6.2f} %  branches {100.0 * b_cov / max(b_total, 1):6.2f} %")
    print(f"{'total':40s} {tc:5d}/{tl:<6d} {bc:5d}/{bl:<6d}"
          f" lines {100.0 * tc / max(tl, 1):6.2f} %  branches {100.0 * bc / max(bl, 1):6.2f} %")
    for name in funcs:
        for rel, ranges in fn_ranges.items():
            if name in ranges:
                s, e = ranges[name]
                per = lines[rel]
                sel = {n: v for n, v in per.items() if s <= n <= e}
                lc = sum(1 for v in sel.values() if v[0] > 0)
                bt = sum(len(v[1]) for v in sel.values())
                bcv = sum(sum(v[1]) for v in sel.values())
                miss = sorted(n for n, v in sel.items() if v[0] == 0 or (v[1] and not all(v[1])))
                print(f"function {name} ({rel}:{s}-{e}): lines {lc}/{len(sel)}, branches {bcv}/{bt}, "
                      f"lines with an uncovered item: {miss}")
                report.setdefault("functions", {})[name] = {"file": rel, "range": [s, e], "lines": [lc, len(sel)],
                                                            "branches": [bcv, bt], "missing": miss}
    if out_json:
        Path(out_json).write_text(json.dumps(report, indent=1) + "\n")


if __name__ == "__main__":
    main()
