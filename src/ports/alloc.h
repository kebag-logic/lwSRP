/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHLAN_PROTS_ALLOC_H
#define SHLAN_PROTS_ALLOC_H

#include <stddef.h>

/*
 * Allocation and I/O abstractions for lwSRP.
 *
 * All heap operations and printf usage in the library must go through
 * these wrappers so that the allocator and output sink can be replaced
 * (e.g. for embedded targets or unit-test instrumentation) without
 * touching call sites.
 */

void *shlan_malloc(size_t size);
void *shlan_calloc(size_t nmemb, size_t size);
void  shlan_free(void *ptr);
int   shlan_printf(const char *fmt, ...);

#endif /* SHLAN_PROTS_ALLOC_H */
