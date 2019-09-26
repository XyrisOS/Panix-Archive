/**
 * @file stdio.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_LIBC_STDIO
#define PANIX_LIBC_STDIO

/**
 * @brief Panics the kernel and halts the CPU.
 * 
 * @param exception Hex / integer value of exception thrown
 */
void panic(int exception);

#endif /* PANIX_LIBC_STDIO */