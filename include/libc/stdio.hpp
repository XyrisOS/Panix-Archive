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
int puts(const char*);
 
#ifdef __cplusplus
    }
#endif
 
#endif