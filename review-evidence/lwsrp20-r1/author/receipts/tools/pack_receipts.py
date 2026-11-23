#!/usr/bin/env python3
"""Pack receipts: pack_receipts.py MANIFEST OUT_DIR.

MANIFEST lines: `<dest relative path>\t<source path>` (a directory source copies its files, not recursively unless
the line ends with `\t**`). Text files get the lane's paths replaced by placeholders; files over 256 KiB are gzipped.
Every packed file's content must satisfy privacy.scrub_redact(b) == b (checked on the decompressed bytes), or the
run fails naming it. INDEX.md lists every file with its size and sha256 prefix.
"""
import gzip
import hashlib
import importlib.util
import sys
from pathlib import Path

MGMT = Path("<management>/2026-09-23")
SUBS = [
    (b"<scratch-home>", b"<scratch-home>"),
    (b"<scratch>", b"<scratch>"),
    (b"<parent>", b"<parent>"),
    (b"<lane>", b"<lane>"),
    (b"<rv32-sdk>", b"<rv32-sdk>"),
    (b"<management>", b"<management>"),
    (b"<litex-tree>", b"<litex-tree>"),
    (b"$HOME", b"$HOME"),
    (b"<tools>", b"<tools>"),
]
LIMIT = 256 * 1024


def load_privacy():
    spec = importlib.util.spec_from_file_location("privacy", MGMT / "privacy.py")
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def main():
    manifest, out = Path(sys.argv[1]), Path(sys.argv[2])
    privacy = load_privacy()
    out.mkdir(parents=True, exist_ok=True)
    rows, bad = [], []
    for line in manifest.read_text().splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        parts = line.split("\t")
        dest, src = parts[0], Path(parts[1])
        recursive = len(parts) > 2 and parts[2] == "**"
        files = [src] if src.is_file() else sorted(p for p in (src.rglob("*") if recursive else src.glob("*"))
                                                    if p.is_file())
        for f in files:
            rel = Path(dest) if src.is_file() else Path(dest) / f.relative_to(src)
            data = f.read_bytes()
            if f.suffix == ".gz":
                data = gzip.decompress(data)
                rel = rel.with_suffix("")
            for old, new in SUBS:
                data = data.replace(old, new)
            if privacy.scrub_redact(data) != data:
                bad.append(str(rel))
                continue
            target = out / rel
            target.parent.mkdir(parents=True, exist_ok=True)
            if len(data) > LIMIT:
                target = target.with_name(target.name + ".gz")
                target.write_bytes(gzip.compress(data, 9, mtime=0))
            else:
                target.write_bytes(data)
            rows.append((str(target.relative_to(out)), target.stat().st_size,
                         hashlib.sha256(target.read_bytes()).hexdigest()[:16]))
    if bad:
        print("NOT PACKED (scrub_redact would change them):")
        for b in bad:
            print("  " + b)
    return rows, bad


if __name__ == "__main__":
    rows, bad = main()
    table = ["| File | Bytes | sha256 (16) |", "|---|---:|---|"]
    table += [f"| `{path}` | {size:,} | `{digest}` |" for path, size, digest in sorted(rows)]
    (Path(sys.argv[2]) / "FILES.md").write_text("\n".join(table) + "\n")
    print(f"packed {len(rows)} files; refused {len(bad)}")
    sys.exit(1 if bad else 0)
