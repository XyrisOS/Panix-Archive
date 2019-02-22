/**
 * File: memory.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/type.h"

/**
 * 
 */
void memoryCopy(char* source, char* destination, int nbytes);

/**
 * 
 */
void memorySet(uint8_t* destination, uint8_t value, uint32_t length);

#endif /* MEMORY_H */