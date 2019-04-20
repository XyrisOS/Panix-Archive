#ifndef CTYPE_H
#define CTYPE_H

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief Converts a given char array to its uppercase equivalent.
 * 
 * @param string Char array to be capitalized.
 * @return char* Resulting capitalized string.
 */
char* toUpper(char* string);

#ifdef __cplusplus
    }
#endif

#endif /* CTYPE_H */