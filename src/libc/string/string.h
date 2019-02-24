/**
 * File: string.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef STRING_H
#define STRING_H

#include "../../cpu/type.h"

/**
 * @brief 
 * 
 * @param s 
 * @param n 
 */
void append(char s[], char n);

/**
 * @brief 
 * 
 * @param s 
 */
void backspace(char s[]);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void hexToString(int n, char str[]);

/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(int n, char str[]);

/**
 * @brief 
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
void intToString(uint8_t n, char str[]);/**
 * @brief 
 * 
 * @param n 
 * @param str 
 */
void intToString(uint8_t n, char str[]);

/**
 * @brief 
 * 
 * @param s 
 */
void reverse(char s[]);

/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int stringComparison(char s1[], char s2[]);

/**
 * @brief 
 * 
 * @param source 
 * @param destination 
 */
void stringCopy(char source[], char destination[]);

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int stringLength(char s[]);

#endif /* STRING_H */