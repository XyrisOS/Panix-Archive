/**
 * File: screen.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "screen.h"

/*******************
* Public Functions *
********************/

void Screen::clearScreen() {
    int screen_size = MAX_COLUMNS * MAX_ROWS;
    char* screen = (char*) VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    setCursorOffset(getOffset(0, 0));
}

void Screen::kprint(char *message) {
    kprintAtPosition(message, -1, -1);
}

void Screen::kprintAtPosition(char* message, int column, int row) {
    /* Set cursor if column/row are negative */
    int offset;
    if (column >= 0 && row >= 0) {
        offset = getOffset(column, row);
    } else {
        offset = getCursorOffset();
        row = getOffsetRow(offset);
        column = getOffsetColumn(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = printCharacter(message[i++], column, row, YELLOW_ON_BLACK);   // TODO: Make color dynamic
        /* Compute row/column for next iteration */
        row = getOffsetRow(offset);
        column = getOffsetColumn(offset);
    }
}

void Screen::kprintBackspace() {
    int offset = getCursorOffset() - 2;
    int row = getOffsetRow(offset);
    int column = getOffsetColumn(offset);

    printCharacter(0x08, column, row, WHITE_ON_BLACK);
}

/********************
* Private Functions *
*********************/

int Screen::getCursorOffset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    setPortByte(REG_SCREEN_CTRL, 14);
    int offset = getPortByte(REG_SCREEN_DATA) << 8; 	/* High byte: << 8 */
    setPortByte(REG_SCREEN_CTRL, 15);
    offset += getPortByte(REG_SCREEN_DATA);

    return offset * 2; 									/* Position * size of character cell */
}

int Screen::getOffset(int column, int row) { 
	return 2 * (row * MAX_COLUMNS + column);
}

int Screen::getOffsetRow(int offset) {
	return offset / (2 * MAX_COLUMNS);
}

int Screen::getOffsetColumn(int offset) {
	return (offset - (getOffsetRow(offset) * 2 * MAX_COLUMNS)) / 2;
}

int Screen::printCharacter(char c, int column, int row, char color) {
    uint8_t* videoMemory = (uint8_t*) VIDEO_ADDRESS;
    if (!color) {
        color = WHITE_ON_BLACK;
    }

    /* Error control: print a red 'E' if the coords aren't right */
    if (column >= MAX_COLUMNS || row >= MAX_ROWS) {
        videoMemory[2 * (MAX_COLUMNS) * (MAX_ROWS) - 2] = 'E';
        videoMemory[2 * (MAX_COLUMNS) * (MAX_ROWS) - 1] = RED_ON_WHITE;
        return getOffset(column, row);
    }

    int offset;
    if (column >= 0 && row >= 0) {
        offset = getOffset(column, row);
    } else {
        offset = getCursorOffset();
    }

    switch(c) {
        case '\n':
            row = getOffsetRow(offset);
            offset = getOffset(0, row + 1);
            break;
        case 0x08:
            videoMemory[offset] = ' ';
            videoMemory[offset + 1] = color;
            break;
        default:
            videoMemory[offset] = c;
            videoMemory[offset + 1] = color;
            offset += 2;
            break;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLUMNS * 2) {
        for (int i = 1; i < MAX_ROWS; i++) {
            memoryCopy(((char*) getOffset(0, i)) + VIDEO_ADDRESS,
                       ((char*) getOffset(0, i - 1)) + VIDEO_ADDRESS,
                       MAX_COLUMNS * 2);
        }

        /* Blank last line */
        char* lastLine = ((char*) getOffset(0, MAX_ROWS - 1)) + VIDEO_ADDRESS;
        for (int i = 0; i < MAX_COLUMNS * 2; i++) {
            lastLine[i] = 0;
        }

        offset -= 2 * MAX_COLUMNS;
    }

    setCursorOffset(offset);
    return offset;
}

void Screen::setCursorOffset(int offset) {
    /* Similar to getCursorOffset, but instead of reading we write data */
    offset /= 2;
    setPortByte(REG_SCREEN_CTRL, 14);
    setPortByte(REG_SCREEN_DATA, (uint8_t) (offset >> 8));
    setPortByte(REG_SCREEN_CTRL, 15);
    setPortByte(REG_SCREEN_DATA, (uint8_t) (offset & 0xff));
}
