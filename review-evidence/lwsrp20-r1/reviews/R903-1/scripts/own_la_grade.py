#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Independent grade of the consumer's OWN-LA withdrawal lines.

Usage: own_la_grade.py <log> [<log> ...]   (plain or .gz)
For each log: withdrawals, offsets, inputs, withdrawals with no Lv, the
largest withdrawal-to-Lv latency, Lv later than 240 ms (Milan v1.2 Table 4.3
LeaveTime bound used by the ruling), and peer deregistration not at the Lv.
"""
import gzip
import re
import sys

LINE = re.compile(r"OWN-LA input=(\d+) offset_ms=(\d+) (.*)")


def fields(rest):
    return dict(kv.split("=", 1) for kv in rest.split())


def grade(path):
    opener = gzip.open if path.endswith(".gz") else open
    rows = []
    with opener(path, "rt") as f:
        for line in f:
            m = LINE.search(line)
            if m:
                rows.append((int(m[1]), int(m[2]), fields(m[3])))
    inputs = sorted({r[0] for r in rows})
    offsets = sorted({r[1] for r in rows})
    unsent, late, peer_mismatch, lat = 0, 0, 0, []
    for inp, off, f in rows:
        lv = f.get("lv_ms")
        if lv is None or lv.startswith("none"):
            unsent += 1
            continue
        d = int(lv) - int(f["withdrawn_ms"])
        lat.append(d)
        if d > 240:
            late += 1
        if f.get("peer_left_ms") != lv:
            peer_mismatch += 1
    print(f"{path.rsplit('/', 1)[-1]}: withdrawals={len(rows)} inputs={len(inputs)} "
          f"offsets={len(offsets)} [{offsets[0] if offsets else '-'}..{offsets[-1] if offsets else '-'}] "
          f"unsent={unsent} max_latency_ms={max(lat) if lat else '-'} over_240ms={late} "
          f"peer_not_at_lv={peer_mismatch}")
    return rows


if __name__ == "__main__":
    for p in sys.argv[1:]:
        grade(p)
