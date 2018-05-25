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
void kprint(char* str);
// Print to the terminal using the given string with color
void kprint_c(char * str, char fore, char back);
// Clear the terminal
void kprint_clear();

#endif /* kprint_h */
