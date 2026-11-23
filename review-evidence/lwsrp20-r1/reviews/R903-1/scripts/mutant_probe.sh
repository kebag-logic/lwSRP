#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# mutant_probe.sh <label> <ON|OFF> <old-file> <new-file>
# Exports the head into scratch, replaces the exact text of <old-file> with
# <new-file> in src/core/mrp_mad.c (must occur once), builds and runs the
# unit target, and lists the failing tests. The checkout is never touched.
set -u
label=$1; m=$2; old=$3; new=$4
W="$PKT/scratch"; t="$W/mut-$label"; b="$W/mutb-$label"
rm -rf "$t" "$b"; mkdir -p "$t"
git -C "$SRC" archive c035764f2d6105fd9598b138112ba01eaa006958 | tar -x -C "$t"
python3 - "$t/src/core/mrp_mad.c" "$old" "$new" <<'EOF'
import sys
p, o, n = sys.argv[1:]
t = open(p).read(); old = open(o).read(); new = open(n).read()
assert t.count(old) == 1, "mutation target must occur once"
open(p, "w").write(t.replace(old, new))
EOF
[ $? -eq 0 ] || exit 30
diff <(git -C "$SRC" show c035764f2d6105fd9598b138112ba01eaa006958:src/core/mrp_mad.c) "$t/src/core/mrp_mad.c"
export LD_LIBRARY_PATH="$CGREEN_PREFIX/lib"
cmake -S "$t" -B "$b" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN=$m -DCMAKE_PREFIX_PATH="$CGREEN_PREFIX" >/dev/null || exit 10
cmake --build "$b" --parallel 4 >/dev/null || exit 11
"$b/unit_tests" > "$b/unit.log" 2>&1; rc=$?
echo "UNIT_RC=$rc $(tail -n 1 "$b/unit.log")"
grep -oE '(Failure|Exception): [a-z_]+ -> [a-z_]+' "$b/unit.log" | sort | uniq -c
exit 0
