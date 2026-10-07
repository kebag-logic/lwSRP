# Shish Lan soft

Tools and functionalities to leverage switch capabilities, built around two "-ilities": testability and flexibility.


## Dependencies

- C11 compiler, CMake >= 3.20
- [cgreen](https://github.com/cgreen-devs/cgreen) — C unit test framework (`apt install libcgreen-dev`)
- [behave](https://behave.readthedocs.io) — Gherkin BDD runner (`pip install behave`)


## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```


## Testing

BDD scenarios (natural language, Gherkin):
```sh
behave
```

C unit tests:
```sh
ctest --test-dir build --output-on-failure
```


# Architecture

The project follows a **Ports & Adapters** pattern. The public C headers define abstract interfaces ("ports"); concrete adapters plug in underneath without changing the interface or the tests above it.

```
src/
  include/shish_lan/   # public API — abstract switch interface
  core/                # low-level hardware drivers ("the metal")
  modules/             # high-level adapters (sim, hw, ...)
tests/
  features/            # Gherkin scenarios + Python/ctypes harness
  unit/                # C unit tests (cgreen)
```


## Testability

Scenarios are written in plain English using Gherkin (`tests/features/*.feature`) so that non-developers can read and write them. The `behave` runner loads the compiled C library at runtime via `ctypes` and maps each GIVEN / WHEN / THEN step to a call into the public C API — no test code knows about internals.

A software simulation adapter (`sim_adapter`) implements the full switch interface in memory, so all scenarios run without physical hardware attached.

C unit tests (`tests/unit/`, cgreen) cover isolated `core/` logic that does not need a full switch context. These are compiled by CMake and run via `ctest`.


## Flexibility

The switch interface (`shlan_switch_t`) is a vtable struct. Swapping from the simulation adapter to a real hardware driver requires no changes to the public API or any test. New capabilities are added by extending the vtable and implementing the new operation in each adapter.


## Licence

lwSRP is licensed under the [Apache License, Version 2.0](LICENSE).
Copyright 2026 kebag-logic. See [NOTICE](NOTICE).

Individuals and companies may contribute under the same licence.

## Builds outside the checkout

The unit executable runs the MRPDU cgreen suite. For an external build
directory, set `SHLAN_LIBRARY` to its `libshlan.so` when running `behave`.
The switch dispatch operations are exported for the Python harness.

## Bare-metal MRP integration

Compile `core/mrp_mad.c`, `core/mrp_pdu.c`, `ports/timer.c` and the chosen
`modules/msrp.c`, `modules/mvrp.c` or `modules/mmrp.c`. Supply the allocation
and debug ports; omit the hosted `ports/alloc.c` and the simulated switch.
The core needs only fixed-width types and memory/string operations. An
application can bind a fixed pool and refuse allocations without a heap.
Allocation failure is returned to the caller; already received attributes
may have been applied before a later allocation fails. Wire-format errors
are validated before any protocol state changes.

Create an application, configure each port before declaring attributes,
then declare and receive on one serialized event loop. Deliver every
centisecond through `shlan_timer_tick()`, including coalesced ticks.
Generic timer defaults are Join 20 cs, Leave 60 cs and LeaveAll 1000 cs;
Milan applications must configure Leave 500 cs. Periodic transmission is
100 cs. LeaveAll draws lie strictly between the configured interval and
1.5 times that interval. All port/application destruction removes its timers.

Call `mrp_transmit()` on each loop pass. Its send port accepts the complete
PDU with zero, or refuses it with a negative result. A refusal preserves the
exact bytes in caller-owned storage. Keep that storage alive and immutable
until the same port accepts; queue RX and local declarations while a PDU
is retained. Registrar timers continue running. The caller supplies an
Ethernet header and chooses the physical interface; the library supplies
the application's group address and EtherType. A bounded PDU buffer may
segment a population over successive Join-spaced opportunities.

Ports, indications, observers and receive-interest filters must never
synchronously call into the owning application. The firmware adapter owns
the debug/release enforcement of that contract. Callbacks must enqueue
future work. The timer list and allocator are process-global; one serialized
dispatcher owns them.

A receive-interest filter may retain only attributes relevant to the end
station. It runs after complete validation, before allocation; LeaveAll
still applies to retained attributes of its type. `mrp_reclaim()` releases
only undeclared, unregistered quiescent attributes outside callbacks and
prepared transmissions (802.1Q Table 10-3 note 11).

MSRP supports Domain, Talker Advertise, Talker Failed and Listener values.
Domain vector offsets increment class and priority, preserving VID. Talker
and Listener vector offsets increment the StreamID's unique-ID field;
Talker destinations also increment. JoinIn/JoinMt replaces an opposite
Talker registration for the same StreamID on that port under 35.2.6.
Conflicting New registrations remain distinguishable so the end station
can apply Talker Failed precedence.

The cgreen executable covers codecs, lifecycle, received state, independent
timers, applicant messages, send refusal/retry, segmentation and attribute
replacement. The behave scenarios cover the exported simulated-switch
entry points. Neither suite claims bridge/RSTP policy or target timing.
