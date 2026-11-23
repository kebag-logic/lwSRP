#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# parent_setup.sh: a scratch milan-fpga dev-soft-core 854bd723 with the
# published consumer patches (pin bump and the own-LeaveAll reproduction),
# its tsn-c-stack gitlink, and lwSRP checked out at the head or the base.
set -u
W="$PKT/scratch"; P="$W/parent"; E="$W/evidence/review-evidence/lwsrp20-r1/author/receipts/parent/patches"
cd "$P" || exit 20
git -c advice.detachedHead=false checkout -q 854bd7236792ce1adbd10c43b13a6a5002ad3bb6 || exit 21
# 0001 was made with --no-binary: its regenerated PNG cannot apply and is not needed to run the arms.
git apply --index --exclude=docs/diagrams/submodule_boundaries.png "$E"/0001-*.patch || exit 22
git apply --index "$E"/0002-*.patch || exit 22
git -c user.name=probe -c user.email=probe@invalid commit -qm "probe: published consumer patches 0001 (no PNG) and 0002" || exit 22
git log --oneline -3
git ls-tree HEAD third_party/
for sub in tsn-c-stack; do
    rev=$(git ls-tree HEAD third_party/$sub | awk '{print $3}')
    url=$(git config -f .gitmodules submodule.third_party/$sub.url)
    rm -rf third_party/$sub; mkdir -p third_party/$sub
    git -C third_party/$sub init -q && git -C third_party/$sub fetch -q --depth 1 "$url" "$rev" && \
        git -C third_party/$sub checkout -q FETCH_HEAD || exit 23
    echo "$sub at $(git -C third_party/$sub rev-parse HEAD)"
done
for rev in c035764f2d6105fd9598b138112ba01eaa006958 08ee86e812a0eb5e1dc6cd61b494d8baf3491348; do
    d="$W/lwsrp-$rev"; rm -rf "$d"; git clone -q "$SRC" "$d" && git -C "$d" checkout -q "$rev" || exit 24
    echo "lwSRP $(git -C "$d" rev-parse HEAD)"
done
