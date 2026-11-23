#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# rv32_size.sh <toolchain-bin-dir>: RV32I -Os object size of src/core/mrp_mad.c
# at the base and the head, with the parent's RV32_FLAGS and -DLWSRP_MILAN=1.
set -u
T=$1; W="$PKT/scratch/rv32"  # needs $PKT/scratch/rv32inc/gnu/stubs-ilp32.h (empty) for the glibc sysroot
rm -rf "$W"; mkdir -p "$W" "$PKT/scratch/rv32inc/gnu"; : > "$PKT/scratch/rv32inc/gnu/stubs-ilp32.h"
"$T/riscv32-linux-gcc" --version | head -n 1
for rev in 08ee86e812a0eb5e1dc6cd61b494d8baf3491348 c035764f2d6105fd9598b138112ba01eaa006958; do
    d="$W/${rev:0:8}"; mkdir -p "$d"
    git -C "$SRC" archive "$rev" src | tar -x -C "$d"
    (cd "$d" && "$T/riscv32-linux-gcc" -march=rv32i -mabi=ilp32 -ffreestanding -fno-stack-protector -Os -DNDEBUG \
        -std=c11 -Wall -Wextra -Werror -pedantic -fstack-usage -DCTRL_MBX_BASE=0x80000000u -DLWSRP_MILAN=1 \
        -I"$PKT/scratch/rv32inc" -Isrc/include -Isrc -c src/core/mrp_mad.c -o mrp_mad.o) || { echo "compile ${rev:0:8} rc=$?"; continue; }
    echo "${rev:0:8} $("$T/riscv32-linux-size" "$d/mrp_mad.o" | tail -n 1)"
    grep -E 'mrp_transmit|sla_registrars|la_event' "$d/mrp_mad.su" | sed "s|$d/||"
done
