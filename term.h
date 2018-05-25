//  Terminal management header.
//  term.h
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//

#ifndef term_h
#define term_h
#include "types.h"

// VGA Textmode buffer size
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// Clear the terminal.
void term_clear();
// Print a given character to the terminal. Handles \n.
void term_printChar(char c);

#endif /* term_h */
