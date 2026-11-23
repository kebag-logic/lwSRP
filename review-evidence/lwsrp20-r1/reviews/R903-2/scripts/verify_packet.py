# SPDX-License-Identifier: Apache-2.0
"""Verify an extracted author packet against its MANIFEST.json and receipts/INDEX.md.

Usage: python3 -I verify_packet.py <review-evidence/lwsrp20-r1 dir> <subdir, e.g. author-r2>
"""
import hashlib, json, re, sys
from pathlib import Path

root, sub = Path(sys.argv[1]), sys.argv[2]
man = json.loads((root / "MANIFEST.json").read_text())
entries = {e["file"]: e for e in man if e["file"].startswith(sub + "/")}
files = {str(p.relative_to(root)) for p in (root / sub).rglob("*") if p.is_file()}
bad = 0
for f in sorted(files | set(entries)):
    if f not in entries:
        print("UNLISTED", f); bad += 1; continue
    if f not in files:
        print("MISSING", f); bad += 1; continue
    h = hashlib.sha256((root / f).read_bytes()).hexdigest()
    if h != entries[f]["published_sha256"]:
        print("HASH", f); bad += 1
print(f"manifest: {len(entries)} entries, {len(files)} files, {bad} problems")
idx = (root / sub / "receipts/INDEX.md").read_text()
rows = re.findall(r"^\| `([^`]+)` \| ([\d,]+) \| `([0-9a-f]{16})` \|$", idx, re.M)
ibad = 0
for path, size, pre in rows:
    p = root / sub / "receipts" / path
    if not p.exists():
        print("INDEX-MISSING", path); ibad += 1; continue
    b = p.read_bytes()
    if hashlib.sha256(b).hexdigest()[:16] != pre or len(b) != int(size.replace(",", "")):
        print("INDEX-MISMATCH", path, len(b), size); ibad += 1
print(f"index: {len(rows)} rows, {ibad} problems")
sys.exit(int(bool(bad or ibad)))
