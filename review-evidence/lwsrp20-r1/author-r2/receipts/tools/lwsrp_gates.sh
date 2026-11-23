#!/bin/bash
# lwSRP gates at the lane head (round 2). Usage: lwsrp_gates.sh PART OUT
# PART: quick | rev-OFF | rev-ON | eq-OFF | eq-ON | ctl-OFF | ctl-ON
set -u
S=<scratch>
source $S/env.sh
L=<lane>
PART=$1; O=$2
mkdir -p $O
export TMPDIR=$S/r2/tmpdir
cd $L
log() { echo "$*" | tee -a $O/summary-$PART.txt; }
log "HEAD $(git rev-parse HEAD) status '$(git status --short | tr '\n' ' ')'"
case_quick() {
  for m in OFF ON; do
    b=$O/build-$m; rm -rf $b
    cmake -S . -B $b -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$CGREEN_PREFIX -DLWSRP_MILAN=$m > $O/cfg-$m.log 2>&1
    cmake --build $b --parallel 8 > $O/build-$m.log 2>&1; rc=$?
    log "build $m rc=$rc warnings=$(/usr/bin/grep -ci 'warning' $O/build-$m.log)"
    (cd $b && ./unit_tests > $O/unit-$m.log 2>&1); log "unit $m rc=$? $(tail -1 $O/unit-$m.log)"
    ctest --test-dir $b --output-on-failure > $O/ctest-$m.log 2>&1; log "ctest $m rc=$? $(/usr/bin/grep 'tests passed' $O/ctest-$m.log)"
    SHLAN_LIBRARY=$b/libshlan.so behave --no-color > $O/behave-$m.log 2>&1; log "behave $m rc=$? $(/usr/bin/grep -E '^[0-9]+ (scenario|step)' $O/behave-$m.log | tr '\n' ' ')"
  done
  behave --dry-run --no-color > $O/behave-dry.log 2>&1; log "behave dry rc=$? $(/usr/bin/grep -E '^[0-9]+ (scenario|step)' $O/behave-dry.log | tr '\n' ' ')"
  cc -std=c11 -Isrc/include tests/unit/mrp_pdu_test.c src/core/mrp_pdu.c -xc - -lcgreen -o $O/mrp_pdu_tests <<'C'
#include <cgreen/cgreen.h>
TestSuite *mrp_pdu_suite(void);
int main(void)
{
    return run_test_suite(mrp_pdu_suite(), create_text_reporter());
}
C
  $O/mrp_pdu_tests > $O/codec.log 2>&1; log "codec rc=$? $(tail -1 $O/codec.log)"
  python3 -I -B tests/check_freestanding.py > $O/free-OFF.log 2>&1; log "freestanding OFF rc=$? $(tail -1 $O/free-OFF.log)"
  CC="cc -DLWSRP_MILAN=1" python3 -I -B tests/check_freestanding.py > $O/free-ON.log 2>&1; log "freestanding ON rc=$? $(tail -1 $O/free-ON.log)"
  python3 -I -B tests/check_embedded.py --work-dir $O/embedded > $O/embedded.log 2>&1; log "embedded rc=$? $(tail -1 $O/embedded.log)"
  for cc in gcc clang; do for m in 0 1; do
    $cc -O2 -std=c11 -Wall -Wextra -Wpedantic -Werror -DLWSRP_MILAN=$m -Isrc/include -Isrc -c src/core/mrp_mad.c -o $O/strict-$cc-$m.o > $O/strict-$cc-$m.log 2>&1
    log "strict $cc milan=$m rc=$? bytes=$(stat -c %s $O/strict-$cc-$m.log)"
  done; done
  for cc in gcc clang; do for m in OFF ON; do
    b=$O/san-$cc-$m; rm -rf $b
    CC=$cc cmake -S . -B $b -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$CGREEN_PREFIX -DLWSRP_MILAN=$m \
      "-DCMAKE_C_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer -O1" \
      -DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined > $O/san-$cc-$m.cfg.log 2>&1
    cmake --build $b --parallel 8 > $O/san-$cc-$m.build.log 2>&1
    syms=$(nm $b/unit_tests | /usr/bin/grep -c -E '__asan_init|__ubsan_handle')
    (cd $b && ./unit_tests > $O/san-$cc-$m.log 2>&1); rc=$?
    log "sanitizer $cc $m rc=$rc symbols=$syms reports=$(/usr/bin/grep -c -E 'ERROR: AddressSanitizer|runtime error' $O/san-$cc-$m.log) $(tail -1 $O/san-$cc-$m.log)"
  done; done
  # Planted control: a heap overread in sla_registrars must be reported.
  n=$O/san-neg; rm -rf $n; mkdir -p $n; cp -r CMakeLists.txt src tests $n/
  python3 -I - $n/src/core/mrp_mad.c <<'PY'
import sys
p = sys.argv[1]; t = open(p).read()
old = "        enum mrp_reg_state reg_from = a->reg;\n"
assert t.count(old) == 1
open(p, "w").write(t.replace(old, old + "        volatile uint8_t past = ((const uint8_t *)a)[sizeof(*a) + 8u]; (void)past; /* Plant */\n"))
PY
  CC=gcc cmake -S $n -B $n/b -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$CGREEN_PREFIX \
    "-DCMAKE_C_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer -O1" \
    -DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined > $O/san-neg.cfg.log 2>&1
  cmake --build $n/b --parallel 8 > $O/san-neg.build.log 2>&1
  (cd $n/b && ./unit_tests > $O/san-neg.log 2>&1); log "sanitizer planted overread rc=$? reports=$(/usr/bin/grep -c 'ERROR: AddressSanitizer' $O/san-neg.log)"
  # Coverage, both profiles merged.
  for m in OFF ON; do
    b=$O/cov-$m; rm -rf $b
    cmake -S . -B $b -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$CGREEN_PREFIX -DLWSRP_MILAN=$m \
      "-DCMAKE_C_FLAGS=--coverage -O0" -DCMAKE_EXE_LINKER_FLAGS=--coverage > $O/cov-$m.cfg.log 2>&1
    cmake --build $b --parallel 8 > $O/cov-$m.build.log 2>&1
    (cd $b && ./unit_tests > $O/cov-$m.unit.log 2>&1); log "coverage build $m unit rc=$? $(tail -1 $O/cov-$m.unit.log)"
  done
  python3 -I $S/tools/lwsrp_cov.py $L $O/cov-OFF $O/cov-ON --functions sla_registrars --json $O/coverage.json > $O/coverage.txt 2>&1
  log "coverage rc=$? $(/usr/bin/grep -E 'mrp_mad.c|TOTAL|sla_registrars' $O/coverage.txt | tr '\n' ' ')"
  # Documentation.
  python3 -I -B doc/tools/check_sentences.py > $O/sentences.log 2>&1; log "sentences rc=$? $(tail -1 $O/sentences.log)"
  python3 -I -B doc/tools/check_references.py > $O/references.log 2>&1; log "references rc=$? $(tail -1 $O/references.log)"
  python3 -I -B doc/tools/check_references.py --self-test > $O/references-self.log 2>&1; log "references self-test rc=$? $(tail -1 $O/references-self.log)"
  python3 -I -B doc/tools/check_links.py --github-auth > $O/links.log 2>&1; log "links rc=$? $(tail -1 $O/links.log)"
  rm -rf $O/graphs; python3 -I -B doc/tools/render_mermaid.py --output $O/graphs > $O/graphs.log 2>&1; log "graphs rc=$? $(tail -1 $O/graphs.log)"
}
case $PART in
  quick) case_quick ;;
  rev-*) m=${PART#rev-}; python3 -B tests/check_reversals.py --work-dir $O/work-$m --prefix $CGREEN_PREFIX --milan $m > $O/rev-$m.log 2>&1; log "reversals $m rc=$? $(tail -1 $O/rev-$m.log)" ;;
  eq-*) m=${PART#eq-}; python3 -I -B tests/check_equivalence.py --work-dir $O/work-$m --prefix $CGREEN_PREFIX --milan $m > $O/eq-$m.log 2>&1; log "equivalence $m rc=$? $(/usr/bin/grep -E '^Scenarios|^REVISED|^FAIL' $O/eq-$m.log | tr '\n' ' ')" ;;
  ctl-*) m=${PART#ctl-}; python3 -I -B tests/check_equivalence_controls.py --work-dir $O/work-$m --prefix $CGREEN_PREFIX --milan $m > $O/ctl-$m.log 2>&1; log "controls $m rc=$? $(tail -1 $O/ctl-$m.log)" ;;
esac
log "git status after '$(git status --short | tr '\n' ' ')'"
