<!-- SPDX-License-Identifier: Apache-2.0 -->
# Tester guide

Use this guide to reproduce the current checks and extend coverage.
Read the [implementation status](manager.md#implementation-status) before interpreting a passing result.
Keep each command's exit code in your test report.

## Run the suites

Install a [C11 draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) compiler, [CMake](https://cmake.org/cmake/help/latest/), [cgreen](https://github.com/cgreen-devs/cgreen), and [behave](https://behave.readthedocs.io/en/stable/).
Set LWSRP_BUILD to a writable build directory outside the checkout.
Set CGREEN_PREFIX to the installed unit framework prefix.
Set CMAKE_PREFIX_PATH to that prefix and LD_LIBRARY_PATH to its library directory.
For the isolated compiler command, also set CPATH and LIBRARY_PATH to its include and library directories.
Run these commands from the repository root.

~~~sh
cmake -S . -B "$LWSRP_BUILD" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN=OFF
cmake --build "$LWSRP_BUILD" --parallel 2
ctest --test-dir "$LWSRP_BUILD" --output-on-failure
"$LWSRP_BUILD/unit_tests"
SHLAN_LIBRARY="$LWSRP_BUILD/libshlan.so" behave
behave --dry-run
~~~

| Check | Current result | Meaning |
| --- | --- | --- |
| Configure and build | Exit 0. | The host library and required unit target compile. |
| Default unit target | Exit 0; 70 tests and 4215 assertions. | The [runner](../tests/unit/main.c) executes eight suites. |
| Scenario execution | Exit 0; three scenarios and ten steps pass. | The [setup hook](../tests/features/environment.py) loads the [test bindings](../tests/features/switch_bindings.c). |
| Scenario dry run | Validates step matching only. | It does not execute setup or verify behavior. |

The [fault-injecting allocation port](../tests/unit/fault_alloc.c) replaces hosted allocation symbols in the unit executable.
The [boundary suite](../tests/unit/review_test.c) fails selected allocations and checks the count of live allocations after teardown.
It also checks changed Listener and Talker values after both received and transmitted LeaveAll.
Named reversals must fail these regressions after compiling successfully.

The [build definition](../CMakeLists.txt) requires the unit framework's headers and library for host configuration.
It rejects an empty suite through an output-based failure rule.
The scenario hook uses SHLAN_LIBRARY when set, with the root build directory as fallback.
The [switch operations](../src/core/switch.c) are exported symbols.
The [test bindings](../tests/features/switch_bindings.c) preserve the established scenario entry points.

## Test both Registrar profiles

The commands above explicitly select default [IEEE 802.1Q-2018, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/) timing.
Set LWSRP_MILAN_BUILD to another writable build directory outside the checkout.
Enable [LWSRP_MILAN](../CMakeLists.txt) for [Milan v1.2, clause 4.2.7.2.2](https://milanav.com/milan-faqs/).

~~~sh
cmake -S . -B "$LWSRP_MILAN_BUILD" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN=ON
cmake --build "$LWSRP_MILAN_BUILD" --parallel 2
ctest --test-dir "$LWSRP_MILAN_BUILD" --output-on-failure
"$LWSRP_MILAN_BUILD/unit_tests"
SHLAN_LIBRARY="$LWSRP_MILAN_BUILD/libshlan.so" behave
~~~

The enabled build passes 70 tests with 4203 assertions.
It also passes three scenarios and ten steps.
The [profile suite](../tests/unit/milan_test.c) checks both application options in each build.
It checks the actual constructor against the build selection.
Different constructor paths account for the assertion-count difference.
Talker and Listener indications must arrive before the receive call returns, without a timer tick.
Repeated withdrawals produce no duplicate indication.
A withdrawal after LeaveAll preserves the deadline, checked one centisecond before expiry and at expiry.
The suite also pins default VLAN and MAC aging and local withdrawal behavior.
Re-declare and transmitted LeaveAll retain their timed transitions when rapid withdrawal is enabled.

## Run the existing codec tests

The [codec test source](../tests/unit/mrp_pdu_test.c) contains nine tests.
The configured unit target includes them through the [suite runner](../tests/unit/main.c).
For an isolated codec run, this command uses the same tests and the [codec implementation](../src/core/mrp_pdu.c).
The [public headers](../src/include/shish_lan/mrp_pdu.h) define the tested helpers.
Use a [C compiler](https://gcc.gnu.org/onlinedocs/gcc/) with the unit dependency available.

~~~sh
cc -std=c11 -Isrc/include tests/unit/mrp_pdu_test.c src/core/mrp_pdu.c -xc - -lcgreen -o "$LWSRP_BUILD/mrp_pdu_tests" <<'C'
#include <cgreen/cgreen.h>
TestSuite *mrp_pdu_suite(void);
int main(void)
{
    return run_test_suite(mrp_pdu_suite(), create_text_reporter());
}
C
"$LWSRP_BUILD/mrp_pdu_tests"
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
Run the real suite to execute setup and assertions.
Both [active-state and inactive-state assertions](../tests/features/steps/switch_steps.py#L27-L37) only repeat the operation and check its return code.
Neither independently reads port state.

## Coverage

~~~mermaid
flowchart LR
    Checks[Current checks] --> Codec[Nine codec tests]
    Checks --> Scenarios[Three switch scenarios]
    Scenarios --> Steps[Ten passing steps]
    Checks --> State[State and timer tests]
    Missing[Coverage gaps] --> Exhaustive[Exhaustive state paths]
    Missing --> Wire[Network interoperability]
    Missing --> Target[Hardware and lifecycle]
~~~

| Area | Current evidence | Next useful cases |
| --- | --- | --- |
| Packed values and encoding | [Nine codec tests](../tests/unit/mrp_pdu_test.c). | Multi-value encoding and malformed lengths. |
| Switch operations | [Three passing scenarios](../tests/features/switch.feature); a wrong disable binding also passes all three. | Independent state queries and adapter failures; see [issue #4](https://github.com/kebag-logic/lwSRP/issues/4). |
| Parser | [Receive tests](../tests/unit/receive_test.c) and [integration tests](../tests/unit/integration_test.c) cover truncation, packed events, complete ends, and atomic validation. | Fuzzing and allocation exhaustion. |
| Receive boundaries | [Boundary tests](../tests/unit/review_test.c) cover range rejection, overflow, legal maxima, unknown types, and unknown events across every application. | Randomized mixed-message input. |
| Deferred propagation | [Multiport tests](../tests/unit/review_test.c) cover refused targets, copied values, source reclamation, allocation rollback, callback order, retry, and teardown. | Exhaustion under prolonged refusal. |
| MRP state | [Transmit tests](../tests/unit/transmit_test.c) cover declaration ladders, refusal, retry, segmentation, withdrawal, and redeclaration. | Exhaustive table paths and topology-dependent propagation masks. |
| Timers | [Lifecycle tests](../tests/unit/timer_test.c) and [integration tests](../tests/unit/integration_test.c) cover removal, recreation, aging, periodic timing, and LeaveAll draws. | Target scheduling and long-duration drift. |
| Profile withdrawal | [Profile tests](../tests/unit/milan_test.c) cover immediate stream withdrawal, unchanged VLAN/MAC timing, and preserved LV deadlines. | Target callback timing and network interoperability. |
| Hardware and network | No adapter or interoperability suite. | Target timing, frame ownership, and packet captures. |

A [disable binding](../tests/features/switch_bindings.c) redirected to enable still passes all three scenarios.
The active-state and inactive-state assertions repeat operations; they cannot establish port state.
The defect is tracked in [issue #4](https://github.com/kebag-logic/lwSRP/issues/4).

The [build definition](../CMakeLists.txt) has no coverage target or instrumentation option.
No line or branch coverage percentage has been measured.
Passing codec assertions do not demonstrate protocol conformance.

## Planted reversals

The [reversal runner](../tests/check_reversals.py) copies source and tests into a new scratch directory.
It changes one behavior at a time, builds, and requires the corresponding check to fail.
It restores each source before continuing and finishes with a passing build and test run.
A behavioral mutation that only breaks compilation does not count as detected.
Every command's return code and output are saved in scratch.
Set REVERSAL_SCRATCH, MILAN_REVERSAL_SCRATCH, and EMBEDDED_SCRATCH to separate new directories outside the checkout.

~~~sh
python3 tests/check_embedded.py --work-dir "$EMBEDDED_SCRATCH"
python3 tests/check_freestanding.py
CC="cc -DLWSRP_MILAN=1" python3 tests/check_freestanding.py
python3 tests/check_reversals.py --work-dir "$REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX"
python3 tests/check_reversals.py --work-dir "$MILAN_REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX" --milan ON
~~~

The [freestanding check](../tests/check_freestanding.py) uses the configured C compiler and rejects hosted allocation, error, and print headers.
The [reversal cases](../tests/check_reversals.py) cover destination addresses, LeaveAll isolation, validation, offsets, retry, timing, storage, and registration changes.
They also check callback member order and strict bounded-header initialization.
Two independent profile reversals delay withdrawal from IN and restart the LV deadline.
The first must fail both immediate-indication tests while the deadline test still passes.
The second must fail the deadline test while the immediate-indication tests still pass.
Additional reversals check build selection and application scope.
Both profiles run all 75 reversals.
They also pin propagation order, recovery indications, extension handling, range errors, and all reported LeaveAll boundaries.
Each added behavioral reversal must fail its named regression after successful compilation.
The [embedded check](../tests/check_embedded.py) exercises the actual module source list with a host compiler in both profiles.
Removing switch dispatch must fail its link with the missing public symbols.
Header and warning regressions intentionally fail compilation or dependency checks.
The checks do not prove target linking or network conformance.

## Documentation checks

Run the [link, sentence, reference, and graph checks](tools/README.md).
Report missing dependencies and failed links separately from successful checks.
Include every graph render result and any unverified target behavior.
