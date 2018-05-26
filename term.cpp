//  Terminal management header.
//  term.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//

#include "term.h"
#include "termcolor.h"

/**
 *
 * Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC
 * B is the background color
 * F is the foreground color
 * C is the ASCII character
 */

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F; // Black screen with white text
// VGA Memory Buffer Address
volatile uint16_t * vMem = (uint16_t *)0xB8000;

/**
 * Sets the terminal color by ORing the foreground and background
 * which are defined in the termcolor header (termcolor.h).
 */
void term_set_color(char fore, char bkg) {
	term_color = (fore | bkg);
}

/**
 * Initializes the terminal by clearing all existing text.
 */
void term_init() {
	// Clear the textmode buffer
	term_color = 0x0F; // Black screen with white text
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
            // Set the characterd to blank (a space character)
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			// Given this, we find an index into the buffer for our character
			const size_t index = (VGA_COLS * row) + col;
            vMem[index] = ((uint16_t)term_color << 8) | ' ';
		}
	}
}

/**
 * Prints a given character to the terminal by placing it in vMem.
 * Handles \n (new line).
 */
void term_print_char(char c)
{
	switch (c)
	{
	// Newline characters should return the column to 0, and increment the row
	case '\n':
		{
			term_col = 0;
			term_row ++;
			break;
		}
	// Normal characters just get displayed and then increment the column
	default:
		{
			const size_t index = (VGA_COLS * term_row) + term_col; // Like before, calculate the buffer index
            vMem[index] = ((uint16_t)term_color << 8) | c;
			term_col ++;
			break;
		}
	}

	// What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}

	// What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
	if (term_row >= VGA_ROWS)
	{
        // TODO: Move all text "up" by clearing top line and shifting everything. Optional: Clear screen and start again...
        term_init();
		term_col = 0;
		term_row = 0;
	}
}
