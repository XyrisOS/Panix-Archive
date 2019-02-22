/**
 * File: util.cpp
 * Author: Keeton Feavel and James Osborne
 */

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) {
		n = -n;
	}

    for (i = 0; (n /= 10) > 0; i++) {
        str[i++] = n % 10 + '0';
    }

    if (sign < 0) {
		str[i++] = '-';
	}
    str[i] = '\0';
    /* TODO: implement "reverse" */
}
