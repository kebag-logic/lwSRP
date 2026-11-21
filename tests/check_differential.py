# SPDX-License-Identifier: Apache-2.0
"""Show that the checkout behaves exactly as a base revision, trace for trace.

Each driver under tests/differential/ prints one random life of a module as
a trace: every call, its result, every callback with its arguments and every
transmitted byte. Each is built twice in a new scratch directory, against the
base revision's sources and against the checkout's, and run on the same seeds.
The two traces must be byte-identical for every seed, in every configuration
the checkout is built in. Then each planted defect of MUTANTS is applied to a
copy of the checkout's sources, and some seed's trace must differ from the
base's: a defect no trace can see would make the comparison an empty proof.
"""

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
#: The revision whose behaviour the lookup, sort and timer changes keep.
BASE = "08ee86e812a0eb5e1dc6cd61b494d8baf3491348"
FLAGS = ["-O2", "-std=c11", "-Wall", "-Wextra", "-Werror"]

#: Each driver and the library sources it links, under src/.
PROGRAMS = {
    "timer": ("tests/differential/timer_trace.c", ["ports/timer.c"]),
}

#: The checkout's builds: the defaults, then a four-slot wheel started just
#: short of the tick counter's wrap, so whole turns and the wrap both show.
CONFIGS = {
    "default": [],
    "slots4-wrap": ["-DLWSRP_TIMER_SLOTS=4u", "-DLWSRP_TIMER_EPOCH=0xFFFFFF00u"],
}

TIMER = "ports/timer.c"

#: Each defect reverses one rule the traces must keep: (name, program, file
#: under src/, original text, planted text).
MUTANTS = [
    ("timer-ahead-tick", "timer", TIMER, "const bool ahead = t->order < g_cursor;",
     "const bool ahead = false;"),
    ("timer-self-ahead", "timer", TIMER, "const bool ahead = t->order < g_cursor;",
     "const bool ahead = t->order <= g_cursor;"),
    ("timer-due-order", "timer", TIMER, "a->order > b->order ? &a : &b", "a->order < b->order ? &a : &b"),
    ("timer-due-insert", "timer", TIMER, "while (*at && (*at)->order > t->order) {",
     "while (*at && (*at)->order < t->order) {"),
    ("timer-rising-run", "timer", TIMER, "list->link = run;\n                run = list;",
     "list->link = run->link;\n                run->link = list;"),
    ("timer-slot-turn", "timer", TIMER, "if (t->cs != g_now) {", "if (false) {"),
    ("timer-zero-arm", "timer", TIMER,
     "    if (t->at) {\n        unlink_timer(t);\n    }\n    if (centiseconds == 0u || t->order == 0u) {\n        return;\n    }",
     "    if (centiseconds == 0u || t->order == 0u) {\n        return;\n    }\n    if (t->at) {\n        unlink_timer(t);\n    }"),
    ("timer-unregistered-arm", "timer", TIMER, "if (centiseconds == 0u || t->order == 0u) {",
     "if (centiseconds == 0u) {"),
    ("timer-removed-armed", "timer", TIMER, "    if (t->at) {\n        unlink_timer(t);\n    }\n    t->cs = 0;",
     "    t->cs = 0;"),
    ("timer-removed-registered", "timer", TIMER, "    t->link = NULL;\n    t->order = 0;\n}", "    t->link = NULL;\n}"),
]


def run(command, log, cwd=None, timeout=600):
    result = subprocess.run(command, cwd=cwd, capture_output=True, text=True, timeout=timeout)
    log.write_text(" ".join(map(str, command)) + "\n" + result.stdout + result.stderr)
    return result.returncode


def build(work, label, src, program, extra):
    driver, sources = PROGRAMS[program]
    exe = work / f"{program}-{label}"
    rc = run(["cc", *FLAGS, *extra, f"-I{src}", f"-I{src / 'include'}", "-o", str(exe), str(ROOT / driver),
              *[str(src / s) for s in sources]], work / f"build-{program}-{label}.log")
    return exe if rc == 0 else None


def trace(exe, seed, steps):
    result = subprocess.run([str(exe), str(seed), str(steps)], capture_output=True, timeout=600)
    return result.returncode, result.stdout


