//  Print function for the EDIX kernel.
//  kprint.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "kprint.h"
#include "term.h"

color_foreground fore; // Foreground color
color_background bkg; // Background color

/**
 * Kernel printing function.
 * @param const char * str - String to be printed.
 */
void kprint(const char * str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        // Use term class to print to terminal
        term_set_color(fore.white, bkg.black);
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
        term_set_color(fore.red, bkg.white);
        term_print_char(str[i]);
    }
}

/**
 * 
 * @param isLoaded Boolean identifying if the service loaded correctly
 * @param str Service name
 */
void kprint_status(bool isLoaded, const char * service_name) {
    kprint("[ ");
    // Determine text color based on service loading
    if (isLoaded) {
        // Service loaded correctly
        kprint_c("PASSED", fore.green, bkg.black);
    } else {
        // Service failed to load
        kprint_c("FAILED", fore.red, bkg.black);
    }
    kprint(" ] ");
    kprint(service_name);
    kprint("\n");
}

/**
 * Clear the terminal.
 */
void kprint_clear() {
    term_init();
}
