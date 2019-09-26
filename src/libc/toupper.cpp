/**
 * @file toupper.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <libc/ctype.hpp>

char* toUpper(char* string) {
    for(char* p=string; *p != '\0'; p++) {
        if(*p >= 'a' && *p <= 'z') {  //Only if it's a lower letter
          *p -= 32;
        }
    }
    return string;
}