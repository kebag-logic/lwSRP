#!/usr/bin/env python3
"""Compare two transmit traces of tests/unit/transmit_trace.c opportunity by opportunity.

Usage: trace_diff.py CHECKOUT BASE.trace CANDIDATE.trace OUT.json
Reuses the checkout's tests/check_equivalence.py read_trace; skips its grouped-form check.
Prints, per differing test, each opportunity whose result or decoded events differ.
"""
import json
import sys
from collections import Counter
from pathlib import Path


def main():
    checkout, base, cand, out = sys.argv[1:5]
    sys.path.insert(0, str(Path(checkout) / "tests"))
    import check_equivalence as eq  # noqa: E402
    b, c = eq.read_trace(Path(base)), eq.read_trace(Path(cand))
    report = {"tests": len(set(b) | set(c)), "opportunities": 0, "identical_events": 0, "differ": []}
    for test in dict.fromkeys(list(b) + list(c)):
        old, new = b.get(test, {}), c.get(test, {})
        keys = sorted(set(old) | set(new))
        for k in keys:
            report["opportunities"] += 1
            x, y = old.get(k), new.get(k)
            ex = [Counter(s["events"]) for s in x["sends"]] if x else None
            ey = [Counter(s["events"]) for s in y["sends"]] if y else None
            same = x is not None and y is not None and x.get("result") == y.get("result") and ex == ey
            if same:
                report["identical_events"] += 1
                continue
            report["differ"].append({
                "test": test, "opportunity": k,
                "base": None if x is None else {"result": x.get("result"), "events": [s["events"] for s in x["sends"]]},
                "candidate": None if y is None else {"result": y.get("result"), "events": [s["events"] for s in y["sends"]]},
            })
    Path(out).write_text(json.dumps(report, indent=1) + "\n")
    print(f"tests {report['tests']}; opportunities {report['opportunities']}; "
          f"identical {report['identical_events']}; different {len(report['differ'])}")
    per = Counter(d["test"] for d in report["differ"])
    for test, n in per.items():
        print(f"  {test}: {n}")


if __name__ == "__main__":
    main()
