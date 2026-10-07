/* SPDX-License-Identifier: Apache-2.0 */
#ifndef TEST_FAULT_ALLOC_H
#define TEST_FAULT_ALLOC_H
#include <stddef.h>
/* Fail exactly the Nth following allocation. Zero disables injection. */
void allocation_fail_after(unsigned count);
size_t allocation_live(void);
#endif
