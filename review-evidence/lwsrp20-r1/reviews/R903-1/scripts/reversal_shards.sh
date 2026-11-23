#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# reversal_shards.sh <ON|OFF> <k> <N>
# Runs the head's tests/check_reversals.py from a scratch export with two
# changes only, for a heavily shared host: the per-check ctest timeout
# (10 s -> 1500 s) and the per-command subprocess timeout (120 s -> 3600 s),
# and runs only the cases whose index i satisfies i % N == k.
# Case bodies, mutations, REQUIRED_FAILURES and the kill rule are unchanged.
set -u
m=$1; k=$2; n=$3
W="$PKT/scratch"
src="$W/revs-src-$m-$k"
rm -rf "$src" "$W/revs-work-$m-$k"; mkdir -p "$src"
git -C "$SRC" archive c035764f2d6105fd9598b138112ba01eaa006958 | tar -x -C "$src"
f="$src/tests/check_reversals.py"
python3 - "$f" "$k" "$n" <<'EOF'
import sys
p, k, n = sys.argv[1], int(sys.argv[2]), int(sys.argv[3])
t = open(p).read()
a = '"--output-on-failure", "--timeout", "10"]'
b = 'capture_output=True, text=True, timeout=120)'
c = '    for label, name, old, new, check in CASES:\n'
assert t.count(a) == 1 and t.count(b) == 1 and t.count(c) == 1
t = t.replace(a, '"--output-on-failure", "--timeout", "1500"]')
t = t.replace(b, 'capture_output=True, text=True, timeout=3600)')
t = t.replace(c, f'    for label, name, old, new, check in [x for i, x in enumerate(CASES) if i % {n} == {k}]:\n')
open(p, "w").write(t)
EOF
diff <(git -C "$SRC" show c035764f2d6105fd9598b138112ba01eaa006958:tests/check_reversals.py) "$f"
cd "$src" && python3 tests/check_reversals.py --work-dir "$W/revs-work-$m-$k" --prefix "$CGREEN_PREFIX" --milan "$m"
