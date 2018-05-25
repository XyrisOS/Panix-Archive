//  Terminal management header.
//  term.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//

#include "term.h"

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F; // Black background, White foreground
// VGA Memory Buffer Address
volatile uint16_t * vMem = (uint16_t *)0xB8000;

/**
 * Initializes the terminal by clearing all existing text.
 */
void term_clear() {
	// Clear the textmode buffer
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			// Given this, we find an index into the buffer for our character
			const size_t index = (VGA_COLS * row) + col;
			// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
			// - B is the background color
			// - F is the foreground color
			// - C is the ASCII character
		 vMem[index] = ((uint16_t)term_color << 8) | ' '; // Set the character to blank (a space character)
		}
	}
}

/**
 * Prints a given character to the terminal by placing it in vMem.
 * Handles \n (new line).
 */
void term_printChar(char c)
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
		term_col = 0;
		term_row = 0;
	}
}