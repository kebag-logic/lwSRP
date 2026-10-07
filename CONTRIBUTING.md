<!-- SPDX-License-Identifier: Apache-2.0 -->
# Contributing

Individuals and companies may contribute under the [Apache License, Version 2.0](LICENSE).
Contributions use the same licence as the project.
Read the [notice](NOTICE) and the [implementation status](doc/manager.md#implementation-status).

## Coding rules

Use braces for every conditional and loop body.
This includes bodies with one statement.
Declare enums with tags.
Do not use typedef enums.
Put each enum element on its own line.
Prefix each element with the uppercase enum name and an underscore.

~~~c
enum port_state {
    PORT_STATE_IDLE = 0,
    PORT_STATE_ACTIVE,
};

if (ready) {
    state = PORT_STATE_ACTIVE;
}
~~~

Use the [allocation and print port](src/ports/alloc.h) for platform services.
Use the [timer port](src/ports/timer.h) for scheduled callbacks.
Keep application policy behind the [application interface](src/include/shish_lan/mrp.h).
See the [extension steps](doc/developer.md#add-an-application) before adding protocol behavior.

## Documentation rules

Keep each sentence at 25 words or fewer.
Make every standard, file, function, issue, and tool reference a link.
Use small graphs with short labels.
Keep each graph to about 15 nodes or fewer.
Give each graph one purpose and nearby links to its evidence.
Start each new Markdown page with the existing SPDX comment.
Keep machine syntax inside fenced examples.
Link its references in the surrounding prose.
Do not include private infrastructure details or generated assets.

## Pull requests

~~~mermaid
flowchart TD
    Scope[Describe scope] --> Change[Make focused changes]
    Change --> Check[Run checks]
    Check --> Review[Submit evidence]
    Review --> Decision[Maintainer review]
~~~

Discuss scope through the [issue tracker](https://github.com/kebag-logic/lwSRP/issues).
Use a focused branch and explain the resulting behavior.
Link the affected requirement and the relevant source.
Run the [test commands](doc/tester.md#run-the-suites) and [documentation checks](doc/tools/README.md).
Record exit codes and failures in the pull request.
Do not describe an empty suite as protocol coverage.
Use one-line commit subjects without bodies or trailers.
Submit through the [pull request list](https://github.com/kebag-logic/lwSRP/pulls).
Maintainers review scope, evidence, and licence compatibility before merging.
