#include <libc/ctype.hpp>

/**
 * @brief 
 * 
 * @param string 
 * @return char* 
 */
char* toUpper(char* string) {
    for(char* p=string; *p != '\0'; p++) {
        if(*p >= 'a' && *p <= 'z') {  //Only if it's a lower letter
          *p -= 32;
        }
    }
    return string;
}