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
/**
 * @brief Panics the kernel and halts the CPU after printing a message.
 * 
 * @param exception Hex / integer value of exception thrown
 * @param msg Custom error message (not exception message)
 */
void panic(int exception, char* msg);
/**
 * @brief Panics the kernel and halts the CPU after printing a message.
 * 
 * @param msg Custom error message
 */
void panic(char* msg);

#endif /* PANIX_LIBC_STDIO */