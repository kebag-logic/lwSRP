### 1x1

Clock: CPU 100 MHz on sys, the product's split CPU clock, bus 100 MHz.

0 of 7 paths and 0 of 280 probe instances miss their budget.

| Path | Interface | Worst instance | ms (bound) | Verdict | Records ahead | Instances | Misses |
|---|---:|---|---:|---|---:|---:|---:|
| ACMP record, every channel at its refill rate, the longest | 0 | `notice-burst-5.held.acmp.if0` (notice-burst-5) | 5.180 | fits | 11 acmp | 16 | 0 |
| ADP record, every channel at its refill rate, the longest | 0 | `notice-burst-5.held.adp.if0` (notice-burst-5) | 5.382 | fits | 7 adp | 16 | 0 |
| AECP record, every channel at its refill rate, the longest | 0 | `notice-every-7.held.aecp.if0` (notice-every-7) | 4.485 | fits | 15 aecp | 16 | 0 |
| MAAP record, every channel at its refill rate, the longest | 0 | `notice-burst-5.held.maap.if0` (notice-burst-5) | 4.785 | fits | 6 maap | 16 | 0 |
| SRP record, every channel at its refill rate, the longest | 0 | `notice-every-7.held.srp.if0` (notice-every-7) | 9.407 | fits | 31 srp | 16 | 0 |
| an MRPDU its periodic timer owes, the longest | 0 | `notice-every-7.mrpdu.periodic.if0` (notice-every-7) | 1.130 | fits | 0 srp | 8 | 0 |
| a queued notice, from its port's answer | 0 | `notice-burst-6.notices.29.36.0.if0` (notice-burst-6) | 20.467 (20.681) | fits | 1 events | 192 | 0 |

Composed windows: a window that left its load unreleased ran its passes without that work, so its longest pass is a lower bound.

| Group | Event records held at its opening | Window ms | Passes in it | Longest pass, CPU cycles (ms) | Load released | Unreleased |
|---|---:|---:|---:|---:|---|---|

Per-pass share (share.py): 20 ms over 10 passes, 2.000 ms, 200,000 CPU cycles. A work pass over it is a finding whatever the rows say.

| Group | Work passes | Over the share | Longest pass, CPU cycles (ms) | Verdict |
|---|---:|---:|---:|---|
| notice-every-0 | 1864 | 0 | 153,770 (1.538) | fits |
| notice-every-1 | 1862 | 0 | 153,708 (1.537) | fits |
| notice-every-2 | 1861 | 0 | 153,708 (1.537) | fits |
| notice-every-3 | 1858 | 0 | 153,811 (1.538) | fits |
| notice-every-4 | 1854 | 0 | 153,840 (1.538) | fits |
| notice-every-5 | 1853 | 0 | 153,668 (1.537) | fits |
| notice-every-6 | 1858 | 0 | 153,700 (1.537) | fits |
| notice-every-7 | 1849 | 0 | 153,694 (1.537) | fits |
| notice-burst-0 | 1261 | 0 | 152,994 (1.530) | fits |
| notice-burst-1 | 1235 | 0 | 152,994 (1.530) | fits |
| notice-burst-2 | 1269 | 0 | 152,770 (1.528) | fits |
| notice-burst-3 | 1260 | 0 | 153,122 (1.531) | fits |
| notice-burst-4 | 1233 | 0 | 153,966 (1.540) | fits |
| notice-burst-5 | 1273 | 0 | 153,090 (1.531) | fits |
| notice-burst-6 | 1220 | 0 | 153,122 (1.531) | fits |
| notice-burst-7 | 1229 | 0 | 153,007 (1.530) | fits |

Retried notices, from the port's answer to the last recipient's commit (notice_window.py; ctrl_loop.h, THE RETRY):

