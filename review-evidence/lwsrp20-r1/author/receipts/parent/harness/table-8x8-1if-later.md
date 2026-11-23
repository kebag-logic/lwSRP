### 8x8-1if

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

0 of 7 paths and 0 of 56 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| ACMP record, every channel at its refill rate, the longest | 0 | `notice-retried-6.held.acmp.if0` (notice-retried-6) | 4.532 | fits | 11 acmp | 8 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `notice-retried-6.held.adp.if0` (notice-retried-6) | 1.718 | fits | 7 adp | 8 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `notice-retried-6.held.aecp.if0` (notice-retried-6) | 4.330 | fits | 15 aecp | 8 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `notice-retried-6.held.maap.if0` (notice-retried-6) | 4.138 | fits | 6 maap | 8 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `notice-retried-0.held.srp.if0` (notice-retried-0) | 7.410 | fits | 31 srp | 8 | 0 |
| an MRPDU its periodic timer owes, the longest | 0 | `notice-retried-7.mrpdu.periodic.if0` (notice-retried-7) | 0.950 | fits | 0 srp | 8 | 0 |
| a retried notice, from its port's answer (THE RETRY) | 0 | `notice-retried-7.stream_info.if0` (notice-retried-7) | 8.316 (8.402) | fits | 2 events | 8 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| notice-retried-0 | 1703 | 0 | 153,012 (1.530) | fits |
| notice-retried-1 | 1702 | 0 | 156,098 (1.561) | fits |
| notice-retried-2 | 1701 | 0 | 153,600 (1.536) | fits |
| notice-retried-3 | 1701 | 0 | 152,921 (1.529) | fits |
| notice-retried-4 | 1701 | 0 | 156,277 (1.563) | fits |
| notice-retried-5 | 1701 | 0 | 155,046 (1.550) | fits |
| notice-retried-6 | 1700 | 0 | 155,130 (1.551) | fits |
| notice-retried-7 | 1700 | 0 | 158,116 (1.581) | fits |

Retried notices, from the port's answer to the last recipient's commit (notice_window.py; ctrl_loop.h, THE RETRY):

| Group | ms | Bound ms | Recipients | Events held at the answer | Verdict |
|---|---:|---:|---:|---:|---|
| notice-retried-0 | 7.686 | 20 | 16 | 2 | within |
| notice-retried-1 | 7.944 | 20 | 16 | 1 | within |
| notice-retried-2 | 8.140 | 20 | 16 | 2 | within |
| notice-retried-3 | 8.185 | 20 | 16 | 1 | within |
| notice-retried-4 | 7.978 | 20 | 16 | 1 | within |
| notice-retried-5 | 8.174 | 20 | 16 | 2 | within |
| notice-retried-6 | 7.978 | 20 | 16 | 1 | within |
| notice-retried-7 | 8.316 | 20 | 16 | 2 | within |

Latest: 8.316 ms, notice-retried-7.

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| notice-retried-0 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-1 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-2 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-3 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-4 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-5 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-6 | 656 | 97,496 (0.975) | 77,568 (0.776) |
| notice-retried-7 | 656 | 97,496 (0.975) | 77,568 (0.776) |

