# SPDX-License-Identifier: Apache-2.0
"""Find unlinked references in prose, including inline code."""

import re
import sys

sys.dont_write_bytecode = True
from common import ROOT, pages, plain, prose_units, syntax_exceptions

PATTERNS = {
    "standard": r"\bIEEE\b|\b802\.1[A-Za-z0-9.-]+",
    "clause": r"(?:\bclauses?\s+|§\s*)\d+(?:\.\d+)*",
    "table": r"\bTable\s+\d+-\d+",
    "issue": r"\b(?:issue|PR|pull request)\s*#?\d+|(?<!\w)#\d+",
    "file": r"\b[\w./-]+\.(?:md|c|h|py|sh|yml|yaml|ini|drawio|svg|feature)\b|\bCMakeLists\.txt\b|\b(?:LICENSE|NOTICE)\b",
    "function": r"\b[a-zA-Z_]\w*\([^\n)]*\)|\b(?:mrp|mrpdu|mvrp|mmrp|msrp|shlan)_[a-zA-Z0-9_]+\b",
    "tool": r"\b(?:CMake|ctest|cgreen|behave|Mermaid|mermaid-cli|mmdc|Zephyr|Python|GCC|GitHub)\b",
    "URL": r"https?://\S+",
}


def main():
    errors = 0
    for path in pages():
        for exception in syntax_exceptions(path):
            print(f"SYNTAX {exception}")
        for number, text in prose_units(path):
            text = plain(text, keep_labels=False)
            for kind, pattern in PATTERNS.items():
                for match in re.finditer(pattern, text, re.IGNORECASE if kind in ("clause", "issue", "table") else 0):
                    errors += 1
                    print(f"FAIL {path.relative_to(ROOT)}:{number}: unlinked {kind}: {match[0]}")
    print(f"Unlinked references: {errors}; prose exceptions: 0")
    return int(errors != 0)


if __name__ == "__main__":
    raise SystemExit(main())
