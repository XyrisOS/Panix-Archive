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

// Print to the terminal using the given string
void kprint(const char* str);
// Print to the terminal using the given string with color
void kprint_c(const char * str, char fore, char back);
// Print an error to the terminal using the given string
void kprint_error(const char * str);
// Clear the terminal
void kprint_clear();

#endif /* kprint_h */
