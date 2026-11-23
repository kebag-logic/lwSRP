### 8x8-1if

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

0 of 7 paths and 0 of 728 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| ACMP record, every channel at its refill rate, the longest | 0 | `notice-every-4.held.acmp.if0` (notice-every-4) | 6.690 | fits | 11 acmp | 16 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `notice-burst-7.held.adp.if0` (notice-burst-7) | 6.173 | fits | 7 adp | 16 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `notice-every-4.held.aecp.if0` (notice-every-4) | 4.918 | fits | 15 aecp | 16 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `notice-every-3.held.maap.if0` (notice-every-3) | 6.108 | fits | 6 maap | 16 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `notice-every-1.held.srp.if0` (notice-every-1) | 9.288 | fits | 31 srp | 16 | 0 |
| an MRPDU its periodic timer owes, the longest | 0 | `notice-every-3.mrpdu.periodic.if0` (notice-every-3) | 1.200 | fits | 0 srp | 8 | 0 |
| a queued notice, from its port's answer | 0 | `notice-burst-5.notices.28.9.0.if0` (notice-burst-5) | 26.350 (26.618) | fits | 1 events | 640 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| notice-every-0 | 1519 | 0 | 163,143 (1.631) | fits |
| notice-every-1 | 1525 | 0 | 160,715 (1.607) | fits |
| notice-every-2 | 1517 | 0 | 158,525 (1.585) | fits |
| notice-every-3 | 1516 | 0 | 160,821 (1.608) | fits |
| notice-every-4 | 1519 | 0 | 162,755 (1.628) | fits |
| notice-every-5 | 1515 | 0 | 162,138 (1.621) | fits |
| notice-every-6 | 1510 | 0 | 157,215 (1.572) | fits |
| notice-every-7 | 1514 | 0 | 160,715 (1.607) | fits |
| notice-burst-0 | 1200 | 0 | 160,924 (1.609) | fits |
| notice-burst-1 | 1203 | 0 | 162,262 (1.623) | fits |
| notice-burst-2 | 1196 | 0 | 160,329 (1.603) | fits |
| notice-burst-3 | 1196 | 0 | 164,702 (1.647) | fits |
| notice-burst-4 | 1179 | 0 | 164,161 (1.642) | fits |
| notice-burst-5 | 1194 | 0 | 157,363 (1.574) | fits |
| notice-burst-6 | 1188 | 0 | 157,976 (1.580) | fits |
| notice-burst-7 | 1184 | 0 | 161,529 (1.615) | fits |

Retried notices, from the port's answer to the last recipient's commit (notice_window.py; ctrl_loop.h, THE RETRY):

