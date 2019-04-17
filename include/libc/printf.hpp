#ifndef PRINTF_HPP
#define PRINTF_HPP

#include <types.hpp>

inline uint16_t* videoMemory = (uint16_t*) 0xb8000;

void printf(const char* str);
void printfAtPosition(const char* str, uint8_t x, uint8_t y, bool resetCursor = false);

#endif /* PRINTF_HPP */