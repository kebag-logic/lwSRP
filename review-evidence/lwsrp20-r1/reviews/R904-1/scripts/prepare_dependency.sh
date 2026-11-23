#!/bin/sh
# Usage: sh prepare_dependency.sh PACKET
# Installs the test-only dependency entirely under the disposable scratch directory.
set -eu
packet=$(realpath "$1")
mkdir -p "$packet/scratch" "$packet/receipts"
git clone --quiet --branch 1.6.4 --depth 1 https://github.com/cgreen-devs/cgreen.git "$packet/scratch/cgreen"
test "$(git -C "$packet/scratch/cgreen" rev-parse HEAD)" = 91ba387904d7f43c6564486690386e76d4f8bc76
cmake -S "$packet/scratch/cgreen" -B "$packet/scratch/cgreen-build" -DCMAKE_INSTALL_PREFIX="$packet/scratch/deps" -DWITH_UNIT_TESTS=OFF
make -C "$packet/scratch/cgreen-build" -j16 install
