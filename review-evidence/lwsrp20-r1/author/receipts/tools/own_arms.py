#!/usr/bin/env python3
"""Build and run the parent's own-LeaveAll SRP arms alone: own_arms.py REPO OUT [8x8|1x1|both] [gtest filter]."""
import sys, time
from pathlib import Path
repo, out = Path(sys.argv[1]).resolve(), Path(sys.argv[2]).resolve()
which = sys.argv[3] if len(sys.argv) > 3 else "both"
filt = sys.argv[4] if len(sys.argv) > 4 else "*"
sys.path.insert(0, str(repo / "sw/firmware/ctrl/test"))
import ctrl_build, fw_gtest, srp_arms  # noqa: E402
tree = ctrl_build.Tree(ctrl_build.CTRL, out / "build", out / "reuse", fw_gtest.Build(jobs=4))
lw = repo / "third_party/lwSRP"
rc = 0
for name, cfg in (("8x8", srp_arms.ENTITY_8X8), ("1x1", srp_arms.DEFAULT_ENTITY)):
    if which not in (name, "both"):
        continue
    start = time.time()
    o = srp_arms.arm_srp(tree, lw, 1, test=("srp_own_leaveall.cpp", filt), config=cfg)
    print(f"== {o.arm}: rc={o.rc} in {time.time() - start:.0f} s")
    print(o.log[-6000:])
    rc |= o.rc
sys.exit(1 if rc else 0)
