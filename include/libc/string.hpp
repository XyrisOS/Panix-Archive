/**
 * @file string.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_STRING_H
#define PANIX_STRING_H

#include <stddef.h>
#include <common/types.hpp>

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
 * @brief Append a char to a given string.
 * 
 * @param s Destination string
 * @param n Souce character
 */
void append(char* s, char n);

/**
 * @brief Removes the last character from a string
 * 
 * @param s TODO: Document
 */
void backspaceString(char* s);

/**
 * @brief Converts a given hex arrangement into an ASCII string
 * 
 * @param n Integer value of hex data
 * @param str TODO: Document
 */
void hexToString(int n, char* str);

/**
 * @brief Converts a given int into an ASCII string
 * 
 * @param n Int value
 * @param str TODO: Document
 */
void intToString(int n, char* str);

/**
 * @brief Reverses a string
 * 
 * @param n 
 * @param str 
 */
void intToString(uint32_t n, char* str);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(uint16_t n, char* str);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(uint8_t n, char* str);

/**
 * @brief 
 * 
 * @param s String to reverse
 */
void reverse(char* s);

/**
 * @brief Compares two strings.
 * 
 * @param s1 String 1
 * @param s2 String 2
 * @return int 
 */
int strcmp(const char* s1, const char* s2);

/**
 * @brief Copies a string from one to another
 * 
 * @param source 
 * @param destination 
 */
void strcpy(const char* source, char* destination);

/**
 * @brief Returns the length of a string
 * 
 * @param s String to analyze
 * @return int Length return value
 */
int strlen(const char* s);
 
#endif