#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# coverage.sh <rev> <tag>: gcov line and branch coverage of src/core/mrp_mad.c
# and sla_registrars, OFF and ON profiles run on one instrumented tree each.
set -u
rev=$1; tag=$2
W="$PKT/scratch"
export LD_LIBRARY_PATH="$CGREEN_PREFIX/lib"
for m in OFF ON; do
    t="$W/cov-$tag-$m"; b="$W/covb-$tag-$m"
    rm -rf "$t" "$b"; mkdir -p "$t"
    git -C "$SRC" archive "$rev" | tar -x -C "$t"
    cmake -S "$t" -B "$b" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN=$m -DCMAKE_PREFIX_PATH="$CGREEN_PREFIX" \
        -DCMAKE_C_FLAGS="--coverage -O0" -DCMAKE_EXE_LINKER_FLAGS=--coverage -DCMAKE_SHARED_LINKER_FLAGS=--coverage >/dev/null || exit 10
    cmake --build "$b" --parallel 4 >/dev/null || exit 11
    "$b/unit_tests" > "$b/unit.log" 2>&1; echo "UNIT_$m=$? $(tail -n 1 "$b/unit.log")"
    obj=$(find "$b" -path '*unit_tests.dir*' -name 'mrp_mad.c.gcda' | head -n 1)
    (cd "$(dirname "$obj")" && gcov -b -c -f -o . "$obj" > "$b/gcov.txt" 2>&1)
    awk '/^File .*mrp_mad.c/{f=1} f&&/Lines executed|Branches executed|Taken at least once/{print "'$m' "$0} f&&/^$/{f=0}' "$b/gcov.txt"
    awk '/^Function .sla_registrars./{f=1} f&&/Lines executed|Taken at least once/{print "'$m' sla_registrars "$0} f&&/^$/{f=0}' "$b/gcov.txt"
done
