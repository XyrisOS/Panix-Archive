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

/**
 * 
 */
void hexToString(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int tmp;
    for (int i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) {
            continue;
        }
        zeros = 1;
        if (tmp > 0xA) {
            append(str, tmp - 0xA + 'a');
        } else {
            append(str, tmp + '0');
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) {
        append(str, tmp - 0xA + 'a');
    } else {
        append(str, tmp + '0');
    }
}

/* K&R */
void intToString(int n, char str[]) {
    int i = 0;
    int sign = n;
    if (sign < 0) {
		n = -n;
	}

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
		str[i++] = '-';
	}

    str[i] = '\0';
    reverse(str);
}

void intToString(uint32_t n, char str[]) {
    int i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    str[i] = '\0';
    reverse(str);
}

void intToString(uint16_t n, char str[]) {
    int i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    str[i] = '\0';
    reverse(str);
}

void intToString(uint8_t n, char str[]) {
    int i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

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

void stringCopy(char source[], char destination[]) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        ++i;
    }
    destination[i] = '\0';
}

/* K&R */
int stringLength(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}