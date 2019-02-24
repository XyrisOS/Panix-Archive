/**
 * File: screen.h
 * Author: Keeton Feavel
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../../cpu/ports.h"
#include "../../libc/memory.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80
// TODO: Move to separate 'colors.h' file like in edix_v1
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define YELLOW_ON_BLACK 0x0e

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
/**
 * @brief 
 * 
 */
void clearScreen();
/**
 * @brief 
 * 
 * @param message 
 */
void kprint(char* message);
/**
 * @brief 
 * 
 * @param message 
 * @param column 
 * @param row 
 */
void kprintAtPosition(char* message, int column, int row);
/**
 * @brief 
 * 
 */
void kprintBackspace();

#endif /* SCREEN_H */