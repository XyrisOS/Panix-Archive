//  BIOS colors header for EDIX kernel.
//  termcolor.h
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//

#ifndef termcolor_h
#define termcolor_h
#include "types.h"

typedef struct color_foreground {
        char black = 0x00;
        char blue = 0x01;
        char green = 0x02;
        char cyan = 0x03;
        char red = 0x04;
        char magenta = 0x05;
        char brown = 0x06;
        char light_gray = 0x07;
        char dark_gray = 0x08;
        char light_blue = 0x09;
        char light_green = 0x0A;
        char light_cyan = 0x0B;
        char light_red = 0x0C;
        char light_magenta = 0x0D;
        char yellow = 0x0E;
        char white = 0x0F;
} color_foreground;

typedef struct color_background {
        char black = 0x00;
        char blue = 0x10;
        char green = 0x20;
        char cyan = 0x30;
        char red = 0x40;
        char magenta = 0x50;
        char brown = 0x60;
        char light_gray = 0x70;
        char dark_gray = 0x80;
        char light_blue = 0x90;
        char light_green = 0xA0;
        char light_cyan = 0xB0;
        char light_red = 0xC0;
        char light_magenta = 0xD0;
        char yellow = 0xE0;
        char white = 0xF0;
} color_background;

#endif /* termcolor_h */
