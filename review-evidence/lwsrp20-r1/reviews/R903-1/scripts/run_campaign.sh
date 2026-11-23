#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# Portable campaign runner: run_campaign.sh <name> <command...>
# Writes receipts/<name>.log, receipts/<name>.rc and start/end stamps.
# Environment: PKT (packet root), SRC (lwSRP checkout), CGREEN_PREFIX.
set -u
name=$1; shift
R="$PKT/receipts"
mkdir -p "$R"
date -u +%FT%TZ > "$R/$name.start"
( "$@" ) > "$R/$name.log" 2>&1
echo $? > "$R/$name.rc"
date -u +%FT%TZ > "$R/$name.end"
