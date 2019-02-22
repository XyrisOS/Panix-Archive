/**
 * File: memory.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "string.h"

/**
 * 
 */
void memoryCopy(char* source, char* destination, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(destination + i) = *(source + i);
    }
}

/**
 * 
 */
void memorySet(uint8_t* destination, uint8_t value, uint32_t length) {
    uint8_t *temp = (uint8_t *)destination;
    while (length > 0) {
        *temp++ = value;
        --length;
    }
}