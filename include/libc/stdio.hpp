#ifndef STDIO_H
#define STDIO_H
 
#include <libc/sys/cdefs.hpp>
#include <libc/printf.hpp>
#define EOF (-1)
 
#ifdef __cplusplus
    extern "C" {
#endif
// TODO: Need to port these to use our pre-made printf
//int printf(const char* __restrict, ...);
//int putchar(int);
/**
 * @brief Prints a given string to the kernel console. Simply calls printf.
 * 
 * @return int Always returns 0 for now.
 */
int puts(const char*);
 
#ifdef __cplusplus
    }
#endif
 
#endif