| Group | ms | Bound ms | Recipients | Events held at the answer | Verdict |
|---|---:|---:|---:|---:|---|
| notice-every-0 | 4.121 | 130 | 16 | 2 | within |
| notice-every-0 | 4.296 | 130 | 16 | 2 | within |
| notice-every-0 | 6.151 | 130 | 16 | 2 | within |
| notice-every-0 | 6.323 | 130 | 16 | 2 | within |
| notice-every-0 | 8.161 | 130 | 16 | 2 | within |
| notice-every-0 | 8.336 | 130 | 16 | 2 | within |
| notice-every-0 | 2.175 | 130 | 16 | 2 | within |
| notice-every-0 | 2.358 | 130 | 16 | 2 | within |
| notice-every-0 | 2.522 | 130 | 16 | 2 | within |
| notice-every-0 | 2.696 | 130 | 16 | 2 | within |
| notice-every-0 | 4.457 | 130 | 16 | 2 | within |
| notice-every-0 | 4.627 | 130 | 16 | 2 | within |
| notice-every-0 | 6.481 | 130 | 16 | 2 | within |
| notice-every-0 | 6.650 | 130 | 16 | 2 | within |
| notice-every-0 | 8.494 | 130 | 16 | 2 | within |
| notice-every-0 | 8.662 | 130 | 16 | 2 | within |
| notice-every-0 | 10.159 | 130 | 16 | 2 | within |
| notice-every-0 | 10.333 | 130 | 16 | 2 | within |
| notice-every-0 | 10.480 | 130 | 16 | 2 | within |
| notice-every-0 | 10.647 | 130 | 16 | 2 | within |
| notice-every-0 | 12.120 | 130 | 16 | 2 | within |
| notice-every-0 | 12.296 | 130 | 16 | 2 | within |
| notice-every-0 | 12.450 | 130 | 16 | 2 | within |
| notice-every-0 | 12.619 | 130 | 16 | 2 | within |
| notice-every-0 | 14.109 | 130 | 16 | 2 | within |
| notice-every-0 | 14.282 | 130 | 16 | 2 | within |
| notice-every-0 | 14.431 | 130 | 16 | 2 | within |
| notice-every-0 | 14.596 | 130 | 16 | 2 | within |
| notice-every-0 | 16.227 | 130 | 16 | 2 | within |
| notice-every-0 | 16.398 | 130 | 16 | 2 | within |
| notice-every-0 | 16.543 | 130 | 16 | 2 | within |
| notice-every-0 | 16.708 | 130 | 16 | 2 | within |
| notice-every-0 | 18.135 | 130 | 16 | 2 | within |
| notice-every-0 | 18.307 | 130 | 16 | 2 | within |
| notice-every-0 | 18.453 | 130 | 16 | 2 | within |
| notice-every-0 | 18.617 | 130 | 16 | 2 | within |
| notice-every-0 | 20.420 | 130 | 16 | 2 | within |
| notice-every-0 | 20.545 | 130 | 16 | 2 | within |
| notice-every-0 | 20.711 | 130 | 16 | 2 | within |
| notice-every-0 | 20.877 | 130 | 16 | 2 | within |
| notice-every-1 | 4.122 | 130 | 16 | 2 | within |
| notice-every-1 | 4.297 | 130 | 16 | 2 | within |
| notice-every-1 | 6.151 | 130 | 16 | 2 | within |
| notice-every-1 | 6.324 | 130 | 16 | 2 | within |
| notice-every-1 | 8.162 | 130 | 16 | 2 | within |
| notice-every-1 | 8.338 | 130 | 16 | 2 | within |
| notice-every-1 | 2.173 | 130 | 16 | 2 | within |
| notice-every-1 | 2.355 | 130 | 16 | 2 | within |
| notice-every-1 | 2.520 | 130 | 16 | 2 | within |
| notice-every-1 | 2.694 | 130 | 16 | 2 | within |
| notice-every-1 | 4.458 | 130 | 16 | 2 | within |
| notice-every-1 | 4.629 | 130 | 16 | 2 | within |
| notice-every-1 | 6.482 | 130 | 16 | 2 | within |
| notice-every-1 | 6.651 | 130 | 16 | 2 | within |
| notice-every-1 | 8.495 | 130 | 16 | 2 | within |
| notice-every-1 | 8.663 | 130 | 16 | 2 | within |
| notice-every-1 | 10.164 | 130 | 16 | 2 | within |
| notice-every-1 | 10.338 | 130 | 16 | 2 | within |
| notice-every-1 | 10.485 | 130 | 16 | 2 | within |
| notice-every-1 | 10.652 | 130 | 16 | 2 | within |
| notice-every-1 | 12.125 | 130 | 16 | 2 | within |
| notice-every-1 | 12.302 | 130 | 16 | 2 | within |
| notice-every-1 | 12.455 | 130 | 16 | 2 | within |
| notice-every-1 | 12.624 | 130 | 16 | 2 | within |
| notice-every-1 | 14.114 | 130 | 16 | 2 | within |
| notice-every-1 | 14.287 | 130 | 16 | 2 | within |
| notice-every-1 | 14.436 | 130 | 16 | 2 | within |
| notice-every-1 | 14.602 | 130 | 16 | 2 | within |
| notice-every-1 | 16.232 | 130 | 16 | 2 | within |
| notice-every-1 | 16.404 | 130 | 16 | 2 | within |
| notice-every-1 | 16.548 | 130 | 16 | 2 | within |
| notice-every-1 | 16.713 | 130 | 16 | 2 | within |
| notice-every-1 | 18.141 | 130 | 16 | 2 | within |
| notice-every-1 | 18.312 | 130 | 16 | 2 | within |
| notice-every-1 | 18.458 | 130 | 16 | 2 | within |
| notice-every-1 | 18.623 | 130 | 16 | 2 | within |
| notice-every-1 | 20.203 | 130 | 16 | 2 | within |
| notice-every-1 | 20.327 | 130 | 16 | 2 | within |
| notice-every-1 | 20.493 | 130 | 16 | 2 | within |
| notice-every-1 | 20.659 | 130 | 16 | 2 | within |
| notice-every-2 | 5.978 | 130 | 16 | 1 | within |
| notice-every-2 | 6.151 | 130 | 16 | 1 | within |
| notice-every-2 | 7.987 | 130 | 16 | 1 | within |
| notice-every-2 | 8.161 | 130 | 16 | 1 | within |
| notice-every-2 | 1.961 | 130 | 16 | 1 | within |
| notice-every-2 | 2.142 | 130 | 16 | 1 | within |
| notice-every-2 | 4.155 | 130 | 16 | 1 | within |
| notice-every-2 | 4.334 | 130 | 16 | 1 | within |
| notice-every-2 | 2.307 | 130 | 16 | 1 | within |
| notice-every-2 | 2.481 | 130 | 16 | 1 | within |
| notice-every-2 | 4.495 | 130 | 16 | 1 | within |
| notice-every-2 | 4.665 | 130 | 16 | 1 | within |
| notice-every-2 | 6.310 | 130 | 16 | 1 | within |
| notice-every-2 | 6.479 | 130 | 16 | 1 | within |
| notice-every-2 | 8.319 | 130 | 16 | 1 | within |
| notice-every-2 | 8.487 | 130 | 16 | 1 | within |
| notice-every-2 | 9.985 | 130 | 16 | 1 | within |
| notice-every-2 | 10.158 | 130 | 16 | 1 | within |
| notice-every-2 | 10.305 | 130 | 16 | 1 | within |
| notice-every-2 | 10.472 | 130 | 16 | 1 | within |
| notice-every-2 | 11.945 | 130 | 16 | 1 | within |
| notice-every-2 | 12.120 | 130 | 16 | 1 | within |
| notice-every-2 | 12.274 | 130 | 16 | 1 | within |
| notice-every-2 | 12.443 | 130 | 16 | 1 | within |
| notice-every-2 | 13.932 | 130 | 16 | 1 | within |
| notice-every-2 | 14.105 | 130 | 16 | 1 | within |
| notice-every-2 | 14.254 | 130 | 16 | 1 | within |
| notice-every-2 | 14.419 | 130 | 16 | 1 | within |
| notice-every-2 | 16.049 | 130 | 16 | 1 | within |
| notice-every-2 | 16.220 | 130 | 16 | 1 | within |
| notice-every-2 | 16.365 | 130 | 16 | 1 | within |
| notice-every-2 | 16.529 | 130 | 16 | 1 | within |
| notice-every-2 | 17.957 | 130 | 16 | 1 | within |
| notice-every-2 | 18.129 | 130 | 16 | 1 | within |
| notice-every-2 | 18.275 | 130 | 16 | 1 | within |
| notice-every-2 | 18.439 | 130 | 16 | 1 | within |
| notice-every-2 | 20.018 | 130 | 16 | 1 | within |
| notice-every-2 | 20.141 | 130 | 16 | 1 | within |
| notice-every-2 | 20.308 | 130 | 16 | 1 | within |
| notice-every-2 | 20.474 | 130 | 16 | 1 | within |
| notice-every-3 | 8.004 | 130 | 16 | 2 | within |
| notice-every-3 | 8.180 | 130 | 16 | 2 | within |
| notice-every-3 | 2.012 | 130 | 16 | 2 | within |
| notice-every-3 | 2.190 | 130 | 16 | 2 | within |
| notice-every-3 | 4.158 | 130 | 16 | 2 | within |
| notice-every-3 | 4.334 | 130 | 16 | 2 | within |
| notice-every-3 | 5.988 | 130 | 16 | 2 | within |
| notice-every-3 | 6.164 | 130 | 16 | 2 | within |
| notice-every-3 | 2.356 | 130 | 16 | 2 | within |
| notice-every-3 | 2.530 | 130 | 16 | 2 | within |
| notice-every-3 | 4.494 | 130 | 16 | 2 | within |
| notice-every-3 | 4.665 | 130 | 16 | 2 | within |
| notice-every-3 | 6.322 | 130 | 16 | 2 | within |
| notice-every-3 | 6.491 | 130 | 16 | 2 | within |
| notice-every-3 | 8.337 | 130 | 16 | 2 | within |
| notice-every-3 | 8.505 | 130 | 16 | 2 | within |
| notice-every-3 | 10.004 | 130 | 16 | 2 | within |
| notice-every-3 | 10.177 | 130 | 16 | 2 | within |
| notice-every-3 | 10.324 | 130 | 16 | 2 | within |
| notice-every-3 | 10.491 | 130 | 16 | 2 | within |
| notice-every-3 | 12.191 | 130 | 16 | 2 | within |
| notice-every-3 | 12.367 | 130 | 16 | 2 | within |
| notice-every-3 | 12.521 | 130 | 16 | 2 | within |
| notice-every-3 | 12.690 | 130 | 16 | 2 | within |
| notice-every-3 | 14.144 | 130 | 16 | 2 | within |
| notice-every-3 | 14.316 | 130 | 16 | 2 | within |
| notice-every-3 | 14.465 | 130 | 16 | 2 | within |
| notice-every-3 | 14.630 | 130 | 16 | 2 | within |
| notice-every-3 | 16.068 | 130 | 16 | 2 | within |
| notice-every-3 | 16.239 | 130 | 16 | 2 | within |
| notice-every-3 | 16.384 | 130 | 16 | 2 | within |
| notice-every-3 | 16.549 | 130 | 16 | 2 | within |
| notice-every-3 | 17.975 | 130 | 16 | 2 | within |
| notice-every-3 | 18.146 | 130 | 16 | 2 | within |
| notice-every-3 | 18.292 | 130 | 16 | 2 | within |
| notice-every-3 | 18.457 | 130 | 16 | 2 | within |
| notice-every-3 | 20.036 | 130 | 16 | 2 | within |
| notice-every-3 | 20.160 | 130 | 16 | 2 | within |
| notice-every-3 | 20.326 | 130 | 16 | 2 | within |
| notice-every-3 | 20.492 | 130 | 16 | 2 | within |
| notice-every-4 | 8.205 | 130 | 16 | 2 | within |
| notice-every-4 | 8.381 | 130 | 16 | 2 | within |
| notice-every-4 | 2.216 | 130 | 16 | 2 | within |
| notice-every-4 | 2.395 | 130 | 16 | 2 | within |
| notice-every-4 | 4.160 | 130 | 16 | 2 | within |
| notice-every-4 | 4.336 | 130 | 16 | 2 | within |
| notice-every-4 | 6.190 | 130 | 16 | 2 | within |
| notice-every-4 | 6.366 | 130 | 16 | 2 | within |
| notice-every-4 | 2.561 | 130 | 16 | 2 | within |
| notice-every-4 | 2.735 | 130 | 16 | 2 | within |
| notice-every-4 | 4.496 | 130 | 16 | 2 | within |
| notice-every-4 | 4.666 | 130 | 16 | 2 | within |
| notice-every-4 | 6.525 | 130 | 16 | 2 | within |
| notice-every-4 | 6.693 | 130 | 16 | 2 | within |
| notice-every-4 | 8.539 | 130 | 16 | 2 | within |
| notice-every-4 | 8.706 | 130 | 16 | 2 | within |
| notice-every-4 | 10.203 | 130 | 16 | 2 | within |
| notice-every-4 | 10.376 | 130 | 16 | 2 | within |
| notice-every-4 | 10.523 | 130 | 16 | 2 | within |
| notice-every-4 | 10.690 | 130 | 16 | 2 | within |
| notice-every-4 | 12.162 | 130 | 16 | 2 | within |
| notice-every-4 | 12.338 | 130 | 16 | 2 | within |
| notice-every-4 | 12.492 | 130 | 16 | 2 | within |
| notice-every-4 | 12.661 | 130 | 16 | 2 | within |
| notice-every-4 | 14.149 | 130 | 16 | 2 | within |
| notice-every-4 | 14.322 | 130 | 16 | 2 | within |
| notice-every-4 | 14.471 | 130 | 16 | 2 | within |
| notice-every-4 | 14.636 | 130 | 16 | 2 | within |
| notice-every-4 | 16.077 | 130 | 16 | 2 | within |
| notice-every-4 | 16.248 | 130 | 16 | 2 | within |
| notice-every-4 | 16.392 | 130 | 16 | 2 | within |
| notice-every-4 | 16.557 | 130 | 16 | 2 | within |
| notice-every-4 | 18.174 | 130 | 16 | 2 | within |
| notice-every-4 | 18.345 | 130 | 16 | 2 | within |
| notice-every-4 | 18.491 | 130 | 16 | 2 | within |
| notice-every-4 | 18.655 | 130 | 16 | 2 | within |
| notice-every-4 | 20.048 | 130 | 16 | 2 | within |
| notice-every-4 | 20.171 | 130 | 16 | 2 | within |
| notice-every-4 | 20.338 | 130 | 16 | 2 | within |
| notice-every-4 | 20.504 | 130 | 16 | 2 | within |
| notice-every-5 | 8.003 | 130 | 16 | 2 | within |
| notice-every-5 | 8.179 | 130 | 16 | 2 | within |
| notice-every-5 | 2.012 | 130 | 16 | 2 | within |
| notice-every-5 | 2.190 | 130 | 16 | 2 | within |
| notice-every-5 | 4.157 | 130 | 16 | 2 | within |
| notice-every-5 | 4.333 | 130 | 16 | 2 | within |
| notice-every-5 | 5.987 | 130 | 16 | 2 | within |
| notice-every-5 | 6.163 | 130 | 16 | 2 | within |
| notice-every-5 | 2.356 | 130 | 16 | 2 | within |
| notice-every-5 | 2.530 | 130 | 16 | 2 | within |
| notice-every-5 | 4.493 | 130 | 16 | 2 | within |
| notice-every-5 | 4.664 | 130 | 16 | 2 | within |
| notice-every-5 | 6.322 | 130 | 16 | 2 | within |
| notice-every-5 | 6.490 | 130 | 16 | 2 | within |
| notice-every-5 | 8.337 | 130 | 16 | 2 | within |
| notice-every-5 | 8.504 | 130 | 16 | 2 | within |
| notice-every-5 | 10.003 | 130 | 16 | 2 | within |
| notice-every-5 | 10.176 | 130 | 16 | 2 | within |
| notice-every-5 | 10.323 | 130 | 16 | 2 | within |
| notice-every-5 | 10.490 | 130 | 16 | 2 | within |
| notice-every-5 | 12.190 | 130 | 16 | 2 | within |
| notice-every-5 | 12.366 | 130 | 16 | 2 | within |
| notice-every-5 | 12.520 | 130 | 16 | 2 | within |
| notice-every-5 | 12.689 | 130 | 16 | 2 | within |
| notice-every-5 | 14.143 | 130 | 16 | 2 | within |
| notice-every-5 | 14.315 | 130 | 16 | 2 | within |
| notice-every-5 | 14.464 | 130 | 16 | 2 | within |
| notice-every-5 | 14.629 | 130 | 16 | 2 | within |
| notice-every-5 | 16.067 | 130 | 16 | 2 | within |
| notice-every-5 | 16.239 | 130 | 16 | 2 | within |
| notice-every-5 | 16.383 | 130 | 16 | 2 | within |
| notice-every-5 | 16.548 | 130 | 16 | 2 | within |
| notice-every-5 | 17.974 | 130 | 16 | 2 | within |
| notice-every-5 | 18.145 | 130 | 16 | 2 | within |
| notice-every-5 | 18.291 | 130 | 16 | 2 | within |
| notice-every-5 | 18.456 | 130 | 16 | 2 | within |
| notice-every-5 | 20.035 | 130 | 16 | 2 | within |
| notice-every-5 | 20.159 | 130 | 16 | 2 | within |
| notice-every-5 | 20.325 | 130 | 16 | 2 | within |
| notice-every-5 | 20.491 | 130 | 16 | 2 | within |
| notice-every-6 | 2.170 | 130 | 16 | 2 | within |
| notice-every-6 | 2.347 | 130 | 16 | 2 | within |
| notice-every-6 | 4.308 | 130 | 16 | 2 | within |
| notice-every-6 | 4.480 | 130 | 16 | 2 | within |
| notice-every-6 | 6.376 | 130 | 16 | 2 | within |
| notice-every-6 | 6.549 | 130 | 16 | 2 | within |
| notice-every-6 | 8.176 | 130 | 16 | 2 | within |
| notice-every-6 | 8.350 | 130 | 16 | 2 | within |
| notice-every-6 | 2.512 | 130 | 16 | 2 | within |
| notice-every-6 | 2.686 | 130 | 16 | 2 | within |
| notice-every-6 | 4.641 | 130 | 16 | 2 | within |
| notice-every-6 | 4.811 | 130 | 16 | 2 | within |
| notice-every-6 | 6.706 | 130 | 16 | 2 | within |
| notice-every-6 | 6.875 | 130 | 16 | 2 | within |
| notice-every-6 | 8.507 | 130 | 16 | 2 | within |
| notice-every-6 | 8.675 | 130 | 16 | 2 | within |
| notice-every-6 | 10.173 | 130 | 16 | 2 | within |
| notice-every-6 | 10.346 | 130 | 16 | 2 | within |
| notice-every-6 | 10.493 | 130 | 16 | 2 | within |
| notice-every-6 | 10.660 | 130 | 16 | 2 | within |
| notice-every-6 | 12.133 | 130 | 16 | 2 | within |
| notice-every-6 | 12.309 | 130 | 16 | 2 | within |
| notice-every-6 | 12.462 | 130 | 16 | 2 | within |
| notice-every-6 | 12.631 | 130 | 16 | 2 | within |
| notice-every-6 | 14.313 | 130 | 16 | 2 | within |
| notice-every-6 | 14.485 | 130 | 16 | 2 | within |
| notice-every-6 | 14.634 | 130 | 16 | 2 | within |
| notice-every-6 | 14.800 | 130 | 16 | 2 | within |
| notice-every-6 | 16.238 | 130 | 16 | 2 | within |
| notice-every-6 | 16.409 | 130 | 16 | 2 | within |
| notice-every-6 | 16.554 | 130 | 16 | 2 | within |
| notice-every-6 | 16.719 | 130 | 16 | 2 | within |
| notice-every-6 | 18.145 | 130 | 16 | 2 | within |
| notice-every-6 | 18.316 | 130 | 16 | 2 | within |
| notice-every-6 | 18.462 | 130 | 16 | 2 | within |
| notice-every-6 | 18.627 | 130 | 16 | 2 | within |
| notice-every-6 | 20.207 | 130 | 16 | 2 | within |
| notice-every-6 | 20.330 | 130 | 16 | 2 | within |
| notice-every-6 | 20.497 | 130 | 16 | 2 | within |
| notice-every-6 | 20.662 | 130 | 16 | 2 | within |
| notice-every-7 | 4.118 | 130 | 16 | 2 | within |
| notice-every-7 | 4.292 | 130 | 16 | 2 | within |
| notice-every-7 | 6.144 | 130 | 16 | 2 | within |
| notice-every-7 | 6.316 | 130 | 16 | 2 | within |
| notice-every-7 | 8.152 | 130 | 16 | 2 | within |
| notice-every-7 | 8.327 | 130 | 16 | 2 | within |
| notice-every-7 | 2.172 | 130 | 16 | 2 | within |
| notice-every-7 | 2.355 | 130 | 16 | 2 | within |
| notice-every-7 | 2.519 | 130 | 16 | 2 | within |
| notice-every-7 | 2.693 | 130 | 16 | 2 | within |
| notice-every-7 | 4.454 | 130 | 16 | 2 | within |
| notice-every-7 | 4.624 | 130 | 16 | 2 | within |
| notice-every-7 | 6.474 | 130 | 16 | 2 | within |
| notice-every-7 | 6.643 | 130 | 16 | 2 | within |
| notice-every-7 | 8.485 | 130 | 16 | 2 | within |
| notice-every-7 | 8.653 | 130 | 16 | 2 | within |
| notice-every-7 | 10.149 | 130 | 16 | 2 | within |
| notice-every-7 | 10.322 | 130 | 16 | 2 | within |
| notice-every-7 | 10.469 | 130 | 16 | 2 | within |
| notice-every-7 | 10.636 | 130 | 16 | 2 | within |
| notice-every-7 | 12.109 | 130 | 16 | 2 | within |
| notice-every-7 | 12.285 | 130 | 16 | 2 | within |
| notice-every-7 | 12.438 | 130 | 16 | 2 | within |
| notice-every-7 | 12.608 | 130 | 16 | 2 | within |
| notice-every-7 | 14.096 | 130 | 16 | 2 | within |
| notice-every-7 | 14.269 | 130 | 16 | 2 | within |
| notice-every-7 | 14.418 | 130 | 16 | 2 | within |
| notice-every-7 | 14.583 | 130 | 16 | 2 | within |
| notice-every-7 | 16.023 | 130 | 16 | 2 | within |
| notice-every-7 | 16.195 | 130 | 16 | 2 | within |
| notice-every-7 | 16.339 | 130 | 16 | 2 | within |
| notice-every-7 | 16.504 | 130 | 16 | 2 | within |
| notice-every-7 | 18.120 | 130 | 16 | 2 | within |
| notice-every-7 | 18.292 | 130 | 16 | 2 | within |
| notice-every-7 | 18.438 | 130 | 16 | 2 | within |
| notice-every-7 | 18.602 | 130 | 16 | 2 | within |
| notice-every-7 | 19.995 | 130 | 16 | 2 | within |
| notice-every-7 | 20.118 | 130 | 16 | 2 | within |
| notice-every-7 | 20.285 | 130 | 16 | 2 | within |
| notice-every-7 | 20.451 | 130 | 16 | 2 | within |
| notice-burst-0 | 2.188 | 130 | 16 | 0 | within |
| notice-burst-0 | 2.364 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.020 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.189 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.342 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.509 | 130 | 16 | 0 | within |
| notice-burst-0 | 4.288 | 130 | 16 | 0 | within |
| notice-burst-0 | 4.462 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.295 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.475 | 130 | 16 | 0 | within |
| notice-burst-0 | 4.620 | 130 | 16 | 0 | within |
| notice-burst-0 | 4.788 | 130 | 16 | 0 | within |
| notice-burst-0 | 5.058 | 130 | 16 | 0 | within |
| notice-burst-0 | 5.231 | 130 | 16 | 0 | within |
| notice-burst-0 | 5.390 | 130 | 16 | 0 | within |
| notice-burst-0 | 5.560 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.637 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.804 | 130 | 16 | 0 | within |
| notice-burst-0 | 15.707 | 130 | 16 | 0 | within |
| notice-burst-0 | 15.878 | 130 | 16 | 0 | within |
| notice-burst-0 | 16.031 | 130 | 16 | 0 | within |
| notice-burst-0 | 16.200 | 130 | 16 | 0 | within |
| notice-burst-0 | 17.656 | 130 | 16 | 0 | within |
| notice-burst-0 | 17.832 | 130 | 16 | 0 | within |
| notice-burst-0 | 17.984 | 130 | 16 | 0 | within |
| notice-burst-0 | 18.150 | 130 | 16 | 0 | within |
| notice-burst-0 | 19.780 | 130 | 16 | 0 | within |
| notice-burst-0 | 19.951 | 130 | 16 | 0 | within |
| notice-burst-0 | 20.097 | 130 | 16 | 0 | within |
| notice-burst-0 | 20.262 | 130 | 16 | 0 | within |
| notice-burst-0 | 21.688 | 130 | 16 | 0 | within |
| notice-burst-0 | 21.858 | 130 | 16 | 0 | within |
| notice-burst-0 | 2.548 | 130 | 16 | 0 | within |
| notice-burst-0 | 2.753 | 130 | 16 | 0 | within |
| notice-burst-0 | 22.004 | 130 | 16 | 0 | within |
| notice-burst-0 | 22.170 | 130 | 16 | 0 | within |
| notice-burst-0 | 23.788 | 130 | 16 | 0 | within |
| notice-burst-0 | 23.913 | 130 | 16 | 0 | within |
| notice-burst-0 | 24.079 | 130 | 16 | 0 | within |
| notice-burst-0 | 24.244 | 130 | 16 | 0 | within |
| notice-burst-1 | 3.956 | 130 | 16 | 1 | within |
| notice-burst-1 | 4.130 | 130 | 16 | 1 | within |
| notice-burst-1 | 4.757 | 130 | 16 | 1 | within |
| notice-burst-1 | 4.926 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.033 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.207 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.363 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.532 | 130 | 16 | 1 | within |
| notice-burst-1 | 15.843 | 130 | 16 | 1 | within |
| notice-burst-1 | 16.022 | 130 | 16 | 1 | within |
| notice-burst-1 | 16.179 | 130 | 16 | 1 | within |
| notice-burst-1 | 16.346 | 130 | 16 | 1 | within |
| notice-burst-1 | 5.092 | 130 | 16 | 1 | within |
| notice-burst-1 | 5.269 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.758 | 130 | 16 | 1 | within |
| notice-burst-1 | 6.934 | 130 | 16 | 1 | within |
| notice-burst-1 | 17.047 | 130 | 16 | 1 | within |
| notice-burst-1 | 17.219 | 130 | 16 | 1 | within |
| notice-burst-1 | 17.365 | 130 | 16 | 1 | within |
| notice-burst-1 | 17.530 | 130 | 16 | 1 | within |
| notice-burst-1 | 2.038 | 130 | 16 | 1 | within |
| notice-burst-1 | 2.239 | 130 | 16 | 1 | within |
| notice-burst-1 | 4.301 | 130 | 16 | 1 | within |
| notice-burst-1 | 4.491 | 130 | 16 | 1 | within |
| notice-burst-1 | 2.416 | 130 | 16 | 1 | within |
| notice-burst-1 | 2.609 | 130 | 16 | 1 | within |
| notice-burst-1 | 7.093 | 130 | 16 | 1 | within |
| notice-burst-1 | 7.268 | 130 | 16 | 1 | within |
| notice-burst-1 | 19.143 | 130 | 16 | 1 | within |
| notice-burst-1 | 19.314 | 130 | 16 | 1 | within |
| notice-burst-1 | 19.461 | 130 | 16 | 1 | within |
| notice-burst-1 | 19.626 | 130 | 16 | 1 | within |
| notice-burst-1 | 21.031 | 130 | 16 | 1 | within |
| notice-burst-1 | 21.201 | 130 | 16 | 1 | within |
| notice-burst-1 | 21.348 | 130 | 16 | 1 | within |
| notice-burst-1 | 21.513 | 130 | 16 | 1 | within |
| notice-burst-1 | 23.106 | 130 | 16 | 1 | within |
| notice-burst-1 | 23.231 | 130 | 16 | 1 | within |
| notice-burst-1 | 2.931 | 130 | 16 | 1 | within |
| notice-burst-1 | 3.138 | 130 | 16 | 1 | within |
| notice-burst-2 | 4.420 | 130 | 16 | 0 | within |
| notice-burst-2 | 4.593 | 130 | 16 | 0 | within |
| notice-burst-2 | 5.206 | 130 | 16 | 0 | within |
| notice-burst-2 | 5.377 | 130 | 16 | 0 | within |
| notice-burst-2 | 5.533 | 130 | 16 | 0 | within |
| notice-burst-2 | 5.702 | 130 | 16 | 0 | within |
| notice-burst-2 | 14.391 | 130 | 16 | 0 | within |
| notice-burst-2 | 14.569 | 130 | 16 | 0 | within |
| notice-burst-2 | 14.730 | 130 | 16 | 0 | within |
| notice-burst-2 | 14.900 | 130 | 16 | 0 | within |
| notice-burst-2 | 15.806 | 130 | 16 | 0 | within |
| notice-burst-2 | 15.978 | 130 | 16 | 0 | within |
| notice-burst-2 | 16.134 | 130 | 16 | 0 | within |
| notice-burst-2 | 16.301 | 130 | 16 | 0 | within |
| notice-burst-2 | 17.760 | 130 | 16 | 0 | within |
| notice-burst-2 | 17.932 | 130 | 16 | 0 | within |
| notice-burst-2 | 18.090 | 130 | 16 | 0 | within |
| notice-burst-2 | 18.256 | 130 | 16 | 0 | within |
| notice-burst-2 | 19.695 | 130 | 16 | 0 | within |
| notice-burst-2 | 19.866 | 130 | 16 | 0 | within |
| notice-burst-2 | 3.089 | 130 | 16 | 0 | within |
| notice-burst-2 | 3.283 | 130 | 16 | 0 | within |
| notice-burst-2 | 2.225 | 130 | 16 | 0 | within |
| notice-burst-2 | 2.429 | 130 | 16 | 0 | within |
| notice-burst-2 | 2.608 | 130 | 16 | 0 | within |
| notice-burst-2 | 2.801 | 130 | 16 | 0 | within |
| notice-burst-2 | 3.453 | 130 | 16 | 0 | within |
| notice-burst-2 | 3.642 | 130 | 16 | 0 | within |
| notice-burst-2 | 4.760 | 130 | 16 | 0 | within |
| notice-burst-2 | 4.946 | 130 | 16 | 0 | within |
| notice-burst-2 | 20.016 | 130 | 16 | 0 | within |
| notice-burst-2 | 20.181 | 130 | 16 | 0 | within |
| notice-burst-2 | 21.796 | 130 | 16 | 0 | within |
| notice-burst-2 | 21.966 | 130 | 16 | 0 | within |
| notice-burst-2 | 22.112 | 130 | 16 | 0 | within |
| notice-burst-2 | 22.278 | 130 | 16 | 0 | within |
| notice-burst-2 | 23.705 | 130 | 16 | 0 | within |
| notice-burst-2 | 23.830 | 130 | 16 | 0 | within |
| notice-burst-2 | 23.996 | 130 | 16 | 0 | within |
| notice-burst-2 | 24.161 | 130 | 16 | 0 | within |
| notice-burst-3 | 5.690 | 130 | 16 | 1 | within |
| notice-burst-3 | 5.864 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.021 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.190 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.440 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.612 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.582 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.758 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.918 | 130 | 16 | 1 | within |
| notice-burst-3 | 16.086 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.773 | 130 | 16 | 1 | within |
| notice-burst-3 | 6.946 | 130 | 16 | 1 | within |
| notice-burst-3 | 16.985 | 130 | 16 | 1 | within |
| notice-burst-3 | 17.157 | 130 | 16 | 1 | within |
| notice-burst-3 | 17.314 | 130 | 16 | 1 | within |
| notice-burst-3 | 17.481 | 130 | 16 | 1 | within |
| notice-burst-3 | 2.027 | 130 | 16 | 1 | within |
| notice-burst-3 | 2.217 | 130 | 16 | 1 | within |
| notice-burst-3 | 2.379 | 130 | 16 | 1 | within |
| notice-burst-3 | 2.564 | 130 | 16 | 1 | within |
| notice-burst-3 | 3.550 | 130 | 16 | 1 | within |
| notice-burst-3 | 3.744 | 130 | 16 | 1 | within |
| notice-burst-3 | 19.116 | 130 | 16 | 1 | within |
| notice-burst-3 | 19.290 | 130 | 16 | 1 | within |
| notice-burst-3 | 4.376 | 130 | 16 | 1 | within |
| notice-burst-3 | 4.567 | 130 | 16 | 1 | within |
| notice-burst-3 | 3.919 | 130 | 16 | 1 | within |
| notice-burst-3 | 4.111 | 130 | 16 | 1 | within |
| notice-burst-3 | 4.738 | 130 | 16 | 1 | within |
| notice-burst-3 | 4.926 | 130 | 16 | 1 | within |
| notice-burst-3 | 19.440 | 130 | 16 | 1 | within |
| notice-burst-3 | 19.605 | 130 | 16 | 1 | within |
| notice-burst-3 | 21.032 | 130 | 16 | 1 | within |
| notice-burst-3 | 21.202 | 130 | 16 | 1 | within |
| notice-burst-3 | 21.348 | 130 | 16 | 1 | within |
| notice-burst-3 | 21.514 | 130 | 16 | 1 | within |
| notice-burst-3 | 22.943 | 130 | 16 | 1 | within |
| notice-burst-3 | 23.067 | 130 | 16 | 1 | within |
| notice-burst-3 | 23.234 | 130 | 16 | 1 | within |
| notice-burst-3 | 23.399 | 130 | 16 | 1 | within |
| notice-burst-4 | 14.539 | 130 | 16 | 0 | within |
| notice-burst-4 | 14.718 | 130 | 16 | 0 | within |
| notice-burst-4 | 14.876 | 130 | 16 | 0 | within |
| notice-burst-4 | 15.045 | 130 | 16 | 0 | within |
| notice-burst-4 | 15.755 | 130 | 16 | 0 | within |
| notice-burst-4 | 15.928 | 130 | 16 | 0 | within |
| notice-burst-4 | 16.085 | 130 | 16 | 0 | within |
| notice-burst-4 | 16.252 | 130 | 16 | 0 | within |
| notice-burst-4 | 2.224 | 130 | 16 | 0 | within |
| notice-burst-4 | 2.409 | 130 | 16 | 0 | within |
| notice-burst-4 | 17.710 | 130 | 16 | 0 | within |
| notice-burst-4 | 17.882 | 130 | 16 | 0 | within |
| notice-burst-4 | 18.038 | 130 | 16 | 0 | within |
| notice-burst-4 | 18.205 | 130 | 16 | 0 | within |
| notice-burst-4 | 19.653 | 130 | 16 | 0 | within |
| notice-burst-4 | 19.824 | 130 | 16 | 0 | within |
| notice-burst-4 | 19.981 | 130 | 16 | 0 | within |
| notice-burst-4 | 20.147 | 130 | 16 | 0 | within |
| notice-burst-4 | 5.268 | 130 | 16 | 0 | within |
| notice-burst-4 | 5.456 | 130 | 16 | 0 | within |
| notice-burst-4 | 5.626 | 130 | 16 | 0 | within |
| notice-burst-4 | 5.816 | 130 | 16 | 0 | within |
| notice-burst-4 | 3.090 | 130 | 16 | 0 | within |
| notice-burst-4 | 3.286 | 130 | 16 | 0 | within |
| notice-burst-4 | 3.461 | 130 | 16 | 0 | within |
| notice-burst-4 | 3.651 | 130 | 16 | 0 | within |
| notice-burst-4 | 4.448 | 130 | 16 | 0 | within |
| notice-burst-4 | 4.644 | 130 | 16 | 0 | within |
| notice-burst-4 | 4.816 | 130 | 16 | 0 | within |
| notice-burst-4 | 5.007 | 130 | 16 | 0 | within |
| notice-burst-4 | 21.765 | 130 | 16 | 0 | within |
| notice-burst-4 | 21.936 | 130 | 16 | 0 | within |
| notice-burst-4 | 2.595 | 130 | 16 | 0 | within |
| notice-burst-4 | 2.799 | 130 | 16 | 0 | within |
| notice-burst-4 | 22.082 | 130 | 16 | 0 | within |
| notice-burst-4 | 22.247 | 130 | 16 | 0 | within |
| notice-burst-4 | 23.722 | 130 | 16 | 0 | within |
| notice-burst-4 | 23.846 | 130 | 16 | 0 | within |
| notice-burst-4 | 24.012 | 130 | 16 | 0 | within |
| notice-burst-4 | 24.177 | 130 | 16 | 0 | within |
| notice-burst-5 | 14.646 | 130 | 16 | 1 | within |
| notice-burst-5 | 14.825 | 130 | 16 | 1 | within |
| notice-burst-5 | 14.982 | 130 | 16 | 1 | within |
| notice-burst-5 | 15.151 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.242 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.416 | 130 | 16 | 1 | within |
| notice-burst-5 | 2.202 | 130 | 16 | 1 | within |
| notice-burst-5 | 2.383 | 130 | 16 | 1 | within |
| notice-burst-5 | 5.225 | 130 | 16 | 1 | within |
| notice-burst-5 | 5.405 | 130 | 16 | 1 | within |
| notice-burst-5 | 5.571 | 130 | 16 | 1 | within |
| notice-burst-5 | 5.746 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.577 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.744 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.198 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.370 | 130 | 16 | 1 | within |
| notice-burst-5 | 2.557 | 130 | 16 | 1 | within |
| notice-burst-5 | 2.739 | 130 | 16 | 1 | within |
| notice-burst-5 | 4.092 | 130 | 16 | 1 | within |
| notice-burst-5 | 4.280 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.520 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.690 | 130 | 16 | 1 | within |
| notice-burst-5 | 4.451 | 130 | 16 | 1 | within |
| notice-burst-5 | 4.640 | 130 | 16 | 1 | within |
| notice-burst-5 | 20.128 | 130 | 16 | 1 | within |
| notice-burst-5 | 20.299 | 130 | 16 | 1 | within |
| notice-burst-5 | 20.448 | 130 | 16 | 1 | within |
| notice-burst-5 | 20.613 | 130 | 16 | 1 | within |
| notice-burst-5 | 22.218 | 130 | 16 | 1 | within |
| notice-burst-5 | 22.388 | 130 | 16 | 1 | within |
| notice-burst-5 | 22.534 | 130 | 16 | 1 | within |
| notice-burst-5 | 22.699 | 130 | 16 | 1 | within |
| notice-burst-5 | 24.187 | 130 | 16 | 1 | within |
| notice-burst-5 | 24.358 | 130 | 16 | 1 | within |
| notice-burst-5 | 24.505 | 130 | 16 | 1 | within |
| notice-burst-5 | 24.670 | 130 | 16 | 1 | within |
| notice-burst-5 | 26.226 | 130 | 16 | 1 | within |
| notice-burst-5 | 26.350 | 130 | 16 | 1 | within |
| notice-burst-5 | 3.060 | 130 | 16 | 1 | within |
| notice-burst-5 | 3.269 | 130 | 16 | 1 | within |
| notice-burst-6 | 14.132 | 130 | 16 | 0 | within |
| notice-burst-6 | 14.311 | 130 | 16 | 0 | within |
| notice-burst-6 | 14.469 | 130 | 16 | 0 | within |
| notice-burst-6 | 14.637 | 130 | 16 | 0 | within |
| notice-burst-6 | 15.735 | 130 | 16 | 0 | within |
| notice-burst-6 | 15.908 | 130 | 16 | 0 | within |
| notice-burst-6 | 2.781 | 130 | 16 | 0 | within |
| notice-burst-6 | 2.963 | 130 | 16 | 0 | within |
| notice-burst-6 | 3.129 | 130 | 16 | 0 | within |
| notice-burst-6 | 3.304 | 130 | 16 | 0 | within |
| notice-burst-6 | 1.663 | 130 | 16 | 0 | within |
| notice-burst-6 | 1.848 | 130 | 16 | 0 | within |
| notice-burst-6 | 2.015 | 130 | 16 | 0 | within |
| notice-burst-6 | 2.194 | 130 | 16 | 0 | within |
| notice-burst-6 | 4.077 | 130 | 16 | 0 | within |
| notice-burst-6 | 4.256 | 130 | 16 | 0 | within |
| notice-burst-6 | 4.419 | 130 | 16 | 0 | within |
| notice-burst-6 | 4.592 | 130 | 16 | 0 | within |
| notice-burst-6 | 4.847 | 130 | 16 | 0 | within |
| notice-burst-6 | 5.024 | 130 | 16 | 0 | within |
| notice-burst-6 | 16.058 | 130 | 16 | 0 | within |
| notice-burst-6 | 16.228 | 130 | 16 | 0 | within |
| notice-burst-6 | 5.188 | 130 | 16 | 0 | within |
| notice-burst-6 | 5.370 | 130 | 16 | 0 | within |
| notice-burst-6 | 17.685 | 130 | 16 | 0 | within |
| notice-burst-6 | 17.856 | 130 | 16 | 0 | within |
| notice-burst-6 | 18.005 | 130 | 16 | 0 | within |
| notice-burst-6 | 18.171 | 130 | 16 | 0 | within |
| notice-burst-6 | 19.609 | 130 | 16 | 0 | within |
| notice-burst-6 | 19.780 | 130 | 16 | 0 | within |
| notice-burst-6 | 19.926 | 130 | 16 | 0 | within |
| notice-burst-6 | 20.091 | 130 | 16 | 0 | within |
| notice-burst-6 | 21.705 | 130 | 16 | 0 | within |
| notice-burst-6 | 21.875 | 130 | 16 | 0 | within |
| notice-burst-6 | 22.021 | 130 | 16 | 0 | within |
| notice-burst-6 | 22.186 | 130 | 16 | 0 | within |
| notice-burst-6 | 23.615 | 130 | 16 | 0 | within |
| notice-burst-6 | 23.739 | 130 | 16 | 0 | within |
| notice-burst-6 | 23.906 | 130 | 16 | 0 | within |
| notice-burst-6 | 24.071 | 130 | 16 | 0 | within |
| notice-burst-7 | 15.886 | 130 | 16 | 1 | within |
| notice-burst-7 | 16.064 | 130 | 16 | 1 | within |
| notice-burst-7 | 2.195 | 130 | 16 | 1 | within |
| notice-burst-7 | 2.371 | 130 | 16 | 1 | within |
| notice-burst-7 | 2.529 | 130 | 16 | 1 | within |
| notice-burst-7 | 2.698 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.040 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.217 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.378 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.548 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.065 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.241 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.790 | 130 | 16 | 1 | within |
| notice-burst-7 | 4.964 | 130 | 16 | 1 | within |
| notice-burst-7 | 5.126 | 130 | 16 | 1 | within |
| notice-burst-7 | 5.299 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.403 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.573 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.785 | 130 | 16 | 1 | within |
| notice-burst-7 | 6.958 | 130 | 16 | 1 | within |
| notice-burst-7 | 7.114 | 130 | 16 | 1 | within |
| notice-burst-7 | 7.287 | 130 | 16 | 1 | within |
| notice-burst-7 | 16.215 | 130 | 16 | 1 | within |
| notice-burst-7 | 16.385 | 130 | 16 | 1 | within |
| notice-burst-7 | 17.081 | 130 | 16 | 1 | within |
| notice-burst-7 | 17.252 | 130 | 16 | 1 | within |
| notice-burst-7 | 17.400 | 130 | 16 | 1 | within |
| notice-burst-7 | 17.565 | 130 | 16 | 1 | within |
| notice-burst-7 | 19.169 | 130 | 16 | 1 | within |
| notice-burst-7 | 19.340 | 130 | 16 | 1 | within |
| notice-burst-7 | 19.486 | 130 | 16 | 1 | within |
| notice-burst-7 | 19.651 | 130 | 16 | 1 | within |
| notice-burst-7 | 21.057 | 130 | 16 | 1 | within |
| notice-burst-7 | 21.227 | 130 | 16 | 1 | within |
| notice-burst-7 | 21.373 | 130 | 16 | 1 | within |
| notice-burst-7 | 21.539 | 130 | 16 | 1 | within |
| notice-burst-7 | 23.132 | 130 | 16 | 1 | within |
| notice-burst-7 | 23.256 | 130 | 16 | 1 | within |
| notice-burst-7 | 3.018 | 130 | 16 | 1 | within |
| notice-burst-7 | 3.227 | 130 | 16 | 1 | within |

