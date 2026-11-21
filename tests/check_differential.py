# SPDX-License-Identifier: Apache-2.0
"""Show that the checkout behaves exactly as a base revision, trace for trace.

Each driver under tests/differential/ prints one random life of a module as
a trace: every call, its result, every callback with its arguments and every
transmitted byte. Each is built twice in a new scratch directory, against the
base revision's sources and against the checkout's, and run on the same seeds.
The two traces must be byte-identical for every seed, in every configuration
the checkout is built in. Then each planted defect of MUTANTS is applied to a
copy of the checkout's sources, built with the scale switches, and some seed's
trace must differ from the base's: a defect no trace can see would make the
comparison an empty proof.
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

#: Each driver, the library sources it links under src/, and its steps a seed.
PROGRAMS = {
    "timer": ("tests/differential/timer_trace.c", ["ports/timer.c"], 20000),
    "mad": ("tests/differential/mad_trace.c", ["core/mrp_mad.c", "core/mrp_pdu.c", "ports/timer.c",
                                               "modules/msrp.c", "modules/mvrp.c", "modules/mmrp.c"], 3000),
}

#: The timer wheel, the lookup buckets and the merged build, as CMake's LWSRP_SCALE selects them.
SCALE = ["-DLWSRP_TIMER_SLOTS=64u", "-DLWSRP_ATTR_BUCKETS=16u", "-DLWSRP_TX_MERGE=1"]
#: The checkout's builds: the defaults (the list walk, the scans and the swapping build); the scale switches;
#: with them a four-slot wheel started just short of the tick counter's wrap, so whole turns and the wrap both
#: show; and one lookup bucket (every instance in one, as the list was) and 256.
def scale(*overrides):
    """SCALE with each override replacing the definition of its macro."""
    names = {o.split("=")[0] for o in overrides}
    return [d for d in SCALE if d.split("=")[0] not in names] + list(overrides)


CONFIGS = {
    "default": [],
    "scale": SCALE,
    "scale-slots4-wrap": scale("-DLWSRP_TIMER_SLOTS=4u", "-DLWSRP_TIMER_EPOCH=0xFFFFFF00u"),
    "scale-buckets1": scale("-DLWSRP_ATTR_BUCKETS=1u"),
    "scale-buckets256": scale("-DLWSRP_ATTR_BUCKETS=256u"),
}

TIMER = "ports/timer.c"
MAD = "core/mrp_mad.c"

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
    # The lookup index: each bucket in the list's order, every instance in its key's bucket.
    ("index-bucket-tail", "mad", MAD,
     "    a->key_next   = *bucket_of(ps, a->key);\n    ps->by_key[a->key % LWSRP_ATTR_BUCKETS] = a;",
     "    struct mrp_attr_inst **end = &ps->by_key[a->key % LWSRP_ATTR_BUCKETS];\n"
     "    while (*end) { end = &(*end)->key_next; }\n    a->key_next = NULL;\n    *end = a;"),
    ("index-reclaim-head", "mad", MAD, "            while (*in != a) {", "            while (false) {"),
    ("index-replacement-bucket", "mad", MAD,
     "for (struct mrp_attr_inst *old = *bucket_of(rc->ps, ai->key); old; old = old->key_next) {",
     "for (struct mrp_attr_inst *old = *bucket_of(rc->ps, (uint8_t)(ai->key + 1u)); old; old = old->key_next) {"),
    ("index-registered-bucket", "mad", MAD,
     "for (const struct mrp_attr_inst *a = *bucket_of(ps, key); a; a = a->key_next) {",
     "for (const struct mrp_attr_inst *a = *bucket_of(ps, (uint8_t)(key + 1u)); a; a = a->key_next) {"),
    ("index-lookup-bucket", "mad", MAD,
     "    for (struct mrp_attr_inst *a = *bucket_of(ps, key); a; a = a->key_next) {\n        if (a->key == key && a->attr_type == type",
     "    for (struct mrp_attr_inst *a = *bucket_of(ps, (uint8_t)(key ^ 1u)); a; a = a->key_next) {\n        if (a->key == key && a->attr_type == type"),
    # The build's order: ascending FirstValue, equal values in the list's order.
    ("sort-merge-ties", "mad", MAD, "struct mrp_attr_inst **from = tx_after(a, b, len) ? &b : &a;",
     "struct mrp_attr_inst **from = tx_after(b, a, len) ? &a : &b;"),
    ("sort-run-reversal", "mad", MAD, "        if (list && tx_after(run, list, len)) {\n            while (list && tx_after(run, list, len)) {",
     "        if (list && !tx_after(list, run, len)) {\n            while (list && !tx_after(list, run, len)) {"),
    ("sort-final-merge", "mad", MAD, "sorted = sorted ? tx_merge(pending[k], sorted, len) : pending[k];",
     "sorted = sorted ? tx_merge(sorted, pending[k], len) : pending[k];"),
    ("sort-reencode", "mad", MAD, "        if (a->tx_key != v + 2) {", "        if (false) {"),
    ("sort-failed-prefix", "mad", MAD,
     "        if (!tx_vector(ops, a, e->tx, type, len, subtype, v)) {\n            if (!ordered) {\n"
     "                tx_order(ops, event, type, chosen, first, size);\n            }",
     "        if (!tx_vector(ops, a, e->tx, type, len, subtype, v)) {"),
    ("sort-ordered-check", "mad", MAD, "if (ordered && v != first && memcmp(v - size + 2, v + 2, len) > 0) {",
     "if (ordered && v != first && memcmp(first + 2, v + 2, len) > 0) {"),
    ("sort-direction", "mad", MAD, "return memcmp(a->tx_key, b->tx_key, len) > 0;", "return memcmp(a->tx_key, b->tx_key, len) < 0;"),
]


def run(command, log, cwd=None, timeout=600):
    result = subprocess.run(command, cwd=cwd, capture_output=True, text=True, timeout=timeout)
    log.write_text(" ".join(map(str, command)) + "\n" + result.stdout + result.stderr)
    return result.returncode


def build(work, label, src, program, extra, milan):
    driver, sources, _ = PROGRAMS[program]
    exe = work / f"{program}-{label}"
    # A base revision before the attribute key builds the driver without it.
    keyed = "attr_key" in (src / "include/shish_lan/mrp.h").read_text()
    extra = [*extra, *(["-DTRACE_ATTR_KEY"] if keyed else []), f"-DLWSRP_MILAN={int(milan == 'ON')}"]
    rc = run(["cc", *FLAGS, *extra, f"-I{src}", f"-I{src / 'include'}", "-o", str(exe), str(ROOT / driver),
              *[str(src / s) for s in sources]], work / f"build-{program}-{label}.log")
    return exe if rc == 0 else None


def trace(exe, seed, steps):
    """A run's status and trace; a run that does not end is a failed run (a corrupted list can loop)."""
    try:
        result = subprocess.run([str(exe), str(seed), str(steps)], capture_output=True, timeout=60)
    except subprocess.TimeoutExpired as late:
        return -9, late.stdout or b""
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
    parser.add_argument("--steps", type=int, help="steps a seed for every driver (default: each driver's own)")
    parser.add_argument("--milan", choices=["OFF", "ON"], default="OFF")
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
    problems, rows, expected_of, references = [], [], {}, {}
    for program, (_, _, default_steps) in PROGRAMS.items():
        steps = args.steps or default_steps
        reference = build(work, "base", base / "src", program, [], args.milan)
        if not reference:
            problems.append(f"{program}: the base build fails")
            continue
        references[program] = reference
        expected, lines = {}, 0
        for seed in range(1, args.seeds + 1):
            rc, out = trace(reference, seed, steps)
            if rc:
                problems.append(f"{program} base seed {seed}: rc={rc}")
            expected[seed] = hashlib.sha256(out).digest()
            lines += out.count(b"\n")
        expected_of[program] = expected
        for config, extra in CONFIGS.items():
            candidate = build(work, config, ROOT / "src", program, extra, args.milan)
            if not candidate:
                problems.append(f"{program} {config}: the checkout's build fails")
                continue
            same = 0
            digest = hashlib.sha256()
            for seed in range(1, args.seeds + 1):
                rc, out = trace(candidate, seed, steps)
                mine = hashlib.sha256(out).digest()
                digest.update(mine)
                if rc == 0 and mine == expected[seed]:
                    same += 1
                else:
                    problems.append(f"{program} {config} seed {seed}: rc={rc}, "
                                    f"{first_difference(trace(reference, seed, steps)[1], out)}")
            rows.append({"program": program, "config": config, "seeds": args.seeds, "steps": steps,
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
            exe = build(work, f"mutant-{name}", tree / "src", program, SCALE, args.milan)
            if not exe:
                problems.append(f"mutant {name}: the build fails, which is no behavioural kill")
                continue
            seen = None
            for seed in range(1, args.seeds + 1):
                rc, out = trace(exe, seed, args.steps or PROGRAMS[program][2])
                if rc != 0 or hashlib.sha256(out).digest() != expected_of.get(program, {}).get(seed):
                    seen = seed
                    break
            print(f"{'KILLED' if seen else 'SURVIVED'} {name}" + (f" at seed {seen}" if seen else ""), flush=True)
            if seen:
                killed.append(name)
            else:
                problems.append(f"mutant {name} survived {args.seeds} seeds")
            shutil.rmtree(tree)
    (work / "differential.json").write_text(json.dumps({"base": args.base, "milan": args.milan, "rows": rows, "killed": killed,
                                                        "problems": problems}, indent=2) + "\n")
    print(f"Drivers: {len(PROGRAMS)}; builds: {len(rows)}; mutants killed: {len(killed)} of "
          f"{0 if args.no_mutants else len(MUTANTS)}; problems: {len(problems)}")
    for problem in problems:
        print(f"FAIL {problem}")
    return int(bool(problems) or not rows)


if __name__ == "__main__":
    sys.exit(main())
