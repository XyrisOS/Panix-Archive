//  Print function for the EDIX kernel.
//  kprint.h
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef kprint_h
#define kprint_h

#include "types.h"

// Print to the terminal using the given string
void kprint(char* str);
// Clear the terminal
void kprint_clear();

#endif /* kprint_h */
