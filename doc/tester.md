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
| Default unit target | Exit 0; 108 tests and 27199 assertions. | The [runner](../tests/unit/main.c) executes ten suites. |
| Scenario execution | Exit 0; three scenarios and ten steps pass. | The [setup hook](../tests/features/environment.py) loads the [test bindings](../tests/features/switch_bindings.c) and reads the simulated port flags. |
| Scenario dry run | Validates step matching only. | It does not execute setup or verify behavior. |

The [fault-injecting allocation port](../tests/unit/fault_alloc.c) replaces hosted allocation symbols in the unit executable.
The [boundary suite](../tests/unit/review_test.c) fails selected allocations and checks the count of live allocations after teardown.
It also checks changed Listener and Talker values after both received and transmitted LeaveAll.
Flush tests fail every reservation from IN and LV, then verify successful recovery on the first tick.
Separate cases repeat failures on successive ticks and assert that each injected fault was reached.
Receive interleavings cover all three stream registrations, both initial states, changed and unchanged values, and New or Join events.
Receive fault sweeps cover all six Leave and Join reservations, repeated refusal, saved values, ordered indications, and teardown.
Cross-port tests run 48 cases with production propagation policy in each profile.
They cover all three stream types, IN and LV, three reservation faults, no-fault controls, and timer or receive completion.
Leave indication and policy must receive the original value while Applicant updates remain visible.
Another 48 cases cover local declarations, repeated failure, and fresh snapshots for later Flush operations.
Timer-completion tests receive three unchanged registrations and require exactly one Leave and one Join.
Observer tests require continuous transitions through the failed Flush and its timer or receive recovery.
Replacement tests start in IN and received-LeaveAll LV, sweep every allocation in both directions, and require Leave before Join.
Additional tests pin receive stopping at source and reservation allocations, policy masks, and allocation-free registration without propagation policy.
Named reversals must fail these regressions after compiling successfully.
The [key suite](../tests/unit/key_test.c) pairs applications that differ only in [attr_key](../src/include/shish_lan/mrp.h).
It runs in a build with LWSRP_ATTR_KEY, such as LWSRP_SCALE's, and is not registered without it.
Both take 4000 random steps of reception, declarations, withdrawals, ticks, and transmissions.
Their indications, attribute states, and transmitted PDUs must match after every step.
Its values often share a key octet across different identities.

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

The enabled build passes 108 tests with 27187 assertions.
It also passes three scenarios and ten steps.
The [profile suite](../tests/unit/milan_test.c) checks both application options in each build.
It checks the actual constructor against the build selection.
Different constructor paths account for the assertion-count difference.
Talker and Listener indications must arrive before the receive call returns, without a timer tick.
Repeated withdrawals produce no duplicate indication.
A withdrawal after LeaveAll preserves the deadline, checked one centisecond before expiry and at expiry.
The suite also pins default VLAN and MAC aging and local withdrawal behavior.
Re-declare and transmitted LeaveAll retain their timed transitions when rapid withdrawal is enabled.

## Check the own LeaveAll

