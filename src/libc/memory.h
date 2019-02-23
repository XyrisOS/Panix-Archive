/**
 * File: memory.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/type.h"

/**
 * @brief Copys memory from one location to another.
 * 
 * @param source Source memory address
 * @param destination Destination memory address
 * @param nbytes Number of bytes to copy
 */
void memoryCopy(char* source, char* destination, int nbytes);

/**
 * @brief Sets the memory at a given location.
 * 
 * @param destination Desintation memory address
 * @param value Value to set in memory
 * @param length Length of bytes to set
 */
void memorySet(uint8_t* destination, uint8_t value, uint32_t length);

/**
 * At this stage there is no 'free' implemented.
 */
/**
 * @brief Kernel memory allocation function.
 * 
 * @param size Size of space to allocate
 * @param align Byte alignment
 * @param physicalAddress Physical memory address
 * @return uint32_t TODO: Document
 */
uint32_t kmalloc(uint32_t size, int align, uint32_t* physicalAddress);

#endif /* MEMORY_H */