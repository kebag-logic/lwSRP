#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# Negative control for tests/check_equivalence.py's REVISED exemption.
# In a scratch clone at the head, plant a wire-neutral defect (mrp_port_status
# always reports LeaveAll Active), which fails the base suite's
# leaveall_draws_are_inside_the_required_interval but changes no PDU.
# The check must exit nonzero and name the candidate suite as a problem.
set -u
W="$PKT/scratch"
d="$W/eqneg-src"; rm -rf "$d" "$W/eqneg-work"
git clone -q "$SRC" "$d" && git -C "$d" checkout -q c035764f2d6105fd9598b138112ba01eaa006958 || exit 20
python3 - "$d/src/core/mrp_mad.c" <<'EOF'
import sys
p = sys.argv[1]; t = open(p).read()
old = "        *la = priv->ports[port_id].la;\n"
assert t.count(old) == 1
open(p, "w").write(t.replace(old, "        *la = MRP_LA_STATE_ACTIVE; /* Plant: wire-neutral status defect. */\n"))
EOF
git -C "$d" diff --stat
# The check archives the checkout's sources from the working tree or HEAD; commit the plant in the clone.
git -C "$d" -c user.name=probe -c user.email=probe@invalid commit -qam "probe plant" || exit 21
cd "$d" && python3 -I tests/check_equivalence.py --work-dir "$W/eqneg-work" --prefix "$CGREEN_PREFIX" --milan OFF
rc=$?
echo "EQUIV_NEGATIVE_RC=$rc"
grep -oE 'Failure: [a-z_]+ -> [a-z_]+' "$W/eqneg-work/unit-candidate.log" | sort | uniq -c
exit 0