Latest: 26.350 ms, notice-burst-5.

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| notice-every-0 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-1 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-2 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-3 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-4 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-5 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-6 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-every-7 | 656 | 98,155 (0.982) | 77,825 (0.778) |
| notice-burst-0 | 666 | 98,155 (0.982) | 77,825 (0.778) |
| notice-burst-1 | 666 | 101,495 (1.015) | 77,825 (0.778) |
| notice-burst-2 | 666 | 99,731 (0.997) | 77,825 (0.778) |
| notice-burst-3 | 666 | 98,155 (0.982) | 77,825 (0.778) |
| notice-burst-4 | 665 | 98,155 (0.982) | 77,825 (0.778) |
| notice-burst-5 | 665 | 98,155 (0.982) | 77,825 (0.778) |
| notice-burst-6 | 666 | 98,630 (0.986) | 77,825 (0.778) |
| notice-burst-7 | 666 | 98,155 (0.982) | 77,825 (0.778) |

Longest pass that carries a step: 101,495 CPU cycles (1.015 ms), notice-burst-1; longest step: 77,825 (0.778 ms), notice-every-0.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.0.if0` | 412,120 | 4.121 | 130 | 134 | fits | 75,498 | 205 | 0.191 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.0.if0` | 429,585 | 4.296 | 130 | 134 | fits | 75,498 | 205 | 0.191 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.1.if0` | 615,102 | 6.151 | 130 | 134 | fits | 73,397 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.1.if0` | 632,331 | 6.323 | 130 | 134 | fits | 73,397 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.2.if0` | 816,086 | 8.161 | 130 | 134 | fits | 73,649 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.2.if0` | 833,630 | 8.336 | 130 | 134 | fits | 73,649 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.3.if0` | 217,464 | 2.175 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.3.if0` | 235,754 | 2.358 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.4.if0` | 252,232 | 2.522 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.4.if0` | 269,629 | 2.696 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.5.if0` | 445,723 | 4.457 | 130 | 134 | fits | 75,498 | 205 | 0.191 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.5.if0` | 462,745 | 4.627 | 130 | 134 | fits | 75,498 | 205 | 0.191 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.6.if0` | 648,147 | 6.481 | 130 | 134 | fits | 73,397 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.6.if0` | 665,017 | 6.650 | 130 | 134 | fits | 73,397 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.7.if0` | 849,389 | 8.494 | 130 | 134 | fits | 73,649 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.7.if0` | 866,172 | 8.662 | 130 | 134 | fits | 73,649 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.8.if0` | 1,015,886 | 10.159 | 130 | 134 | fits | 72,514 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.8.if0` | 1,033,272 | 10.333 | 130 | 134 | fits | 72,514 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.0.if0` | 1,047,980 | 10.480 | 130 | 134 | fits | 72,514 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.0.if0` | 1,064,657 | 10.647 | 130 | 134 | fits | 72,514 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.1.if0` | 1,212,023 | 12.120 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.1.if0` | 1,229,642 | 12.296 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.2.if0` | 1,245,008 | 12.450 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.2.if0` | 1,261,922 | 12.619 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.3.if0` | 1,410,895 | 14.109 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.3.if0` | 1,428,216 | 14.282 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.4.if0` | 1,443,116 | 14.431 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.4.if0` | 1,459,649 | 14.596 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.5.if0` | 1,622,679 | 16.227 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.5.if0` | 1,639,842 | 16.398 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.6.if0` | 1,654,310 | 16.543 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.6.if0` | 1,670,764 | 16.708 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.7.if0` | 1,813,535 | 18.135 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.7.if0` | 1,830,698 | 18.307 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.8.if0` | 1,845,296 | 18.453 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.8.if0` | 1,861,750 | 18.617 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-0.notices.27.9.0.if0` | 2,041,992 | 20.420 | 130 | 134 | fits | 65,106 | 203 | 0.148 |
| a queued notice, from its port's answer | `notice-every-0.notices.28.9.0.if0` | 2,054,454 | 20.545 | 130 | 134 | fits | 65,106 | 203 | 0.148 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.9.0.if0` | 2,071,129 | 20.711 | 130 | 134 | fits | 65,106 | 203 | 0.148 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.36.0.if0` | 2,087,667 | 20.877 | 130 | 134 | fits | 65,106 | 203 | 0.148 |
| ADP record, every channel at its refill rate, the longest | `notice-every-0.held.adp.if0` | 172,874 | 1.729 | 20 | 200 | fits | 152,527 | 222 | 0.262 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-0.held.acmp.if0` | 663,734 | 6.637 | 20 | 20 | fits | 137,406 | 76 | 0.640 |
| AECP record, every channel at its refill rate, the longest | `notice-every-0.held.aecp.if0` | 487,661 | 4.877 | 20 | 24 | fits | 155,451 | 151 | 0.462 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-0.held.maap.if0` | 468,390 | 4.684 | 20 | 50 | fits | 155,451 | 151 | 0.462 |
| SRP record, every channel at its refill rate, the longest | `notice-every-0.held.srp.if0` | 883,440 | 8.834 | 20 | 20 | fits | 126,587 | 73 | 0.575 |
| an MRPDU its periodic timer owes, the longest | `notice-every-0.mrpdu.periodic.if0` | 105,867 | 1.059 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.0.if0` | 412,230 | 4.122 | 130 | 134 | fits | 75,553 | 205 | 0.192 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.0.if0` | 429,695 | 4.297 | 130 | 134 | fits | 75,553 | 205 | 0.192 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.1.if0` | 615,137 | 6.151 | 130 | 134 | fits | 73,601 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.1.if0` | 632,366 | 6.324 | 130 | 134 | fits | 73,601 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.2.if0` | 816,206 | 8.162 | 130 | 134 | fits | 73,853 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.2.if0` | 833,750 | 8.338 | 130 | 134 | fits | 73,853 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.3.if0` | 217,252 | 2.173 | 130 | 134 | fits | 78,504 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.3.if0` | 235,542 | 2.355 | 130 | 134 | fits | 78,504 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.4.if0` | 252,020 | 2.520 | 130 | 134 | fits | 78,504 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.4.if0` | 269,417 | 2.694 | 130 | 134 | fits | 78,504 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.5.if0` | 445,833 | 4.458 | 130 | 134 | fits | 75,553 | 205 | 0.192 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.5.if0` | 462,855 | 4.629 | 130 | 134 | fits | 75,553 | 205 | 0.192 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.6.if0` | 648,182 | 6.482 | 130 | 134 | fits | 73,601 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.6.if0` | 665,052 | 6.651 | 130 | 134 | fits | 73,601 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.7.if0` | 849,509 | 8.495 | 130 | 134 | fits | 73,853 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.7.if0` | 866,292 | 8.663 | 130 | 134 | fits | 73,853 | 205 | 0.178 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.8.if0` | 1,016,409 | 10.164 | 130 | 134 | fits | 72,569 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.8.if0` | 1,033,795 | 10.338 | 130 | 134 | fits | 72,569 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.0.if0` | 1,048,503 | 10.485 | 130 | 134 | fits | 72,569 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.0.if0` | 1,065,180 | 10.652 | 130 | 134 | fits | 72,569 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.1.if0` | 1,212,546 | 12.125 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.1.if0` | 1,230,165 | 12.302 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.2.if0` | 1,245,531 | 12.455 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.2.if0` | 1,262,445 | 12.624 | 130 | 134 | fits | 72,602 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.3.if0` | 1,411,418 | 14.114 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.3.if0` | 1,428,739 | 14.287 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.4.if0` | 1,443,639 | 14.436 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.4.if0` | 1,460,172 | 14.602 | 130 | 134 | fits | 70,878 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.5.if0` | 1,623,202 | 16.232 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.5.if0` | 1,640,365 | 16.404 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.6.if0` | 1,654,833 | 16.548 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.6.if0` | 1,671,287 | 16.713 | 130 | 134 | fits | 69,880 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.7.if0` | 1,814,058 | 18.141 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.7.if0` | 1,831,221 | 18.312 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.8.if0` | 1,845,819 | 18.458 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.8.if0` | 1,862,273 | 18.623 | 130 | 134 | fits | 69,595 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-every-1.notices.27.9.0.if0` | 2,020,259 | 20.203 | 130 | 134 | fits | 64,762 | 203 | 0.140 |
| a queued notice, from its port's answer | `notice-every-1.notices.28.9.0.if0` | 2,032,668 | 20.327 | 130 | 134 | fits | 64,762 | 203 | 0.140 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.9.0.if0` | 2,049,343 | 20.493 | 130 | 134 | fits | 64,762 | 203 | 0.140 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.36.0.if0` | 2,065,881 | 20.659 | 130 | 134 | fits | 64,762 | 203 | 0.140 |
| ADP record, every channel at its refill rate, the longest | `notice-every-1.held.adp.if0` | 507,222 | 5.072 | 20 | 200 | fits | 152,005 | 129 | 0.483 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-1.held.acmp.if0` | 644,050 | 6.441 | 20 | 20 | fits | 138,215 | 90 | 0.585 |
| AECP record, every channel at its refill rate, the longest | `notice-every-1.held.aecp.if0` | 466,750 | 4.668 | 20 | 24 | fits | 152,005 | 129 | 0.483 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-1.held.maap.if0` | 447,479 | 4.475 | 20 | 50 | fits | 152,005 | 129 | 0.483 |
| SRP record, every channel at its refill rate, the longest | `notice-every-1.held.srp.if0` | 928,804 | 9.288 | 20 | 20 | fits | 40,158 | 25 | 0.812 |
| an MRPDU its periodic timer owes, the longest | `notice-every-1.mrpdu.periodic.if0` | 87,586 | 0.876 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.0.if0` | 597,808 | 5.978 | 130 | 134 | fits | 74,009 | 205 | 0.179 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.0.if0` | 615,146 | 6.151 | 130 | 134 | fits | 74,009 | 205 | 0.179 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.1.if0` | 798,707 | 7.987 | 130 | 134 | fits | 73,290 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.1.if0` | 816,111 | 8.161 | 130 | 134 | fits | 73,290 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.2.if0` | 196,091 | 1.961 | 130 | 134 | fits | 78,442 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.2.if0` | 214,199 | 2.142 | 130 | 134 | fits | 78,442 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.3.if0` | 415,456 | 4.155 | 130 | 134 | fits | 75,859 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.3.if0` | 433,414 | 4.334 | 130 | 134 | fits | 75,859 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.4.if0` | 230,691 | 2.307 | 130 | 134 | fits | 78,442 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.4.if0` | 248,118 | 2.481 | 130 | 134 | fits | 78,442 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.5.if0` | 449,525 | 4.495 | 130 | 134 | fits | 75,859 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.5.if0` | 466,547 | 4.665 | 130 | 134 | fits | 75,859 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.6.if0` | 630,991 | 6.310 | 130 | 134 | fits | 74,009 | 205 | 0.179 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.6.if0` | 647,861 | 6.479 | 130 | 134 | fits | 74,009 | 205 | 0.179 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.7.if0` | 831,870 | 8.319 | 130 | 134 | fits | 73,290 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.7.if0` | 848,653 | 8.487 | 130 | 134 | fits | 73,290 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.8.if0` | 998,452 | 9.985 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.8.if0` | 1,015,790 | 10.158 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.0.if0` | 1,030,498 | 10.305 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.0.if0` | 1,047,175 | 10.472 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.1.if0` | 1,194,461 | 11.945 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.1.if0` | 1,212,032 | 12.120 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.2.if0` | 1,227,398 | 12.274 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.2.if0` | 1,244,312 | 12.443 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.3.if0` | 1,393,182 | 13.932 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.3.if0` | 1,410,455 | 14.105 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.4.if0` | 1,425,355 | 14.254 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.4.if0` | 1,441,888 | 14.419 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.5.if0` | 1,604,897 | 16.049 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.5.if0` | 1,622,012 | 16.220 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.6.if0` | 1,636,480 | 16.365 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.6.if0` | 1,652,934 | 16.529 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.7.if0` | 1,795,745 | 17.957 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.7.if0` | 1,812,860 | 18.129 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.8.if0` | 1,827,458 | 18.275 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.8.if0` | 1,843,912 | 18.439 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-2.notices.27.9.0.if0` | 2,001,780 | 20.018 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-2.notices.28.9.0.if0` | 2,014,141 | 20.141 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.9.0.if0` | 2,030,816 | 20.308 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.36.0.if0` | 2,047,354 | 20.474 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-2.held.adp.if0` | 337,587 | 3.376 | 20 | 200 | fits | 107,912 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-2.held.acmp.if0` | 642,214 | 6.422 | 20 | 20 | fits | 140,030 | 109 | 0.621 |
| AECP record, every channel at its refill rate, the longest | `notice-every-2.held.aecp.if0` | 463,307 | 4.633 | 20 | 24 | fits | 158,525 | 131 | 0.471 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-2.held.maap.if0` | 602,739 | 6.027 | 20 | 50 | fits | 140,030 | 109 | 0.621 |
| SRP record, every channel at its refill rate, the longest | `notice-every-2.held.srp.if0` | 926,480 | 9.265 | 20 | 20 | fits | 42,012 | 31 | 0.804 |
| an MRPDU its periodic timer owes, the longest | `notice-every-2.mrpdu.periodic.if0` | 84,302 | 0.843 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.0.if0` | 800,395 | 8.004 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.0.if0` | 817,956 | 8.180 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.1.if0` | 201,201 | 2.012 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.1.if0` | 219,016 | 2.190 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.2.if0` | 415,799 | 4.158 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.2.if0` | 433,382 | 4.334 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.3.if0` | 598,783 | 5.988 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.3.if0` | 616,431 | 6.164 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.4.if0` | 235,623 | 2.356 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.4.if0` | 253,050 | 2.530 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.5.if0` | 449,428 | 4.494 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.5.if0` | 466,450 | 4.665 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.6.if0` | 632,247 | 6.322 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.6.if0` | 649,117 | 6.491 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.7.if0` | 833,742 | 8.337 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.7.if0` | 850,525 | 8.505 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.8.if0` | 1,000,379 | 10.004 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.8.if0` | 1,017,717 | 10.177 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.0.if0` | 1,032,425 | 10.324 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.0.if0` | 1,049,102 | 10.491 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.1.if0` | 1,219,072 | 12.191 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.1.if0` | 1,236,722 | 12.367 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.2.if0` | 1,252,088 | 12.521 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.2.if0` | 1,269,002 | 12.690 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.3.if0` | 1,414,361 | 14.144 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.3.if0` | 1,431,555 | 14.316 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.4.if0` | 1,446,455 | 14.465 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.4.if0` | 1,462,988 | 14.630 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.5.if0` | 1,606,834 | 16.068 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.5.if0` | 1,623,949 | 16.239 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.6.if0` | 1,638,417 | 16.384 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.6.if0` | 1,654,871 | 16.549 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.7.if0` | 1,797,517 | 17.975 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.7.if0` | 1,814,632 | 18.146 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.8.if0` | 1,829,230 | 18.292 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.8.if0` | 1,845,684 | 18.457 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-3.notices.27.9.0.if0` | 2,003,590 | 20.036 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-3.notices.28.9.0.if0` | 2,015,951 | 20.160 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.9.0.if0` | 2,032,626 | 20.326 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.36.0.if0` | 2,049,164 | 20.492 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-3.held.adp.if0` | 332,481 | 3.325 | 20 | 200 | fits | 107,991 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-3.held.acmp.if0` | 650,278 | 6.503 | 20 | 20 | fits | 140,548 | 98 | 0.630 |
| AECP record, every channel at its refill rate, the longest | `notice-every-3.held.aecp.if0` | 470,907 | 4.709 | 20 | 24 | fits | 158,818 | 134 | 0.472 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-3.held.maap.if0` | 610,803 | 6.108 | 20 | 50 | fits | 140,548 | 98 | 0.630 |
| SRP record, every channel at its refill rate, the longest | `notice-every-3.held.srp.if0` | 870,300 | 8.703 | 20 | 20 | fits | 132,223 | 69 | 0.556 |
| an MRPDU its periodic timer owes, the longest | `notice-every-3.mrpdu.periodic.if0` | 120,011 | 1.200 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.0.if0` | 820,513 | 8.205 | 130 | 134 | fits | 73,719 | 203 | 0.175 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.0.if0` | 838,074 | 8.381 | 130 | 134 | fits | 73,719 | 203 | 0.175 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.1.if0` | 221,637 | 2.216 | 130 | 134 | fits | 77,791 | 203 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.1.if0` | 239,452 | 2.395 | 130 | 134 | fits | 77,791 | 203 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.2.if0` | 415,981 | 4.160 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.2.if0` | 433,564 | 4.336 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.3.if0` | 618,994 | 6.190 | 130 | 134 | fits | 74,078 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.3.if0` | 636,642 | 6.366 | 130 | 134 | fits | 74,078 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.4.if0` | 256,083 | 2.561 | 130 | 134 | fits | 77,791 | 203 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.4.if0` | 273,510 | 2.735 | 130 | 134 | fits | 77,791 | 203 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.5.if0` | 449,610 | 4.496 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.5.if0` | 466,632 | 4.666 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.6.if0` | 652,458 | 6.525 | 130 | 134 | fits | 74,078 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.6.if0` | 669,328 | 6.693 | 130 | 134 | fits | 74,078 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.7.if0` | 853,860 | 8.539 | 130 | 134 | fits | 73,719 | 203 | 0.175 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.7.if0` | 870,643 | 8.706 | 130 | 134 | fits | 73,719 | 203 | 0.175 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.8.if0` | 1,020,256 | 10.203 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.8.if0` | 1,037,594 | 10.376 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.0.if0` | 1,052,302 | 10.523 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.0.if0` | 1,068,979 | 10.690 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.1.if0` | 1,216,216 | 12.162 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.1.if0` | 1,233,787 | 12.338 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.2.if0` | 1,249,153 | 12.492 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.2.if0` | 1,266,067 | 12.661 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.3.if0` | 1,414,937 | 14.149 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.3.if0` | 1,432,210 | 14.322 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.4.if0` | 1,447,110 | 14.471 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.4.if0` | 1,463,643 | 14.636 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.5.if0` | 1,607,654 | 16.077 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.5.if0` | 1,624,769 | 16.248 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.6.if0` | 1,639,237 | 16.392 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.6.if0` | 1,655,691 | 16.557 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.7.if0` | 1,817,354 | 18.174 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.7.if0` | 1,834,469 | 18.345 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.8.if0` | 1,849,067 | 18.491 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.8.if0` | 1,865,521 | 18.655 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-4.notices.27.9.0.if0` | 2,004,785 | 20.048 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-4.notices.28.9.0.if0` | 2,017,146 | 20.171 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.9.0.if0` | 2,033,821 | 20.338 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.36.0.if0` | 2,050,359 | 20.504 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-4.held.adp.if0` | 328,268 | 3.283 | 20 | 200 | fits | 107,912 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-4.held.acmp.if0` | 669,024 | 6.690 | 20 | 20 | fits | 138,483 | 80 | 0.637 |
| AECP record, every channel at its refill rate, the longest | `notice-every-4.held.aecp.if0` | 491,801 | 4.918 | 20 | 24 | fits | 155,775 | 153 | 0.467 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-4.held.maap.if0` | 472,530 | 4.725 | 20 | 50 | fits | 155,775 | 153 | 0.467 |
| SRP record, every channel at its refill rate, the longest | `notice-every-4.held.srp.if0` | 881,188 | 8.812 | 20 | 20 | fits | 124,471 | 65 | 0.569 |
| an MRPDU its periodic timer owes, the longest | `notice-every-4.mrpdu.periodic.if0` | 118,673 | 1.187 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.0.if0` | 800,310 | 8.003 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.0.if0` | 817,871 | 8.179 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.1.if0` | 201,201 | 2.012 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.1.if0` | 219,016 | 2.190 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.2.if0` | 415,714 | 4.157 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.2.if0` | 433,297 | 4.333 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.3.if0` | 598,698 | 5.987 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.3.if0` | 616,346 | 6.163 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.4.if0` | 235,623 | 2.356 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.4.if0` | 253,050 | 2.530 | 130 | 134 | fits | 77,892 | 205 | 0.214 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.5.if0` | 449,343 | 4.493 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.5.if0` | 466,365 | 4.664 | 130 | 134 | fits | 75,463 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.6.if0` | 632,162 | 6.322 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.6.if0` | 649,032 | 6.490 | 130 | 134 | fits | 74,227 | 205 | 0.175 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.7.if0` | 833,657 | 8.337 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.7.if0` | 850,440 | 8.504 | 130 | 134 | fits | 73,923 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.8.if0` | 1,000,294 | 10.003 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.8.if0` | 1,017,632 | 10.176 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.0.if0` | 1,032,340 | 10.323 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.0.if0` | 1,049,017 | 10.490 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.1.if0` | 1,218,987 | 12.190 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.1.if0` | 1,236,637 | 12.366 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.2.if0` | 1,252,003 | 12.520 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.2.if0` | 1,268,917 | 12.689 | 130 | 134 | fits | 72,866 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.3.if0` | 1,414,276 | 14.143 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.3.if0` | 1,431,470 | 14.315 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.4.if0` | 1,446,370 | 14.464 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.4.if0` | 1,462,903 | 14.629 | 130 | 134 | fits | 70,401 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.5.if0` | 1,606,749 | 16.067 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.5.if0` | 1,623,864 | 16.239 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.6.if0` | 1,638,332 | 16.383 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.6.if0` | 1,654,786 | 16.548 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.7.if0` | 1,797,432 | 17.974 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.7.if0` | 1,814,547 | 18.145 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.8.if0` | 1,829,145 | 18.291 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.8.if0` | 1,845,599 | 18.456 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-5.notices.27.9.0.if0` | 2,003,505 | 20.035 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-5.notices.28.9.0.if0` | 2,015,866 | 20.159 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.9.0.if0` | 2,032,541 | 20.325 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.36.0.if0` | 2,049,079 | 20.491 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-5.held.adp.if0` | 332,484 | 3.325 | 20 | 200 | fits | 107,991 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-5.held.acmp.if0` | 651,170 | 6.512 | 20 | 20 | fits | 138,321 | 80 | 0.634 |
| AECP record, every channel at its refill rate, the longest | `notice-every-5.held.aecp.if0` | 473,941 | 4.739 | 20 | 24 | fits | 154,481 | 147 | 0.466 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-5.held.maap.if0` | 454,670 | 4.547 | 20 | 50 | fits | 154,481 | 147 | 0.466 |
| SRP record, every channel at its refill rate, the longest | `notice-every-5.held.srp.if0` | 863,228 | 8.632 | 20 | 20 | fits | 124,393 | 65 | 0.568 |
| an MRPDU its periodic timer owes, the longest | `notice-every-5.mrpdu.periodic.if0` | 108,934 | 1.089 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.0.if0` | 216,963 | 2.170 | 130 | 134 | fits | 77,893 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.0.if0` | 234,686 | 2.347 | 130 | 134 | fits | 77,893 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.1.if0` | 430,752 | 4.308 | 130 | 134 | fits | 74,580 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.1.if0` | 448,012 | 4.480 | 130 | 134 | fits | 74,580 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.2.if0` | 637,603 | 6.376 | 130 | 134 | fits | 73,642 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.2.if0` | 654,876 | 6.549 | 130 | 134 | fits | 73,642 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.3.if0` | 817,577 | 8.176 | 130 | 134 | fits | 73,300 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.3.if0` | 834,994 | 8.350 | 130 | 134 | fits | 73,300 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.4.if0` | 251,154 | 2.512 | 130 | 134 | fits | 77,893 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.4.if0` | 268,581 | 2.686 | 130 | 134 | fits | 77,893 | 205 | 0.210 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.5.if0` | 464,123 | 4.641 | 130 | 134 | fits | 74,580 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.5.if0` | 481,145 | 4.811 | 130 | 134 | fits | 74,580 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.6.if0` | 670,646 | 6.706 | 130 | 134 | fits | 73,642 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.6.if0` | 687,516 | 6.875 | 130 | 134 | fits | 73,642 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.7.if0` | 850,722 | 8.507 | 130 | 134 | fits | 73,300 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.7.if0` | 867,505 | 8.675 | 130 | 134 | fits | 73,300 | 205 | 0.177 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.8.if0` | 1,017,288 | 10.173 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.8.if0` | 1,034,626 | 10.346 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.0.if0` | 1,049,334 | 10.493 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.0.if0` | 1,066,011 | 10.660 | 130 | 134 | fits | 72,433 | 203 | 0.169 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.1.if0` | 1,213,297 | 12.133 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.1.if0` | 1,230,868 | 12.309 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.2.if0` | 1,246,234 | 12.462 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.2.if0` | 1,263,148 | 12.631 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.3.if0` | 1,431,270 | 14.313 | 130 | 134 | fits | 70,801 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.3.if0` | 1,448,543 | 14.485 | 130 | 134 | fits | 70,801 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.4.if0` | 1,463,443 | 14.634 | 130 | 134 | fits | 70,801 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.4.if0` | 1,479,976 | 14.800 | 130 | 134 | fits | 70,801 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.5.if0` | 1,623,822 | 16.238 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.5.if0` | 1,640,937 | 16.409 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.6.if0` | 1,655,405 | 16.554 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.6.if0` | 1,671,859 | 16.719 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.7.if0` | 1,814,505 | 18.145 | 130 | 134 | fits | 69,538 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.7.if0` | 1,831,620 | 18.316 | 130 | 134 | fits | 69,538 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.8.if0` | 1,846,218 | 18.462 | 130 | 134 | fits | 69,538 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.8.if0` | 1,862,672 | 18.627 | 130 | 134 | fits | 69,538 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-6.notices.27.9.0.if0` | 2,020,657 | 20.207 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-6.notices.28.9.0.if0` | 2,033,018 | 20.330 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.9.0.if0` | 2,049,693 | 20.497 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.36.0.if0` | 2,066,231 | 20.662 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-6.held.adp.if0` | 333,889 | 3.339 | 20 | 200 | fits | 107,912 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-6.held.acmp.if0` | 636,871 | 6.369 | 20 | 20 | fits | 133,173 | 111 | 0.628 |
| AECP record, every channel at its refill rate, the longest | `notice-every-6.held.aecp.if0` | 460,721 | 4.607 | 20 | 24 | fits | 157,215 | 125 | 0.476 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-6.held.maap.if0` | 597,396 | 5.974 | 20 | 50 | fits | 133,173 | 111 | 0.628 |
| SRP record, every channel at its refill rate, the longest | `notice-every-6.held.srp.if0` | 925,181 | 9.252 | 20 | 20 | fits | 48,713 | 29 | 0.772 |
| an MRPDU its periodic timer owes, the longest | `notice-every-6.mrpdu.periodic.if0` | 77,893 | 0.779 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.0.if0` | 411,824 | 4.118 | 130 | 134 | fits | 75,213 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.0.if0` | 429,241 | 4.292 | 130 | 134 | fits | 75,213 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.1.if0` | 614,416 | 6.144 | 130 | 134 | fits | 73,261 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.1.if0` | 631,597 | 6.316 | 130 | 134 | fits | 73,261 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.2.if0` | 815,249 | 8.152 | 130 | 134 | fits | 73,513 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.2.if0` | 832,745 | 8.327 | 130 | 134 | fits | 73,513 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.3.if0` | 217,178 | 2.172 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.3.if0` | 235,468 | 2.355 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.4.if0` | 251,946 | 2.519 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.4.if0` | 269,343 | 2.693 | 130 | 134 | fits | 78,300 | 203 | 0.209 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.5.if0` | 445,379 | 4.454 | 130 | 134 | fits | 75,213 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.5.if0` | 462,401 | 4.624 | 130 | 134 | fits | 75,213 | 203 | 0.188 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.6.if0` | 647,413 | 6.474 | 130 | 134 | fits | 73,261 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.6.if0` | 664,283 | 6.643 | 130 | 134 | fits | 73,261 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.7.if0` | 848,504 | 8.485 | 130 | 134 | fits | 73,513 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.7.if0` | 865,287 | 8.653 | 130 | 134 | fits | 73,513 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.8.if0` | 1,014,898 | 10.149 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.8.if0` | 1,032,236 | 10.322 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.0.if0` | 1,046,944 | 10.469 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.0.if0` | 1,063,621 | 10.636 | 130 | 134 | fits | 72,378 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.1.if0` | 1,210,907 | 12.109 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.1.if0` | 1,228,478 | 12.285 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.2.if0` | 1,243,844 | 12.438 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.2.if0` | 1,260,758 | 12.608 | 130 | 134 | fits | 72,466 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.3.if0` | 1,409,628 | 14.096 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.3.if0` | 1,426,901 | 14.269 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.4.if0` | 1,441,801 | 14.418 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.4.if0` | 1,458,334 | 14.583 | 130 | 134 | fits | 70,742 | 203 | 0.170 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.5.if0` | 1,602,345 | 16.023 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.5.if0` | 1,619,460 | 16.195 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.6.if0` | 1,633,928 | 16.339 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.6.if0` | 1,650,382 | 16.504 | 130 | 134 | fits | 69,744 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.7.if0` | 1,812,045 | 18.120 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.7.if0` | 1,829,160 | 18.292 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.8.if0` | 1,843,758 | 18.438 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.8.if0` | 1,860,212 | 18.602 | 130 | 134 | fits | 69,459 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-every-7.notices.27.9.0.if0` | 1,999,476 | 19.995 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-7.notices.28.9.0.if0` | 2,011,837 | 20.118 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.9.0.if0` | 2,028,512 | 20.285 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.36.0.if0` | 2,045,050 | 20.451 | 130 | 134 | fits | 64,626 | 203 | 0.138 |
| ADP record, every channel at its refill rate, the longest | `notice-every-7.held.adp.if0` | 325,240 | 3.252 | 20 | 200 | fits | 107,912 | 114 | 0.352 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-7.held.acmp.if0` | 642,131 | 6.421 | 20 | 20 | fits | 139,560 | 92 | 0.637 |
| AECP record, every channel at its refill rate, the longest | `notice-every-7.held.aecp.if0` | 463,766 | 4.638 | 20 | 24 | fits | 159,030 | 132 | 0.475 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-7.held.maap.if0` | 602,656 | 6.027 | 20 | 50 | fits | 139,560 | 92 | 0.637 |
| SRP record, every channel at its refill rate, the longest | `notice-every-7.held.srp.if0` | 868,922 | 8.689 | 20 | 20 | fits | 134,640 | 77 | 0.565 |
| an MRPDU its periodic timer owes, the longest | `notice-every-7.mrpdu.periodic.if0` | 88,210 | 0.882 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.0.if0` | 218,777 | 2.188 | 130 | 134 | fits | 105,061 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.0.if0` | 236,402 | 2.364 | 130 | 134 | fits | 105,061 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.1.if0` | 302,021 | 3.020 | 130 | 134 | fits | 73,444 | 205 | 0.117 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.1.if0` | 318,898 | 3.189 | 130 | 134 | fits | 73,444 | 205 | 0.117 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.2.if0` | 334,193 | 3.342 | 130 | 134 | fits | 73,444 | 205 | 0.117 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.2.if0` | 350,905 | 3.509 | 130 | 134 | fits | 73,444 | 205 | 0.117 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.3.if0` | 428,818 | 4.288 | 130 | 134 | fits | 97,326 | 211 | 0.191 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.3.if0` | 446,210 | 4.462 | 130 | 134 | fits | 97,326 | 211 | 0.191 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.4.if0` | 1,429,532 | 14.295 | 130 | 134 | fits | 76,526 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.4.if0` | 1,447,499 | 14.475 | 130 | 134 | fits | 76,526 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.5.if0` | 461,972 | 4.620 | 130 | 134 | fits | 97,326 | 211 | 0.191 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.5.if0` | 478,836 | 4.788 | 130 | 134 | fits | 97,326 | 211 | 0.191 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.6.if0` | 505,793 | 5.058 | 130 | 134 | fits | 73,803 | 205 | 0.119 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.6.if0` | 523,071 | 5.231 | 130 | 134 | fits | 73,803 | 205 | 0.119 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.7.if0` | 538,961 | 5.390 | 130 | 134 | fits | 73,803 | 205 | 0.119 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.7.if0` | 556,048 | 5.560 | 130 | 134 | fits | 73,803 | 205 | 0.119 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.8.if0` | 1,463,655 | 14.637 | 130 | 134 | fits | 76,526 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.8.if0` | 1,480,432 | 14.804 | 130 | 134 | fits | 76,526 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.0.if0` | 1,570,671 | 15.707 | 130 | 134 | fits | 71,760 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.0.if0` | 1,587,840 | 15.878 | 130 | 134 | fits | 71,760 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.1.if0` | 1,603,055 | 16.031 | 130 | 134 | fits | 71,760 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.1.if0` | 1,620,042 | 16.200 | 130 | 134 | fits | 71,760 | 203 | 0.168 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.2.if0` | 1,765,617 | 17.656 | 130 | 134 | fits | 71,708 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.2.if0` | 1,783,163 | 17.832 | 130 | 134 | fits | 71,708 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.3.if0` | 1,798,437 | 17.984 | 130 | 134 | fits | 71,708 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.3.if0` | 1,815,043 | 18.150 | 130 | 134 | fits | 71,708 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.4.if0` | 1,977,986 | 19.780 | 130 | 134 | fits | 69,826 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.4.if0` | 1,995,076 | 19.951 | 130 | 134 | fits | 69,826 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.5.if0` | 2,009,681 | 20.097 | 130 | 134 | fits | 69,826 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.5.if0` | 2,026,208 | 20.262 | 130 | 134 | fits | 69,826 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.6.if0` | 2,168,754 | 21.688 | 130 | 134 | fits | 69,688 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.6.if0` | 2,185,844 | 21.858 | 130 | 134 | fits | 69,688 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.7.if0` | 254,811 | 2.548 | 130 | 134 | fits | 105,061 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.7.if0` | 275,277 | 2.753 | 130 | 134 | fits | 105,061 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.8.if0` | 2,200,442 | 22.004 | 130 | 134 | fits | 69,688 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.8.if0` | 2,216,969 | 22.170 | 130 | 134 | fits | 69,688 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-0.notices.27.9.0.if0` | 2,378,765 | 23.788 | 130 | 134 | fits | 65,150 | 202 | 0.148 |
| a queued notice, from its port's answer | `notice-burst-0.notices.28.9.0.if0` | 2,391,253 | 23.913 | 130 | 134 | fits | 65,150 | 202 | 0.148 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.9.0.if0` | 2,407,931 | 24.079 | 130 | 134 | fits | 65,150 | 202 | 0.148 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.36.0.if0` | 2,424,405 | 24.244 | 130 | 134 | fits | 65,150 | 202 | 0.148 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-0.held.adp.if0` | 485,089 | 4.851 | 20 | 200 | fits | 151,078 | 151 | 0.406 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-0.held.acmp.if0` | 597,730 | 5.977 | 20 | 20 | fits | 132,909 | 61 | 0.645 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-0.held.aecp.if0` | 444,617 | 4.446 | 20 | 24 | fits | 151,078 | 151 | 0.406 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-0.held.maap.if0` | 425,346 | 4.253 | 20 | 50 | fits | 151,078 | 151 | 0.406 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-0.held.srp.if0` | 780,019 | 7.800 | 20 | 20 | fits | 111,417 | 54 | 0.536 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.0.if0` | 395,631 | 3.956 | 130 | 134 | fits | 101,495 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.0.if0` | 413,023 | 4.130 | 130 | 134 | fits | 101,495 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.1.if0` | 475,667 | 4.757 | 130 | 134 | fits | 74,525 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.1.if0` | 492,570 | 4.926 | 130 | 134 | fits | 74,525 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.2.if0` | 603,270 | 6.033 | 130 | 134 | fits | 92,365 | 213 | 0.189 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.2.if0` | 620,741 | 6.207 | 130 | 134 | fits | 92,365 | 213 | 0.189 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.3.if0` | 636,337 | 6.363 | 130 | 134 | fits | 92,365 | 213 | 0.189 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.3.if0` | 653,193 | 6.532 | 130 | 134 | fits | 92,365 | 213 | 0.189 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.4.if0` | 1,584,339 | 15.843 | 130 | 134 | fits | 75,400 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.4.if0` | 1,602,158 | 16.022 | 130 | 134 | fits | 75,400 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.5.if0` | 1,617,936 | 16.179 | 130 | 134 | fits | 75,400 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.5.if0` | 1,634,648 | 16.346 | 130 | 134 | fits | 75,400 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.6.if0` | 509,156 | 5.092 | 130 | 134 | fits | 74,525 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.6.if0` | 526,857 | 5.269 | 130 | 134 | fits | 74,525 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.7.if0` | 675,805 | 6.758 | 130 | 134 | fits | 73,269 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.7.if0` | 693,441 | 6.934 | 130 | 134 | fits | 73,269 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.8.if0` | 1,704,712 | 17.047 | 130 | 134 | fits | 71,027 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.8.if0` | 1,721,881 | 17.219 | 130 | 134 | fits | 71,027 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.0.if0` | 1,736,488 | 17.365 | 130 | 134 | fits | 71,027 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.0.if0` | 1,753,015 | 17.530 | 130 | 134 | fits | 71,027 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.1.if0` | 203,850 | 2.038 | 130 | 134 | fits | 108,136 | 213 | 0.206 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.1.if0` | 223,860 | 2.239 | 130 | 134 | fits | 108,136 | 213 | 0.206 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.2.if0` | 430,110 | 4.301 | 130 | 134 | fits | 101,495 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.2.if0` | 449,097 | 4.491 | 130 | 134 | fits | 101,495 | 211 | 0.194 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.3.if0` | 241,619 | 2.416 | 130 | 134 | fits | 108,136 | 213 | 0.206 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.3.if0` | 260,924 | 2.609 | 130 | 134 | fits | 108,136 | 213 | 0.206 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.4.if0` | 709,286 | 7.093 | 130 | 134 | fits | 73,269 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.4.if0` | 726,816 | 7.268 | 130 | 134 | fits | 73,269 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.5.if0` | 1,914,340 | 19.143 | 130 | 134 | fits | 69,659 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.5.if0` | 1,931,430 | 19.314 | 130 | 134 | fits | 69,659 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.6.if0` | 1,946,051 | 19.461 | 130 | 134 | fits | 69,659 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.6.if0` | 1,962,578 | 19.626 | 130 | 134 | fits | 69,659 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.7.if0` | 2,103,053 | 21.031 | 130 | 134 | fits | 69,462 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.7.if0` | 2,120,143 | 21.201 | 130 | 134 | fits | 69,462 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.8.if0` | 2,134,820 | 21.348 | 130 | 134 | fits | 69,462 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.8.if0` | 2,151,347 | 21.513 | 130 | 134 | fits | 69,462 | 203 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.27.9.0.if0` | 2,310,577 | 23.106 | 130 | 134 | fits | 31,871 | 101 | 0.265 |
| a queued notice, from its port's answer | `notice-burst-1.notices.28.9.0.if0` | 2,323,063 | 23.231 | 130 | 134 | fits | 31,871 | 101 | 0.265 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.9.0.if0` | 293,061 | 2.931 | 130 | 134 | fits | 50,649 | 103 | 0.073 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.36.0.if0` | 313,787 | 3.138 | 130 | 134 | fits | 50,649 | 103 | 0.073 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-1.held.adp.if0` | 615,984 | 6.160 | 20 | 200 | fits | 150,297 | 212 | 0.198 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-1.held.acmp.if0` | 595,716 | 5.957 | 20 | 20 | fits | 150,297 | 212 | 0.198 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-1.held.aecp.if0` | 425,215 | 4.252 | 20 | 24 | fits | 153,873 | 155 | 0.425 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-1.held.maap.if0` | 556,241 | 5.562 | 20 | 50 | fits | 150,297 | 212 | 0.198 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-1.held.srp.if0` | 898,756 | 8.988 | 20 | 20 | fits | 102,167 | 50 | 0.546 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.0.if0` | 442,014 | 4.420 | 130 | 134 | fits | 99,731 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.0.if0` | 459,279 | 4.593 | 130 | 134 | fits | 99,731 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.1.if0` | 520,579 | 5.206 | 130 | 134 | fits | 72,053 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.1.if0` | 537,705 | 5.377 | 130 | 134 | fits | 72,053 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.2.if0` | 553,288 | 5.533 | 130 | 134 | fits | 72,053 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.2.if0` | 570,223 | 5.702 | 130 | 134 | fits | 72,053 | 205 | 0.120 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.3.if0` | 1,439,127 | 14.391 | 130 | 134 | fits | 76,096 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.3.if0` | 1,456,920 | 14.569 | 130 | 134 | fits | 76,096 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.4.if0` | 1,472,986 | 14.730 | 130 | 134 | fits | 76,096 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.4.if0` | 1,489,986 | 14.900 | 130 | 134 | fits | 76,096 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.5.if0` | 1,580,584 | 15.806 | 130 | 134 | fits | 72,415 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.5.if0` | 1,597,784 | 15.978 | 130 | 134 | fits | 72,415 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.6.if0` | 1,613,426 | 16.134 | 130 | 134 | fits | 72,415 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.6.if0` | 1,630,138 | 16.301 | 130 | 134 | fits | 72,415 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.7.if0` | 1,775,960 | 17.760 | 130 | 134 | fits | 72,105 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.7.if0` | 1,793,160 | 17.932 | 130 | 134 | fits | 72,105 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.8.if0` | 1,809,011 | 18.090 | 130 | 134 | fits | 72,105 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.8.if0` | 1,825,644 | 18.256 | 130 | 134 | fits | 72,105 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.0.if0` | 1,969,543 | 19.695 | 130 | 134 | fits | 69,808 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.0.if0` | 1,986,585 | 19.866 | 130 | 134 | fits | 69,808 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.1.if0` | 308,866 | 3.089 | 130 | 134 | fits | 81,006 | 205 | 0.099 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.1.if0` | 328,328 | 3.283 | 130 | 134 | fits | 81,006 | 205 | 0.099 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.2.if0` | 222,465 | 2.225 | 130 | 134 | fits | 108,654 | 211 | 0.188 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.2.if0` | 242,943 | 2.429 | 130 | 134 | fits | 108,654 | 211 | 0.188 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.3.if0` | 260,782 | 2.608 | 130 | 134 | fits | 108,654 | 211 | 0.188 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.3.if0` | 280,087 | 2.801 | 130 | 134 | fits | 108,654 | 211 | 0.188 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.4.if0` | 345,325 | 3.453 | 130 | 134 | fits | 81,006 | 205 | 0.099 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.4.if0` | 364,162 | 3.642 | 130 | 134 | fits | 81,006 | 205 | 0.099 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.5.if0` | 476,013 | 4.760 | 130 | 134 | fits | 99,731 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.5.if0` | 494,619 | 4.946 | 130 | 134 | fits | 99,731 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.6.if0` | 2,001,573 | 20.016 | 130 | 134 | fits | 69,808 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.6.if0` | 2,018,100 | 20.181 | 130 | 134 | fits | 69,808 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.7.if0` | 2,179,581 | 21.796 | 130 | 134 | fits | 69,617 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.7.if0` | 2,196,623 | 21.966 | 130 | 134 | fits | 69,617 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.8.if0` | 2,211,230 | 22.112 | 130 | 134 | fits | 69,617 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.8.if0` | 2,227,757 | 22.278 | 130 | 134 | fits | 69,617 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-2.notices.27.9.0.if0` | 2,370,525 | 23.705 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-2.notices.28.9.0.if0` | 2,382,965 | 23.830 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.9.0.if0` | 2,399,643 | 23.996 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.36.0.if0` | 2,416,108 | 24.161 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-2.held.adp.if0` | 491,849 | 4.918 | 20 | 200 | fits | 150,267 | 152 | 0.406 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-2.held.acmp.if0` | 604,593 | 6.046 | 20 | 20 | fits | 133,012 | 61 | 0.646 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-2.held.aecp.if0` | 451,377 | 4.514 | 20 | 24 | fits | 150,267 | 152 | 0.406 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-2.held.maap.if0` | 432,106 | 4.321 | 20 | 50 | fits | 150,267 | 152 | 0.406 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-2.held.srp.if0` | 786,714 | 7.867 | 20 | 20 | fits | 111,271 | 54 | 0.536 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.0.if0` | 568,962 | 5.690 | 130 | 134 | fits | 96,083 | 211 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.0.if0` | 586,450 | 5.864 | 130 | 134 | fits | 96,083 | 211 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.1.if0` | 602,124 | 6.021 | 130 | 134 | fits | 96,083 | 211 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.1.if0` | 618,980 | 6.190 | 130 | 134 | fits | 96,083 | 211 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.2.if0` | 644,033 | 6.440 | 130 | 134 | fits | 72,767 | 205 | 0.116 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.2.if0` | 661,238 | 6.612 | 130 | 134 | fits | 72,767 | 205 | 0.116 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.3.if0` | 1,558,153 | 15.582 | 130 | 134 | fits | 75,530 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.3.if0` | 1,575,798 | 15.758 | 130 | 134 | fits | 75,530 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.4.if0` | 1,591,785 | 15.918 | 130 | 134 | fits | 75,530 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.4.if0` | 1,608,641 | 16.086 | 130 | 134 | fits | 75,530 | 203 | 0.225 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.5.if0` | 677,280 | 6.773 | 130 | 134 | fits | 72,767 | 205 | 0.116 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.5.if0` | 694,598 | 6.946 | 130 | 134 | fits | 72,767 | 205 | 0.116 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.6.if0` | 1,698,502 | 16.985 | 130 | 134 | fits | 72,156 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.6.if0` | 1,715,702 | 17.157 | 130 | 134 | fits | 72,156 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.7.if0` | 1,731,360 | 17.314 | 130 | 134 | fits | 72,156 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.7.if0` | 1,748,072 | 17.481 | 130 | 134 | fits | 72,156 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.8.if0` | 202,703 | 2.027 | 130 | 134 | fits | 81,857 | 205 | 0.146 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.8.if0` | 221,694 | 2.217 | 130 | 134 | fits | 81,857 | 205 | 0.146 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.0.if0` | 237,948 | 2.379 | 130 | 134 | fits | 81,857 | 205 | 0.146 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.0.if0` | 256,353 | 2.564 | 130 | 134 | fits | 81,857 | 205 | 0.146 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.1.if0` | 355,032 | 3.550 | 130 | 134 | fits | 103,609 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.1.if0` | 374,378 | 3.744 | 130 | 134 | fits | 103,609 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.2.if0` | 1,911,569 | 19.116 | 130 | 134 | fits | 70,744 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.2.if0` | 1,928,988 | 19.290 | 130 | 134 | fits | 70,744 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.3.if0` | 437,593 | 4.376 | 130 | 134 | fits | 79,641 | 205 | 0.098 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.3.if0` | 456,680 | 4.567 | 130 | 134 | fits | 79,641 | 205 | 0.098 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.4.if0` | 391,913 | 3.919 | 130 | 134 | fits | 103,609 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.4.if0` | 411,066 | 4.111 | 130 | 134 | fits | 103,609 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.5.if0` | 473,765 | 4.738 | 130 | 134 | fits | 79,641 | 205 | 0.098 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.5.if0` | 492,608 | 4.926 | 130 | 134 | fits | 79,641 | 205 | 0.098 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.6.if0` | 1,943,976 | 19.440 | 130 | 134 | fits | 70,744 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.6.if0` | 1,960,503 | 19.605 | 130 | 134 | fits | 70,744 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.7.if0` | 2,103,177 | 21.032 | 130 | 134 | fits | 69,691 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.7.if0` | 2,120,219 | 21.202 | 130 | 134 | fits | 69,691 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.8.if0` | 2,134,826 | 21.348 | 130 | 134 | fits | 69,691 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.8.if0` | 2,151,353 | 21.514 | 130 | 134 | fits | 69,691 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-3.notices.27.9.0.if0` | 2,294,279 | 22.943 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-3.notices.28.9.0.if0` | 2,306,719 | 23.067 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.9.0.if0` | 2,323,397 | 23.234 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.36.0.if0` | 2,339,862 | 23.399 | 130 | 134 | fits | 65,005 | 202 | 0.145 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-3.held.adp.if0` | 593,954 | 5.940 | 20 | 200 | fits | 151,570 | 218 | 0.195 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-3.held.acmp.if0` | 573,686 | 5.737 | 20 | 20 | fits | 151,570 | 218 | 0.195 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-3.held.aecp.if0` | 401,912 | 4.019 | 20 | 24 | fits | 154,776 | 151 | 0.428 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-3.held.maap.if0` | 534,211 | 5.342 | 20 | 50 | fits | 151,570 | 218 | 0.195 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-3.held.srp.if0` | 878,001 | 8.780 | 20 | 20 | fits | 102,668 | 50 | 0.546 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.0.if0` | 1,453,923 | 14.539 | 130 | 134 | fits | 75,919 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.0.if0` | 1,471,842 | 14.718 | 130 | 134 | fits | 75,919 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.1.if0` | 1,487,599 | 14.876 | 130 | 134 | fits | 75,919 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.1.if0` | 1,504,455 | 15.045 | 130 | 134 | fits | 75,919 | 203 | 0.223 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.2.if0` | 1,575,512 | 15.755 | 130 | 134 | fits | 72,570 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.2.if0` | 1,592,791 | 15.928 | 130 | 134 | fits | 72,570 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.3.if0` | 1,608,486 | 16.085 | 130 | 134 | fits | 72,570 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.3.if0` | 1,625,198 | 16.252 | 130 | 134 | fits | 72,570 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.4.if0` | 222,352 | 2.224 | 130 | 134 | fits | 107,607 | 211 | 0.195 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.4.if0` | 240,892 | 2.409 | 130 | 134 | fits | 107,607 | 211 | 0.195 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.5.if0` | 1,770,961 | 17.710 | 130 | 134 | fits | 72,063 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.5.if0` | 1,788,161 | 17.882 | 130 | 134 | fits | 72,063 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.6.if0` | 1,803,803 | 18.038 | 130 | 134 | fits | 72,063 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.6.if0` | 1,820,515 | 18.205 | 130 | 134 | fits | 72,063 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.7.if0` | 1,965,282 | 19.653 | 130 | 134 | fits | 71,651 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.7.if0` | 1,982,403 | 19.824 | 130 | 134 | fits | 71,651 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.8.if0` | 1,998,110 | 19.981 | 130 | 134 | fits | 71,651 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.8.if0` | 2,014,664 | 20.147 | 130 | 134 | fits | 71,651 | 203 | 0.176 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.0.if0` | 526,759 | 5.268 | 130 | 134 | fits | 78,558 | 205 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.0.if0` | 545,627 | 5.456 | 130 | 134 | fits | 78,558 | 205 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.1.if0` | 562,645 | 5.626 | 130 | 134 | fits | 78,558 | 205 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.1.if0` | 581,624 | 5.816 | 130 | 134 | fits | 78,558 | 205 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.2.if0` | 308,956 | 3.090 | 130 | 134 | fits | 82,507 | 205 | 0.102 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.2.if0` | 328,576 | 3.286 | 130 | 134 | fits | 82,507 | 205 | 0.102 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.3.if0` | 346,050 | 3.461 | 130 | 134 | fits | 82,507 | 205 | 0.102 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.3.if0` | 365,124 | 3.651 | 130 | 134 | fits | 82,507 | 205 | 0.102 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.4.if0` | 444,840 | 4.448 | 130 | 134 | fits | 103,597 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.4.if0` | 464,429 | 4.644 | 130 | 134 | fits | 103,597 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.5.if0` | 481,598 | 4.816 | 130 | 134 | fits | 103,597 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.5.if0` | 500,672 | 5.007 | 130 | 134 | fits | 103,597 | 211 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.6.if0` | 2,176,524 | 21.765 | 130 | 134 | fits | 69,626 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.6.if0` | 2,193,566 | 21.936 | 130 | 134 | fits | 69,626 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.7.if0` | 259,459 | 2.595 | 130 | 134 | fits | 107,607 | 211 | 0.195 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.7.if0` | 279,925 | 2.799 | 130 | 134 | fits | 107,607 | 211 | 0.195 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.8.if0` | 2,208,164 | 22.082 | 130 | 134 | fits | 69,626 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.8.if0` | 2,224,691 | 22.247 | 130 | 134 | fits | 69,626 | 203 | 0.163 |
| a queued notice, from its port's answer | `notice-burst-4.notices.27.9.0.if0` | 2,372,162 | 23.722 | 130 | 134 | fits | 64,972 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-4.notices.28.9.0.if0` | 2,384,569 | 23.846 | 130 | 134 | fits | 64,972 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.9.0.if0` | 2,401,247 | 24.012 | 130 | 134 | fits | 64,972 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.36.0.if0` | 2,417,712 | 24.177 | 130 | 134 | fits | 64,972 | 202 | 0.144 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-4.held.adp.if0` | 509,300 | 5.093 | 20 | 200 | fits | 152,221 | 218 | 0.206 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-4.held.acmp.if0` | 621,661 | 6.217 | 20 | 20 | fits | 132,629 | 61 | 0.641 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-4.held.aecp.if0` | 316,607 | 3.166 | 20 | 24 | fits | 152,119 | 153 | 0.434 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-4.held.maap.if0` | 449,557 | 4.496 | 20 | 50 | fits | 152,221 | 218 | 0.206 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-4.held.srp.if0` | 803,623 | 8.036 | 20 | 20 | fits | 111,286 | 54 | 0.533 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.0.if0` | 1,464,564 | 14.646 | 130 | 134 | fits | 75,833 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.0.if0` | 1,482,483 | 14.825 | 130 | 134 | fits | 75,833 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.1.if0` | 1,498,240 | 14.982 | 130 | 134 | fits | 75,833 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.1.if0` | 1,515,096 | 15.151 | 130 | 134 | fits | 75,833 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.2.if0` | 1,624,204 | 16.242 | 130 | 134 | fits | 73,261 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.2.if0` | 1,641,627 | 16.416 | 130 | 134 | fits | 73,261 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.3.if0` | 220,203 | 2.202 | 130 | 134 | fits | 103,423 | 213 | 0.217 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.3.if0` | 238,298 | 2.383 | 130 | 134 | fits | 103,423 | 213 | 0.217 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.4.if0` | 522,478 | 5.225 | 130 | 134 | fits | 77,122 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.4.if0` | 540,543 | 5.405 | 130 | 134 | fits | 77,122 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.5.if0` | 557,069 | 5.571 | 130 | 134 | fits | 77,122 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.5.if0` | 574,618 | 5.746 | 130 | 134 | fits | 77,122 | 203 | 0.174 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.6.if0` | 1,657,736 | 16.577 | 130 | 134 | fits | 73,261 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.6.if0` | 1,674,448 | 16.744 | 130 | 134 | fits | 73,261 | 203 | 0.178 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.7.if0` | 1,819,808 | 18.198 | 130 | 134 | fits | 72,151 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.7.if0` | 1,837,008 | 18.370 | 130 | 134 | fits | 72,151 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.8.if0` | 255,711 | 2.557 | 130 | 134 | fits | 103,423 | 213 | 0.217 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.8.if0` | 273,882 | 2.739 | 130 | 134 | fits | 103,423 | 213 | 0.217 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.0.if0` | 409,232 | 4.092 | 130 | 134 | fits | 102,445 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.0.if0` | 427,970 | 4.280 | 130 | 134 | fits | 102,445 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.1.if0` | 1,852,000 | 18.520 | 130 | 134 | fits | 72,151 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.1.if0` | 1,868,987 | 18.690 | 130 | 134 | fits | 72,151 | 203 | 0.171 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.2.if0` | 445,128 | 4.451 | 130 | 134 | fits | 102,445 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.2.if0` | 464,042 | 4.640 | 130 | 134 | fits | 102,445 | 211 | 0.183 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.3.if0` | 2,012,815 | 20.128 | 130 | 134 | fits | 70,053 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.3.if0` | 2,029,936 | 20.299 | 130 | 134 | fits | 70,053 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.4.if0` | 2,044,780 | 20.448 | 130 | 134 | fits | 70,053 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.4.if0` | 2,061,307 | 20.613 | 130 | 134 | fits | 70,053 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.5.if0` | 2,221,751 | 22.218 | 130 | 134 | fits | 69,560 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.5.if0` | 2,238,793 | 22.388 | 130 | 134 | fits | 69,560 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.6.if0` | 2,253,414 | 22.534 | 130 | 134 | fits | 69,560 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.6.if0` | 2,269,941 | 22.699 | 130 | 134 | fits | 69,560 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.7.if0` | 2,418,703 | 24.187 | 130 | 134 | fits | 69,813 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.7.if0` | 2,435,824 | 24.358 | 130 | 134 | fits | 69,813 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.8.if0` | 2,450,510 | 24.505 | 130 | 134 | fits | 69,813 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.8.if0` | 2,467,037 | 24.670 | 130 | 134 | fits | 69,813 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-5.notices.27.9.0.if0` | 2,622,639 | 26.226 | 130 | 134 | fits | 31,438 | 101 | 0.251 |
| a queued notice, from its port's answer | `notice-burst-5.notices.28.9.0.if0` | 2,634,998 | 26.350 | 130 | 134 | fits | 31,438 | 101 | 0.251 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.9.0.if0` | 306,038 | 3.060 | 130 | 134 | fits | 51,198 | 103 | 0.078 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.36.0.if0` | 326,913 | 3.269 | 130 | 134 | fits | 51,198 | 103 | 0.078 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-5.held.adp.if0` | 166,656 | 1.667 | 20 | 200 | fits | 152,734 | 225 | 0.252 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-5.held.acmp.if0` | 586,795 | 5.868 | 20 | 20 | fits | 132,879 | 61 | 0.646 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-5.held.aecp.if0` | 433,712 | 4.337 | 20 | 24 | fits | 150,165 | 148 | 0.406 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-5.held.maap.if0` | 414,441 | 4.144 | 20 | 50 | fits | 150,165 | 148 | 0.406 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-5.held.srp.if0` | 769,068 | 7.691 | 20 | 20 | fits | 111,463 | 54 | 0.537 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.0.if0` | 1,413,206 | 14.132 | 130 | 134 | fits | 75,946 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.0.if0` | 1,431,125 | 14.311 | 130 | 134 | fits | 75,946 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.1.if0` | 1,446,882 | 14.469 | 130 | 134 | fits | 75,946 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.1.if0` | 1,463,738 | 14.637 | 130 | 134 | fits | 75,946 | 203 | 0.224 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.2.if0` | 1,573,523 | 15.735 | 130 | 134 | fits | 72,757 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.2.if0` | 1,590,802 | 15.908 | 130 | 134 | fits | 72,757 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.3.if0` | 278,102 | 2.781 | 130 | 134 | fits | 80,090 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.3.if0` | 296,277 | 2.963 | 130 | 134 | fits | 80,090 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.4.if0` | 312,916 | 3.129 | 130 | 134 | fits | 80,090 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.4.if0` | 330,386 | 3.304 | 130 | 134 | fits | 80,090 | 203 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.5.if0` | 166,265 | 1.663 | 130 | 134 | fits | 102,478 | 213 | 0.216 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.5.if0` | 184,822 | 1.848 | 130 | 134 | fits | 102,478 | 213 | 0.216 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.6.if0` | 201,535 | 2.015 | 130 | 134 | fits | 102,478 | 213 | 0.216 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.6.if0` | 219,353 | 2.194 | 130 | 134 | fits | 102,478 | 213 | 0.216 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.7.if0` | 407,742 | 4.077 | 130 | 134 | fits | 98,630 | 211 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.7.if0` | 425,556 | 4.256 | 130 | 134 | fits | 98,630 | 211 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.8.if0` | 441,908 | 4.419 | 130 | 134 | fits | 98,630 | 211 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.8.if0` | 459,155 | 4.592 | 130 | 134 | fits | 98,630 | 211 | 0.186 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.0.if0` | 484,706 | 4.847 | 130 | 134 | fits | 75,031 | 205 | 0.104 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.0.if0` | 502,446 | 5.024 | 130 | 134 | fits | 75,031 | 205 | 0.104 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.1.if0` | 1,605,827 | 16.058 | 130 | 134 | fits | 72,757 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.1.if0` | 1,622,814 | 16.228 | 130 | 134 | fits | 72,757 | 203 | 0.172 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.2.if0` | 518,825 | 5.188 | 130 | 134 | fits | 75,031 | 205 | 0.104 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.2.if0` | 537,038 | 5.370 | 130 | 134 | fits | 75,031 | 205 | 0.104 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.3.if0` | 1,768,487 | 17.685 | 130 | 134 | fits | 70,372 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.3.if0` | 1,785,608 | 17.856 | 130 | 134 | fits | 70,372 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.4.if0` | 1,800,452 | 18.005 | 130 | 134 | fits | 70,372 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.4.if0` | 1,817,058 | 18.171 | 130 | 134 | fits | 70,372 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.5.if0` | 1,960,913 | 19.609 | 130 | 134 | fits | 69,797 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.5.if0` | 1,977,955 | 19.780 | 130 | 134 | fits | 69,797 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.6.if0` | 1,992,576 | 19.926 | 130 | 134 | fits | 69,797 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.6.if0` | 2,009,103 | 20.091 | 130 | 134 | fits | 69,797 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.7.if0` | 2,170,459 | 21.705 | 130 | 134 | fits | 69,482 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.7.if0` | 2,187,501 | 21.875 | 130 | 134 | fits | 69,482 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.8.if0` | 2,202,108 | 22.021 | 130 | 134 | fits | 69,482 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.8.if0` | 2,218,635 | 22.186 | 130 | 134 | fits | 69,482 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-6.notices.27.9.0.if0` | 2,361,541 | 23.615 | 130 | 134 | fits | 64,981 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-6.notices.28.9.0.if0` | 2,373,948 | 23.739 | 130 | 134 | fits | 64,981 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.9.0.if0` | 2,390,626 | 23.906 | 130 | 134 | fits | 64,981 | 202 | 0.144 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.36.0.if0` | 2,407,100 | 24.071 | 130 | 134 | fits | 64,981 | 202 | 0.144 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-6.held.adp.if0` | 159,698 | 1.597 | 20 | 200 | fits | 157,976 | 222 | 0.305 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-6.held.acmp.if0` | 586,126 | 5.861 | 20 | 20 | fits | 133,305 | 61 | 0.650 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-6.held.aecp.if0` | 432,617 | 4.326 | 20 | 24 | fits | 157,489 | 167 | 0.393 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-6.held.maap.if0` | 413,346 | 4.133 | 20 | 50 | fits | 157,489 | 167 | 0.393 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-6.held.srp.if0` | 768,317 | 7.683 | 20 | 20 | fits | 111,387 | 54 | 0.538 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.0.if0` | 1,588,556 | 15.886 | 130 | 134 | fits | 75,224 | 203 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.0.if0` | 1,606,390 | 16.064 | 130 | 134 | fits | 75,224 | 203 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.1.if0` | 219,521 | 2.195 | 130 | 134 | fits | 99,459 | 213 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.1.if0` | 237,141 | 2.371 | 130 | 134 | fits | 99,459 | 213 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.2.if0` | 252,880 | 2.529 | 130 | 134 | fits | 99,459 | 213 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.2.if0` | 269,823 | 2.698 | 130 | 134 | fits | 99,459 | 213 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.3.if0` | 404,037 | 4.040 | 130 | 134 | fits | 95,384 | 213 | 0.197 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.3.if0` | 421,691 | 4.217 | 130 | 134 | fits | 95,384 | 213 | 0.197 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.4.if0` | 437,809 | 4.378 | 130 | 134 | fits | 95,384 | 213 | 0.197 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.4.if0` | 454,817 | 4.548 | 130 | 134 | fits | 95,384 | 213 | 0.197 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.5.if0` | 606,488 | 6.065 | 130 | 134 | fits | 93,156 | 213 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.5.if0` | 624,063 | 6.241 | 130 | 134 | fits | 93,156 | 213 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.6.if0` | 479,001 | 4.790 | 130 | 134 | fits | 75,177 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.6.if0` | 496,445 | 4.964 | 130 | 134 | fits | 75,177 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.7.if0` | 512,566 | 5.126 | 130 | 134 | fits | 75,177 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.7.if0` | 529,884 | 5.299 | 130 | 134 | fits | 75,177 | 203 | 0.115 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.8.if0` | 640,255 | 6.403 | 130 | 134 | fits | 93,156 | 213 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.8.if0` | 657,263 | 6.573 | 130 | 134 | fits | 93,156 | 213 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.0.if0` | 678,478 | 6.785 | 130 | 134 | fits | 71,671 | 203 | 0.107 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.0.if0` | 695,804 | 6.958 | 130 | 134 | fits | 71,671 | 203 | 0.107 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.1.if0` | 711,439 | 7.114 | 130 | 134 | fits | 71,671 | 203 | 0.107 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.1.if0` | 728,657 | 7.287 | 130 | 134 | fits | 71,671 | 203 | 0.107 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.2.if0` | 1,621,518 | 16.215 | 130 | 134 | fits | 75,224 | 203 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.2.if0` | 1,638,505 | 16.385 | 130 | 134 | fits | 75,224 | 203 | 0.218 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.3.if0` | 1,708,056 | 17.081 | 130 | 134 | fits | 70,125 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.3.if0` | 1,725,177 | 17.252 | 130 | 134 | fits | 70,125 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.4.if0` | 1,740,021 | 17.400 | 130 | 134 | fits | 70,125 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.4.if0` | 1,756,548 | 17.565 | 130 | 134 | fits | 70,125 | 203 | 0.165 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.5.if0` | 1,916,945 | 19.169 | 130 | 134 | fits | 69,551 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.5.if0` | 1,933,987 | 19.340 | 130 | 134 | fits | 69,551 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.6.if0` | 1,948,608 | 19.486 | 130 | 134 | fits | 69,551 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.6.if0` | 1,965,135 | 19.651 | 130 | 134 | fits | 69,551 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.7.if0` | 2,105,687 | 21.057 | 130 | 134 | fits | 69,265 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.7.if0` | 2,122,729 | 21.227 | 130 | 134 | fits | 69,265 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.8.if0` | 2,137,336 | 21.373 | 130 | 134 | fits | 69,265 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.8.if0` | 2,153,863 | 21.539 | 130 | 134 | fits | 69,265 | 203 | 0.164 |
| a queued notice, from its port's answer | `notice-burst-7.notices.27.9.0.if0` | 2,313,180 | 23.132 | 130 | 134 | fits | 31,735 | 101 | 0.260 |
| a queued notice, from its port's answer | `notice-burst-7.notices.28.9.0.if0` | 2,325,618 | 23.256 | 130 | 134 | fits | 31,735 | 101 | 0.260 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.9.0.if0` | 301,789 | 3.018 | 130 | 134 | fits | 51,277 | 103 | 0.078 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.36.0.if0` | 322,664 | 3.227 | 130 | 134 | fits | 51,277 | 103 | 0.078 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-7.held.adp.if0` | 617,309 | 6.173 | 20 | 200 | fits | 151,068 | 203 | 0.197 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-7.held.acmp.if0` | 597,041 | 5.970 | 20 | 20 | fits | 151,068 | 203 | 0.197 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-7.held.aecp.if0` | 425,769 | 4.258 | 20 | 24 | fits | 156,316 | 170 | 0.428 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-7.held.maap.if0` | 557,566 | 5.576 | 20 | 50 | fits | 151,068 | 203 | 0.197 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-7.held.srp.if0` | 899,790 | 8.998 | 20 | 20 | fits | 102,100 | 50 | 0.547 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
