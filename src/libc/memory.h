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

/**
 * At this stage there is no 'free' implemented.
 */
uint32_t kmalloc(uint32_t size, int align, uint32_t* physicalAddress);

#endif /* MEMORY_H */