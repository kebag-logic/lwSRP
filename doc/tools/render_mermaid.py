# SPDX-License-Identifier: Apache-2.0
"""Render every graph outside the checkout and reject graphs over 15 nodes."""

import argparse
import re
import shlex
import subprocess
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

sys.dont_write_bytecode = True
from common import ROOT, pages, sections


def nodes(source):
    identifiers = set()
    for line in source.splitlines()[1:]:
        line = line.strip()
        if not line or line.startswith("%%"):
            continue
        if source.startswith("sequenceDiagram"):
            match = re.match(r"participant\s+(\w+)", line)
            if match:
                identifiers.add(match[1])
        elif source.startswith("stateDiagram"):
            match = re.match(r"(\w+|\[\*\])\s*-->\s*(\w+|\[\*\])", line)
            if match:
                identifiers.update(value for value in match.groups() if value != "[*]")
        else:
            identifiers.update(re.findall(r"(\w+)\[", line))
    return len(identifiers)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--puppeteer-config", type=Path)
    args = parser.parse_args()
    output = args.output.resolve()
    if output.is_relative_to(ROOT):
        parser.error("Render output must be outside the checkout")
    output.mkdir(parents=True, exist_ok=True)
    failures = 0
    count = 0
    for path in pages():
        for kind, line, source in sections(path):
            if kind != "mermaid":
                continue
            count += 1
            label = f"{path.relative_to(ROOT)}:{line}"
            size = nodes(source)
            if not 0 < size <= 15:
                print(f"FAIL {label}: {size} nodes; expected 1 through 15")
                failures += 1
                continue
            stem = f"{path.relative_to(ROOT).as_posix().replace('/', '-')}-{line}"
            input_path = output / f"{stem}.mmd"
            svg_path = output / f"{stem}.svg"
            input_path.write_text(source + "\n", encoding="utf-8")
            command = ["mmdc", "-i", str(input_path), "-o", str(svg_path), "-b", "white"]
            if args.puppeteer_config:
                command.extend(["-p", str(args.puppeteer_config.resolve())])
            try:
                result = subprocess.run(command, timeout=60, capture_output=True, text=True)
                rc = result.returncode
                print(f"COMMAND {shlex.join(command)}; rc={rc}")
                if rc != 0:
                    print(result.stderr.strip() or result.stdout.strip())
                else:
                    root = ET.parse(svg_path).getroot()
                    if not root.tag.endswith("svg"):
                        rc = 1
            except (OSError, subprocess.TimeoutExpired, ET.ParseError) as error:
                rc = 1
                print(f"COMMAND {shlex.join(command)}; rc={rc}; {error}")
            print(f"{'PASS' if rc == 0 else 'FAIL'} {label}: {size} nodes; render rc={rc}", flush=True)
            failures += rc != 0
    print(f"Graphs: {count}; failures: {failures}")
    return int(failures != 0 or count == 0)


if __name__ == "__main__":
    raise SystemExit(main())
