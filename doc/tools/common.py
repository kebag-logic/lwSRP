# SPDX-License-Identifier: Apache-2.0
"""Shared parsing for the repository's deliberately small Markdown subset."""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LINK = re.compile(r"!?\[([^\]\n]+)\]\(([^\s)]+)(?:\s+['\"][^\n]*?['\"])?\)")
FENCE = re.compile(r"^\s*(`{3,}|~{3,})(\w*)\s*$")


def pages(root=ROOT):
    return sorted(set(root.glob("*.md")) | set((root / "doc").rglob("*.md")))


def sections(path):
    """Yield prose lines and fenced blocks with their starting line numbers."""
    lines = path.read_text(encoding="utf-8").splitlines()
    fence = None
    block = []
    start = 0
    language = ""
    for number, line in enumerate(lines, 1):
        match = FENCE.match(line)
        if fence is None:
            if match:
                fence = match[1]
                language = match[2]
                start = number
                block = []
            else:
                yield "prose", number, line
        elif match and match[1][0] == fence[0] and len(match[1]) >= len(fence):
            yield language or "code", start, "\n".join(block)
            fence = None
        else:
            block.append(line)
    if fence is not None:
        raise ValueError(f"{path.relative_to(ROOT)}:{start}: unclosed fence")


def plain(text, keep_labels=True):
    text = LINK.sub(lambda m: m[1] if keep_labels else " ", text)
    text = re.sub(r"[`*]", "", text)
    return re.sub(r"(?<!\w)_+|_+(?!\w)", "", text)


def prose_units(path):
    """Join wrapped paragraphs; check list items and table cells separately."""
    paragraph = []
    start = 0
    for kind, number, line in sections(path):
        separate = kind != "prose" or not line.strip()
        separate = separate or bool(re.match(r"^\s*(?:#{1,6}\s|[-*+]\s|\d+\.\s|\|)", line))
        if separate and paragraph:
            yield start, " ".join(paragraph)
            paragraph = []
        if kind != "prose" or not line.strip() or line.startswith("<!--"):
            continue
        if line.lstrip().startswith("|"):
            for cell in line.strip().strip("|").split("|"):
                if not re.fullmatch(r"[\s:-]*", cell):
                    yield number, cell.strip()
        elif separate:
            yield number, re.sub(r"^\s*(?:#{1,6}\s+|[-*+]\s+|\d+\.\s+)", "", line)
        else:
            if not paragraph:
                start = number
            paragraph.append(line.strip())
    if paragraph:
        yield start, " ".join(paragraph)


def syntax_exceptions(path):
    for kind, number, _ in sections(path):
        if kind != "prose":
            yield f"{path.relative_to(ROOT)}:{number}: {kind} fence: literal machine syntax; nearby reference links require review"


def anchors(path):
    found = set()
    counts = {}
    for kind, _, line in sections(path):
        if kind != "prose":
            continue
        match = re.match(r"^#{1,6}\s+(.+?)\s*#*\s*$", line)
        if match:
            slug = re.sub(r"[^\w\- ]", "", plain(match[1]).lower()).replace(" ", "-")
            count = counts.get(slug, 0)
            counts[slug] = count + 1
            found.add(slug if count == 0 else f"{slug}-{count}")
    return found
