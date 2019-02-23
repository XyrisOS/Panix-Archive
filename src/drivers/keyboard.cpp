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
const char* Keyboard::scancodeName[] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
    "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "[", "]", "Enter", "Lctrl", "A", "S",
    "D", "F", "G", "H", "J", "K", "L", ";",
    "'", "`", "LShift", "\\", "Z", "X", "C", "V",
    "B", "N", "M", ",", ".", "/", "RShift", "Keypad *",
    "LAlt", "Spacebar"
};

void Keyboard::callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = getPortByte(0x60);
    
    if (scancode > SCANCODE_MAX) {
        return;
    }
    if (scancode == BACKSPACE) {
        backspace(Keyboard::keyBuffer);
        kprintBackspace();
    } else if (scancode == ENTER) {
        kprint((char*) "\n");
        handleUserInput(Keyboard::keyBuffer);
        Keyboard::keyBuffer[0] = '\0';
    } else {
        char letter = scancodeAscii[(int) scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(Keyboard::keyBuffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void Keyboard::initialize() {
   registerInterruptHandler(IRQ1, Keyboard::callback); 
}
