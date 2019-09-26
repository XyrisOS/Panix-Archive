/**
 * @file tty.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <libc/tty.hpp>

void clearScreen() {
    char str[] =  { ' ', '\0' };
    for (int y = 0; y < 80; y++) {
        for (int x = 0; x < 25; x++) {
            kprintAtPosition(str, x, y, true);
        }
    }
}

void printPanicScreen() {
    kprintSetColor(Black, White);
    clearScreen();
    kprint(" ________________________\n");
    kprint("< OH NO! Panix panicked! >\n");
    kprint(" ------------------------\n");
    kprint("        \\   ^__^\n");
    kprint("         \\  (XX)\\_______\n");
    kprint("            (__)\\       )\\/\\\n");
    kprint("                ||----w |\n");
    kprint("                ||     ||\n");
}