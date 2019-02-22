/**
 * File: string.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "string.h"

/**
 * 
 */
void append(char s[], char n) {
    int length = stringLength(s);
    s[length] = n;
    s[length + 1] = '\0';
}

/**
 * 
 */
void backspace(char s[]) {
    int length = stringLength(s);
    s[length - 1] = '\0';
}

/* K&R */
void intToString(int n, char str[]) {
    int sign;
    if ((sign = n) < 0) {
		n = -n;
	}

    int i;
    for (i = 0; (n /= 10) > 0; i++) {
        str[i++] = n % 10 + '0';
    }

    if (sign < 0) {
		str[i++] = '-';
	}
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c;
    int j = stringLength(s) - 1;
    for (int i = 0; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R 
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int stringComparison(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return s1[i] - s2[i];
}

/* K&R */
int stringLength(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}