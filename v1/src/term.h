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
const uint8_t VGA_COLS = 80;
const uint8_t VGA_ROWS = 25;

/**
 * Sets the terminal color by ORing the foreground and background
 * which are defined in the termcolor header (termcolor.h).
 * @param fore - Foreground color
 * @param bkg - Background color
 */
void term_set_color(char fore, char bkg);

/**
 * Initializes and clears the terminal.
 */
void term_init();

/**
 * Prints a given character to the terminal by placing it in vMem.
 * Handles \n (new line).
 * @param c - Character to be printed to the terminal.
 */
void term_print_char(char c);

#endif /* term_h */
