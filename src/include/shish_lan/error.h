/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SHISH_LAN_ERROR_H
#define SHISH_LAN_ERROR_H
/* Stable negative API results without a hosted errno or thread-local state. */
enum shlan_error {
    SHLAN_ERROR_NO_MEMORY = 12,
    SHLAN_ERROR_INVALID = 22,
    SHLAN_ERROR_RANGE = 34,
    SHLAN_ERROR_NO_BUFFER = 105,
};
#endif
