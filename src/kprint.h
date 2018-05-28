//  Print function for the EDIX kernel.
//  kprint.h
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef kprint_h
#define kprint_h
#include "types.h"
#include "termcolor.h"

/**
 * Print to the terminal using the given string
 * @param str - String to be printed.
 */
void kprint(const char * str);

/**
 * Print to the terminal using the given string with color
 * @param str - String to be printed
 * @param fore - Foreground color
 * @param back - Background color
 */
void kprint_c(const char * str, char fore, char back);

/**
 * Print an error to the terminal using the given string
 * @param str Error message to be printed
 */
void kprint_error(const char * str);

/**
 * Print a system status to the console
 * @param isLoaded - Boolean determining positive or negative status
 * @param service_name - Name of the service loaded or failed
 */
void kprint_status(bool isLoaded, const char * service_name);

/**
 * Clears the terminal
 */
void kprint_clear();

#endif /* kprint_h */
