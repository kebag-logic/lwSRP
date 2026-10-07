<!-- SPDX-License-Identifier: Apache-2.0 -->
# Tester guide

Use this guide to reproduce the current checks and extend coverage.
Read the [implementation status](manager.md#implementation-status) before interpreting a passing result.
Keep each command's exit code in your test report.

## Run the suites

Install a C11 compiler, [CMake](https://cmake.org/cmake/help/latest/), [cgreen](https://github.com/cgreen-devs/cgreen), and [behave](https://behave.readthedocs.io/en/stable/).
Make the unit framework's headers and library discoverable by the compiler and build system.
Run these commands from the repository root.

~~~sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/unit_tests
behave
behave --dry-run
~~~

| Check | Current result | Meaning |
| --- | --- | --- |
| Configure and build | Exit 0. | The host library and optional unit target compile. |
| Configured unit target | Exit 0; zero assertions. | The [runner](../tests/unit/placeholder.c) creates an empty suite. |
| Scenario execution | Exit 1; three scenarios untested. | The [setup hook](../tests/features/environment.py) cannot load [shlan_connect](../src/include/shish_lan/switch.h). |
| Scenario dry run | Validates step matching only. | It does not execute setup or verify behavior. |

The [build definition](../CMakeLists.txt) silently omits the unit target when its dependency is absent.
The scenario hook loads the shared library from the root build directory.
The [switch wrappers](../src/include/shish_lan/switch.h) are static inline functions and do not provide the requested dynamic symbols.
This must be fixed before the scenario suite can execute.

## Run the existing codec tests

The [codec test source](../tests/unit/mrp_pdu_test.c) contains nine tests.
The configured unit target does not include them.
This command compiles them with a small runner and the [codec implementation](../src/core/mrp_pdu.c).
The [public headers](../src/include/shish_lan/mrp_pdu.h) define the tested helpers.
Use a [C compiler](https://gcc.gnu.org/onlinedocs/gcc/) with the unit dependency available.

~~~sh
cc -std=c11 -Isrc/include tests/unit/mrp_pdu_test.c src/core/mrp_pdu.c -xc - -lcgreen -o build/mrp_pdu_tests <<'C'
#include <cgreen/cgreen.h>
TestSuite *mrp_pdu_suite(void);
int main(void)
{
    return run_test_suite(mrp_pdu_suite(), create_text_reporter());
}
C
./build/mrp_pdu_tests
~~~

The observed result is exit 0, with nine tests and 1690 passing assertions.
This exercises packed events, vector headers, framing helpers, vector encoding, and one short-buffer rejection.
It does not test parsing or state-machine behavior.

## Write a scenario

~~~mermaid
flowchart TD
    Behavior[Choose behavior] --> Given[Define starting state]
    Given --> When[Perform one action]
    When --> Then[Check observable result]
    Then --> Match[Check step matching]
    Match --> Execute[Run with working setup]
~~~

Start with the [switch feature](../tests/features/switch.feature).
Use its [step definitions](../tests/features/steps/switch_steps.py) and [lifecycle hooks](../tests/features/environment.py).
The following example uses existing step phrases.

~~~gherkin
Scenario: Enable a port
  Given the switch is connected
  When port 0 is enabled
  Then port 0 should be active
~~~

Place new scenarios in the existing feature directory configured by [the runner settings](../behave.ini).
Reuse matching steps or add a precise new step definition.
Keep setup, action, and assertion separate.
Run the dry-run command above to check matching.
Run the real suite after resolving its setup failure.
The current active-state assertion repeats an operation and checks success.
It does not independently read port state.

## Coverage

~~~mermaid
flowchart LR
    Checks[Current checks] --> Empty[Empty configured unit suite]
    Checks --> Codec[Nine codec tests]
    Checks --> Scenarios[Three switch scenarios]
    Scenarios --> Blocked[Blocked during setup]
    Missing[Coverage gaps] --> State[State and timer behavior]
    Missing --> Wire[Parser and interoperability]
    Missing --> Target[Hardware and lifecycle]
~~~

| Area | Current evidence | Next useful cases |
| --- | --- | --- |
| Packed values and encoding | [Nine codec tests](../tests/unit/mrp_pdu_test.c). | Multi-value encoding and malformed lengths. |
| Switch operations | [Three scenarios](../tests/features/switch.feature), currently blocked. | Independent state queries and adapter failures. |
| Parser | No parser test in the current suite. | Truncation, version handling, subtype vectors, and list boundaries. |
| MRP state | No wired state-machine suite. | Event tables, propagation masks, and callback order. |
| Timers | No timer tests. | Global ticking, expiry, cancellation, and destruction. |
| Hardware and network | No adapter or interoperability suite. | Target timing and packet captures after transmit implementation. |

The [build definition](../CMakeLists.txt) has no coverage target or instrumentation option.
No line or branch coverage percentage has been measured.
Passing codec assertions do not demonstrate protocol conformance.

## Documentation checks

Run the [link, sentence, reference, and graph checks](tools/README.md).
Report missing dependencies and failed links separately from successful checks.
Include every graph render result and any unverified target behavior.
