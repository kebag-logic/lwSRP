# SPDX-License-Identifier: Apache-2.0
"""Check prose sentences, including wrapped paragraphs, against 25 words."""

import re
import sys

sys.dont_write_bytecode = True
from common import ROOT, pages, plain, prose_units, syntax_exceptions


def main():
    errors = 0
    checked = 0
    for path in pages():
        for exception in syntax_exceptions(path):
            print(f"SYNTAX {exception}")
        for number, text in prose_units(path):
            text = plain(text)
            for sentence in re.split(r"(?<=[.!?])\s+(?=[A-Z0-9])", text):
                words = re.findall(r"\S+", sentence)
                checked += 1
                if len(words) > 25:
                    errors += 1
                    print(f"FAIL {path.relative_to(ROOT)}:{number}: {len(words)} words: {sentence}")
    print(f"Sentences/fragments: {checked}; over limit: {errors}; prose exceptions: 0")
    return int(errors != 0)


if __name__ == "__main__":
    raise SystemExit(main())
