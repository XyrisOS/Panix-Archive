#include <libc/kprint.hpp>

uint8_t x = 0;
uint8_t y = 0;

void kprint(const char* str) {    
    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i])
        {
            case 0x08:
                if (x > 0) {
                    x--;
                }
                videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0xFF00) | ' ';
                break;
            case '\n':
                x = 0;
                y++;
                break;
            default:
                videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x >= 80) {
            x = 0;
            y++;
        }
        
        if(y >= 25) {
            for(y = 0; y < 25; y++) {
                for(x = 0; x < 80; x++) {
                    videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ' ';
                }
            }
            x = 0;
            y = 0;
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
        x = 0;
        y = 0;
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