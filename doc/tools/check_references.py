# SPDX-License-Identifier: Apache-2.0
"""Find unlinked references in prose, including inline code."""

import argparse
import re
import sys

sys.dont_write_bytecode = True
from common import ROOT, pages, plain, prose_units, syntax_exceptions

PATTERNS = {
    "standard": (
        r"\b(?:IEEE|ISO(?:/IEC)?|IEC|SPDX|POSIX)\b|\b802\.1[A-Za-z0-9.-]+"
        r"|\bC(?:89|90|95|99|11|17|18|23|2x|2y)\b"
        r"|\bC\+\+(?:98|03|11|14|17|20|23|26)\b"
    ),
    "clause": r"(?:\bclauses?\s+|§\s*)\d+(?:\.\d+)*",
    "table": r"\bTable\s+\d+-\d+",
    "issue": r"\b(?:issue|PR|pull request)\s*#?\d+|(?<!\w)#\d+",
    "file": r"\b[\w./-]+\.(?:md|c|h|py|sh|yml|yaml|ini|drawio|svg|feature|zephyr)\b|\bCMakeLists\.txt\b|\b(?:LICENSE|NOTICE)\b",
    "function": r"\b[a-zA-Z_]\w*\([^\n)]*\)|\b(?:mrp|mrpdu|mvrp|mmrp|msrp|shlan)_[a-zA-Z0-9_]+\b",
    "tool": r"\b(?:CMake|ctest|cgreen|behave|Mermaid|mermaid-cli|mmdc|Zephyr|Python|GCC|GitHub)\b",
    "URL": r"https?://\S+",
}


def references(text):
    text = plain(text, keep_labels=False)
    for kind, pattern in PATTERNS.items():
        flags = re.IGNORECASE if kind in ("clause", "issue", "table") else 0
        for match in re.finditer(pattern, text, flags):
            yield kind, match[0]


def self_test():
    """Exercise the same prose path as the checker without writing fixtures."""
    cases = []
    standards = (
        "C89", "C90", "C95", "C99", "C11", "C17", "C18", "C23", "C2x", "C2y",
        "C++98", "C++03", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26",
        "IEEE", "802.1Q-2018", "ISO/IEC 9899:2011", "IEC 61508", "POSIX", "SPDX",
    )
    for name in standards:
        cases.extend([
            (f"Use {name}.", "standard"),
            (f"Use `{name}`.", "standard"),
            (f"Use [{name}](https://example.org/reference).", None),
        ])
    cases.extend([
        ("Use Kconfig.zephyr.", "file"),
        ("Use `Kconfig.zephyr`.", "file"),
        ("Use [Kconfig.zephyr](../../Kconfig.zephyr).", None),
        ("The AC11 and C110 identifiers are ordinary prose.", None),
        ("The C11_mode identifier is ordinary prose.", None),
        ("Use [C11](https://www.iso.org/standard/57853.html) and C23.", "standard"),
        ("Use [a compiler](https://example.org/C11).", None),
    ])
    failures = 0
    for text, expected in cases:
        found = list(references(text))
        passed = (not found) if expected is None else len(found) == 1 and found[0][0] == expected
        if not passed:
            failures += 1
            print(f"FAIL self-test: {text!r}: expected {expected!r}; found {found!r}")
    print(f"Reference self-test: {len(cases)} cases; failures: {failures}")
    return int(failures != 0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--self-test", action="store_true", help="check detection and link exclusion")
    if parser.parse_args().self_test:
        return self_test()
    errors = 0
    for path in pages():
        for exception in syntax_exceptions(path):
            print(f"SYNTAX {exception}")
        for number, text in prose_units(path):
            for kind, reference in references(text):
                errors += 1
                print(f"FAIL {path.relative_to(ROOT)}:{number}: unlinked {kind}: {reference}")
    print(f"Unlinked references: {errors}; prose exceptions: 0")
    return int(errors != 0)


if __name__ == "__main__":
    raise SystemExit(main())
