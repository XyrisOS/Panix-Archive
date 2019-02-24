/**
 * File: string.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef STRING_H
#define STRING_H

#include "../../cpu/type.h"

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
 * @param n Int value
 * @param str TODO: Document
 */
void intToString(int n, char str[]);

/**
 * @brief Reverses a string
 * 
 * @param n 
 * @param str 
 */
void intToString(uint32_t n, char str[]);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(uint16_t n, char str[]);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(uint8_t n, char str[]);

/**
 * @brief 
 * 
 * @param s String to reverse
 */
void reverse(char s[]);

/**
 * @brief Compares two strings.
 * 
 * @param s1 String 1
 * @param s2 String 2
 * @return int 
 */
int stringComparison(char s1[], char s2[]);

/**
 * @brief Gets the length of a given string.
 * 
 * @param source 
 * @param destination 
 */
void stringCopy(char source[], char destination[]);

/**
 * @brief 
 * 
 * @param s String to analyze
 * @return int Length return value
 */
int stringLength(char s[]);

#endif /* STRING_H */