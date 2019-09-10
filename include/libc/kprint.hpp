#ifndef PANIX_KPRINT_HPP
#define PANIX_KPRINT_HPP

#include <types.hpp>

inline uint16_t* videoMemory = (uint16_t*) 0xb8000;
/**
 * @brief Prints a given string to the kernel display.
 * 
 * @param str Input string to be printed.
 */
void kprint(const char* str);
/**
 * @brief Prints a given string to a particular coordinate in the kernel display.
 * 
 * @param str Input string to be printed.
 * @param x X-coordinate of the kernel display.
 * @param y Y-coordinate of the kernel display.
 * @param resetCursor Determines whether or not the cursor should be reset to the starting position.
 */
void kprintAtPosition(const char* str, uint8_t x, uint8_t y, bool resetCursor = false);
/**
 * @brief Prints a hexidecimal address to the kernel console.
 * 
 * @param key Hexidecimal value to print.
 */
void kprintHex(uint8_t key);

#endif /* PANIX_KPRINT_HPP */