Longest pass that carries a step: 97,496 CPU cycles (0.975 ms), notice-retried-0; longest step: 77,568 (0.776 ms), notice-retried-0.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-0.stream_info.if0` | 768,573 | 7.686 | 20 | 24 | fits | 23,091 | 52 | 0.444 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-0.held.adp.if0` | 162,603 | 1.626 | 20 | 200 | fits | 153,012 | 224 | 0.235 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-0.held.acmp.if0` | 438,245 | 4.382 | 20 | 20 | fits | 143,229 | 145 | 0.416 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-0.held.aecp.if0` | 418,041 | 4.180 | 20 | 24 | fits | 143,229 | 145 | 0.416 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-0.held.maap.if0` | 398,770 | 3.988 | 20 | 50 | fits | 143,229 | 145 | 0.416 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-0.held.srp.if0` | 741,002 | 7.410 | 20 | 20 | fits | 91,191 | 46 | 0.517 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-0.mrpdu.periodic.if0` | 77,535 | 0.775 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-1.stream_info.if0` | 794,420 | 7.944 | 20 | 24 | fits | 23,045 | 52 | 0.444 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-1.held.adp.if0` | 159,112 | 1.591 | 20 | 200 | fits | 156,098 | 230 | 0.229 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-1.held.acmp.if0` | 434,583 | 4.346 | 20 | 20 | fits | 143,143 | 145 | 0.415 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-1.held.aecp.if0` | 414,379 | 4.144 | 20 | 24 | fits | 143,143 | 145 | 0.415 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-1.held.maap.if0` | 395,108 | 3.951 | 20 | 50 | fits | 143,143 | 145 | 0.415 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-1.held.srp.if0` | 737,356 | 7.374 | 20 | 20 | fits | 95,499 | 59 | 0.561 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-1.mrpdu.periodic.if0` | 76,431 | 0.764 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-2.stream_info.if0` | 813,975 | 8.140 | 20 | 24 | fits | 23,043 | 52 | 0.442 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-2.held.adp.if0` | 160,222 | 1.602 | 20 | 200 | fits | 153,600 | 224 | 0.245 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-2.held.acmp.if0` | 435,725 | 4.357 | 20 | 20 | fits | 143,227 | 145 | 0.415 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-2.held.aecp.if0` | 415,521 | 4.155 | 20 | 24 | fits | 143,227 | 145 | 0.415 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-2.held.maap.if0` | 396,250 | 3.962 | 20 | 50 | fits | 143,227 | 145 | 0.415 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-2.held.srp.if0` | 738,712 | 7.387 | 20 | 20 | fits | 95,442 | 59 | 0.560 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-2.mrpdu.periodic.if0` | 78,889 | 0.789 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-3.stream_info.if0` | 818,523 | 8.185 | 20 | 24 | fits | 23,093 | 52 | 0.447 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-3.held.adp.if0` | 168,208 | 1.682 | 20 | 200 | fits | 150,923 | 222 | 0.267 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-3.held.acmp.if0` | 444,074 | 4.441 | 20 | 20 | fits | 143,278 | 145 | 0.417 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-3.held.aecp.if0` | 423,870 | 4.239 | 20 | 24 | fits | 143,278 | 145 | 0.417 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-3.held.maap.if0` | 404,599 | 4.046 | 20 | 50 | fits | 143,278 | 145 | 0.417 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-3.held.srp.if0` | 731,941 | 7.319 | 20 | 20 | fits | 91,290 | 48 | 0.514 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-3.mrpdu.periodic.if0` | 85,779 | 0.858 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-4.stream_info.if0` | 797,773 | 7.978 | 20 | 24 | fits | 23,093 | 52 | 0.447 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-4.held.adp.if0` | 148,660 | 1.487 | 20 | 200 | fits | 136,535 | 151 | 0.166 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-4.held.acmp.if0` | 447,723 | 4.477 | 20 | 20 | fits | 144,485 | 145 | 0.430 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-4.held.aecp.if0` | 427,519 | 4.275 | 20 | 24 | fits | 144,485 | 145 | 0.430 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-4.held.maap.if0` | 408,248 | 4.082 | 20 | 50 | fits | 144,485 | 145 | 0.430 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-4.held.srp.if0` | 735,587 | 7.356 | 20 | 20 | fits | 91,066 | 46 | 0.514 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-4.mrpdu.periodic.if0` | 86,156 | 0.862 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-5.stream_info.if0` | 817,394 | 8.174 | 20 | 24 | fits | 23,091 | 52 | 0.444 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-5.held.adp.if0` | 148,087 | 1.481 | 20 | 200 | fits | 138,065 | 154 | 0.165 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-5.held.acmp.if0` | 446,534 | 4.465 | 20 | 20 | fits | 155,046 | 175 | 0.424 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-5.held.aecp.if0` | 426,330 | 4.263 | 20 | 24 | fits | 155,046 | 175 | 0.424 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-5.held.maap.if0` | 407,059 | 4.071 | 20 | 50 | fits | 155,046 | 175 | 0.424 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-5.held.srp.if0` | 734,392 | 7.344 | 20 | 20 | fits | 91,066 | 46 | 0.514 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-5.mrpdu.periodic.if0` | 87,210 | 0.872 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-6.stream_info.if0` | 797,773 | 7.978 | 20 | 24 | fits | 23,093 | 52 | 0.447 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-6.held.adp.if0` | 171,781 | 1.718 | 20 | 200 | fits | 155,130 | 223 | 0.235 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-6.held.acmp.if0` | 453,245 | 4.532 | 20 | 20 | fits | 138,766 | 149 | 0.455 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-6.held.aecp.if0` | 433,041 | 4.330 | 20 | 24 | fits | 138,766 | 149 | 0.455 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-6.held.maap.if0` | 413,770 | 4.138 | 20 | 50 | fits | 138,766 | 149 | 0.455 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-6.held.srp.if0` | 740,767 | 7.408 | 20 | 20 | fits | 91,066 | 46 | 0.514 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-6.mrpdu.periodic.if0` | 78,004 | 0.780 | 49 | 49 | fits | 0 | - | 0.000 |
| a retried notice, from its port's answer (THE RETRY) | `notice-retried-7.stream_info.if0` | 831,626 | 8.316 | 20 | 24 | fits | 23,997 | 52 | 0.480 |
| ADP record, every channel at its refill rate, the longest | `notice-retried-7.held.adp.if0` | 169,975 | 1.700 | 20 | 200 | fits | 158,116 | 230 | 0.257 |
| ACMP record, every channel at its refill rate, the longest | `notice-retried-7.held.acmp.if0` | 437,595 | 4.376 | 20 | 20 | fits | 134,962 | 138 | 0.436 |
| AECP record, every channel at its refill rate, the longest | `notice-retried-7.held.aecp.if0` | 417,391 | 4.174 | 20 | 24 | fits | 134,962 | 138 | 0.436 |
| MAAP record, every channel at its refill rate, the longest | `notice-retried-7.held.maap.if0` | 398,120 | 3.981 | 20 | 50 | fits | 134,962 | 138 | 0.436 |
| SRP record, every channel at its refill rate, the longest | `notice-retried-7.held.srp.if0` | 739,503 | 7.395 | 20 | 20 | fits | 99,123 | 50 | 0.488 |
| an MRPDU its periodic timer owes, the longest | `notice-retried-7.mrpdu.periodic.if0` | 95,023 | 0.950 | 49 | 49 | fits | 0 | - | 0.000 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
