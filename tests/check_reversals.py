# SPDX-License-Identifier: Apache-2.0
"""Plant independent regressions in a scratch copy and require failing checks."""

import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
MAD = "src/core/mrp_mad.c"
MSRP = "src/modules/msrp.c"
PDU = "src/core/mrp_pdu.c"

# Each replacement reverses one contract. The original checkout is never edited.
CASES = [
    ("timer-unlink", "src/ports/timer.c", "    struct shlan_timer **at = &g_head;",
     "    if (t->cs && t->link && t->link->cs) { return; }\n    struct shlan_timer **at = &g_head;", "unit"),
    ("msrp-address", MSRP, "{ 0x01u, 0x80u, 0xC2u, 0x00u, 0x00u, 0x0Eu }",
     "{ 0x91u, 0xE0u, 0xF0u, 0x00u, 0x0Eu, 0x80u }", "unit"),
    ("mmrp-address", "src/include/shish_lan/mrp.h", "0x00u, 0x20u", "0x00u, 0x21u", "unit"),
    ("mvrp-address", "src/include/shish_lan/mrp.h", "0x00u, 0x21u", "0x00u, 0x20u", "unit"),
    ("domain-offset", MSRP, "d->class_id = (uint8_t)(buf[0] + offset);",
     "d->class_id = buf[0];", "unit"),
    ("talker-offset", MSRP, "increment_stream(t->stream_id.bytes + 6, 2, offset)",
     "increment_stream(t->stream_id.bytes + 6, 2, 0)", "unit"),
    ("listener-offset", MSRP, "increment_stream((uint8_t *)attr_val_out + 6, 2, offset)",
     "increment_stream((uint8_t *)attr_val_out + 6, 2, 0)", "unit"),
    ("wire-prevalidation", PDU, "int r = parse_pass(pdu, len, ops, NULL, NULL, NULL);",
     "int r = 0;", "unit"),
    ("pdu-endmark", PDU, "if (vector_seen && off == len)",
     "if (false && vector_seen && off == len)", "unit"),
    ("leaveall-scope", MAD, "if (a->attr_type == attr_type)",
     "if (a->attr_type == attr_type || a->attr_type != attr_type)", "unit"),
    ("local-registration", MAD, "const struct reg_entry *e = &reg_table[ev][ai->reg];",
     "if (ev == MRP_EVENT_NEW) { ev = MRP_EVENT_RNEW; }\n    const struct reg_entry *e = &reg_table[ev][ai->reg];", "unit"),
    ("registrar-condition", MAD, "ai->reg != MRP_REG_STATE_IN)",
     "false && ai->reg != MRP_REG_STATE_IN)", "unit"),
    ("periodic-interval", MAD, "&ps->pt_timer, 100u", "&ps->pt_timer, 20u", "unit"),
    ("leaveall-randomization", MAD,
     "return ps->leaveall_cs + 1u + ps->random % (ps->leaveall_cs / 2u - 1u);",
     "return ps->leaveall_cs;", "unit"),
    ("refused-storage", MAD, "if (r != 0) {\n        return r;",
     "if (r != 0) {\n        ps->prepared_pdu = NULL;\n        return r;", "unit"),
    ("registrar-during-refusal", MAD, "struct mrp_attr_timer_arg *a = (struct mrp_attr_timer_arg *)arg;",
     "struct mrp_attr_timer_arg *a = (struct mrp_attr_timer_arg *)arg;\n    if (priv_of(a->app)->ports[a->port_id].prepared_pdu) { return; }", "unit"),
    ("changed-listener-indication", MAD, "if (changed_in && (ev == MRP_EVENT_RJOININ",
     "if (false && changed_in && (ev == MRP_EVENT_RJOININ", "unit"),
    ("receive-opportunity", MAD, "// Table 10-3 note 6: receiving an event can request a transmit too.\n    switch (ai->appl)",
     "// Reversal: omit receive-driven requests.\n    switch (MRP_APPL_STATE_QA)", "unit"),
    ("receive-interest", MAD, "if (priv->filter && !priv->filter(",
     "if (false && priv->filter && !priv->filter(", "unit"),
    ("reclaim", MAD, "if (a->reg == MRP_REG_STATE_MT &&",
     "if (false && a->reg == MRP_REG_STATE_MT &&", "unit"),
    ("split-fairness", MAD, "a->tx_deferred != (priority == 0)",
     "a->tx_deferred != (priority != 0)", "unit"),
    ("received-withdrawal-value", MAD, "previous && !declares ? previous :",
     "previous && !declares && false ? previous :", "unit"),
    ("local-withdrawal-value", MAD,
     "*ai   = find_attr(ps, app->ops, attr_type, attr_val);",
     "*ai   = get_or_create_attr(app, ps, port_id, attr_type, attr_val);", "unit"),
    ("talker-replacement", MAD, "rc->app->ops->attr_replaces) {",
     "rc->app->ops->attr_replaces && false) {", "unit"),
    ("listener-redeclaration", MSRP, "MSRP_ATTR_TYPE_LISTENER, val, true);",
     "MSRP_ATTR_TYPE_LISTENER, val, false);", "unit"),
    ("domain-member-order", "src/include/shish_lan/msrp.h", "struct msrp_ctx {",
     "struct msrp_ctx {\n    void (*inserted_before_existing_members)(void);", "unit"),
    ("hosted-allocation-header", "src/ports/alloc.h", "#include <stddef.h>",
     "#include <stddef.h>\n#include <stdlib.h>", "freestanding"),
    ("hosted-error-header", PDU, '#include "shish_lan/error.h"',
     '#include "shish_lan/error.h"\n#include <errno.h>', "freestanding"),
    ("point-to-point-condition", MAD, "if ((p2p && ev == MRP_EVENT_RJOININ &&",
     "if ((false && p2p && ev == MRP_EVENT_RJOININ &&", "unit"),
    ("shared-in-condition", MAD, "(!p2p && ev == MRP_EVENT_RIN)",
     "(false && !p2p && ev == MRP_EVENT_RIN)", "unit"),
    ("withdrawal-transition", MAD,
     "_S(TX_MSG_LEAVE, MRP_APPL_STATE_VO), _X, _X,",
     "_S(TX_MSG_LEAVE, MRP_APPL_STATE_LO), _X, _X,", "unit"),
    ("periodic-passive", MAD,
     "_X, _S(TX_MSG_NONE, MRP_APPL_STATE_AP), _X,\n    },\n    /* LEAVETIMER:",
     "_X, _X, _X,\n    },\n    /* LEAVETIMER:", "unit"),
    ("leaveall-all-types", MAD,
     "for (unsigned type = 1; type <= last; ++type)",
     "for (unsigned type = 1; type < last; ++type)", "unit"),
    ("unknown-stream-message", PDU, "bool unknown = !expected && later;",
     "bool unknown = false;", "unit"),
    ("bounded-header-initialization", PDU, "uint16_t vh = 0;",
     "uint16_t vh;", "strict"),
    ("milan-delayed-in-leave", MAD,
     "if (app->ops->milan_rapid_leave && ev == MRP_EVENT_RLV &&",
     "if (false && app->ops->milan_rapid_leave && ev == MRP_EVENT_RLV &&", "unit"),
    ("milan-restarted-lv-deadline", MAD,
     "const struct reg_entry *e = &reg_table[ev][ai->reg];",
     "const struct reg_entry *e = &reg_table[ev][ai->reg];\n"
     "    if (app->ops->milan_rapid_leave && ev == MRP_EVENT_RLV && ai->reg == MRP_REG_STATE_LV) {\n"
     "        e = &reg_table[MRP_EVENT_RLV][MRP_REG_STATE_IN];\n    }", "unit"),
    ("milan-profile-selection", MSRP,
     ".milan_rapid_leave = LWSRP_MILAN != 0,",
     ".milan_rapid_leave = LWSRP_MILAN == 0,", "unit"),
    ("milan-option-scope", MAD,
     "if (app->ops->milan_rapid_leave && ev == MRP_EVENT_RLV &&",
     "if (ev == MRP_EVENT_RLV &&", "unit"),
    ('application-decode-error', PDU, 'return r; /* The validation pass rejects the complete PDU. */',
     'continue; /* Plant: skip an invalid application value. */', "unit"),
    ('stream-increment-overflow', MSRP, 'return offset ? -SHLAN_ERROR_RANGE : 0;',
     'return 0;', "unit"),
    ('domain-priority-range', MSRP, 'buf[1] > 7u || offset > 7u - buf[1]',
     'false', "unit"),
    ('domain-class-range', MSRP, 'offset > 255u - buf[0]',
     'false', "unit"),
    ('vlan-range', 'src/modules/mvrp.c', 'vid > MVRP_VID_MAX || offset > MVRP_VID_MAX - vid',
     'false', "unit"),
    ('mac-increment-overflow', 'src/modules/mmrp.c', 'if (carry) {',
     'if (false && carry) {', "unit"),
    ('unknown-event-extension', PDU, 'unknown || (later && unknown_event)',
     'unknown', "unit"),
    ('current-version-extension', PDU, 'bool later = pdu[0] > ops->proto_version;',
     'bool later = true;', "unit"),
    ('propagation-retention', MAD, 'ps->map_tail = work;',
     'ps->map_tail = work;\n        if (ps->prepared_pdu) {\n            if (ps->map_head == work) { ps->map_head = NULL; ps->map_tail = NULL; }\n        }', "unit"),
    ('propagation-order', MAD, 'ps->map_tail->next = work;',
     'work->next = ps->map_head;\n            ps->map_head = work;', "unit"),
    ('registrar-recovery-indication', MAD, '_RE(REG_IND_NONE, REG_TIMER_STOP, MRP_REG_STATE_IN),',
     '_RE(REG_IND_JOIN, REG_TIMER_STOP, MRP_REG_STATE_IN),', "unit"),
    ('committed-local-leaveall', MAD, '// 10.7.6.6: the committed sLA also signals rLA locally.\n        broadcast_event(app, ps, MRP_EVENT_RLA, port_id);',
     '/* Plant: no local receive event after committed LeaveAll. */', "unit"),
    ('omitted-leaveall-event', MAD, 'deliver_event(app, ps, a, MRP_EVENT_TXLAF, port_id);',
     '/* Plant: omit txLAF. */', "unit"),
    ('reserved-leaveall-event', PDU, 'bool unknown_event = la > MRP_LA_ALL;',
     'bool unknown_event = false;', "unit"),
    ('listener-subtype', MAD, 'mrp_four_pack(bytes[len], 0, 0, 0)',
     'mrp_four_pack(2, 0, 0, 0)', "unit"),
    ('leaveall-upper-bound', MAD, 'ps->leaveall_cs / 2u - 1u',
     'ps->leaveall_cs / 2u + 1u', "unit"),
    ('reclaim-leaving-observer', MAD, 'a->appl == MRP_APPL_STATE_QO))',
     'a->appl == MRP_APPL_STATE_QO || a->appl == MRP_APPL_STATE_LO))', "unit"),
    ('milan-redeclare-scope', MAD, 'ev == MRP_EVENT_RLV &&',
     '(ev == MRP_EVENT_RLV || ev == MRP_EVENT_REDECLARE) &&', "unit"),
    ('milan-transmitted-leaveall-scope', MAD, 'ev == MRP_EVENT_RLV &&',
     '(ev == MRP_EVENT_RLV || ev == MRP_EVENT_TXLA) &&', "unit"),
    ('received-leaveall-restart', MAD, 'la_event(rc->app, rc->ps, MRP_EVENT_RLA, rc->port_id);',
     '/* Plant: omit participant LeaveAll restart. */', "unit"),
    ("embedded-switch-source", "CMakeLists.txt", "      src/core/switch.c\n", "", "embedded"),
]