| Group | ms | Bound ms | Recipients | Events held at the answer | Verdict |
|---|---:|---:|---:|---:|---|
| notice-every-0 | 2.289 | 130 | 16 | 2 | within |
| notice-every-0 | 2.468 | 130 | 16 | 2 | within |
| notice-every-0 | 4.126 | 130 | 16 | 2 | within |
| notice-every-0 | 4.302 | 130 | 16 | 2 | within |
| notice-every-0 | 6.158 | 130 | 16 | 2 | within |
| notice-every-0 | 6.332 | 130 | 16 | 2 | within |
| notice-every-0 | 8.205 | 130 | 16 | 2 | within |
| notice-every-0 | 8.376 | 130 | 16 | 2 | within |
| notice-every-0 | 2.605 | 130 | 16 | 2 | within |
| notice-every-0 | 4.433 | 130 | 16 | 2 | within |
| notice-every-0 | 6.502 | 130 | 16 | 2 | within |
| notice-every-0 | 8.541 | 130 | 16 | 2 | within |
| notice-every-1 | 2.087 | 130 | 16 | 2 | within |
| notice-every-1 | 2.265 | 130 | 16 | 2 | within |
| notice-every-1 | 4.092 | 130 | 16 | 2 | within |
| notice-every-1 | 4.268 | 130 | 16 | 2 | within |
| notice-every-1 | 6.124 | 130 | 16 | 2 | within |
| notice-every-1 | 6.297 | 130 | 16 | 2 | within |
| notice-every-1 | 8.170 | 130 | 16 | 2 | within |
| notice-every-1 | 8.341 | 130 | 16 | 2 | within |
| notice-every-1 | 2.403 | 130 | 16 | 2 | within |
| notice-every-1 | 4.399 | 130 | 16 | 2 | within |
| notice-every-1 | 6.467 | 130 | 16 | 2 | within |
| notice-every-1 | 8.506 | 130 | 16 | 2 | within |
| notice-every-2 | 1.917 | 130 | 16 | 2 | within |
| notice-every-2 | 2.093 | 130 | 16 | 2 | within |
| notice-every-2 | 3.918 | 130 | 16 | 2 | within |
| notice-every-2 | 4.094 | 130 | 16 | 2 | within |
| notice-every-2 | 5.950 | 130 | 16 | 2 | within |
| notice-every-2 | 6.123 | 130 | 16 | 2 | within |
| notice-every-2 | 7.995 | 130 | 16 | 2 | within |
| notice-every-2 | 8.167 | 130 | 16 | 2 | within |
| notice-every-2 | 2.230 | 130 | 16 | 2 | within |
| notice-every-2 | 4.224 | 130 | 16 | 2 | within |
| notice-every-2 | 6.293 | 130 | 16 | 2 | within |
| notice-every-2 | 8.331 | 130 | 16 | 2 | within |
| notice-every-3 | 3.802 | 130 | 16 | 2 | within |
| notice-every-3 | 3.978 | 130 | 16 | 2 | within |
| notice-every-3 | 5.849 | 130 | 16 | 2 | within |
| notice-every-3 | 6.024 | 130 | 16 | 2 | within |
| notice-every-3 | 7.858 | 130 | 16 | 2 | within |
| notice-every-3 | 8.032 | 130 | 16 | 2 | within |
| notice-every-3 | 1.912 | 130 | 16 | 2 | within |
| notice-every-3 | 2.093 | 130 | 16 | 2 | within |
| notice-every-3 | 4.113 | 130 | 16 | 2 | within |
| notice-every-3 | 6.151 | 130 | 16 | 2 | within |
| notice-every-3 | 2.267 | 130 | 16 | 2 | within |
| notice-every-3 | 8.199 | 130 | 16 | 2 | within |
| notice-every-4 | 6.143 | 130 | 16 | 2 | within |
| notice-every-4 | 6.318 | 130 | 16 | 2 | within |
| notice-every-4 | 8.007 | 130 | 16 | 2 | within |
| notice-every-4 | 8.183 | 130 | 16 | 2 | within |
| notice-every-4 | 1.910 | 130 | 16 | 2 | within |
| notice-every-4 | 2.092 | 130 | 16 | 2 | within |
| notice-every-4 | 3.949 | 130 | 16 | 2 | within |
| notice-every-4 | 4.128 | 130 | 16 | 2 | within |
| notice-every-4 | 6.451 | 130 | 16 | 2 | within |
| notice-every-4 | 8.307 | 130 | 16 | 2 | within |
| notice-every-4 | 2.267 | 130 | 16 | 2 | within |
| notice-every-4 | 4.301 | 130 | 16 | 2 | within |
| notice-every-5 | 6.029 | 130 | 16 | 2 | within |
| notice-every-5 | 6.204 | 130 | 16 | 2 | within |
| notice-every-5 | 7.893 | 130 | 16 | 2 | within |
| notice-every-5 | 8.069 | 130 | 16 | 2 | within |
| notice-every-5 | 1.912 | 130 | 16 | 2 | within |
| notice-every-5 | 2.094 | 130 | 16 | 2 | within |
| notice-every-5 | 3.991 | 130 | 16 | 2 | within |
| notice-every-5 | 4.170 | 130 | 16 | 2 | within |
| notice-every-5 | 6.337 | 130 | 16 | 2 | within |
| notice-every-5 | 8.193 | 130 | 16 | 2 | within |
| notice-every-5 | 2.269 | 130 | 16 | 2 | within |
| notice-every-5 | 4.343 | 130 | 16 | 2 | within |
| notice-every-6 | 8.330 | 130 | 16 | 2 | within |
| notice-every-6 | 8.505 | 130 | 16 | 2 | within |
| notice-every-6 | 2.144 | 130 | 16 | 2 | within |
| notice-every-6 | 2.323 | 130 | 16 | 2 | within |
| notice-every-6 | 4.186 | 130 | 16 | 2 | within |
| notice-every-6 | 4.365 | 130 | 16 | 2 | within |
| notice-every-6 | 6.184 | 130 | 16 | 2 | within |
| notice-every-6 | 6.360 | 130 | 16 | 2 | within |
| notice-every-6 | 8.636 | 130 | 16 | 2 | within |
| notice-every-6 | 10.136 | 130 | 16 | 2 | within |
| notice-every-6 | 2.497 | 130 | 16 | 2 | within |
| notice-every-6 | 4.539 | 130 | 16 | 2 | within |
| notice-every-7 | 8.027 | 130 | 16 | 2 | within |
| notice-every-7 | 8.202 | 130 | 16 | 2 | within |
| notice-every-7 | 1.812 | 130 | 16 | 2 | within |
| notice-every-7 | 1.989 | 130 | 16 | 2 | within |
| notice-every-7 | 3.852 | 130 | 16 | 2 | within |
| notice-every-7 | 4.031 | 130 | 16 | 2 | within |
| notice-every-7 | 6.035 | 130 | 16 | 2 | within |
| notice-every-7 | 6.211 | 130 | 16 | 2 | within |
| notice-every-7 | 8.334 | 130 | 16 | 2 | within |
| notice-every-7 | 9.834 | 130 | 16 | 2 | within |
| notice-every-7 | 2.163 | 130 | 16 | 2 | within |
| notice-every-7 | 4.205 | 130 | 16 | 2 | within |
| notice-burst-0 | 9.266 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.246 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.419 | 130 | 16 | 0 | within |
| notice-burst-0 | 14.589 | 130 | 16 | 0 | within |
| notice-burst-0 | 1.932 | 130 | 16 | 0 | within |
| notice-burst-0 | 2.114 | 130 | 16 | 0 | within |
| notice-burst-0 | 2.930 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.109 | 130 | 16 | 0 | within |
| notice-burst-0 | 15.967 | 130 | 16 | 0 | within |
| notice-burst-0 | 16.088 | 130 | 16 | 0 | within |
| notice-burst-0 | 16.256 | 130 | 16 | 0 | within |
| notice-burst-0 | 3.283 | 130 | 16 | 0 | within |
| notice-burst-1 | 8.292 | 130 | 16 | 0 | within |
| notice-burst-1 | 13.261 | 130 | 16 | 0 | within |
| notice-burst-1 | 13.433 | 130 | 16 | 0 | within |
| notice-burst-1 | 13.604 | 130 | 16 | 0 | within |
| notice-burst-1 | 2.173 | 130 | 16 | 0 | within |
| notice-burst-1 | 2.355 | 130 | 16 | 0 | within |
| notice-burst-1 | 2.968 | 130 | 16 | 0 | within |
| notice-burst-1 | 3.147 | 130 | 16 | 0 | within |
| notice-burst-1 | 14.982 | 130 | 16 | 0 | within |
| notice-burst-1 | 15.103 | 130 | 16 | 0 | within |
| notice-burst-1 | 15.271 | 130 | 16 | 0 | within |
| notice-burst-1 | 3.321 | 130 | 16 | 0 | within |
| notice-burst-2 | 8.590 | 130 | 16 | 2 | within |
| notice-burst-2 | 12.733 | 130 | 16 | 2 | within |
| notice-burst-2 | 12.905 | 130 | 16 | 2 | within |
| notice-burst-2 | 13.076 | 130 | 16 | 2 | within |
| notice-burst-2 | 14.026 | 130 | 16 | 2 | within |
| notice-burst-2 | 14.197 | 130 | 16 | 2 | within |
| notice-burst-2 | 2.043 | 130 | 16 | 2 | within |
| notice-burst-2 | 2.225 | 130 | 16 | 2 | within |
| notice-burst-2 | 14.331 | 130 | 16 | 2 | within |
| notice-burst-2 | 16.129 | 130 | 16 | 2 | within |
| notice-burst-2 | 16.300 | 130 | 16 | 2 | within |
| notice-burst-2 | 4.589 | 130 | 16 | 2 | within |
| notice-burst-3 | 11.451 | 130 | 16 | 1 | within |
| notice-burst-3 | 11.629 | 130 | 16 | 1 | within |
| notice-burst-3 | 11.780 | 130 | 16 | 1 | within |
| notice-burst-3 | 13.061 | 130 | 16 | 1 | within |
| notice-burst-3 | 13.224 | 130 | 16 | 1 | within |
| notice-burst-3 | 13.394 | 130 | 16 | 1 | within |
| notice-burst-3 | 3.547 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.106 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.242 | 130 | 16 | 1 | within |
| notice-burst-3 | 15.360 | 130 | 16 | 1 | within |
| notice-burst-3 | 17.197 | 130 | 16 | 1 | within |
| notice-burst-3 | 17.365 | 130 | 16 | 1 | within |
| notice-burst-4 | 5.276 | 130 | 16 | 1 | within |
| notice-burst-4 | 5.453 | 130 | 16 | 1 | within |
| notice-burst-4 | 5.604 | 130 | 16 | 1 | within |
| notice-burst-4 | 6.047 | 130 | 16 | 1 | within |
| notice-burst-4 | 15.485 | 130 | 16 | 1 | within |
| notice-burst-4 | 15.662 | 130 | 16 | 1 | within |
| notice-burst-4 | 15.808 | 130 | 16 | 1 | within |
| notice-burst-4 | 17.226 | 130 | 16 | 1 | within |
| notice-burst-4 | 6.188 | 130 | 16 | 1 | within |
| notice-burst-4 | 6.309 | 130 | 16 | 1 | within |
| notice-burst-4 | 17.397 | 130 | 16 | 1 | within |
| notice-burst-4 | 17.561 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.164 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.340 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.491 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.725 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.164 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.340 | 130 | 16 | 1 | within |
| notice-burst-5 | 16.487 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.210 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.864 | 130 | 16 | 1 | within |
| notice-burst-5 | 6.985 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.381 | 130 | 16 | 1 | within |
| notice-burst-5 | 18.545 | 130 | 16 | 1 | within |
| notice-burst-6 | 6.736 | 130 | 16 | 1 | within |
| notice-burst-6 | 14.577 | 130 | 16 | 1 | within |
| notice-burst-6 | 14.749 | 130 | 16 | 1 | within |
| notice-burst-6 | 14.918 | 130 | 16 | 1 | within |
| notice-burst-6 | 16.182 | 130 | 16 | 1 | within |
| notice-burst-6 | 16.353 | 130 | 16 | 1 | within |
| notice-burst-6 | 16.500 | 130 | 16 | 1 | within |
| notice-burst-6 | 18.208 | 130 | 16 | 1 | within |
| notice-burst-6 | 18.343 | 130 | 16 | 1 | within |
| notice-burst-6 | 18.461 | 130 | 16 | 1 | within |
| notice-burst-6 | 20.299 | 130 | 16 | 1 | within |
| notice-burst-6 | 20.467 | 130 | 16 | 1 | within |
| notice-burst-7 | 8.969 | 130 | 16 | 0 | within |
| notice-burst-7 | 15.276 | 130 | 16 | 0 | within |
| notice-burst-7 | 15.449 | 130 | 16 | 0 | within |
| notice-burst-7 | 15.620 | 130 | 16 | 0 | within |
| notice-burst-7 | 2.173 | 130 | 16 | 0 | within |
| notice-burst-7 | 2.355 | 130 | 16 | 0 | within |
| notice-burst-7 | 2.969 | 130 | 16 | 0 | within |
| notice-burst-7 | 3.147 | 130 | 16 | 0 | within |
| notice-burst-7 | 16.996 | 130 | 16 | 0 | within |
| notice-burst-7 | 17.118 | 130 | 16 | 0 | within |
| notice-burst-7 | 17.286 | 130 | 16 | 0 | within |
| notice-burst-7 | 3.321 | 130 | 16 | 0 | within |

