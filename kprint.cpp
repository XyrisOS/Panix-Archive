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
 * @param const char * str - String to be printed.
 */
void kprint(const char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore.white, back.black);
        term_print_char(str[i]);
    }
}

/**
 * Kernel printing function including color.
 * @param const char * str - String to be printed.
 */
void kprint_c(const char * str, char fore, char back) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore, back);
        term_print_char(str[i]);
    }
}

/**
 * Kernel error printing function.
 * @param const char * str - String to be printed.
 */
void kprint_error(const char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore.red, back.white);
        term_print_char(str[i]);
    }
}

/**
 * Clear the terminal.
 */
void kprint_clear() {
    term_init();
}
