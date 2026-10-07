/* SPDX-License-Identifier: Apache-2.0 */
/* Executable symbols replace the shared library's hosted allocation port. */
#include <stdlib.h>
#include "ports/alloc.h"
#include "fault_alloc.h"

static unsigned remaining;
static unsigned failures;
static size_t live;
void allocation_fail_after(unsigned count)
{
    remaining = count;
    failures = 0;
}
unsigned allocation_failures(void)
{
    return failures;
}
size_t allocation_live(void)
{
    return live;
}
static int fail_now(void)
{
    if (remaining && --remaining == 0) {
        ++failures;
        return 1;
    }
    return 0;
}
void *shlan_malloc(size_t size)
{
    void *p = fail_now() ? NULL : malloc(size);
    if (p) {
        ++live;
    }
    return p;
}
void *shlan_calloc(size_t count, size_t size)
{
    void *p = fail_now() ? NULL : calloc(count, size);
    if (p) {
        ++live;
    }
    return p;
}
void shlan_free(void *p)
{
    if (p) {
        --live;
    }
    free(p);
}