Latest: 20.467 ms, notice-burst-6.

Passes that carry the store's step (THE STEP), and the longest step's own CPU time, the store's and its flash port's:

| Group | Passes | Longest, CPU cycles (ms) | Longest step, CPU cycles (ms) |
|---|---:|---:|---:|
| notice-every-0 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-1 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-2 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-3 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-4 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-5 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-6 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-every-7 | 402 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-0 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-1 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-2 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-3 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-4 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-5 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-6 | 412 | 95,374 (0.954) | 78,283 (0.783) |
| notice-burst-7 | 412 | 95,374 (0.954) | 78,283 (0.783) |

Longest pass that carries a step: 95,374 CPU cycles (0.954 ms), notice-every-0; longest step: 78,283 (0.783 ms), notice-every-0.

| Path | Probe | CPU cycles | ms | Budget (+W) ms | Ceiling ms | Verdict | Taking pass cycles | Mailbox accesses (model) | Fetch share |
|---|---|---:|---:|---:|---:|---|---:|---:|---:|
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.0.if0` | 228,944 | 2.289 | 130 | 134 | fits | 58,546 | 153 | 0.256 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.0.if0` | 246,755 | 2.468 | 130 | 134 | fits | 58,546 | 153 | 0.256 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.5.1.if0` | 412,643 | 4.126 | 130 | 134 | fits | 55,683 | 153 | 0.223 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.5.1.if0` | 430,239 | 4.302 | 130 | 134 | fits | 55,683 | 153 | 0.223 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.0.if0` | 615,842 | 6.158 | 130 | 134 | fits | 58,242 | 155 | 0.174 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.0.if0` | 633,205 | 6.332 | 130 | 134 | fits | 58,242 | 155 | 0.174 |
| a queued notice, from its port's answer | `notice-every-0.notices.f.6.1.if0` | 820,463 | 8.205 | 130 | 134 | fits | 56,707 | 153 | 0.171 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.6.1.if0` | 837,603 | 8.376 | 130 | 134 | fits | 56,707 | 153 | 0.171 |
| a queued notice, from its port's answer | `notice-every-0.notices.27.9.0.if0` | 260,495 | 2.605 | 130 | 134 | fits | 58,546 | 153 | 0.256 |
| a queued notice, from its port's answer | `notice-every-0.notices.28.9.0.if0` | 443,252 | 4.433 | 130 | 134 | fits | 55,683 | 153 | 0.223 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.9.0.if0` | 650,186 | 6.502 | 130 | 134 | fits | 58,242 | 155 | 0.174 |
| a queued notice, from its port's answer | `notice-every-0.notices.29.36.0.if0` | 854,076 | 8.541 | 130 | 134 | fits | 56,707 | 153 | 0.171 |
| ADP record, every channel at its refill rate, the longest | `notice-every-0.held.adp.if0` | 174,747 | 1.747 | 20 | 200 | fits | 150,309 | 299 | 0.233 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-0.held.acmp.if0` | 437,543 | 4.375 | 20 | 20 | fits | 134,247 | 93 | 0.474 |
| AECP record, every channel at its refill rate, the longest | `notice-every-0.held.aecp.if0` | 417,339 | 4.173 | 20 | 24 | fits | 134,247 | 93 | 0.474 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-0.held.maap.if0` | 115,004 | 1.150 | 20 | 50 | fits | 150,309 | 299 | 0.233 |
| SRP record, every channel at its refill rate, the longest | `notice-every-0.held.srp.if0` | 909,624 | 9.096 | 20 | 20 | fits | 56,458 | 33 | 0.746 |
| an MRPDU its periodic timer owes, the longest | `notice-every-0.mrpdu.periodic.if0` | 112,295 | 1.123 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.0.if0` | 208,733 | 2.087 | 130 | 134 | fits | 58,655 | 155 | 0.256 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.0.if0` | 226,544 | 2.265 | 130 | 134 | fits | 58,655 | 155 | 0.256 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.5.1.if0` | 409,194 | 4.092 | 130 | 134 | fits | 55,802 | 153 | 0.225 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.5.1.if0` | 426,790 | 4.268 | 130 | 134 | fits | 55,802 | 153 | 0.225 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.0.if0` | 612,374 | 6.124 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.0.if0` | 629,737 | 6.297 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.f.6.1.if0` | 816,965 | 8.170 | 130 | 134 | fits | 56,628 | 153 | 0.170 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.6.1.if0` | 834,105 | 8.341 | 130 | 134 | fits | 56,628 | 153 | 0.170 |
| a queued notice, from its port's answer | `notice-every-1.notices.27.9.0.if0` | 240,284 | 2.403 | 130 | 134 | fits | 58,655 | 155 | 0.256 |
| a queued notice, from its port's answer | `notice-every-1.notices.28.9.0.if0` | 439,857 | 4.399 | 130 | 134 | fits | 55,802 | 153 | 0.225 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.9.0.if0` | 646,718 | 6.467 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-1.notices.29.36.0.if0` | 850,578 | 8.506 | 130 | 134 | fits | 56,628 | 153 | 0.170 |
| ADP record, every channel at its refill rate, the longest | `notice-every-1.held.adp.if0` | 169,432 | 1.694 | 20 | 200 | fits | 148,989 | 293 | 0.234 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-1.held.acmp.if0` | 461,890 | 4.619 | 20 | 20 | fits | 135,976 | 100 | 0.481 |
| AECP record, every channel at its refill rate, the longest | `notice-every-1.held.aecp.if0` | 441,686 | 4.417 | 20 | 24 | fits | 135,976 | 100 | 0.481 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-1.held.maap.if0` | 109,689 | 1.097 | 20 | 50 | fits | 148,989 | 293 | 0.234 |
| SRP record, every channel at its refill rate, the longest | `notice-every-1.held.srp.if0` | 914,939 | 9.149 | 20 | 20 | fits | 54,460 | 33 | 0.701 |
| an MRPDU its periodic timer owes, the longest | `notice-every-1.mrpdu.periodic.if0` | 85,846 | 0.858 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.0.if0` | 191,657 | 1.917 | 130 | 134 | fits | 57,837 | 154 | 0.239 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.0.if0` | 209,312 | 2.093 | 130 | 134 | fits | 57,837 | 154 | 0.239 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.5.1.if0` | 391,849 | 3.918 | 130 | 134 | fits | 55,845 | 154 | 0.223 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.5.1.if0` | 409,381 | 4.094 | 130 | 134 | fits | 55,845 | 154 | 0.223 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.0.if0` | 594,963 | 5.950 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.0.if0` | 612,326 | 6.123 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-2.notices.f.6.1.if0` | 799,535 | 7.995 | 130 | 134 | fits | 56,549 | 153 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.6.1.if0` | 816,675 | 8.167 | 130 | 134 | fits | 56,549 | 153 | 0.169 |
| a queued notice, from its port's answer | `notice-every-2.notices.27.9.0.if0` | 222,979 | 2.230 | 130 | 134 | fits | 57,837 | 154 | 0.239 |
| a queued notice, from its port's answer | `notice-every-2.notices.28.9.0.if0` | 422,448 | 4.224 | 130 | 134 | fits | 55,845 | 154 | 0.223 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.9.0.if0` | 629,307 | 6.293 | 130 | 134 | fits | 58,163 | 155 | 0.172 |
| a queued notice, from its port's answer | `notice-every-2.notices.29.36.0.if0` | 833,148 | 8.331 | 130 | 134 | fits | 56,549 | 153 | 0.169 |
| ADP record, every channel at its refill rate, the longest | `notice-every-2.held.adp.if0` | 169,334 | 1.693 | 20 | 200 | fits | 149,634 | 293 | 0.234 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-2.held.acmp.if0` | 467,265 | 4.673 | 20 | 20 | fits | 137,897 | 106 | 0.484 |
| AECP record, every channel at its refill rate, the longest | `notice-every-2.held.aecp.if0` | 447,061 | 4.471 | 20 | 24 | fits | 137,897 | 106 | 0.484 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-2.held.maap.if0` | 109,591 | 1.096 | 20 | 50 | fits | 149,634 | 293 | 0.234 |
| SRP record, every channel at its refill rate, the longest | `notice-every-2.held.srp.if0` | 935,335 | 9.353 | 20 | 20 | fits | 57,427 | 39 | 0.727 |
| an MRPDU its periodic timer owes, the longest | `notice-every-2.mrpdu.periodic.if0` | 106,912 | 1.069 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.0.if0` | 380,169 | 3.802 | 130 | 134 | fits | 56,885 | 154 | 0.233 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.0.if0` | 397,755 | 3.978 | 130 | 134 | fits | 56,885 | 154 | 0.233 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.5.1.if0` | 584,897 | 5.849 | 130 | 134 | fits | 54,806 | 154 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.5.1.if0` | 602,429 | 6.024 | 130 | 134 | fits | 54,806 | 154 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.0.if0` | 785,812 | 7.858 | 130 | 134 | fits | 57,402 | 153 | 0.173 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.0.if0` | 803,175 | 8.032 | 130 | 134 | fits | 57,402 | 153 | 0.173 |
| a queued notice, from its port's answer | `notice-every-3.notices.f.6.1.if0` | 191,184 | 1.912 | 130 | 134 | fits | 61,304 | 153 | 0.182 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.6.1.if0` | 209,315 | 2.093 | 130 | 134 | fits | 61,304 | 153 | 0.182 |
| a queued notice, from its port's answer | `notice-every-3.notices.27.9.0.if0` | 411,293 | 4.113 | 130 | 134 | fits | 56,885 | 154 | 0.233 |
| a queued notice, from its port's answer | `notice-every-3.notices.28.9.0.if0` | 615,107 | 6.151 | 130 | 134 | fits | 54,806 | 154 | 0.214 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.9.0.if0` | 226,658 | 2.267 | 130 | 134 | fits | 61,304 | 153 | 0.182 |
| a queued notice, from its port's answer | `notice-every-3.notices.29.36.0.if0` | 819,931 | 8.199 | 130 | 134 | fits | 57,402 | 153 | 0.173 |
| ADP record, every channel at its refill rate, the longest | `notice-every-3.held.adp.if0` | 175,707 | 1.757 | 20 | 200 | fits | 151,398 | 302 | 0.237 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-3.held.acmp.if0` | 457,581 | 4.576 | 20 | 20 | fits | 137,553 | 106 | 0.486 |
| AECP record, every channel at its refill rate, the longest | `notice-every-3.held.aecp.if0` | 437,377 | 4.374 | 20 | 24 | fits | 137,553 | 106 | 0.486 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-3.held.maap.if0` | 115,964 | 1.160 | 20 | 50 | fits | 151,398 | 302 | 0.237 |
| SRP record, every channel at its refill rate, the longest | `notice-every-3.held.srp.if0` | 927,973 | 9.280 | 20 | 20 | fits | 57,595 | 33 | 0.760 |
| an MRPDU its periodic timer owes, the longest | `notice-every-3.mrpdu.periodic.if0` | 97,179 | 0.972 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.0.if0` | 614,341 | 6.143 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.0.if0` | 631,837 | 6.318 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.5.1.if0` | 800,738 | 8.007 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.5.1.if0` | 818,270 | 8.183 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.0.if0` | 191,039 | 1.910 | 130 | 134 | fits | 61,568 | 155 | 0.182 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.0.if0` | 209,227 | 2.092 | 130 | 134 | fits | 61,568 | 155 | 0.182 |
| a queued notice, from its port's answer | `notice-every-4.notices.f.6.1.if0` | 394,870 | 3.949 | 130 | 134 | fits | 59,964 | 155 | 0.178 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.6.1.if0` | 412,755 | 4.128 | 130 | 134 | fits | 59,964 | 155 | 0.178 |
| a queued notice, from its port's answer | `notice-every-4.notices.27.9.0.if0` | 645,144 | 6.451 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-4.notices.28.9.0.if0` | 830,717 | 8.307 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.9.0.if0` | 226,714 | 2.267 | 130 | 134 | fits | 61,568 | 155 | 0.182 |
| a queued notice, from its port's answer | `notice-every-4.notices.29.36.0.if0` | 430,060 | 4.301 | 130 | 134 | fits | 59,964 | 155 | 0.178 |
| ADP record, every channel at its refill rate, the longest | `notice-every-4.held.adp.if0` | 173,570 | 1.736 | 20 | 200 | fits | 150,095 | 301 | 0.228 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-4.held.acmp.if0` | 460,383 | 4.604 | 20 | 20 | fits | 138,526 | 108 | 0.490 |
| AECP record, every channel at its refill rate, the longest | `notice-every-4.held.aecp.if0` | 440,179 | 4.402 | 20 | 24 | fits | 138,526 | 108 | 0.490 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-4.held.maap.if0` | 113,827 | 1.138 | 20 | 50 | fits | 150,095 | 301 | 0.228 |
| SRP record, every channel at its refill rate, the longest | `notice-every-4.held.srp.if0` | 925,385 | 9.254 | 20 | 20 | fits | 56,598 | 33 | 0.746 |
| an MRPDU its periodic timer owes, the longest | `notice-every-4.mrpdu.periodic.if0` | 99,155 | 0.992 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.0.if0` | 602,929 | 6.029 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.0.if0` | 620,425 | 6.204 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.5.1.if0` | 789,326 | 7.893 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.5.1.if0` | 806,858 | 8.069 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.0.if0` | 191,205 | 1.912 | 130 | 134 | fits | 61,491 | 153 | 0.183 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.0.if0` | 209,393 | 2.094 | 130 | 134 | fits | 61,491 | 153 | 0.183 |
| a queued notice, from its port's answer | `notice-every-5.notices.f.6.1.if0` | 399,114 | 3.991 | 130 | 134 | fits | 59,830 | 153 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.6.1.if0` | 416,999 | 4.170 | 130 | 134 | fits | 59,830 | 153 | 0.177 |
| a queued notice, from its port's answer | `notice-every-5.notices.27.9.0.if0` | 633,732 | 6.337 | 130 | 134 | fits | 55,963 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-5.notices.28.9.0.if0` | 819,305 | 8.193 | 130 | 134 | fits | 54,108 | 152 | 0.215 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.9.0.if0` | 226,880 | 2.269 | 130 | 134 | fits | 61,491 | 153 | 0.183 |
| a queued notice, from its port's answer | `notice-every-5.notices.29.36.0.if0` | 434,304 | 4.343 | 130 | 134 | fits | 59,830 | 153 | 0.177 |
| ADP record, every channel at its refill rate, the longest | `notice-every-5.held.adp.if0` | 164,658 | 1.647 | 20 | 200 | fits | 148,834 | 293 | 0.229 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-5.held.acmp.if0` | 466,018 | 4.660 | 20 | 20 | fits | 138,054 | 108 | 0.489 |
| AECP record, every channel at its refill rate, the longest | `notice-every-5.held.aecp.if0` | 445,814 | 4.458 | 20 | 24 | fits | 138,054 | 108 | 0.489 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-5.held.maap.if0` | 104,915 | 1.049 | 20 | 50 | fits | 148,834 | 293 | 0.229 |
| SRP record, every channel at its refill rate, the longest | `notice-every-5.held.srp.if0` | 932,074 | 9.321 | 20 | 20 | fits | 56,518 | 33 | 0.746 |
| an MRPDU its periodic timer owes, the longest | `notice-every-5.mrpdu.periodic.if0` | 105,645 | 1.056 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.0.if0` | 832,994 | 8.330 | 130 | 134 | fits | 55,405 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.0.if0` | 850,460 | 8.505 | 130 | 134 | fits | 55,405 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.5.1.if0` | 214,390 | 2.144 | 130 | 134 | fits | 62,681 | 155 | 0.219 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.5.1.if0` | 232,257 | 2.323 | 130 | 134 | fits | 62,681 | 155 | 0.219 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.0.if0` | 418,608 | 4.186 | 130 | 134 | fits | 60,002 | 153 | 0.179 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.0.if0` | 436,485 | 4.365 | 130 | 134 | fits | 60,002 | 153 | 0.179 |
| a queued notice, from its port's answer | `notice-every-6.notices.f.6.1.if0` | 618,414 | 6.184 | 130 | 134 | fits | 41,439 | 103 | 0.233 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.6.1.if0` | 635,989 | 6.360 | 130 | 134 | fits | 41,439 | 103 | 0.233 |
| a queued notice, from its port's answer | `notice-every-6.notices.27.9.0.if0` | 863,609 | 8.636 | 130 | 134 | fits | 55,405 | 152 | 0.224 |
| a queued notice, from its port's answer | `notice-every-6.notices.28.9.0.if0` | 1,013,601 | 10.136 | 130 | 134 | fits | 20,034 | 51 | 0.343 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.9.0.if0` | 249,665 | 2.497 | 130 | 134 | fits | 62,681 | 155 | 0.219 |
| a queued notice, from its port's answer | `notice-every-6.notices.29.36.0.if0` | 453,934 | 4.539 | 130 | 134 | fits | 60,002 | 153 | 0.179 |
| ADP record, every channel at its refill rate, the longest | `notice-every-6.held.adp.if0` | 161,938 | 1.619 | 20 | 200 | fits | 149,816 | 295 | 0.230 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-6.held.acmp.if0` | 450,462 | 4.505 | 20 | 20 | fits | 139,140 | 112 | 0.486 |
| AECP record, every channel at its refill rate, the longest | `notice-every-6.held.aecp.if0` | 430,258 | 4.303 | 20 | 24 | fits | 139,140 | 112 | 0.486 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-6.held.maap.if0` | 102,195 | 1.022 | 20 | 50 | fits | 149,816 | 295 | 0.230 |
| SRP record, every channel at its refill rate, the longest | `notice-every-6.held.srp.if0` | 914,578 | 9.146 | 20 | 20 | fits | 56,601 | 33 | 0.746 |
| an MRPDU its periodic timer owes, the longest | `notice-every-6.mrpdu.periodic.if0` | 103,674 | 1.037 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.0.if0` | 802,738 | 8.027 | 130 | 134 | fits | 55,534 | 152 | 0.225 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.0.if0` | 820,204 | 8.202 | 130 | 134 | fits | 55,534 | 152 | 0.225 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.5.1.if0` | 181,212 | 1.812 | 130 | 134 | fits | 61,788 | 155 | 0.201 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.5.1.if0` | 198,923 | 1.989 | 130 | 134 | fits | 61,788 | 155 | 0.201 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.0.if0` | 385,204 | 3.852 | 130 | 134 | fits | 60,096 | 155 | 0.180 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.0.if0` | 403,081 | 4.031 | 130 | 134 | fits | 60,096 | 155 | 0.180 |
| a queued notice, from its port's answer | `notice-every-7.notices.f.6.1.if0` | 603,497 | 6.035 | 130 | 134 | fits | 41,468 | 103 | 0.235 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.6.1.if0` | 621,072 | 6.211 | 130 | 134 | fits | 41,468 | 103 | 0.235 |
| a queued notice, from its port's answer | `notice-every-7.notices.27.9.0.if0` | 833,353 | 8.334 | 130 | 134 | fits | 55,534 | 152 | 0.225 |
| a queued notice, from its port's answer | `notice-every-7.notices.28.9.0.if0` | 983,387 | 9.834 | 130 | 134 | fits | 20,034 | 51 | 0.343 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.9.0.if0` | 216,331 | 2.163 | 130 | 134 | fits | 61,788 | 155 | 0.201 |
| a queued notice, from its port's answer | `notice-every-7.notices.29.36.0.if0` | 420,530 | 4.205 | 130 | 134 | fits | 60,096 | 155 | 0.180 |
| ADP record, every channel at its refill rate, the longest | `notice-every-7.held.adp.if0` | 173,090 | 1.731 | 20 | 200 | fits | 149,297 | 291 | 0.231 |
| ACMP record, every channel at its refill rate, the longest | `notice-every-7.held.acmp.if0` | 468,658 | 4.687 | 20 | 20 | fits | 136,583 | 102 | 0.488 |
| AECP record, every channel at its refill rate, the longest | `notice-every-7.held.aecp.if0` | 448,454 | 4.485 | 20 | 24 | fits | 136,583 | 102 | 0.488 |
| MAAP record, every channel at its refill rate, the longest | `notice-every-7.held.maap.if0` | 113,347 | 1.133 | 20 | 50 | fits | 149,297 | 291 | 0.231 |
| SRP record, every channel at its refill rate, the longest | `notice-every-7.held.srp.if0` | 940,723 | 9.407 | 20 | 20 | fits | 56,520 | 33 | 0.746 |
| an MRPDU its periodic timer owes, the longest | `notice-every-7.mrpdu.periodic.if0` | 112,957 | 1.130 | 49 | 49 | fits | 0 | - | 0.000 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.0.if0` | 926,625 | 9.266 | 130 | 134 | fits | 26,580 | 51 | 0.489 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.0.if0` | 1,424,610 | 14.246 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.5.1.if0` | 1,441,859 | 14.419 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.5.1.if0` | 1,458,903 | 14.589 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.0.if0` | 193,224 | 1.932 | 130 | 134 | fits | 56,037 | 111 | 0.239 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.0.if0` | 211,411 | 2.114 | 130 | 134 | fits | 56,037 | 111 | 0.239 |
| a queued notice, from its port's answer | `notice-burst-0.notices.f.6.1.if0` | 293,005 | 2.930 | 130 | 134 | fits | 72,364 | 162 | 0.179 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.6.1.if0` | 310,883 | 3.109 | 130 | 134 | fits | 72,364 | 162 | 0.179 |
| a queued notice, from its port's answer | `notice-burst-0.notices.27.9.0.if0` | 1,596,691 | 15.967 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-0.notices.28.9.0.if0` | 1,608,769 | 16.088 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.9.0.if0` | 1,625,562 | 16.256 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-0.notices.29.36.0.if0` | 328,291 | 3.283 | 130 | 134 | fits | 72,364 | 162 | 0.179 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-0.held.adp.if0` | 38,849 | 0.388 | 20 | 200 | fits | 35,831 | 60 | 0.072 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-0.held.acmp.if0` | 408,772 | 4.088 | 20 | 20 | fits | 139,979 | 122 | 0.449 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-0.held.aecp.if0` | 388,568 | 3.886 | 20 | 24 | fits | 139,979 | 122 | 0.449 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-0.held.maap.if0` | 369,297 | 3.693 | 20 | 50 | fits | 139,979 | 122 | 0.449 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-0.held.srp.if0` | 844,926 | 8.449 | 20 | 20 | fits | 51,621 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.0.if0` | 829,168 | 8.292 | 130 | 134 | fits | 26,593 | 51 | 0.489 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.0.if0` | 1,326,098 | 13.261 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.5.1.if0` | 1,343,347 | 13.433 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.5.1.if0` | 1,360,391 | 13.604 | 130 | 134 | fits | 60,919 | 153 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.0.if0` | 217,274 | 2.173 | 130 | 134 | fits | 43,744 | 102 | 0.249 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.0.if0` | 235,461 | 2.355 | 130 | 134 | fits | 43,744 | 102 | 0.249 |
| a queued notice, from its port's answer | `notice-burst-1.notices.f.6.1.if0` | 296,846 | 2.968 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.6.1.if0` | 314,663 | 3.147 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-1.notices.27.9.0.if0` | 1,498,245 | 14.982 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-1.notices.28.9.0.if0` | 1,510,323 | 15.103 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.9.0.if0` | 1,527,116 | 15.271 | 130 | 134 | fits | 49,942 | 152 | 0.173 |
| a queued notice, from its port's answer | `notice-burst-1.notices.29.36.0.if0` | 332,071 | 3.321 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-1.held.adp.if0` | 37,928 | 0.379 | 20 | 200 | fits | 35,831 | 60 | 0.072 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-1.held.acmp.if0` | 408,760 | 4.088 | 20 | 20 | fits | 139,702 | 134 | 0.445 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-1.held.aecp.if0` | 388,556 | 3.886 | 20 | 24 | fits | 139,702 | 134 | 0.445 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-1.held.maap.if0` | 369,285 | 3.693 | 20 | 50 | fits | 139,702 | 134 | 0.445 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-1.held.srp.if0` | 843,939 | 8.439 | 20 | 20 | fits | 51,621 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.0.if0` | 859,011 | 8.590 | 130 | 134 | fits | 27,635 | 52 | 0.506 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.0.if0` | 1,273,266 | 12.733 | 130 | 134 | fits | 60,844 | 153 | 0.233 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.5.1.if0` | 1,290,515 | 12.905 | 130 | 134 | fits | 60,844 | 153 | 0.233 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.5.1.if0` | 1,307,559 | 13.076 | 130 | 134 | fits | 60,844 | 153 | 0.233 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.0.if0` | 1,402,557 | 14.026 | 130 | 134 | fits | 53,809 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.0.if0` | 1,419,744 | 14.197 | 130 | 134 | fits | 53,809 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-2.notices.f.6.1.if0` | 204,341 | 2.043 | 130 | 134 | fits | 56,003 | 111 | 0.241 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.6.1.if0` | 222,471 | 2.225 | 130 | 134 | fits | 56,003 | 111 | 0.241 |
| a queued notice, from its port's answer | `notice-burst-2.notices.27.9.0.if0` | 1,433,051 | 14.331 | 130 | 134 | fits | 53,809 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-2.notices.28.9.0.if0` | 1,612,890 | 16.129 | 130 | 134 | fits | 37,283 | 102 | 0.201 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.9.0.if0` | 1,630,020 | 16.300 | 130 | 134 | fits | 37,283 | 102 | 0.201 |
| a queued notice, from its port's answer | `notice-burst-2.notices.29.36.0.if0` | 458,873 | 4.589 | 130 | 134 | fits | 27,280 | 53 | 0.344 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-2.held.adp.if0` | 150,886 | 1.509 | 20 | 200 | fits | 150,652 | 281 | 0.214 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-2.held.acmp.if0` | 445,004 | 4.450 | 20 | 20 | fits | 136,789 | 110 | 0.488 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-2.held.aecp.if0` | 424,800 | 4.248 | 20 | 24 | fits | 136,789 | 110 | 0.488 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-2.held.maap.if0` | 405,529 | 4.055 | 20 | 50 | fits | 136,789 | 110 | 0.488 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-2.held.srp.if0` | 884,339 | 8.843 | 20 | 20 | fits | 51,770 | 26 | 0.714 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.0.if0` | 1,145,076 | 11.451 | 130 | 134 | fits | 60,436 | 152 | 0.284 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.0.if0` | 1,162,879 | 11.629 | 130 | 134 | fits | 60,436 | 152 | 0.284 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.5.1.if0` | 1,177,950 | 11.780 | 130 | 134 | fits | 60,436 | 152 | 0.284 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.5.1.if0` | 1,306,141 | 13.061 | 130 | 134 | fits | 58,278 | 153 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.0.if0` | 1,322,445 | 13.224 | 130 | 134 | fits | 58,278 | 153 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.0.if0` | 1,339,372 | 13.394 | 130 | 134 | fits | 58,278 | 153 | 0.187 |
| a queued notice, from its port's answer | `notice-burst-3.notices.f.6.1.if0` | 354,679 | 3.547 | 130 | 134 | fits | 26,345 | 52 | 0.483 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.6.1.if0` | 1,510,627 | 15.106 | 130 | 134 | fits | 49,880 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-3.notices.27.9.0.if0` | 1,524,153 | 15.242 | 130 | 134 | fits | 49,880 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-3.notices.28.9.0.if0` | 1,535,970 | 15.360 | 130 | 134 | fits | 49,880 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.9.0.if0` | 1,719,727 | 17.197 | 130 | 134 | fits | 40,747 | 103 | 0.150 |
| a queued notice, from its port's answer | `notice-burst-3.notices.29.36.0.if0` | 1,736,495 | 17.365 | 130 | 134 | fits | 40,747 | 103 | 0.150 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-3.held.adp.if0` | 146,007 | 1.460 | 20 | 200 | fits | 146,737 | 275 | 0.229 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-3.held.acmp.if0` | 447,087 | 4.471 | 20 | 20 | fits | 144,013 | 123 | 0.462 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-3.held.aecp.if0` | 426,883 | 4.269 | 20 | 24 | fits | 144,013 | 123 | 0.462 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-3.held.maap.if0` | 407,612 | 4.076 | 20 | 50 | fits | 144,013 | 123 | 0.462 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-3.held.srp.if0` | 853,251 | 8.533 | 20 | 20 | fits | 51,818 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.0.if0` | 527,621 | 5.276 | 130 | 134 | fits | 58,432 | 152 | 0.238 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.0.if0` | 545,275 | 5.453 | 130 | 134 | fits | 58,432 | 152 | 0.238 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.5.1.if0` | 560,437 | 5.604 | 130 | 134 | fits | 58,432 | 152 | 0.238 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.5.1.if0` | 604,682 | 6.047 | 130 | 134 | fits | 70,833 | 167 | 0.251 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.0.if0` | 1,548,475 | 15.485 | 130 | 134 | fits | 57,974 | 153 | 0.266 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.0.if0` | 1,566,166 | 15.662 | 130 | 134 | fits | 57,974 | 153 | 0.266 |
| a queued notice, from its port's answer | `notice-burst-4.notices.f.6.1.if0` | 1,580,814 | 15.808 | 130 | 134 | fits | 57,974 | 153 | 0.266 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.6.1.if0` | 1,722,619 | 17.226 | 130 | 134 | fits | 57,805 | 153 | 0.124 |
| a queued notice, from its port's answer | `notice-burst-4.notices.27.9.0.if0` | 618,846 | 6.188 | 130 | 134 | fits | 70,833 | 167 | 0.251 |
| a queued notice, from its port's answer | `notice-burst-4.notices.28.9.0.if0` | 630,949 | 6.309 | 130 | 134 | fits | 70,833 | 167 | 0.251 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.9.0.if0` | 1,739,722 | 17.397 | 130 | 134 | fits | 57,805 | 153 | 0.124 |
| a queued notice, from its port's answer | `notice-burst-4.notices.29.36.0.if0` | 1,756,125 | 17.561 | 130 | 134 | fits | 57,805 | 153 | 0.124 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-4.held.adp.if0` | 473,500 | 4.735 | 20 | 200 | fits | 123,370 | 229 | 0.185 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-4.held.acmp.if0` | 453,232 | 4.532 | 20 | 20 | fits | 123,370 | 229 | 0.185 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-4.held.aecp.if0` | 309,658 | 3.097 | 20 | 24 | fits | 153,966 | 156 | 0.449 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-4.held.maap.if0` | 413,757 | 4.138 | 20 | 50 | fits | 123,370 | 229 | 0.185 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-4.held.srp.if0` | 855,973 | 8.560 | 20 | 20 | fits | 51,758 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.0.if0` | 616,418 | 6.164 | 130 | 134 | fits | 70,975 | 161 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.0.if0` | 634,005 | 6.340 | 130 | 134 | fits | 70,975 | 161 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.5.1.if0` | 649,104 | 6.491 | 130 | 134 | fits | 70,975 | 161 | 0.237 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.5.1.if0` | 672,527 | 6.725 | 130 | 134 | fits | 48,449 | 152 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.0.if0` | 1,616,354 | 16.164 | 130 | 134 | fits | 57,976 | 153 | 0.267 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.0.if0` | 1,634,045 | 16.340 | 130 | 134 | fits | 57,976 | 153 | 0.267 |
| a queued notice, from its port's answer | `notice-burst-5.notices.f.6.1.if0` | 1,648,695 | 16.487 | 130 | 134 | fits | 57,976 | 153 | 0.267 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.6.1.if0` | 1,821,016 | 18.210 | 130 | 134 | fits | 57,835 | 153 | 0.125 |
| a queued notice, from its port's answer | `notice-burst-5.notices.27.9.0.if0` | 686,361 | 6.864 | 130 | 134 | fits | 48,449 | 152 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-5.notices.28.9.0.if0` | 698,495 | 6.985 | 130 | 134 | fits | 48,449 | 152 | 0.100 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.9.0.if0` | 1,838,119 | 18.381 | 130 | 134 | fits | 57,835 | 153 | 0.125 |
| a queued notice, from its port's answer | `notice-burst-5.notices.29.36.0.if0` | 1,854,522 | 18.545 | 130 | 134 | fits | 57,835 | 153 | 0.125 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-5.held.adp.if0` | 538,249 | 5.382 | 20 | 200 | fits | 125,668 | 241 | 0.185 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-5.held.acmp.if0` | 517,981 | 5.180 | 20 | 20 | fits | 125,668 | 241 | 0.185 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-5.held.aecp.if0` | 372,109 | 3.721 | 20 | 24 | fits | 150,583 | 151 | 0.456 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-5.held.maap.if0` | 478,506 | 4.785 | 20 | 50 | fits | 125,668 | 241 | 0.185 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-5.held.srp.if0` | 920,701 | 9.207 | 20 | 20 | fits | 51,758 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.0.if0` | 673,613 | 6.736 | 130 | 134 | fits | 27,164 | 52 | 0.496 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.0.if0` | 1,457,749 | 14.577 | 130 | 134 | fits | 61,649 | 153 | 0.254 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.5.1.if0` | 1,474,895 | 14.749 | 130 | 134 | fits | 61,649 | 153 | 0.254 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.5.1.if0` | 1,491,784 | 14.918 | 130 | 134 | fits | 61,649 | 153 | 0.254 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.0.if0` | 1,618,175 | 16.182 | 130 | 134 | fits | 55,336 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.0.if0` | 1,635,321 | 16.353 | 130 | 134 | fits | 55,336 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-6.notices.f.6.1.if0` | 1,649,969 | 16.500 | 130 | 134 | fits | 55,336 | 152 | 0.207 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.6.1.if0` | 1,820,769 | 18.208 | 130 | 134 | fits | 49,894 | 152 | 0.177 |
| a queued notice, from its port's answer | `notice-burst-6.notices.27.9.0.if0` | 1,834,314 | 18.343 | 130 | 134 | fits | 49,894 | 152 | 0.177 |
| a queued notice, from its port's answer | `notice-burst-6.notices.28.9.0.if0` | 1,846,131 | 18.461 | 130 | 134 | fits | 49,894 | 152 | 0.177 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.9.0.if0` | 2,029,888 | 20.299 | 130 | 134 | fits | 40,747 | 103 | 0.150 |
| a queued notice, from its port's answer | `notice-burst-6.notices.29.36.0.if0` | 2,046,656 | 20.467 | 130 | 134 | fits | 40,747 | 103 | 0.150 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-6.held.adp.if0` | 154,842 | 1.548 | 20 | 200 | fits | 146,028 | 272 | 0.220 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-6.held.acmp.if0` | 452,063 | 4.521 | 20 | 20 | fits | 138,513 | 118 | 0.479 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-6.held.aecp.if0` | 431,859 | 4.319 | 20 | 24 | fits | 138,513 | 118 | 0.479 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-6.held.maap.if0` | 412,588 | 4.126 | 20 | 50 | fits | 138,513 | 118 | 0.479 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-6.held.srp.if0` | 856,367 | 8.564 | 20 | 20 | fits | 51,807 | 26 | 0.712 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.0.if0` | 896,874 | 8.969 | 130 | 134 | fits | 26,183 | 52 | 0.478 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.0.if0` | 1,527,563 | 15.276 | 130 | 134 | fits | 61,753 | 153 | 0.255 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.5.1.if0` | 1,544,852 | 15.449 | 130 | 134 | fits | 61,753 | 153 | 0.255 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.5.1.if0` | 1,562,043 | 15.620 | 130 | 134 | fits | 61,753 | 153 | 0.255 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.0.if0` | 217,337 | 2.173 | 130 | 134 | fits | 43,594 | 102 | 0.247 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.0.if0` | 235,524 | 2.355 | 130 | 134 | fits | 43,594 | 102 | 0.247 |
| a queued notice, from its port's answer | `notice-burst-7.notices.f.6.1.if0` | 296,909 | 2.969 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.6.1.if0` | 314,726 | 3.147 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| a queued notice, from its port's answer | `notice-burst-7.notices.27.9.0.if0` | 1,699,569 | 16.996 | 130 | 134 | fits | 50,049 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-7.notices.28.9.0.if0` | 1,711,761 | 17.118 | 130 | 134 | fits | 50,049 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.9.0.if0` | 1,728,554 | 17.286 | 130 | 134 | fits | 50,049 | 152 | 0.175 |
| a queued notice, from its port's answer | `notice-burst-7.notices.29.36.0.if0` | 332,134 | 3.321 | 130 | 134 | fits | 71,705 | 162 | 0.166 |
| ADP record, every channel at its refill rate, the longest | `notice-burst-7.held.adp.if0` | 152,597 | 1.526 | 20 | 200 | fits | 145,835 | 272 | 0.218 |
| ACMP record, every channel at its refill rate, the longest | `notice-burst-7.held.acmp.if0` | 443,533 | 4.435 | 20 | 20 | fits | 139,802 | 125 | 0.493 |
| AECP record, every channel at its refill rate, the longest | `notice-burst-7.held.aecp.if0` | 423,329 | 4.233 | 20 | 24 | fits | 139,802 | 125 | 0.493 |
| MAAP record, every channel at its refill rate, the longest | `notice-burst-7.held.maap.if0` | 404,058 | 4.041 | 20 | 50 | fits | 139,802 | 125 | 0.493 |
| SRP record, every channel at its refill rate, the longest | `notice-burst-7.held.srp.if0` | 845,372 | 8.454 | 20 | 20 | fits | 51,570 | 26 | 0.712 |

Bounded waits that timed out (the probe is graded on what the log holds):

- none
