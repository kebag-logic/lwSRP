#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Run only the consumer's own-LeaveAll arms (srp_own_leaveall.cpp at 8x8/1if
and 1x1/1if) from a scratch parent tree, against one lwSRP checkout.

Usage: own_leaveall_arms.py <parent-root> <lwsrp-checkout> <out-dir> [--base-pin]
--base-pin points the parent's pin check at the lwSRP checkout's own HEAD, as
the published base arm did ("the pin moved back in a scratch copy"); nothing
else in the arm changes.
"""
import subprocess
import sys
from pathlib import Path

root, lwsrp, out = (Path(a).resolve() for a in sys.argv[1:4])
base_pin = "--base-pin" in sys.argv[4:]
sys.path[:0] = [str(root / "sw/firmware/ctrl/test"), str(root / "sw/firmware/gtest")]
import ctrl_arms  # noqa: E402
import fw_gtest  # noqa: E402
import srp_arms  # noqa: E402
from ctrl_build import CTRL, Tree  # noqa: E402

if base_pin:
    head = subprocess.run(["git", "-C", str(lwsrp), "rev-parse", "HEAD"], capture_output=True, text=True,
                          check=True).stdout.strip()
    ctrl_arms.LWSRP_REV = head
print(f"pin {ctrl_arms.LWSRP_REV}")
tree = Tree(CTRL, out / "build", out / "reuse", fw_gtest.Build(jobs=4))
outcomes = srp_arms.own_leaveall_arms(tree, lwsrp)
for o in outcomes:
    print(f"=== arm {o.arm} rc={o.rc}")
    print(o.log)
sys.exit(int(any(o.rc for o in outcomes)))
