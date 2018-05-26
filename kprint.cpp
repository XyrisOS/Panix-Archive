//  Print function for the EDIX kernel.
//  kprint.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "kprint.h"
#include "term.h"

color_foreground fore; // Foreground color
color_background back; // Background color

/**
 * Kernel printing function.
 * char * str - String to be printed.
 */
void kprint(const char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_printChar(str[i]);
    }
}

/**
 * Kernel printing function including color.
 * char * str - String to be printed.
 */
void kprint_c(const char * str, char fore, char back) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore, back);
        term_printChar(str[i]);
    }
}

void kprint_error(const char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore.red, back.white);
        term_printChar(str[i]);
    }
}

/**
 * Clear the terminal.
 */
void kprint_clear() {
    term_clear();
}
