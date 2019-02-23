/**
 * File: string.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef STRING_H
#define STRING_H

#include "../cpu/type.h"

/**
 * @brief Append a char to a given string.
 * 
 * @param s Destination string
 * @param n Souce character
 */
void append(char s[], char n);

/**
 * @brief "Prints" a backspace to the kernel console.
 * 
 * @param s TODO: Document
 */
void backspace(char s[]);

/**
 * @brief Converts a given hex arrangement into an ASCII string
 * 
 * @param n Integer value of hex data
 * @param str TODO: Document
 */
void hexToString(int n, char str[]);

/**
 * @brief Converts a given int into an ASCII string
 * 
 * @param n 
 * @param str 
 */
void intToString(int n, char str[]);

/**
 * @brief Reverses a string
 * 
 * @param s 
 */
void reverse(char s[]);

/**
 * @brief Compares two strings.
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int stringComparison(char s1[], char s2[]);

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int stringLength(char s[]);

#endif /* STRING_H */