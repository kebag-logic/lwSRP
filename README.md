<!-- SPDX-License-Identifier: Apache-2.0 -->
# lwSRP

lwSRP is a C library for Multiple Registration Protocol state and attribute handling.
It includes VLAN, MAC, and stream registration applications.
Its reference is [IEEE 802.1Q-2018, clauses 10, 11.2, and 35](https://standards.ieee.org/ieee/802.1Q/6844/).

The library is an early integration base.
It provides transactional PDU transmission and receive validation.
The host supplies frame transport and hardware policy.
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

Use a [C11 draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) compiler and [CMake](https://cmake.org/cmake/help/latest/) version 3.20 or newer.
Install [cgreen](https://github.com/cgreen-devs/cgreen) headers and libraries for the required host unit target.
Install [behave](https://behave.readthedocs.io/en/stable/) for scenarios.
Set LWSRP_BUILD to a writable build directory outside the checkout.
Set CMAKE_PREFIX_PATH to the unit dependency prefix when it is outside standard locations.
Set LD_LIBRARY_PATH to its library directory when required by your host loader.
Run these commands from the repository root.

~~~sh
cmake -S . -B "$LWSRP_BUILD" -DCMAKE_BUILD_TYPE=Debug -DLWSRP_MILAN=OFF
cmake --build "$LWSRP_BUILD" --parallel 2
ctest --test-dir "$LWSRP_BUILD" --output-on-failure
SHLAN_LIBRARY="$LWSRP_BUILD/libshlan.so" behave
~~~

The default unit target runs 46 tests with 2675 assertions.
The scenario suite passes three scenarios and ten steps.
The [tester guide](doc/tester.md) explains their coverage and limits.
An [optional Milan setting](doc/integrator.md#milan-received-leave) enables immediate withdrawal of received stream registrations.

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
