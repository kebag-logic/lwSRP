# SPDX-License-Identifier: Apache-2.0
option(LWSRP_MILAN "Use Milan rapid MSRP withdrawal" OFF)
# The timer wheel, the lookup buckets and the merged Message build, for many attributes (doc/integrator.md).
option(LWSRP_SCALE "Use the timer wheel, lookup buckets and merged build" OFF)
set(LWSRP_SCALE_DEFINITIONS LWSRP_TIMER_SLOTS=64u LWSRP_ATTR_BUCKETS=16u LWSRP_TX_MERGE=1)
if(DEFINED ZEPHYR_BASE)
  if(CONFIG_LWSRP)
    zephyr_library_named(lwsrp)
    zephyr_library_sources(
      src/core/mrp_mad.c
      src/core/mrp_pdu.c
      src/core/switch.c
      src/modules/mvrp.c
      src/modules/mmrp.c
      src/modules/msrp.c
      src/ports/alloc.c
      src/ports/timer.c
    )
    zephyr_include_directories(src/include)
    zephyr_library_include_directories(src)
    zephyr_library_compile_definitions(LWSRP_MILAN=$<BOOL:${LWSRP_MILAN}>)
    if(LWSRP_SCALE)
      zephyr_compile_definitions(${LWSRP_SCALE_DEFINITIONS})
    endif()
  endif()
  return()
endif()

cmake_minimum_required(VERSION 3.20)
project(shish_lan C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

# ---------- shared library (loaded by behave via ctypes) ----------
add_library(shlan SHARED
    src/ports/alloc.c
    src/ports/timer.c
    src/core/mrp_mad.c
    src/core/mrp_pdu.c
    src/core/switch.c
    src/modules/sim_adapter.c
    src/modules/mvrp.c
    src/modules/mmrp.c
    src/modules/msrp.c
    tests/features/switch_bindings.c
    # src/core/hw_adapter.c    (add when hardware driver exists)
)
target_include_directories(shlan PUBLIC src/include src/modules src)
target_compile_definitions(shlan PUBLIC LWSRP_MILAN=$<BOOL:${LWSRP_MILAN}>)
if(LWSRP_SCALE)
  target_compile_definitions(shlan PUBLIC ${LWSRP_SCALE_DEFINITIONS})
endif()

# ---------- unit tests (cgreen, C-only, for core/ internals) ----------
enable_testing()
find_library(CGREEN_LIB cgreen REQUIRED)
find_path(CGREEN_INCLUDE cgreen/cgreen.h REQUIRED)

add_executable(unit_tests
    tests/unit/main.c
    tests/unit/fault_alloc.c
    tests/unit/mrp_pdu_test.c
    tests/unit/timer_test.c
    tests/unit/msrp_values_test.c
    tests/unit/receive_test.c
    tests/unit/transmit_test.c
    tests/unit/integration_test.c
    tests/unit/milan_test.c
    tests/unit/review_test.c
    tests/unit/grouping_test.c
    tests/unit/own_leaveall_test.c
    tests/unit/key_test.c
    tests/unit/mrpdu_decoder.c
)
target_include_directories(unit_tests PRIVATE ${CGREEN_INCLUDE} src/include src)
target_link_libraries(unit_tests PRIVATE shlan ${CGREEN_LIB})
add_test(NAME unit COMMAND unit_tests)
# An empty cgreen suite exits successfully; it must not pass CTest.
set_tests_properties(unit PROPERTIES FAIL_REGULAR_EXPRESSION "No assertions")
