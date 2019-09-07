#include <libc/kprint.hpp>

uint8_t ttyCoordsX = 0;
uint8_t ttyCoordsY = 0;

void kprint(const char* str) {    
    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i])
        {
            case 0x08:
                if (ttyCoordsX > 0) {
                    ttyCoordsX--;
                }
                videoMemory[80 * ttyCoordsY + ttyCoordsX] = (videoMemory[80 * ttyCoordsY + ttyCoordsX] & 0xFF00) | ' ';
                break;
            case '\n':
                ttyCoordsX = 0;
                ttyCoordsY++;
                break;
            default:
                videoMemory[80*ttyCoordsY+ttyCoordsX] = (videoMemory[80*ttyCoordsY+ttyCoordsX] & 0xFF00) | str[i];
                ttyCoordsX++;
                break;
        }
        
        if(ttyCoordsX >= 80) {
            ttyCoordsX = 0;
            ttyCoordsY++;
        }
        
        if(ttyCoordsY >= 25) {
            for(ttyCoordsY = 0; ttyCoordsY < 25; ttyCoordsY++) {
                for(ttyCoordsX = 0; ttyCoordsX < 80; ttyCoordsX++) {
                    videoMemory[80*ttyCoordsY+ttyCoordsX] = (videoMemory[80*ttyCoordsY+ttyCoordsX] & 0xFF00) | ' ';
                }
            }
            ttyCoordsX = 0;
            ttyCoordsY = 0;
        }
    }
}

void kprintAtPosition(const char* str, uint8_t positionX, uint8_t positionY, bool resetCursor) {
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case 0x08:
                if (positionX > 0) {
                    positionX--;
                }
                videoMemory[80 * positionY + positionX] = (videoMemory[80 * positionY + positionX] & 0xFF00) | ' ';
                break;
            case '\n':
                positionX = 0;
                positionY++;
                break;
            default:
                videoMemory[80*positionY+positionX] = (videoMemory[80*positionY+positionX] & 0xFF00) | str[i];
                positionX++;
                break;
        }
        
        if(positionX >= 80) {
            positionX = 0;
            positionY++;
        }
        
        if(positionY >= 25) {
            for(positionY = 0; positionY < 25; positionY++) {
                for(positionX = 0; positionX < 80; positionX++) {
                    videoMemory[80*positionY+positionX] = (videoMemory[80*positionY+positionX] & 0xFF00) | ' ';
                }
            }
            positionX = 0;
            positionY = 0;
        }
    }

    if (resetCursor) {
        ttyCoordsX = 0;
        ttyCoordsY = 0;
    }
}

void kprintHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    kprint(foo);
}