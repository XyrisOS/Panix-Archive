/**
 * File: keyboard.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "keyboard.h"

const char Keyboard::scancodeAscii[] = { 
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', '?', '?', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '?',
    '?', ' '
};
const char Keyboard::scancodeName[64][16] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
    "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "[", "]", "Enter", "Lctrl", "A", "S",
    "D", "F", "G", "H", "J", "K", "L", ";",
    "'", "`", "LShift", "\\", "Z", "X", "C", "V",
    "B", "N", "M", ",", ".", "/", "RShift", "Keypad *",
    "LAlt", "Spacebar"
};

char* keyBuffer = (char*) "\0";

char* lastCommand = (char*) "\0";

int lengthOfCurrentCommand = 0;

/*******************
* Public Functions *
********************/
void Keyboard::callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = getPortByte(0x60);
    if (scancode == UP_ARROW && stringLength(lastCommand) > 0) {
        while (lengthOfCurrentCommand > 0) {
            Screen::kprintBackspace();
            --lengthOfCurrentCommand;
        }
        stringCopy(lastCommand, keyBuffer);
        lengthOfCurrentCommand = stringLength(lastCommand);
        Screen::kprint(lastCommand);
        return;
    }
    if (scancode > SCANCODE_MAX) {
        return;
    }
    if (scancode == BACKSPACE) {
        if (lengthOfCurrentCommand > 0) {
            --lengthOfCurrentCommand;
            backspace(Keyboard::keyBuffer);
            Screen::kprintBackspace();
        }
    } else if (scancode == ENTER) {
        Screen::kprint((char*) "\n");
        handleUserInput(Keyboard::keyBuffer);
        if (lengthOfCurrentCommand >= 256) {
            lengthOfCurrentCommand = 255;
        }
        keyBuffer[lengthOfCurrentCommand] = '\0';
        stringCopy(Keyboard::keyBuffer, lastCommand);
        lengthOfCurrentCommand = 0;
        Keyboard::keyBuffer[0] = '\0';
    } else {
        char letter = scancodeAscii[(int) scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(Keyboard::keyBuffer, letter);
        Screen::kprint(str);
        ++lengthOfCurrentCommand;
    }
    UNUSED(regs);
}

void Keyboard::initialize() {
   registerInterruptHandler(IRQ1, Keyboard::callback); 
}
