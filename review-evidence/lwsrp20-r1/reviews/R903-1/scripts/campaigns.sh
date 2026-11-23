#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# Independent review campaigns for lwSRP PR #21 (issue #20).
# Usage: campaigns.sh <campaign>   with PKT, SRC, CGREEN_PREFIX exported.
# Every tree it builds lives under $PKT/scratch; the checkout is only read
# (git archive), never modified.
set -u
HEAD_REV=c035764f2d6105fd9598b138112ba01eaa006958
BASE_REV=08ee86e812a0eb5e1dc6cd61b494d8baf3491348
W="$PKT/scratch"
export CMAKE_PREFIX_PATH="$CGREEN_PREFIX" LD_LIBRARY_PATH="$CGREEN_PREFIX/lib" \
       CPATH="$CGREEN_PREFIX/include" LIBRARY_PATH="$CGREEN_PREFIX/lib"

export_tree() { # export_tree <rev> <dir>
    rm -rf "$2"; mkdir -p "$2"
    git -C "$SRC" archive "$1" | tar -x -C "$2"
}

unit() { # unit <tree> <build> <ON|OFF> [extra cmake args]
    local tree=$1 build=$2 milan=$3; shift 3
    rm -rf "$build"
    cmake -S "$tree" -B "$build" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN="$milan" "$@" || return 10
    cmake --build "$build" --parallel 4 2>&1 | tee "$build.build.log" || return 11
    echo "WARNINGS: $(grep -c 'warning:' "$build.build.log")"
    "$build/unit_tests"; local u=$?
    echo "UNIT_RC=$u"
    return $u
}

case "$1" in
unit-OFF|unit-ON)
    m=${1#unit-}
    export_tree $HEAD_REV "$W/head-$m"
    unit "$W/head-$m" "$W/build-$m" "$m" || exit $?
    ctest --test-dir "$W/build-$m" --output-on-failure; c=$?; echo "CTEST_RC=$c"
    (cd "$W/head-$m" && SHLAN_LIBRARY="$W/build-$m/libshlan.so" behave --no-color); b=$?; echo "BEHAVE_RC=$b"
    (cd "$W/head-$m" && behave --dry-run --no-color); d=$?; echo "DRY_RC=$d"
    exit $((c || b || d))
    ;;
base-OFF|base-ON)
    m=${1#base-}
    export_tree $BASE_REV "$W/base-$m"
    unit "$W/base-$m" "$W/build-base-$m" "$m"
    ;;
first-OFF|first-ON)   # head tests on base sources
    m=${1#first-}
    export_tree $HEAD_REV "$W/first-$m"
    rm -rf "$W/first-$m/src"
    git -C "$SRC" archive $BASE_REV src | tar -x -C "$W/first-$m"
    unit "$W/first-$m" "$W/build-first-$m" "$m"
    ;;
asan-gcc-OFF|asan-gcc-ON|asan-clang-OFF|asan-clang-ON)
    cc=$(echo "$1" | cut -d- -f2); m=$(echo "$1" | cut -d- -f3)
    export_tree $HEAD_REV "$W/$1"
    export ASAN_OPTIONS=detect_leaks=1:abort_on_error=0 UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1
    CC=$cc unit "$W/$1" "$W/build-$1" "$m" \
        -DCMAKE_C_FLAGS="-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer"
    ;;
reversals-OFF|reversals-ON)
    m=${1#reversals-}
    export_tree $HEAD_REV "$W/rev-src-$m"
    rm -rf "$W/rev-work-$m"
    cd "$W/rev-src-$m" && python3 -I tests/check_reversals.py --work-dir "$W/rev-work-$m" \
        --prefix "$CGREEN_PREFIX" --milan "$m"
    ;;
equiv-OFF|equiv-ON)
    m=${1#equiv-}
    rm -rf "$W/eq-src-$m"; git clone -q "$SRC" "$W/eq-src-$m" && git -C "$W/eq-src-$m" checkout -q $HEAD_REV || exit 20
    rm -rf "$W/eq-work-$m"
    cd "$W/eq-src-$m" && python3 -I tests/check_equivalence.py --work-dir "$W/eq-work-$m" \
        --prefix "$CGREEN_PREFIX" --milan "$m"
    ;;
free-embedded)
    export_tree $HEAD_REV "$W/fe-src"
    cd "$W/fe-src" || exit 20
    python3 -I tests/check_freestanding.py; a=$?; echo "FREE_OFF_RC=$a"
    CC="cc -DLWSRP_MILAN=1" python3 -I tests/check_freestanding.py; b=$?; echo "FREE_ON_RC=$b"
    rm -rf "$W/emb-work"
    python3 -I tests/check_embedded.py --work-dir "$W/emb-work"; c=$?; echo "EMB_RC=$c"
    exit $((a || b || c))
    ;;
docs)
    cd "$SRC" || exit 20
    python3 doc/tools/check_sentences.py; a=$?; echo "SENTENCES_RC=$a"
    python3 doc/tools/check_references.py; b=$?; echo "REFERENCES_RC=$b"
    python3 doc/tools/check_references.py --self-test; c=$?; echo "REFSELF_RC=$c"
    python3 doc/tools/check_links.py; d=$?; echo "LINKS_RC=$d"
    exit $((a || b || c || d))
    ;;
*) echo "unknown campaign $1"; exit 2;;
esac
