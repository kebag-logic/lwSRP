### 8x8-1if

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

4 of 87 paths and 7 of 963 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| BIND_RX | 0 | `acmp.bind_rx.if0` (acmp-cmd) | 0.194 (0.436) | fits | 0 acmp | 2 | 0 |
| DISCONNECT_TX | 0 | `acmp.disconnect_tx.if0` (acmp-cmd) | 0.086 (0.251) | fits | 0 acmp | 1 | 0 |
| ENTITY_AVAILABLE from its RX_HEAD (H-DISC) | 0 | `acmp.entity_available.if0` (acmp-disc) | 0.091 (0.299) | fits | 0 adp | 1 | 0 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | 0 | `fixture.entity_departing.if0` (fixture) | 0.086 (0.458) | fits | 0 adp | 2 | 0 |
| GET_RX_STATE | 0 | `acmp.get_rx_state.if0` (acmp-cmd) | 0.096 (0.263) | fits | 0 acmp | 1 | 0 |
| GET_TX_CONNECTION, refused NOT_SUPPORTED | 0 | `acmp.get_tx_connection.if0` (acmp-cmd) | 0.091 (0.265) | fits | 0 acmp | 1 | 0 |
| GET_TX_STATE | 0 | `acmp.get_tx_state.if0` (acmp-cmd) | 0.089 (0.259) | fits | 0 acmp | 1 | 0 |
| PROBE_TX, refused TALKER_DEST_MAC_FAIL | 0 | `acmp.probe_tx.if0` (acmp-cmd) | 0.097 (0.268) | fits | 0 acmp | 1 | 0 |
| PROBE_TX_RESPONSE | 0 | `acmp.probe_tx_response.if0` (acmp-cmd) | 0.097 (0.327) | fits | 0 acmp | 1 | 0 |
| TMR_DELAY | 0 | `acmp.tmr_delay.if0` (acmp-noresp) | 0.266 (0.651) | fits | 0 events | 1 | 0 |
| TMR_NO_ADP (H-DISC) | 0 | `acmp.tmr_no_adp.if0` (acmp-disc) | 0.205 (0.609) | fits | 0 events | 1 | 0 |
| TMR_DELAY, or the first TMR_NO_RESP | 0 | `acmp.tmr_no_resp1.if0` (acmp-noresp) | 0.204 (0.608) | fits | 0 events | 2 | 0 |
| the second TMR_NO_RESP | 0 | `acmp.tmr_no_resp2.if0` (acmp-noresp) | 0.156 (0.541) | fits | 0 events | 1 | 0 |
| TMR_NO_TK | 0 | `acmp.tmr_no_tk.if0` (acmp-notk) | 0.112 (0.547) | fits | 0 events | 1 | 0 |
| TMR_RETRY | 0 | `acmp.tmr_retry.if0` (acmp-noresp) | 0.265 (0.542) | fits | 0 events | 1 | 0 |
| UNBIND_RX | 0 | `acmp.unbind_rx.if0` (acmp-cmd) | 0.145 (0.410) | fits | 0 acmp | 1 | 0 |
| RCV_ADP_DISCOVER | 0 | `adp.discover.if0` (adp-discover) | 0.039 (0.181) | fits | 0 adp | 2 | 0 |
| GM_CHANGE | 0 | `adp.gm_change.if0` (adp-gm) | 0.019 (0.168) | fits | 0 events | 1 | 0 |
| LINK_DOWN | 0 | `fixture.link_down.if0` (fixture) | 0.021 (0.312) | fits | 0 events | 2 | 0 |
| LINK_UP | 0 | `adp.link_up.if0` (adp-advertise) | 0.021 (0.318) | fits | 0 events | 6 | 0 |
| TMR_ADVERTISE expiry | 0 | `adp.tmr_advertise.if0` (adp-advertise) | 0.063 (0.234) | fits | 0 events | 1 | 0 |
| TMR_DELAY expiry | 0 | `adp.tmr_delay.if0` (adp-advertise) | 0.062 (0.391) | fits | 0 events | 5 | 0 |
| entity_available | 0 | `aecp.entity_available.if0` (aecp) | 0.212 (0.556) | fits | 0 aecp | 1 | 0 |
| get_as_path, refused ENTITY_MISBEHAVING | 0 | `aecp.get_as_path.if0` (aecp) | 0.111 (0.448) | fits | 0 aecp | 1 | 0 |
| get_avb_info, refused ENTITY_MISBEHAVING | 0 | `aecp.get_avb_info.if0` (aecp) | 0.213 (0.559) | fits | 0 aecp | 1 | 0 |
| get_configuration | 0 | `aecp.get_configuration.if0` (aecp) | 0.185 (0.532) | fits | 0 aecp | 1 | 0 |
| get_counters, refused ENTITY_MISBEHAVING | 0 | `aecp.get_counters.if0` (aecp) | 0.255 (0.607) | fits | 0 aecp | 1 | 0 |
| get_name | 0 | `aecp.get_name.if0` (aecp) | 0.205 (0.551) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR held for a token (#917) | 0 | `aecp.held.read_descriptor.if0` (aecp-held) | 5.177 (5.526) | fits | 16 aecp | 1 | 0 |
| lock_entity | 0 | `aecp.lock_entity.if0` (aecp) | 0.234 (0.676) | fits | 0 aecp | 1 | 0 |
| MVU GET_MILAN_INFO | 0 | `aecp.mvu_get_milan_info.if0` (aecp) | 0.179 (0.521) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (312 B) | 0 | `aecp.read_descriptor.t0.i0.c0.if0` (aecp) | 0.271 (0.622) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (106 B) | 0 | `aecp.read_descriptor.t1.i0.c0.if0` (aecp) | 0.208 (0.554) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (86 B) | 0 | `aecp.read_descriptor.t10.i9.c0.if0` (aecp) | 0.199 (0.544) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (72 B) | 0 | `aecp.read_descriptor.t12.i0.c0.if0` (aecp) | 0.235 (0.581) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (452 B) | 0 | `aecp.read_descriptor.t13.i0.c0.if0` (aecp) | 0.283 (0.634) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (20 B) | 0 | `aecp.read_descriptor.t14.i7.c0.if0` (aecp) | 0.200 (0.546) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (20 B) | 0 | `aecp.read_descriptor.t15.i7.c0.if0` (aecp) | 0.231 (0.578) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (148 B) | 0 | `aecp.read_descriptor.t2.i0.c0.if0` (aecp) | 0.235 (0.580) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (90 B) | 0 | `aecp.read_descriptor.t20.i71.c0.if0` (aecp) | 0.201 (0.546) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (113 B) | 0 | `aecp.read_descriptor.t26.i0.c0.if0` (aecp) | 0.240 (0.587) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (96 B) | 0 | `aecp.read_descriptor.t36.i0.c0.if0` (aecp) | 0.206 (0.552) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (146 B) | 0 | `aecp.read_descriptor.t5.i8.c0.if0` (aecp) | 0.238 (0.586) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (146 B) | 0 | `aecp.read_descriptor.t6.i8.c0.if0` (aecp) | 0.209 (0.556) | fits | 0 aecp | 1 | 0 |
| READ_DESCRIPTOR (102 B) | 0 | `aecp.read_descriptor.t9.i0.c0.if0` (aecp) | 0.234 (0.579) | fits | 0 aecp | 1 | 0 |
| register_unsolicited | 0 | `aecp.register_unsolicited.if0` (aecp) | 0.174 (0.519) | fits | 0 aecp | 1 | 0 |
| set_name | 0 | `aecp.set_name.if0` (aecp) | 0.300 (0.749) | fits | 0 aecp | 1 | 0 |
| unknown_command, refused NOT_IMPLEMENTED | 0 | `aecp.unknown_command.if0` (aecp) | 0.224 (0.571) | fits | 0 aecp | 1 | 0 |
| unlock_entity | 0 | `aecp.unlock_entity.if0` (aecp) | 0.244 (0.637) | fits | 0 aecp | 1 | 0 |
| lock_entity | 0 | `aecp_fanout.lock_entity.if0` (aecp-fanout) | 0.364 (0.675) | fits | 0 aecp | 1 | 0 |
| set_clock_source | 0 | `aecp_fanout.set_clock_source.if0` (aecp-fanout) | 0.537 (0.922) | fits | 0 aecp | 1 | 0 |
| set_control_identify_on | 0 | `aecp_fanout.set_control_identify_on.if0` (aecp-fanout) | 0.373 (0.679) | fits | 0 aecp | 2 | 0 |
| set_name | 0 | `aecp_fanout.set_name.if0` (aecp-fanout) | 0.590 (0.941) | fits | 0 aecp | 1 | 0 |
| set_sampling_rate | 0 | `aecp_fanout.set_sampling_rate.if0` (aecp-fanout) | 0.521 (0.840) | fits | 0 aecp | 1 | 0 |
| unlock_entity | 0 | `aecp_fanout.unlock_entity.if0` (aecp-fanout) | 0.512 (0.830) | fits | 0 aecp | 1 | 0 |
| an ACMP command behind a full acmp ring | 0 | `backlog.acmp_command.if0` (backlog) | 4.446 (4.847) | fits | 11 acmp | 1 | 0 |
| an ENTITY_AVAILABLE behind a full adp ring | 0 | `backlog-adp@program-aged2-7.adp_available.if0` (backlog-adp@program-aged2-7) | 4.730 (5.484) | fits | 7 adp | 73 | 0 |
| an ENTITY_AVAILABLE behind the adp ring, its bucket refilling (observed) | 0 | `backlog.adp_available_refill.if0` (backlog-adp-refill) | 0.179 (0.566) | fits | 0 adp | 1 | 0 |
| an event behind 15 others | 0 | `backlog.event.if0` (backlog) | 1.645 (2.106) | fits | 15 events | 1 | 0 |
| a response with 7 frames owed ahead of it | 0 | `backlog.owed.if0` (backlog-owed) | 63.226 (63.565) | MISS ceiling | 7 acmp | 1 | 1 |
| an ACMP command behind the owed input | 0 | `backlog.owed_behind3.if0` (backlog-owed) | 64.072 (64.411) | MISS ceiling | 11 acmp | 4 | 4 |
| SET_NAME fan-out to one registered controller | 0 | `fixture.set_name.if0` (fixture) | 0.321 (0.457) | fits | 0 aecp | 1 | 0 |
| ACMP record, every channel at its refill rate, the longest | 0 | `save-burst.held.acmp.if0` (save-burst) | 2.713 | fits | 11 acmp | 4 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `save-flight.held.adp.if0` (save-flight) | 3.138 | fits | 7 adp | 4 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `save-flight.held.aecp.if0` (save-flight) | 3.693 | fits | 14 aecp | 4 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `save-flight.held.maap.if0` (save-flight) | 2.573 | fits | 6 maap | 4 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `save-starved.held.srp.if0` (save-starved) | 7.252 | fits | 31 srp | 4 | 0 |
| ANNOUNCE (TMR expiry) | 0 | `maap.announce.if0` (maap) | 0.278 (0.633) | fits | 0 events | 1 | 0 |
| conflicting PROBE -> DEFEND | 0 | `maap.defend.if0` (maap) | 0.132 (0.280) | fits | 0 maap | 1 | 0 |
| first PROBE (LINK_UP) | 0 | `maap.probe1.if0` (maap) | 0.141 (0.318) | fits | 0 events | 1 | 0 |
| last PROBE retransmission (TMR expiry) | 0 | `maap.probe4.if0` (maap) | 0.258 (0.633) | fits | 0 events | 1 | 0 |
| PROBE retransmission (TMR expiry) | 0 | `maap.probe3.if0` (maap) | 0.232 (0.566) | fits | 0 events | 2 | 0 |
| an MRPDU its join timer owes, the longest | 0 | `save-starved.mrpdu.periodic.if0` (save-starved) | 1.581 | fits | 0 srp | 10 | 0 |
| ACMP record released under the composed load, first | 0 | `backlog.service.acmp.first.if0` (backlog) | 4.215 | fits | 0 acmp | 77 | 0 |
| ACMP record released under the composed load, last | 0 | `backlog-owed.service.acmp.last.if0` (backlog-owed) | 62.226 | MISS ceiling | 11 acmp | 77 | 1 |
| ADP record released under the composed load, first | 0 | `backlog.service.adp.first.if0` (backlog) | 4.258 | fits | 0 adp | 77 | 0 |
| ADP record released under the composed load, last | 0 | `backlog-adp@program-aged2-7.service.adp.last.if0` (backlog-adp@program-aged2-7) | 5.408 | fits | 7 adp | 77 | 0 |
| AECP record released under the composed load, first | 0 | `backlog-adp@verify-0.service.aecp.first.if0` (backlog-adp@verify-0) | 2.409 | fits | 0 aecp | 77 | 0 |
| AECP record released under the composed load, last | 0 | `backlog-owed.service.aecp.last.if0` (backlog-owed) | 61.576 | MISS ceiling | 15 aecp | 77 | 1 |
| MAAP record released under the composed load, first | 0 | `backlog.service.maap.first.if0` (backlog) | 4.240 | fits | 0 maap | 77 | 0 |
| MAAP record released under the composed load, last | 0 | `backlog-adp@program-aged2-7.service.maap.last.if0` (backlog-adp@program-aged2-7) | 5.445 | fits | 6 maap | 77 | 0 |
| SRP record released under the composed load, first | 0 | `backlog-adp@program-aged2-7.service.srp.first.if0` (backlog-adp@program-aged2-7) | 6.722 | fits | 0 srp | 77 | 0 |
| SRP record released under the composed load, last | 0 | `backlog-adp@program-aged2-7.service.srp.last.if0` (backlog-adp@program-aged2-7) | 8.918 | fits | 31 srp | 77 | 0 |
| Domain RX -> declarations (JoinTime wait) | 0 | `srp.domain.if0` (srp) | 0.735 (0.790) | fits | 0 srp | 1 | 0 |
| Listener Ready RX (registrar) | 0 | `srp.listener_ready.if0` (srp) | 0.406 (0.406) | fits | 0 srp | 1 | 0 |
| malformed MRPDU discard | 0 | `fixture.malformed.if0` (fixture) | 0.222 (0.223) | fits | 0 srp | 2 | 0 |
| startup declarations (LINK_UP) | 0 | `srp.startup.if0` (srp) | 0.790 (0.865) | fits | 0 events | 1 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|
| backlog-adp@blank-0 | 0 | 13.894 | 9 | 151,572 (1.516) | yes | - |
| backlog-adp@blank-1 | 0 | 13.765 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-2 | 0 | 13.640 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-3 | 0 | 13.515 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-4 | 0 | 13.390 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-5 | 0 | 13.265 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-6 | 0 | 13.140 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@blank-7 | 0 | 13.015 | 9 | 151,666 (1.517) | yes | - |
| backlog-adp@program-0 | 0 | 9.763 | 7 | 155,089 (1.551) | yes | - |
| backlog-adp@program-1 | 0 | 9.513 | 7 | 155,089 (1.551) | yes | - |
| backlog-adp@program-2 | 0 | 10.211 | 7 | 155,126 (1.551) | yes | - |
| backlog-adp@program-3 | 0 | 10.162 | 7 | 155,185 (1.552) | yes | - |
| backlog-adp@program-4 | 0 | 9.912 | 7 | 155,185 (1.552) | yes | - |
| backlog-adp@program-5 | 1 | 9.380 | 6 | 149,515 (1.495) | yes | - |
| backlog-adp@program-6 | 0 | 9.375 | 6 | 149,515 (1.495) | yes | - |
| backlog-adp@program-7 | 0 | 11.861 | 9 | 152,037 (1.520) | yes | - |
| backlog-adp@verify-0 | 0 | 11.692 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-1 | 0 | 11.567 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-2 | 0 | 11.442 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-3 | 0 | 11.317 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-4 | 0 | 11.192 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-5 | 0 | 11.067 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-6 | 0 | 10.942 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@verify-7 | 0 | 10.817 | 7 | 151,774 (1.518) | yes | - |
| backlog-adp@blank-aged2-0 | 0 | 12.773 | 8 | 150,831 (1.508) | yes | - |
| backlog-adp@blank-aged2-1 | 0 | 11.908 | 8 | 150,831 (1.508) | yes | - |
| backlog-adp@blank-aged2-2 | 0 | 10.630 | 7 | 150,831 (1.508) | yes | - |
| backlog-adp@blank-aged2-3 | 0 | 13.689 | 9 | 150,831 (1.508) | yes | - |
| backlog-adp@blank-aged2-4 | 0 | 12.823 | 9 | 150,849 (1.508) | yes | - |
| backlog-adp@blank-aged2-5 | 0 | 11.527 | 6 | 149,383 (1.494) | yes | - |
| backlog-adp@blank-aged2-6 | 0 | 11.613 | 7 | 150,770 (1.508) | yes | - |
| backlog-adp@blank-aged2-7 | 0 | 15.751 | 10 | 155,089 (1.551) | yes | - |
| backlog-adp@blank-aged1-0 | 0 | 12.925 | 9 | 150,802 (1.508) | yes | - |
| backlog-adp@blank-aged1-1 | 0 | 11.928 | 8 | 150,802 (1.508) | yes | - |
| backlog-adp@blank-aged1-2 | 0 | 10.779 | 7 | 150,802 (1.508) | yes | - |
| backlog-adp@blank-aged1-3 | 0 | 10.821 | 7 | 150,802 (1.508) | yes | - |
| backlog-adp@blank-aged1-4 | 0 | 10.897 | 7 | 150,802 (1.508) | yes | - |
| backlog-adp@blank-aged1-5 | 0 | 12.871 | 9 | 150,896 (1.509) | yes | - |
| backlog-adp@blank-aged1-6 | 0 | 11.127 | 9 | 151,017 (1.510) | yes | - |
| backlog-adp@blank-aged1-7 | 0 | 10.897 | 7 | 154,947 (1.549) | yes | - |
| backlog-adp@program-aged2-0 | 0 | 10.143 | 7 | 150,786 (1.508) | yes | - |
| backlog-adp@program-aged2-1 | 0 | 10.894 | 10 | 150,805 (1.508) | yes | - |
| backlog-adp@program-aged2-2 | 1 | 10.138 | 7 | 149,145 (1.491) | yes | - |
| backlog-adp@program-aged2-3 | 0 | 10.264 | 7 | 150,614 (1.506) | yes | - |
| backlog-adp@program-aged2-4 | 0 | 10.321 | 7 | 150,614 (1.506) | yes | - |
| backlog-adp@program-aged2-5 | 0 | 10.215 | 7 | 150,614 (1.506) | yes | - |
| backlog-adp@program-aged2-6 | 0 | 10.305 | 7 | 150,614 (1.506) | yes | - |
| backlog-adp@program-aged2-7 | 0 | 12.939 | 10 | 155,883 (1.559) | yes | - |
| backlog-adp@program-aged1-0 | 0 | 10.177 | 7 | 150,614 (1.506) | yes | - |
| backlog-adp@program-aged1-1 | 0 | 11.942 | 9 | 149,177 (1.492) | yes | - |
| backlog-adp@program-aged1-2 | 0 | 10.666 | 9 | 150,686 (1.507) | yes | - |
| backlog-adp@program-aged1-3 | 0 | 10.368 | 8 | 150,754 (1.508) | yes | - |
| backlog-adp@program-aged1-4 | 0 | 10.276 | 7 | 150,707 (1.507) | yes | - |
| backlog-adp@program-aged1-5 | 0 | 10.177 | 7 | 150,707 (1.507) | yes | - |
| backlog-adp@program-aged1-6 | 0 | 10.256 | 7 | 150,707 (1.507) | yes | - |
| backlog-adp@program-aged1-7 | 0 | 10.163 | 6 | 149,034 (1.490) | yes | - |
| backlog-adp@verify-aged2-0 | 1 | 12.772 | 7 | 148,985 (1.490) | yes | - |
| backlog-adp@verify-aged2-1 | 0 | 11.893 | 8 | 150,549 (1.505) | yes | - |
| backlog-adp@verify-aged2-2 | 0 | 10.766 | 7 | 150,549 (1.505) | yes | - |
| backlog-adp@verify-aged2-3 | 0 | 11.836 | 9 | 150,603 (1.506) | yes | - |
| backlog-adp@verify-aged2-4 | 0 | 11.615 | 7 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged2-5 | 0 | 11.670 | 7 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged2-6 | 1 | 11.597 | 6 | 148,871 (1.489) | yes | - |
| backlog-adp@verify-aged2-7 | 0 | 15.767 | 10 | 153,146 (1.531) | yes | - |
| backlog-adp@verify-aged1-0 | 0 | 12.770 | 8 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged1-1 | 0 | 11.916 | 8 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged1-2 | 0 | 10.902 | 7 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged1-3 | 0 | 10.810 | 7 | 150,642 (1.506) | yes | - |
| backlog-adp@verify-aged1-4 | 0 | 12.963 | 9 | 150,721 (1.507) | yes | - |
| backlog-adp@verify-aged1-5 | 0 | 13.026 | 9 | 150,740 (1.507) | yes | - |
| backlog-adp@verify-aged1-6 | 0 | 10.833 | 7 | 150,549 (1.505) | yes | - |
| backlog-adp@verify-aged1-7 | 0 | 10.876 | 7 | 153,260 (1.533) | yes | - |
| backlog | 0 | 5.953 | 7 | 155,624 (1.556) | yes | - |
| backlog-adp | 0 | 8.536 | 7 | 150,823 (1.508) | yes | - |
| backlog-adp-refill | 0 | 40.890 | 21 | 150,823 (1.508) | yes | - |
| backlog-owed | 0 | 64.982 | 24 | 151,632 (1.516) | yes | - |
| fixture | 0 | 1.367 | 2 | 86,181 (0.862) | yes | - |

Composed maximum over the 4 backlog windows: 155,624 CPU cycles (1.556 ms), backlog.
Over the windows that released their whole load only: 155,624 (1.556 ms), backlog.

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| save-second | 146988 | 0 | 48,487 (0.485) | fits |
| save-burst | 2724 | 0 | 156,670 (1.567) | fits |
| save-held | 2884 | 0 | 157,621 (1.576) | fits |
| save-starved | 70662 | 0 | 157,621 (1.576) | fits |
| save-flight | 2498 | 0 | 157,621 (1.576) | fits |
| acmp-notk | 3604 | 0 | 110,157 (1.102) | fits |
| backlog-adp@blank-0 | 472 | 0 | 151,572 (1.516) | fits |
| backlog-adp@blank-1 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-2 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-3 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-4 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-5 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-6 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@blank-7 | 472 | 0 | 151,666 (1.517) | fits |
| backlog-adp@program-0 | 504 | 0 | 155,089 (1.551) | fits |
| backlog-adp@program-1 | 504 | 0 | 155,089 (1.551) | fits |
| backlog-adp@program-2 | 504 | 0 | 155,126 (1.551) | fits |
| backlog-adp@program-3 | 504 | 0 | 155,185 (1.552) | fits |
| backlog-adp@program-4 | 504 | 0 | 155,185 (1.552) | fits |
| backlog-adp@program-5 | 504 | 0 | 154,331 (1.543) | fits |
| backlog-adp@program-6 | 504 | 0 | 154,331 (1.543) | fits |
| backlog-adp@program-7 | 507 | 0 | 152,037 (1.520) | fits |
| backlog-adp@verify-0 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-1 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-2 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-3 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-4 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-5 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-6 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@verify-7 | 525 | 0 | 151,774 (1.518) | fits |
| backlog-adp@blank-aged2-0 | 755 | 0 | 150,831 (1.508) | fits |
| backlog-adp@blank-aged2-1 | 763 | 0 | 150,831 (1.508) | fits |
| backlog-adp@blank-aged2-2 | 769 | 0 | 150,831 (1.508) | fits |
| backlog-adp@blank-aged2-3 | 779 | 0 | 150,831 (1.508) | fits |
| backlog-adp@blank-aged2-4 | 787 | 0 | 150,849 (1.508) | fits |
| backlog-adp@blank-aged2-5 | 792 | 0 | 150,770 (1.508) | fits |
| backlog-adp@blank-aged2-6 | 800 | 0 | 150,770 (1.508) | fits |
| backlog-adp@blank-aged2-7 | 811 | 0 | 155,089 (1.551) | fits |
| backlog-adp@blank-aged1-0 | 695 | 0 | 150,802 (1.508) | fits |
| backlog-adp@blank-aged1-1 | 702 | 0 | 150,802 (1.508) | fits |
| backlog-adp@blank-aged1-2 | 708 | 0 | 150,802 (1.508) | fits |
| backlog-adp@blank-aged1-3 | 716 | 0 | 150,802 (1.508) | fits |
| backlog-adp@blank-aged1-4 | 724 | 0 | 150,802 (1.508) | fits |
| backlog-adp@blank-aged1-5 | 733 | 0 | 150,896 (1.509) | fits |
| backlog-adp@blank-aged1-6 | 741 | 0 | 151,017 (1.510) | fits |
| backlog-adp@blank-aged1-7 | 747 | 0 | 154,947 (1.549) | fits |
| backlog-adp@program-aged2-0 | 771 | 0 | 150,786 (1.508) | fits |
| backlog-adp@program-aged2-1 | 782 | 0 | 150,805 (1.508) | fits |
| backlog-adp@program-aged2-2 | 787 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged2-3 | 794 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged2-4 | 802 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged2-5 | 809 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged2-6 | 817 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged2-7 | 828 | 0 | 155,883 (1.559) | fits |
| backlog-adp@program-aged1-0 | 710 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged1-1 | 720 | 0 | 150,614 (1.506) | fits |
| backlog-adp@program-aged1-2 | 727 | 0 | 150,686 (1.507) | fits |
| backlog-adp@program-aged1-3 | 734 | 0 | 150,754 (1.508) | fits |
| backlog-adp@program-aged1-4 | 741 | 0 | 150,707 (1.507) | fits |
| backlog-adp@program-aged1-5 | 748 | 0 | 150,707 (1.507) | fits |
| backlog-adp@program-aged1-6 | 756 | 0 | 150,707 (1.507) | fits |
| backlog-adp@program-aged1-7 | 763 | 0 | 150,707 (1.507) | fits |
| backlog-adp@verify-aged2-0 | 814 | 0 | 150,549 (1.505) | fits |
| backlog-adp@verify-aged2-1 | 822 | 0 | 150,549 (1.505) | fits |
| backlog-adp@verify-aged2-2 | 829 | 0 | 150,549 (1.505) | fits |
| backlog-adp@verify-aged2-3 | 838 | 0 | 150,603 (1.506) | fits |
| backlog-adp@verify-aged2-4 | 844 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged2-5 | 852 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged2-6 | 859 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged2-7 | 870 | 0 | 153,146 (1.531) | fits |
| backlog-adp@verify-aged1-0 | 753 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged1-1 | 761 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged1-2 | 768 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged1-3 | 775 | 0 | 150,642 (1.506) | fits |
| backlog-adp@verify-aged1-4 | 785 | 0 | 150,721 (1.507) | fits |
| backlog-adp@verify-aged1-5 | 793 | 0 | 150,740 (1.507) | fits |
| backlog-adp@verify-aged1-6 | 798 | 0 | 150,549 (1.505) | fits |
| backlog-adp@verify-aged1-7 | 806 | 0 | 153,260 (1.533) | fits |
| adp-advertise | 598 | 0 | 33,203 (0.332) | fits |
| acmp-noresp | 1910 | 0 | 110,104 (1.101) | fits |
| save | 610 | 0 | 81,044 (0.810) | fits |
| srp | 290 | 0 | 44,575 (0.446) | fits |
| backlog | 286 | 0 | 155,624 (1.556) | fits |
| backlog-adp | 309 | 0 | 150,823 (1.508) | fits |
| backlog-adp-refill | 323 | 0 | 150,823 (1.508) | fits |
| backlog-owed | 309 | 0 | 151,632 (1.516) | fits |
| acmp-disc | 902 | 0 | 110,080 (1.101) | fits |
| maap | 184 | 0 | 33,203 (0.332) | fits |
| adp-link | 89 | 0 | 41,916 (0.419) | fits |
| adp-gm | 88 | 0 | 31,840 (0.318) | fits |
| adp-discover | 88 | 0 | 31,840 (0.318) | fits |
| control | 88 | 0 | 31,840 (0.318) | fits |
| aecp-fanout | 110 | 0 | 57,454 (0.575) | fits |
| acmp-cmd | 88 | 0 | 43,579 (0.436) | fits |
| aecp | 114 | 0 | 44,568 (0.446) | fits |
| aecp-held | 105 | 0 | 37,807 (0.378) | fits |
| datapath-events | 119 | 0 | 31,840 (0.318) | fits |
| fixture | 161 | 0 | 86,181 (0.862) | fits |

Aged windows, opened with THE STEP's age at its limit or one short of it (save_window.aged_window): the aged steps among the window's records and after them (start after the window opened, CPU time, the step) and the window's tightest row:

| Group | Age at opening | Aged steps among its records | After them | Tightest row | ms (budget) | Margin ms |
|---|---:|---|---|---|---:|---:|
| backlog-adp@blank-aged2-0 | 2 | none | none | `backlog-adp@blank-aged2-0.service.srp.last.if0` | 7.986 (20) | 12.014 |
| backlog-adp@blank-aged2-1 | 2 | none | none | `backlog-adp@blank-aged2-1.service.srp.last.if0` | 8.029 (20) | 11.971 |
| backlog-adp@blank-aged2-2 | 2 | none | +8.024 ms, 76,405 (0.764 ms), read-back | `backlog-adp@blank-aged2-2.service.srp.last.if0` | 7.986 (20) | 12.014 |
| backlog-adp@blank-aged2-3 | 2 | +7.087 ms, 76,395 (0.764 ms), read-back | none | `backlog-adp@blank-aged2-3.service.srp.last.if0` | 8.806 (20) | 11.194 |
| backlog-adp@blank-aged2-4 | 2 | +5.887 ms, 76,479 (0.765 ms), read-back | none | `backlog-adp@blank-aged2-4.service.srp.last.if0` | 8.843 (20) | 11.157 |
| backlog-adp@blank-aged2-5 | 2 | +5.652 ms, 76,316 (0.763 ms), read-back | none | `backlog-adp@blank-aged2-5.service.srp.last.if0` | 8.752 (20) | 11.248 |
| backlog-adp@blank-aged2-6 | 2 | +4.459 ms, 76,134 (0.761 ms), read-back | none | `backlog-adp@blank-aged2-6.service.srp.last.if0` | 8.836 (20) | 11.164 |
| backlog-adp@blank-aged2-7 | 2 | +3.169 ms, 75,970 (0.760 ms), read-back | none | `backlog-adp@blank-aged2-7.service.srp.last.if0` | 8.863 (20) | 11.137 |
| backlog-adp@blank-aged1-0 | 1 | none | none | `backlog-adp@blank-aged1-0.service.srp.last.if0` | 7.847 (20) | 12.153 |
| backlog-adp@blank-aged1-1 | 1 | none | none | `backlog-adp@blank-aged1-1.service.srp.last.if0` | 8.052 (20) | 11.948 |
| backlog-adp@blank-aged1-2 | 1 | none | none | `backlog-adp@blank-aged1-2.service.srp.last.if0` | 8.001 (20) | 11.999 |
| backlog-adp@blank-aged1-3 | 1 | none | none | `backlog-adp@blank-aged1-3.service.srp.last.if0` | 8.041 (20) | 11.959 |
| backlog-adp@blank-aged1-4 | 1 | none | none | `backlog-adp@blank-aged1-4.service.srp.last.if0` | 8.114 (20) | 11.886 |
| backlog-adp@blank-aged1-5 | 1 | none | none | `backlog-adp@blank-aged1-5.service.srp.last.if0` | 8.004 (20) | 11.996 |
| backlog-adp@blank-aged1-6 | 1 | none | none | `backlog-adp@blank-aged1-6.service.srp.last.if0` | 8.057 (20) | 11.943 |
| backlog-adp@blank-aged1-7 | 1 | none | none | `backlog-adp@blank-aged1-7.service.srp.last.if0` | 8.120 (20) | 11.880 |
| backlog-adp@program-aged2-0 | 2 | none | none | `backlog-adp@program-aged2-0.service.srp.last.if0` | 7.969 (20) | 12.031 |
| backlog-adp@program-aged2-1 | 2 | none | none | `backlog-adp@program-aged2-1.service.srp.last.if0` | 8.029 (20) | 11.971 |
| backlog-adp@program-aged2-2 | 2 | none | +8.161 ms, 80,107 (0.801 ms), issue | `backlog-adp@program-aged2-2.service.srp.last.if0` | 7.784 (20) | 12.216 |
| backlog-adp@program-aged2-3 | 2 | none | none | `backlog-adp@program-aged2-3.service.srp.last.if0` | 8.847 (20) | 11.153 |
| backlog-adp@program-aged2-4 | 2 | none | none | `backlog-adp@program-aged2-4.service.srp.last.if0` | 8.903 (20) | 11.097 |
| backlog-adp@program-aged2-5 | 2 | +5.790 ms, 80,702 (0.807 ms), issue | none | `backlog-adp@program-aged2-5.service.srp.last.if0` | 8.800 (20) | 11.200 |
| backlog-adp@program-aged2-6 | 2 | +4.616 ms, 80,373 (0.804 ms), issue | none | `backlog-adp@program-aged2-6.service.srp.last.if0` | 8.884 (20) | 11.116 |
| backlog-adp@program-aged2-7 | 2 | +3.288 ms, 80,296 (0.803 ms), issue | none | `backlog-adp@program-aged2-7.service.srp.last.if0` | 8.918 (20) | 11.082 |
| backlog-adp@program-aged1-0 | 1 | none | none | `backlog-adp@program-aged1-0.service.srp.last.if0` | 8.009 (20) | 11.991 |
| backlog-adp@program-aged1-1 | 1 | none | none | `backlog-adp@program-aged1-1.service.srp.last.if0` | 7.924 (20) | 12.076 |
| backlog-adp@program-aged1-2 | 1 | none | none | `backlog-adp@program-aged1-2.service.srp.last.if0` | 7.991 (20) | 12.009 |
| backlog-adp@program-aged1-3 | 1 | none | none | `backlog-adp@program-aged1-3.service.srp.last.if0` | 7.916 (20) | 12.084 |
| backlog-adp@program-aged1-4 | 1 | none | none | `backlog-adp@program-aged1-4.service.srp.last.if0` | 8.111 (20) | 11.889 |
| backlog-adp@program-aged1-5 | 1 | none | none | `backlog-adp@program-aged1-5.service.srp.last.if0` | 8.011 (20) | 11.989 |
| backlog-adp@program-aged1-6 | 1 | none | none | `backlog-adp@program-aged1-6.service.srp.last.if0` | 8.088 (20) | 11.912 |
| backlog-adp@program-aged1-7 | 1 | none | none | `backlog-adp@program-aged1-7.service.srp.last.if0` | 7.993 (20) | 12.007 |
| backlog-adp@verify-aged2-0 | 2 | none | none | `backlog-adp@verify-aged2-0.service.srp.last.if0` | 7.938 (20) | 12.062 |
| backlog-adp@verify-aged2-1 | 2 | none | none | `backlog-adp@verify-aged2-1.service.srp.last.if0` | 7.976 (20) | 12.024 |
| backlog-adp@verify-aged2-2 | 2 | none | +8.132 ms, 77,127 (0.771 ms), read-back | `backlog-adp@verify-aged2-2.service.srp.last.if0` | 8.094 (20) | 11.906 |
| backlog-adp@verify-aged2-3 | 2 | +7.010 ms, 77,297 (0.773 ms), read-back | none | `backlog-adp@verify-aged2-3.service.srp.last.if0` | 8.740 (20) | 11.260 |
| backlog-adp@verify-aged2-4 | 2 | +6.933 ms, 77,207 (0.772 ms), read-back | none | `backlog-adp@verify-aged2-4.service.srp.last.if0` | 8.690 (20) | 11.310 |
| backlog-adp@verify-aged2-5 | 2 | +5.748 ms, 77,291 (0.773 ms), read-back | none | `backlog-adp@verify-aged2-5.service.srp.last.if0` | 8.865 (20) | 11.135 |
| backlog-adp@verify-aged2-6 | 2 | +4.406 ms, 76,946 (0.769 ms), read-back | none | `backlog-adp@verify-aged2-6.service.srp.last.if0` | 8.792 (20) | 11.208 |
| backlog-adp@verify-aged2-7 | 2 | +3.093 ms, 76,795 (0.768 ms), read-back | none | `backlog-adp@verify-aged2-7.service.srp.last.if0` | 8.813 (20) | 11.187 |
| backlog-adp@verify-aged1-0 | 1 | none | none | `backlog-adp@verify-aged1-0.service.srp.last.if0` | 7.938 (20) | 12.062 |
| backlog-adp@verify-aged1-1 | 1 | none | none | `backlog-adp@verify-aged1-1.service.srp.last.if0` | 8.001 (20) | 11.999 |
| backlog-adp@verify-aged1-2 | 1 | none | none | `backlog-adp@verify-aged1-2.service.srp.last.if0` | 8.093 (20) | 11.907 |
| backlog-adp@verify-aged1-3 | 1 | none | none | `backlog-adp@verify-aged1-3.service.srp.last.if0` | 7.998 (20) | 12.002 |
| backlog-adp@verify-aged1-4 | 1 | none | none | `backlog-adp@verify-aged1-4.service.srp.last.if0` | 8.020 (20) | 11.980 |
| backlog-adp@verify-aged1-5 | 1 | none | none | `backlog-adp@verify-aged1-5.service.srp.last.if0` | 8.111 (20) | 11.889 |
| backlog-adp@verify-aged1-6 | 1 | none | none | `backlog-adp@verify-aged1-6.service.srp.last.if0` | 7.904 (20) | 12.096 |
| backlog-adp@verify-aged1-7 | 1 | none | none | `backlog-adp@verify-aged1-7.service.srp.last.if0` | 8.069 (20) | 11.931 |

Least margin over the aged windows: 11.082 ms, `backlog-adp@program-aged2-7.service.srp.last.if0` at 8.918 ms.

Saves, from the change to durable (save_window.bound_ms: the first-dirty window, or the rest of a save in flight, then each step at most CTRL_LOOP_STEP_AGE + 1 ticks after the one before):

| Group | Durable ms | Stated worst case ms | Steps | Save in flight, records | Longest gap between flash steps, ms | Grandmaster flood | Verdict |
|---|---:|---:|---:|---:|---:|---|---|
| save-second | 22829.559 | 22,870 | 382 | 2 | 31.397 | yes | within |
| save-held | 1324.870 | 12,470 | 382 | - | 42.066 | no | within |
| save-starved | 12447.611 | 12,470 | 382 | - | 32.899 | yes | within |
| save | 1290.072 | 12,470 | 382 | - | 98.977 | no | within |

Names from their response to durable (save_burst.py; #920, #665's ruling of 2026-11-15, item 1):

| Group | Names | Latest, ms (name) | Target ms | Saves | Not durable | Over | At the cut, or the next save | Verdict |
|---|---:|---:|---:|---:|---|---|---|---|
| save-burst | 107 | 1335.800 (0) | 5,000 | 7 | - | - | sequence 7, 0 missing | within |
| save-flight | 1 | 610.769 (0) | 5,000 | 2 | - | - | 59 steps (want 59), 22.393 ms | within |

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| save-second | 1080 | 81,637 (0.816) | 78,530 (0.785) |
| save-burst | 4088 | 98,159 (0.982) | 78,144 (0.781) |
| save-held | 1912 | 95,041 (0.950) | 77,881 (0.779) |
| save-starved | 698 | 82,301 (0.823) | 78,695 (0.787) |
| save-flight | 2068 | 98,071 (0.981) | 78,135 (0.781) |
| acmp-notk | 1416 | 110,157 (1.102) | 78,376 (0.784) |
| backlog-adp@blank-0 | 384 | 98,167 (0.982) | 75,657 (0.757) |
| backlog-adp@blank-1 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-2 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-3 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-4 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-5 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-6 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@blank-7 | 384 | 98,396 (0.984) | 75,713 (0.757) |
| backlog-adp@program-0 | 491 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-1 | 491 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-2 | 492 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-3 | 493 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-4 | 493 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-5 | 493 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-6 | 493 | 97,168 (0.972) | 77,819 (0.778) |
| backlog-adp@program-7 | 497 | 102,596 (1.026) | 78,550 (0.785) |
| backlog-adp@verify-0 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-1 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-2 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-3 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-4 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-5 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-6 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-7 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@blank-aged2-0 | 381 | 92,637 (0.926) | 75,872 (0.759) |
| backlog-adp@blank-aged2-1 | 380 | 92,710 (0.927) | 75,872 (0.759) |
| backlog-adp@blank-aged2-2 | 379 | 93,351 (0.934) | 75,614 (0.756) |
| backlog-adp@blank-aged2-3 | 382 | 93,562 (0.936) | 75,621 (0.756) |
| backlog-adp@blank-aged2-4 | 381 | 93,692 (0.937) | 75,621 (0.756) |
| backlog-adp@blank-aged2-5 | 380 | 92,181 (0.922) | 75,642 (0.756) |
| backlog-adp@blank-aged2-6 | 380 | 92,448 (0.924) | 75,683 (0.757) |
| backlog-adp@blank-aged2-7 | 384 | 93,786 (0.938) | 75,642 (0.756) |
| backlog-adp@blank-aged1-0 | 381 | 91,549 (0.915) | 75,821 (0.758) |
| backlog-adp@blank-aged1-1 | 380 | 92,445 (0.924) | 75,872 (0.759) |
| backlog-adp@blank-aged1-2 | 379 | 92,637 (0.926) | 75,872 (0.759) |
| backlog-adp@blank-aged1-3 | 379 | 92,710 (0.927) | 75,872 (0.759) |
| backlog-adp@blank-aged1-4 | 379 | 92,988 (0.930) | 75,872 (0.759) |
| backlog-adp@blank-aged1-5 | 381 | 98,185 (0.982) | 75,872 (0.759) |
| backlog-adp@blank-aged1-6 | 379 | 91,549 (0.915) | 75,821 (0.758) |
| backlog-adp@blank-aged1-7 | 379 | 92,445 (0.924) | 75,872 (0.759) |
| backlog-adp@program-aged2-0 | 488 | 97,250 (0.973) | 78,524 (0.785) |
| backlog-adp@program-aged2-1 | 489 | 97,268 (0.973) | 78,524 (0.785) |
| backlog-adp@program-aged2-2 | 488 | 97,168 (0.972) | 78,341 (0.783) |
| backlog-adp@program-aged2-3 | 489 | 97,168 (0.972) | 78,716 (0.787) |
| backlog-adp@program-aged2-4 | 489 | 97,168 (0.972) | 78,637 (0.786) |
| backlog-adp@program-aged2-5 | 489 | 97,168 (0.972) | 78,556 (0.786) |
| backlog-adp@program-aged2-6 | 489 | 97,168 (0.972) | 78,392 (0.784) |
| backlog-adp@program-aged2-7 | 492 | 97,168 (0.972) | 78,209 (0.782) |
| backlog-adp@program-aged1-0 | 488 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-aged1-1 | 491 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-aged1-2 | 489 | 97,250 (0.973) | 78,524 (0.785) |
| backlog-adp@program-aged1-3 | 488 | 97,168 (0.972) | 78,484 (0.785) |
| backlog-adp@program-aged1-4 | 488 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-aged1-5 | 488 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-aged1-6 | 488 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@program-aged1-7 | 488 | 97,168 (0.972) | 78,524 (0.785) |
| backlog-adp@verify-aged2-0 | 599 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-1 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-2 | 597 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-3 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-4 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-5 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-6 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged2-7 | 602 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-0 | 599 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-1 | 598 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-2 | 597 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-3 | 597 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-4 | 599 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-5 | 599 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-6 | 597 | 101,861 (1.019) | 78,216 (0.782) |
| backlog-adp@verify-aged1-7 | 597 | 101,861 (1.019) | 78,216 (0.782) |
| adp-advertise | 577 | 24,588 (0.246) | 2,582 (0.026) |
| acmp-noresp | 966 | 110,104 (1.101) | 78,381 (0.784) |
| save | 938 | 95,037 (0.950) | 77,726 (0.777) |
| srp | 271 | 24,570 (0.246) | 2,582 (0.026) |
| backlog | 265 | 24,570 (0.246) | 2,582 (0.026) |
| backlog-adp | 271 | 24,570 (0.246) | 2,582 (0.026) |
| backlog-adp-refill | 274 | 24,570 (0.246) | 2,582 (0.026) |
| backlog-owed | 277 | 24,570 (0.246) | 2,582 (0.026) |
| acmp-disc | 657 | 110,080 (1.101) | 78,381 (0.784) |
| maap | 171 | 24,527 (0.245) | 2,582 (0.026) |
| adp-link | 79 | 24,527 (0.245) | 2,582 (0.026) |
| adp-gm | 79 | 24,527 (0.245) | 2,582 (0.026) |
| adp-discover | 79 | 24,527 (0.245) | 2,582 (0.026) |
| control | 79 | 24,527 (0.245) | 2,582 (0.026) |
| aecp-fanout | 79 | 24,527 (0.245) | 2,582 (0.026) |
| acmp-cmd | 66 | 24,527 (0.245) | 2,582 (0.026) |
| aecp | 80 | 24,527 (0.245) | 2,582 (0.026) |
| aecp-held | 94 | 24,527 (0.245) | 2,582 (0.026) |
| datapath-events | 70 | 24,527 (0.245) | 2,582 (0.026) |
| fixture | 54 | 17,922 (0.179) | 2,147 (0.021) |

Longest pass that carries a step: 110,157 CPU cycles (1.102 ms), acmp-notk; longest step: 78,716 (0.787 ms), backlog-adp@program-aged2-3.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| ADP record, every channel at its refill rate, the longest | `save-burst.held.adp.if0` | 215,533 | 2.155 | 20 | 200 | fits | 134,427 | 140 | 0.163 |
| ACMP record, every channel at its refill rate, the longest | `save-burst.held.acmp.if0` | 271,252 | 2.713 | 20 | 20 | fits | 50,933 | 42 | 0.303 |
| AECP record, every channel at its refill rate, the longest | `save-burst.held.aecp.if0` | 291,170 | 2.912 | 20 | 24 | fits | 142,548 | 149 | 0.610 |
| MAAP record, every channel at its refill rate, the longest | `save-burst.held.maap.if0` | 231,558 | 2.316 | 20 | 50 | fits | 142,548 | 149 | 0.610 |
| SRP record, every channel at its refill rate, the longest | `save-burst.held.srp.if0` | 607,672 | 6.077 | 20 | 20 | fits | 131,423 | 58 | 0.604 |
| an MRPDU its join timer owes, the longest | `save-burst.mrpdu.join.if0` | 55,055 | 0.551 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its leaveall timer owes, the longest | `save-burst.mrpdu.leaveall.if0` | 54,054 | 0.541 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its periodic timer owes, the longest | `save-burst.mrpdu.periodic.if0` | 148,458 | 1.485 | 49 | 49 | fits | 0 | - | 0.000 |
| ADP record, every channel at its refill rate, the longest | `save-held.held.adp.if0` | 295,615 | 2.956 | 20 | 200 | fits | 138,934 | 133 | 0.516 |
| ACMP record, every channel at its refill rate, the longest | `save-held.held.acmp.if0` | 249,308 | 2.493 | 20 | 20 | fits | 50,730 | 42 | 0.294 |
| AECP record, every channel at its refill rate, the longest | `save-held.held.aecp.if0` | 285,135 | 2.851 | 20 | 24 | fits | 66,117 | 51 | 0.495 |
| MAAP record, every channel at its refill rate, the longest | `save-held.held.maap.if0` | 180,080 | 1.801 | 20 | 50 | fits | 93,673 | 175 | 0.219 |
| SRP record, every channel at its refill rate, the longest | `save-held.held.srp.if0` | 714,146 | 7.141 | 20 | 20 | fits | 109,805 | 65 | 0.515 |
| an MRPDU its join timer owes, the longest | `save-held.mrpdu.join.if0` | 54,763 | 0.548 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its leaveall timer owes, the longest | `save-held.mrpdu.leaveall.if0` | 57,034 | 0.570 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its periodic timer owes, the longest | `save-held.mrpdu.periodic.if0` | 148,814 | 1.488 | 49 | 49 | fits | 0 | - | 0.000 |
| ADP record, every channel at its refill rate, the longest | `save-starved.held.adp.if0` | 290,181 | 2.902 | 20 | 200 | fits | 133,500 | 135 | 0.546 |
| ACMP record, every channel at its refill rate, the longest | `save-starved.held.acmp.if0` | 231,445 | 2.314 | 20 | 20 | fits | 128,164 | 136 | 0.229 |
| AECP record, every channel at its refill rate, the longest | `save-starved.held.aecp.if0` | 246,480 | 2.465 | 20 | 24 | fits | 61,862 | 50 | 0.469 |
| MAAP record, every channel at its refill rate, the longest | `save-starved.held.maap.if0` | 230,569 | 2.306 | 20 | 50 | fits | 133,500 | 135 | 0.546 |
| SRP record, every channel at its refill rate, the longest | `save-starved.held.srp.if0` | 725,201 | 7.252 | 20 | 20 | fits | 119,986 | 75 | 0.503 |
| an MRPDU its join timer owes, the longest | `save-starved.mrpdu.join.if0` | 59,513 | 0.595 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its leaveall timer owes, the longest | `save-starved.mrpdu.leaveall.if0` | 59,513 | 0.595 | 49 | 49 | fits | 0 | - | 0.000 |
| an MRPDU its periodic timer owes, the longest | `save-starved.mrpdu.periodic.if0` | 158,070 | 1.581 | 49 | 49 | fits | 0 | - | 0.000 |
| ADP record, every channel at its refill rate, the longest | `save-flight.held.adp.if0` | 313,836 | 3.138 | 20 | 200 | fits | 132,051 | 105 | 0.407 |
| ACMP record, every channel at its refill rate, the longest | `save-flight.held.acmp.if0` | 246,408 | 2.464 | 20 | 20 | fits | 50,719 | 42 | 0.294 |
| AECP record, every channel at its refill rate, the longest | `save-flight.held.aecp.if0` | 369,344 | 3.693 | 20 | 24 | fits | 124,642 | 67 | 0.492 |
| MAAP record, every channel at its refill rate, the longest | `save-flight.held.maap.if0` | 257,301 | 2.573 | 20 | 50 | fits | 127,167 | 202 | 0.321 |
| SRP record, every channel at its refill rate, the longest | `save-flight.held.srp.if0` | 703,855 | 7.039 | 20 | 20 | fits | 99,514 | 55 | 0.541 |
| an MRPDU its periodic timer owes, the longest | `save-flight.mrpdu.periodic.if0` | 86,041 | 0.860 | 49 | 49 | fits | 0 | - | 0.000 |
| TMR_NO_TK | `acmp.tmr_no_tk.if0` | 11,232 | 0.112 | 20 | 20 | fits | 36,876 | 19 (14) | 0.872 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-0.adp_available.if0` | 380,264 | 3.803 | 20 | 20 | fits | 139,012 | 170 | 0.371 |
| ADP record released under the composed load, first | `backlog-adp@blank-0.service.adp.first.if0` | 299,554 | 2.996 | 20 | 200 | fits | 148,812 | 218 | 0.367 |
| ADP record released under the composed load, last | `backlog-adp@blank-0.service.adp.last.if0` | 447,737 | 4.477 | 20 | 200 | fits | 139,012 | 170 | 0.371 |
| ACMP record released under the composed load, first | `backlog-adp@blank-0.service.acmp.first.if0` | 300,478 | 3.005 | 20 | 20 | fits | 148,812 | 218 | 0.367 |
| ACMP record released under the composed load, last | `backlog-adp@blank-0.service.acmp.last.if0` | 448,441 | 4.484 | 20 | 20 | fits | 139,012 | 170 | 0.371 |
| AECP record released under the composed load, first | `backlog-adp@blank-0.service.aecp.first.if0` | 155,306 | 1.553 | 20 | 24 | fits | 151,572 | 164 | 0.383 |
| AECP record released under the composed load, last | `backlog-adp@blank-0.service.aecp.last.if0` | 303,128 | 3.031 | 20 | 24 | fits | 148,812 | 218 | 0.367 |
| MAAP record released under the composed load, first | `backlog-adp@blank-0.service.maap.first.if0` | 303,062 | 3.031 | 20 | 50 | fits | 148,812 | 218 | 0.367 |
| MAAP record released under the composed load, last | `backlog-adp@blank-0.service.maap.last.if0` | 451,465 | 4.515 | 20 | 50 | fits | 139,012 | 170 | 0.371 |
| SRP record released under the composed load, first | `backlog-adp@blank-0.service.srp.first.if0` | 584,654 | 5.847 | 20 | 20 | fits | 133,255 | 58 | 0.602 |
| SRP record released under the composed load, last | `backlog-adp@blank-0.service.srp.last.if0` | 812,412 | 8.124 | 20 | 20 | fits | 98,862 | 45 | 0.473 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-1.adp_available.if0` | 463,434 | 4.634 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-1.service.adp.first.if0` | 388,553 | 3.886 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-1.service.adp.last.if0` | 530,940 | 5.309 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-1.service.acmp.first.if0` | 389,477 | 3.895 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-1.service.acmp.last.if0` | 531,644 | 5.316 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-1.service.aecp.first.if0` | 233,680 | 2.337 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-1.service.aecp.last.if0` | 392,127 | 3.921 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-1.service.maap.first.if0` | 392,061 | 3.921 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-1.service.maap.last.if0` | 534,668 | 5.347 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-1.service.srp.first.if0` | 666,538 | 6.665 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-1.service.srp.last.if0` | 889,749 | 8.897 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-2.adp_available.if0` | 450,934 | 4.509 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-2.service.adp.first.if0` | 376,053 | 3.761 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-2.service.adp.last.if0` | 518,440 | 5.184 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-2.service.acmp.first.if0` | 376,977 | 3.770 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-2.service.acmp.last.if0` | 519,144 | 5.191 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-2.service.aecp.first.if0` | 221,180 | 2.212 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-2.service.aecp.last.if0` | 379,627 | 3.796 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-2.service.maap.first.if0` | 379,561 | 3.796 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-2.service.maap.last.if0` | 522,168 | 5.222 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-2.service.srp.first.if0` | 654,038 | 6.540 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-2.service.srp.last.if0` | 877,249 | 8.772 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-3.adp_available.if0` | 438,434 | 4.384 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-3.service.adp.first.if0` | 363,553 | 3.636 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-3.service.adp.last.if0` | 505,940 | 5.059 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-3.service.acmp.first.if0` | 364,477 | 3.645 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-3.service.acmp.last.if0` | 506,644 | 5.066 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-3.service.aecp.first.if0` | 208,680 | 2.087 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-3.service.aecp.last.if0` | 367,127 | 3.671 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-3.service.maap.first.if0` | 367,061 | 3.671 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-3.service.maap.last.if0` | 509,668 | 5.097 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-3.service.srp.first.if0` | 641,538 | 6.415 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-3.service.srp.last.if0` | 864,749 | 8.647 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-4.adp_available.if0` | 425,934 | 4.259 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-4.service.adp.first.if0` | 351,053 | 3.511 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-4.service.adp.last.if0` | 493,440 | 4.934 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-4.service.acmp.first.if0` | 351,977 | 3.520 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-4.service.acmp.last.if0` | 494,144 | 4.941 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-4.service.aecp.first.if0` | 196,180 | 1.962 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-4.service.aecp.last.if0` | 354,627 | 3.546 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-4.service.maap.first.if0` | 354,561 | 3.546 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-4.service.maap.last.if0` | 497,168 | 4.972 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-4.service.srp.first.if0` | 629,038 | 6.290 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-4.service.srp.last.if0` | 852,249 | 8.522 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-5.adp_available.if0` | 413,434 | 4.134 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-5.service.adp.first.if0` | 338,553 | 3.386 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-5.service.adp.last.if0` | 480,940 | 4.809 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-5.service.acmp.first.if0` | 339,477 | 3.395 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-5.service.acmp.last.if0` | 481,644 | 4.816 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-5.service.aecp.first.if0` | 183,680 | 1.837 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-5.service.aecp.last.if0` | 342,127 | 3.421 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-5.service.maap.first.if0` | 342,061 | 3.421 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-5.service.maap.last.if0` | 484,668 | 4.847 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-5.service.srp.first.if0` | 616,538 | 6.165 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-5.service.srp.last.if0` | 839,749 | 8.397 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-6.adp_available.if0` | 400,934 | 4.009 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-6.service.adp.first.if0` | 326,053 | 3.261 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-6.service.adp.last.if0` | 468,440 | 4.684 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-6.service.acmp.first.if0` | 326,977 | 3.270 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-6.service.acmp.last.if0` | 469,144 | 4.691 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-6.service.aecp.first.if0` | 171,180 | 1.712 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-6.service.aecp.last.if0` | 329,627 | 3.296 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-6.service.maap.first.if0` | 329,561 | 3.296 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-6.service.maap.last.if0` | 472,168 | 4.722 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-6.service.srp.first.if0` | 604,038 | 6.040 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-6.service.srp.last.if0` | 827,249 | 8.272 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-7.adp_available.if0` | 388,434 | 3.884 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| ADP record released under the composed load, first | `backlog-adp@blank-7.service.adp.first.if0` | 313,553 | 3.136 | 20 | 200 | fits | 150,185 | 222 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@blank-7.service.adp.last.if0` | 455,940 | 4.559 | 20 | 200 | fits | 143,003 | 169 | 0.356 |
| ACMP record released under the composed load, first | `backlog-adp@blank-7.service.acmp.first.if0` | 314,477 | 3.145 | 20 | 20 | fits | 150,185 | 222 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@blank-7.service.acmp.last.if0` | 456,644 | 4.566 | 20 | 20 | fits | 143,003 | 169 | 0.356 |
| AECP record released under the composed load, first | `backlog-adp@blank-7.service.aecp.first.if0` | 158,680 | 1.587 | 20 | 24 | fits | 151,666 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@blank-7.service.aecp.last.if0` | 317,127 | 3.171 | 20 | 24 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@blank-7.service.maap.first.if0` | 317,061 | 3.171 | 20 | 50 | fits | 150,185 | 222 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@blank-7.service.maap.last.if0` | 459,668 | 4.597 | 20 | 50 | fits | 143,003 | 169 | 0.356 |
| SRP record released under the composed load, first | `backlog-adp@blank-7.service.srp.first.if0` | 591,538 | 5.915 | 20 | 20 | fits | 128,043 | 53 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-7.service.srp.last.if0` | 814,749 | 8.147 | 20 | 20 | fits | 98,339 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-0.adp_available.if0` | 414,989 | 4.150 | 20 | 20 | fits | 139,071 | 169 | 0.378 |
| ADP record released under the composed load, first | `backlog-adp@program-0.service.adp.first.if0` | 335,305 | 3.353 | 20 | 200 | fits | 155,089 | 223 | 0.369 |
| ADP record released under the composed load, last | `backlog-adp@program-0.service.adp.last.if0` | 483,256 | 4.833 | 20 | 200 | fits | 139,071 | 169 | 0.378 |
| ACMP record released under the composed load, first | `backlog-adp@program-0.service.acmp.first.if0` | 336,229 | 3.362 | 20 | 20 | fits | 155,089 | 223 | 0.369 |
| ACMP record released under the composed load, last | `backlog-adp@program-0.service.acmp.last.if0` | 483,960 | 4.840 | 20 | 20 | fits | 139,071 | 169 | 0.378 |
| AECP record released under the composed load, first | `backlog-adp@program-0.service.aecp.first.if0` | 184,780 | 1.848 | 20 | 24 | fits | 152,337 | 164 | 0.387 |
| AECP record released under the composed load, last | `backlog-adp@program-0.service.aecp.last.if0` | 338,879 | 3.389 | 20 | 24 | fits | 155,089 | 223 | 0.369 |
| MAAP record released under the composed load, first | `backlog-adp@program-0.service.maap.first.if0` | 338,813 | 3.388 | 20 | 50 | fits | 155,089 | 223 | 0.369 |
| MAAP record released under the composed load, last | `backlog-adp@program-0.service.maap.last.if0` | 486,984 | 4.870 | 20 | 50 | fits | 139,071 | 169 | 0.378 |
| SRP record released under the composed load, first | `backlog-adp@program-0.service.srp.first.if0` | 614,587 | 6.146 | 20 | 20 | fits | 127,669 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-0.service.srp.last.if0` | 834,323 | 8.343 | 20 | 20 | fits | 98,342 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-1.adp_available.if0` | 389,989 | 3.900 | 20 | 20 | fits | 139,071 | 169 | 0.378 |
| ADP record released under the composed load, first | `backlog-adp@program-1.service.adp.first.if0` | 310,305 | 3.103 | 20 | 200 | fits | 155,089 | 223 | 0.369 |
| ADP record released under the composed load, last | `backlog-adp@program-1.service.adp.last.if0` | 458,256 | 4.583 | 20 | 200 | fits | 139,071 | 169 | 0.378 |
| ACMP record released under the composed load, first | `backlog-adp@program-1.service.acmp.first.if0` | 311,229 | 3.112 | 20 | 20 | fits | 155,089 | 223 | 0.369 |
| ACMP record released under the composed load, last | `backlog-adp@program-1.service.acmp.last.if0` | 458,960 | 4.590 | 20 | 20 | fits | 139,071 | 169 | 0.378 |
| AECP record released under the composed load, first | `backlog-adp@program-1.service.aecp.first.if0` | 159,780 | 1.598 | 20 | 24 | fits | 152,337 | 164 | 0.387 |
| AECP record released under the composed load, last | `backlog-adp@program-1.service.aecp.last.if0` | 313,879 | 3.139 | 20 | 24 | fits | 155,089 | 223 | 0.369 |
| MAAP record released under the composed load, first | `backlog-adp@program-1.service.maap.first.if0` | 313,813 | 3.138 | 20 | 50 | fits | 155,089 | 223 | 0.369 |
| MAAP record released under the composed load, last | `backlog-adp@program-1.service.maap.last.if0` | 461,984 | 4.620 | 20 | 50 | fits | 139,071 | 169 | 0.378 |
| SRP record released under the composed load, first | `backlog-adp@program-1.service.srp.first.if0` | 589,587 | 5.896 | 20 | 20 | fits | 127,669 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-1.service.srp.last.if0` | 809,323 | 8.093 | 20 | 20 | fits | 98,342 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-2.adp_available.if0` | 385,419 | 3.854 | 20 | 20 | fits | 138,884 | 169 | 0.372 |
| ADP record released under the composed load, first | `backlog-adp@program-2.service.adp.first.if0` | 305,999 | 3.060 | 20 | 200 | fits | 155,126 | 223 | 0.367 |
| ADP record released under the composed load, last | `backlog-adp@program-2.service.adp.last.if0` | 453,694 | 4.537 | 20 | 200 | fits | 138,884 | 169 | 0.372 |
| ACMP record released under the composed load, first | `backlog-adp@program-2.service.acmp.first.if0` | 306,923 | 3.069 | 20 | 20 | fits | 155,126 | 223 | 0.367 |
| ACMP record released under the composed load, last | `backlog-adp@program-2.service.acmp.last.if0` | 454,398 | 4.544 | 20 | 20 | fits | 138,884 | 169 | 0.372 |
| AECP record released under the composed load, first | `backlog-adp@program-2.service.aecp.first.if0` | 155,437 | 1.554 | 20 | 24 | fits | 152,319 | 164 | 0.388 |
| AECP record released under the composed load, last | `backlog-adp@program-2.service.aecp.last.if0` | 309,573 | 3.096 | 20 | 24 | fits | 155,126 | 223 | 0.367 |
| MAAP record released under the composed load, first | `backlog-adp@program-2.service.maap.first.if0` | 309,507 | 3.095 | 20 | 50 | fits | 155,126 | 223 | 0.367 |
| MAAP record released under the composed load, last | `backlog-adp@program-2.service.maap.last.if0` | 457,422 | 4.574 | 20 | 50 | fits | 138,884 | 169 | 0.372 |
| SRP record released under the composed load, first | `backlog-adp@program-2.service.srp.first.if0` | 585,013 | 5.850 | 20 | 20 | fits | 127,657 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-2.service.srp.last.if0` | 804,558 | 8.046 | 20 | 20 | fits | 98,270 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-3.adp_available.if0` | 463,652 | 4.637 | 20 | 20 | fits | 138,581 | 169 | 0.369 |
| ADP record released under the composed load, first | `backlog-adp@program-3.service.adp.first.if0` | 375,950 | 3.760 | 20 | 200 | fits | 155,185 | 223 | 0.368 |
| ADP record released under the composed load, last | `backlog-adp@program-3.service.adp.last.if0` | 523,480 | 5.235 | 20 | 200 | fits | 138,581 | 169 | 0.369 |
| ACMP record released under the composed load, first | `backlog-adp@program-3.service.acmp.first.if0` | 376,874 | 3.769 | 20 | 20 | fits | 155,185 | 223 | 0.368 |
| ACMP record released under the composed load, last | `backlog-adp@program-3.service.acmp.last.if0` | 524,184 | 5.242 | 20 | 20 | fits | 138,581 | 169 | 0.369 |
| AECP record released under the composed load, first | `backlog-adp@program-3.service.aecp.first.if0` | 225,329 | 2.253 | 20 | 24 | fits | 152,366 | 164 | 0.387 |
| AECP record released under the composed load, last | `backlog-adp@program-3.service.aecp.last.if0` | 379,524 | 3.795 | 20 | 24 | fits | 155,185 | 223 | 0.368 |
| MAAP record released under the composed load, first | `backlog-adp@program-3.service.maap.first.if0` | 379,458 | 3.795 | 20 | 50 | fits | 155,185 | 223 | 0.368 |
| MAAP record released under the composed load, last | `backlog-adp@program-3.service.maap.last.if0` | 527,208 | 5.272 | 20 | 50 | fits | 138,581 | 169 | 0.369 |
| SRP record released under the composed load, first | `backlog-adp@program-3.service.srp.first.if0` | 654,822 | 6.548 | 20 | 20 | fits | 127,680 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-3.service.srp.last.if0` | 874,372 | 8.744 | 20 | 20 | fits | 98,288 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-4.adp_available.if0` | 438,652 | 4.387 | 20 | 20 | fits | 138,581 | 169 | 0.369 |
| ADP record released under the composed load, first | `backlog-adp@program-4.service.adp.first.if0` | 350,950 | 3.510 | 20 | 200 | fits | 155,185 | 223 | 0.368 |
| ADP record released under the composed load, last | `backlog-adp@program-4.service.adp.last.if0` | 498,480 | 4.985 | 20 | 200 | fits | 138,581 | 169 | 0.369 |
| ACMP record released under the composed load, first | `backlog-adp@program-4.service.acmp.first.if0` | 351,874 | 3.519 | 20 | 20 | fits | 155,185 | 223 | 0.368 |
| ACMP record released under the composed load, last | `backlog-adp@program-4.service.acmp.last.if0` | 499,184 | 4.992 | 20 | 20 | fits | 138,581 | 169 | 0.369 |
| AECP record released under the composed load, first | `backlog-adp@program-4.service.aecp.first.if0` | 200,329 | 2.003 | 20 | 24 | fits | 152,366 | 164 | 0.387 |
| AECP record released under the composed load, last | `backlog-adp@program-4.service.aecp.last.if0` | 354,524 | 3.545 | 20 | 24 | fits | 155,185 | 223 | 0.368 |
| MAAP record released under the composed load, first | `backlog-adp@program-4.service.maap.first.if0` | 354,458 | 3.545 | 20 | 50 | fits | 155,185 | 223 | 0.368 |
| MAAP record released under the composed load, last | `backlog-adp@program-4.service.maap.last.if0` | 502,208 | 5.022 | 20 | 50 | fits | 138,581 | 169 | 0.369 |
| SRP record released under the composed load, first | `backlog-adp@program-4.service.srp.first.if0` | 629,822 | 6.298 | 20 | 20 | fits | 127,680 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-4.service.srp.last.if0` | 849,372 | 8.494 | 20 | 20 | fits | 98,288 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-5.adp_available.if0` | 385,452 | 3.855 | 20 | 20 | fits | 138,647 | 169 | 0.370 |
| ADP record released under the composed load, first | `backlog-adp@program-5.service.adp.first.if0` | 297,688 | 2.977 | 20 | 200 | fits | 149,515 | 223 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@program-5.service.adp.last.if0` | 445,284 | 4.453 | 20 | 200 | fits | 138,647 | 169 | 0.370 |
| ACMP record released under the composed load, first | `backlog-adp@program-5.service.acmp.first.if0` | 298,612 | 2.986 | 20 | 20 | fits | 149,515 | 223 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@program-5.service.acmp.last.if0` | 445,988 | 4.460 | 20 | 20 | fits | 138,647 | 169 | 0.370 |
| AECP record released under the composed load, first | `backlog-adp@program-5.service.aecp.first.if0` | 152,737 | 1.527 | 20 | 24 | fits | 154,331 | 164 | 0.385 |
| AECP record released under the composed load, last | `backlog-adp@program-5.service.aecp.last.if0` | 301,262 | 3.013 | 20 | 24 | fits | 149,515 | 223 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@program-5.service.maap.first.if0` | 301,196 | 3.012 | 20 | 50 | fits | 149,515 | 223 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@program-5.service.maap.last.if0` | 449,012 | 4.490 | 20 | 50 | fits | 138,647 | 169 | 0.370 |
| SRP record released under the composed load, first | `backlog-adp@program-5.service.srp.first.if0` | 576,626 | 5.766 | 20 | 20 | fits | 127,680 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-5.service.srp.last.if0` | 796,176 | 7.962 | 20 | 20 | fits | 98,288 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-6.adp_available.if0` | 385,009 | 3.850 | 20 | 20 | fits | 138,647 | 169 | 0.370 |
| ADP record released under the composed load, first | `backlog-adp@program-6.service.adp.first.if0` | 297,245 | 2.972 | 20 | 200 | fits | 149,515 | 223 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@program-6.service.adp.last.if0` | 444,841 | 4.448 | 20 | 200 | fits | 138,647 | 169 | 0.370 |
| ACMP record released under the composed load, first | `backlog-adp@program-6.service.acmp.first.if0` | 298,169 | 2.982 | 20 | 20 | fits | 149,515 | 223 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@program-6.service.acmp.last.if0` | 445,545 | 4.455 | 20 | 20 | fits | 138,647 | 169 | 0.370 |
| AECP record released under the composed load, first | `backlog-adp@program-6.service.aecp.first.if0` | 152,294 | 1.523 | 20 | 24 | fits | 154,331 | 164 | 0.385 |
| AECP record released under the composed load, last | `backlog-adp@program-6.service.aecp.last.if0` | 300,819 | 3.008 | 20 | 24 | fits | 149,515 | 223 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@program-6.service.maap.first.if0` | 300,753 | 3.008 | 20 | 50 | fits | 149,515 | 223 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@program-6.service.maap.last.if0` | 448,569 | 4.486 | 20 | 50 | fits | 138,647 | 169 | 0.370 |
| SRP record released under the composed load, first | `backlog-adp@program-6.service.srp.first.if0` | 576,183 | 5.762 | 20 | 20 | fits | 127,680 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@program-6.service.srp.last.if0` | 795,733 | 7.957 | 20 | 20 | fits | 98,288 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-7.adp_available.if0` | 385,048 | 3.850 | 20 | 20 | fits | 133,889 | 163 | 0.307 |
| ADP record released under the composed load, first | `backlog-adp@program-7.service.adp.first.if0` | 318,421 | 3.184 | 20 | 200 | fits | 149,981 | 222 | 0.369 |
| ADP record released under the composed load, last | `backlog-adp@program-7.service.adp.last.if0` | 451,694 | 4.517 | 20 | 200 | fits | 133,889 | 163 | 0.307 |
| ACMP record released under the composed load, first | `backlog-adp@program-7.service.acmp.first.if0` | 319,345 | 3.193 | 20 | 20 | fits | 149,981 | 222 | 0.369 |
| ACMP record released under the composed load, last | `backlog-adp@program-7.service.acmp.last.if0` | 452,398 | 4.524 | 20 | 20 | fits | 133,889 | 163 | 0.307 |
| AECP record released under the composed load, first | `backlog-adp@program-7.service.aecp.first.if0` | 164,498 | 1.645 | 20 | 24 | fits | 152,037 | 165 | 0.384 |
| AECP record released under the composed load, last | `backlog-adp@program-7.service.aecp.last.if0` | 321,995 | 3.220 | 20 | 24 | fits | 149,981 | 222 | 0.369 |
| MAAP record released under the composed load, first | `backlog-adp@program-7.service.maap.first.if0` | 321,929 | 3.219 | 20 | 50 | fits | 149,981 | 222 | 0.369 |
| MAAP record released under the composed load, last | `backlog-adp@program-7.service.maap.last.if0` | 455,422 | 4.554 | 20 | 50 | fits | 133,889 | 163 | 0.307 |
| SRP record released under the composed load, first | `backlog-adp@program-7.service.srp.first.if0` | 583,259 | 5.833 | 20 | 20 | fits | 127,903 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@program-7.service.srp.last.if0` | 803,081 | 8.031 | 20 | 20 | fits | 98,373 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-0.adp_available.if0` | 463,536 | 4.635 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-0.service.adp.first.if0` | 386,198 | 3.862 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-0.service.adp.last.if0` | 531,563 | 5.316 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-0.service.acmp.first.if0` | 387,122 | 3.871 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-0.service.acmp.last.if0` | 532,267 | 5.323 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-0.service.aecp.first.if0` | 240,899 | 2.409 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-0.service.aecp.last.if0` | 389,772 | 3.898 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-0.service.maap.first.if0` | 389,706 | 3.897 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-0.service.maap.last.if0` | 535,291 | 5.353 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-0.service.srp.first.if0` | 662,993 | 6.630 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-0.service.srp.last.if0` | 888,155 | 8.882 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-1.adp_available.if0` | 451,036 | 4.510 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-1.service.adp.first.if0` | 373,698 | 3.737 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-1.service.adp.last.if0` | 519,063 | 5.191 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-1.service.acmp.first.if0` | 374,622 | 3.746 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-1.service.acmp.last.if0` | 519,767 | 5.198 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-1.service.aecp.first.if0` | 228,399 | 2.284 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-1.service.aecp.last.if0` | 377,272 | 3.773 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-1.service.maap.first.if0` | 377,206 | 3.772 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-1.service.maap.last.if0` | 522,791 | 5.228 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-1.service.srp.first.if0` | 650,493 | 6.505 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-1.service.srp.last.if0` | 875,655 | 8.757 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-2.adp_available.if0` | 438,536 | 4.385 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-2.service.adp.first.if0` | 361,198 | 3.612 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-2.service.adp.last.if0` | 506,563 | 5.066 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-2.service.acmp.first.if0` | 362,122 | 3.621 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-2.service.acmp.last.if0` | 507,267 | 5.073 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-2.service.aecp.first.if0` | 215,899 | 2.159 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-2.service.aecp.last.if0` | 364,772 | 3.648 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-2.service.maap.first.if0` | 364,706 | 3.647 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-2.service.maap.last.if0` | 510,291 | 5.103 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-2.service.srp.first.if0` | 637,993 | 6.380 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-2.service.srp.last.if0` | 863,155 | 8.632 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-3.adp_available.if0` | 426,036 | 4.260 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-3.service.adp.first.if0` | 348,698 | 3.487 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-3.service.adp.last.if0` | 494,063 | 4.941 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-3.service.acmp.first.if0` | 349,622 | 3.496 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-3.service.acmp.last.if0` | 494,767 | 4.948 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-3.service.aecp.first.if0` | 203,399 | 2.034 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-3.service.aecp.last.if0` | 352,272 | 3.523 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-3.service.maap.first.if0` | 352,206 | 3.522 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-3.service.maap.last.if0` | 497,791 | 4.978 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-3.service.srp.first.if0` | 625,493 | 6.255 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-3.service.srp.last.if0` | 850,655 | 8.507 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-4.adp_available.if0` | 413,536 | 4.135 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-4.service.adp.first.if0` | 336,198 | 3.362 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-4.service.adp.last.if0` | 481,563 | 4.816 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-4.service.acmp.first.if0` | 337,122 | 3.371 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-4.service.acmp.last.if0` | 482,267 | 4.823 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-4.service.aecp.first.if0` | 190,899 | 1.909 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-4.service.aecp.last.if0` | 339,772 | 3.398 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-4.service.maap.first.if0` | 339,706 | 3.397 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-4.service.maap.last.if0` | 485,291 | 4.853 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-4.service.srp.first.if0` | 612,993 | 6.130 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-4.service.srp.last.if0` | 838,155 | 8.382 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-5.adp_available.if0` | 401,036 | 4.010 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-5.service.adp.first.if0` | 323,698 | 3.237 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-5.service.adp.last.if0` | 469,063 | 4.691 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-5.service.acmp.first.if0` | 324,622 | 3.246 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-5.service.acmp.last.if0` | 469,767 | 4.698 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-5.service.aecp.first.if0` | 178,399 | 1.784 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-5.service.aecp.last.if0` | 327,272 | 3.273 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-5.service.maap.first.if0` | 327,206 | 3.272 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-5.service.maap.last.if0` | 472,791 | 4.728 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-5.service.srp.first.if0` | 600,493 | 6.005 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-5.service.srp.last.if0` | 825,655 | 8.257 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-6.adp_available.if0` | 388,536 | 3.885 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-6.service.adp.first.if0` | 311,198 | 3.112 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-6.service.adp.last.if0` | 456,563 | 4.566 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-6.service.acmp.first.if0` | 312,122 | 3.121 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-6.service.acmp.last.if0` | 457,267 | 4.573 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-6.service.aecp.first.if0` | 165,899 | 1.659 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-6.service.aecp.last.if0` | 314,772 | 3.148 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-6.service.maap.first.if0` | 314,706 | 3.147 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-6.service.maap.last.if0` | 460,291 | 4.603 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-6.service.srp.first.if0` | 587,993 | 5.880 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-6.service.srp.last.if0` | 813,155 | 8.132 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-7.adp_available.if0` | 376,036 | 3.760 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| ADP record released under the composed load, first | `backlog-adp@verify-7.service.adp.first.if0` | 298,698 | 2.987 | 20 | 200 | fits | 149,863 | 223 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-7.service.adp.last.if0` | 444,063 | 4.441 | 20 | 200 | fits | 136,483 | 163 | 0.362 |
| ACMP record released under the composed load, first | `backlog-adp@verify-7.service.acmp.first.if0` | 299,622 | 2.996 | 20 | 20 | fits | 149,863 | 223 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-7.service.acmp.last.if0` | 444,767 | 4.448 | 20 | 20 | fits | 136,483 | 163 | 0.362 |
| AECP record released under the composed load, first | `backlog-adp@verify-7.service.aecp.first.if0` | 153,399 | 1.534 | 20 | 24 | fits | 151,774 | 164 | 0.382 |
| AECP record released under the composed load, last | `backlog-adp@verify-7.service.aecp.last.if0` | 302,272 | 3.023 | 20 | 24 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-7.service.maap.first.if0` | 302,206 | 3.022 | 20 | 50 | fits | 149,863 | 223 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-7.service.maap.last.if0` | 447,791 | 4.478 | 20 | 50 | fits | 136,483 | 163 | 0.362 |
| SRP record released under the composed load, first | `backlog-adp@verify-7.service.srp.first.if0` | 575,493 | 5.755 | 20 | 20 | fits | 127,768 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-7.service.srp.last.if0` | 800,655 | 8.007 | 20 | 20 | fits | 98,425 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-0.adp_available.if0` | 365,382 | 3.654 | 20 | 20 | fits | 133,806 | 163 | 0.305 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.adp.first.if0` | 298,803 | 2.988 | 20 | 200 | fits | 148,237 | 217 | 0.364 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.adp.last.if0` | 431,993 | 4.320 | 20 | 200 | fits | 133,806 | 163 | 0.305 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.acmp.first.if0` | 299,727 | 2.997 | 20 | 20 | fits | 148,237 | 217 | 0.364 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.acmp.last.if0` | 432,697 | 4.327 | 20 | 20 | fits | 133,806 | 163 | 0.305 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.aecp.first.if0` | 155,130 | 1.551 | 20 | 24 | fits | 150,831 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.aecp.last.if0` | 302,377 | 3.024 | 20 | 24 | fits | 148,237 | 217 | 0.364 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.maap.first.if0` | 302,311 | 3.023 | 20 | 50 | fits | 148,237 | 217 | 0.364 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.maap.last.if0` | 435,721 | 4.357 | 20 | 50 | fits | 133,806 | 163 | 0.305 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-0.service.srp.first.if0` | 563,668 | 5.637 | 20 | 20 | fits | 128,013 | 53 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-0.service.srp.last.if0` | 798,628 | 7.986 | 20 | 20 | fits | 98,815 | 44 | 0.471 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-1.adp_available.if0` | 379,153 | 3.792 | 20 | 20 | fits | 133,778 | 164 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.adp.first.if0` | 305,047 | 3.050 | 20 | 200 | fits | 148,337 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.adp.last.if0` | 438,209 | 4.382 | 20 | 200 | fits | 133,778 | 164 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.acmp.first.if0` | 305,971 | 3.060 | 20 | 20 | fits | 148,337 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.acmp.last.if0` | 438,913 | 4.389 | 20 | 20 | fits | 133,778 | 164 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.aecp.first.if0` | 161,274 | 1.613 | 20 | 24 | fits | 150,831 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.aecp.last.if0` | 308,621 | 3.086 | 20 | 24 | fits | 148,337 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.maap.first.if0` | 308,555 | 3.086 | 20 | 50 | fits | 148,337 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.maap.last.if0` | 441,937 | 4.419 | 20 | 50 | fits | 133,778 | 164 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-1.service.srp.first.if0` | 582,407 | 5.824 | 20 | 20 | fits | 131,043 | 59 | 0.602 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-1.service.srp.last.if0` | 802,863 | 8.029 | 20 | 20 | fits | 98,567 | 44 | 0.460 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-2.adp_available.if0` | 375,141 | 3.751 | 20 | 20 | fits | 138,865 | 170 | 0.369 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.adp.first.if0` | 294,801 | 2.948 | 20 | 200 | fits | 148,340 | 218 | 0.364 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.adp.last.if0` | 442,478 | 4.425 | 20 | 200 | fits | 138,865 | 170 | 0.369 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.acmp.first.if0` | 295,725 | 2.957 | 20 | 20 | fits | 148,340 | 218 | 0.364 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.acmp.last.if0` | 443,182 | 4.432 | 20 | 20 | fits | 138,865 | 170 | 0.369 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.aecp.first.if0` | 151,025 | 1.510 | 20 | 24 | fits | 150,831 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.aecp.last.if0` | 298,375 | 2.984 | 20 | 24 | fits | 148,340 | 218 | 0.364 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.maap.first.if0` | 298,309 | 2.983 | 20 | 50 | fits | 148,340 | 218 | 0.364 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.maap.last.if0` | 446,206 | 4.462 | 20 | 50 | fits | 138,865 | 170 | 0.369 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-2.service.srp.first.if0` | 573,867 | 5.739 | 20 | 20 | fits | 127,727 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-2.service.srp.last.if0` | 798,618 | 7.986 | 20 | 20 | fits | 103,518 | 50 | 0.503 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-3.adp_available.if0` | 387,421 | 3.874 | 20 | 20 | fits | 136,041 | 163 | 0.353 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.adp.first.if0` | 302,299 | 3.023 | 20 | 200 | fits | 149,694 | 223 | 0.357 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.adp.last.if0` | 447,009 | 4.470 | 20 | 200 | fits | 136,041 | 163 | 0.353 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.acmp.first.if0` | 303,223 | 3.032 | 20 | 20 | fits | 149,694 | 223 | 0.357 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.acmp.last.if0` | 447,713 | 4.477 | 20 | 20 | fits | 136,041 | 163 | 0.353 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.aecp.first.if0` | 157,169 | 1.572 | 20 | 24 | fits | 150,831 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.aecp.last.if0` | 305,873 | 3.059 | 20 | 24 | fits | 149,694 | 223 | 0.357 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.maap.first.if0` | 305,807 | 3.058 | 20 | 50 | fits | 149,694 | 223 | 0.357 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.maap.last.if0` | 450,737 | 4.507 | 20 | 50 | fits | 136,041 | 163 | 0.353 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-3.service.srp.first.if0` | 578,392 | 5.784 | 20 | 20 | fits | 127,721 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-3.service.srp.last.if0` | 880,595 | 8.806 | 20 | 20 | fits | 99,203 | 45 | 0.479 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-4.adp_available.if0` | 383,382 | 3.834 | 20 | 20 | fits | 134,113 | 163 | 0.311 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.adp.first.if0` | 317,318 | 3.173 | 20 | 200 | fits | 149,960 | 222 | 0.367 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.adp.last.if0` | 450,815 | 4.508 | 20 | 200 | fits | 134,113 | 163 | 0.311 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.acmp.first.if0` | 318,242 | 3.182 | 20 | 20 | fits | 149,960 | 222 | 0.367 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.acmp.last.if0` | 451,519 | 4.515 | 20 | 20 | fits | 134,113 | 163 | 0.311 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.aecp.first.if0` | 163,331 | 1.633 | 20 | 24 | fits | 150,849 | 162 | 0.381 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.aecp.last.if0` | 320,892 | 3.209 | 20 | 24 | fits | 149,960 | 222 | 0.367 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.maap.first.if0` | 320,826 | 3.208 | 20 | 50 | fits | 149,960 | 222 | 0.367 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.maap.last.if0` | 454,543 | 4.545 | 20 | 50 | fits | 134,113 | 163 | 0.311 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-4.service.srp.first.if0` | 587,029 | 5.870 | 20 | 20 | fits | 132,552 | 58 | 0.600 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-4.service.srp.last.if0` | 884,275 | 8.843 | 20 | 20 | fits | 98,291 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-5.adp_available.if0` | 359,923 | 3.599 | 20 | 20 | fits | 133,736 | 163 | 0.303 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.adp.first.if0` | 294,120 | 2.941 | 20 | 200 | fits | 149,383 | 222 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.adp.last.if0` | 427,240 | 4.272 | 20 | 200 | fits | 133,736 | 163 | 0.303 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.acmp.first.if0` | 295,044 | 2.950 | 20 | 20 | fits | 149,383 | 222 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.acmp.last.if0` | 427,944 | 4.279 | 20 | 20 | fits | 133,736 | 163 | 0.303 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.aecp.first.if0` | 149,301 | 1.493 | 20 | 24 | fits | 150,770 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.aecp.last.if0` | 297,694 | 2.977 | 20 | 24 | fits | 149,383 | 222 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.maap.first.if0` | 297,628 | 2.976 | 20 | 50 | fits | 149,383 | 222 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.maap.last.if0` | 430,968 | 4.310 | 20 | 50 | fits | 133,736 | 163 | 0.303 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-5.service.srp.first.if0` | 563,483 | 5.635 | 20 | 20 | fits | 132,581 | 58 | 0.599 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-5.service.srp.last.if0` | 875,175 | 8.752 | 20 | 20 | fits | 103,016 | 51 | 0.535 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-6.adp_available.if0` | 373,722 | 3.737 | 20 | 20 | fits | 141,931 | 169 | 0.342 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.adp.first.if0` | 299,260 | 2.993 | 20 | 200 | fits | 148,379 | 217 | 0.366 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.adp.last.if0` | 440,575 | 4.406 | 20 | 200 | fits | 141,931 | 169 | 0.342 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.acmp.first.if0` | 300,184 | 3.002 | 20 | 20 | fits | 148,379 | 217 | 0.366 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.acmp.last.if0` | 441,279 | 4.413 | 20 | 20 | fits | 141,931 | 169 | 0.342 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.aecp.first.if0` | 155,445 | 1.554 | 20 | 24 | fits | 150,770 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.aecp.last.if0` | 302,834 | 3.028 | 20 | 24 | fits | 148,379 | 217 | 0.366 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.maap.first.if0` | 302,768 | 3.028 | 20 | 50 | fits | 148,379 | 217 | 0.366 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.maap.last.if0` | 444,303 | 4.443 | 20 | 50 | fits | 141,931 | 169 | 0.342 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-6.service.srp.first.if0` | 648,619 | 6.486 | 20 | 20 | fits | 128,248 | 54 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-6.service.srp.last.if0` | 883,619 | 8.836 | 20 | 20 | fits | 98,814 | 44 | 0.469 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged2-7.adp_available.if0` | 462,377 | 4.624 | 20 | 20 | fits | 134,067 | 164 | 0.307 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.adp.first.if0` | 312,114 | 3.121 | 20 | 200 | fits | 155,089 | 222 | 0.367 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.adp.last.if0` | 521,535 | 5.215 | 20 | 200 | fits | 134,067 | 164 | 0.307 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.acmp.first.if0` | 313,038 | 3.130 | 20 | 20 | fits | 155,089 | 222 | 0.367 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.acmp.last.if0` | 522,239 | 5.222 | 20 | 20 | fits | 134,067 | 164 | 0.307 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.aecp.first.if0` | 161,589 | 1.616 | 20 | 24 | fits | 150,770 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.aecp.last.if0` | 315,688 | 3.157 | 20 | 24 | fits | 155,089 | 222 | 0.367 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.maap.first.if0` | 315,622 | 3.156 | 20 | 50 | fits | 155,089 | 222 | 0.367 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.maap.last.if0` | 525,263 | 5.253 | 20 | 50 | fits | 134,067 | 164 | 0.307 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged2-7.service.srp.first.if0` | 665,775 | 6.658 | 20 | 20 | fits | 130,992 | 59 | 0.602 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged2-7.service.srp.last.if0` | 886,286 | 8.863 | 20 | 20 | fits | 98,567 | 44 | 0.460 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-0.adp_available.if0` | 366,606 | 3.666 | 20 | 20 | fits | 133,700 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.adp.first.if0` | 300,133 | 3.001 | 20 | 200 | fits | 148,350 | 217 | 0.365 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.adp.last.if0` | 433,217 | 4.332 | 20 | 200 | fits | 133,700 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.acmp.first.if0` | 301,057 | 3.011 | 20 | 20 | fits | 148,350 | 217 | 0.365 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.acmp.last.if0` | 433,921 | 4.339 | 20 | 20 | fits | 133,700 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.aecp.first.if0` | 156,347 | 1.563 | 20 | 24 | fits | 150,802 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.aecp.last.if0` | 303,707 | 3.037 | 20 | 24 | fits | 148,350 | 217 | 0.365 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.maap.first.if0` | 303,641 | 3.036 | 20 | 50 | fits | 148,350 | 217 | 0.365 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.maap.last.if0` | 436,945 | 4.369 | 20 | 50 | fits | 133,700 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-0.service.srp.first.if0` | 564,748 | 5.647 | 20 | 20 | fits | 127,869 | 52 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-0.service.srp.last.if0` | 784,713 | 7.847 | 20 | 20 | fits | 98,516 | 45 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-1.adp_available.if0` | 380,217 | 3.802 | 20 | 20 | fits | 133,529 | 163 | 0.299 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.adp.first.if0` | 306,217 | 3.062 | 20 | 200 | fits | 148,450 | 217 | 0.363 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.adp.last.if0` | 439,130 | 4.391 | 20 | 200 | fits | 133,529 | 163 | 0.299 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.acmp.first.if0` | 307,141 | 3.071 | 20 | 20 | fits | 148,450 | 217 | 0.363 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.acmp.last.if0` | 439,834 | 4.398 | 20 | 20 | fits | 133,529 | 163 | 0.299 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.aecp.first.if0` | 162,331 | 1.623 | 20 | 24 | fits | 150,802 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.aecp.last.if0` | 309,791 | 3.098 | 20 | 24 | fits | 148,450 | 217 | 0.363 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.maap.first.if0` | 309,725 | 3.097 | 20 | 50 | fits | 148,450 | 217 | 0.363 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.maap.last.if0` | 442,858 | 4.429 | 20 | 50 | fits | 133,529 | 163 | 0.299 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-1.service.srp.first.if0` | 570,614 | 5.706 | 20 | 20 | fits | 127,822 | 52 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-1.service.srp.last.if0` | 805,227 | 8.052 | 20 | 20 | fits | 103,291 | 51 | 0.540 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-2.adp_available.if0` | 362,201 | 3.622 | 20 | 20 | fits | 133,700 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.adp.first.if0` | 295,728 | 2.957 | 20 | 200 | fits | 148,350 | 217 | 0.365 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.adp.last.if0` | 428,812 | 4.288 | 20 | 200 | fits | 133,700 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.acmp.first.if0` | 296,652 | 2.967 | 20 | 20 | fits | 148,350 | 217 | 0.365 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.acmp.last.if0` | 429,516 | 4.295 | 20 | 20 | fits | 133,700 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.aecp.first.if0` | 151,942 | 1.519 | 20 | 24 | fits | 150,802 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.aecp.last.if0` | 299,302 | 2.993 | 20 | 24 | fits | 148,350 | 217 | 0.365 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.maap.first.if0` | 299,236 | 2.992 | 20 | 50 | fits | 148,350 | 217 | 0.365 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.maap.last.if0` | 432,540 | 4.325 | 20 | 50 | fits | 133,700 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-2.service.srp.first.if0` | 560,486 | 5.605 | 20 | 20 | fits | 128,012 | 53 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-2.service.srp.last.if0` | 800,055 | 8.001 | 20 | 20 | fits | 103,424 | 50 | 0.502 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-3.adp_available.if0` | 375,812 | 3.758 | 20 | 20 | fits | 133,672 | 164 | 0.300 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.adp.first.if0` | 301,812 | 3.018 | 20 | 200 | fits | 148,450 | 217 | 0.363 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.adp.last.if0` | 434,868 | 4.349 | 20 | 200 | fits | 133,672 | 164 | 0.300 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.acmp.first.if0` | 302,736 | 3.027 | 20 | 20 | fits | 148,450 | 217 | 0.363 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.acmp.last.if0` | 435,572 | 4.356 | 20 | 20 | fits | 133,672 | 164 | 0.300 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.aecp.first.if0` | 157,926 | 1.579 | 20 | 24 | fits | 150,802 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.aecp.last.if0` | 305,386 | 3.054 | 20 | 24 | fits | 148,450 | 217 | 0.363 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.maap.first.if0` | 305,320 | 3.053 | 20 | 50 | fits | 148,450 | 217 | 0.363 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.maap.last.if0` | 438,596 | 4.386 | 20 | 50 | fits | 133,672 | 164 | 0.300 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-3.service.srp.first.if0` | 578,809 | 5.788 | 20 | 20 | fits | 130,930 | 59 | 0.601 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-3.service.srp.last.if0` | 804,124 | 8.041 | 20 | 20 | fits | 98,650 | 44 | 0.462 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-4.adp_available.if0` | 387,542 | 3.875 | 20 | 20 | fits | 139,186 | 170 | 0.376 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.adp.first.if0` | 307,799 | 3.078 | 20 | 200 | fits | 148,453 | 218 | 0.365 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.adp.last.if0` | 455,705 | 4.557 | 20 | 200 | fits | 139,186 | 170 | 0.376 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.acmp.first.if0` | 308,723 | 3.087 | 20 | 20 | fits | 148,453 | 218 | 0.365 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.acmp.last.if0` | 456,409 | 4.564 | 20 | 20 | fits | 139,186 | 170 | 0.376 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.aecp.first.if0` | 163,910 | 1.639 | 20 | 24 | fits | 150,802 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.aecp.last.if0` | 311,373 | 3.114 | 20 | 24 | fits | 148,453 | 218 | 0.365 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.maap.first.if0` | 311,307 | 3.113 | 20 | 50 | fits | 148,453 | 218 | 0.365 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.maap.last.if0` | 459,433 | 4.594 | 20 | 50 | fits | 139,186 | 170 | 0.376 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-4.service.srp.first.if0` | 591,820 | 5.918 | 20 | 20 | fits | 132,453 | 58 | 0.598 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-4.service.srp.last.if0` | 811,388 | 8.114 | 20 | 20 | fits | 98,260 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-5.adp_available.if0` | 389,780 | 3.898 | 20 | 20 | fits | 141,884 | 169 | 0.342 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.adp.first.if0` | 307,758 | 3.078 | 20 | 200 | fits | 150,451 | 222 | 0.370 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.adp.last.if0` | 449,026 | 4.490 | 20 | 200 | fits | 141,884 | 169 | 0.342 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.acmp.first.if0` | 308,682 | 3.087 | 20 | 20 | fits | 150,451 | 222 | 0.370 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.acmp.last.if0` | 449,730 | 4.497 | 20 | 20 | fits | 141,884 | 169 | 0.342 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.aecp.first.if0` | 153,615 | 1.536 | 20 | 24 | fits | 150,896 | 162 | 0.381 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.aecp.last.if0` | 311,332 | 3.113 | 20 | 24 | fits | 150,451 | 222 | 0.370 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.maap.first.if0` | 311,266 | 3.113 | 20 | 50 | fits | 150,451 | 222 | 0.370 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.maap.last.if0` | 452,754 | 4.528 | 20 | 50 | fits | 141,884 | 169 | 0.342 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-5.service.srp.first.if0` | 580,553 | 5.806 | 20 | 20 | fits | 127,865 | 52 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-5.service.srp.last.if0` | 800,367 | 8.004 | 20 | 20 | fits | 98,391 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-6.adp_available.if0` | 386,414 | 3.864 | 20 | 20 | fits | 142,273 | 169 | 0.348 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.adp.first.if0` | 312,318 | 3.123 | 20 | 200 | fits | 148,332 | 217 | 0.363 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.adp.last.if0` | 453,975 | 4.540 | 20 | 200 | fits | 142,273 | 169 | 0.348 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.acmp.first.if0` | 313,242 | 3.132 | 20 | 20 | fits | 148,332 | 217 | 0.363 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.acmp.last.if0` | 454,679 | 4.547 | 20 | 20 | fits | 142,273 | 169 | 0.348 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.aecp.first.if0` | 168,550 | 1.685 | 20 | 24 | fits | 151,017 | 162 | 0.381 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.aecp.last.if0` | 315,892 | 3.159 | 20 | 24 | fits | 148,332 | 217 | 0.363 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.maap.first.if0` | 315,826 | 3.158 | 20 | 50 | fits | 148,332 | 217 | 0.363 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.maap.last.if0` | 457,703 | 4.577 | 20 | 50 | fits | 142,273 | 169 | 0.348 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-6.service.srp.first.if0` | 585,563 | 5.856 | 20 | 20 | fits | 127,926 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-6.service.srp.last.if0` | 805,732 | 8.057 | 20 | 20 | fits | 98,588 | 45 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@blank-aged1-7.adp_available.if0` | 386,887 | 3.869 | 20 | 20 | fits | 133,635 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.adp.first.if0` | 312,781 | 3.128 | 20 | 200 | fits | 154,947 | 222 | 0.366 |
| ADP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.adp.last.if0` | 445,800 | 4.458 | 20 | 200 | fits | 133,635 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.acmp.first.if0` | 313,705 | 3.137 | 20 | 20 | fits | 154,947 | 222 | 0.366 |
| ACMP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.acmp.last.if0` | 446,504 | 4.465 | 20 | 20 | fits | 133,635 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.aecp.first.if0` | 162,398 | 1.624 | 20 | 24 | fits | 150,831 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.aecp.last.if0` | 316,355 | 3.164 | 20 | 24 | fits | 154,947 | 222 | 0.366 |
| MAAP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.maap.first.if0` | 316,289 | 3.163 | 20 | 50 | fits | 154,947 | 222 | 0.366 |
| MAAP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.maap.last.if0` | 449,528 | 4.495 | 20 | 50 | fits | 133,635 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@blank-aged1-7.service.srp.first.if0` | 577,285 | 5.773 | 20 | 20 | fits | 127,823 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@blank-aged1-7.service.srp.last.if0` | 811,953 | 8.120 | 20 | 20 | fits | 103,291 | 51 | 0.540 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-0.adp_available.if0` | 387,469 | 3.875 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-0.service.adp.first.if0` | 310,665 | 3.107 | 20 | 200 | fits | 148,692 | 218 | 0.377 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-0.service.adp.last.if0` | 445,441 | 4.454 | 20 | 200 | fits | 135,392 | 166 | 0.299 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-0.service.acmp.first.if0` | 311,589 | 3.116 | 20 | 20 | fits | 148,692 | 218 | 0.377 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-0.service.acmp.last.if0` | 446,145 | 4.461 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-0.service.aecp.first.if0` | 158,083 | 1.581 | 20 | 24 | fits | 150,786 | 162 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-0.service.aecp.last.if0` | 314,239 | 3.142 | 20 | 24 | fits | 148,692 | 218 | 0.377 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-0.service.maap.first.if0` | 314,173 | 3.142 | 20 | 50 | fits | 148,692 | 218 | 0.377 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-0.service.maap.last.if0` | 449,169 | 4.492 | 20 | 50 | fits | 135,392 | 166 | 0.299 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-0.service.srp.first.if0` | 576,915 | 5.769 | 20 | 20 | fits | 127,812 | 52 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-0.service.srp.last.if0` | 796,920 | 7.969 | 20 | 20 | fits | 98,432 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-1.adp_available.if0` | 384,089 | 3.841 | 20 | 20 | fits | 134,025 | 163 | 0.308 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-1.service.adp.first.if0` | 318,156 | 3.182 | 20 | 200 | fits | 150,180 | 222 | 0.367 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-1.service.adp.last.if0` | 451,565 | 4.516 | 20 | 200 | fits | 134,025 | 163 | 0.308 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-1.service.acmp.first.if0` | 319,080 | 3.191 | 20 | 20 | fits | 150,180 | 222 | 0.367 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-1.service.acmp.last.if0` | 452,269 | 4.523 | 20 | 20 | fits | 134,025 | 163 | 0.308 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-1.service.aecp.first.if0` | 164,086 | 1.641 | 20 | 24 | fits | 150,805 | 162 | 0.381 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-1.service.aecp.last.if0` | 321,730 | 3.217 | 20 | 24 | fits | 150,180 | 222 | 0.367 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-1.service.maap.first.if0` | 321,664 | 3.217 | 20 | 50 | fits | 150,180 | 222 | 0.367 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-1.service.maap.last.if0` | 455,293 | 4.553 | 20 | 50 | fits | 134,025 | 163 | 0.308 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-1.service.srp.first.if0` | 583,214 | 5.832 | 20 | 20 | fits | 127,987 | 52 | 0.586 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-1.service.srp.last.if0` | 802,948 | 8.029 | 20 | 20 | fits | 98,373 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-2.adp_available.if0` | 368,009 | 3.680 | 20 | 20 | fits | 133,600 | 163 | 0.301 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-2.service.adp.first.if0` | 293,938 | 2.939 | 20 | 200 | fits | 149,145 | 222 | 0.358 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-2.service.adp.last.if0` | 426,922 | 4.269 | 20 | 200 | fits | 133,600 | 163 | 0.301 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-2.service.acmp.first.if0` | 294,862 | 2.949 | 20 | 20 | fits | 149,145 | 222 | 0.358 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-2.service.acmp.last.if0` | 427,626 | 4.276 | 20 | 20 | fits | 133,600 | 163 | 0.301 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-2.service.aecp.first.if0` | 149,357 | 1.494 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-2.service.aecp.last.if0` | 297,512 | 2.975 | 20 | 24 | fits | 149,145 | 222 | 0.358 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-2.service.maap.first.if0` | 297,446 | 2.974 | 20 | 50 | fits | 149,145 | 222 | 0.358 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-2.service.maap.last.if0` | 430,650 | 4.306 | 20 | 50 | fits | 133,600 | 163 | 0.301 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-2.service.srp.first.if0` | 558,406 | 5.584 | 20 | 20 | fits | 127,822 | 52 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-2.service.srp.last.if0` | 778,389 | 7.784 | 20 | 20 | fits | 98,534 | 45 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-3.adp_available.if0` | 366,009 | 3.660 | 20 | 20 | fits | 133,895 | 163 | 0.307 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-3.service.adp.first.if0` | 300,004 | 3.000 | 20 | 200 | fits | 148,150 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-3.service.adp.last.if0` | 433,283 | 4.333 | 20 | 200 | fits | 133,895 | 163 | 0.307 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-3.service.acmp.first.if0` | 300,928 | 3.009 | 20 | 20 | fits | 148,150 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-3.service.acmp.last.if0` | 433,987 | 4.340 | 20 | 20 | fits | 133,895 | 163 | 0.307 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-3.service.aecp.first.if0` | 156,418 | 1.564 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-3.service.aecp.last.if0` | 303,578 | 3.036 | 20 | 24 | fits | 148,150 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-3.service.maap.first.if0` | 303,512 | 3.035 | 20 | 50 | fits | 148,150 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-3.service.maap.last.if0` | 437,011 | 4.370 | 20 | 50 | fits | 133,895 | 163 | 0.307 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-3.service.srp.first.if0` | 564,870 | 5.649 | 20 | 20 | fits | 127,925 | 52 | 0.586 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-3.service.srp.last.if0` | 884,673 | 8.847 | 20 | 20 | fits | 101,356 | 45 | 0.536 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-4.adp_available.if0` | 372,817 | 3.728 | 20 | 20 | fits | 133,778 | 163 | 0.304 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-4.service.adp.first.if0` | 306,218 | 3.062 | 20 | 200 | fits | 148,220 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-4.service.adp.last.if0` | 439,380 | 4.394 | 20 | 200 | fits | 133,778 | 163 | 0.304 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-4.service.acmp.first.if0` | 307,142 | 3.071 | 20 | 20 | fits | 148,220 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-4.service.acmp.last.if0` | 440,084 | 4.401 | 20 | 20 | fits | 133,778 | 163 | 0.304 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-4.service.aecp.first.if0` | 162,562 | 1.626 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-4.service.aecp.last.if0` | 309,792 | 3.098 | 20 | 24 | fits | 148,220 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-4.service.maap.first.if0` | 309,726 | 3.097 | 20 | 50 | fits | 148,220 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-4.service.maap.last.if0` | 443,108 | 4.431 | 20 | 50 | fits | 133,778 | 163 | 0.304 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-4.service.srp.first.if0` | 577,441 | 5.774 | 20 | 20 | fits | 134,399 | 65 | 0.591 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-4.service.srp.last.if0` | 890,345 | 8.903 | 20 | 20 | fits | 98,563 | 44 | 0.464 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-5.adp_available.if0` | 361,904 | 3.619 | 20 | 20 | fits | 134,036 | 164 | 0.308 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-5.service.adp.first.if0` | 295,899 | 2.959 | 20 | 200 | fits | 148,150 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-5.service.adp.last.if0` | 429,319 | 4.293 | 20 | 200 | fits | 134,036 | 164 | 0.308 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-5.service.acmp.first.if0` | 296,823 | 2.968 | 20 | 20 | fits | 148,150 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-5.service.acmp.last.if0` | 430,023 | 4.300 | 20 | 20 | fits | 134,036 | 164 | 0.308 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-5.service.aecp.first.if0` | 152,313 | 1.523 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-5.service.aecp.last.if0` | 299,473 | 2.995 | 20 | 24 | fits | 148,150 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-5.service.maap.first.if0` | 299,407 | 2.994 | 20 | 50 | fits | 148,150 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-5.service.maap.last.if0` | 433,047 | 4.330 | 20 | 50 | fits | 134,036 | 164 | 0.308 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-5.service.srp.first.if0` | 577,336 | 5.773 | 20 | 20 | fits | 134,937 | 65 | 0.605 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-5.service.srp.last.if0` | 880,036 | 8.800 | 20 | 20 | fits | 98,687 | 44 | 0.467 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-6.adp_available.if0` | 388,894 | 3.889 | 20 | 20 | fits | 145,325 | 176 | 0.375 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-6.service.adp.first.if0` | 302,221 | 3.022 | 20 | 200 | fits | 148,328 | 218 | 0.363 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-6.service.adp.last.if0` | 456,203 | 4.562 | 20 | 200 | fits | 145,325 | 176 | 0.375 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-6.service.acmp.first.if0` | 303,145 | 3.031 | 20 | 20 | fits | 148,328 | 218 | 0.363 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-6.service.acmp.last.if0` | 456,907 | 4.569 | 20 | 20 | fits | 145,325 | 176 | 0.375 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-6.service.aecp.first.if0` | 158,457 | 1.585 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-6.service.aecp.last.if0` | 305,795 | 3.058 | 20 | 24 | fits | 148,328 | 218 | 0.363 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-6.service.maap.first.if0` | 305,729 | 3.057 | 20 | 50 | fits | 148,328 | 218 | 0.363 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-6.service.maap.last.if0` | 459,931 | 4.599 | 20 | 50 | fits | 145,325 | 176 | 0.375 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-6.service.srp.first.if0` | 668,253 | 6.683 | 20 | 20 | fits | 128,015 | 53 | 0.581 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-6.service.srp.last.if0` | 888,430 | 8.884 | 20 | 20 | fits | 98,357 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged2-7.adp_available.if0` | 473,009 | 4.730 | 20 | 20 | fits | 137,046 | 169 | 0.339 |
| ADP record released under the composed load, first | `backlog-adp@program-aged2-7.service.adp.first.if0` | 324,038 | 3.240 | 20 | 200 | fits | 155,883 | 222 | 0.378 |
| ADP record released under the composed load, last | `backlog-adp@program-aged2-7.service.adp.last.if0` | 540,764 | 5.408 | 20 | 200 | fits | 137,046 | 169 | 0.339 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged2-7.service.acmp.first.if0` | 324,962 | 3.250 | 20 | 20 | fits | 155,883 | 222 | 0.378 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged2-7.service.acmp.last.if0` | 541,468 | 5.415 | 20 | 20 | fits | 137,046 | 169 | 0.339 |
| AECP record released under the composed load, first | `backlog-adp@program-aged2-7.service.aecp.first.if0` | 164,646 | 1.646 | 20 | 24 | fits | 150,659 | 162 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged2-7.service.aecp.last.if0` | 327,612 | 3.276 | 20 | 24 | fits | 155,883 | 222 | 0.378 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged2-7.service.maap.first.if0` | 327,546 | 3.275 | 20 | 50 | fits | 155,883 | 222 | 0.378 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged2-7.service.maap.last.if0` | 544,492 | 5.445 | 20 | 50 | fits | 137,046 | 169 | 0.339 |
| SRP record released under the composed load, first | `backlog-adp@program-aged2-7.service.srp.first.if0` | 672,225 | 6.722 | 20 | 20 | fits | 127,799 | 52 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@program-aged2-7.service.srp.last.if0` | 891,845 | 8.918 | 20 | 20 | fits | 98,270 | 44 | 0.454 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-0.adp_available.if0` | 369,326 | 3.693 | 20 | 20 | fits | 133,921 | 164 | 0.304 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-0.service.adp.first.if0` | 302,727 | 3.027 | 20 | 200 | fits | 148,249 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-0.service.adp.last.if0` | 436,032 | 4.360 | 20 | 200 | fits | 133,921 | 164 | 0.304 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-0.service.acmp.first.if0` | 303,651 | 3.037 | 20 | 20 | fits | 148,249 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-0.service.acmp.last.if0` | 436,736 | 4.367 | 20 | 20 | fits | 133,921 | 164 | 0.304 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-0.service.aecp.first.if0` | 159,042 | 1.590 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-0.service.aecp.last.if0` | 306,301 | 3.063 | 20 | 24 | fits | 148,249 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-0.service.maap.first.if0` | 306,235 | 3.062 | 20 | 50 | fits | 148,249 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-0.service.maap.last.if0` | 439,760 | 4.398 | 20 | 50 | fits | 133,921 | 164 | 0.304 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-0.service.srp.first.if0` | 580,306 | 5.803 | 20 | 20 | fits | 131,050 | 59 | 0.602 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-0.service.srp.last.if0` | 800,921 | 8.009 | 20 | 20 | fits | 98,608 | 44 | 0.462 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-1.adp_available.if0` | 373,123 | 3.731 | 20 | 20 | fits | 139,068 | 169 | 0.378 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-1.service.adp.first.if0` | 293,406 | 2.934 | 20 | 200 | fits | 149,177 | 223 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-1.service.adp.last.if0` | 441,286 | 4.413 | 20 | 200 | fits | 139,068 | 169 | 0.378 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-1.service.acmp.first.if0` | 294,330 | 2.943 | 20 | 20 | fits | 149,177 | 223 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-1.service.acmp.last.if0` | 441,990 | 4.420 | 20 | 20 | fits | 139,068 | 169 | 0.378 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-1.service.aecp.first.if0` | 148,793 | 1.488 | 20 | 24 | fits | 150,614 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-1.service.aecp.last.if0` | 296,980 | 2.970 | 20 | 24 | fits | 149,177 | 223 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-1.service.maap.first.if0` | 296,914 | 2.969 | 20 | 50 | fits | 149,177 | 223 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-1.service.maap.last.if0` | 445,014 | 4.450 | 20 | 50 | fits | 139,068 | 169 | 0.378 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-1.service.srp.first.if0` | 572,764 | 5.728 | 20 | 20 | fits | 127,816 | 52 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-1.service.srp.last.if0` | 792,363 | 7.924 | 20 | 20 | fits | 98,342 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-2.adp_available.if0` | 384,332 | 3.843 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-2.service.adp.first.if0` | 307,528 | 3.075 | 20 | 200 | fits | 148,620 | 218 | 0.376 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-2.service.adp.last.if0` | 442,304 | 4.423 | 20 | 200 | fits | 135,392 | 166 | 0.299 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-2.service.acmp.first.if0` | 308,452 | 3.085 | 20 | 20 | fits | 148,620 | 218 | 0.376 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-2.service.acmp.last.if0` | 443,008 | 4.430 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-2.service.aecp.first.if0` | 155,009 | 1.550 | 20 | 24 | fits | 150,686 | 162 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-2.service.aecp.last.if0` | 311,102 | 3.111 | 20 | 24 | fits | 148,620 | 218 | 0.376 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-2.service.maap.first.if0` | 311,036 | 3.110 | 20 | 50 | fits | 148,620 | 218 | 0.376 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-2.service.maap.last.if0` | 446,032 | 4.460 | 20 | 50 | fits | 135,392 | 166 | 0.299 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-2.service.srp.first.if0` | 573,778 | 5.738 | 20 | 20 | fits | 127,812 | 52 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-2.service.srp.last.if0` | 799,097 | 7.991 | 20 | 20 | fits | 103,746 | 50 | 0.508 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-3.adp_available.if0` | 367,169 | 3.672 | 20 | 20 | fits | 133,818 | 163 | 0.306 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-3.service.adp.first.if0` | 301,241 | 3.012 | 20 | 200 | fits | 148,020 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-3.service.adp.last.if0` | 434,443 | 4.344 | 20 | 200 | fits | 133,818 | 163 | 0.306 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-3.service.acmp.first.if0` | 302,165 | 3.022 | 20 | 20 | fits | 148,020 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-3.service.acmp.last.if0` | 435,147 | 4.351 | 20 | 20 | fits | 133,818 | 163 | 0.306 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-3.service.aecp.first.if0` | 157,785 | 1.578 | 20 | 24 | fits | 150,754 | 161 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-3.service.aecp.last.if0` | 304,815 | 3.048 | 20 | 24 | fits | 148,020 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-3.service.maap.first.if0` | 304,749 | 3.047 | 20 | 50 | fits | 148,020 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-3.service.maap.last.if0` | 438,171 | 4.382 | 20 | 50 | fits | 133,818 | 163 | 0.306 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-3.service.srp.first.if0` | 566,003 | 5.660 | 20 | 20 | fits | 127,898 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-3.service.srp.last.if0` | 791,569 | 7.916 | 20 | 20 | fits | 98,671 | 45 | 0.460 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-4.adp_available.if0` | 373,907 | 3.739 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-4.service.adp.first.if0` | 307,375 | 3.074 | 20 | 200 | fits | 148,106 | 217 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-4.service.adp.last.if0` | 440,470 | 4.405 | 20 | 200 | fits | 133,711 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-4.service.acmp.first.if0` | 308,299 | 3.083 | 20 | 20 | fits | 148,106 | 217 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-4.service.acmp.last.if0` | 441,174 | 4.412 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-4.service.aecp.first.if0` | 163,833 | 1.638 | 20 | 24 | fits | 150,707 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-4.service.aecp.last.if0` | 310,949 | 3.109 | 20 | 24 | fits | 148,106 | 217 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-4.service.maap.first.if0` | 310,883 | 3.109 | 20 | 50 | fits | 148,106 | 217 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-4.service.maap.last.if0` | 444,198 | 4.442 | 20 | 50 | fits | 133,711 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-4.service.srp.first.if0` | 576,560 | 5.766 | 20 | 20 | fits | 132,428 | 58 | 0.596 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-4.service.srp.last.if0` | 811,104 | 8.111 | 20 | 20 | fits | 102,989 | 51 | 0.535 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-5.adp_available.if0` | 362,889 | 3.629 | 20 | 20 | fits | 133,863 | 163 | 0.307 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-5.service.adp.first.if0` | 296,916 | 2.969 | 20 | 200 | fits | 148,036 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-5.service.adp.last.if0` | 430,163 | 4.302 | 20 | 200 | fits | 133,863 | 163 | 0.307 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-5.service.acmp.first.if0` | 297,840 | 2.978 | 20 | 20 | fits | 148,036 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-5.service.acmp.last.if0` | 430,867 | 4.309 | 20 | 20 | fits | 133,863 | 163 | 0.307 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-5.service.aecp.first.if0` | 153,444 | 1.534 | 20 | 24 | fits | 150,707 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-5.service.aecp.last.if0` | 300,490 | 3.005 | 20 | 24 | fits | 148,036 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-5.service.maap.first.if0` | 300,424 | 3.004 | 20 | 50 | fits | 148,036 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-5.service.maap.last.if0` | 433,891 | 4.339 | 20 | 50 | fits | 133,863 | 163 | 0.307 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-5.service.srp.first.if0` | 566,487 | 5.665 | 20 | 20 | fits | 132,662 | 59 | 0.597 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-5.service.srp.last.if0` | 801,101 | 8.011 | 20 | 20 | fits | 98,768 | 44 | 0.467 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-6.adp_available.if0` | 377,309 | 3.773 | 20 | 20 | fits | 141,903 | 170 | 0.340 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-6.service.adp.first.if0` | 302,970 | 3.030 | 20 | 200 | fits | 148,106 | 217 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-6.service.adp.last.if0` | 444,257 | 4.443 | 20 | 200 | fits | 141,903 | 170 | 0.340 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-6.service.acmp.first.if0` | 303,894 | 3.039 | 20 | 20 | fits | 148,106 | 217 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-6.service.acmp.last.if0` | 444,961 | 4.450 | 20 | 20 | fits | 141,903 | 170 | 0.340 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-6.service.aecp.first.if0` | 159,428 | 1.594 | 20 | 24 | fits | 150,707 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-6.service.aecp.last.if0` | 306,544 | 3.065 | 20 | 24 | fits | 148,106 | 217 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-6.service.maap.first.if0` | 306,478 | 3.065 | 20 | 50 | fits | 148,106 | 217 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-6.service.maap.last.if0` | 447,985 | 4.480 | 20 | 50 | fits | 141,903 | 170 | 0.340 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-6.service.srp.first.if0` | 588,412 | 5.884 | 20 | 20 | fits | 130,931 | 59 | 0.601 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-6.service.srp.last.if0` | 808,789 | 8.088 | 20 | 20 | fits | 98,449 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@program-aged1-7.adp_available.if0` | 379,933 | 3.799 | 20 | 20 | fits | 145,942 | 175 | 0.389 |
| ADP record released under the composed load, first | `backlog-adp@program-aged1-7.service.adp.first.if0` | 293,509 | 2.935 | 20 | 200 | fits | 149,034 | 223 | 0.360 |
| ADP record released under the composed load, last | `backlog-adp@program-aged1-7.service.adp.last.if0` | 448,119 | 4.481 | 20 | 200 | fits | 145,942 | 175 | 0.389 |
| ACMP record released under the composed load, first | `backlog-adp@program-aged1-7.service.acmp.first.if0` | 294,433 | 2.944 | 20 | 20 | fits | 149,034 | 223 | 0.360 |
| ACMP record released under the composed load, last | `backlog-adp@program-aged1-7.service.acmp.last.if0` | 448,823 | 4.488 | 20 | 20 | fits | 145,942 | 175 | 0.389 |
| AECP record released under the composed load, first | `backlog-adp@program-aged1-7.service.aecp.first.if0` | 149,039 | 1.490 | 20 | 24 | fits | 150,707 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@program-aged1-7.service.aecp.last.if0` | 297,083 | 2.971 | 20 | 24 | fits | 149,034 | 223 | 0.360 |
| MAAP record released under the composed load, first | `backlog-adp@program-aged1-7.service.maap.first.if0` | 297,017 | 2.970 | 20 | 50 | fits | 149,034 | 223 | 0.360 |
| MAAP record released under the composed load, last | `backlog-adp@program-aged1-7.service.maap.last.if0` | 451,847 | 4.518 | 20 | 50 | fits | 145,942 | 175 | 0.389 |
| SRP record released under the composed load, first | `backlog-adp@program-aged1-7.service.srp.first.if0` | 579,662 | 5.797 | 20 | 20 | fits | 127,881 | 52 | 0.584 |
| SRP record released under the composed load, last | `backlog-adp@program-aged1-7.service.srp.last.if0` | 799,261 | 7.993 | 20 | 20 | fits | 98,342 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-0.adp_available.if0` | 359,753 | 3.598 | 20 | 20 | fits | 133,930 | 163 | 0.309 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.adp.first.if0` | 293,713 | 2.937 | 20 | 200 | fits | 148,985 | 222 | 0.360 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.adp.last.if0` | 427,027 | 4.270 | 20 | 200 | fits | 133,930 | 163 | 0.309 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.acmp.first.if0` | 294,637 | 2.946 | 20 | 20 | fits | 148,985 | 222 | 0.360 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.acmp.last.if0` | 427,731 | 4.277 | 20 | 20 | fits | 133,930 | 163 | 0.309 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.aecp.first.if0` | 149,292 | 1.493 | 20 | 24 | fits | 150,549 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.aecp.last.if0` | 297,287 | 2.973 | 20 | 24 | fits | 148,985 | 222 | 0.360 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.maap.first.if0` | 297,221 | 2.972 | 20 | 50 | fits | 148,985 | 222 | 0.360 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.maap.last.if0` | 430,755 | 4.308 | 20 | 50 | fits | 133,930 | 163 | 0.309 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-0.service.srp.first.if0` | 558,884 | 5.589 | 20 | 20 | fits | 128,195 | 53 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-0.service.srp.last.if0` | 793,789 | 7.938 | 20 | 20 | fits | 98,769 | 44 | 0.469 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-1.adp_available.if0` | 365,867 | 3.659 | 20 | 20 | fits | 133,921 | 164 | 0.304 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.adp.first.if0` | 299,268 | 2.993 | 20 | 200 | fits | 148,160 | 217 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.adp.last.if0` | 432,573 | 4.326 | 20 | 200 | fits | 133,921 | 164 | 0.304 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.acmp.first.if0` | 300,192 | 3.002 | 20 | 20 | fits | 148,160 | 217 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.acmp.last.if0` | 433,277 | 4.333 | 20 | 20 | fits | 133,921 | 164 | 0.304 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.aecp.first.if0` | 155,672 | 1.557 | 20 | 24 | fits | 150,549 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.aecp.last.if0` | 302,842 | 3.028 | 20 | 24 | fits | 148,160 | 217 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.maap.first.if0` | 302,776 | 3.028 | 20 | 50 | fits | 148,160 | 217 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.maap.last.if0` | 436,301 | 4.363 | 20 | 50 | fits | 133,921 | 164 | 0.304 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-1.service.srp.first.if0` | 576,973 | 5.770 | 20 | 20 | fits | 131,176 | 59 | 0.603 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-1.service.srp.last.if0` | 797,588 | 7.976 | 20 | 20 | fits | 98,608 | 44 | 0.462 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-2.adp_available.if0` | 385,229 | 3.852 | 20 | 20 | fits | 139,079 | 170 | 0.373 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.adp.first.if0` | 305,550 | 3.055 | 20 | 200 | fits | 148,298 | 218 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.adp.last.if0` | 453,372 | 4.534 | 20 | 200 | fits | 139,079 | 170 | 0.373 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.acmp.first.if0` | 306,474 | 3.065 | 20 | 20 | fits | 148,298 | 218 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.acmp.last.if0` | 454,076 | 4.541 | 20 | 20 | fits | 139,079 | 170 | 0.373 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.aecp.first.if0` | 161,816 | 1.618 | 20 | 24 | fits | 150,549 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.aecp.last.if0` | 309,124 | 3.091 | 20 | 24 | fits | 148,298 | 218 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.maap.first.if0` | 309,058 | 3.091 | 20 | 50 | fits | 148,298 | 218 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.maap.last.if0` | 457,100 | 4.571 | 20 | 50 | fits | 139,079 | 170 | 0.373 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-2.service.srp.first.if0` | 584,687 | 5.847 | 20 | 20 | fits | 127,653 | 52 | 0.581 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-2.service.srp.last.if0` | 809,425 | 8.094 | 20 | 20 | fits | 103,518 | 50 | 0.503 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-3.adp_available.if0` | 380,884 | 3.809 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.adp.first.if0` | 304,080 | 3.041 | 20 | 200 | fits | 148,560 | 218 | 0.375 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.adp.last.if0` | 438,856 | 4.389 | 20 | 200 | fits | 135,392 | 166 | 0.299 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.acmp.first.if0` | 305,004 | 3.050 | 20 | 20 | fits | 148,560 | 218 | 0.375 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.acmp.last.if0` | 439,560 | 4.396 | 20 | 20 | fits | 135,392 | 166 | 0.299 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.aecp.first.if0` | 151,621 | 1.516 | 20 | 24 | fits | 150,603 | 162 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.aecp.last.if0` | 307,654 | 3.077 | 20 | 24 | fits | 148,560 | 218 | 0.375 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.maap.first.if0` | 307,588 | 3.076 | 20 | 50 | fits | 148,560 | 218 | 0.375 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.maap.last.if0` | 442,584 | 4.426 | 20 | 50 | fits | 135,392 | 166 | 0.299 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-3.service.srp.first.if0` | 570,320 | 5.703 | 20 | 20 | fits | 127,802 | 52 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-3.service.srp.last.if0` | 874,029 | 8.740 | 20 | 20 | fits | 99,525 | 46 | 0.483 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-4.adp_available.if0` | 363,698 | 3.637 | 20 | 20 | fits | 133,828 | 163 | 0.306 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.adp.first.if0` | 297,760 | 2.978 | 20 | 200 | fits | 147,976 | 217 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.adp.last.if0` | 430,972 | 4.310 | 20 | 200 | fits | 133,828 | 163 | 0.306 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.acmp.first.if0` | 298,684 | 2.987 | 20 | 20 | fits | 147,976 | 217 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.acmp.last.if0` | 431,676 | 4.317 | 20 | 20 | fits | 133,828 | 163 | 0.306 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.aecp.first.if0` | 154,348 | 1.543 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.aecp.last.if0` | 301,334 | 3.013 | 20 | 24 | fits | 147,976 | 217 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.maap.first.if0` | 301,268 | 3.013 | 20 | 50 | fits | 147,976 | 217 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.maap.last.if0` | 434,700 | 4.347 | 20 | 50 | fits | 133,828 | 163 | 0.306 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-4.service.srp.first.if0` | 562,658 | 5.627 | 20 | 20 | fits | 128,024 | 52 | 0.586 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-4.service.srp.last.if0` | 869,007 | 8.690 | 20 | 20 | fits | 102,247 | 52 | 0.497 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-5.adp_available.if0` | 370,346 | 3.703 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.adp.first.if0` | 303,814 | 3.038 | 20 | 200 | fits | 148,046 | 217 | 0.360 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.adp.last.if0` | 436,909 | 4.369 | 20 | 200 | fits | 133,711 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.acmp.first.if0` | 304,738 | 3.047 | 20 | 20 | fits | 148,046 | 217 | 0.360 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.acmp.last.if0` | 437,613 | 4.376 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.aecp.first.if0` | 160,332 | 1.603 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.aecp.last.if0` | 307,388 | 3.074 | 20 | 24 | fits | 148,046 | 217 | 0.360 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.maap.first.if0` | 307,322 | 3.073 | 20 | 50 | fits | 148,046 | 217 | 0.360 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.maap.last.if0` | 440,637 | 4.406 | 20 | 50 | fits | 133,711 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-5.service.srp.first.if0` | 573,125 | 5.731 | 20 | 20 | fits | 132,554 | 58 | 0.597 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-5.service.srp.last.if0` | 886,510 | 8.865 | 20 | 20 | fits | 100,805 | 45 | 0.524 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-6.adp_available.if0` | 367,825 | 3.678 | 20 | 20 | fits | 142,239 | 169 | 0.348 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.adp.first.if0` | 293,660 | 2.937 | 20 | 200 | fits | 148,871 | 222 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.adp.last.if0` | 435,283 | 4.353 | 20 | 200 | fits | 142,239 | 169 | 0.348 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.acmp.first.if0` | 294,584 | 2.946 | 20 | 20 | fits | 148,871 | 222 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.acmp.last.if0` | 435,987 | 4.360 | 20 | 20 | fits | 142,239 | 169 | 0.348 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.aecp.first.if0` | 149,353 | 1.494 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.aecp.last.if0` | 297,234 | 2.972 | 20 | 24 | fits | 148,871 | 222 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.maap.first.if0` | 297,168 | 2.972 | 20 | 50 | fits | 148,871 | 222 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.maap.last.if0` | 439,011 | 4.390 | 20 | 50 | fits | 142,239 | 169 | 0.348 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-6.service.srp.first.if0` | 647,170 | 6.472 | 20 | 20 | fits | 131,279 | 60 | 0.592 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-6.service.srp.last.if0` | 879,168 | 8.792 | 20 | 20 | fits | 98,549 | 44 | 0.462 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged2-7.adp_available.if0` | 461,753 | 4.618 | 20 | 20 | fits | 138,904 | 173 | 0.328 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.adp.first.if0` | 304,509 | 3.045 | 20 | 200 | fits | 153,146 | 218 | 0.371 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.adp.last.if0` | 519,592 | 5.196 | 20 | 200 | fits | 138,904 | 173 | 0.328 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.acmp.first.if0` | 305,433 | 3.054 | 20 | 20 | fits | 153,146 | 218 | 0.371 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.acmp.last.if0` | 520,296 | 5.203 | 20 | 20 | fits | 138,904 | 173 | 0.328 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.aecp.first.if0` | 155,927 | 1.559 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.aecp.last.if0` | 308,083 | 3.081 | 20 | 24 | fits | 153,146 | 218 | 0.371 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.maap.first.if0` | 308,017 | 3.080 | 20 | 50 | fits | 153,146 | 218 | 0.371 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.maap.last.if0` | 523,320 | 5.233 | 20 | 50 | fits | 138,904 | 173 | 0.328 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged2-7.service.srp.first.if0` | 661,308 | 6.613 | 20 | 20 | fits | 128,603 | 53 | 0.595 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged2-7.service.srp.last.if0` | 881,300 | 8.813 | 20 | 20 | fits | 98,346 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-0.adp_available.if0` | 360,169 | 3.602 | 20 | 20 | fits | 133,828 | 163 | 0.306 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.adp.first.if0` | 294,231 | 2.942 | 20 | 200 | fits | 147,976 | 217 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.adp.last.if0` | 427,443 | 4.274 | 20 | 200 | fits | 133,828 | 163 | 0.306 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.acmp.first.if0` | 295,155 | 2.952 | 20 | 20 | fits | 147,976 | 217 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.acmp.last.if0` | 428,147 | 4.281 | 20 | 20 | fits | 133,828 | 163 | 0.306 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.aecp.first.if0` | 150,819 | 1.508 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.aecp.last.if0` | 297,805 | 2.978 | 20 | 24 | fits | 147,976 | 217 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.maap.first.if0` | 297,739 | 2.977 | 20 | 50 | fits | 147,976 | 217 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.maap.last.if0` | 431,171 | 4.312 | 20 | 50 | fits | 133,828 | 163 | 0.306 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-0.service.srp.first.if0` | 559,130 | 5.591 | 20 | 20 | fits | 128,025 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-0.service.srp.last.if0` | 793,844 | 7.938 | 20 | 20 | fits | 103,260 | 51 | 0.540 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-1.adp_available.if0` | 366,817 | 3.668 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.adp.first.if0` | 300,285 | 3.003 | 20 | 200 | fits | 148,046 | 217 | 0.360 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.adp.last.if0` | 433,380 | 4.334 | 20 | 200 | fits | 133,711 | 163 | 0.302 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.acmp.first.if0` | 301,209 | 3.012 | 20 | 20 | fits | 148,046 | 217 | 0.360 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.acmp.last.if0` | 434,084 | 4.341 | 20 | 20 | fits | 133,711 | 163 | 0.302 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.aecp.first.if0` | 156,803 | 1.568 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.aecp.last.if0` | 303,859 | 3.039 | 20 | 24 | fits | 148,046 | 217 | 0.360 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.maap.first.if0` | 303,793 | 3.038 | 20 | 50 | fits | 148,046 | 217 | 0.360 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.maap.last.if0` | 437,108 | 4.371 | 20 | 50 | fits | 133,711 | 163 | 0.302 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-1.service.srp.first.if0` | 565,119 | 5.651 | 20 | 20 | fits | 128,077 | 53 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-1.service.srp.last.if0` | 800,061 | 8.001 | 20 | 20 | fits | 98,756 | 44 | 0.469 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-2.adp_available.if0` | 372,106 | 3.721 | 20 | 20 | fits | 133,881 | 164 | 0.304 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.adp.first.if0` | 306,299 | 3.063 | 20 | 200 | fits | 148,076 | 217 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.adp.last.if0` | 439,564 | 4.396 | 20 | 200 | fits | 133,881 | 164 | 0.304 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.acmp.first.if0` | 307,223 | 3.072 | 20 | 20 | fits | 148,076 | 217 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.acmp.last.if0` | 440,268 | 4.403 | 20 | 20 | fits | 133,881 | 164 | 0.304 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.aecp.first.if0` | 162,787 | 1.628 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.aecp.last.if0` | 309,873 | 3.099 | 20 | 24 | fits | 148,076 | 217 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.maap.first.if0` | 309,807 | 3.098 | 20 | 50 | fits | 148,076 | 217 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.maap.last.if0` | 443,292 | 4.433 | 20 | 50 | fits | 133,881 | 164 | 0.304 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-2.service.srp.first.if0` | 584,030 | 5.840 | 20 | 20 | fits | 131,311 | 59 | 0.606 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-2.service.srp.last.if0` | 809,290 | 8.093 | 20 | 20 | fits | 103,331 | 50 | 0.498 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-3.adp_available.if0` | 376,055 | 3.761 | 20 | 20 | fits | 138,575 | 170 | 0.363 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.adp.first.if0` | 295,968 | 2.960 | 20 | 200 | fits | 148,134 | 218 | 0.361 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.adp.last.if0` | 443,344 | 4.433 | 20 | 200 | fits | 138,575 | 170 | 0.363 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.acmp.first.if0` | 296,892 | 2.969 | 20 | 20 | fits | 148,134 | 218 | 0.361 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.acmp.last.if0` | 444,048 | 4.440 | 20 | 20 | fits | 138,575 | 170 | 0.363 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.aecp.first.if0` | 152,398 | 1.524 | 20 | 24 | fits | 150,642 | 161 | 0.379 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.aecp.last.if0` | 299,542 | 2.995 | 20 | 24 | fits | 148,134 | 218 | 0.361 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.maap.first.if0` | 299,476 | 2.995 | 20 | 50 | fits | 148,134 | 218 | 0.361 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.maap.last.if0` | 447,072 | 4.471 | 20 | 50 | fits | 138,575 | 170 | 0.363 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-3.service.srp.first.if0` | 574,788 | 5.748 | 20 | 20 | fits | 127,782 | 52 | 0.582 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-3.service.srp.last.if0` | 799,831 | 7.998 | 20 | 20 | fits | 98,412 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-4.adp_available.if0` | 378,502 | 3.785 | 20 | 20 | fits | 134,060 | 163 | 0.309 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.adp.first.if0` | 312,534 | 3.125 | 20 | 200 | fits | 150,183 | 222 | 0.368 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.adp.last.if0` | 445,978 | 4.460 | 20 | 200 | fits | 134,060 | 163 | 0.309 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.acmp.first.if0` | 313,458 | 3.135 | 20 | 20 | fits | 150,183 | 222 | 0.368 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.acmp.last.if0` | 446,682 | 4.467 | 20 | 20 | fits | 134,060 | 163 | 0.309 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.aecp.first.if0` | 158,461 | 1.585 | 20 | 24 | fits | 150,721 | 162 | 0.380 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.aecp.last.if0` | 316,108 | 3.161 | 20 | 24 | fits | 150,183 | 222 | 0.368 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.maap.first.if0` | 316,042 | 3.160 | 20 | 50 | fits | 150,183 | 222 | 0.368 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.maap.last.if0` | 449,706 | 4.497 | 20 | 50 | fits | 134,060 | 163 | 0.309 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-4.service.srp.first.if0` | 582,229 | 5.822 | 20 | 20 | fits | 132,589 | 58 | 0.599 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-4.service.srp.last.if0` | 802,046 | 8.020 | 20 | 20 | fits | 98,373 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-5.adp_available.if0` | 392,606 | 3.926 | 20 | 20 | fits | 142,078 | 169 | 0.345 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.adp.first.if0` | 318,088 | 3.181 | 20 | 200 | fits | 149,734 | 222 | 0.364 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.adp.last.if0` | 459,550 | 4.596 | 20 | 200 | fits | 142,078 | 169 | 0.345 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.acmp.first.if0` | 319,012 | 3.190 | 20 | 20 | fits | 149,734 | 222 | 0.364 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.acmp.last.if0` | 460,254 | 4.603 | 20 | 20 | fits | 142,078 | 169 | 0.345 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.aecp.first.if0` | 164,464 | 1.645 | 20 | 24 | fits | 150,740 | 162 | 0.381 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.aecp.last.if0` | 321,662 | 3.217 | 20 | 24 | fits | 149,734 | 222 | 0.364 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.maap.first.if0` | 321,596 | 3.216 | 20 | 50 | fits | 149,734 | 222 | 0.364 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.maap.last.if0` | 463,278 | 4.633 | 20 | 50 | fits | 142,078 | 169 | 0.345 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-5.service.srp.first.if0` | 591,238 | 5.912 | 20 | 20 | fits | 128,026 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-5.service.srp.last.if0` | 811,060 | 8.111 | 20 | 20 | fits | 98,373 | 44 | 0.456 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-6.adp_available.if0` | 368,261 | 3.683 | 20 | 20 | fits | 142,157 | 169 | 0.347 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.adp.first.if0` | 294,178 | 2.942 | 20 | 200 | fits | 148,090 | 217 | 0.362 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.adp.last.if0` | 435,719 | 4.357 | 20 | 200 | fits | 142,157 | 169 | 0.347 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.acmp.first.if0` | 295,102 | 2.951 | 20 | 20 | fits | 148,090 | 217 | 0.362 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.acmp.last.if0` | 436,423 | 4.364 | 20 | 20 | fits | 142,157 | 169 | 0.347 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.aecp.first.if0` | 150,652 | 1.507 | 20 | 24 | fits | 150,549 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.aecp.last.if0` | 297,752 | 2.978 | 20 | 24 | fits | 148,090 | 217 | 0.362 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.maap.first.if0` | 297,686 | 2.977 | 20 | 50 | fits | 148,090 | 217 | 0.362 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.maap.last.if0` | 439,447 | 4.394 | 20 | 50 | fits | 142,157 | 169 | 0.347 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-6.service.srp.first.if0` | 567,366 | 5.674 | 20 | 20 | fits | 127,985 | 52 | 0.585 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-6.service.srp.last.if0` | 790,418 | 7.904 | 20 | 20 | fits | 101,471 | 51 | 0.485 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog-adp@verify-aged1-7.adp_available.if0` | 382,238 | 3.822 | 20 | 20 | fits | 135,243 | 166 | 0.297 |
| ADP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.adp.first.if0` | 305,492 | 3.055 | 20 | 200 | fits | 153,260 | 218 | 0.372 |
| ADP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.adp.last.if0` | 440,119 | 4.401 | 20 | 200 | fits | 135,243 | 166 | 0.297 |
| ACMP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.acmp.first.if0` | 306,416 | 3.064 | 20 | 20 | fits | 153,260 | 218 | 0.372 |
| ACMP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.acmp.last.if0` | 440,823 | 4.408 | 20 | 20 | fits | 135,243 | 166 | 0.297 |
| AECP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.aecp.first.if0` | 156,796 | 1.568 | 20 | 24 | fits | 150,549 | 161 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.aecp.last.if0` | 309,066 | 3.091 | 20 | 24 | fits | 153,260 | 218 | 0.372 |
| MAAP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.maap.first.if0` | 309,000 | 3.090 | 20 | 50 | fits | 153,260 | 218 | 0.372 |
| MAAP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.maap.last.if0` | 443,847 | 4.438 | 20 | 50 | fits | 135,243 | 166 | 0.297 |
| SRP record released under the composed load, first | `backlog-adp@verify-aged1-7.service.srp.first.if0` | 571,885 | 5.719 | 20 | 20 | fits | 128,104 | 53 | 0.583 |
| SRP record released under the composed load, last | `backlog-adp@verify-aged1-7.service.srp.last.if0` | 806,882 | 8.069 | 20 | 20 | fits | 98,756 | 44 | 0.469 |
| LINK_UP | `adp.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 6,247 | 0.062 | 20 | 200 | fits | 21,893 | 23 (39) | 0.617 |
| TMR_ADVERTISE expiry | `adp.tmr_advertise.if0` | 6,282 | 0.063 | 20 | 200 | fits | 1,898 | 10 (11) | 0.368 |
| TMR_DELAY, or the first TMR_NO_RESP | `acmp.tmr_no_resp1.if0` | 20,394 | 0.204 | 20 | 20 | fits | 33,312 | 21 (35) | 0.794 |
| the second TMR_NO_RESP | `acmp.tmr_no_resp2.if0` | 15,559 | 0.156 | 20 | 20 | fits | 28,598 | 17 (14) | 0.816 |
| TMR_RETRY | `acmp.tmr_retry.if0` | 26,523 | 0.265 | 20 | 20 | fits | 31,994 | 24 (14) | 0.818 |
| TMR_DELAY | `acmp.tmr_delay.if0` | 26,581 | 0.266 | 20 | 20 | fits | 36,354 | 27 (35) | 0.762 |
| startup declarations (LINK_UP) | `srp.startup.if0` | 78,974 | 0.790 | 20 | 20 | fits | 27,820 | 8 | 0.843 |
| Listener Ready RX (registrar) | `srp.listener_ready.if0` | 40,558 | 0.406 | 20 | 20 | fits | 40,624 | 12 | 0.884 |
| malformed MRPDU discard | `srp.malformed.if0` | 22,118 | 0.221 | 20 | 20 | fits | 22,184 | 12 | 0.705 |
| Domain RX -> declarations (JoinTime wait) | `srp.domain.if0` | 73,460 | 0.735 | 220 | 220 | fits | 44,575 | 6 | 0.921 |
| an event behind 15 others | `backlog.event.if0` | 164,498 | 1.645 | 20 | 200 | fits | 54,950 | 78 | 0.527 |
| an ACMP command behind a full acmp ring | `backlog.acmp_command.if0` | 444,624 | 4.446 | 20 | 20 | fits | 58,748 | 81 | 0.208 |
| ADP record released under the composed load, first | `backlog.service.adp.first.if0` | 425,781 | 4.258 | 20 | 200 | fits | 153,913 | 131 | 0.253 |
| ADP record released under the composed load, last | `backlog.service.adp.last.if0` | 425,165 | 4.252 | 20 | 200 | fits | 153,913 | 131 | 0.253 |
| ACMP record released under the composed load, first | `backlog.service.acmp.first.if0` | 421,459 | 4.215 | 20 | 20 | fits | 153,913 | 131 | 0.253 |
| ACMP record released under the composed load, last | `backlog.service.acmp.last.if0` | 479,371 | 4.794 | 20 | 20 | fits | 58,748 | 81 | 0.208 |
| AECP record released under the composed load, first | `backlog.service.aecp.first.if0` | 154,733 | 1.547 | 20 | 24 | fits | 155,624 | 167 | 0.394 |
| AECP record released under the composed load, last | `backlog.service.aecp.last.if0` | 270,196 | 2.702 | 20 | 24 | fits | 61,503 | 26 | 0.693 |
| MAAP record released under the composed load, first | `backlog.service.maap.first.if0` | 424,043 | 4.240 | 20 | 50 | fits | 153,913 | 131 | 0.253 |
| MAAP record released under the composed load, last | `backlog.service.maap.last.if0` | 423,647 | 4.236 | 20 | 50 | fits | 153,913 | 131 | 0.253 |
| SRP record released under the composed load, first | `backlog.service.srp.first.if0` | 482,329 | 4.823 | 20 | 20 | fits | 58,748 | 81 | 0.208 |
| SRP record released under the composed load, last | `backlog.service.srp.last.if0` | 542,001 | 5.420 | 20 | 20 | fits | 26,296 | 41 | 0.101 |
| an ENTITY_AVAILABLE behind a full adp ring | `backlog.adp_available.if0` | 373,043 | 3.730 | 20 | 20 | fits | 138,402 | 170 | 0.373 |
| ADP record released under the composed load, first | `backlog-adp.service.adp.first.if0` | 293,876 | 2.939 | 20 | 200 | fits | 147,803 | 218 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp.service.adp.last.if0` | 441,044 | 4.410 | 20 | 200 | fits | 138,402 | 170 | 0.373 |
| ACMP record released under the composed load, first | `backlog-adp.service.acmp.first.if0` | 294,800 | 2.948 | 20 | 20 | fits | 147,803 | 218 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp.service.acmp.last.if0` | 441,748 | 4.417 | 20 | 20 | fits | 138,402 | 170 | 0.373 |
| AECP record released under the composed load, first | `backlog-adp.service.aecp.first.if0` | 150,637 | 1.506 | 20 | 24 | fits | 150,823 | 164 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp.service.aecp.last.if0` | 297,450 | 2.974 | 20 | 24 | fits | 147,803 | 218 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp.service.maap.first.if0` | 297,384 | 2.974 | 20 | 50 | fits | 147,803 | 218 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp.service.maap.last.if0` | 444,772 | 4.448 | 20 | 50 | fits | 138,402 | 170 | 0.373 |
| SRP record released under the composed load, first | `backlog-adp.service.srp.first.if0` | 572,318 | 5.723 | 20 | 20 | fits | 127,612 | 52 | 0.581 |
| SRP record released under the composed load, last | `backlog-adp.service.srp.last.if0` | 797,259 | 7.973 | 20 | 20 | fits | 98,420 | 44 | 0.458 |
| an ENTITY_AVAILABLE behind the adp ring, its bucket refilling (observed) | `backlog.adp_available_refill.if0` | 17,949 | 0.179 | 20 | 20 | fits | 30,971 | 19 | 0.773 |
| ADP record released under the composed load, first | `backlog-adp-refill.service.adp.first.if0` | 293,876 | 2.939 | 20 | 200 | fits | 147,803 | 218 | 0.359 |
| ADP record released under the composed load, last | `backlog-adp-refill.service.adp.last.if0` | 38,836 | 0.388 | 20 | 200 | fits | 30,971 | 19 | 0.773 |
| ACMP record released under the composed load, first | `backlog-adp-refill.service.acmp.first.if0` | 294,800 | 2.948 | 20 | 20 | fits | 147,803 | 218 | 0.359 |
| ACMP record released under the composed load, last | `backlog-adp-refill.service.acmp.last.if0` | 452,488 | 4.525 | 20 | 20 | fits | 149,142 | 164 | 0.456 |
| AECP record released under the composed load, first | `backlog-adp-refill.service.aecp.first.if0` | 150,637 | 1.506 | 20 | 24 | fits | 150,823 | 164 | 0.378 |
| AECP record released under the composed load, last | `backlog-adp-refill.service.aecp.last.if0` | 297,450 | 2.974 | 20 | 24 | fits | 147,803 | 218 | 0.359 |
| MAAP record released under the composed load, first | `backlog-adp-refill.service.maap.first.if0` | 297,384 | 2.974 | 20 | 50 | fits | 147,803 | 218 | 0.359 |
| MAAP record released under the composed load, last | `backlog-adp-refill.service.maap.last.if0` | 455,512 | 4.555 | 20 | 50 | fits | 149,142 | 164 | 0.456 |
| SRP record released under the composed load, first | `backlog-adp-refill.service.srp.first.if0` | 455,446 | 4.554 | 20 | 20 | fits | 149,142 | 164 | 0.456 |
| SRP record released under the composed load, last | `backlog-adp-refill.service.srp.last.if0` | 788,482 | 7.885 | 20 | 20 | fits | 81,505 | 36 | 0.512 |
| a response with 7 frames owed ahead of it | `backlog.owed.if0` | 6,322,634 | 63.226 | 20 | 20 | MISS ceiling | 21,268 | 13 | 0.500 |
| an ACMP command behind the owed input | `backlog.owed_behind0.if0` | 6,343,853 | 63.439 | 20 | 20 | MISS ceiling | 21,295 | 13 | 0.473 |
| an ACMP command behind the owed input | `backlog.owed_behind1.if0` | 6,364,994 | 63.650 | 20 | 20 | MISS ceiling | 21,198 | 13 | 0.481 |
| an ACMP command behind the owed input | `backlog.owed_behind2.if0` | 6,386,201 | 63.862 | 20 | 20 | MISS ceiling | 21,283 | 13 | 0.464 |
| an ACMP command behind the owed input | `backlog.owed_behind3.if0` | 6,407,230 | 64.072 | 20 | 20 | MISS ceiling | 21,092 | 13 | 0.500 |
| ADP record released under the composed load, first | `backlog-owed.service.adp.first.if0` | 166,230 | 1.662 | 20 | 200 | fits | 151,632 | 200 | 0.410 |
| ADP record released under the composed load, last | `backlog-owed.service.adp.last.if0` | 311,042 | 3.110 | 20 | 200 | fits | 145,428 | 189 | 0.431 |
| ACMP record released under the composed load, first | `backlog-owed.service.acmp.first.if0` | 161,908 | 1.619 | 20 | 20 | fits | 151,632 | 200 | 0.410 |
| ACMP record released under the composed load, last | `backlog-owed.service.acmp.last.if0` | 6,222,606 | 62.226 | 20 | 20 | MISS ceiling | 33,997 | 15 | 0.634 |
| AECP record released under the composed load, first | `backlog-owed.service.aecp.first.if0` | 165,548 | 1.655 | 20 | 24 | fits | 151,632 | 200 | 0.410 |
| AECP record released under the composed load, last | `backlog-owed.service.aecp.last.if0` | 6,157,588 | 61.576 | 20 | 24 | MISS ceiling | 140,803 | 107 | 0.435 |
| MAAP record released under the composed load, first | `backlog-owed.service.maap.first.if0` | 164,492 | 1.645 | 20 | 50 | fits | 151,632 | 200 | 0.410 |
| MAAP record released under the composed load, last | `backlog-owed.service.maap.last.if0` | 309,524 | 3.095 | 20 | 50 | fits | 145,428 | 189 | 0.431 |
| SRP record released under the composed load, first | `backlog-owed.service.srp.first.if0` | 309,458 | 3.095 | 20 | 20 | fits | 145,428 | 189 | 0.431 |
| SRP record released under the composed load, last | `backlog-owed.service.srp.last.if0` | 640,330 | 6.403 | 20 | 20 | fits | 80,803 | 36 | 0.489 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | `acmp.entity_departing.if0` | 5,856 | 0.059 | 20 | 20 | fits | 26,168 | 13 (29) | 0.690 |
| ENTITY_AVAILABLE from its RX_HEAD (H-DISC) | `acmp.entity_available.if0` | 9,139 | 0.091 | 20 | 20 | fits | 29,927 | 19 (35) | 0.754 |
| TMR_NO_ADP (H-DISC) | `acmp.tmr_no_adp.if0` | 20,528 | 0.205 | 20 | 20 | fits | 33,315 | 21 (12) | 0.792 |
| first PROBE (LINK_UP) | `maap.probe1.if0` | 14,133 | 0.141 | 20 | 50 | fits | 31,840 | 43 | 0.676 |
| PROBE retransmission (TMR expiry) | `maap.probe2.if0` | 19,694 | 0.197 | 20 | 50 | fits | 28,356 | 35 | 0.625 |
| PROBE retransmission (TMR expiry) | `maap.probe3.if0` | 23,209 | 0.232 | 20 | 50 | fits | 28,268 | 35 | 0.621 |
| last PROBE retransmission (TMR expiry) | `maap.probe4.if0` | 25,826 | 0.258 | 20 | 50 | fits | 33,203 | 61 | 0.561 |
| ANNOUNCE (TMR expiry) | `maap.announce.if0` | 27,759 | 0.278 | 20 | 50 | fits | 33,203 | 61 | 0.561 |
| conflicting PROBE -> DEFEND | `maap.defend.if0` | 13,212 | 0.132 | 20 | 50 | fits | 28,045 | 30 | 0.608 |
| LINK_UP | `adp.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 6,247 | 0.062 | 20 | 200 | fits | 21,893 | 23 (39) | 0.617 |
| LINK_DOWN | `adp.link_down.if0` | 1,687 | 0.017 | 20 | 200 | fits | 29,510 | 23 (9) | 0.686 |
| LINK_UP | `adp.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 6,247 | 0.062 | 20 | 200 | fits | 21,893 | 23 (39) | 0.617 |
| GM_CHANGE | `adp.gm_change.if0` | 1,896 | 0.019 | 20 | 200 | fits | 16,751 | 17 (11) | 0.382 |
| LINK_UP | `adp.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 6,247 | 0.062 | 20 | 200 | fits | 21,893 | 23 (39) | 0.617 |
| RCV_ADP_DISCOVER | `adp.discover.if0` | 3,857 | 0.039 | 20 | 200 | fits | 18,057 | 16 (31) | 0.517 |
| LINK_UP | `adp.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| TMR_DELAY expiry | `adp.tmr_delay.if0` | 6,247 | 0.062 | 20 | 200 | fits | 21,893 | 23 (39) | 0.617 |
| RCV_ADP_DISCOVER (control) | `control.discover.if0` | 3,857 | 0.039 | 20 | 200 | fits | 18,057 | 16 (31) | 0.517 |
| set_name | `aecp_fanout.set_name.if0` | 58,972 | 0.590 | 20 | 24 | fits | 57,454 | 88 | 0.541 |
| set_clock_source | `aecp_fanout.set_clock_source.if0` | 53,671 | 0.537 | 20 | 24 | fits | 52,447 | 77 | 0.581 |
| set_control_identify_on | `aecp_fanout.set_control_identify_on.if0` | 37,321 | 0.373 | 20 | 24 | fits | 47,729 | 78 | 0.546 |
| set_control_identify_off | `aecp_fanout.set_control_identify_off.if0` | 36,275 | 0.363 | 20 | 24 | fits | 47,753 | 77 | 0.542 |
| set_sampling_rate | `aecp_fanout.set_sampling_rate.if0` | 52,110 | 0.521 | 20 | 24 | fits | 50,739 | 67 | 0.575 |
| lock_entity | `aecp_fanout.lock_entity.if0` | 36,430 | 0.364 | 20 | 24 | fits | 47,569 | 77 | 0.548 |
| unlock_entity | `aecp_fanout.unlock_entity.if0` | 51,209 | 0.512 | 20 | 24 | fits | 46,953 | 78 | 0.531 |
| BIND_RX | `acmp.bind_rx.if0` | 19,361 | 0.194 | 20 | 20 | fits | 43,579 | 26 (77) | 0.761 |
| PROBE_TX_RESPONSE | `acmp.probe_tx_response.if0` | 9,728 | 0.097 | 20 | 20 | fits | 32,695 | 19 (32) | 0.804 |
| GET_RX_STATE | `acmp.get_rx_state.if0` | 9,581 | 0.096 | 20 | 20 | fits | 26,279 | 15 (47) | 0.687 |
| UNBIND_RX | `acmp.unbind_rx.if0` | 14,519 | 0.145 | 20 | 20 | fits | 41,050 | 18 (50) | 0.825 |
| PROBE_TX, refused TALKER_DEST_MAC_FAIL | `acmp.probe_tx.if0` | 9,691 | 0.097 | 20 | 20 | fits | 26,827 | 17 (48) | 0.681 |
| GET_TX_STATE | `acmp.get_tx_state.if0` | 8,949 | 0.089 | 20 | 20 | fits | 25,899 | 16 (48) | 0.615 |
| DISCONNECT_TX | `acmp.disconnect_tx.if0` | 8,590 | 0.086 | 20 | 20 | fits | 25,060 | 16 (48) | 0.598 |
| GET_TX_CONNECTION, refused NOT_SUPPORTED | `acmp.get_tx_connection.if0` | 9,115 | 0.091 | 20 | 20 | fits | 26,532 | 16 (48) | 0.700 |
| register_unsolicited | `aecp.register_unsolicited.if0` | 17,422 | 0.174 | 20 | 24 | fits | 27,900 | 20 | 0.750 |
| READ_DESCRIPTOR (312 B) | `aecp.read_descriptor.t0.i0.c0.if0` | 27,099 | 0.271 | 20 | 24 | fits | 31,682 | 20 | 0.670 |
| READ_DESCRIPTOR (106 B) | `aecp.read_descriptor.t1.i0.c0.if0` | 20,788 | 0.208 | 20 | 24 | fits | 28,200 | 20 | 0.697 |
| READ_DESCRIPTOR (148 B) | `aecp.read_descriptor.t2.i0.c0.if0` | 23,451 | 0.235 | 20 | 24 | fits | 27,469 | 20 | 0.687 |
| READ_DESCRIPTOR (146 B) | `aecp.read_descriptor.t5.i8.c0.if0` | 23,821 | 0.238 | 20 | 24 | fits | 28,110 | 20 | 0.685 |
| READ_DESCRIPTOR (146 B) | `aecp.read_descriptor.t6.i8.c0.if0` | 20,946 | 0.209 | 20 | 24 | fits | 28,358 | 20 | 0.689 |
| READ_DESCRIPTOR (102 B) | `aecp.read_descriptor.t9.i0.c0.if0` | 23,399 | 0.234 | 20 | 24 | fits | 27,417 | 20 | 0.691 |
| READ_DESCRIPTOR (86 B) | `aecp.read_descriptor.t10.i9.c0.if0` | 19,945 | 0.199 | 20 | 24 | fits | 27,123 | 20 | 0.699 |
| READ_DESCRIPTOR (72 B) | `aecp.read_descriptor.t12.i0.c0.if0` | 23,525 | 0.235 | 20 | 24 | fits | 27,619 | 20 | 0.713 |
| READ_DESCRIPTOR (452 B) | `aecp.read_descriptor.t13.i0.c0.if0` | 28,327 | 0.283 | 20 | 24 | fits | 33,035 | 21 | 0.609 |
| READ_DESCRIPTOR (20 B) | `aecp.read_descriptor.t14.i7.c0.if0` | 19,957 | 0.200 | 20 | 24 | fits | 27,304 | 20 | 0.727 |
| READ_DESCRIPTOR (20 B) | `aecp.read_descriptor.t15.i7.c0.if0` | 23,147 | 0.231 | 20 | 24 | fits | 27,241 | 20 | 0.733 |
| READ_DESCRIPTOR (90 B) | `aecp.read_descriptor.t20.i71.c0.if0` | 20,057 | 0.201 | 20 | 24 | fits | 27,314 | 20 | 0.690 |
| READ_DESCRIPTOR (113 B) | `aecp.read_descriptor.t26.i0.c0.if0` | 24,042 | 0.240 | 20 | 24 | fits | 28,215 | 20 | 0.699 |
| READ_DESCRIPTOR (96 B) | `aecp.read_descriptor.t36.i0.c0.if0` | 20,570 | 0.206 | 20 | 24 | fits | 27,982 | 20 | 0.693 |
| get_configuration | `aecp.get_configuration.if0` | 18,532 | 0.185 | 20 | 24 | fits | 25,480 | 20 | 0.716 |
| entity_available | `aecp.entity_available.if0` | 21,247 | 0.212 | 20 | 24 | fits | 25,136 | 20 | 0.698 |
| get_name | `aecp.get_name.if0` | 20,516 | 0.205 | 20 | 24 | fits | 28,013 | 20 | 0.719 |
| get_counters, refused ENTITY_MISBEHAVING | `aecp.get_counters.if0` | 25,474 | 0.255 | 20 | 24 | fits | 29,792 | 26 | 0.704 |
| get_avb_info, refused ENTITY_MISBEHAVING | `aecp.get_avb_info.if0` | 21,270 | 0.213 | 20 | 24 | fits | 28,713 | 29 | 0.718 |
| get_as_path, refused ENTITY_MISBEHAVING | `aecp.get_as_path.if0` | 11,116 | 0.111 | 20 | 24 | fits | 28,118 | 28 | 0.734 |
| unknown_command, refused NOT_IMPLEMENTED | `aecp.unknown_command.if0` | 22,361 | 0.224 | 20 | 24 | fits | 25,751 | 20 | 0.734 |
| MVU GET_MILAN_INFO | `aecp.mvu_get_milan_info.if0` | 17,906 | 0.179 | 20 | 24 | fits | 24,850 | 20 | 0.691 |
| set_name | `aecp.set_name.if0` | 30,038 | 0.300 | 20 | 24 | fits | 44,568 | 42 | 0.740 |
| lock_entity | `aecp.lock_entity.if0` | 23,400 | 0.234 | 20 | 24 | fits | 35,038 | 34 | 0.762 |
| unlock_entity | `aecp.unlock_entity.if0` | 24,362 | 0.244 | 20 | 24 | fits | 35,441 | 32 | 0.779 |
| READ_DESCRIPTOR held for a token (#917) | `aecp.held.read_descriptor.if0` | 517,676 | 5.177 | 20 | 24 | fits | 32,023 | 17 | 0.693 |
| LINK_UP | `fixture.link_up.if0` | 2,107 | 0.021 | 20 | 200 | fits | 31,840 | 43 (11) | 0.676 |
| malformed MRPDU discard | `fixture.malformed.if0` | 22,240 | 0.222 | 20 | 20 | fits | 22,306 | 12 | 0.714 |
| SET_NAME fan-out to one registered controller | `fixture.set_name.if0` | 32,083 | 0.321 | 20 | 24 | fits | 45,719 | 42 | 0.756 |
| LINK_DOWN | `fixture.link_down.if0` | 2,068 | 0.021 | 20 | 200 | fits | 31,214 | 23 (9) | 0.743 |
| BIND_RX | `fixture.bind_rx.if0` | 18,787 | 0.188 | 20 | 20 | fits | 43,356 | 26 (77) | 0.769 |
| TMR_DELAY, or the first TMR_NO_RESP | `fixture.tmr_no_resp1.if0` | 15,118 | 0.151 | 20 | 20 | fits | 41,442 | 29 (35) | 0.762 |
| ENTITY_DEPARTING from its RX_HEAD (H-DISC) | `fixture.entity_departing.if0` | 8,637 | 0.086 | 20 | 20 | fits | 27,455 | 13 (29) | 0.752 |
| ADP record released under the composed load, first | `fixture.service.adp.first.if0` | 86,077 | 0.861 | 20 | 200 | fits | 86,181 | 75 | 0.730 |
| ADP record released under the composed load, last | `fixture.service.adp.last.if0` | 86,077 | 0.861 | 20 | 200 | fits | 86,181 | 75 | 0.730 |
| ACMP record released under the composed load, first | `fixture.service.acmp.first.if0` | 85,803 | 0.858 | 20 | 20 | fits | 86,181 | 75 | 0.730 |
| ACMP record released under the composed load, last | `fixture.service.acmp.last.if0` | 85,803 | 0.858 | 20 | 20 | fits | 86,181 | 75 | 0.730 |
| AECP record released under the composed load, first | `fixture.service.aecp.first.if0` | 86,011 | 0.860 | 20 | 24 | fits | 86,181 | 75 | 0.730 |
| AECP record released under the composed load, last | `fixture.service.aecp.last.if0` | 86,011 | 0.860 | 20 | 24 | fits | 86,181 | 75 | 0.730 |
| MAAP record released under the composed load, first | `fixture.service.maap.first.if0` | 85,945 | 0.859 | 20 | 50 | fits | 86,181 | 75 | 0.730 |
| MAAP record released under the composed load, last | `fixture.service.maap.last.if0` | 85,945 | 0.859 | 20 | 50 | fits | 86,181 | 75 | 0.730 |
| SRP record released under the composed load, first | `fixture.service.srp.first.if0` | 85,879 | 0.859 | 20 | 20 | fits | 86,181 | 75 | 0.730 |
| SRP record released under the composed load, last | `fixture.service.srp.last.if0` | 85,879 | 0.859 | 20 | 20 | fits | 86,181 | 75 | 0.730 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
