/* SPDX-License-Identifier: Apache-2.0 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

void *shlan_malloc(size_t size)
{
    return malloc(size);
}

void *shlan_calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void shlan_free(void *ptr)
{
    free(ptr);
}

int shlan_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = vprintf(fmt, ap);
    va_end(ap);
    return ret;
}
