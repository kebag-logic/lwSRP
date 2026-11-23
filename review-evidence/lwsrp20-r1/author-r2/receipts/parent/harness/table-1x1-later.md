### 1x1

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

0 of 7 paths and 0 of 56 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| ACMP record, every channel at its refill rate, the longest | 0 | `notice-retried-4.held.acmp.if0` (notice-retried-4) | 4.215 | fits | 11 acmp | 8 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `notice-retried-1.held.adp.if0` (notice-retried-1) | 1.594 | fits | 7 adp | 8 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `notice-retried-4.held.aecp.if0` (notice-retried-4) | 4.013 | fits | 15 aecp | 8 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `notice-retried-5.held.maap.if0` (notice-retried-5) | 3.779 | fits | 6 maap | 8 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `notice-retried-3.held.srp.if0` (notice-retried-3) | 8.173 | fits | 31 srp | 8 | 0 |
| an MRPDU its periodic timer owes, the longest | 0 | `notice-retried-0.mrpdu.periodic.if0` (notice-retried-0) | 0.938 | fits | 0 srp | 8 | 0 |
| a retried notice, from its port's answer (THE RETRY) | 0 | `notice-retried-5.stream_info.if0` (notice-retried-5) | 8.236 (8.351) | fits | 2 events | 8 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| notice-retried-0 | 2075 | 0 | 154,442 (1.544) | fits |
| notice-retried-1 | 2075 | 0 | 154,661 (1.547) | fits |
| notice-retried-2 | 2075 | 0 | 154,544 (1.545) | fits |
| notice-retried-3 | 2074 | 0 | 155,705 (1.557) | fits |
| notice-retried-4 | 2073 | 0 | 156,306 (1.563) | fits |
| notice-retried-5 | 2073 | 0 | 154,938 (1.549) | fits |
| notice-retried-6 | 2074 | 0 | 154,468 (1.545) | fits |
| notice-retried-7 | 2073 | 0 | 154,802 (1.548) | fits |

Retried notices, from the port's answer to the last recipient's commit (notice_window.py; ctrl_loop.h, THE RETRY):

| Group | ms | Bound ms | Recipients | Events held at the answer | Verdict |
|---|---:|---:|---:|---:|---|
| notice-retried-0 | 7.975 | 20 | 16 | 2 | within |
| notice-retried-1 | 8.138 | 20 | 16 | 1 | within |
| notice-retried-2 | 8.060 | 20 | 16 | 1 | within |
| notice-retried-3 | 8.019 | 20 | 16 | 1 | within |
| notice-retried-4 | 8.235 | 20 | 16 | 2 | within |
| notice-retried-5 | 8.236 | 20 | 16 | 2 | within |
| notice-retried-6 | 8.177 | 20 | 16 | 2 | within |
| notice-retried-7 | 8.176 | 20 | 16 | 2 | within |

Latest: 8.236 ms, notice-retried-5.

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| notice-retried-0 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-1 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-2 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-3 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-4 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-5 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-6 | 402 | 94,086 (0.941) | 77,958 (0.780) |
| notice-retried-7 | 402 | 94,086 (0.941) | 77,958 (0.780) |

