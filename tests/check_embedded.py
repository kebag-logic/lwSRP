# SPDX-License-Identifier: Apache-2.0
"""Link and exercise the actual embedded source list with a host compiler."""
import argparse
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work-dir", type=Path, required=True)
    args = parser.parse_args()
    work = args.work_dir.resolve()
    if work.is_relative_to(ROOT) or work.exists():
        parser.error("Use a new scratch directory outside the checkout")
    work.mkdir(parents=True)
    (work / "CMakeLists.txt").write_text(r'''# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20)
project(embedded_probe C)
set(ZEPHYR_BASE TRUE)
set(CONFIG_LWSRP TRUE)
function(zephyr_library_named name)
  add_library(${name} STATIC)
endfunction()
function(zephyr_library_sources)
  foreach(source IN LISTS ARGN)
    target_sources(lwsrp PRIVATE "${LWSRP_ROOT}/${source}")
  endforeach()
endfunction()
function(zephyr_include_directories)
  foreach(path IN LISTS ARGN)
    target_include_directories(lwsrp PUBLIC "${LWSRP_ROOT}/${path}")
  endforeach()
endfunction()
function(zephyr_library_include_directories)
  zephyr_include_directories(${ARGN})
endfunction()
function(zephyr_library_compile_definitions)
  target_compile_definitions(lwsrp PRIVATE ${ARGN})
endfunction()
include("${LWSRP_ROOT}/CMakeLists.txt")
add_executable(probe "${LWSRP_ROOT}/tests/embedded_switch.c")
target_link_libraries(probe PRIVATE lwsrp)
''')
    for profile in ["OFF", "ON"]:
        build = work / profile
        commands = [
            ["cmake", "-S", str(work), "-B", str(build),
             f"-DLWSRP_ROOT={ROOT}", f"-DLWSRP_MILAN={profile}"],
            ["cmake", "--build", str(build), "--parallel", "2"],
            [str(build / "probe")],
        ]
        for command in commands:
            result = subprocess.run(command, capture_output=True, text=True, timeout=120)
            print(result.stdout + result.stderr, end="")
            print(f"{profile}: {command}; rc={result.returncode}")
            if result.returncode:
                return 1
    print("Embedded source list: both profile links and dispatch probes pass")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