REQUIRED_FAILURES = {
    'application-decode-error': ['application_errors_reject_the_whole_pdu'],
    'stream-increment-overflow': ['stream_vectors_cannot_wrap_identity_or_destination'],
    'domain-priority-range': ['application_errors_reject_the_whole_pdu'],
    'domain-class-range': ['application_errors_reject_the_whole_pdu'],
    'vlan-range': ['vlan_and_mac_vector_ranges_are_atomic'],
    'mac-increment-overflow': ['vlan_and_mac_vector_ranges_are_atomic'],
    'unknown-event-extension': ['later_versions_skip_unknown_events_but_current_versions_reject_them'],
    'current-version-extension': ['later_versions_skip_unknown_messages_in_every_application'],
    'propagation-retention': ['retained_ports_replay_propagated_join_and_timer_leave_in_order'],
    'propagation-order': ['queued_propagation_owns_values_and_survives_source_reclamation'],
    'registrar-recovery-indication': ['registrar_recovery_stops_aging_without_duplicate_join_or_map'],
    'committed-local-leaveall': ['full_leaveall_reports_each_required_transition'],
    'omitted-leaveall-event': ['full_leaveall_reports_each_required_transition'],
    'reserved-leaveall-event': ['reserved_leaveall_events_are_rejected_atomically'],
    'listener-subtype': ['changed_listener_redeclares_from_a_quiet_applicant'],
    'leaveall-upper-bound': ['leaveall_draws_are_inside_the_required_interval'],
    'reclaim-leaving-observer': ['leaving_observer_is_retained_until_its_pending_transmission'],
    'milan-redeclare-scope': ['redeclare_keeps_the_ieee_deadline'],
    'milan-transmitted-leaveall-scope': ['transmitted_leaveall_keeps_the_ieee_deadline'],
    'received-leaveall-restart': ['received_leaveall_restarts_the_participant_deadline'],
    "unknown-stream-message": ["later_versions_skip_unknown_messages_in_every_application", "later_versions_skip_unknown_stream_messages"],
    "milan-delayed-in-leave": ["talker_leave_in_is_immediate", "listener_leave_in_is_immediate"],
    "milan-restarted-lv-deadline": ["leave_in_lv_keeps_the_original_deadline"],
    "milan-profile-selection": ["msrp_constructor_selects_the_build_profile"],
    "milan-option-scope": ["mvrp_keeps_ieee_leave_timing", "mmrp_keeps_ieee_leave_timing",
                           "disabled_application_option_preserves_ieee_timing"],
}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work-dir", type=Path, required=True)
    parser.add_argument("--prefix", type=Path, required=True)
    parser.add_argument("--milan", choices=["OFF", "ON"], default="OFF")
    args = parser.parse_args()
    work = args.work_dir.resolve()
    if work.is_relative_to(ROOT) or work.exists():
        parser.error("Use a new scratch directory outside the checkout")
    work.mkdir(parents=True)
    source = work / "source"
    source.mkdir()
    for name in ["CMakeLists.txt", "src", "tests"]:
        path = ROOT / name
        if path.is_dir():
            shutil.copytree(path, source / name, ignore=shutil.ignore_patterns("__pycache__"))
        else:
            shutil.copy2(path, source / name)
    build = work / "build"
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = str(args.prefix.resolve() / "lib") + os.pathsep + env.get("LD_LIBRARY_PATH", "")
    records = []

    def run(label, command):
        result = subprocess.run(command, cwd=source, env=env, capture_output=True, text=True, timeout=120)
        output = result.stdout + result.stderr
        (work / (label + ".log")).write_text(output)
        records.append({"label": label, "command": list(map(str, command)), "rc": result.returncode})
        (work / "commands.json").write_text(json.dumps(records, indent=2) + "\n")
        print(f"{label}: rc={result.returncode}", flush=True)
        return result.returncode, output

    rc, _ = run("configure", ["cmake", "-S", str(source), "-B", str(build),
                              "-DCMAKE_BUILD_TYPE=Release", f"-DCMAKE_PREFIX_PATH={args.prefix.resolve()}",
                              f"-DLWSRP_MILAN={args.milan}"])
    if rc:
        return 1
    build_command = ["cmake", "--build", str(build), "--parallel", "2"]
    check_command = ["ctest", "--test-dir", str(build), "--output-on-failure", "--timeout", "10"]
    if run("baseline-build", build_command)[0] or run("baseline-check", check_command)[0]:
        return 1
    failures = 0
    for label, name, old, new, check in CASES:
        path = source / name
        original = path.read_text()
        if old not in original:
            print(f"FAIL {label}: mutation target missing")
            failures += 1
            continue
        path.write_text(original.replace(old, new))
        try:
            if check == "unit":
                if run(label + "-build", build_command)[0]:
                    print(f"FAIL {label}: build failure is not a killed behavioral reversal")
                    failures += 1
                    continue
                rc, output = run(label, check_command)
                killed = rc != 0 and "Failure:" in output
                killed = killed and all(name in output for name in REQUIRED_FAILURES.get(label, []))
                if label == "milan-delayed-in-leave":
                    killed = killed and "leave_in_lv_keeps_the_original_deadline" not in output
                if label == "milan-restarted-lv-deadline":
                    killed = killed and "leave_in_is_immediate" not in output
            elif check == "embedded":
                rc, output = run(label, [sys.executable, "tests/check_embedded.py",
                                         "--work-dir", str(work / "embedded")])
                killed = rc != 0 and "undefined reference" in output and "shlan_connect" in output
            elif check == "strict":
                rc, output = run(label, ["cc", "-O2", "-std=c11", "-Wall", "-Wextra", "-Werror",
                                         "-Isrc/include", "-Isrc", "-c", name, "-o", str(work / "strict.o")])
                killed = rc != 0 and "uninitialized" in output
            else:
                rc, output = run(label, [sys.executable, "tests/check_freestanding.py"])
                killed = rc != 0 and "hosted headers" in output
            print(f"{'KILLED' if killed else 'SURVIVED'} {label}", flush=True)
            failures += not killed
        finally:
            path.write_text(original)
    if run("restored-build", build_command)[0] or run("restored-check", check_command)[0]:
        failures += 1
    print(f"Reversals: {len(CASES)}; failures: {failures}")
    return int(failures != 0)


if __name__ == "__main__":
    raise SystemExit(main())
