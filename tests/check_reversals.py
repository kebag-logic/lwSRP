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
    ("changed-listener-indication", MAD, "if (changed && (ev == MRP_EVENT_RJOININ",
     "if (false && changed && (ev == MRP_EVENT_RJOININ", "unit"),
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
    ("pending-point-to-point-condition", MAD,
     "ai->appl == MRP_APPL_STATE_VO || ai->appl == MRP_APPL_STATE_VP",
     "ai->appl == MRP_APPL_STATE_VO", "unit"),
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
    ('changed-in-only', 'src/core/mrp_mad.c', 'previous->reg != MRP_REG_STATE_MT &&', 'previous->reg == MRP_REG_STATE_IN &&', 'unit'),
    ('stream-list-boundary', 'src/core/mrp_pdu.c', 'if (unknown && msrp) {', 'if (false && unknown && msrp) {', 'unit'),
    ('changed-value-rollback', 'src/core/mrp_mad.c', 'memcpy(ai->attr_val, previous_value, sizeof(previous_value));', '/* Plant: retain changed source value after failed reservation. */', 'unit'),
    ('registrar-rollback', 'src/core/mrp_mad.c', '        ai->reg = previous;', '        (void)previous;', 'unit'),
    ('applicant-rollback', 'src/core/mrp_mad.c', '        ai->appl = appl_from;', '        (void)appl_from;', 'unit'),
    ('leave-timer-retry', 'src/core/mrp_mad.c', '            shlan_timer_arm(&ai->leave_timer, 1u);', '            /* Plant: no timer retry. */', 'unit'),
    ('receive-map-error', 'src/core/mrp_mad.c', 'ctx.error ? ctx.error : priv->map_error;', 'ctx.error;', 'unit'),
    ('reservation-atomicity', 'src/core/mrp_mad.c', '            priv_of(app)->map_error = -SHLAN_ERROR_NO_MEMORY;\n            return -SHLAN_ERROR_NO_MEMORY;', '            priv_of(app)->map_error = -SHLAN_ERROR_NO_MEMORY;\n            return 0;', 'unit'),
    ('poll-replay', 'src/core/mrp_mad.c', '    map_replay(app, port_id);\n    if (!ps->prepared_pdu &&', '    if (!ps->prepared_pdu &&', 'unit'),
    ('commit-replay', 'src/core/mrp_mad.c', '    map_replay(app, port_id);\n    ps->join_wait = ps->join_cs;', '    ps->join_wait = ps->join_cs;', 'unit'),
    ('queue-teardown', 'src/core/mrp_mad.c', 'struct mrp_map_work *work = priv->ports[p].map_head;', 'struct mrp_map_work *work = NULL;', 'unit'),
    ('zero-attribute-length', 'src/core/mrp_pdu.c', '|| !alen ||', '||', 'unit'),
    ('changed-value-propagation', 'src/core/mrp_mad.c', '    if (indicated) {\n        map_publish', '    if (indicated && !changed) {\n        map_publish', 'unit'),
    ('replay-error-retention', 'src/core/mrp_mad.c', 'return; /* Retain work if destination allocation is exhausted. */', '/* Plant: discard failed destination work. */', 'unit'),
    ('callback-order', 'src/core/mrp_mad.c', '    switch (e->ind) {\n    case REG_IND_NEW:\n        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, true);\n        break;\n    case REG_IND_JOIN:\n        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, false);\n        break;\n    case REG_IND_LV:\n        app->ops->leave_ind(app, port_id, ai->attr_type, ind_value);\n        break;\n    default:\n        break;\n    }\n    if (indicated) {\n        map_publish(app, port_id, ai->attr_type, ind_value, join, reserved);\n        map_replay_all(app);\n    }\n', '    if (indicated) {\n        map_publish(app, port_id, ai->attr_type, ind_value, join, reserved);\n    }\n    switch (e->ind) {\n    case REG_IND_NEW:\n        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, true);\n        break;\n    case REG_IND_JOIN:\n        app->ops->join_ind(app, port_id, ai->attr_type, ai->attr_val, false);\n        break;\n    case REG_IND_LV:\n        app->ops->leave_ind(app, port_id, ai->attr_type, ind_value);\n        break;\n    default:\n        break;\n    }\n    if (indicated) {\n        map_replay_all(app);\n    }\n', 'unit'),
    ('flush-retry', 'src/core/mrp_mad.c', '        if (ev == MRP_EVENT_FLUSH) {\n            /* The topology API cannot report refusal. Retain its withdrawal. */\n            if (!ai->flush_pending) {\n                memcpy(ai->flush_value, ai->attr_val, attr_store_len(app->ops, ai->attr_type));\n            }\n            ai->flush_pending = true;\n            ai->reg = MRP_REG_STATE_LV;\n            shlan_timer_arm(&ai->leave_timer, 1u);\n        }\n', '', 'unit'),
    ('replacement-order', 'src/core/mrp_mad.c', '                if (r < 0) {\n                    if (previous) {', '                if (false && r < 0) {\n                    if (previous) {', 'unit'),
    ('receive-stop', 'src/core/mrp_mad.c', 'if (rc->error || priv->map_error) {', 'if (rc->error) {', 'unit'),
    ('policy-mask', 'src/core/mrp_mad.c', '        if (!(ports & (1u << work->port_id))) {', '        if (false && !(ports & (1u << work->port_id))) {', 'unit'),
    ('no-policy-reservation', 'src/core/mrp_mad.c', '    if (join ? !app->ops->map_join : !app->ops->map_leave) {\n        return 0;\n    }\n', '', 'unit'),
    ('pending-flush', 'src/core/mrp_mad.c', '            ai->flush_pending = true;', '            ai->flush_pending = false;', 'unit'),
    ('flush-before-refresh', 'src/core/mrp_mad.c', 'if (previous && previous->flush_pending) {', 'if (false && previous && previous->flush_pending) {', 'unit'),
    ('flush-deadline', 'src/core/mrp_mad.c', 'ai->reg = MRP_REG_STATE_LV;\n            shlan_timer_arm(&ai->leave_timer, 1u);', 'ai->reg = MRP_REG_STATE_LV;\n            shlan_timer_arm(&ai->leave_timer, 2u);', 'unit'),
    ('flush-observer', 'src/core/mrp_mad.c', '        observe(app, ai, ev, port_id, appl_from, reg_from);\n        return r;', '        return r;', 'unit'),
    ('replacement-lv', 'src/core/mrp_mad.c', 'if (old != ai && old->reg != MRP_REG_STATE_MT &&', 'if (old != ai && old->reg == MRP_REG_STATE_IN &&', 'unit'),
    ('replacement-leave-timer', 'src/core/mrp_mad.c', '                if (r >= 0) {\n                    r = deliver_event_changed(rc->app, rc->ps, old,\n                                              MRP_EVENT_LEAVETIMER, rc->port_id, false);\n                }\n', '', 'unit'),
    ('receive-instance-stop', 'src/core/mrp_mad.c', 'if (rc->error || priv->map_error) {', 'if (priv->map_error) {', 'unit'),
    ('flush-completion', MAD, '        ai->flush_pending = false;', '        /* Plant: retain completed withdrawal. */', 'unit'),
    ('flush-snapshot-bypass', 'src/core/mrp_mad.c', 'ai->flush_value : ai->attr_val;', 'ai->attr_val : ai->attr_val;', 'unit'),
    ('flush-snapshot-replaced', 'src/core/mrp_mad.c', 'if (!ai->flush_pending) {', 'if (true) {', 'unit'),
    ('flush-snapshot-indication', 'src/core/mrp_mad.c', 'app->ops->leave_ind(app, port_id, ai->attr_type, ind_value);', 'app->ops->leave_ind(app, port_id, ai->attr_type, ai->attr_val);', 'unit'),
    ('flush-snapshot-policy', 'src/core/mrp_mad.c', 'map_publish(app, port_id, ai->attr_type, ind_value, join, reserved);', 'map_publish(app, port_id, ai->attr_type, ai->attr_val, join, reserved);', 'unit'),
    ('flush-timer-completion', 'src/core/mrp_mad.c', '    if (e->ind == REG_IND_LV) {', '    if (e->ind == REG_IND_LV && ev == MRP_EVENT_FLUSH) {', 'unit'),
    # Issue #17: one Message per AttributeType, ascending vectors, one EndMark each.
    ("grouped-message-split", MAD, "        v += size;\n    }\n    return tx_close(ops, buf, v);",
     "        v += size;\n        /* Plant: close the Message after every vector. */\n"
     "        buf = tx_close(ops, buf, v);\n        v = first = tx_open(ops, type, buf);\n"
     "    }\n    return tx_close(ops, buf, v);", "unit"),
    ("grouped-endmark-count", MAD, "pdu[off++] = 0; pdu[off++] = 0; /* MRPDU EndMark */",
     "/* Plant: omit the MRPDU EndMark. */", "unit"),
    ("grouped-vector-order", MAD, "memcmp(at - size + 2, at + 2, len) > 0",
     "memcmp(at - size + 2, at + 2, len) < 0", "unit"),
    ("grouped-dropped-vector", MAD, "a->attr_type != type || e->tx == TX_MSG_NONE",
     "a->attr_type != type || !a->next || e->tx == TX_MSG_NONE", "unit"),
]

