/**
 * File: screen.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../../cpu/ports/ports.h"
#include "../../libc/memory/memory.h"
#include "../driver.h"
#include "colors.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

class Screen : public Driver {
    public:
        /**
         * @brief Clears the screen
         * 
         */
        static void clearScreen();

        /**
         * @brief Prints a string at current cursor position
         * 
         * @param message 
         */
        static void kprint(char* message);

        /**
         * @brief Prints a string at specified position
         * 
         * @param message String to print
         * @param column Column to start printing at, a value of -1 will print at cursor position
         * @param row Row to start printing at, a value of -1 will print at cursor position
         */
        static void kprintAtPosition(char* message, int column = -1, int row = -1);

        /**
         * @brief Moves the cursor back one column and removes last printed character
         * 
         */
        static void kprintBackspace();
    
    private:
        /**
         * @brief Get the cursor's video memory offset
         * 
         * @return int The cursor's video memory offset
         */
        static int getCursorOffset();

        /**
         * @brief Get the video memory offset of a specified position
         * 
         * @param column The column to get the video memory offset of
         * @param row The row to get the video memory offset of
         * @return int The cursor offset in video memory
         */
        static int getOffset(int column, int row);

        /**
         * @brief Get the video memory offset of a specified row
         * 
         * @param offset The video memory offset to get the row of
         * @return int The row of the video memory offset
         */
        static int getOffsetRow(int offset);

        /**
         * @brief Get the video memory offset of a column
         * 
         * @param offset The video memory offset to get the column of
         * @return int The column of the video memory offset
         */
        static int getOffsetColumn(int offset);

        /**
         * @brief Print a single character at the specified position
         * 
         * @param c Character to print
         * @param column Column to print at, a value of -1 will print at cursor position
         * @param row Row to print at, a value of -1 will print at cursor position
         * @param color Color to print the character as
         * @return int The cursor's new video memory offset after printing the character
         */
        static int printCharacter(char c, int column = -1, int row = -1, char color = WHITE_ON_BLACK);

        /**
         * @brief Set the cursor's video memory offset
         * 
         * @param offset The video memory offset to move the cursor to
         */
        static void setCursorOffset(int offset);
};

#endif /* SCREEN_H */