/**
 * File: util.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "util.h"

/**
 * 
 */
void memory_copy(char* source, char* destination, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(destination + i) = *(source + i);
    }
}

/**
 * 
 */
void memory_set(uint8_t* destination, uint8_t value, uint32_t length) {
    uint8_t *temp = (uint8_t *)destination;
    while (length > 0) {
        *temp++ = value;
        --length;
    }
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i;
    int sign;
    if ((sign = n) < 0) {
		n = -n;
	}

    for (i = 0; (n /= 10) > 0; i++) {
        str[i++] = n % 10 + '0';
    }

    if (sign < 0) {
		str[i++] = '-';
	}
    str[i] = '\0';
    /* TODO: implement "reverse" */
}
