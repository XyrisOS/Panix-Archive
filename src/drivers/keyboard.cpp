#include "keyboard.h"

void printLetter(uint8_t scancode);

static void keyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = getPortByte(0x60);
    
    if (scancode > SCANCODE_MAX) {
        return;
    }
    if (scancode == BACKSPACE) {
        backspace(keyBuffer);
        kprintBackspace();
    } else if (scancode == ENTER) {
        kprint((char*) "\n");
        handleUserInput(keyBuffer);
        keyBuffer[0] = '\0';
    } else {
        char letter = scancodeAscii[(int) scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(keyBuffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void initKeyboard() {
   registerInterruptHandler(IRQ1, keyboardCallback); 
}