REQUIRED_FAILURES = {
    "grouped-message-split": ["two_listener_values_share_one_message",
                              "every_stream_pdu_keeps_one_ordered_message_per_type"],
    "grouped-endmark-count": ["two_listener_values_share_one_message",
                              "every_vlan_and_mac_pdu_keeps_one_ordered_message_per_type"],
    "grouped-vector-order": ["two_listener_values_share_one_message",
                             "domain_classes_share_one_message_in_ascending_order"],
    "grouped-dropped-vector": ["two_listener_values_share_one_message",
                               "an_ethernet_mtu_carries_124_listener_vectors_in_one_message"],
    "point-to-point-condition": ["applicant_receive_conditions_follow_link_mode",
                                  "pending_applicant_joinin_obeys_note_four"],
    "pending-point-to-point-condition": ["pending_applicant_joinin_obeys_note_four"],
    "shared-in-condition": ["applicant_receive_conditions_follow_link_mode"],
    'flush-snapshot-bypass': ['pending_flush_talker_snapshot_survives_cross_port_updates', 'pending_flush_failed_talker_snapshot_survives_cross_port_updates', 'pending_flush_listener_snapshot_survives_cross_port_updates', 'pending_flush_snapshot_survives_local_declarations_and_repeated_failure'],
    'flush-snapshot-replaced': ['pending_flush_snapshot_survives_local_declarations_and_repeated_failure'],
    'flush-snapshot-indication': ['pending_flush_talker_snapshot_survives_cross_port_updates', 'pending_flush_failed_talker_snapshot_survives_cross_port_updates', 'pending_flush_listener_snapshot_survives_cross_port_updates'],
    'flush-snapshot-policy': ['pending_flush_talker_snapshot_survives_cross_port_updates', 'pending_flush_failed_talker_snapshot_survives_cross_port_updates', 'pending_flush_listener_snapshot_survives_cross_port_updates'],
    'flush-timer-completion': ['timer_completed_flush_keeps_unchanged_registrations_quiet'],

    'flush-completion': ['pending_flush_precedes_received_registration'],
    'pending-flush': ['pending_flush_precedes_received_registration', 'pending_flush_talker_receive_failures_preserve_order_and_values', 'pending_flush_failed_talker_receive_failures_preserve_order_and_values', 'pending_flush_listener_receive_failures_preserve_order_and_values'],
    'flush-before-refresh': ['pending_flush_precedes_received_registration'],
    'flush-deadline': ['flush_allocation_failures_retry_withdrawal_on_the_next_tick'],
    'flush-observer': ['failed_flush_reports_continuous_observer_transitions'],
    'replacement-lv': ['replacement_from_lv_keeps_leave_before_join_at_every_allocation'],
    'replacement-leave-timer': ['replacement_from_lv_keeps_leave_before_join_at_every_allocation'],
    'receive-instance-stop': ['reservation_failure_stops_later_receive_messages'],

    'flush-retry': ['flush_allocation_failures_retry_withdrawal_on_the_next_tick'],
    'replacement-order': ['replacement_allocation_failures_keep_leave_before_join'],
    'receive-stop': ['reservation_failure_stops_later_receive_messages'],
    'policy-mask': ['propagation_obeys_talker_and_listener_policy_masks'],
    'no-policy-reservation': ['applications_without_policy_do_not_reserve_propagation'],

    'changed-in-only': ['changed_values_after_received_leaveall_are_indicated_and_propagated', 'changed_values_after_transmitted_leaveall_are_indicated_and_propagated'],
    'stream-list-boundary': ['unknown_stream_layout_uses_attribute_list_length'],
    'changed-value-rollback': ['changed_value_allocation_failure_preserves_retry'],
    'registrar-rollback': ['timer_allocation_failure_rolls_back_and_retries', 'reservation_failure_is_reported_without_partial_publication'],
    'applicant-rollback': ['reservation_failure_is_reported_without_partial_publication'],
    'leave-timer-retry': ['timer_allocation_failure_rolls_back_and_retries'],
    'receive-map-error': ['reservation_failure_is_reported_without_partial_publication'],
    'reservation-atomicity': ['reservation_failure_is_reported_without_partial_publication'],
    'poll-replay': ['failed_commit_replay_is_retried_by_the_next_poll'],
    'commit-replay': ['retained_ports_replay_propagated_join_and_timer_leave_in_order'],
    'queue-teardown': ['destroy_releases_all_queued_allocations'],
    'zero-attribute-length': ['unknown_generic_messages_reject_zero_attribute_length'],
    'changed-value-propagation': ['changed_values_after_received_leaveall_are_indicated_and_propagated', 'changed_values_after_transmitted_leaveall_are_indicated_and_propagated'],
    'replay-error-retention': ['failed_commit_replay_is_retried_by_the_next_poll'],
    'callback-order': ['propagation_policy_observes_completed_host_indications'],

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
