//  Print function for the EDIX kernel.
//  kprint.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "kprint.h"

/**
 * Kernel printing function.
 * char * str - String to be printed.
 */
extern "C" void kprint(char * str) {
    static uint16_t * vMem = (uint16_t *)0xb8000;
    for (int i = 0; str[i] != '\0'; ++i) {
        vMem[i] = (vMem[i] & 0xFF00) | str[i];
    }
}