Longest pass that carries a step: 94,086 CPU cycles (0.941 ms), notice-retried-0; longest step: 77,958 (0.780 ms), notice-retried-0.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-0.stream_info.if0` | 797,457 | 7.975 | 20 | 24 | fits | 24,591 | 52 | 0.445 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-0.held.adp.if0` | 152,899 | 1.529 | 20 | 200 | fits | 145,041 | 273 | 0.211 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-0.held.acmp.if0` | 408,533 | 4.085 | 20 | 20 | fits | 121,460 | 105 | 0.495 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-0.held.aecp.if0` | 388,329 | 3.883 | 20 | 24 | fits | 121,460 | 105 | 0.495 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-0.held.maap.if0` | 369,058 | 3.691 | 20 | 50 | fits | 121,460 | 105 | 0.495 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-0.held.srp.if0` | 817,051 | 8.171 | 20 | 20 | fits | 50,854 | 26 | 0.703 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-0.mrpdu.periodic.if0` | 93,823 | 0.938 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-1.stream_info.if0` | 813,803 | 8.138 | 20 | 24 | fits | 24,591 | 52 | 0.445 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-1.held.adp.if0` | 159,388 | 1.594 | 20 | 200 | fits | 148,113 | 291 | 0.207 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-1.held.acmp.if0` | 408,218 | 4.082 | 20 | 20 | fits | 114,437 | 84 | 0.488 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-1.held.aecp.if0` | 388,014 | 3.880 | 20 | 24 | fits | 114,437 | 84 | 0.488 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-1.held.maap.if0` | 99,645 | 0.996 | 20 | 50 | fits | 148,113 | 291 | 0.207 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-1.held.srp.if0` | 816,650 | 8.166 | 20 | 20 | fits | 50,917 | 26 | 0.703 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-1.mrpdu.periodic.if0` | 75,167 | 0.752 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-2.stream_info.if0` | 806,036 | 8.060 | 20 | 24 | fits | 24,511 | 52 | 0.442 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-2.held.adp.if0` | 159,244 | 1.592 | 20 | 200 | fits | 148,113 | 291 | 0.207 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-2.held.acmp.if0` | 407,957 | 4.080 | 20 | 20 | fits | 114,437 | 84 | 0.488 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-2.held.aecp.if0` | 387,753 | 3.878 | 20 | 24 | fits | 114,437 | 84 | 0.488 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-2.held.maap.if0` | 99,501 | 0.995 | 20 | 50 | fits | 148,113 | 291 | 0.207 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-2.held.srp.if0` | 816,121 | 8.161 | 20 | 20 | fits | 51,177 | 26 | 0.710 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-2.mrpdu.periodic.if0` | 74,570 | 0.746 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-3.stream_info.if0` | 801,943 | 8.019 | 20 | 24 | fits | 24,531 | 52 | 0.442 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-3.held.adp.if0` | 153,336 | 1.533 | 20 | 200 | fits | 145,939 | 276 | 0.231 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-3.held.acmp.if0` | 409,123 | 4.091 | 20 | 20 | fits | 121,458 | 105 | 0.495 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-3.held.aecp.if0` | 388,919 | 3.889 | 20 | 24 | fits | 121,458 | 105 | 0.495 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-3.held.maap.if0` | 369,648 | 3.696 | 20 | 50 | fits | 121,458 | 105 | 0.495 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-3.held.srp.if0` | 817,325 | 8.173 | 20 | 20 | fits | 56,118 | 39 | 0.716 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-3.mrpdu.periodic.if0` | 76,396 | 0.764 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-4.stream_info.if0` | 823,542 | 8.235 | 20 | 24 | fits | 24,591 | 52 | 0.445 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-4.held.adp.if0` | 158,300 | 1.583 | 20 | 200 | fits | 148,807 | 293 | 0.213 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-4.held.acmp.if0` | 421,472 | 4.215 | 20 | 20 | fits | 114,757 | 84 | 0.494 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-4.held.aecp.if0` | 401,268 | 4.013 | 20 | 24 | fits | 114,757 | 84 | 0.494 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-4.held.maap.if0` | 98,557 | 0.986 | 20 | 50 | fits | 148,807 | 293 | 0.213 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-4.held.srp.if0` | 810,888 | 8.109 | 20 | 20 | fits | 50,672 | 26 | 0.699 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-4.mrpdu.periodic.if0` | 76,172 | 0.762 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-5.stream_info.if0` | 823,554 | 8.236 | 20 | 24 | fits | 24,591 | 52 | 0.445 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-5.held.adp.if0` | 125,655 | 1.257 | 20 | 200 | fits | 125,849 | 166 | 0.165 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-5.held.acmp.if0` | 417,394 | 4.174 | 20 | 20 | fits | 125,178 | 118 | 0.510 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-5.held.aecp.if0` | 397,190 | 3.972 | 20 | 24 | fits | 125,178 | 118 | 0.510 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-5.held.maap.if0` | 377,919 | 3.779 | 20 | 50 | fits | 125,178 | 118 | 0.510 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-5.held.srp.if0` | 807,194 | 8.072 | 20 | 20 | fits | 50,692 | 26 | 0.699 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-5.mrpdu.periodic.if0` | 74,506 | 0.745 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-6.stream_info.if0` | 817,659 | 8.177 | 20 | 24 | fits | 25,559 | 52 | 0.485 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-6.held.adp.if0` | 126,310 | 1.263 | 20 | 200 | fits | 121,115 | 157 | 0.170 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-6.held.acmp.if0` | 407,938 | 4.079 | 20 | 20 | fits | 124,336 | 114 | 0.482 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-6.held.aecp.if0` | 387,734 | 3.877 | 20 | 24 | fits | 124,336 | 114 | 0.482 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-6.held.maap.if0` | 368,463 | 3.685 | 20 | 50 | fits | 124,336 | 114 | 0.482 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-6.held.srp.if0` | 811,790 | 8.118 | 20 | 20 | fits | 50,672 | 26 | 0.699 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-6.mrpdu.periodic.if0` | 78,708 | 0.787 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-7.stream_info.if0` | 817,582 | 8.176 | 20 | 24 | fits | 25,559 | 52 | 0.485 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-7.held.adp.if0` | 152,246 | 1.522 | 20 | 200 | fits | 144,690 | 275 | 0.234 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-7.held.acmp.if0` | 408,052 | 4.081 | 20 | 20 | fits | 121,272 | 107 | 0.490 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-7.held.aecp.if0` | 387,848 | 3.878 | 20 | 24 | fits | 121,272 | 107 | 0.490 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-7.held.maap.if0` | 368,577 | 3.686 | 20 | 50 | fits | 121,272 | 107 | 0.490 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-7.held.srp.if0` | 813,758 | 8.138 | 20 | 20 | fits | 50,760 | 26 | 0.700 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-7.mrpdu.periodic.if0` | 80,831 | 0.808 | 49 | 49 | fits | 0 | - | 0.000 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
