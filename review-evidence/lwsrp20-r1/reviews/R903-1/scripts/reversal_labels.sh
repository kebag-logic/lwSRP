#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# reversal_labels.sh <ON|OFF> <tag> <label> [<label> ...]
# As reversal_shards.sh (same two timeout changes for a heavily shared host),
# but runs exactly the named CASES labels. Mutations, REQUIRED_FAILURES and
# the kill rule are unchanged.
set -u
m=$1; tag=$2; shift 2
W="$PKT/scratch"
src="$W/revl-src-$m-$tag"
rm -rf "$src" "$W/revl-work-$m-$tag"; mkdir -p "$src"
git -C "$SRC" archive c035764f2d6105fd9598b138112ba01eaa006958 | tar -x -C "$src"
f="$src/tests/check_reversals.py"
python3 - "$f" "$@" <<'EOF'
import sys
p, labels = sys.argv[1], sys.argv[2:]
t = open(p).read()
a = '"--output-on-failure", "--timeout", "10"]'
b = 'capture_output=True, text=True, timeout=120)'
c = '    for label, name, old, new, check in CASES:\n'
assert t.count(a) == 1 and t.count(b) == 1 and t.count(c) == 1
t = t.replace(a, '"--output-on-failure", "--timeout", "1500"]')
t = t.replace(b, 'capture_output=True, text=True, timeout=3600)')
t = t.replace(c, f'    for label, name, old, new, check in [x for x in CASES if x[0] in {labels!r}]:\n')
open(p, "w").write(t)
EOF
diff <(git -C "$SRC" show c035764f2d6105fd9598b138112ba01eaa006958:tests/check_reversals.py) "$f"
cd "$src" && python3 tests/check_reversals.py --work-dir "$W/revl-work-$m-$tag" --prefix "$CGREEN_PREFIX" --milan "$m"
