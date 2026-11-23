#!/usr/bin/env python3
"""Write round 2's receipts manifest (dest<TAB>source) for pack_receipts.py: make_manifest.py OUT."""
import sys
from pathlib import Path

R = Path("<scratch>/r2")
G = R / "gates"
rows = []


def add(dest, src):
    src = Path(src)
    if src.exists():
        rows.append(f"{dest}\t{src}")
    else:
        rows.append(f"# missing: {dest}\t{src}")


q = G / "quick"
for m in ("OFF", "ON"):
    for kind in ("build", "unit", "ctest", "cfg"):
        add(f"lwsrp/unit/{kind}-{m}.log", q / f"{kind}-{m}.log")
    add(f"lwsrp/gates/behave-{m}.log", q / f"behave-{m}.log")
    add(f"lwsrp/gates/free-{m}.log", q / f"free-{m}.log")
add("lwsrp/gates/behave-dry.log", q / "behave-dry.log")
add("lwsrp/gates/codec.log", q / "codec.log")
add("lwsrp/gates/embedded.log", q / "embedded.log")
for cc in ("gcc", "clang"):
    for m in ("0", "1"):
        add(f"lwsrp/gates/strict-{cc}-{m}.log", q / f"strict-{cc}-{m}.log")
    for m in ("OFF", "ON"):
        add(f"lwsrp/sanitizers/{cc}-{m}.log", q / f"san-{cc}-{m}.log")
        add(f"lwsrp/sanitizers/{cc}-{m}.build.log", q / f"san-{cc}-{m}.build.log")
add("lwsrp/sanitizers/planted-overread.log", q / "san-neg.log")
add("lwsrp/coverage/head.txt", q / "coverage.txt")
add("lwsrp/coverage/head.json", q / "coverage.json")
add("lwsrp/summary-quick.txt", q / "summary-quick.txt")
for n in ("sentences", "references", "references-self", "links", "graphs"):
    add(f"lwsrp/docs/{n}.log", G / "docs" / f"{n}.log")
for m in ("OFF", "ON"):
    add(f"lwsrp/reversals/rev-{m}.log", G / f"rev-{m}" / f"rev-{m}.log")
    add(f"lwsrp/equivalence/eq-{m}.log", G / f"eq-{m}" / f"eq-{m}.log")
    add(f"lwsrp/equivalence/eq-{m}.json", G / f"eq-{m}" / f"work-{m}" / "equivalence.json")
    add(f"lwsrp/equivalence/eq-{m}-unit-candidate.log", G / f"eq-{m}" / f"work-{m}" / "unit-candidate.log")
    add(f"lwsrp/equivalence/eq-{m}-unit-base.log", G / f"eq-{m}" / f"work-{m}" / "unit-base.log")
# The equivalence controls: at the head (gates/ctl-*), at the fix before the merge (ctl/fix-*), and the same
# controls against c035764f's gate (ctl/old-*), where the regression must fail.
for label, base in (("head", G), ("fix", R / "ctl"), ("c035764f", R / "ctl")):
    for m in ("OFF", "ON"):
        if label == "head":
            run, work = base / f"ctl-{m}" / f"ctl-{m}.log", base / f"ctl-{m}" / f"work-{m}"
        else:
            name = ("fix-" if label == "fix" else "old-") + m
            run, work = base / f"{name}.log", base / name
        add(f"lwsrp/controls/{label}-{m}/run.log", run)
        add(f"lwsrp/controls/{label}-{m}/controls.json", work / "controls.json")
        for c in ("revised", "signal", "timeout", "other-assertion", "other-test"):
            add(f"lwsrp/controls/{label}-{m}/{c}.log", work / f"{c}.log")
            add(f"lwsrp/controls/{label}-{m}/{c}-equivalence.json", work / c / "equivalence.json")
            add(f"lwsrp/controls/{label}-{m}/{c}-unit-candidate.log", work / c / "unit-candidate.log")
for m in ("OFF", "ON"):
    add(f"lwsrp/tests-first/unit-{m}.log", R / "tf" / f"unit-{m}.log")
add("lwsrp/tests-first/PROVENANCE", R / "tf" / "src-OFF" / "PROVENANCE")
for v in ("head", "plant"):
    for m in ("OFF", "ON"):
        add(f"lwsrp/registrar-indication-probe/{v}-{m}.log", R / "s4q" / f"{v}-{m}" / "unit.log")
for f in ("commits.txt", "identity.txt", "delta-stat.txt", "delta-from-c035764f.diff", "round2-own-commits.diff",
          "merge-tester-cc.diff", "merge-and-link-docs.diff", "pr-vs-main-stat.txt"):
    add(f"lwsrp/lane/{f}", R / "lane" / f)
# Parent.
add("parent/patches/0003-pin-25b5a740.patch", R / "parent-patch" / "0003-pin-25b5a740.patch")
add("parent/patches/parent-diagram.log", R / "parent-diagram.log")
for k in range(4):
    for f in (f"gate-{k}.log", f"rc-{k}", f"start-{k}", f"end-{k}"):
        add(f"parent/firmware/{f}", R / "fw" / f)
add("parent/firmware/summary.txt", R / "fw" / "summary.txt")
for f in ("own-head.log", "grade.txt", "rc", "start", "end"):
    add(f"parent/own-leaveall/{f}", R / "own" / f)
for arm in ("8x8", "1x1_tdm8"):
    add(f"parent/own-leaveall/run-{arm}.log",
        R / "own" / "head" / "build" / f"srp-srp_own_leaveall-if1-endstation_ax7101_{arm}" / "run.log")
for p in ("1x1", "8x8-1if", "1x1-every", "8x8-1if-every", "1x1-later", "8x8-1if-later"):
    for f in (f"run-{p}.log", f"rc-{p}", f"start-{p}", f"end-{p}"):
        add(f"parent/harness/{f}", R / "harness" / f)
    add(f"parent/harness/table-{p}.md", R / "harness" / f"b-{p}" / "results" / "table.md")
    add(f"parent/harness/grade-{p}.txt", R / "harness" / f"grade-{p}.txt")
add("parent/harness/selftest.log", R / "harness" / "selftest.log")
add("parent/harness/rc-selftest", R / "harness" / "rc-selftest")
add("parent/harness/egress-ledger-8x8-1if.log", R / "harness" / "egress-ledger-8x8-1if.log")
add("parent/harness/egress-ledger-selftest.log", R / "harness" / "egress-ledger-selftest.log")
add("parent/harness/own-leaveall-window/8x8-save-groups.txt", R / "harness" / "8x8-save-groups.txt")
for f in ("load_check.log", "flip_1x1.log", "flip_8x8_1if.log"):
    add(f"parent/budget-model/{f}", R / "flip" / f)
for f in ("head.log", "rc-head", "test_ctrl_memory.log", "images-vs-round1.txt"):
    add(f"parent/ledger/{f}", R / "ledger" / f)
# Tools.
for f in ("lwsrp_gates.sh", "harness_grade.py", "make_manifest.py"):
    add(f"tools/{f}", R / "tools" / f)
for f in ("pack_receipts.py", "own_arms.py", "la_window.py", "lwsrp_cov.py"):
    add(f"tools/{f}", Path("<scratch>/tools") / f)
add("tools/env.sh", "<scratch>/env.sh")
add("tools/penv.sh", "<scratch>/penv.sh")
Path(sys.argv[1]).write_text("# dest\tsource\n" + "\n".join(rows) + "\n")
print(f"{sum(1 for r in rows if not r.startswith('#'))} entries; missing: "
      + ", ".join(r.split('\t')[0][11:] for r in rows if r.startswith('#')))
