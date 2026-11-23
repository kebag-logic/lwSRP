### 1x1

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

4 of 94 paths and 7 of 964 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| BIND_RX | 0 | `fixture.bind_rx.if0` (fixture) | 0.190 (0.385) | fits | 0 acmp | 2 | 0 |
| DISCONNECT_TX | 0 | `acmp.disconnect_tx.if0` (acmp-cmd) | 0.088 (0.207) | fits | 0 acmp | 1 | 0 |
| ENTITY_AVAILABLE from its RX_HEAD (H-DISC) | 0 | `acmp.entity_available.if0` (acmp-disc) | 0.080 (0.241) | fits | 0 adp | 1 | 0 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | 0 | `acmp.entity_departing.if0` (acmp-disc) | 0.056 (0.210) | fits | 0 adp | 2 | 0 |
| GET_RX_STATE | 0 | `acmp.get_rx_state.if0` (acmp-cmd) | 0.104 (0.226) | fits | 0 acmp | 1 | 0 |
| GET_TX_CONNECTION, refused NOT_SUPPORTED | 0 | `acmp.get_tx_connection.if0` (acmp-cmd) | 0.087 (0.206) | fits | 0 acmp | 1 | 0 |
| GET_TX_STATE | 0 | `acmp.get_tx_state.if0` (acmp-cmd) | 0.092 (0.215) | fits | 0 acmp | 1 | 0 |
| PROBE_TX, refused TALKER_DEST_MAC_FAIL | 0 | `acmp.probe_tx.if0` (acmp-cmd) | 0.107 (0.227) | fits | 0 acmp | 1 | 0 |
| PROBE_TX_RESPONSE | 0 | `acmp.probe_tx_response.if0` (acmp-cmd) | 0.095 (0.282) | fits | 0 acmp | 1 | 0 |
| TMR_DELAY | 0 | `acmp.tmr_delay.if0` (acmp-noresp) | 0.105 (0.440) | fits | 0 events | 1 | 0 |
| TMR_NO_ADP (H-DISC) | 0 | `acmp.tmr_no_adp.if0` (acmp-disc) | 0.170 (0.474) | fits | 0 events | 1 | 0 |
| TMR_DELAY, or the first TMR_NO_RESP | 0 | `fixture.tmr_no_resp1.if0` (fixture) | 0.192 (0.565) | fits | 0 events | 2 | 0 |
| the second TMR_NO_RESP | 0 | `acmp.tmr_no_resp2.if0` (acmp-noresp) | 0.080 (0.393) | fits | 0 events | 1 | 0 |
| TMR_NO_TK | 0 | `acmp.tmr_no_tk.if0` (acmp-notk) | 0.090 (0.484) | fits | 0 events | 1 | 0 |
| TMR_RETRY | 0 | `acmp.tmr_retry.if0` (acmp-noresp) | 0.137 (0.473) | fits | 0 events | 1 | 0 |
| UNBIND_RX | 0 | `acmp.unbind_rx.if0` (acmp-cmd) | 0.150 (0.367) | fits | 0 acmp | 1 | 0 |
| RCV_ADP_DISCOVER | 0 | `adp.discover.if0` (adp-discover) | 0.050 (0.142) | fits | 0 adp | 2 | 0 |
| GM_CHANGE | 0 | `adp.gm_change.if0` (adp-gm) | 0.021 (0.126) | fits | 0 events | 1 | 0 |
| LINK_DOWN | 0 | `fixture.link_down.if0` (fixture) | 0.022 (0.212) | fits | 0 events | 2 | 0 |
| LINK_UP | 0 | `adp.link_up.if0` (adp-advertise) | 0.023 (0.239) | fits | 0 events | 6 | 0 |
| TMR_ADVERTISE expiry | 0 | `adp.tmr_advertise.if0` (adp-advertise) | 0.123 (0.267) | fits | 0 events | 1 | 0 |
| TMR_DELAY expiry | 0 | `adp.tmr_delay.if0` (adp-advertise) | 0.056 (0.175) | fits | 0 events | 5 | 0 |
| entity_available | 0 | `aecp.entity_available.if0` (aecp) | 0.174 (0.454) | fits | 0 aecp | 1 | 0 |
| get_as_path, refused ENTITY_MISBEHAVING | 0 | `aecp.get_as_path.if0` (aecp) | 0.240 (0.524) | fits | 0 aecp | 1 | 0 |
| get_avb_info, refused ENTITY_MISBEHAVING | 0 | `aecp.get_avb_info.if0` (aecp) | 0.216 (0.499) | fits | 0 aecp | 1 | 0 |
| get_configuration | 0 | `aecp.get_configuration.if0` (aecp) | 0.195 (0.476) | fits | 0 aecp | 1 | 0 |
| get_counters, refused ENTITY_MISBEHAVING | 0 | `aecp.get_counters.if0` (aecp) | 0.244 (0.535) | fits | 0 aecp | 1 | 0 |
| get_name | 0 | `aecp.get_name.if0` (aecp) | 0.204 (0.490) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR held for a token (#917) | 0 | `aecp.held.read_descriptor.if0` (aecp-held) | 5.151 (5.441) | fits | 16 aecp | 1 | 0 |
| lock_entity | 0 | `aecp.lock_entity.if0` (aecp) | 0.244 (0.634) | fits | 0 aecp | 1 | 0 |
| MVU GET_MILAN_INFO | 0 | `aecp.mvu_get_milan_info.if0` (aecp) | 0.126 (0.395) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (312 B) | 0 | `aecp.read_descriptor.t0.i0.c0.if0` (aecp) | 0.264 (0.552) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (106 B) | 0 | `aecp.read_descriptor.t1.i0.c0.if0` (aecp) | 0.214 (0.501) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (86 B) | 0 | `aecp.read_descriptor.t10.i2.c0.if0` (aecp) | 0.204 (0.489) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (72 B) | 0 | `aecp.read_descriptor.t12.i0.c0.if0` (aecp) | 0.222 (0.507) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (452 B) | 0 | `aecp.read_descriptor.t13.i0.c0.if0` (aecp) | 0.229 (0.512) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (20 B) | 0 | `aecp.read_descriptor.t14.i0.c0.if0` (aecp) | 0.218 (0.503) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (20 B) | 0 | `aecp.read_descriptor.t15.i0.c0.if0` (aecp) | 0.219 (0.503) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (148 B) | 0 | `aecp.read_descriptor.t2.i0.c0.if0` (aecp) | 0.224 (0.510) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (90 B) | 0 | `aecp.read_descriptor.t20.i24.c0.if0` (aecp) | 0.198 (0.482) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (113 B) | 0 | `aecp.read_descriptor.t26.i0.c0.if0` (aecp) | 0.235 (0.522) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (82 B) | 0 | `aecp.read_descriptor.t36.i0.c0.if0` (aecp) | 0.203 (0.490) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (146 B) | 0 | `aecp.read_descriptor.t5.i1.c0.if0` (aecp) | 0.233 (0.518) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (146 B) | 0 | `aecp.read_descriptor.t6.i1.c0.if0` (aecp) | 0.209 (0.495) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (102 B) | 0 | `aecp.read_descriptor.t9.i0.c0.if0` (aecp) | 0.223 (0.507) | fits | 0 aecp | 1 | 0 |
| register_unsolicited | 0 | `aecp.register_unsolicited.if0` (aecp) | 0.157 (0.441) | fits | 0 aecp | 1 | 0 |
| set_name | 0 | `aecp.set_name.if0` (aecp) | 0.278 (0.574) | fits | 0 aecp | 1 | 0 |
| unknown_command, refused NOT_IMPLEMENTED | 0 | `aecp.unknown_command.if0` (aecp) | 0.182 (0.462) | fits | 0 aecp | 1 | 0 |
| unlock_entity | 0 | `aecp.unlock_entity.if0` (aecp) | 0.156 (0.356) | fits | 0 aecp | 1 | 0 |
| add_audio_mappings | 0 | `aecp_fanout.add_audio_mappings.if0` (aecp-fanout) | 2.624 (2.936) | fits | 0 aecp | 1 | 0 |
| lock_entity | 0 | `aecp_fanout.lock_entity.if0` (aecp-fanout) | 0.496 (0.768) | fits | 0 aecp | 1 | 0 |
| remove_audio_mappings | 0 | `aecp_fanout.remove_audio_mappings.if0` (aecp-fanout) | 0.509 (0.799) | fits | 0 aecp | 1 | 0 |
| set_clock_source | 0 | `aecp_fanout.set_clock_source.if0` (aecp-fanout) | 0.528 (0.815) | fits | 0 aecp | 1 | 0 |
| set_control_identify_on | 0 | `aecp_fanout.set_control_identify_off.if0` (aecp-fanout) | 0.491 (0.758) | fits | 0 aecp | 2 | 0 |
| set_name | 0 | `aecp_fanout.set_name.if0` (aecp-fanout) | 0.554 (0.854) | fits | 0 aecp | 1 | 0 |
| set_sampling_rate | 0 | `aecp_fanout.set_sampling_rate.if0` (aecp-fanout) | 3.211 (3.507) | fits | 0 aecp | 1 | 0 |
| unlock_entity | 0 | `aecp_fanout.unlock_entity.if0` (aecp-fanout) | 0.390 (0.647) | fits | 0 aecp | 1 | 0 |
| ADD_AUDIO_MAPPINGS of 63 (550 B notice) | 0 | `aecp_long.add_audio_mappings.if0` (aecp-largest-notice) | 2.846 (3.141) | fits | 0 aecp | 1 | 0 |
| COLLISION_INDICES of 63, refused BAD_ARGUMENTS | 0 | `aecp_long.refused.collision_indices.if0` (aecp-largest-notice) | 2.358 (2.694) | fits | 0 aecp | 1 | 0 |
| COLLISION_VALUES of 63, refused BAD_ARGUMENTS | 0 | `aecp_long.refused.collision_values.if0` (aecp-largest-notice) | 3.759 (4.087) | fits | 0 aecp | 1 | 0 |
| CONFLICT_LAST of 63, refused BAD_ARGUMENTS | 0 | `aecp_long.refused.conflict_last.if0` (aecp-largest-notice) | 3.458 (3.777) | fits | 0 aecp | 1 | 0 |
| REMOVE_AUDIO_MAPPINGS of 63 (550 B notice) | 0 | `aecp_long.remove_audio_mappings.if0` (aecp-largest-notice) | 1.440 (1.744) | fits | 0 aecp | 1 | 0 |
| an ACMP command behind a full acmp ring | 0 | `backlog.acmp_command.if0` (backlog) | 4.034 (4.364) | fits | 11 acmp | 1 | 0 |
| an ENTITY_AVAILABLE behind a full adp ring | 0 | `backlog-adp@blank-0.adp_available.if0` (backlog-adp@blank-0) | 4.545 (5.895) | fits | 7 adp | 73 | 0 |
| an ENTITY_AVAILABLE behind the adp ring, its bucket refilling (observed) | 0 | `backlog.adp_available_refill.if0` (backlog-adp-refill) | 0.113 (0.430) | fits | 0 adp | 1 | 0 |
| an event behind 15 others | 0 | `backlog.event.if0` (backlog) | 1.572 (1.962) | fits | 15 events | 1 | 0 |
| a response with 7 frames owed ahead of it | 0 | `backlog.owed.if0` (backlog-owed) | 62.855 (62.993) | MISS ceiling | 7 acmp | 1 | 1 |
| an ACMP command behind the owed input | 0 | `backlog.owed_behind3.if0` (backlog-owed) | 63.512 (63.651) | MISS ceiling | 11 acmp | 4 | 4 |
| SET_NAME fan-out to one registered controller | 0 | `fixture.set_name.if0` (fixture) | 0.320 (0.447) | fits | 0 aecp | 1 | 0 |
| ACMP record, every channel at its refill rate, the longest | 0 | `save-flight.held.acmp.if0` (save-flight) | 2.247 | fits | 11 acmp | 4 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `save-burst.held.adp.if0` (save-burst) | 1.522 | fits | 7 adp | 4 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `save-flight.held.aecp.if0` (save-flight) | 2.948 | fits | 14 aecp | 4 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `save-flight.held.maap.if0` (save-flight) | 2.402 | fits | 6 maap | 4 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `save-starved.held.srp.if0` (save-starved) | 7.893 | fits | 31 srp | 4 | 0 |
| ANNOUNCE (TMR expiry) | 0 | `maap.announce.if0` (maap) | 0.134 (0.420) | fits | 0 events | 1 | 0 |
| conflicting PROBE -> DEFEND | 0 | `maap.defend.if0` (maap) | 0.093 (0.194) | fits | 0 maap | 1 | 0 |
| first PROBE (LINK_UP) | 0 | `maap.probe1.if0` (maap) | 0.100 (0.239) | fits | 0 events | 1 | 0 |
| last PROBE retransmission (TMR expiry) | 0 | `maap.probe4.if0` (maap) | 0.114 (0.420) | fits | 0 events | 1 | 0 |
| PROBE retransmission (TMR expiry) | 0 | `maap.probe3.if0` (maap) | 0.182 (0.447) | fits | 0 events | 2 | 0 |
| an MRPDU its periodic timer owes, the longest | 0 | `save-starved.mrpdu.periodic.if0` (save-starved) | 2.438 | fits | 0 srp | 4 | 0 |
| ACMP record released under the composed load, first | 0 | `backlog.service.acmp.first.if0` (backlog) | 3.944 | fits | 0 acmp | 77 | 0 |
| ACMP record released under the composed load, last | 0 | `backlog-owed.service.acmp.last.if0` (backlog-owed) | 62.059 | MISS ceiling | 11 acmp | 77 | 1 |
| ADP record released under the composed load, first | 0 | `backlog.service.adp.first.if0` (backlog) | 3.988 | fits | 0 adp | 77 | 0 |
| ADP record released under the composed load, last | 0 | `backlog-adp@blank-0.service.adp.last.if0` (backlog-adp@blank-0) | 5.008 | fits | 7 adp | 77 | 0 |
| AECP record released under the composed load, first | 0 | `backlog-adp@program-2.service.aecp.first.if0` (backlog-adp@program-2) | 2.308 | fits | 0 aecp | 77 | 0 |
| AECP record released under the composed load, last | 0 | `backlog-owed.service.aecp.last.if0` (backlog-owed) | 61.817 | MISS ceiling | 15 aecp | 77 | 1 |
| MAAP record released under the composed load, first | 0 | `backlog.service.maap.first.if0` (backlog) | 3.970 | fits | 0 maap | 77 | 0 |
| MAAP record released under the composed load, last | 0 | `backlog-adp@blank-0.service.maap.last.if0` (backlog-adp@blank-0) | 5.046 | fits | 6 maap | 77 | 0 |
| SRP record released under the composed load, first | 0 | `backlog-adp@verify-aged2-6.service.srp.first.if0` (backlog-adp@verify-aged2-6) | 5.882 | fits | 0 srp | 77 | 0 |
| SRP record released under the composed load, last | 0 | `backlog-adp@program-aged2-4.service.srp.last.if0` (backlog-adp@program-aged2-4) | 9.460 | fits | 31 srp | 77 | 0 |
| Domain RX -> declarations (JoinTime wait) | 0 | `srp.domain.if0` (srp) | 0.771 (0.867) | fits | 0 srp | 1 | 0 |
| Listener Ready RX (registrar) | 0 | `srp.listener_ready.if0` (srp) | 0.395 (0.396) | fits | 0 srp | 1 | 0 |
| malformed MRPDU discard | 0 | `fixture.malformed.if0` (fixture) | 0.184 (0.185) | fits | 0 srp | 2 | 0 |
| startup declarations (LINK_UP) | 0 | `srp.startup.if0` (srp) | 0.733 (0.821) | fits | 0 events | 1 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|
| backlog-adp@blank-0 | 0 | 14.846 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-1 | 0 | 14.721 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-2 | 0 | 14.596 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-3 | 0 | 14.471 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-4 | 0 | 14.346 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-5 | 0 | 14.221 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-6 | 0 | 14.096 | 11 | 147,088 (1.471) | yes | - |
| backlog-adp@blank-7 | 0 | 13.951 | 11 | 147,633 (1.476) | yes | - |
| backlog-adp@program-0 | 0 | 11.342 | 11 | 147,576 (1.476) | yes | - |
| backlog-adp@program-1 | 0 | 11.078 | 11 | 148,262 (1.483) | yes | - |
| backlog-adp@program-2 | 0 | 11.944 | 11 | 147,709 (1.477) | yes | - |
| backlog-adp@program-3 | 0 | 11.694 | 11 | 147,709 (1.477) | yes | - |
| backlog-adp@program-4 | 0 | 11.444 | 11 | 147,709 (1.477) | yes | - |
| backlog-adp@program-5 | 1 | 11.038 | 10 | 146,911 (1.469) | yes | - |
| backlog-adp@program-6 | 0 | 9.849 | 9 | 146,785 (1.468) | yes | - |
| backlog-adp@program-7 | 0 | 10.539 | 9 | 147,955 (1.480) | yes | - |
| backlog-adp@verify-0 | 0 | 13.116 | 11 | 146,755 (1.468) | yes | - |
| backlog-adp@verify-1 | 0 | 13.988 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-2 | 0 | 13.863 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-3 | 0 | 13.738 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-4 | 0 | 13.613 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-5 | 0 | 13.488 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-6 | 0 | 13.363 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@verify-7 | 0 | 13.238 | 12 | 148,322 (1.483) | yes | - |
| backlog-adp@blank-aged2-0 | 0 | 13.106 | 11 | 145,944 (1.459) | yes | - |
| backlog-adp@blank-aged2-1 | 0 | 12.278 | 12 | 146,019 (1.460) | yes | - |
| backlog-adp@blank-aged2-2 | 0 | 11.058 | 9 | 145,811 (1.458) | yes | - |
| backlog-adp@blank-aged2-3 | 0 | 11.931 | 9 | 145,811 (1.458) | yes | - |
| backlog-adp@blank-aged2-4 | 0 | 11.927 | 9 | 145,811 (1.458) | yes | - |
| backlog-adp@blank-aged2-5 | 0 | 16.677 | 12 | 145,811 (1.458) | yes | - |
| backlog-adp@blank-aged2-6 | 0 | 15.009 | 12 | 146,142 (1.461) | yes | - |
| backlog-adp@blank-aged2-7 | 0 | 14.064 | 12 | 146,345 (1.463) | yes | - |
| backlog-adp@blank-aged1-0 | 0 | 15.027 | 12 | 147,987 (1.480) | yes | - |
| backlog-adp@blank-aged1-1 | 0 | 13.269 | 12 | 148,152 (1.482) | yes | - |
| backlog-adp@blank-aged1-2 | 0 | 12.254 | 11 | 146,190 (1.462) | yes | - |
| backlog-adp@blank-aged1-3 | 0 | 11.265 | 10 | 148,121 (1.481) | yes | - |
| backlog-adp@blank-aged1-4 | 0 | 11.338 | 10 | 148,081 (1.481) | yes | - |
| backlog-adp@blank-aged1-5 | 0 | 11.140 | 9 | 148,081 (1.481) | yes | - |
| backlog-adp@blank-aged1-6 | 0 | 11.143 | 9 | 148,081 (1.481) | yes | - |
| backlog-adp@blank-aged1-7 | 0 | 11.124 | 9 | 145,766 (1.458) | yes | - |
| backlog-adp@program-aged2-0 | 0 | 11.714 | 10 | 148,016 (1.480) | yes | - |
| backlog-adp@program-aged2-1 | 0 | 10.493 | 10 | 148,181 (1.482) | yes | - |
| backlog-adp@program-aged2-2 | 0 | 10.830 | 11 | 146,086 (1.461) | yes | - |
| backlog-adp@program-aged2-3 | 0 | 10.790 | 10 | 147,964 (1.480) | yes | - |
| backlog-adp@program-aged2-4 | 0 | 10.807 | 10 | 147,924 (1.479) | yes | - |
| backlog-adp@program-aged2-5 | 0 | 10.799 | 10 | 147,924 (1.479) | yes | - |
| backlog-adp@program-aged2-6 | 0 | 10.573 | 9 | 147,924 (1.479) | yes | - |
| backlog-adp@program-aged2-7 | 0 | 10.566 | 9 | 145,870 (1.459) | yes | - |
| backlog-adp@program-aged1-0 | 0 | 11.712 | 10 | 146,578 (1.466) | yes | - |
| backlog-adp@program-aged1-1 | 0 | 10.591 | 10 | 146,578 (1.466) | yes | - |
| backlog-adp@program-aged1-2 | 0 | 10.475 | 9 | 146,578 (1.466) | yes | - |
| backlog-adp@program-aged1-3 | 1 | 10.454 | 8 | 147,723 (1.477) | yes | - |
| backlog-adp@program-aged1-4 | 1 | 11.779 | 10 | 148,087 (1.481) | yes | - |
| backlog-adp@program-aged1-5 | 0 | 10.494 | 9 | 148,016 (1.480) | yes | - |
| backlog-adp@program-aged1-6 | 0 | 10.522 | 9 | 148,016 (1.480) | yes | - |
| backlog-adp@program-aged1-7 | 0 | 10.500 | 9 | 145,766 (1.458) | yes | - |
| backlog-adp@verify-aged2-0 | 0 | 13.165 | 11 | 147,280 (1.473) | yes | - |
| backlog-adp@verify-aged2-1 | 0 | 12.324 | 12 | 147,121 (1.471) | yes | - |
| backlog-adp@verify-aged2-2 | 0 | 10.981 | 8 | 147,989 (1.480) | yes | - |
| backlog-adp@verify-aged2-3 | 0 | 11.980 | 9 | 145,817 (1.458) | yes | - |
| backlog-adp@verify-aged2-4 | 0 | 11.976 | 9 | 145,817 (1.458) | yes | - |
| backlog-adp@verify-aged2-5 | 0 | 16.792 | 12 | 145,817 (1.458) | yes | - |
| backlog-adp@verify-aged2-6 | 0 | 15.103 | 12 | 146,148 (1.461) | yes | - |
| backlog-adp@verify-aged2-7 | 0 | 14.140 | 12 | 146,279 (1.463) | yes | - |
| backlog-adp@verify-aged1-0 | 0 | 15.073 | 12 | 147,993 (1.480) | yes | - |
| backlog-adp@verify-aged1-1 | 0 | 13.349 | 12 | 148,327 (1.483) | yes | - |
| backlog-adp@verify-aged1-2 | 0 | 12.314 | 11 | 146,018 (1.460) | yes | - |
| backlog-adp@verify-aged1-3 | 0 | 11.316 | 10 | 145,870 (1.459) | yes | - |
| backlog-adp@verify-aged1-4 | 0 | 11.388 | 10 | 145,870 (1.459) | yes | - |
| backlog-adp@verify-aged1-5 | 0 | 11.190 | 9 | 145,870 (1.459) | yes | - |
| backlog-adp@verify-aged1-6 | 0 | 11.191 | 9 | 145,870 (1.459) | yes | - |
| backlog-adp@verify-aged1-7 | 0 | 11.164 | 9 | 145,870 (1.459) | yes | - |
| backlog | 0 | 5.335 | 7 | 148,428 (1.484) | yes | - |
| backlog-adp | 0 | 8.833 | 9 | 146,401 (1.464) | yes | - |
| backlog-adp-refill | 0 | 40.692 | 23 | 146,401 (1.464) | yes | - |
| backlog-owed | 0 | 64.066 | 24 | 148,520 (1.485) | yes | - |
| fixture | 0 | 1.243 | 2 | 81,680 (0.817) | yes | - |

Composed maximum over the 4 backlog windows: 148,520 CPU cycles (1.485 ms), backlog-owed.
Over the windows that released their whole load only: 148,520 (1.485 ms), backlog-owed.

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| save-flight | 2830 | 0 | 152,972 (1.530) | fits |
| save-burst | 2579 | 0 | 152,972 (1.530) | fits |
| acmp-notk | 3607 | 0 | 96,838 (0.968) | fits |
| save-second | 61102 | 0 | 47,428 (0.474) | fits |
| backlog-adp@blank-0 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-1 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-2 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-3 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-4 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-5 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-6 | 469 | 0 | 147,088 (1.471) | fits |
| backlog-adp@blank-7 | 469 | 0 | 147,633 (1.476) | fits |
| backlog-adp@program-0 | 477 | 0 | 147,576 (1.476) | fits |
| backlog-adp@program-1 | 477 | 0 | 148,262 (1.483) | fits |
| backlog-adp@program-2 | 477 | 0 | 147,709 (1.477) | fits |
| backlog-adp@program-3 | 477 | 0 | 147,709 (1.477) | fits |
| backlog-adp@program-4 | 477 | 0 | 147,709 (1.477) | fits |
| backlog-adp@program-5 | 477 | 0 | 149,436 (1.494) | fits |
| backlog-adp@program-6 | 477 | 0 | 146,785 (1.468) | fits |
| backlog-adp@program-7 | 477 | 0 | 147,955 (1.480) | fits |
| backlog-adp@verify-0 | 483 | 0 | 146,755 (1.468) | fits |
| backlog-adp@verify-1 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-2 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-3 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-4 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-5 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-6 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@verify-7 | 484 | 0 | 148,322 (1.483) | fits |
| backlog-adp@blank-aged2-0 | 816 | 0 | 145,944 (1.459) | fits |
| backlog-adp@blank-aged2-1 | 827 | 0 | 146,019 (1.460) | fits |
| backlog-adp@blank-aged2-2 | 834 | 0 | 145,811 (1.458) | fits |
| backlog-adp@blank-aged2-3 | 844 | 0 | 145,811 (1.458) | fits |
| backlog-adp@blank-aged2-4 | 854 | 0 | 145,811 (1.458) | fits |
| backlog-adp@blank-aged2-5 | 867 | 0 | 145,811 (1.458) | fits |
| backlog-adp@blank-aged2-6 | 877 | 0 | 146,142 (1.461) | fits |
| backlog-adp@blank-aged2-7 | 887 | 0 | 146,345 (1.463) | fits |
| backlog-adp@blank-aged1-0 | 737 | 0 | 147,987 (1.480) | fits |
| backlog-adp@blank-aged1-1 | 747 | 0 | 148,152 (1.482) | fits |
| backlog-adp@blank-aged1-2 | 756 | 0 | 146,190 (1.462) | fits |
| backlog-adp@blank-aged1-3 | 765 | 0 | 148,121 (1.481) | fits |
| backlog-adp@blank-aged1-4 | 775 | 0 | 148,081 (1.481) | fits |
| backlog-adp@blank-aged1-5 | 784 | 0 | 148,081 (1.481) | fits |
| backlog-adp@blank-aged1-6 | 794 | 0 | 148,081 (1.481) | fits |
| backlog-adp@blank-aged1-7 | 804 | 0 | 145,766 (1.458) | fits |
| backlog-adp@program-aged2-0 | 856 | 0 | 148,016 (1.480) | fits |
| backlog-adp@program-aged2-1 | 866 | 0 | 148,181 (1.482) | fits |
| backlog-adp@program-aged2-2 | 877 | 0 | 146,086 (1.461) | fits |
| backlog-adp@program-aged2-3 | 886 | 0 | 147,964 (1.480) | fits |
| backlog-adp@program-aged2-4 | 896 | 0 | 147,924 (1.479) | fits |
| backlog-adp@program-aged2-5 | 906 | 0 | 147,924 (1.479) | fits |
| backlog-adp@program-aged2-6 | 915 | 0 | 147,924 (1.479) | fits |
| backlog-adp@program-aged2-7 | 925 | 0 | 145,870 (1.459) | fits |
| backlog-adp@program-aged1-0 | 776 | 0 | 146,578 (1.466) | fits |
| backlog-adp@program-aged1-1 | 786 | 0 | 146,578 (1.466) | fits |
| backlog-adp@program-aged1-2 | 795 | 0 | 146,578 (1.466) | fits |
| backlog-adp@program-aged1-3 | 805 | 0 | 147,723 (1.477) | fits |
| backlog-adp@program-aged1-4 | 817 | 0 | 148,087 (1.481) | fits |
| backlog-adp@program-aged1-5 | 825 | 0 | 148,016 (1.480) | fits |
| backlog-adp@program-aged1-6 | 835 | 0 | 148,016 (1.480) | fits |
| backlog-adp@program-aged1-7 | 845 | 0 | 145,766 (1.458) | fits |
| backlog-adp@verify-aged2-0 | 796 | 0 | 147,280 (1.473) | fits |
| backlog-adp@verify-aged2-1 | 807 | 0 | 147,121 (1.471) | fits |
| backlog-adp@verify-aged2-2 | 813 | 0 | 151,733 (1.517) | fits |
| backlog-adp@verify-aged2-3 | 824 | 0 | 145,817 (1.458) | fits |
| backlog-adp@verify-aged2-4 | 834 | 0 | 145,817 (1.458) | fits |
| backlog-adp@verify-aged2-5 | 847 | 0 | 145,817 (1.458) | fits |
| backlog-adp@verify-aged2-6 | 857 | 0 | 146,148 (1.461) | fits |
| backlog-adp@verify-aged2-7 | 867 | 0 | 146,279 (1.463) | fits |
| backlog-adp@verify-aged1-0 | 717 | 0 | 147,993 (1.480) | fits |
| backlog-adp@verify-aged1-1 | 727 | 0 | 148,327 (1.483) | fits |
| backlog-adp@verify-aged1-2 | 736 | 0 | 146,018 (1.460) | fits |
| backlog-adp@verify-aged1-3 | 745 | 0 | 145,870 (1.459) | fits |
| backlog-adp@verify-aged1-4 | 755 | 0 | 145,870 (1.459) | fits |
| backlog-adp@verify-aged1-5 | 764 | 0 | 145,870 (1.459) | fits |
| backlog-adp@verify-aged1-6 | 774 | 0 | 145,870 (1.459) | fits |
| backlog-adp@verify-aged1-7 | 784 | 0 | 145,870 (1.459) | fits |
| adp-advertise | 599 | 0 | 29,728 (0.297) | fits |
| save-held | 1337 | 0 | 152,972 (1.530) | fits |
| save-starved | 32850 | 0 | 152,972 (1.530) | fits |
| acmp-noresp | 2027 | 0 | 94,589 (0.946) | fits |
| save | 610 | 0 | 43,575 (0.436) | fits |
| srp | 290 | 0 | 53,204 (0.532) | fits |
| backlog | 286 | 0 | 148,428 (1.484) | fits |
| backlog-adp | 311 | 0 | 146,401 (1.464) | fits |
| backlog-adp-refill | 325 | 0 | 146,401 (1.464) | fits |
| backlog-owed | 309 | 0 | 148,520 (1.485) | fits |
| acmp-disc | 938 | 0 | 47,691 (0.477) | fits |
| maap | 178 | 0 | 29,728 (0.297) | fits |
| adp-link | 90 | 0 | 33,880 (0.339) | fits |
| adp-gm | 89 | 0 | 29,728 (0.297) | fits |
| adp-discover | 89 | 0 | 29,728 (0.297) | fits |
| control | 89 | 0 | 29,728 (0.297) | fits |
| aecp-fanout | 112 | 0 | 67,644 (0.676) | fits |
| acmp-cmd | 87 | 0 | 38,157 (0.382) | fits |
| aecp | 114 | 0 | 43,922 (0.439) | fits |
| aecp-largest-notice | 107 | 0 | 145,517 (1.455) | fits |
| aecp-held | 109 | 0 | 38,481 (0.385) | fits |
| datapath-events | 119 | 0 | 29,728 (0.297) | fits |
| fixture | 159 | 0 | 81,680 (0.817) | fits |

Aged windows, opened with THE STEP's age at its limit or one short of it (save_window.aged_window): the aged steps among the window's records and after them (start after the window opened, CPU time, the step) and the window's tightest row:

| Group | Age at opening | Aged steps among its records | After them | Tightest row | ms (budget) | Margin ms |
|---|---:|---|---|---|---:|---:|
| backlog-adp@blank-aged2-0 | 2 | none | none | `backlog-adp@blank-aged2-0.service.srp.last.if0` | 8.367 (20) | 11.633 |
| backlog-adp@blank-aged2-1 | 2 | none | +8.560 ms, 76,522 (0.765 ms), read-back | `backlog-adp@blank-aged2-1.service.srp.last.if0` | 8.358 (20) | 11.642 |
| backlog-adp@blank-aged2-2 | 2 | none | +8.506 ms, 77,083 (0.771 ms), read-back | `backlog-adp@blank-aged2-2.service.srp.last.if0` | 8.469 (20) | 11.531 |
| backlog-adp@blank-aged2-3 | 2 | +6.764 ms, 77,083 (0.771 ms), read-back | none | `backlog-adp@blank-aged2-3.service.srp.last.if0` | 9.240 (20) | 10.760 |
| backlog-adp@blank-aged2-4 | 2 | +5.890 ms, 77,083 (0.771 ms), read-back | none | `backlog-adp@blank-aged2-4.service.srp.last.if0` | 9.236 (20) | 10.764 |
| backlog-adp@blank-aged2-5 | 2 | +5.084 ms, 77,156 (0.772 ms), read-back | none | `backlog-adp@blank-aged2-5.service.srp.last.if0` | 9.205 (20) | 10.795 |
| backlog-adp@blank-aged2-6 | 2 | +4.294 ms, 77,036 (0.770 ms), read-back | none | `backlog-adp@blank-aged2-6.service.srp.last.if0` | 9.226 (20) | 10.774 |
| backlog-adp@blank-aged2-7 | 2 | +3.077 ms, 76,574 (0.766 ms), read-back | none | `backlog-adp@blank-aged2-7.service.srp.last.if0` | 9.179 (20) | 10.821 |
| backlog-adp@blank-aged1-0 | 1 | none | none | `backlog-adp@blank-aged1-0.service.srp.last.if0` | 8.372 (20) | 11.628 |
| backlog-adp@blank-aged1-1 | 1 | none | none | `backlog-adp@blank-aged1-1.service.srp.last.if0` | 8.367 (20) | 11.633 |
| backlog-adp@blank-aged1-2 | 1 | none | none | `backlog-adp@blank-aged1-2.service.srp.last.if0` | 8.380 (20) | 11.620 |
| backlog-adp@blank-aged1-3 | 1 | none | none | `backlog-adp@blank-aged1-3.service.srp.last.if0` | 8.288 (20) | 11.712 |
| backlog-adp@blank-aged1-4 | 1 | none | none | `backlog-adp@blank-aged1-4.service.srp.last.if0` | 8.641 (20) | 11.359 |
| backlog-adp@blank-aged1-5 | 1 | none | none | `backlog-adp@blank-aged1-5.service.srp.last.if0` | 8.442 (20) | 11.558 |
| backlog-adp@blank-aged1-6 | 1 | none | none | `backlog-adp@blank-aged1-6.service.srp.last.if0` | 8.445 (20) | 11.555 |
| backlog-adp@blank-aged1-7 | 1 | none | none | `backlog-adp@blank-aged1-7.service.srp.last.if0` | 8.422 (20) | 11.578 |
| backlog-adp@program-aged2-0 | 2 | none | none | `backlog-adp@program-aged2-0.service.srp.last.if0` | 8.350 (20) | 11.650 |
| backlog-adp@program-aged2-1 | 2 | none | +8.546 ms, 80,819 (0.808 ms), issue | `backlog-adp@program-aged2-1.service.srp.last.if0` | 8.345 (20) | 11.655 |
| backlog-adp@program-aged2-2 | 2 | none | +8.393 ms, 81,217 (0.812 ms), issue | `backlog-adp@program-aged2-2.service.srp.last.if0` | 8.356 (20) | 11.644 |
| backlog-adp@program-aged2-3 | 2 | +6.565 ms, 81,217 (0.812 ms), issue | none | `backlog-adp@program-aged2-3.service.srp.last.if0` | 9.444 (20) | 10.556 |
| backlog-adp@program-aged2-4 | 2 | +5.691 ms, 81,217 (0.812 ms), issue | none | `backlog-adp@program-aged2-4.service.srp.last.if0` | 9.460 (20) | 10.540 |
| backlog-adp@program-aged2-5 | 2 | +4.904 ms, 81,201 (0.812 ms), issue | none | `backlog-adp@program-aged2-5.service.srp.last.if0` | 9.452 (20) | 10.548 |
| backlog-adp@program-aged2-6 | 2 | none | none | `backlog-adp@program-aged2-6.service.srp.last.if0` | 9.227 (20) | 10.773 |
| backlog-adp@program-aged2-7 | 2 | none | none | `backlog-adp@program-aged2-7.service.srp.last.if0` | 9.213 (20) | 10.787 |
| backlog-adp@program-aged1-0 | 1 | none | none | `backlog-adp@program-aged1-0.service.srp.last.if0` | 8.351 (20) | 11.649 |
| backlog-adp@program-aged1-1 | 1 | none | none | `backlog-adp@program-aged1-1.service.srp.last.if0` | 8.345 (20) | 11.655 |
| backlog-adp@program-aged1-2 | 1 | none | none | `backlog-adp@program-aged1-2.service.srp.last.if0` | 8.379 (20) | 11.621 |
| backlog-adp@program-aged1-3 | 1 | none | none | `backlog-adp@program-aged1-3.service.srp.last.if0` | 8.355 (20) | 11.645 |
| backlog-adp@program-aged1-4 | 1 | none | none | `backlog-adp@program-aged1-4.service.srp.last.if0` | 8.324 (20) | 11.676 |
| backlog-adp@program-aged1-5 | 1 | none | none | `backlog-adp@program-aged1-5.service.srp.last.if0` | 8.399 (20) | 11.601 |
| backlog-adp@program-aged1-6 | 1 | none | none | `backlog-adp@program-aged1-6.service.srp.last.if0` | 8.427 (20) | 11.573 |
| backlog-adp@program-aged1-7 | 1 | none | none | `backlog-adp@program-aged1-7.service.srp.last.if0` | 8.405 (20) | 11.595 |
| backlog-adp@verify-aged2-0 | 2 | none | none | `backlog-adp@verify-aged2-0.service.srp.last.if0` | 8.365 (20) | 11.635 |
| backlog-adp@verify-aged2-1 | 2 | none | +8.559 ms, 77,365 (0.774 ms), read-back | `backlog-adp@verify-aged2-1.service.srp.last.if0` | 8.357 (20) | 11.643 |
| backlog-adp@verify-aged2-2 | 2 | none | +8.395 ms, 77,955 (0.780 ms), read-back | `backlog-adp@verify-aged2-2.service.srp.last.if0` | 8.358 (20) | 11.642 |
| backlog-adp@verify-aged2-3 | 2 | +6.766 ms, 77,955 (0.780 ms), read-back | none | `backlog-adp@verify-aged2-3.service.srp.last.if0` | 9.251 (20) | 10.749 |
| backlog-adp@verify-aged2-4 | 2 | +5.892 ms, 77,955 (0.780 ms), read-back | none | `backlog-adp@verify-aged2-4.service.srp.last.if0` | 9.248 (20) | 10.752 |
| backlog-adp@verify-aged2-5 | 2 | +5.086 ms, 78,028 (0.780 ms), read-back | none | `backlog-adp@verify-aged2-5.service.srp.last.if0` | 9.221 (20) | 10.779 |
| backlog-adp@verify-aged2-6 | 2 | +4.298 ms, 77,879 (0.779 ms), read-back | none | `backlog-adp@verify-aged2-6.service.srp.last.if0` | 9.244 (20) | 10.756 |
| backlog-adp@verify-aged2-7 | 2 | +3.080 ms, 77,581 (0.776 ms), read-back | none | `backlog-adp@verify-aged2-7.service.srp.last.if0` | 9.191 (20) | 10.809 |
| backlog-adp@verify-aged1-0 | 1 | none | none | `backlog-adp@verify-aged1-0.service.srp.last.if0` | 8.391 (20) | 11.609 |
| backlog-adp@verify-aged1-1 | 1 | none | none | `backlog-adp@verify-aged1-1.service.srp.last.if0` | 8.387 (20) | 11.613 |
| backlog-adp@verify-aged1-2 | 1 | none | none | `backlog-adp@verify-aged1-2.service.srp.last.if0` | 8.395 (20) | 11.605 |
| backlog-adp@verify-aged1-3 | 1 | none | none | `backlog-adp@verify-aged1-3.service.srp.last.if0` | 8.306 (20) | 11.694 |
| backlog-adp@verify-aged1-4 | 1 | none | none | `backlog-adp@verify-aged1-4.service.srp.last.if0` | 8.659 (20) | 11.341 |
| backlog-adp@verify-aged1-5 | 1 | none | none | `backlog-adp@verify-aged1-5.service.srp.last.if0` | 8.460 (20) | 11.540 |
| backlog-adp@verify-aged1-6 | 1 | none | none | `backlog-adp@verify-aged1-6.service.srp.last.if0` | 8.461 (20) | 11.539 |
| backlog-adp@verify-aged1-7 | 1 | none | none | `backlog-adp@verify-aged1-7.service.srp.last.if0` | 8.430 (20) | 11.570 |

Least margin over the aged windows: 10.540 ms, `backlog-adp@program-aged2-4.service.srp.last.if0` at 9.460 ms.

Saves, from the change to durable (save_window.bound_ms: the first-dirty window, or the rest of a save in flight, then each step at most CTRL_LOOP_STEP_AGE + 1 ticks after the one before):

| Group | Durable ms | Stated worst case ms | Steps | Save in flight, records | Longest gap between flash steps, ms | Grandmaster flood | Verdict |
|---|---:|---:|---:|---:|---:|---|---|
| save-second | 6030.387 | 6,070 | 102 | 2 | 30.777 | yes | within |
| save-held | 1085.869 | 4,070 | 102 | - | 20.757 | no | within |
| save-starved | 4048.236 | 4,070 | 102 | - | 31.306 | yes | within |
| save | 1077.320 | 4,070 | 102 | - | 24.737 | no | within |

Names from their response to durable (save_burst.py; #920, #665's ruling of 2026-11-15, item 1):

| Group | Names | Latest, ms (name) | Target ms | Saves | Not durable | Over | At the cut, or the next save | Verdict |
|---|---:|---:|---:|---:|---|---|---|---|
| save-flight | 1 | 150.298 (0) | 5,000 | 2 | - | - | 19 steps (want 19), 6.219 ms | within |
| save-burst | 39 | 1099.116 (0) | 5,000 | 1 | - | - | sequence 1, 0 missing | within |

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| save-flight | 1554 | 92,768 (0.928) | 78,178 (0.782) |
| save-burst | 1479 | 92,121 (0.921) | 78,385 (0.784) |
| acmp-notk | 1158 | 96,838 (0.968) | 78,830 (0.788) |
| save-second | 520 | 80,367 (0.804) | 78,386 (0.784) |
| backlog-adp@blank-0 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-1 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-2 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-3 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-4 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-5 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-6 | 345 | 96,181 (0.962) | 76,153 (0.762) |
| backlog-adp@blank-7 | 345 | 96,451 (0.965) | 76,153 (0.762) |
| backlog-adp@program-0 | 373 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@program-1 | 373 | 94,923 (0.949) | 78,966 (0.790) |
| backlog-adp@program-2 | 375 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@program-3 | 375 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@program-4 | 375 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@program-5 | 375 | 100,862 (1.009) | 78,551 (0.786) |
| backlog-adp@program-6 | 373 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@program-7 | 374 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@verify-0 | 399 | 97,151 (0.972) | 78,319 (0.783) |
| backlog-adp@verify-1 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-2 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-3 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-4 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-5 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-6 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@verify-7 | 400 | 97,675 (0.977) | 78,319 (0.783) |
| backlog-adp@blank-aged2-0 | 341 | 96,290 (0.963) | 76,514 (0.765) |
| backlog-adp@blank-aged2-1 | 340 | 91,673 (0.917) | 75,892 (0.759) |
| backlog-adp@blank-aged2-2 | 339 | 90,251 (0.903) | 76,061 (0.761) |
| backlog-adp@blank-aged2-3 | 340 | 89,640 (0.896) | 76,061 (0.761) |
| backlog-adp@blank-aged2-4 | 340 | 89,640 (0.896) | 76,061 (0.761) |
| backlog-adp@blank-aged2-5 | 345 | 95,707 (0.957) | 76,061 (0.761) |
| backlog-adp@blank-aged2-6 | 343 | 91,692 (0.917) | 75,971 (0.760) |
| backlog-adp@blank-aged2-7 | 342 | 88,596 (0.886) | 76,009 (0.760) |
| backlog-adp@blank-aged1-0 | 343 | 91,708 (0.917) | 76,514 (0.765) |
| backlog-adp@blank-aged1-1 | 341 | 91,701 (0.917) | 76,435 (0.764) |
| backlog-adp@blank-aged1-2 | 340 | 91,701 (0.917) | 76,514 (0.765) |
| backlog-adp@blank-aged1-3 | 339 | 89,022 (0.890) | 76,435 (0.764) |
| backlog-adp@blank-aged1-4 | 339 | 90,255 (0.903) | 76,514 (0.765) |
| backlog-adp@blank-aged1-5 | 339 | 90,243 (0.902) | 76,514 (0.765) |
| backlog-adp@blank-aged1-6 | 339 | 90,314 (0.903) | 76,514 (0.765) |
| backlog-adp@blank-aged1-7 | 339 | 90,663 (0.907) | 76,514 (0.765) |
| backlog-adp@program-aged2-0 | 370 | 94,293 (0.943) | 78,966 (0.790) |
| backlog-adp@program-aged2-1 | 368 | 94,288 (0.943) | 78,562 (0.786) |
| backlog-adp@program-aged2-2 | 369 | 94,288 (0.943) | 78,567 (0.786) |
| backlog-adp@program-aged2-3 | 369 | 94,288 (0.943) | 78,567 (0.786) |
| backlog-adp@program-aged2-4 | 369 | 94,288 (0.943) | 78,567 (0.786) |
| backlog-adp@program-aged2-5 | 369 | 94,288 (0.943) | 78,443 (0.784) |
| backlog-adp@program-aged2-6 | 369 | 94,288 (0.943) | 78,603 (0.786) |
| backlog-adp@program-aged2-7 | 369 | 94,288 (0.943) | 78,834 (0.788) |
| backlog-adp@program-aged1-0 | 370 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@program-aged1-1 | 368 | 94,288 (0.943) | 78,961 (0.790) |
| backlog-adp@program-aged1-2 | 368 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@program-aged1-3 | 368 | 94,631 (0.946) | 78,966 (0.790) |
| backlog-adp@program-aged1-4 | 370 | 94,793 (0.948) | 78,966 (0.790) |
| backlog-adp@program-aged1-5 | 368 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@program-aged1-6 | 368 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@program-aged1-7 | 368 | 94,288 (0.943) | 78,966 (0.790) |
| backlog-adp@verify-aged2-0 | 400 | 97,494 (0.975) | 78,319 (0.783) |
| backlog-adp@verify-aged2-1 | 399 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged2-2 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged2-3 | 399 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged2-4 | 399 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged2-5 | 404 | 97,210 (0.972) | 78,319 (0.783) |
| backlog-adp@verify-aged2-6 | 402 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged2-7 | 401 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-0 | 402 | 96,906 (0.969) | 78,319 (0.783) |
| backlog-adp@verify-aged1-1 | 400 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-2 | 399 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-3 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-4 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-5 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-6 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| backlog-adp@verify-aged1-7 | 398 | 94,288 (0.943) | 78,319 (0.783) |
| adp-advertise | 578 | 21,505 (0.215) | 2,796 (0.028) |
| save-held | 816 | 92,799 (0.928) | 78,374 (0.784) |
| save-starved | 418 | 80,993 (0.810) | 78,562 (0.786) |
| acmp-noresp | 708 | 95,910 (0.959) | 78,830 (0.788) |
| save | 680 | 92,108 (0.921) | 78,300 (0.783) |
| srp | 271 | 21,505 (0.215) | 2,796 (0.028) |
| backlog | 265 | 21,505 (0.215) | 2,796 (0.028) |
| backlog-adp | 271 | 21,505 (0.215) | 2,796 (0.028) |
| backlog-adp-refill | 274 | 21,505 (0.215) | 2,796 (0.028) |
| backlog-owed | 276 | 21,505 (0.215) | 2,796 (0.028) |
| acmp-disc | 398 | 95,786 (0.958) | 78,830 (0.788) |
| maap | 165 | 21,262 (0.213) | 2,796 (0.028) |
| adp-link | 80 | 21,262 (0.213) | 2,796 (0.028) |
| adp-gm | 80 | 21,262 (0.213) | 2,796 (0.028) |
| adp-discover | 80 | 21,262 (0.213) | 2,796 (0.028) |
| control | 80 | 21,262 (0.213) | 2,796 (0.028) |
| aecp-fanout | 80 | 21,262 (0.213) | 2,796 (0.028) |
| acmp-cmd | 65 | 21,262 (0.213) | 2,796 (0.028) |
| aecp | 80 | 21,262 (0.213) | 3,952 (0.040) |
| aecp-largest-notice | 78 | 21,262 (0.213) | 2,796 (0.028) |
| aecp-held | 98 | 21,262 (0.213) | 2,796 (0.028) |
| datapath-events | 70 | 21,262 (0.213) | 2,796 (0.028) |
| fixture | 54 | 15,498 (0.155) | 2,796 (0.028) |

Longest pass that carries a step: 100,862 CPU cycles (1.009 ms), backlog-adp@program-5; longest step: 78,966 (0.790 ms), backlog-adp@program-1.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| ADP record, every channel at its refill rate, the longest | `save-flight.held.adp.if0` | 152,032 | 1.520 | 20 | 200 | fits | 152,972 | 256 | 0.372 |
| ACMP record, every channel at its refill rate, the longest | `save-flight.held.acmp.if0` | 224,694 | 2.247 | 20 | 20 | fits | 92,799 | 81 | 0.669 |
| AECP record, every channel at its refill rate, the longest | `save-flight.held.aecp.if0` | 294,783 | 2.948 | 20 | 24 | fits | 63,490 | 44 | 0.465 |
| MAAP record, every channel at its refill rate, the longest | `save-flight.held.maap.if0` | 240,231 | 2.402 | 20 | 50 | fits | 107,086 | 211 | 0.328 |
| SRP record, every channel at its refill rate, the longest | `save-flight.held.srp.if0` | 763,044 | 7.630 | 20 | 20 | fits | 33,624 | 18 | 0.837 |
| an MRPDU its periodic timer owes, the longest | `save-flight.mrpdu.periodic.if0` | 82,743 | 0.827 | 49 | 49 | fits | 0 | - | 0.000 |
| ADP record, every channel at its refill rate, the longest | `save-burst.held.adp.if0` | 152,163 | 1.522 | 20 | 200 | fits | 152,972 | 256 | 0.372 |
| ACMP record, every channel at its refill rate, the longest | `save-burst.held.acmp.if0` | 207,218 | 2.072 | 20 | 20 | fits | 135,192 | 264 | 0.205 |
| AECP record, every channel at its refill rate, the longest | `save-burst.held.aecp.if0` | 144,335 | 1.443 | 20 | 24 | fits | 85,470 | 34 | 0.765 |
| MAAP record, every channel at its refill rate, the longest | `save-burst.held.maap.if0` | 167,743 | 1.677 | 20 | 50 | fits | 135,192 | 264 | 0.205 |
| SRP record, every channel at its refill rate, the longest | `save-burst.held.srp.if0` | 665,541 | 6.655 | 20 | 20 | fits | 84,560 | 39 | 0.711 |
| an MRPDU its periodic timer owes, the longest | `save-burst.mrpdu.periodic.if0` | 220,638 | 2.206 | 49 | 49 | fits | 0 | - | 0.000 |
| TMR_NO_TK | `acmp.tmr_no_tk.if0` | 8,957 | 0.090 | 20 | 20 | fits | 30,064 | 19 (14) | 0.874 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-0.adp_available.if0` | 454,534 | 4.545 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-0.service.adp.first.if0` | 370,402 | 3.704 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-0.service.adp.last.if0` | 500,837 | 5.008 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-0.service.acmp.first.if0` | 371,326 | 3.713 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-0.service.acmp.last.if0` | 501,541 | 5.015 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-0.service.aecp.first.if0` | 229,736 | 2.297 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-0.service.aecp.last.if0` | 373,976 | 3.740 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-0.service.maap.first.if0` | 373,910 | 3.739 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-0.service.maap.last.if0` | 504,565 | 5.046 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-0.service.srp.first.if0` | 586,777 | 5.868 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-0.service.srp.last.if0` | 922,971 | 9.230 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-1.adp_available.if0` | 442,034 | 4.420 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-1.service.adp.first.if0` | 357,902 | 3.579 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-1.service.adp.last.if0` | 488,337 | 4.883 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-1.service.acmp.first.if0` | 358,826 | 3.588 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-1.service.acmp.last.if0` | 489,041 | 4.890 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-1.service.aecp.first.if0` | 217,236 | 2.172 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-1.service.aecp.last.if0` | 361,476 | 3.615 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-1.service.maap.first.if0` | 361,410 | 3.614 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-1.service.maap.last.if0` | 492,065 | 4.921 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-1.service.srp.first.if0` | 574,277 | 5.743 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-1.service.srp.last.if0` | 910,471 | 9.105 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-2.adp_available.if0` | 429,534 | 4.295 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-2.service.adp.first.if0` | 345,402 | 3.454 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-2.service.adp.last.if0` | 475,837 | 4.758 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-2.service.acmp.first.if0` | 346,326 | 3.463 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-2.service.acmp.last.if0` | 476,541 | 4.765 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-2.service.aecp.first.if0` | 204,736 | 2.047 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-2.service.aecp.last.if0` | 348,976 | 3.490 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-2.service.maap.first.if0` | 348,910 | 3.489 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-2.service.maap.last.if0` | 479,565 | 4.796 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-2.service.srp.first.if0` | 561,777 | 5.618 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-2.service.srp.last.if0` | 897,971 | 8.980 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-3.adp_available.if0` | 417,034 | 4.170 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-3.service.adp.first.if0` | 332,902 | 3.329 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-3.service.adp.last.if0` | 463,337 | 4.633 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-3.service.acmp.first.if0` | 333,826 | 3.338 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-3.service.acmp.last.if0` | 464,041 | 4.640 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-3.service.aecp.first.if0` | 192,236 | 1.922 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-3.service.aecp.last.if0` | 336,476 | 3.365 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-3.service.maap.first.if0` | 336,410 | 3.364 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-3.service.maap.last.if0` | 467,065 | 4.671 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-3.service.srp.first.if0` | 549,277 | 5.493 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-3.service.srp.last.if0` | 885,471 | 8.855 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-4.adp_available.if0` | 404,534 | 4.045 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-4.service.adp.first.if0` | 320,402 | 3.204 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-4.service.adp.last.if0` | 450,837 | 4.508 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-4.service.acmp.first.if0` | 321,326 | 3.213 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-4.service.acmp.last.if0` | 451,541 | 4.515 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-4.service.aecp.first.if0` | 179,736 | 1.797 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-4.service.aecp.last.if0` | 323,976 | 3.240 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-4.service.maap.first.if0` | 323,910 | 3.239 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-4.service.maap.last.if0` | 454,565 | 4.546 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-4.service.srp.first.if0` | 536,777 | 5.368 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-4.service.srp.last.if0` | 872,971 | 8.730 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-5.adp_available.if0` | 392,034 | 3.920 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-5.service.adp.first.if0` | 307,902 | 3.079 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-5.service.adp.last.if0` | 438,337 | 4.383 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-5.service.acmp.first.if0` | 308,826 | 3.088 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-5.service.acmp.last.if0` | 439,041 | 4.390 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-5.service.aecp.first.if0` | 167,236 | 1.672 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-5.service.aecp.last.if0` | 311,476 | 3.115 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-5.service.maap.first.if0` | 311,410 | 3.114 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-5.service.maap.last.if0` | 442,065 | 4.421 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-5.service.srp.first.if0` | 524,277 | 5.243 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-5.service.srp.last.if0` | 860,471 | 8.605 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-6.adp_available.if0` | 379,534 | 3.795 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| ADP record released under the composed load, first | `backlog-adp@blank-6.service.adp.first.if0` | 295,402 | 2.954 | 20 | 200 | fits | 145,230 | 205 | 0.406 |
| ADP record released under the composed load, last | `backlog-adp@blank-6.service.adp.last.if0` | 425,837 | 4.258 | 20 | 200 | fits | 119,262 | 205 | 0.327 |
| ACMP record released under the composed load, first | `backlog-adp@blank-6.service.acmp.first.if0` | 296,326 | 2.963 | 20 | 20 | fits | 145,230 | 205 | 0.406 |
| ACMP record released under the composed load, last | `backlog-adp@blank-6.service.acmp.last.if0` | 426,541 | 4.265 | 20 | 20 | fits | 119,262 | 205 | 0.327 |
| AECP record released under the composed load, first | `backlog-adp@blank-6.service.aecp.first.if0` | 154,736 | 1.547 | 20 | 24 | fits | 147,088 | 145 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-6.service.aecp.last.if0` | 298,976 | 2.990 | 20 | 24 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, first | `backlog-adp@blank-6.service.maap.first.if0` | 298,910 | 2.989 | 20 | 50 | fits | 145,230 | 205 | 0.406 |
| MAAP record released under the composed load, last | `backlog-adp@blank-6.service.maap.last.if0` | 429,565 | 4.296 | 20 | 50 | fits | 119,262 | 205 | 0.327 |
| SRP record released under the composed load, first | `backlog-adp@blank-6.service.srp.first.if0` | 511,777 | 5.118 | 20 | 20 | fits | 82,278 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-6.service.srp.last.if0` | 847,971 | 8.480 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-7.adp_available.if0` | 446,457 | 4.465 | 20 | 20 | fits | 116,150 | 202 | 0.293 |
| ADP record released under the composed load, first | `backlog-adp@blank-7.service.adp.first.if0` | 383,606 | 3.836 | 20 | 200 | fits | 147,633 | 208 | 0.412 |
| ADP record released under the composed load, last | `backlog-adp@blank-7.service.adp.last.if0` | 499,140 | 4.991 | 20 | 200 | fits | 116,150 | 202 | 0.293 |
| ACMP record released under the composed load, first | `backlog-adp@blank-7.service.acmp.first.if0` | 384,530 | 3.845 | 20 | 20 | fits | 147,633 | 208 | 0.412 |
| ACMP record released under the composed load, last | `backlog-adp@blank-7.service.acmp.last.if0` | 499,844 | 4.998 | 20 | 20 | fits | 116,150 | 202 | 0.293 |
| AECP record released under the composed load, first | `backlog-adp@blank-7.service.aecp.first.if0` | 230,227 | 2.302 | 20 | 24 | fits | 147,266 | 146 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@blank-7.service.aecp.last.if0` | 387,180 | 3.872 | 20 | 24 | fits | 147,633 | 208 | 0.412 |
| MAAP record released under the composed load, first | `backlog-adp@blank-7.service.maap.first.if0` | 387,114 | 3.871 | 20 | 50 | fits | 147,633 | 208 | 0.412 |
| MAAP record released under the composed load, last | `backlog-adp@blank-7.service.maap.last.if0` | 502,868 | 5.029 | 20 | 50 | fits | 116,150 | 202 | 0.293 |
| SRP record released under the composed load, first | `backlog-adp@blank-7.service.srp.first.if0` | 585,010 | 5.850 | 20 | 20 | fits | 82,208 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-7.service.srp.last.if0` | 921,186 | 9.212 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-0.adp_available.if0` | 377,487 | 3.775 | 20 | 20 | fits | 112,719 | 193 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@program-0.service.adp.first.if0` | 319,221 | 3.192 | 20 | 200 | fits | 144,056 | 212 | 0.394 |
| ADP record released under the composed load, last | `backlog-adp@program-0.service.adp.last.if0` | 431,324 | 4.313 | 20 | 200 | fits | 112,719 | 193 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@program-0.service.acmp.first.if0` | 320,145 | 3.201 | 20 | 20 | fits | 144,056 | 212 | 0.394 |
| ACMP record released under the composed load, last | `backlog-adp@program-0.service.acmp.last.if0` | 432,028 | 4.320 | 20 | 20 | fits | 112,719 | 193 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@program-0.service.aecp.first.if0` | 169,753 | 1.698 | 20 | 24 | fits | 147,576 | 146 | 0.417 |
| AECP record released under the composed load, last | `backlog-adp@program-0.service.aecp.last.if0` | 322,795 | 3.228 | 20 | 24 | fits | 144,056 | 212 | 0.394 |
| MAAP record released under the composed load, first | `backlog-adp@program-0.service.maap.first.if0` | 322,729 | 3.227 | 20 | 50 | fits | 144,056 | 212 | 0.394 |
| MAAP record released under the composed load, last | `backlog-adp@program-0.service.maap.last.if0` | 435,052 | 4.351 | 20 | 50 | fits | 112,719 | 193 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@program-0.service.srp.first.if0` | 517,201 | 5.172 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-0.service.srp.last.if0` | 857,556 | 8.576 | 20 | 20 | fits | 86,687 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-1.adp_available.if0` | 377,331 | 3.773 | 20 | 20 | fits | 106,785 | 187 | 0.284 |
| ADP record released under the composed load, first | `backlog-adp@program-1.service.adp.first.if0` | 316,714 | 3.167 | 20 | 200 | fits | 148,262 | 215 | 0.390 |
| ADP record released under the composed load, last | `backlog-adp@program-1.service.adp.last.if0` | 422,883 | 4.229 | 20 | 200 | fits | 106,785 | 187 | 0.284 |
| ACMP record released under the composed load, first | `backlog-adp@program-1.service.acmp.first.if0` | 317,638 | 3.176 | 20 | 20 | fits | 148,262 | 215 | 0.390 |
| ACMP record released under the composed load, last | `backlog-adp@program-1.service.acmp.last.if0` | 423,587 | 4.236 | 20 | 20 | fits | 106,785 | 187 | 0.284 |
| AECP record released under the composed load, first | `backlog-adp@program-1.service.aecp.first.if0` | 162,973 | 1.630 | 20 | 24 | fits | 147,469 | 146 | 0.419 |
| AECP record released under the composed load, last | `backlog-adp@program-1.service.aecp.last.if0` | 320,288 | 3.203 | 20 | 24 | fits | 148,262 | 215 | 0.390 |
| MAAP record released under the composed load, first | `backlog-adp@program-1.service.maap.first.if0` | 320,222 | 3.202 | 20 | 50 | fits | 148,262 | 215 | 0.390 |
| MAAP record released under the composed load, last | `backlog-adp@program-1.service.maap.last.if0` | 426,611 | 4.266 | 20 | 50 | fits | 106,785 | 187 | 0.284 |
| SRP record released under the composed load, first | `backlog-adp@program-1.service.srp.first.if0` | 508,760 | 5.088 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-1.service.srp.last.if0` | 849,167 | 8.492 | 20 | 20 | fits | 86,700 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-2.adp_available.if0` | 438,959 | 4.390 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| ADP record released under the composed load, first | `backlog-adp@program-2.service.adp.first.if0` | 383,371 | 3.834 | 20 | 200 | fits | 147,256 | 230 | 0.385 |
| ADP record released under the composed load, last | `backlog-adp@program-2.service.adp.last.if0` | 491,593 | 4.916 | 20 | 200 | fits | 108,838 | 175 | 0.274 |
| ACMP record released under the composed load, first | `backlog-adp@program-2.service.acmp.first.if0` | 384,295 | 3.843 | 20 | 20 | fits | 147,256 | 230 | 0.385 |
| ACMP record released under the composed load, last | `backlog-adp@program-2.service.acmp.last.if0` | 492,297 | 4.923 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| AECP record released under the composed load, first | `backlog-adp@program-2.service.aecp.first.if0` | 230,769 | 2.308 | 20 | 24 | fits | 147,709 | 146 | 0.416 |
| AECP record released under the composed load, last | `backlog-adp@program-2.service.aecp.last.if0` | 386,945 | 3.869 | 20 | 24 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, first | `backlog-adp@program-2.service.maap.first.if0` | 386,879 | 3.869 | 20 | 50 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, last | `backlog-adp@program-2.service.maap.last.if0` | 495,321 | 4.953 | 20 | 50 | fits | 108,838 | 175 | 0.274 |
| SRP record released under the composed load, first | `backlog-adp@program-2.service.srp.first.if0` | 581,817 | 5.818 | 20 | 20 | fits | 86,562 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-2.service.srp.last.if0` | 917,993 | 9.180 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-3.adp_available.if0` | 413,959 | 4.140 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| ADP record released under the composed load, first | `backlog-adp@program-3.service.adp.first.if0` | 358,371 | 3.584 | 20 | 200 | fits | 147,256 | 230 | 0.385 |
| ADP record released under the composed load, last | `backlog-adp@program-3.service.adp.last.if0` | 466,593 | 4.666 | 20 | 200 | fits | 108,838 | 175 | 0.274 |
| ACMP record released under the composed load, first | `backlog-adp@program-3.service.acmp.first.if0` | 359,295 | 3.593 | 20 | 20 | fits | 147,256 | 230 | 0.385 |
| ACMP record released under the composed load, last | `backlog-adp@program-3.service.acmp.last.if0` | 467,297 | 4.673 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| AECP record released under the composed load, first | `backlog-adp@program-3.service.aecp.first.if0` | 205,769 | 2.058 | 20 | 24 | fits | 147,709 | 146 | 0.416 |
| AECP record released under the composed load, last | `backlog-adp@program-3.service.aecp.last.if0` | 361,945 | 3.619 | 20 | 24 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, first | `backlog-adp@program-3.service.maap.first.if0` | 361,879 | 3.619 | 20 | 50 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, last | `backlog-adp@program-3.service.maap.last.if0` | 470,321 | 4.703 | 20 | 50 | fits | 108,838 | 175 | 0.274 |
| SRP record released under the composed load, first | `backlog-adp@program-3.service.srp.first.if0` | 556,817 | 5.568 | 20 | 20 | fits | 86,562 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-3.service.srp.last.if0` | 892,993 | 8.930 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-4.adp_available.if0` | 388,959 | 3.890 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| ADP record released under the composed load, first | `backlog-adp@program-4.service.adp.first.if0` | 333,371 | 3.334 | 20 | 200 | fits | 147,256 | 230 | 0.385 |
| ADP record released under the composed load, last | `backlog-adp@program-4.service.adp.last.if0` | 441,593 | 4.416 | 20 | 200 | fits | 108,838 | 175 | 0.274 |
| ACMP record released under the composed load, first | `backlog-adp@program-4.service.acmp.first.if0` | 334,295 | 3.343 | 20 | 20 | fits | 147,256 | 230 | 0.385 |
| ACMP record released under the composed load, last | `backlog-adp@program-4.service.acmp.last.if0` | 442,297 | 4.423 | 20 | 20 | fits | 108,838 | 175 | 0.274 |
| AECP record released under the composed load, first | `backlog-adp@program-4.service.aecp.first.if0` | 180,769 | 1.808 | 20 | 24 | fits | 147,709 | 146 | 0.416 |
| AECP record released under the composed load, last | `backlog-adp@program-4.service.aecp.last.if0` | 336,945 | 3.369 | 20 | 24 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, first | `backlog-adp@program-4.service.maap.first.if0` | 336,879 | 3.369 | 20 | 50 | fits | 147,256 | 230 | 0.385 |
| MAAP record released under the composed load, last | `backlog-adp@program-4.service.maap.last.if0` | 445,321 | 4.453 | 20 | 50 | fits | 108,838 | 175 | 0.274 |
| SRP record released under the composed load, first | `backlog-adp@program-4.service.srp.first.if0` | 531,817 | 5.318 | 20 | 20 | fits | 86,562 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-4.service.srp.last.if0` | 867,993 | 8.680 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-5.adp_available.if0` | 355,509 | 3.555 | 20 | 20 | fits | 108,754 | 175 | 0.272 |
| ADP record released under the composed load, first | `backlog-adp@program-5.service.adp.first.if0` | 300,005 | 3.000 | 20 | 200 | fits | 146,911 | 230 | 0.383 |
| ADP record released under the composed load, last | `backlog-adp@program-5.service.adp.last.if0` | 408,143 | 4.081 | 20 | 200 | fits | 108,754 | 175 | 0.272 |
| ACMP record released under the composed load, first | `backlog-adp@program-5.service.acmp.first.if0` | 300,929 | 3.009 | 20 | 20 | fits | 146,911 | 230 | 0.383 |
| ACMP record released under the composed load, last | `backlog-adp@program-5.service.acmp.last.if0` | 408,847 | 4.088 | 20 | 20 | fits | 108,754 | 175 | 0.272 |
| AECP record released under the composed load, first | `backlog-adp@program-5.service.aecp.first.if0` | 147,682 | 1.477 | 20 | 24 | fits | 149,436 | 146 | 0.418 |
| AECP record released under the composed load, last | `backlog-adp@program-5.service.aecp.last.if0` | 303,579 | 3.036 | 20 | 24 | fits | 146,911 | 230 | 0.383 |
| MAAP record released under the composed load, first | `backlog-adp@program-5.service.maap.first.if0` | 303,513 | 3.035 | 20 | 50 | fits | 146,911 | 230 | 0.383 |
| MAAP record released under the composed load, last | `backlog-adp@program-5.service.maap.last.if0` | 411,871 | 4.119 | 20 | 50 | fits | 108,754 | 175 | 0.272 |
| SRP record released under the composed load, first | `backlog-adp@program-5.service.srp.first.if0` | 498,312 | 4.983 | 20 | 20 | fits | 86,507 | 34 | 0.770 |
| SRP record released under the composed load, last | `backlog-adp@program-5.service.srp.last.if0` | 834,488 | 8.345 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-6.adp_available.if0` | 352,490 | 3.525 | 20 | 20 | fits | 109,116 | 175 | 0.282 |
| ADP record released under the composed load, first | `backlog-adp@program-6.service.adp.first.if0` | 297,149 | 2.971 | 20 | 200 | fits | 145,883 | 225 | 0.380 |
| ADP record released under the composed load, last | `backlog-adp@program-6.service.adp.last.if0` | 405,649 | 4.056 | 20 | 200 | fits | 109,116 | 175 | 0.282 |
| ACMP record released under the composed load, first | `backlog-adp@program-6.service.acmp.first.if0` | 298,073 | 2.981 | 20 | 20 | fits | 145,883 | 225 | 0.380 |
| ACMP record released under the composed load, last | `backlog-adp@program-6.service.acmp.last.if0` | 406,353 | 4.064 | 20 | 20 | fits | 109,116 | 175 | 0.282 |
| AECP record released under the composed load, first | `backlog-adp@program-6.service.aecp.first.if0` | 155,830 | 1.558 | 20 | 24 | fits | 146,785 | 146 | 0.412 |
| AECP record released under the composed load, last | `backlog-adp@program-6.service.aecp.last.if0` | 300,723 | 3.007 | 20 | 24 | fits | 145,883 | 225 | 0.380 |
| MAAP record released under the composed load, first | `backlog-adp@program-6.service.maap.first.if0` | 300,657 | 3.007 | 20 | 50 | fits | 145,883 | 225 | 0.380 |
| MAAP record released under the composed load, last | `backlog-adp@program-6.service.maap.last.if0` | 409,377 | 4.094 | 20 | 50 | fits | 109,116 | 175 | 0.282 |
| SRP record released under the composed load, first | `backlog-adp@program-6.service.srp.first.if0` | 495,841 | 4.958 | 20 | 20 | fits | 86,530 | 34 | 0.770 |
| SRP record released under the composed load, last | `backlog-adp@program-6.service.srp.last.if0` | 835,029 | 8.350 | 20 | 20 | fits | 80,471 | 39 | 0.622 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-7.adp_available.if0` | 343,093 | 3.431 | 20 | 20 | fits | 105,558 | 184 | 0.296 |
| ADP record released under the composed load, first | `backlog-adp@program-7.service.adp.first.if0` | 296,270 | 2.963 | 20 | 200 | fits | 147,955 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@program-7.service.adp.last.if0` | 401,212 | 4.012 | 20 | 200 | fits | 105,558 | 184 | 0.296 |
| ACMP record released under the composed load, first | `backlog-adp@program-7.service.acmp.first.if0` | 297,194 | 2.972 | 20 | 20 | fits | 147,955 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@program-7.service.acmp.last.if0` | 401,916 | 4.019 | 20 | 20 | fits | 105,558 | 184 | 0.296 |
| AECP record released under the composed load, first | `backlog-adp@program-7.service.aecp.first.if0` | 152,879 | 1.529 | 20 | 24 | fits | 147,404 | 145 | 0.419 |
| AECP record released under the composed load, last | `backlog-adp@program-7.service.aecp.last.if0` | 299,844 | 2.998 | 20 | 24 | fits | 147,955 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@program-7.service.maap.first.if0` | 299,778 | 2.998 | 20 | 50 | fits | 147,955 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@program-7.service.maap.last.if0` | 404,940 | 4.049 | 20 | 50 | fits | 105,558 | 184 | 0.296 |
| SRP record released under the composed load, first | `backlog-adp@program-7.service.srp.first.if0` | 491,470 | 4.915 | 20 | 20 | fits | 86,596 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-7.service.srp.last.if0` | 844,224 | 8.442 | 20 | 20 | fits | 81,397 | 39 | 0.665 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-0.adp_available.if0` | 356,232 | 3.562 | 20 | 20 | fits | 112,680 | 193 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@verify-0.service.adp.first.if0` | 297,985 | 2.980 | 20 | 200 | fits | 144,254 | 212 | 0.397 |
| ADP record released under the composed load, last | `backlog-adp@verify-0.service.adp.last.if0` | 410,049 | 4.100 | 20 | 200 | fits | 112,680 | 193 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@verify-0.service.acmp.first.if0` | 298,909 | 2.989 | 20 | 20 | fits | 144,254 | 212 | 0.397 |
| ACMP record released under the composed load, last | `backlog-adp@verify-0.service.acmp.last.if0` | 410,753 | 4.108 | 20 | 20 | fits | 112,680 | 193 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@verify-0.service.aecp.first.if0` | 148,004 | 1.480 | 20 | 24 | fits | 146,755 | 146 | 0.411 |
| AECP record released under the composed load, last | `backlog-adp@verify-0.service.aecp.last.if0` | 301,559 | 3.016 | 20 | 24 | fits | 144,254 | 212 | 0.397 |
| MAAP record released under the composed load, first | `backlog-adp@verify-0.service.maap.first.if0` | 301,493 | 3.015 | 20 | 50 | fits | 144,254 | 212 | 0.397 |
| MAAP record released under the composed load, last | `backlog-adp@verify-0.service.maap.last.if0` | 413,777 | 4.138 | 20 | 50 | fits | 112,680 | 193 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@verify-0.service.srp.first.if0` | 495,926 | 4.959 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-0.service.srp.last.if0` | 832,107 | 8.321 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-1.adp_available.if0` | 439,273 | 4.393 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-1.service.adp.first.if0` | 378,691 | 3.787 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-1.service.adp.last.if0` | 484,825 | 4.848 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-1.service.acmp.first.if0` | 379,615 | 3.796 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-1.service.acmp.last.if0` | 485,529 | 4.855 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-1.service.aecp.first.if0` | 224,640 | 2.246 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-1.service.aecp.last.if0` | 382,265 | 3.823 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-1.service.maap.first.if0` | 382,199 | 3.822 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-1.service.maap.last.if0` | 488,553 | 4.886 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-1.service.srp.first.if0` | 570,702 | 5.707 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-1.service.srp.last.if0` | 906,896 | 9.069 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-2.adp_available.if0` | 426,773 | 4.268 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-2.service.adp.first.if0` | 366,191 | 3.662 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-2.service.adp.last.if0` | 472,325 | 4.723 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-2.service.acmp.first.if0` | 367,115 | 3.671 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-2.service.acmp.last.if0` | 473,029 | 4.730 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-2.service.aecp.first.if0` | 212,140 | 2.121 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-2.service.aecp.last.if0` | 369,765 | 3.698 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-2.service.maap.first.if0` | 369,699 | 3.697 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-2.service.maap.last.if0` | 476,053 | 4.761 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-2.service.srp.first.if0` | 558,202 | 5.582 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-2.service.srp.last.if0` | 894,396 | 8.944 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-3.adp_available.if0` | 414,273 | 4.143 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-3.service.adp.first.if0` | 353,691 | 3.537 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-3.service.adp.last.if0` | 459,825 | 4.598 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-3.service.acmp.first.if0` | 354,615 | 3.546 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-3.service.acmp.last.if0` | 460,529 | 4.605 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-3.service.aecp.first.if0` | 199,640 | 1.996 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-3.service.aecp.last.if0` | 357,265 | 3.573 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-3.service.maap.first.if0` | 357,199 | 3.572 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-3.service.maap.last.if0` | 463,553 | 4.636 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-3.service.srp.first.if0` | 545,702 | 5.457 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-3.service.srp.last.if0` | 881,896 | 8.819 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-4.adp_available.if0` | 401,773 | 4.018 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-4.service.adp.first.if0` | 341,191 | 3.412 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-4.service.adp.last.if0` | 447,325 | 4.473 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-4.service.acmp.first.if0` | 342,115 | 3.421 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-4.service.acmp.last.if0` | 448,029 | 4.480 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-4.service.aecp.first.if0` | 187,140 | 1.871 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-4.service.aecp.last.if0` | 344,765 | 3.448 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-4.service.maap.first.if0` | 344,699 | 3.447 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-4.service.maap.last.if0` | 451,053 | 4.511 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-4.service.srp.first.if0` | 533,202 | 5.332 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-4.service.srp.last.if0` | 869,396 | 8.694 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-5.adp_available.if0` | 389,273 | 3.893 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-5.service.adp.first.if0` | 328,691 | 3.287 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-5.service.adp.last.if0` | 434,825 | 4.348 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-5.service.acmp.first.if0` | 329,615 | 3.296 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-5.service.acmp.last.if0` | 435,529 | 4.355 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-5.service.aecp.first.if0` | 174,640 | 1.746 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-5.service.aecp.last.if0` | 332,265 | 3.323 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-5.service.maap.first.if0` | 332,199 | 3.322 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-5.service.maap.last.if0` | 438,553 | 4.386 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-5.service.srp.first.if0` | 520,702 | 5.207 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-5.service.srp.last.if0` | 856,896 | 8.569 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-6.adp_available.if0` | 376,773 | 3.768 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-6.service.adp.first.if0` | 316,191 | 3.162 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-6.service.adp.last.if0` | 422,325 | 4.223 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-6.service.acmp.first.if0` | 317,115 | 3.171 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-6.service.acmp.last.if0` | 423,029 | 4.230 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-6.service.aecp.first.if0` | 162,140 | 1.621 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-6.service.aecp.last.if0` | 319,765 | 3.198 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-6.service.maap.first.if0` | 319,699 | 3.197 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-6.service.maap.last.if0` | 426,053 | 4.261 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-6.service.srp.first.if0` | 508,202 | 5.082 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-6.service.srp.last.if0` | 844,396 | 8.444 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-7.adp_available.if0` | 364,273 | 3.643 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@verify-7.service.adp.first.if0` | 303,691 | 3.037 | 20 | 200 | fits | 148,322 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@verify-7.service.adp.last.if0` | 409,825 | 4.098 | 20 | 200 | fits | 106,750 | 187 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@verify-7.service.acmp.first.if0` | 304,615 | 3.046 | 20 | 20 | fits | 148,322 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@verify-7.service.acmp.last.if0` | 410,529 | 4.105 | 20 | 20 | fits | 106,750 | 187 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@verify-7.service.aecp.first.if0` | 149,640 | 1.496 | 20 | 24 | fits | 146,979 | 146 | 0.415 |
| AECP record released under the composed load, last | `backlog-adp@verify-7.service.aecp.last.if0` | 307,265 | 3.073 | 20 | 24 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@verify-7.service.maap.first.if0` | 307,199 | 3.072 | 20 | 50 | fits | 148,322 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@verify-7.service.maap.last.if0` | 413,553 | 4.136 | 20 | 50 | fits | 106,750 | 187 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@verify-7.service.srp.first.if0` | 495,702 | 4.957 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-7.service.srp.last.if0` | 831,896 | 8.319 | 20 | 20 | fits | 77,472 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-0.adp_available.if0` | 349,467 | 3.495 | 20 | 20 | fits | 112,835 | 193 | 0.285 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.adp.first.if0` | 302,356 | 3.024 | 20 | 200 | fits | 144,229 | 212 | 0.395 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.adp.last.if0` | 414,575 | 4.146 | 20 | 200 | fits | 112,835 | 193 | 0.285 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.acmp.first.if0` | 303,280 | 3.033 | 20 | 20 | fits | 144,229 | 212 | 0.395 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.acmp.last.if0` | 415,279 | 4.153 | 20 | 20 | fits | 112,835 | 193 | 0.285 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.aecp.first.if0` | 152,931 | 1.529 | 20 | 24 | fits | 145,944 | 143 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.aecp.last.if0` | 305,930 | 3.059 | 20 | 24 | fits | 144,229 | 212 | 0.395 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.maap.first.if0` | 305,864 | 3.059 | 20 | 50 | fits | 144,229 | 212 | 0.395 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.maap.last.if0` | 418,303 | 4.183 | 20 | 50 | fits | 112,835 | 193 | 0.285 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.srp.first.if0` | 500,452 | 5.005 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.srp.last.if0` | 836,696 | 8.367 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-1.adp_available.if0` | 348,663 | 3.487 | 20 | 20 | fits | 112,768 | 193 | 0.284 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.adp.first.if0` | 301,552 | 3.016 | 20 | 200 | fits | 144,070 | 212 | 0.393 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.adp.last.if0` | 413,704 | 4.137 | 20 | 200 | fits | 112,768 | 193 | 0.284 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.acmp.first.if0` | 302,476 | 3.025 | 20 | 20 | fits | 144,070 | 212 | 0.393 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.acmp.last.if0` | 414,408 | 4.144 | 20 | 20 | fits | 112,768 | 193 | 0.284 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.aecp.first.if0` | 152,326 | 1.523 | 20 | 24 | fits | 146,019 | 143 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.aecp.last.if0` | 305,126 | 3.051 | 20 | 24 | fits | 144,070 | 212 | 0.393 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.maap.first.if0` | 305,060 | 3.051 | 20 | 50 | fits | 144,070 | 212 | 0.393 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.maap.last.if0` | 417,432 | 4.174 | 20 | 50 | fits | 112,768 | 193 | 0.284 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.srp.first.if0` | 499,581 | 4.996 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.srp.last.if0` | 835,825 | 8.358 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-2.adp_available.if0` | 351,369 | 3.514 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.adp.first.if0` | 295,923 | 2.959 | 20 | 200 | fits | 145,811 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.adp.last.if0` | 404,384 | 4.044 | 20 | 200 | fits | 109,077 | 175 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.acmp.first.if0` | 296,847 | 2.968 | 20 | 20 | fits | 145,811 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.acmp.last.if0` | 405,088 | 4.051 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.aecp.first.if0` | 154,676 | 1.547 | 20 | 24 | fits | 145,802 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.aecp.last.if0` | 299,497 | 2.995 | 20 | 24 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.maap.first.if0` | 299,431 | 2.994 | 20 | 50 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.maap.last.if0` | 408,112 | 4.081 | 20 | 50 | fits | 109,077 | 175 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.srp.first.if0` | 490,226 | 4.902 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.srp.last.if0` | 846,858 | 8.469 | 20 | 20 | fits | 85,345 | 45 | 0.669 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-3.adp_available.if0` | 350,689 | 3.507 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.adp.first.if0` | 295,243 | 2.952 | 20 | 200 | fits | 145,811 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.adp.last.if0` | 403,704 | 4.037 | 20 | 200 | fits | 109,077 | 175 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.acmp.first.if0` | 296,167 | 2.962 | 20 | 20 | fits | 145,811 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.acmp.last.if0` | 404,408 | 4.044 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.aecp.first.if0` | 153,996 | 1.540 | 20 | 24 | fits | 145,802 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.aecp.last.if0` | 298,817 | 2.988 | 20 | 24 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.maap.first.if0` | 298,751 | 2.988 | 20 | 50 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.maap.last.if0` | 407,432 | 4.074 | 20 | 50 | fits | 109,077 | 175 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.srp.first.if0` | 489,546 | 4.895 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.srp.last.if0` | 923,969 | 9.240 | 20 | 20 | fits | 86,872 | 36 | 0.597 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-4.adp_available.if0` | 350,009 | 3.500 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.adp.first.if0` | 294,563 | 2.946 | 20 | 200 | fits | 145,811 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.adp.last.if0` | 403,024 | 4.030 | 20 | 200 | fits | 109,077 | 175 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.acmp.first.if0` | 295,487 | 2.955 | 20 | 20 | fits | 145,811 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.acmp.last.if0` | 403,728 | 4.037 | 20 | 20 | fits | 109,077 | 175 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.aecp.first.if0` | 153,316 | 1.533 | 20 | 24 | fits | 145,802 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.aecp.last.if0` | 298,137 | 2.981 | 20 | 24 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.maap.first.if0` | 298,071 | 2.981 | 20 | 50 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.maap.last.if0` | 406,752 | 4.068 | 20 | 50 | fits | 109,077 | 175 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.srp.first.if0` | 489,095 | 4.891 | 20 | 20 | fits | 82,409 | 29 | 0.761 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.srp.last.if0` | 923,639 | 9.236 | 20 | 20 | fits | 86,831 | 36 | 0.595 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-5.adp_available.if0` | 349,329 | 3.493 | 20 | 20 | fits | 109,375 | 176 | 0.284 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.adp.first.if0` | 293,883 | 2.939 | 20 | 200 | fits | 145,811 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.adp.last.if0` | 402,642 | 4.026 | 20 | 200 | fits | 109,375 | 176 | 0.284 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.acmp.first.if0` | 294,807 | 2.948 | 20 | 20 | fits | 145,811 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.acmp.last.if0` | 403,346 | 4.033 | 20 | 20 | fits | 109,375 | 176 | 0.284 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.aecp.first.if0` | 152,636 | 1.526 | 20 | 24 | fits | 145,802 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.aecp.last.if0` | 297,457 | 2.975 | 20 | 24 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.maap.first.if0` | 297,391 | 2.974 | 20 | 50 | fits | 145,811 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.maap.last.if0` | 406,370 | 4.064 | 20 | 50 | fits | 109,375 | 176 | 0.284 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.srp.first.if0` | 506,688 | 5.067 | 20 | 20 | fits | 88,667 | 41 | 0.764 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.srp.last.if0` | 920,501 | 9.205 | 20 | 20 | fits | 86,788 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-6.adp_available.if0` | 370,339 | 3.703 | 20 | 20 | fits | 119,621 | 188 | 0.357 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.adp.first.if0` | 293,534 | 2.935 | 20 | 200 | fits | 146,142 | 226 | 0.381 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.adp.last.if0` | 424,050 | 4.240 | 20 | 200 | fits | 119,621 | 188 | 0.357 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.acmp.first.if0` | 294,458 | 2.945 | 20 | 20 | fits | 146,142 | 226 | 0.381 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.acmp.last.if0` | 424,754 | 4.248 | 20 | 20 | fits | 119,621 | 188 | 0.357 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.aecp.first.if0` | 151,956 | 1.520 | 20 | 24 | fits | 145,802 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.aecp.last.if0` | 297,108 | 2.971 | 20 | 24 | fits | 146,142 | 226 | 0.381 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.maap.first.if0` | 297,042 | 2.970 | 20 | 50 | fits | 146,142 | 226 | 0.381 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.maap.last.if0` | 427,778 | 4.278 | 20 | 50 | fits | 119,621 | 188 | 0.357 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.srp.first.if0` | 586,956 | 5.870 | 20 | 20 | fits | 82,208 | 29 | 0.761 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.srp.last.if0` | 922,595 | 9.226 | 20 | 20 | fits | 77,325 | 32 | 0.615 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-7.adp_available.if0` | 441,902 | 4.419 | 20 | 20 | fits | 116,711 | 202 | 0.303 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.adp.first.if0` | 302,925 | 3.029 | 20 | 200 | fits | 146,345 | 208 | 0.409 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.adp.last.if0` | 495,594 | 4.956 | 20 | 200 | fits | 116,711 | 202 | 0.303 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.acmp.first.if0` | 303,849 | 3.038 | 20 | 20 | fits | 146,345 | 208 | 0.409 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.acmp.last.if0` | 496,298 | 4.963 | 20 | 20 | fits | 116,711 | 202 | 0.303 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.aecp.first.if0` | 151,578 | 1.516 | 20 | 24 | fits | 146,104 | 143 | 0.409 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.aecp.last.if0` | 306,499 | 3.065 | 20 | 24 | fits | 146,345 | 208 | 0.409 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.maap.first.if0` | 306,433 | 3.064 | 20 | 50 | fits | 146,345 | 208 | 0.409 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.maap.last.if0` | 499,322 | 4.993 | 20 | 50 | fits | 116,711 | 202 | 0.303 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.srp.first.if0` | 581,373 | 5.814 | 20 | 20 | fits | 82,117 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.srp.last.if0` | 917,862 | 9.179 | 20 | 20 | fits | 77,706 | 33 | 0.619 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-0.adp_available.if0` | 352,891 | 3.529 | 20 | 20 | fits | 105,649 | 185 | 0.294 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.adp.first.if0` | 294,838 | 2.948 | 20 | 200 | fits | 147,987 | 214 | 0.373 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.adp.last.if0` | 399,871 | 3.999 | 20 | 200 | fits | 105,649 | 185 | 0.294 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.acmp.first.if0` | 295,762 | 2.958 | 20 | 20 | fits | 147,987 | 214 | 0.373 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.acmp.last.if0` | 400,575 | 4.006 | 20 | 20 | fits | 105,649 | 185 | 0.294 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.aecp.first.if0` | 151,415 | 1.514 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.aecp.last.if0` | 298,412 | 2.984 | 20 | 24 | fits | 147,987 | 214 | 0.373 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.maap.first.if0` | 298,346 | 2.983 | 20 | 50 | fits | 147,987 | 214 | 0.373 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.maap.last.if0` | 403,599 | 4.036 | 20 | 50 | fits | 105,649 | 185 | 0.294 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.srp.first.if0` | 500,589 | 5.006 | 20 | 20 | fits | 85,272 | 35 | 0.769 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.srp.last.if0` | 837,231 | 8.372 | 20 | 20 | fits | 77,542 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-1.adp_available.if0` | 367,816 | 3.678 | 20 | 20 | fits | 110,149 | 191 | 0.360 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.adp.first.if0` | 294,323 | 2.943 | 20 | 200 | fits | 148,152 | 215 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.adp.last.if0` | 415,194 | 4.152 | 20 | 200 | fits | 110,149 | 191 | 0.360 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.acmp.first.if0` | 295,247 | 2.952 | 20 | 20 | fits | 148,152 | 215 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.acmp.last.if0` | 415,898 | 4.159 | 20 | 20 | fits | 110,149 | 191 | 0.360 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.aecp.first.if0` | 150,735 | 1.507 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.aecp.last.if0` | 297,897 | 2.979 | 20 | 24 | fits | 148,152 | 215 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.maap.first.if0` | 297,831 | 2.978 | 20 | 50 | fits | 148,152 | 215 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.maap.last.if0` | 418,922 | 4.189 | 20 | 50 | fits | 110,149 | 191 | 0.360 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.srp.first.if0` | 501,115 | 5.011 | 20 | 20 | fits | 82,259 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.srp.last.if0` | 836,688 | 8.367 | 20 | 20 | fits | 77,307 | 32 | 0.615 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-2.adp_available.if0` | 357,763 | 3.578 | 20 | 20 | fits | 112,740 | 193 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.adp.first.if0` | 299,516 | 2.995 | 20 | 200 | fits | 144,028 | 212 | 0.393 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.adp.last.if0` | 411,640 | 4.116 | 20 | 200 | fits | 112,740 | 193 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.acmp.first.if0` | 300,440 | 3.004 | 20 | 20 | fits | 144,028 | 212 | 0.393 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.acmp.last.if0` | 412,344 | 4.123 | 20 | 20 | fits | 112,740 | 193 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.aecp.first.if0` | 150,375 | 1.504 | 20 | 24 | fits | 146,190 | 143 | 0.410 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.aecp.last.if0` | 303,090 | 3.031 | 20 | 24 | fits | 144,028 | 212 | 0.393 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.maap.first.if0` | 303,024 | 3.030 | 20 | 50 | fits | 144,028 | 212 | 0.393 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.maap.last.if0` | 415,368 | 4.154 | 20 | 50 | fits | 112,740 | 193 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.srp.first.if0` | 497,517 | 4.975 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.srp.last.if0` | 837,962 | 8.380 | 20 | 20 | fits | 81,723 | 38 | 0.647 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-3.adp_available.if0` | 343,950 | 3.439 | 20 | 20 | fits | 105,537 | 184 | 0.295 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.adp.first.if0` | 297,148 | 2.971 | 20 | 200 | fits | 148,121 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.adp.last.if0` | 402,069 | 4.021 | 20 | 200 | fits | 105,537 | 184 | 0.295 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.acmp.first.if0` | 298,072 | 2.981 | 20 | 20 | fits | 148,121 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.acmp.last.if0` | 402,773 | 4.028 | 20 | 20 | fits | 105,537 | 184 | 0.295 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.aecp.first.if0` | 153,591 | 1.536 | 20 | 24 | fits | 145,806 | 142 | 0.406 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.aecp.last.if0` | 300,722 | 3.007 | 20 | 24 | fits | 148,121 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.maap.first.if0` | 300,656 | 3.007 | 20 | 50 | fits | 148,121 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.maap.last.if0` | 405,797 | 4.058 | 20 | 50 | fits | 105,537 | 184 | 0.295 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.srp.first.if0` | 487,977 | 4.880 | 20 | 20 | fits | 82,246 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.srp.last.if0` | 828,766 | 8.288 | 20 | 20 | fits | 86,916 | 37 | 0.595 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-4.adp_available.if0` | 343,283 | 3.433 | 20 | 20 | fits | 105,582 | 184 | 0.296 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.adp.first.if0` | 296,436 | 2.964 | 20 | 200 | fits | 148,081 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.adp.last.if0` | 401,402 | 4.014 | 20 | 200 | fits | 105,582 | 184 | 0.296 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.acmp.first.if0` | 297,360 | 2.974 | 20 | 20 | fits | 148,081 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.acmp.last.if0` | 402,106 | 4.021 | 20 | 20 | fits | 105,582 | 184 | 0.296 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.aecp.first.if0` | 152,919 | 1.529 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.aecp.last.if0` | 300,010 | 3.000 | 20 | 24 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.maap.first.if0` | 299,944 | 2.999 | 20 | 50 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.maap.last.if0` | 405,130 | 4.051 | 20 | 50 | fits | 105,582 | 184 | 0.296 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.srp.first.if0` | 487,310 | 4.873 | 20 | 20 | fits | 82,246 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.srp.last.if0` | 864,079 | 8.641 | 20 | 20 | fits | 28,418 | 12 | 0.824 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-5.adp_available.if0` | 342,603 | 3.426 | 20 | 20 | fits | 105,582 | 184 | 0.296 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.adp.first.if0` | 295,756 | 2.958 | 20 | 200 | fits | 148,081 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.adp.last.if0` | 400,722 | 4.007 | 20 | 200 | fits | 105,582 | 184 | 0.296 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.acmp.first.if0` | 296,680 | 2.967 | 20 | 20 | fits | 148,081 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.acmp.last.if0` | 401,426 | 4.014 | 20 | 20 | fits | 105,582 | 184 | 0.296 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.aecp.first.if0` | 152,239 | 1.522 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.aecp.last.if0` | 299,330 | 2.993 | 20 | 24 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.maap.first.if0` | 299,264 | 2.993 | 20 | 50 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.maap.last.if0` | 404,450 | 4.045 | 20 | 50 | fits | 105,582 | 184 | 0.296 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.srp.first.if0` | 490,980 | 4.910 | 20 | 20 | fits | 86,596 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.srp.last.if0` | 844,220 | 8.442 | 20 | 20 | fits | 86,751 | 36 | 0.592 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-6.adp_available.if0` | 348,753 | 3.488 | 20 | 20 | fits | 112,885 | 191 | 0.343 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.adp.first.if0` | 295,076 | 2.951 | 20 | 200 | fits | 148,081 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.adp.last.if0` | 407,345 | 4.073 | 20 | 200 | fits | 112,885 | 191 | 0.343 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.acmp.first.if0` | 296,000 | 2.960 | 20 | 20 | fits | 148,081 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.acmp.last.if0` | 408,049 | 4.080 | 20 | 20 | fits | 112,885 | 191 | 0.343 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.aecp.first.if0` | 151,559 | 1.516 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.aecp.last.if0` | 298,650 | 2.986 | 20 | 24 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.maap.first.if0` | 298,584 | 2.986 | 20 | 50 | fits | 148,081 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.maap.last.if0` | 411,073 | 4.111 | 20 | 50 | fits | 112,885 | 191 | 0.343 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.srp.first.if0` | 507,974 | 5.080 | 20 | 20 | fits | 85,156 | 35 | 0.767 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.srp.last.if0` | 844,494 | 8.445 | 20 | 20 | fits | 86,770 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-7.adp_available.if0` | 366,841 | 3.668 | 20 | 20 | fits | 118,071 | 202 | 0.334 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.adp.first.if0` | 291,658 | 2.917 | 20 | 200 | fits | 145,343 | 209 | 0.395 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.adp.last.if0` | 420,740 | 4.207 | 20 | 200 | fits | 118,071 | 202 | 0.334 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.acmp.first.if0` | 292,582 | 2.926 | 20 | 20 | fits | 145,343 | 209 | 0.395 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.acmp.last.if0` | 421,444 | 4.214 | 20 | 20 | fits | 118,071 | 202 | 0.334 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.aecp.first.if0` | 150,879 | 1.509 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.aecp.last.if0` | 295,232 | 2.952 | 20 | 24 | fits | 145,343 | 209 | 0.395 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.maap.first.if0` | 295,166 | 2.952 | 20 | 50 | fits | 145,343 | 209 | 0.395 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.maap.last.if0` | 424,468 | 4.245 | 20 | 50 | fits | 118,071 | 202 | 0.334 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.srp.first.if0` | 506,612 | 5.066 | 20 | 20 | fits | 82,210 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.srp.last.if0` | 842,198 | 8.422 | 20 | 20 | fits | 77,307 | 32 | 0.615 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-0.adp_available.if0` | 350,563 | 3.506 | 20 | 20 | fits | 105,758 | 185 | 0.295 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-0.service.adp.first.if0` | 292,545 | 2.925 | 20 | 200 | fits | 148,016 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-0.service.adp.last.if0` | 397,687 | 3.977 | 20 | 200 | fits | 105,758 | 185 | 0.295 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-0.service.acmp.first.if0` | 293,469 | 2.935 | 20 | 20 | fits | 148,016 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-0.service.acmp.last.if0` | 398,391 | 3.984 | 20 | 20 | fits | 105,758 | 185 | 0.295 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-0.service.aecp.first.if0` | 149,093 | 1.491 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-0.service.aecp.last.if0` | 296,119 | 2.961 | 20 | 24 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-0.service.maap.first.if0` | 296,053 | 2.961 | 20 | 50 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-0.service.maap.last.if0` | 401,415 | 4.014 | 20 | 50 | fits | 105,758 | 185 | 0.295 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-0.service.srp.first.if0` | 498,405 | 4.984 | 20 | 20 | fits | 85,272 | 35 | 0.769 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-0.service.srp.last.if0` | 835,047 | 8.350 | 20 | 20 | fits | 77,542 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-1.adp_available.if0` | 365,588 | 3.656 | 20 | 20 | fits | 110,149 | 191 | 0.360 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-1.service.adp.first.if0` | 292,030 | 2.920 | 20 | 200 | fits | 148,181 | 215 | 0.375 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-1.service.adp.last.if0` | 412,966 | 4.130 | 20 | 200 | fits | 110,149 | 191 | 0.360 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-1.service.acmp.first.if0` | 292,954 | 2.930 | 20 | 20 | fits | 148,181 | 215 | 0.375 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-1.service.acmp.last.if0` | 413,670 | 4.137 | 20 | 20 | fits | 110,149 | 191 | 0.360 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-1.service.aecp.first.if0` | 148,413 | 1.484 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-1.service.aecp.last.if0` | 295,604 | 2.956 | 20 | 24 | fits | 148,181 | 215 | 0.375 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-1.service.maap.first.if0` | 295,538 | 2.955 | 20 | 50 | fits | 148,181 | 215 | 0.375 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-1.service.maap.last.if0` | 416,694 | 4.167 | 20 | 50 | fits | 110,149 | 191 | 0.360 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-1.service.srp.first.if0` | 498,887 | 4.989 | 20 | 20 | fits | 82,259 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-1.service.srp.last.if0` | 834,460 | 8.345 | 20 | 20 | fits | 77,307 | 32 | 0.615 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-2.adp_available.if0` | 355,499 | 3.555 | 20 | 20 | fits | 112,764 | 193 | 0.283 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-2.service.adp.first.if0` | 297,168 | 2.972 | 20 | 200 | fits | 144,035 | 212 | 0.394 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-2.service.adp.last.if0` | 409,316 | 4.093 | 20 | 200 | fits | 112,764 | 193 | 0.283 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-2.service.acmp.first.if0` | 298,092 | 2.981 | 20 | 20 | fits | 144,035 | 212 | 0.394 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-2.service.acmp.last.if0` | 410,020 | 4.100 | 20 | 20 | fits | 112,764 | 193 | 0.283 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-2.service.aecp.first.if0` | 148,053 | 1.481 | 20 | 24 | fits | 146,086 | 143 | 0.408 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-2.service.aecp.last.if0` | 300,742 | 3.007 | 20 | 24 | fits | 144,035 | 212 | 0.394 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-2.service.maap.first.if0` | 300,676 | 3.007 | 20 | 50 | fits | 144,035 | 212 | 0.394 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-2.service.maap.last.if0` | 413,044 | 4.130 | 20 | 50 | fits | 112,764 | 193 | 0.283 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-2.service.srp.first.if0` | 495,193 | 4.952 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-2.service.srp.last.if0` | 835,578 | 8.356 | 20 | 20 | fits | 81,663 | 38 | 0.646 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-3.adp_available.if0` | 341,591 | 3.416 | 20 | 20 | fits | 105,439 | 184 | 0.294 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-3.service.adp.first.if0` | 294,825 | 2.948 | 20 | 200 | fits | 147,964 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-3.service.adp.last.if0` | 399,648 | 3.996 | 20 | 200 | fits | 105,439 | 184 | 0.294 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-3.service.acmp.first.if0` | 295,749 | 2.957 | 20 | 20 | fits | 147,964 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-3.service.acmp.last.if0` | 400,352 | 4.004 | 20 | 20 | fits | 105,439 | 184 | 0.294 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-3.service.aecp.first.if0` | 151,425 | 1.514 | 20 | 24 | fits | 145,858 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-3.service.aecp.last.if0` | 298,399 | 2.984 | 20 | 24 | fits | 147,964 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-3.service.maap.first.if0` | 298,333 | 2.983 | 20 | 50 | fits | 147,964 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-3.service.maap.last.if0` | 403,376 | 4.034 | 20 | 50 | fits | 105,439 | 184 | 0.294 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-3.service.srp.first.if0` | 485,556 | 4.856 | 20 | 20 | fits | 82,246 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-3.service.srp.last.if0` | 944,438 | 9.444 | 20 | 20 | fits | 28,788 | 12 | 0.831 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-4.adp_available.if0` | 341,047 | 3.410 | 20 | 20 | fits | 105,555 | 184 | 0.296 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-4.service.adp.first.if0` | 294,165 | 2.942 | 20 | 200 | fits | 147,924 | 214 | 0.373 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-4.service.adp.last.if0` | 399,104 | 3.991 | 20 | 200 | fits | 105,555 | 184 | 0.296 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-4.service.acmp.first.if0` | 295,089 | 2.951 | 20 | 20 | fits | 147,924 | 214 | 0.373 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-4.service.acmp.last.if0` | 399,808 | 3.998 | 20 | 20 | fits | 105,555 | 184 | 0.296 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-4.service.aecp.first.if0` | 150,805 | 1.508 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-4.service.aecp.last.if0` | 297,739 | 2.977 | 20 | 24 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-4.service.maap.first.if0` | 297,673 | 2.977 | 20 | 50 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-4.service.maap.last.if0` | 402,832 | 4.028 | 20 | 50 | fits | 105,555 | 184 | 0.296 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-4.service.srp.first.if0` | 485,012 | 4.850 | 20 | 20 | fits | 82,246 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-4.service.srp.last.if0` | 945,953 | 9.460 | 20 | 20 | fits | 38,730 | 16 | 0.772 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-5.adp_available.if0` | 340,367 | 3.404 | 20 | 20 | fits | 105,555 | 184 | 0.296 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-5.service.adp.first.if0` | 293,485 | 2.935 | 20 | 200 | fits | 147,924 | 214 | 0.373 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-5.service.adp.last.if0` | 398,424 | 3.984 | 20 | 200 | fits | 105,555 | 184 | 0.296 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-5.service.acmp.first.if0` | 294,409 | 2.944 | 20 | 20 | fits | 147,924 | 214 | 0.373 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-5.service.acmp.last.if0` | 399,128 | 3.991 | 20 | 20 | fits | 105,555 | 184 | 0.296 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-5.service.aecp.first.if0` | 150,125 | 1.501 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-5.service.aecp.last.if0` | 297,059 | 2.971 | 20 | 24 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-5.service.maap.first.if0` | 296,993 | 2.970 | 20 | 50 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-5.service.maap.last.if0` | 402,152 | 4.022 | 20 | 50 | fits | 105,555 | 184 | 0.296 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-5.service.srp.first.if0` | 488,682 | 4.887 | 20 | 20 | fits | 86,596 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-5.service.srp.last.if0` | 945,204 | 9.452 | 20 | 20 | fits | 28,512 | 12 | 0.825 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-6.adp_available.if0` | 346,482 | 3.465 | 20 | 20 | fits | 112,823 | 191 | 0.342 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-6.service.adp.first.if0` | 292,805 | 2.928 | 20 | 200 | fits | 147,924 | 214 | 0.373 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-6.service.adp.last.if0` | 405,012 | 4.050 | 20 | 200 | fits | 112,823 | 191 | 0.342 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-6.service.acmp.first.if0` | 293,729 | 2.937 | 20 | 20 | fits | 147,924 | 214 | 0.373 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-6.service.acmp.last.if0` | 405,716 | 4.057 | 20 | 20 | fits | 112,823 | 191 | 0.342 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-6.service.aecp.first.if0` | 149,445 | 1.494 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-6.service.aecp.last.if0` | 296,379 | 2.964 | 20 | 24 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-6.service.maap.first.if0` | 296,313 | 2.963 | 20 | 50 | fits | 147,924 | 214 | 0.373 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-6.service.maap.last.if0` | 408,740 | 4.087 | 20 | 50 | fits | 112,823 | 191 | 0.342 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-6.service.srp.first.if0` | 585,642 | 5.856 | 20 | 20 | fits | 85,253 | 35 | 0.768 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-6.service.srp.last.if0` | 922,674 | 9.227 | 20 | 20 | fits | 77,542 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-7.adp_available.if0` | 444,619 | 4.446 | 20 | 20 | fits | 118,555 | 202 | 0.342 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-7.service.adp.first.if0` | 289,469 | 2.895 | 20 | 200 | fits | 145,268 | 209 | 0.395 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-7.service.adp.last.if0` | 498,635 | 4.986 | 20 | 200 | fits | 118,555 | 202 | 0.342 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-7.service.acmp.first.if0` | 290,393 | 2.904 | 20 | 20 | fits | 145,268 | 209 | 0.395 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-7.service.acmp.last.if0` | 499,339 | 4.993 | 20 | 20 | fits | 118,555 | 202 | 0.342 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-7.service.aecp.first.if0` | 148,765 | 1.488 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-7.service.aecp.last.if0` | 293,043 | 2.930 | 20 | 24 | fits | 145,268 | 209 | 0.395 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-7.service.maap.first.if0` | 292,977 | 2.930 | 20 | 50 | fits | 145,268 | 209 | 0.395 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-7.service.maap.last.if0` | 502,363 | 5.024 | 20 | 50 | fits | 118,555 | 202 | 0.342 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-7.service.srp.first.if0` | 584,322 | 5.843 | 20 | 20 | fits | 82,025 | 28 | 0.760 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-7.service.srp.last.if0` | 921,300 | 9.213 | 20 | 20 | fits | 77,626 | 32 | 0.621 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-0.adp_available.if0` | 350,301 | 3.503 | 20 | 20 | fits | 106,833 | 187 | 0.286 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-0.service.adp.first.if0` | 289,676 | 2.897 | 20 | 200 | fits | 146,578 | 210 | 0.381 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-0.service.adp.last.if0` | 395,893 | 3.959 | 20 | 200 | fits | 106,833 | 187 | 0.286 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-0.service.acmp.first.if0` | 290,600 | 2.906 | 20 | 20 | fits | 146,578 | 210 | 0.381 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-0.service.acmp.last.if0` | 396,597 | 3.966 | 20 | 20 | fits | 106,833 | 187 | 0.286 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-0.service.aecp.first.if0` | 147,662 | 1.477 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-0.service.aecp.last.if0` | 293,250 | 2.933 | 20 | 24 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-0.service.maap.first.if0` | 293,184 | 2.932 | 20 | 50 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-0.service.maap.last.if0` | 399,621 | 3.996 | 20 | 50 | fits | 106,833 | 187 | 0.286 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-0.service.srp.first.if0` | 481,735 | 4.817 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-0.service.srp.last.if0` | 835,130 | 8.351 | 20 | 20 | fits | 86,764 | 36 | 0.592 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-1.adp_available.if0` | 349,621 | 3.496 | 20 | 20 | fits | 106,833 | 187 | 0.286 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-1.service.adp.first.if0` | 288,996 | 2.890 | 20 | 200 | fits | 146,578 | 210 | 0.381 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-1.service.adp.last.if0` | 395,213 | 3.952 | 20 | 200 | fits | 106,833 | 187 | 0.286 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-1.service.acmp.first.if0` | 289,920 | 2.899 | 20 | 20 | fits | 146,578 | 210 | 0.381 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-1.service.acmp.last.if0` | 395,917 | 3.959 | 20 | 20 | fits | 106,833 | 187 | 0.286 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-1.service.aecp.first.if0` | 146,982 | 1.470 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-1.service.aecp.last.if0` | 292,570 | 2.926 | 20 | 24 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-1.service.maap.first.if0` | 292,504 | 2.925 | 20 | 50 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-1.service.maap.last.if0` | 398,941 | 3.989 | 20 | 50 | fits | 106,833 | 187 | 0.286 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-1.service.srp.first.if0` | 481,284 | 4.813 | 20 | 20 | fits | 82,409 | 29 | 0.761 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-1.service.srp.last.if0` | 834,523 | 8.345 | 20 | 20 | fits | 86,769 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-2.adp_available.if0` | 353,031 | 3.530 | 20 | 20 | fits | 110,882 | 194 | 0.314 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-2.service.adp.first.if0` | 288,316 | 2.883 | 20 | 200 | fits | 146,578 | 210 | 0.381 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-2.service.adp.last.if0` | 398,582 | 3.986 | 20 | 200 | fits | 110,882 | 194 | 0.314 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-2.service.acmp.first.if0` | 289,240 | 2.892 | 20 | 20 | fits | 146,578 | 210 | 0.381 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-2.service.acmp.last.if0` | 399,286 | 3.993 | 20 | 20 | fits | 110,882 | 194 | 0.314 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-2.service.aecp.first.if0` | 146,302 | 1.463 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-2.service.aecp.last.if0` | 291,890 | 2.919 | 20 | 24 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-2.service.maap.first.if0` | 291,824 | 2.918 | 20 | 50 | fits | 146,578 | 210 | 0.381 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-2.service.maap.last.if0` | 402,310 | 4.023 | 20 | 50 | fits | 110,882 | 194 | 0.314 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-2.service.srp.first.if0` | 496,811 | 4.968 | 20 | 20 | fits | 83,039 | 29 | 0.769 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-2.service.srp.last.if0` | 837,939 | 8.379 | 20 | 20 | fits | 82,029 | 38 | 0.649 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-3.adp_available.if0` | 362,877 | 3.629 | 20 | 20 | fits | 110,938 | 193 | 0.347 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-3.service.adp.first.if0` | 287,438 | 2.874 | 20 | 200 | fits | 147,723 | 216 | 0.381 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-3.service.adp.last.if0` | 409,098 | 4.091 | 20 | 200 | fits | 110,938 | 193 | 0.347 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-3.service.acmp.first.if0` | 288,362 | 2.884 | 20 | 20 | fits | 147,723 | 216 | 0.381 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-3.service.acmp.last.if0` | 409,802 | 4.098 | 20 | 20 | fits | 110,938 | 193 | 0.347 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-3.service.aecp.first.if0` | 144,279 | 1.443 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-3.service.aecp.last.if0` | 291,012 | 2.910 | 20 | 24 | fits | 147,723 | 216 | 0.381 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-3.service.maap.first.if0` | 290,946 | 2.909 | 20 | 50 | fits | 147,723 | 216 | 0.381 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-3.service.maap.last.if0` | 412,826 | 4.128 | 20 | 50 | fits | 110,938 | 193 | 0.347 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-3.service.srp.first.if0` | 495,093 | 4.951 | 20 | 20 | fits | 82,333 | 28 | 0.763 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-3.service.srp.last.if0` | 835,495 | 8.355 | 20 | 20 | fits | 86,700 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-4.adp_available.if0` | 360,499 | 3.605 | 20 | 20 | fits | 109,070 | 193 | 0.305 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-4.service.adp.first.if0` | 297,687 | 2.977 | 20 | 200 | fits | 148,087 | 215 | 0.391 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-4.service.adp.last.if0` | 406,141 | 4.061 | 20 | 200 | fits | 109,070 | 193 | 0.305 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-4.service.acmp.first.if0` | 298,611 | 2.986 | 20 | 20 | fits | 148,087 | 215 | 0.391 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-4.service.acmp.last.if0` | 406,845 | 4.068 | 20 | 20 | fits | 109,070 | 193 | 0.305 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-4.service.aecp.first.if0` | 144,563 | 1.446 | 20 | 24 | fits | 146,154 | 143 | 0.410 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-4.service.aecp.last.if0` | 301,261 | 3.013 | 20 | 24 | fits | 148,087 | 215 | 0.391 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-4.service.maap.first.if0` | 301,195 | 3.012 | 20 | 50 | fits | 148,087 | 215 | 0.391 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-4.service.maap.last.if0` | 409,869 | 4.099 | 20 | 50 | fits | 109,070 | 193 | 0.305 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-4.service.srp.first.if0` | 492,069 | 4.921 | 20 | 20 | fits | 82,266 | 28 | 0.763 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-4.service.srp.last.if0` | 832,379 | 8.324 | 20 | 20 | fits | 86,700 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-5.adp_available.if0` | 350,049 | 3.500 | 20 | 20 | fits | 105,460 | 184 | 0.292 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-5.service.adp.first.if0` | 292,031 | 2.920 | 20 | 200 | fits | 148,016 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-5.service.adp.last.if0` | 396,875 | 3.969 | 20 | 200 | fits | 105,460 | 184 | 0.292 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-5.service.acmp.first.if0` | 292,955 | 2.930 | 20 | 20 | fits | 148,016 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-5.service.acmp.last.if0` | 397,579 | 3.976 | 20 | 20 | fits | 105,460 | 184 | 0.292 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-5.service.aecp.first.if0` | 148,579 | 1.486 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-5.service.aecp.last.if0` | 295,605 | 2.956 | 20 | 24 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-5.service.maap.first.if0` | 295,539 | 2.955 | 20 | 50 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-5.service.maap.last.if0` | 400,603 | 4.006 | 20 | 50 | fits | 105,460 | 184 | 0.292 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-5.service.srp.first.if0` | 487,133 | 4.871 | 20 | 20 | fits | 86,596 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-5.service.srp.last.if0` | 839,901 | 8.399 | 20 | 20 | fits | 81,476 | 39 | 0.667 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-6.adp_available.if0` | 356,272 | 3.563 | 20 | 20 | fits | 112,538 | 190 | 0.338 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-6.service.adp.first.if0` | 291,351 | 2.914 | 20 | 200 | fits | 148,016 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-6.service.adp.last.if0` | 403,273 | 4.033 | 20 | 200 | fits | 112,538 | 190 | 0.338 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-6.service.acmp.first.if0` | 292,275 | 2.923 | 20 | 20 | fits | 148,016 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-6.service.acmp.last.if0` | 403,977 | 4.040 | 20 | 20 | fits | 112,538 | 190 | 0.338 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-6.service.aecp.first.if0` | 147,899 | 1.479 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-6.service.aecp.last.if0` | 294,925 | 2.949 | 20 | 24 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-6.service.maap.first.if0` | 294,859 | 2.949 | 20 | 50 | fits | 148,016 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-6.service.maap.last.if0` | 407,001 | 4.070 | 20 | 50 | fits | 112,538 | 190 | 0.338 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-6.service.srp.first.if0` | 489,172 | 4.892 | 20 | 20 | fits | 82,237 | 28 | 0.763 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-6.service.srp.last.if0` | 842,728 | 8.427 | 20 | 20 | fits | 87,188 | 36 | 0.605 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-7.adp_available.if0` | 354,415 | 3.544 | 20 | 20 | fits | 113,947 | 196 | 0.275 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-7.service.adp.first.if0` | 287,841 | 2.878 | 20 | 200 | fits | 145,186 | 208 | 0.396 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-7.service.adp.last.if0` | 401,172 | 4.012 | 20 | 200 | fits | 113,947 | 196 | 0.275 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-7.service.acmp.first.if0` | 288,765 | 2.888 | 20 | 20 | fits | 145,186 | 208 | 0.396 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-7.service.acmp.last.if0` | 401,876 | 4.019 | 20 | 20 | fits | 113,947 | 196 | 0.275 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-7.service.aecp.first.if0` | 147,219 | 1.472 | 20 | 24 | fits | 145,766 | 142 | 0.405 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-7.service.aecp.last.if0` | 291,415 | 2.914 | 20 | 24 | fits | 145,186 | 208 | 0.396 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-7.service.maap.first.if0` | 291,349 | 2.913 | 20 | 50 | fits | 145,186 | 208 | 0.396 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-7.service.maap.last.if0` | 404,900 | 4.049 | 20 | 50 | fits | 113,947 | 196 | 0.275 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-7.service.srp.first.if0` | 487,188 | 4.872 | 20 | 20 | fits | 82,354 | 29 | 0.760 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-7.service.srp.last.if0` | 840,466 | 8.405 | 20 | 20 | fits | 86,756 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-0.adp_available.if0` | 361,442 | 3.614 | 20 | 20 | fits | 109,079 | 175 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.adp.first.if0` | 305,994 | 3.060 | 20 | 200 | fits | 147,280 | 230 | 0.387 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.adp.last.if0` | 414,457 | 4.145 | 20 | 200 | fits | 109,079 | 175 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.acmp.first.if0` | 306,918 | 3.069 | 20 | 20 | fits | 147,280 | 230 | 0.387 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.acmp.last.if0` | 415,161 | 4.152 | 20 | 20 | fits | 109,079 | 175 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.aecp.first.if0` | 153,637 | 1.536 | 20 | 24 | fits | 146,048 | 143 | 0.408 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.aecp.last.if0` | 309,568 | 3.096 | 20 | 24 | fits | 147,280 | 230 | 0.387 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.maap.first.if0` | 309,502 | 3.095 | 20 | 50 | fits | 147,280 | 230 | 0.387 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.maap.last.if0` | 418,185 | 4.182 | 20 | 50 | fits | 109,079 | 175 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.srp.first.if0` | 500,331 | 5.003 | 20 | 20 | fits | 82,212 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.srp.last.if0` | 836,525 | 8.365 | 20 | 20 | fits | 77,477 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-1.adp_available.if0` | 360,638 | 3.606 | 20 | 20 | fits | 109,079 | 175 | 0.281 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.adp.first.if0` | 305,190 | 3.052 | 20 | 200 | fits | 147,121 | 230 | 0.385 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.adp.last.if0` | 413,653 | 4.137 | 20 | 200 | fits | 109,079 | 175 | 0.281 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.acmp.first.if0` | 306,114 | 3.061 | 20 | 20 | fits | 147,121 | 230 | 0.385 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.acmp.last.if0` | 414,357 | 4.144 | 20 | 20 | fits | 109,079 | 175 | 0.281 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.aecp.first.if0` | 153,032 | 1.530 | 20 | 24 | fits | 146,123 | 143 | 0.409 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.aecp.last.if0` | 308,764 | 3.088 | 20 | 24 | fits | 147,121 | 230 | 0.385 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.maap.first.if0` | 308,698 | 3.087 | 20 | 50 | fits | 147,121 | 230 | 0.385 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.maap.last.if0` | 417,381 | 4.174 | 20 | 50 | fits | 109,079 | 175 | 0.281 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.srp.first.if0` | 499,527 | 4.995 | 20 | 20 | fits | 82,212 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.srp.last.if0` | 835,721 | 8.357 | 20 | 20 | fits | 77,477 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-2.adp_available.if0` | 347,407 | 3.474 | 20 | 20 | fits | 101,829 | 196 | 0.330 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.adp.first.if0` | 292,084 | 2.921 | 20 | 200 | fits | 147,989 | 238 | 0.354 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.adp.last.if0` | 393,297 | 3.933 | 20 | 200 | fits | 101,829 | 196 | 0.330 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.acmp.first.if0` | 293,008 | 2.930 | 20 | 20 | fits | 147,989 | 238 | 0.354 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.acmp.last.if0` | 394,001 | 3.940 | 20 | 20 | fits | 101,829 | 196 | 0.330 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.aecp.first.if0` | 148,659 | 1.487 | 20 | 24 | fits | 151,733 | 111 | 0.418 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.aecp.last.if0` | 295,658 | 2.957 | 20 | 24 | fits | 147,989 | 238 | 0.354 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.maap.first.if0` | 295,592 | 2.956 | 20 | 50 | fits | 147,989 | 238 | 0.354 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.maap.last.if0` | 397,025 | 3.970 | 20 | 50 | fits | 101,829 | 196 | 0.330 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.srp.first.if0` | 479,190 | 4.792 | 20 | 20 | fits | 82,231 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.srp.last.if0` | 835,796 | 8.358 | 20 | 20 | fits | 85,287 | 45 | 0.668 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-3.adp_available.if0` | 351,182 | 3.512 | 20 | 20 | fits | 108,905 | 175 | 0.276 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.adp.first.if0` | 295,629 | 2.956 | 20 | 200 | fits | 145,817 | 225 | 0.379 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.adp.last.if0` | 403,918 | 4.039 | 20 | 200 | fits | 108,905 | 175 | 0.276 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.acmp.first.if0` | 296,553 | 2.966 | 20 | 20 | fits | 145,817 | 225 | 0.379 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.acmp.last.if0` | 404,622 | 4.046 | 20 | 20 | fits | 108,905 | 175 | 0.276 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.aecp.first.if0` | 154,376 | 1.544 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.aecp.last.if0` | 299,203 | 2.992 | 20 | 24 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.maap.first.if0` | 299,137 | 2.991 | 20 | 50 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.maap.last.if0` | 407,646 | 4.076 | 20 | 50 | fits | 108,905 | 175 | 0.276 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.srp.first.if0` | 489,760 | 4.898 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.srp.last.if0` | 925,101 | 9.251 | 20 | 20 | fits | 86,832 | 36 | 0.598 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-4.adp_available.if0` | 350,502 | 3.505 | 20 | 20 | fits | 108,905 | 175 | 0.276 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.adp.first.if0` | 294,949 | 2.949 | 20 | 200 | fits | 145,817 | 225 | 0.379 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.adp.last.if0` | 403,238 | 4.032 | 20 | 200 | fits | 108,905 | 175 | 0.276 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.acmp.first.if0` | 295,873 | 2.959 | 20 | 20 | fits | 145,817 | 225 | 0.379 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.acmp.last.if0` | 403,942 | 4.039 | 20 | 20 | fits | 108,905 | 175 | 0.276 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.aecp.first.if0` | 153,696 | 1.537 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.aecp.last.if0` | 298,523 | 2.985 | 20 | 24 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.maap.first.if0` | 298,457 | 2.985 | 20 | 50 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.maap.last.if0` | 406,966 | 4.070 | 20 | 50 | fits | 108,905 | 175 | 0.276 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.srp.first.if0` | 489,309 | 4.893 | 20 | 20 | fits | 82,409 | 29 | 0.761 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.srp.last.if0` | 924,770 | 9.248 | 20 | 20 | fits | 86,813 | 36 | 0.595 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-5.adp_available.if0` | 349,822 | 3.498 | 20 | 20 | fits | 109,203 | 176 | 0.279 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.adp.first.if0` | 294,269 | 2.943 | 20 | 200 | fits | 145,817 | 225 | 0.379 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.adp.last.if0` | 402,856 | 4.029 | 20 | 200 | fits | 109,203 | 176 | 0.279 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.acmp.first.if0` | 295,193 | 2.952 | 20 | 20 | fits | 145,817 | 225 | 0.379 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.acmp.last.if0` | 403,560 | 4.036 | 20 | 20 | fits | 109,203 | 176 | 0.279 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.aecp.first.if0` | 153,016 | 1.530 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.aecp.last.if0` | 297,843 | 2.978 | 20 | 24 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.maap.first.if0` | 297,777 | 2.978 | 20 | 50 | fits | 145,817 | 225 | 0.379 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.maap.last.if0` | 406,584 | 4.066 | 20 | 50 | fits | 109,203 | 176 | 0.279 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.srp.first.if0` | 506,899 | 5.069 | 20 | 20 | fits | 88,597 | 41 | 0.763 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.srp.last.if0` | 922,124 | 9.221 | 20 | 20 | fits | 77,542 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-6.adp_available.if0` | 371,096 | 3.711 | 20 | 20 | fits | 119,504 | 188 | 0.354 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.adp.first.if0` | 293,920 | 2.939 | 20 | 200 | fits | 146,148 | 226 | 0.382 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.adp.last.if0` | 424,384 | 4.244 | 20 | 200 | fits | 119,504 | 188 | 0.354 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.acmp.first.if0` | 294,844 | 2.948 | 20 | 20 | fits | 146,148 | 226 | 0.382 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.acmp.last.if0` | 425,088 | 4.251 | 20 | 20 | fits | 119,504 | 188 | 0.354 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.aecp.first.if0` | 152,336 | 1.523 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.aecp.last.if0` | 297,494 | 2.975 | 20 | 24 | fits | 146,148 | 226 | 0.382 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.maap.first.if0` | 297,428 | 2.974 | 20 | 50 | fits | 146,148 | 226 | 0.382 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.maap.last.if0` | 428,112 | 4.281 | 20 | 50 | fits | 119,504 | 188 | 0.354 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.srp.first.if0` | 588,200 | 5.882 | 20 | 20 | fits | 82,275 | 29 | 0.761 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.srp.last.if0` | 924,426 | 9.244 | 20 | 20 | fits | 77,459 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-7.adp_available.if0` | 443,925 | 4.439 | 20 | 20 | fits | 116,704 | 202 | 0.300 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.adp.first.if0` | 303,206 | 3.032 | 20 | 200 | fits | 146,279 | 208 | 0.408 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.adp.last.if0` | 496,875 | 4.969 | 20 | 200 | fits | 116,704 | 202 | 0.300 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.acmp.first.if0` | 304,130 | 3.041 | 20 | 20 | fits | 146,279 | 208 | 0.408 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.acmp.last.if0` | 497,579 | 4.976 | 20 | 20 | fits | 116,704 | 202 | 0.300 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.aecp.first.if0` | 151,958 | 1.520 | 20 | 24 | fits | 146,000 | 143 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.aecp.last.if0` | 306,780 | 3.068 | 20 | 24 | fits | 146,279 | 208 | 0.408 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.maap.first.if0` | 306,714 | 3.067 | 20 | 50 | fits | 146,279 | 208 | 0.408 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.maap.last.if0` | 500,603 | 5.006 | 20 | 50 | fits | 116,704 | 202 | 0.300 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.srp.first.if0` | 582,654 | 5.827 | 20 | 20 | fits | 82,117 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.srp.last.if0` | 919,122 | 9.191 | 20 | 20 | fits | 77,688 | 33 | 0.619 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-0.adp_available.if0` | 343,240 | 3.432 | 20 | 20 | fits | 105,915 | 185 | 0.300 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.adp.first.if0` | 296,358 | 2.964 | 20 | 200 | fits | 147,993 | 214 | 0.374 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.adp.last.if0` | 401,657 | 4.017 | 20 | 200 | fits | 105,915 | 185 | 0.300 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.acmp.first.if0` | 297,282 | 2.973 | 20 | 20 | fits | 147,993 | 214 | 0.374 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.acmp.last.if0` | 402,361 | 4.024 | 20 | 20 | fits | 105,915 | 185 | 0.300 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.aecp.first.if0` | 152,929 | 1.529 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.aecp.last.if0` | 299,932 | 2.999 | 20 | 24 | fits | 147,993 | 214 | 0.374 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.maap.first.if0` | 299,866 | 2.999 | 20 | 50 | fits | 147,993 | 214 | 0.374 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.maap.last.if0` | 405,385 | 4.054 | 20 | 50 | fits | 105,915 | 185 | 0.300 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.srp.first.if0` | 502,375 | 5.024 | 20 | 20 | fits | 85,272 | 35 | 0.769 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.srp.last.if0` | 839,080 | 8.391 | 20 | 20 | fits | 77,542 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-1.adp_available.if0` | 358,372 | 3.584 | 20 | 20 | fits | 110,311 | 191 | 0.364 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.adp.first.if0` | 296,012 | 2.960 | 20 | 200 | fits | 148,327 | 215 | 0.377 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.adp.last.if0` | 417,110 | 4.171 | 20 | 200 | fits | 110,311 | 191 | 0.364 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.acmp.first.if0` | 296,936 | 2.969 | 20 | 20 | fits | 148,327 | 215 | 0.377 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.acmp.last.if0` | 417,814 | 4.178 | 20 | 20 | fits | 110,311 | 191 | 0.364 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.aecp.first.if0` | 152,249 | 1.522 | 20 | 24 | fits | 145,698 | 142 | 0.404 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.aecp.last.if0` | 299,586 | 2.996 | 20 | 24 | fits | 148,327 | 215 | 0.377 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.maap.first.if0` | 299,520 | 2.995 | 20 | 50 | fits | 148,327 | 215 | 0.377 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.maap.last.if0` | 420,838 | 4.208 | 20 | 50 | fits | 110,311 | 191 | 0.364 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.srp.first.if0` | 503,031 | 5.030 | 20 | 20 | fits | 82,259 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.srp.last.if0` | 838,667 | 8.387 | 20 | 20 | fits | 77,307 | 32 | 0.615 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-2.adp_available.if0` | 348,047 | 3.480 | 20 | 20 | fits | 112,800 | 193 | 0.284 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.adp.first.if0` | 300,971 | 3.010 | 20 | 200 | fits | 144,002 | 212 | 0.394 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.adp.last.if0` | 413,155 | 4.132 | 20 | 200 | fits | 112,800 | 193 | 0.284 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.acmp.first.if0` | 301,895 | 3.019 | 20 | 20 | fits | 144,002 | 212 | 0.394 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.acmp.last.if0` | 413,859 | 4.139 | 20 | 20 | fits | 112,800 | 193 | 0.284 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.aecp.first.if0` | 151,889 | 1.519 | 20 | 24 | fits | 146,018 | 143 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.aecp.last.if0` | 304,545 | 3.045 | 20 | 24 | fits | 144,002 | 212 | 0.394 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.maap.first.if0` | 304,479 | 3.045 | 20 | 50 | fits | 144,002 | 212 | 0.394 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.maap.last.if0` | 416,883 | 4.169 | 20 | 50 | fits | 112,800 | 193 | 0.284 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.srp.first.if0` | 499,032 | 4.990 | 20 | 20 | fits | 82,215 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.srp.last.if0` | 839,480 | 8.395 | 20 | 20 | fits | 81,663 | 38 | 0.646 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-3.adp_available.if0` | 350,903 | 3.509 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.adp.first.if0` | 295,457 | 2.955 | 20 | 200 | fits | 145,716 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.adp.last.if0` | 404,000 | 4.040 | 20 | 200 | fits | 109,159 | 175 | 0.282 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.acmp.first.if0` | 296,381 | 2.964 | 20 | 20 | fits | 145,716 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.acmp.last.if0` | 404,704 | 4.047 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.aecp.first.if0` | 154,305 | 1.543 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.aecp.last.if0` | 299,031 | 2.990 | 20 | 24 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.maap.first.if0` | 298,965 | 2.990 | 20 | 50 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.maap.last.if0` | 407,728 | 4.077 | 20 | 50 | fits | 109,159 | 175 | 0.282 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.srp.first.if0` | 489,842 | 4.898 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.srp.last.if0` | 830,620 | 8.306 | 20 | 20 | fits | 86,934 | 37 | 0.595 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-4.adp_available.if0` | 350,223 | 3.502 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.adp.first.if0` | 294,777 | 2.948 | 20 | 200 | fits | 145,716 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.adp.last.if0` | 403,320 | 4.033 | 20 | 200 | fits | 109,159 | 175 | 0.282 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.acmp.first.if0` | 295,701 | 2.957 | 20 | 20 | fits | 145,716 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.acmp.last.if0` | 404,024 | 4.040 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.aecp.first.if0` | 153,625 | 1.536 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.aecp.last.if0` | 298,351 | 2.984 | 20 | 24 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.maap.first.if0` | 298,285 | 2.983 | 20 | 50 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.maap.last.if0` | 407,048 | 4.070 | 20 | 50 | fits | 109,159 | 175 | 0.282 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.srp.first.if0` | 489,162 | 4.892 | 20 | 20 | fits | 82,180 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.srp.last.if0` | 865,867 | 8.659 | 20 | 20 | fits | 28,418 | 12 | 0.824 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-5.adp_available.if0` | 349,543 | 3.495 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.adp.first.if0` | 294,097 | 2.941 | 20 | 200 | fits | 145,716 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.adp.last.if0` | 402,640 | 4.026 | 20 | 200 | fits | 109,159 | 175 | 0.282 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.acmp.first.if0` | 295,021 | 2.950 | 20 | 20 | fits | 145,716 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.acmp.last.if0` | 403,344 | 4.033 | 20 | 20 | fits | 109,159 | 175 | 0.282 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.aecp.first.if0` | 152,945 | 1.529 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.aecp.last.if0` | 297,671 | 2.977 | 20 | 24 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.maap.first.if0` | 297,605 | 2.976 | 20 | 50 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.maap.last.if0` | 406,368 | 4.064 | 20 | 50 | fits | 109,159 | 175 | 0.282 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.srp.first.if0` | 492,882 | 4.929 | 20 | 20 | fits | 86,580 | 34 | 0.771 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.srp.last.if0` | 846,019 | 8.460 | 20 | 20 | fits | 86,769 | 36 | 0.592 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-6.adp_available.if0` | 355,186 | 3.552 | 20 | 20 | fits | 115,913 | 182 | 0.320 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.adp.first.if0` | 293,417 | 2.934 | 20 | 200 | fits | 145,716 | 225 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.adp.last.if0` | 408,714 | 4.087 | 20 | 200 | fits | 115,913 | 182 | 0.320 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.acmp.first.if0` | 294,341 | 2.943 | 20 | 20 | fits | 145,716 | 225 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.acmp.last.if0` | 409,418 | 4.094 | 20 | 20 | fits | 115,913 | 182 | 0.320 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.aecp.first.if0` | 152,265 | 1.523 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.aecp.last.if0` | 296,991 | 2.970 | 20 | 24 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.maap.first.if0` | 296,925 | 2.969 | 20 | 50 | fits | 145,716 | 225 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.maap.last.if0` | 412,442 | 4.124 | 20 | 50 | fits | 115,913 | 182 | 0.320 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.srp.first.if0` | 509,135 | 5.091 | 20 | 20 | fits | 85,015 | 35 | 0.766 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.srp.last.if0` | 846,117 | 8.461 | 20 | 20 | fits | 77,560 | 32 | 0.618 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-7.adp_available.if0` | 367,194 | 3.672 | 20 | 20 | fits | 118,092 | 202 | 0.336 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.adp.first.if0` | 292,127 | 2.921 | 20 | 200 | fits | 145,106 | 209 | 0.396 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.adp.last.if0` | 420,968 | 4.210 | 20 | 200 | fits | 118,092 | 202 | 0.336 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.acmp.first.if0` | 293,051 | 2.931 | 20 | 20 | fits | 145,106 | 209 | 0.396 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.acmp.last.if0` | 421,672 | 4.217 | 20 | 20 | fits | 118,092 | 202 | 0.336 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.aecp.first.if0` | 151,585 | 1.516 | 20 | 24 | fits | 145,870 | 142 | 0.407 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.aecp.last.if0` | 295,701 | 2.957 | 20 | 24 | fits | 145,106 | 209 | 0.396 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.maap.first.if0` | 295,635 | 2.956 | 20 | 50 | fits | 145,106 | 209 | 0.396 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.maap.last.if0` | 424,696 | 4.247 | 20 | 50 | fits | 118,092 | 202 | 0.336 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.srp.first.if0` | 506,840 | 5.068 | 20 | 20 | fits | 82,210 | 28 | 0.762 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.srp.last.if0` | 843,034 | 8.430 | 20 | 20 | fits | 77,477 | 32 | 0.618 |
| LINK_UP | `adp.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 5,600 | 0.056 | 20 | 200 | fits | 17,505 | 23 (39) | 0.573 |
| TMR_ADVERTISE expiry | `adp.tmr_advertise.if0` | 12,346 | 0.123 | 20 | 200 | fits | 2,117 | 10 (11) | 0.333 |
| ADP record, every channel at its refill rate, the longest | `save-held.held.adp.if0` | 152,032 | 1.520 | 20 | 200 | fits | 152,972 | 256 | 0.372 |
| ACMP record, every channel at its refill rate, the longest | `save-held.held.acmp.if0` | 224,694 | 2.247 | 20 | 20 | fits | 92,799 | 81 | 0.669 |
| AECP record, every channel at its refill rate, the longest | `save-held.held.aecp.if0` | 283,077 | 2.831 | 20 | 24 | fits | 92,006 | 58 | 0.549 |
| MAAP record, every channel at its refill rate, the longest | `save-held.held.maap.if0` | 185,219 | 1.852 | 20 | 50 | fits | 92,799 | 81 | 0.669 |
| SRP record, every channel at its refill rate, the longest | `save-held.held.srp.if0` | 775,405 | 7.754 | 20 | 20 | fits | 33,624 | 18 | 0.837 |
| an MRPDU its periodic timer owes, the longest | `save-held.mrpdu.periodic.if0` | 208,119 | 2.081 | 49 | 49 | fits | 0 | - | 0.000 |
| ADP record, every channel at its refill rate, the longest | `save-starved.held.adp.if0` | 152,032 | 1.520 | 20 | 200 | fits | 152,972 | 256 | 0.372 |
| ACMP record, every channel at its refill rate, the longest | `save-starved.held.acmp.if0` | 204,117 | 2.041 | 20 | 20 | fits | 136,888 | 270 | 0.219 |
| AECP record, every channel at its refill rate, the longest | `save-starved.held.aecp.if0` | 244,450 | 2.445 | 20 | 24 | fits | 76,987 | 60 | 0.449 |
| MAAP record, every channel at its refill rate, the longest | `save-starved.held.maap.if0` | 164,642 | 1.646 | 20 | 50 | fits | 136,888 | 270 | 0.219 |
| SRP record, every channel at its refill rate, the longest | `save-starved.held.srp.if0` | 789,338 | 7.893 | 20 | 20 | fits | 73,204 | 40 | 0.655 |
| an MRPDU its periodic timer owes, the longest | `save-starved.mrpdu.periodic.if0` | 243,804 | 2.438 | 49 | 49 | fits | 0 | - | 0.000 |
| TMR_DELAY, or the first TMR_NO_RESP | `acmp.tmr_no_resp1.if0` | 9,763 | 0.098 | 20 | 20 | fits | 26,534 | 21 (35) | 0.773 |
| the second TMR_NO_RESP | `acmp.tmr_no_resp2.if0` | 8,016 | 0.080 | 20 | 20 | fits | 22,640 | 17 (14) | 0.816 |
| TMR_RETRY | `acmp.tmr_retry.if0` | 13,725 | 0.137 | 20 | 20 | fits | 22,807 | 18 (14) | 0.823 |
| TMR_DELAY | `acmp.tmr_delay.if0` | 10,508 | 0.105 | 20 | 20 | fits | 26,773 | 21 (35) | 0.776 |
| startup declarations (LINK_UP) | `srp.startup.if0` | 73,297 | 0.733 | 20 | 20 | fits | 29,728 | 8 | 0.830 |
| Listener Ready RX (registrar) | `srp.listener_ready.if0` | 39,519 | 0.395 | 20 | 20 | fits | 39,585 | 12 | 0.887 |
| malformed MRPDU discard | `srp.malformed.if0` | 18,290 | 0.183 | 20 | 20 | fits | 18,356 | 12 | 0.723 |
| Domain RX -> declarations (JoinTime wait) | `srp.domain.if0` | 77,076 | 0.771 | 220 | 220 | fits | 53,204 | 6 | 0.914 |
| an event behind 15 others | `backlog.event.if0` | 157,237 | 1.572 | 20 | 200 | fits | 47,775 | 79 | 0.510 |
| an ACMP command behind a full acmp ring | `backlog.acmp_command.if0` | 403,448 | 4.034 | 20 | 20 | fits | 37,441 | 63 | 0.252 |
| ADP record released under the composed load, first | `backlog.service.adp.first.if0` | 398,757 | 3.988 | 20 | 200 | fits | 147,802 | 167 | 0.298 |
| ADP record released under the composed load, last | `backlog.service.adp.last.if0` | 398,141 | 3.981 | 20 | 200 | fits | 147,802 | 167 | 0.298 |
| ACMP record released under the composed load, first | `backlog.service.acmp.first.if0` | 394,435 | 3.944 | 20 | 20 | fits | 147,802 | 167 | 0.298 |
| ACMP record released under the composed load, last | `backlog.service.acmp.last.if0` | 431,040 | 4.310 | 20 | 20 | fits | 37,441 | 63 | 0.252 |
| AECP record released under the composed load, first | `backlog.service.aecp.first.if0` | 147,537 | 1.475 | 20 | 24 | fits | 148,428 | 148 | 0.423 |
| AECP record released under the composed load, last | `backlog.service.aecp.last.if0` | 397,085 | 3.971 | 20 | 24 | fits | 147,802 | 167 | 0.298 |
| MAAP record released under the composed load, first | `backlog.service.maap.first.if0` | 397,019 | 3.970 | 20 | 50 | fits | 147,802 | 167 | 0.298 |
| MAAP record released under the composed load, last | `backlog.service.maap.last.if0` | 396,623 | 3.966 | 20 | 50 | fits | 147,802 | 167 | 0.298 |
| SRP record released under the composed load, first | `backlog.service.srp.first.if0` | 433,998 | 4.340 | 20 | 20 | fits | 37,441 | 63 | 0.252 |
| SRP record released under the composed load, last | `backlog.service.srp.last.if0` | 487,835 | 4.878 | 20 | 20 | fits | 22,247 | 41 | 0.113 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog.adp_available.if0` | 342,314 | 3.423 | 20 | 20 | fits | 109,096 | 176 | 0.282 |
| ADP record released under the composed load, first | `backlog-adp.service.adp.first.if0` | 287,112 | 2.871 | 20 | 200 | fits | 145,461 | 225 | 0.377 |
| ADP record released under the composed load, last | `backlog-adp.service.adp.last.if0` | 395,592 | 3.956 | 20 | 200 | fits | 109,096 | 176 | 0.282 |
| ACMP record released under the composed load, first | `backlog-adp.service.acmp.first.if0` | 288,036 | 2.880 | 20 | 20 | fits | 145,461 | 225 | 0.377 |
| ACMP record released under the composed load, last | `backlog-adp.service.acmp.last.if0` | 396,296 | 3.963 | 20 | 20 | fits | 109,096 | 176 | 0.282 |
| AECP record released under the composed load, first | `backlog-adp.service.aecp.first.if0` | 146,215 | 1.462 | 20 | 24 | fits | 146,401 | 145 | 0.410 |
| AECP record released under the composed load, last | `backlog-adp.service.aecp.last.if0` | 290,686 | 2.907 | 20 | 24 | fits | 145,461 | 225 | 0.377 |
| MAAP record released under the composed load, first | `backlog-adp.service.maap.first.if0` | 290,620 | 2.906 | 20 | 50 | fits | 145,461 | 225 | 0.377 |
| MAAP record released under the composed load, last | `backlog-adp.service.maap.last.if0` | 399,320 | 3.993 | 20 | 50 | fits | 109,096 | 176 | 0.282 |
| SRP record released under the composed load, first | `backlog-adp.service.srp.first.if0` | 495,572 | 4.956 | 20 | 20 | fits | 84,601 | 35 | 0.767 |
| SRP record released under the composed load, last | `backlog-adp.service.srp.last.if0` | 836,117 | 8.361 | 20 | 20 | fits | 86,783 | 36 | 0.594 |
| an ENTITY_AVAILABLE behind the adp ring, its bucket refilling (observed) | `backlog.adp_available_refill.if0` | 11,280 | 0.113 | 20 | 20 | fits | 24,614 | 19 | 0.771 |
| ADP record released under the composed load, first | `backlog-adp-refill.service.adp.first.if0` | 287,112 | 2.871 | 20 | 200 | fits | 145,461 | 225 | 0.377 |
| ADP record released under the composed load, last | `backlog-adp-refill.service.adp.last.if0` | 27,961 | 0.280 | 20 | 200 | fits | 24,614 | 19 | 0.771 |
| ACMP record released under the composed load, first | `backlog-adp-refill.service.acmp.first.if0` | 288,036 | 2.880 | 20 | 20 | fits | 145,461 | 225 | 0.377 |
| ACMP record released under the composed load, last | `backlog-adp-refill.service.acmp.last.if0` | 385,672 | 3.857 | 20 | 20 | fits | 98,472 | 166 | 0.196 |
| AECP record released under the composed load, first | `backlog-adp-refill.service.aecp.first.if0` | 146,215 | 1.462 | 20 | 24 | fits | 146,401 | 145 | 0.410 |
| AECP record released under the composed load, last | `backlog-adp-refill.service.aecp.last.if0` | 290,686 | 2.907 | 20 | 24 | fits | 145,461 | 225 | 0.377 |
| MAAP record released under the composed load, first | `backlog-adp-refill.service.maap.first.if0` | 290,620 | 2.906 | 20 | 50 | fits | 145,461 | 225 | 0.377 |
| MAAP record released under the composed load, last | `backlog-adp-refill.service.maap.last.if0` | 388,696 | 3.887 | 20 | 50 | fits | 98,472 | 166 | 0.196 |
| SRP record released under the composed load, first | `backlog-adp-refill.service.srp.first.if0` | 484,781 | 4.848 | 20 | 20 | fits | 84,527 | 35 | 0.766 |
| SRP record released under the composed load, last | `backlog-adp-refill.service.srp.last.if0` | 825,326 | 8.253 | 20 | 20 | fits | 86,783 | 36 | 0.594 |
| a response with 7 frames owed ahead of it | `backlog.owed.if0` | 6,285,535 | 62.855 | 20 | 20 | MISS ceiling | 16,528 | 13 | 0.438 |
| an ACMP command behind the owed input | `backlog.owed_behind0.if0` | 6,302,073 | 63.021 | 20 | 20 | MISS ceiling | 16,535 | 13 | 0.420 |
| an ACMP command behind the owed input | `backlog.owed_behind1.if0` | 6,318,449 | 63.184 | 20 | 20 | MISS ceiling | 16,433 | 13 | 0.420 |
| an ACMP command behind the owed input | `backlog.owed_behind2.if0` | 6,334,896 | 63.349 | 20 | 20 | MISS ceiling | 16,523 | 13 | 0.412 |
| an ACMP command behind the owed input | `backlog.owed_behind3.if0` | 6,351,171 | 63.512 | 20 | 20 | MISS ceiling | 16,338 | 13 | 0.438 |
| ADP record released under the composed load, first | `backlog-owed.service.adp.first.if0` | 148,385 | 1.484 | 20 | 200 | fits | 146,122 | 222 | 0.412 |
| ADP record released under the composed load, last | `backlog-owed.service.adp.last.if0` | 227,927 | 2.279 | 20 | 200 | fits | 80,158 | 164 | 0.244 |
| ACMP record released under the composed load, first | `backlog-owed.service.acmp.first.if0` | 144,063 | 1.441 | 20 | 20 | fits | 146,122 | 222 | 0.412 |
| ACMP record released under the composed load, last | `backlog-owed.service.acmp.last.if0` | 6,205,911 | 62.059 | 20 | 20 | MISS ceiling | 27,700 | 15 | 0.669 |
| AECP record released under the composed load, first | `backlog-owed.service.aecp.first.if0` | 147,703 | 1.477 | 20 | 24 | fits | 146,122 | 222 | 0.412 |
| AECP record released under the composed load, last | `backlog-owed.service.aecp.last.if0` | 6,181,697 | 61.817 | 20 | 24 | MISS ceiling | 148,520 | 106 | 0.432 |
| MAAP record released under the composed load, first | `backlog-owed.service.maap.first.if0` | 146,647 | 1.466 | 20 | 50 | fits | 146,122 | 222 | 0.412 |
| MAAP record released under the composed load, last | `backlog-owed.service.maap.last.if0` | 226,409 | 2.264 | 20 | 50 | fits | 80,158 | 164 | 0.244 |
| SRP record released under the composed load, first | `backlog-owed.service.srp.first.if0` | 306,560 | 3.066 | 20 | 20 | fits | 80,217 | 28 | 0.746 |
| SRP record released under the composed load, last | `backlog-owed.service.srp.last.if0` | 644,583 | 6.446 | 20 | 20 | fits | 86,110 | 36 | 0.582 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | `acmp.entity_departing.if0` | 5,632 | 0.056 | 20 | 20 | fits | 20,968 | 13 (29) | 0.686 |
| ENTITY_AVAILABLE from its RX_HEAD (H-DISC) | `acmp.entity_available.if0` | 8,012 | 0.080 | 20 | 20 | fits | 24,092 | 19 (35) | 0.754 |
| TMR_NO_ADP (H-DISC) | `acmp.tmr_no_adp.if0` | 16,960 | 0.170 | 20 | 20 | fits | 26,555 | 21 (12) | 0.773 |
| first PROBE (LINK_UP) | `maap.probe1.if0` | 10,005 | 0.100 | 20 | 50 | fits | 23,932 | 43 | 0.676 |
| PROBE retransmission (TMR expiry) | `maap.probe2.if0` | 16,083 | 0.161 | 20 | 50 | fits | 19,683 | 35 | 0.585 |
| PROBE retransmission (TMR expiry) | `maap.probe3.if0` | 18,199 | 0.182 | 20 | 50 | fits | 19,666 | 35 | 0.581 |
| last PROBE retransmission (TMR expiry) | `maap.probe4.if0` | 11,396 | 0.114 | 20 | 50 | fits | 25,162 | 61 | 0.564 |
| ANNOUNCE (TMR expiry) | `maap.announce.if0` | 13,364 | 0.134 | 20 | 50 | fits | 25,162 | 61 | 0.564 |
| conflicting PROBE -> DEFEND | `maap.defend.if0` | 9,287 | 0.093 | 20 | 50 | fits | 19,368 | 30 | 0.588 |
| LINK_UP | `adp.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 5,600 | 0.056 | 20 | 200 | fits | 17,505 | 23 (39) | 0.573 |
| LINK_DOWN | `adp.link_down.if0` | 1,936 | 0.019 | 20 | 200 | fits | 19,473 | 23 (9) | 0.675 |
| LINK_UP | `adp.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 5,600 | 0.056 | 20 | 200 | fits | 17,505 | 23 (39) | 0.573 |
| GM_CHANGE | `adp.gm_change.if0` | 2,076 | 0.021 | 20 | 200 | fits | 12,636 | 17 (11) | 0.323 |
| LINK_UP | `adp.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 5,600 | 0.056 | 20 | 200 | fits | 17,505 | 23 (39) | 0.573 |
| RCV_ADP_DISCOVER | `adp.discover.if0` | 5,016 | 0.050 | 20 | 200 | fits | 14,189 | 16 (31) | 0.508 |
| LINK_UP | `adp.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 5,600 | 0.056 | 20 | 200 | fits | 17,505 | 23 (39) | 0.573 |
| RCV_ADP_DISCOVER (control) | `control.discover.if0` | 5,016 | 0.050 | 20 | 200 | fits | 14,189 | 16 (31) | 0.508 |
| set_name | `aecp_fanout.set_name.if0` | 55,369 | 0.554 | 20 | 24 | fits | 56,027 | 88 | 0.548 |
| set_clock_source | `aecp_fanout.set_clock_source.if0` | 52,751 | 0.528 | 20 | 24 | fits | 50,870 | 78 | 0.579 |
| set_control_identify_on | `aecp_fanout.set_control_identify_on.if0` | 38,338 | 0.383 | 20 | 24 | fits | 46,690 | 78 | 0.552 |
| set_control_identify_off | `aecp_fanout.set_control_identify_off.if0` | 49,054 | 0.491 | 20 | 24 | fits | 45,173 | 78 | 0.517 |
| remove_audio_mappings | `aecp_fanout.remove_audio_mappings.if0` | 50,945 | 0.509 | 20 | 24 | fits | 62,788 | 110 | 0.584 |
| add_audio_mappings | `aecp_fanout.add_audio_mappings.if0` | 262,419 | 2.624 | 20 | 24 | fits | 67,644 | 124 | 0.590 |
| set_sampling_rate | `aecp_fanout.set_sampling_rate.if0` | 321,135 | 3.211 | 20 | 24 | fits | 49,930 | 67 | 0.590 |
| lock_entity | `aecp_fanout.lock_entity.if0` | 49,625 | 0.496 | 20 | 24 | fits | 45,982 | 77 | 0.536 |
| unlock_entity | `aecp_fanout.unlock_entity.if0` | 39,000 | 0.390 | 20 | 24 | fits | 46,612 | 78 | 0.545 |
| BIND_RX | `acmp.bind_rx.if0` | 18,356 | 0.184 | 20 | 20 | fits | 38,157 | 26 (77) | 0.756 |
| PROBE_TX_RESPONSE | `acmp.probe_tx_response.if0` | 9,510 | 0.095 | 20 | 20 | fits | 28,176 | 19 (32) | 0.806 |
| GET_RX_STATE | `acmp.get_rx_state.if0` | 10,444 | 0.104 | 20 | 20 | fits | 22,642 | 15 (47) | 0.684 |
| UNBIND_RX | `acmp.unbind_rx.if0` | 14,997 | 0.150 | 20 | 20 | fits | 36,686 | 18 (50) | 0.822 |
| PROBE_TX, refused TALKER_DEST_MAC_FAIL | `acmp.probe_tx.if0` | 10,689 | 0.107 | 20 | 20 | fits | 22,664 | 17 (48) | 0.670 |
| GET_TX_STATE | `acmp.get_tx_state.if0` | 9,165 | 0.092 | 20 | 20 | fits | 21,477 | 16 (48) | 0.598 |
| DISCONNECT_TX | `acmp.disconnect_tx.if0` | 8,792 | 0.088 | 20 | 20 | fits | 20,726 | 16 (48) | 0.584 |
| GET_TX_CONNECTION, refused NOT_SUPPORTED | `acmp.get_tx_connection.if0` | 8,747 | 0.087 | 20 | 20 | fits | 20,567 | 16 (48) | 0.575 |
| register_unsolicited | `aecp.register_unsolicited.if0` | 15,701 | 0.157 | 20 | 24 | fits | 25,758 | 20 | 0.753 |
| READ_DESCRIPTOR (312 B) | `aecp.read_descriptor.t0.i0.c0.if0` | 26,424 | 0.264 | 20 | 24 | fits | 30,684 | 20 | 0.672 |
| READ_DESCRIPTOR (106 B) | `aecp.read_descriptor.t1.i0.c0.if0` | 21,405 | 0.214 | 20 | 24 | fits | 27,684 | 20 | 0.707 |
| READ_DESCRIPTOR (148 B) | `aecp.read_descriptor.t2.i0.c0.if0` | 22,433 | 0.224 | 20 | 24 | fits | 26,442 | 20 | 0.693 |
| READ_DESCRIPTOR (146 B) | `aecp.read_descriptor.t5.i1.c0.if0` | 23,316 | 0.233 | 20 | 24 | fits | 27,322 | 20 | 0.701 |
| READ_DESCRIPTOR (146 B) | `aecp.read_descriptor.t6.i1.c0.if0` | 20,880 | 0.209 | 20 | 24 | fits | 27,076 | 20 | 0.697 |
| READ_DESCRIPTOR (102 B) | `aecp.read_descriptor.t9.i0.c0.if0` | 22,316 | 0.223 | 20 | 24 | fits | 26,088 | 20 | 0.697 |
| READ_DESCRIPTOR (86 B) | `aecp.read_descriptor.t10.i2.c0.if0` | 20,446 | 0.204 | 20 | 24 | fits | 26,642 | 20 | 0.715 |
| READ_DESCRIPTOR (72 B) | `aecp.read_descriptor.t12.i0.c0.if0` | 22,236 | 0.222 | 20 | 24 | fits | 25,929 | 20 | 0.711 |
| READ_DESCRIPTOR (452 B) | `aecp.read_descriptor.t13.i0.c0.if0` | 22,856 | 0.229 | 20 | 24 | fits | 28,930 | 21 | 0.611 |
| READ_DESCRIPTOR (20 B) | `aecp.read_descriptor.t14.i0.c0.if0` | 21,816 | 0.218 | 20 | 24 | fits | 25,664 | 20 | 0.731 |
| READ_DESCRIPTOR (20 B) | `aecp.read_descriptor.t15.i0.c0.if0` | 21,881 | 0.219 | 20 | 24 | fits | 25,651 | 20 | 0.729 |
| READ_DESCRIPTOR (90 B) | `aecp.read_descriptor.t20.i24.c0.if0` | 19,842 | 0.198 | 20 | 24 | fits | 25,913 | 20 | 0.696 |
| READ_DESCRIPTOR (113 B) | `aecp.read_descriptor.t26.i0.c0.if0` | 23,471 | 0.235 | 20 | 24 | fits | 27,315 | 20 | 0.707 |
| READ_DESCRIPTOR (82 B) | `aecp.read_descriptor.t36.i0.c0.if0` | 20,258 | 0.203 | 20 | 24 | fits | 26,544 | 20 | 0.715 |
| get_configuration | `aecp.get_configuration.if0` | 19,470 | 0.195 | 20 | 24 | fits | 23,081 | 20 | 0.723 |
| entity_available | `aecp.entity_available.if0` | 17,413 | 0.174 | 20 | 24 | fits | 23,205 | 20 | 0.707 |
| get_name | `aecp.get_name.if0` | 20,392 | 0.204 | 20 | 24 | fits | 26,636 | 20 | 0.728 |
| get_counters, refused ENTITY_MISBEHAVING | `aecp.get_counters.if0` | 24,397 | 0.244 | 20 | 24 | fits | 28,419 | 26 | 0.702 |
| get_avb_info, refused ENTITY_MISBEHAVING | `aecp.get_avb_info.if0` | 21,626 | 0.216 | 20 | 24 | fits | 27,638 | 29 | 0.718 |
| get_as_path, refused ENTITY_MISBEHAVING | `aecp.get_as_path.if0` | 23,986 | 0.240 | 20 | 24 | fits | 26,809 | 29 | 0.724 |
| unknown_command, refused NOT_IMPLEMENTED | `aecp.unknown_command.if0` | 18,163 | 0.182 | 20 | 24 | fits | 24,079 | 20 | 0.731 |
| MVU GET_MILAN_INFO | `aecp.mvu_get_milan_info.if0` | 12,559 | 0.126 | 20 | 24 | fits | 22,946 | 20 | 0.700 |
| set_name | `aecp.set_name.if0` | 27,838 | 0.278 | 20 | 24 | fits | 43,922 | 42 | 0.736 |
| lock_entity | `aecp.lock_entity.if0` | 24,353 | 0.244 | 20 | 24 | fits | 35,386 | 33 | 0.769 |
| unlock_entity | `aecp.unlock_entity.if0` | 15,587 | 0.156 | 20 | 24 | fits | 35,638 | 32 | 0.780 |
| REMOVE_AUDIO_MAPPINGS of 63 (550 B notice) | `aecp_long.remove_audio_mappings.if0` | 143,965 | 1.440 | 20 | 24 | fits | 145,517 | 136 | 0.309 |
| ADD_AUDIO_MAPPINGS of 63 (550 B notice) | `aecp_long.add_audio_mappings.if0` | 284,637 | 2.846 | 20 | 24 | fits | 138,092 | 114 | 0.294 |
| COLLISION_INDICES of 63, refused BAD_ARGUMENTS | `aecp_long.refused.collision_indices.if0` | 235,820 | 2.358 | 20 | 24 | fits | 45,524 | 18 | 0.667 |
| COLLISION_VALUES of 63, refused BAD_ARGUMENTS | `aecp_long.refused.collision_values.if0` | 375,880 | 3.759 | 20 | 24 | fits | 81,886 | 17 | 0.671 |
| CONFLICT_LAST of 63, refused BAD_ARGUMENTS | `aecp_long.refused.conflict_last.if0` | 345,805 | 3.458 | 20 | 24 | fits | 91,792 | 17 | 0.668 |
| READ_DESCRIPTOR held for a token (#917) | `aecp.held.read_descriptor.if0` | 515,146 | 5.151 | 20 | 24 | fits | 30,588 | 17 | 0.698 |
| LINK_UP | `fixture.link_up.if0` | 2,306 | 0.023 | 20 | 200 | fits | 23,932 | 43 (11) | 0.676 |
| malformed MRPDU discard | `fixture.malformed.if0` | 18,433 | 0.184 | 20 | 20 | fits | 18,499 | 12 | 0.729 |
| SET_NAME fan-out to one registered controller | `fixture.set_name.if0` | 31,961 | 0.320 | 20 | 24 | fits | 44,651 | 42 | 0.756 |
| LINK_DOWN | `fixture.link_down.if0` | 2,249 | 0.022 | 20 | 200 | fits | 21,165 | 23 (9) | 0.727 |
| BIND_RX | `fixture.bind_rx.if0` | 18,978 | 0.190 | 20 | 20 | fits | 38,461 | 26 (77) | 0.763 |
| TMR_DELAY, or the first TMR_NO_RESP | `fixture.tmr_no_resp1.if0` | 19,230 | 0.192 | 20 | 20 | fits | 36,506 | 35 (35) | 0.757 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | `fixture.entity_departing.if0` | 5,421 | 0.054 | 20 | 20 | fits | 22,768 | 13 (29) | 0.768 |
| ADP record released under the composed load, first | `fixture.service.adp.first.if0` | 81,576 | 0.816 | 20 | 200 | fits | 81,680 | 77 | 0.730 |
| ADP record released under the composed load, last | `fixture.service.adp.last.if0` | 81,576 | 0.816 | 20 | 200 | fits | 81,680 | 77 | 0.730 |
| ACMP record released under the composed load, first | `fixture.service.acmp.first.if0` | 81,302 | 0.813 | 20 | 20 | fits | 81,680 | 77 | 0.730 |
| ACMP record released under the composed load, last | `fixture.service.acmp.last.if0` | 81,302 | 0.813 | 20 | 20 | fits | 81,680 | 77 | 0.730 |
| AECP record released under the composed load, first | `fixture.service.aecp.first.if0` | 81,510 | 0.815 | 20 | 24 | fits | 81,680 | 77 | 0.730 |
| AECP record released under the composed load, last | `fixture.service.aecp.last.if0` | 81,510 | 0.815 | 20 | 24 | fits | 81,680 | 77 | 0.730 |
| MAAP record released under the composed load, first | `fixture.service.maap.first.if0` | 81,444 | 0.814 | 20 | 50 | fits | 81,680 | 77 | 0.730 |
| MAAP record released under the composed load, last | `fixture.service.maap.last.if0` | 81,444 | 0.814 | 20 | 50 | fits | 81,680 | 77 | 0.730 |
| SRP record released under the composed load, first | `fixture.service.srp.first.if0` | 81,378 | 0.814 | 20 | 20 | fits | 81,680 | 77 | 0.730 |
| SRP record released under the composed load, last | `fixture.service.srp.last.if0` | 81,378 | 0.814 | 20 | 20 | fits | 81,680 | 77 | 0.730 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