The [LeaveAll suite](../tests/unit/own_leaveall_test.c) pins the participant's own LeaveAll for [issue #20](https://github.com/kebag-logic/lwSRP/issues/20).
Each Applicant takes exactly one of txLA! or txLAF!, and the local rLA! reaches Registrars only.
The rules are [IEEE 802.1Q-2018, clause 10.7.6.6 and Tables 10-3 to 10-5](https://standards.ieee.org/ieee/802.1Q/6844/).
Its first four tests follow the ruling's rows on a stream participant with a peer's Talker and Domain.

| Test | Row | Result at the defect |
| --- | --- | --- |
| A fitting declaration stays quiet | The LeaveAll PDU carries the Join; QA stays QA; the Registrar enters LV. | Fails: QA became VP, and both Joins were sent again. |
| A withdrawal after the LeaveAll PDU sends its Leave | Leave request in QA gives LA; the next PDU carries Lv; then VO. | Fails: VP went to VO with no Lv. |
| An omitted declaration leaves silently | txLAF! gives VP; a Leave request then gives VO, without Lv or Join. | Passes. |
| A withdrawal before the LeaveAll PDU sends no Join | LA takes txLA! to LO, then sends Mt. | Passes. |

The fitting and omitted tests also require no Leave indication at the LeaveAll.
There, rLA! only starts each Registrar's leavetimer ([IEEE 802.1Q-2018, Table 10-4](https://standards.ieee.org/ieee/802.1Q/6844/)).

Two more tests drive one VLAN to each of the twelve Applicant states on shared media.
They grade every state's txLA! cell with a fitting PDU and its txLAF! cell with a full one.
Each grade includes the sent message, the next state, and the Registrar's LV.
The [boundary suite](../tests/unit/review_test.c) also checks one fitting and one omitted VLAN, and the observer's records.
Its earlier expectation, that a fitting QA reaches VP, is replaced.

## Check the grouped encoding

The [grouping suite](../tests/unit/grouping_test.c) pins transmitted bytes for [issue #17](https://github.com/kebag-logic/lwSRP/issues/17).
Its goldens cover two Listener values, both Domain classes, and mixed Talker and Listener Messages.
They also cover empty types under LeaveAll and a VLAN Message under LeaveAll.
Boundary cases fit two values exactly, move one value when one octet is missing, and fill a 1500-octet PDU.
Another stops stream PDUs at 65535 octets, the reach of the two-octet list length.
Sweeps grade every PDU of all three applications across four capacities and two LeaveAll periods.
Three receive tests register the same values from separate, grouped, and packed vectors.
The [test-side decoder](../tests/unit/mrpdu_decoder.c) follows [IEEE 802.1Q-2018, clauses 10.8.1.2 and 10.8.2](https://standards.ieee.org/ieee/802.1Q/6844/).
It shares no code with the [library parser](../src/core/mrp_pdu.c).

The [equivalence check](../tests/check_equivalence.py) builds the base revision's own unit suite twice.
One build uses the base sources; the other uses this checkout's sources.
A [trace library](../tests/unit/transmit_trace.c) wraps each transmit call and decodes every offered PDU.
Every opportunity must return the same result and decode to the same events.
Every new PDU must also have the grouped form.
The base suite may fail only the assertions the [check](../tests/check_equivalence.py) lists as revised by a later issue.
One is listed: its expected local rLA! count changed with [issue #20](https://github.com/kebag-logic/lwSRP/issues/20).
Each suite must also end normally: exit 0, or the runner's exit 1 with its completion line.
A suite ended by a signal or by its time limit fails the check, whatever its log reports.
Set EQUIVALENCE_SCRATCH and MILAN_EQUIVALENCE_SCRATCH to new directories outside the checkout.

~~~sh
python3 tests/check_equivalence.py --work-dir "$EQUIVALENCE_SCRATCH" --prefix "$CGREEN_PREFIX"
python3 tests/check_equivalence.py --work-dir "$MILAN_EQUIVALENCE_SCRATCH" --prefix "$CGREEN_PREFIX" --milan ON
~~~

Both profiles report 22 transmitting scenarios, 148 opportunities, and 138 PDUs.
Of those, 125 PDUs are byte-identical and 13 change only their layout.
No decoded event differs.
Both profiles also report the one revised test.
The switch scenarios make no transmit calls.

The [equivalence controls](../tests/check_equivalence_controls.py) plant one change each in a scratch clone and run the check there.
The revised failure alone must pass.
A signal or a time limit after that failure must fail the check.
So must another assertion of the revised test, and a failure of another test.
Every control must still find no decoded difference.
Set CONTROLS_SCRATCH and MILAN_CONTROLS_SCRATCH to new directories outside the checkout.

~~~sh
python3 tests/check_equivalence_controls.py --work-dir "$CONTROLS_SCRATCH" --prefix "$CGREEN_PREFIX"
python3 tests/check_equivalence_controls.py --work-dir "$MILAN_CONTROLS_SCRATCH" --prefix "$CGREEN_PREFIX" --milan ON
~~~

The time-limit control lets each suite run for 480 seconds; set `--timeout` above one normal suite run.
Both profiles pass all five controls.

## Differential traces

The [differential check](../tests/check_differential.py) proves that a change keeps a base revision's behaviour exactly.
Each trace driver prints one random life of a module.
The trace holds every call, its result, every callback with its arguments, and every transmitted octet.
The check builds each driver against the base revision's sources and against this checkout's.
Both run the same seeds, and every pair of traces must be byte-identical.
The checkout is built with its defaults, and with the three scale options of the [integrator guide](integrator.md#port-platform-services).
With those options it is also built with a four-slot timer wheel started just short of the tick counter's wrap.
It is built with one lookup bucket, as the plain list was, and with 256 buckets.
It is built with each end-station switch alone: lean validation, one-port MAP work, rapid replacement, lean copies and lean tx!.
It is also built with all five on the scale options.
A one-port build's trace at one port is compared without its policy calls that name no port and without its allocation counts.
Its seeds that refuse allocations at one port are counted and not compared: there the base refuses receives that build applies, the [one-port difference](integrator.md#one-port-propagation).
Then each planted defect in the check's list is applied to a copy of the sources, built with the scale options or its own.
Some seed's trace must then differ from the base's, or the defect counts as surviving.
A run that does not end counts as differing.
A defect that only breaks compilation does not count as detected.
Set DIFFERENTIAL_SCRATCH to a new directory outside the checkout.

~~~sh
python3 tests/check_differential.py --work-dir "$DIFFERENTIAL_SCRATCH"
python3 tests/check_differential.py --work-dir "$MILAN_DIFFERENTIAL_SCRATCH" --milan ON
~~~

With --sanitize-memory and a clang, the check also runs the MRP driver's end-station build under MemorySanitizer.
No seed may report a read of an unwritten octet, which the lean validation pass would expose.
A planted Talker decoder that reads a field before writing it must be reported.

~~~sh
python3 tests/check_differential.py --work-dir "$DIFFERENTIAL_SCRATCH" --sanitize-memory clang
~~~

The unit suite also runs with the scale options.
Set SCALE_BUILD to a new directory outside the checkout.

~~~sh
cmake -S . -B "$SCALE_BUILD" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_SCALE=ON
cmake --build "$SCALE_BUILD" --parallel 2
ctest --test-dir "$SCALE_BUILD" --output-on-failure
~~~

That build also registers the key suite: 110 tests with 27227 assertions, and 27215 with the Milan setting.

The [timer driver](../tests/differential/timer_trace.c) registers, arms, disarms, removes, and ticks 48 timers at random.
Its callbacks arm, disarm, and register other timers and themselves, as the MRP callbacks do.
The [MRP driver](../tests/differential/mad_trace.c) runs the stream, VLAN, or MAC application, or a test application, on one to three ports.
It receives random PDUs, declares and withdraws, transmits at seven capacities, ticks, reclaims, and changes roles.
Its seeds refuse some allocations and sends, and its test application refuses to encode one value.
The test application encodes one octet of a two-octet value, so equal FirstValues share a Message.
Its key collides across values, and each received value can replace up to three registrations.
After each step the trace records a digest of every attribute's states and value, and of the transmit buffer.
Each driver runs 200 seeds, 20000 steps each for timers and 3000 for MRP.
Every build gives identical traces in both profiles, the one-port builds as compared above: 177 of 200 seeds identical and 23 refusal seeds counted.
All 36 planted defects are detected: ten in the timers, five in the buckets, eleven in the vector order, and twelve in the end-station switches.
The end-station ones are two in the one-port switch, one in the rapid replacement, four in the lean copies and three in the lean tx!.
The sanitized run reports no seed, and its planted decoder is reported.

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
Check each effect in the [simulated port flags](../tests/features/environment.py), not by repeating an operation.
The setup hook takes the flag count from the [simulation adapter](../src/modules/sim_adapter.c) and stops if its private layout changes.
The [connection step](../tests/features/steps/switch_steps.py) first enables every port, so the reset is visible.
Each port operation must change only its own flag, and a rejected operation must change none.
The [teardown hook](../tests/features/environment.py) requires disconnection to leave every flag unchanged.

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
| Packed values and encoding | [Nine codec tests](../tests/unit/mrp_pdu_test.c) and [grouped-encoding goldens](../tests/unit/grouping_test.c). | Packed transmit vectors and malformed lengths. |
| Switch operations | [Three scenarios](../tests/features/switch.feature) check each connection and port call against the simulated port flags. | Two enabled ports, adapter failures, and an observable disconnection. |
| Parser | [Receive tests](../tests/unit/receive_test.c) and [integration tests](../tests/unit/integration_test.c) cover truncation, packed events, complete ends, and atomic validation. | Fuzzing and allocation exhaustion. |
| Receive boundaries | [Boundary tests](../tests/unit/review_test.c) cover range rejection, overflow, legal maxima, unknown types, and unknown events across every application. | Randomized mixed-message input. |
| Deferred propagation | [Multiport tests](../tests/unit/review_test.c) cover refused targets, copied values, source reclamation, allocation rollback, ordered replacement, Flush snapshots, timer completion, receive interleaving, observer continuity, and teardown. | Exhaustion under prolonged refusal. |
| Propagation policy | [Boundary tests](../tests/unit/review_test.c) pin selected destinations, excluded source ports, Listener routing, receive stopping, and allocation-free operation without policy. | Future spanning-tree role filtering. |
| MRP state | [Transmit tests](../tests/unit/transmit_test.c) cover declaration ladders, refusal, retry, segmentation, withdrawal, and redeclaration. | Exhaustive table paths. |
| Timers | [Lifecycle tests](../tests/unit/timer_test.c) and [integration tests](../tests/unit/integration_test.c) cover removal, recreation, aging, periodic timing, and LeaveAll draws. The [differential check](../tests/check_differential.py) holds the optional wheel to the list walk. | Target scheduling and long-duration drift. |
| Profile withdrawal | [Profile tests](../tests/unit/milan_test.c) cover immediate stream withdrawal, unchanged VLAN/MAC timing, and preserved LV deadlines. | Target callback timing and network interoperability. |
| Hardware and network | No adapter or interoperability suite. | Target timing, frame ownership, and packet captures. |

The [simulation adapter](../src/modules/sim_adapter.c) changes no flag on disconnection.
A [disconnect binding](../tests/features/switch_bindings.c) that skips the call therefore still passes.
The disable scenario enables only port 0, so a disable binding that reconnects also passes.

The [build definition](../CMakeLists.txt) has no coverage target or instrumentation option.
No line or branch coverage percentage has been measured.
Passing codec assertions do not demonstrate protocol conformance.

## Planted reversals

The [reversal runner](../tests/check_reversals.py) copies source and tests into a new scratch directory.
It changes one behavior at a time, builds, and requires the corresponding check to fail.
It restores each source before continuing and finishes with a passing build and test run.
A behavioral mutation that only breaks compilation does not count as detected.
Every command's return code and output are saved in scratch.
Set REVERSAL_SCRATCH, MILAN_REVERSAL_SCRATCH, KEY_REVERSAL_SCRATCH, MILAN_KEY_REVERSAL_SCRATCH, and EMBEDDED_SCRATCH to separate new directories outside the checkout.
The attribute key's reversals run only with --scale ON, which builds LWSRP_SCALE; that run holds no other case.

~~~sh
python3 tests/check_embedded.py --work-dir "$EMBEDDED_SCRATCH"
python3 tests/check_freestanding.py
CC="cc -DLWSRP_MILAN=1" python3 tests/check_freestanding.py
python3 tests/check_reversals.py --work-dir "$REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX"
python3 tests/check_reversals.py --work-dir "$MILAN_REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX" --milan ON
python3 tests/check_reversals.py --work-dir "$KEY_REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX" --scale ON
python3 tests/check_reversals.py --work-dir "$MILAN_KEY_REVERSAL_SCRATCH" --prefix "$CGREEN_PREFIX" --milan ON --scale ON
~~~

The [freestanding check](../tests/check_freestanding.py) uses the configured C compiler and rejects hosted allocation, error, and print headers.
The [reversal cases](../tests/check_reversals.py) cover destination addresses, LeaveAll isolation, validation, offsets, retry, timing, storage, registration changes, and the attribute key.
They also check callback member order and strict bounded-header initialization.
Two independent profile reversals delay withdrawal from IN and restart the LV deadline.
The first must fail both immediate-indication tests while the deadline test still passes.
The second must fail the deadline test while the immediate-indication tests still pass.
Additional reversals check build selection and application scope.
Five grouping reversals split a Message, omit the PDU EndMark, reverse vector order, drop a vector, and remove the length bound.
Each must fail its named [grouping tests](../tests/unit/grouping_test.c).
Five LeaveAll reversals restore the local rLA! for Applicants, apply it before txLA!, and drop it for Registrars.
They also send txLA! for omitted values, and give the Registrars' rLA! a Leave indication.
Each must fail its named [LeaveAll tests](../tests/unit/own_leaveall_test.c).
Seven scenario reversals miswire the [test bindings](../tests/features/switch_bindings.c) or their [scenario setup](../tests/features/environment.py) for [issue #4](https://github.com/kebag-logic/lwSRP/issues/4).
They swap enable and disable, disable the next port, skip connection, and swap connection with disconnection.
Each must fail exactly its named [scenarios](../tests/features/switch.feature) with the expected assertion words.
The runner's interpreter must import [behave](https://behave.readthedocs.io/en/stable/), because it also runs the scenarios before and after the plants.
Both profiles run all 110 reversals, and with --scale ON the attribute key's four.
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
