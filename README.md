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
