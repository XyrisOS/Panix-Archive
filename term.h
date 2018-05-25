//  Terminal management header.
//  term.h
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//

#ifndef term_h
#define term_h
#include "types.h"

// VGA Memory Buffer Address
volatile uint16_t * vMem = (uint16_t *)0xB8000;
// VGA Textmode buffer size
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

void term_clear();
void term_printChar(char c);

#endif /* term_h */
