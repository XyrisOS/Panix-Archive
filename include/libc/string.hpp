#ifndef STRING_H
#define STRING_H

#include <libc/sys/cdefs.hpp>
#include <stddef.h>
 
#ifdef __cplusplus
    extern "C" {
#endif
/**
 * @brief Compares memory at pointer A to pointer B
 * 
 * @param aptr Pointer A
 * @param bptr Pointer B
 * @param size Size of the data
 * @return int Returns -1 if A < B, 1 if B > A and 0 if identical.
 */
int memcmp(const void* aptr, const void* bptr, size_t size);
/**
 * @brief Copys memory from one location to another.
 * 
 * @param dstptr Destination pointer
 * @param srcptr Source pointer
 * @param size Size of the data
 * @return void* Result pointer
 */
void* memcpy(void* dstptr, const void* srcptr, size_t size);
/**
 * @brief Move memory from one location to another.
 * 
 * @param dstptr Destination pointer
 * @param srcptr Source pointer
 * @param size Size of the data
 * @return void* Result pointer
 */
void* memmove(void* dstptr, const void* srcptr, size_t size);
/**
 * @brief Set memory at bufptr to value.
 * 
 * @param bufptr Buffer pointer
 * @param value Value to be set
 * @param size Size of the value
 * @return void* memory pointer
 */
void* memset(void* bufptr, int value, size_t size);
/**
 * @brief Calculates the length of a string.
 * 
 * @param str String to be evaluated.
 * @return size_t Length of str.
 */
size_t strlen(const char* str);
 
#ifdef __cplusplus
    }
#endif
 
#endif