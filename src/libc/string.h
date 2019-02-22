/**
 * File: string.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef STRING_H
#define STRING_H

#include "../cpu/type.h"

/**
 * 
 */
void append(char s[], char n);

/**
 * 
 */
void backspace(char s[]);

/**
 * 
 */
void intToString(int n, char str[]);

/**
 * 
 */
void reverse(char s[]);

/**
 * 
 */
int stringComparison(char s1[], char s2[]);

/**
 * 
 */
int stringLength(char s[]);

#endif /* STRING_H */