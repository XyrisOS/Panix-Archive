/**
 * File: memory.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "../../cpu/type.h"

/**
 * @brief 
 * 
 * @param source 
 * @param destination 
 * @param nbytes 
 */
void memoryCopy(char* source, char* destination, int nbytes);

/**
 * @brief 
 * 
 * @param destination 
 * @param value 
 * @param length 
 */
void memorySet(uint8_t* destination, uint8_t value, uint32_t length);

/**
 * At this stage there is no 'free' implemented.
 */
/**
 * @brief 
 * 
 * @param size 
 * @param align 
 * @param physicalAddress 
 * @return uint32_t 
 */
uint32_t kmalloc(uint32_t size, int align, uint32_t* physicalAddress);

#endif /* MEMORY_H */