//  Print function for the EDIX kernel.
//  kprint.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "kprint.h"
#include "term.h"

/**
 * Kernel printing function.
 * char * str - String to be printed.
 */
void kprint(char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_printChar(str[i]);
    }
}

/**
 * Clear the terminal.
 */
void kprint_clear() {
    term_clear();
}
