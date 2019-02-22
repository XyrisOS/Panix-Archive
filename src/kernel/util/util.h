/**
 * File: util.c
 * Author: Keeton Feavel
 */

#ifndef UTIL_H
#define UTIL_H

#include "../../cpu/types.h"

/**
 * 
 */
void memory_copy(char* source, char* destination, int nbytes);

/**
 * 
 */
void memory_set(uint8_t* destination, uint8_t value, uint32_t length);

/**
 * 
 */
void int_to_ascii(int n, char str[]);

#endif // !UTIL_H