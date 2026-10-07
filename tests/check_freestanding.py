# SPDX-License-Identifier: Apache-2.0
"""Check strict core compilation and reject hosted allocation/error headers."""

import os
from pathlib import Path
import shlex
import subprocess


ROOT = Path(__file__).resolve().parents[1]
SOURCES = [
    "src/core/mrp_mad.c", "src/core/mrp_pdu.c", "src/ports/timer.c",
    "src/modules/mmrp.c", "src/modules/mvrp.c", "src/modules/msrp.c",
]


def main():
    compiler = shlex.split(os.environ.get("CC", "cc"))
    flags = ["-std=c11", "-ffreestanding", "-Wall", "-Wextra", "-Wpedantic",
             "-Werror", "-Isrc/include", "-Isrc"]
    failures = 0
    for source in SOURCES:
        command = compiler + flags + ["-fsyntax-only", source]
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=60)
        print(f"COMMAND {shlex.join(command)}; rc={result.returncode}")
        print(result.stdout + result.stderr, end="")
        failures += result.returncode != 0
        command = compiler + flags + ["-M", source]
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=60)
        print(f"COMMAND {shlex.join(command)}; rc={result.returncode}")
        failures += result.returncode != 0
        forbidden = {"stdlib.h", "errno.h", "stdio.h"}
        found = sorted({Path(item).name for item in result.stdout.split()} & forbidden)
        if found:
            print(f"FAIL {source}: hosted headers {', '.join(found)}")
            failures += 1
    print(f"Freestanding sources: {len(SOURCES)}; failures: {failures}")
    return int(failures != 0)


if __name__ == "__main__":
    raise SystemExit(main())
