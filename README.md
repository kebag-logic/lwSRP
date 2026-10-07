<!-- SPDX-License-Identifier: Apache-2.0 -->
# lwSRP

lwSRP is a C library for Multiple Registration Protocol state and attribute handling.
It includes VLAN, MAC, and stream registration applications.
Its reference is [IEEE 802.1Q-2018, clauses 10, 11.2, and 35](https://standards.ieee.org/ieee/802.1Q/6844/).

The library is an early integration base.
It has no complete transmit path or hardware adapter.
Read the [implementation status](doc/manager.md#implementation-status) before planning deployment.

## Architecture

~~~mermaid
flowchart TD
    Host[Host application] --> Apps[VLAN / MAC / stream applications]
    Apps --> Core[MRP state and codec]
    Core --> Ports[Allocation and timers]
    Host --> Switch[Switch interface]
    Switch --> Sim[Port simulation]
~~~

The [protocol core](src/core/mrp_mad.c) and [switch interface](src/include/shish_lan/switch.h) are separate integration surfaces.
The [simulation adapter](src/modules/sim_adapter.c) models port enablement only.
See the [architecture guide](doc/architecture.md) for the boundaries.

## Quick start

Use a C11 compiler and [CMake](https://cmake.org/cmake/help/latest/) version 3.20 or newer.
Install [cgreen](https://github.com/cgreen-devs/cgreen) headers and libraries for the required host unit target.
Install [behave](https://behave.readthedocs.io/en/stable/) for scenarios.
Run these commands from the repository root.

~~~sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
behave
~~~

The configured unit target runs nine codec tests with 1690 assertions.
The scenario suite passes three scenarios and ten steps.
The [tester guide](doc/tester.md) explains their coverage and limits.

## Choose your guide

| Reader | Start here |
| --- | --- |
| Developer | [Understand the code and extend an application](doc/developer.md). |
| Integrator | [Connect platform services and plan an adapter](doc/integrator.md). |
| Manager | [Assess scope, gaps, and release readiness](doc/manager.md). |
| Tester | [Run checks and understand coverage](doc/tester.md). |

See the [contribution guide](CONTRIBUTING.md) before submitting changes.

## Licence

lwSRP is licensed under the [Apache License, Version 2.0](LICENSE). Copyright 2026 kebag-logic. See [NOTICE](NOTICE). Individuals and companies may contribute under the same licence.
