# SPDX-License-Identifier: Apache-2.0
if(DEFINED ZEPHYR_BASE)
  if(CONFIG_LWSRP)
    zephyr_library_named(lwsrp)
    zephyr_library_sources(
      src/core/mrp_mad.c
      src/core/mrp_pdu.c
      src/modules/mvrp.c
      src/modules/mmrp.c
      src/modules/msrp.c
      src/ports/alloc.c
      src/ports/timer.c
    )
    zephyr_include_directories(src/include)
    zephyr_library_include_directories(src)
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
    # src/core/hw_adapter.c    (add when hardware driver exists)
)
target_include_directories(shlan PUBLIC src/include src/modules src)

# ---------- unit tests (cgreen, C-only, for core/ internals) ----------
enable_testing()
find_library(CGREEN_LIB cgreen)
find_path(CGREEN_INCLUDE cgreen/cgreen.h)

if(CGREEN_LIB AND CGREEN_INCLUDE)
    add_executable(unit_tests tests/unit/placeholder.c tests/unit/mrp_pdu_test.c)
    target_include_directories(unit_tests PRIVATE ${CGREEN_INCLUDE} src/include)
    target_link_libraries(unit_tests PRIVATE shlan ${CGREEN_LIB})
    add_test(NAME unit COMMAND unit_tests)
endif()