def first_difference(a, b):
    for n, (x, y) in enumerate(zip(a.splitlines(), b.splitlines()), 1):
        if x != y:
            return f"line {n}: {x.decode(errors='replace')!r} / {y.decode(errors='replace')!r}"
    return f"lengths {len(a)} / {len(b)}"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work-dir", type=Path, required=True)
    parser.add_argument("--base", default=BASE, help="the revision whose behaviour is the reference")
    parser.add_argument("--seeds", type=int, default=200)
    parser.add_argument("--steps", type=int, default=20000)
    parser.add_argument("--no-mutants", action="store_true", help="compare only; plant nothing")
    args = parser.parse_args()
    work = args.work_dir.resolve()
    if work.is_relative_to(ROOT) or work.exists():
        parser.error("Use a new scratch directory outside the checkout")
    work.mkdir(parents=True)
    base = work / "base"
    base.mkdir()
    archive = work / "base.tar"
    if run(["git", "-C", str(ROOT), "archive", "-o", str(archive), args.base, "src"], work / "archive.log") or \
       run(["tar", "-xf", str(archive), "-C", str(base)], work / "extract.log"):
        print(f"FAIL the base revision {args.base} cannot be read")
        return 1
    problems, rows, expected_of = [], [], {}
    for program in PROGRAMS:
        reference = build(work, "base", base / "src", program, [])
        if not reference:
            problems.append(f"{program}: the base build fails")
            continue
        expected = {}
        for seed in range(1, args.seeds + 1):
            rc, out = trace(reference, seed, args.steps)
            if rc:
                problems.append(f"{program} base seed {seed}: rc={rc}")
            expected[seed] = out
        expected_of[program] = expected
        for config, extra in CONFIGS.items():
            candidate = build(work, config, ROOT / "src", program, extra)
            if not candidate:
                problems.append(f"{program} {config}: the checkout's build fails")
                continue
            same = 0
            digest = hashlib.sha256()
            for seed in range(1, args.seeds + 1):
                rc, out = trace(candidate, seed, args.steps)
                digest.update(out)
                if rc == 0 and out == expected[seed]:
                    same += 1
                else:
                    problems.append(f"{program} {config} seed {seed}: rc={rc}, "
                                    f"{first_difference(expected[seed], out)}")
            lines = sum(out.count(b"\n") for out in expected.values())
            rows.append({"program": program, "config": config, "seeds": args.seeds, "steps": args.steps,
                         "identical": same, "trace_lines": lines, "sha256": digest.hexdigest()})
    print("| Driver | Build | Seeds | Steps a seed | Trace lines | Identical | Traces' sha256 |")
    print("| --- | --- | --- | --- | --- | --- | --- |")
    for row in rows:
        print(f"| {row['program']} | {row['config']} | {row['seeds']} | {row['steps']} | {row['trace_lines']} | "
              f"{row['identical']} | {row['sha256'][:16]} |")
    killed = []
    if not args.no_mutants:
        for name, program, path, old, new in MUTANTS:
            tree = work / f"mutant-{name}"
            shutil.copytree(ROOT / "src", tree / "src")
            target = tree / "src" / path
            text = target.read_text()
            if old not in text:
                problems.append(f"mutant {name}: its target is missing")
                continue
            target.write_text(text.replace(old, new, 1))
            exe = build(work, f"mutant-{name}", tree / "src", program, [])
            if not exe:
                problems.append(f"mutant {name}: the build fails, which is no behavioural kill")
                continue
            seen = None
            for seed in range(1, args.seeds + 1):
                rc, out = trace(exe, seed, args.steps)
                if rc != 0 or out != expected_of.get(program, {}).get(seed):
                    seen = seed
                    break
            print(f"{'KILLED' if seen else 'SURVIVED'} {name}" + (f" at seed {seen}" if seen else ""), flush=True)
            if seen:
                killed.append(name)
            else:
                problems.append(f"mutant {name} survived {args.seeds} seeds")
            shutil.rmtree(tree)
    (work / "differential.json").write_text(json.dumps({"base": args.base, "rows": rows, "killed": killed,
                                                        "problems": problems}, indent=2) + "\n")
    print(f"Drivers: {len(PROGRAMS)}; builds: {len(rows)}; mutants killed: {len(killed)} of "
          f"{0 if args.no_mutants else len(MUTANTS)}; problems: {len(problems)}")
    for problem in problems:
        print(f"FAIL {problem}")
    return int(bool(problems) or not rows)


if __name__ == "__main__":
    sys.exit(main())
