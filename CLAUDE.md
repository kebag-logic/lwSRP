# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Coding Style Rules

### Braces Required
All `if`, `while`, and `for` control flow statements MUST use braces `{}`, even for single-line or two-line bodies. Never write braceless control flow.

Bad:
```c
if (x) do_something();

if (x)
    do_something();

for (int i = 0; i < n; i++)
    do_something(i);

while (cond)
    do_something();
```

Good:
```c
if (x) {
    do_something();
}

for (int i = 0; i < n; i++) {
    do_something(i);
}

while (cond) {
    do_something();
}
```

### No typedef enums — multi-line — prefixed elements
Do not use `typedef enum`. Declare enums with a tag name and without typedef.
Every enum must span multiple lines (one element per line).
Each element must be named `ENUM_NAME_ELEMENT` (uppercase enum name, underscore, element name).

Bad:
```c
typedef enum { FOO_A, FOO_B } foo_t;
typedef enum { FOO_A, FOO_B } foo_t;  /* single line */
enum foo { A, B };                      /* elements not prefixed */
```

Good:
```c
enum foo_state {
    FOO_STATE_IDLE = 0,
    FOO_STATE_RUNNING,
    FOO_STATE_DONE,
};
```

