#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"

void printLetter(uint8_t scancode);

static void keyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    char* scancodeString;
    int_to_ascii(scancode, scancodeString);
    kprint((char*) "Keyboard scancode: ");
    kprint(scancodeString);
    kprint((char*) ", ");
    printLetter(scancode);
    kprint((char*) "\n");
}

void initKeyboard() {
   registerInterruptHandler(IRQ1, keyboardCallback); 
}

void printLetter(uint8_t scancode) {
    switch (scancode) {
        case 0x0:
            kprint((char*) "ERROR");
            break;
        case 0x1:
            kprint((char*) "ESC");
            break;
        case 0x2:
            kprint((char*) "1");
            break;
        case 0x3:
            kprint((char*) "2");
            break;
        case 0x4:
            kprint((char*) "3");
            break;
        case 0x5:
            kprint((char*) "4");
            break;
        case 0x6:
            kprint((char*) "5");
            break;
        case 0x7:
            kprint((char*) "6");
            break;
        case 0x8:
            kprint((char*) "7");
            break;
        case 0x9:
            kprint((char*) "8");
            break;
        case 0x0A:
            kprint((char*) "9");
            break;
        case 0x0B:
            kprint((char*) "0");
            break;
        case 0x0C:
            kprint((char*) "-");
            break;
        case 0x0D:
            kprint((char*) "+");
            break;
        case 0x0E:
            kprint((char*) "Backspace");
            break;
        case 0x0F:
            kprint((char*) "Tab");
            break;
        case 0x10:
            kprint((char*) "Q");
            break;
        case 0x11:
            kprint((char*) "W");
            break;
        case 0x12:
            kprint((char*) "E");
            break;
        case 0x13:
            kprint((char*) "R");
            break;
        case 0x14:
            kprint((char*) "T");
            break;
        case 0x15:
            kprint((char*) "Y");
            break;
        case 0x16:
            kprint((char*) "U");
            break;
        case 0x17:
            kprint((char*) "I");
            break;
        case 0x18:
            kprint((char*) "O");
            break;
        case 0x19:
            kprint((char*) "P");
            break;
		case 0x1A:
			kprint((char*) "[");
			break;
		case 0x1B:
			kprint((char*) "]");
			break;
		case 0x1C:
			kprint((char*) "ENTER");
			break;
		case 0x1D:
			kprint((char*) "LCtrl");
			break;
		case 0x1E:
			kprint((char*) "A");
			break;
		case 0x1F:
			kprint((char*) "S");
			break;
        case 0x20:
            kprint((char*) "D");
            break;
        case 0x21:
            kprint((char*) "F");
            break;
        case 0x22:
            kprint((char*) "G");
            break;
        case 0x23:
            kprint((char*) "H");
            break;
        case 0x24:
            kprint((char*) "J");
            break;
        case 0x25:
            kprint((char*) "K");
            break;
        case 0x26:
            kprint((char*) "L");
            break;
        case 0x27:
            kprint((char*) ";");
            break;
        case 0x28:
            kprint((char*) "'");
            break;
        case 0x29:
            kprint((char*) "`");
            break;
		case 0x2A:
			kprint((char*) "LShift");
			break;
		case 0x2B:
			kprint((char*) "\\");
			break;
		case 0x2C:
			kprint((char*) "Z");
			break;
		case 0x2D:
			kprint((char*) "X");
			break;
		case 0x2E:
			kprint((char*) "C");
			break;
		case 0x2F:
			kprint((char*) "V");
			break;
        case 0x30:
            kprint((char*) "B");
            break;
        case 0x31:
            kprint((char*) "N");
            break;
        case 0x32:
            kprint((char*) "M");
            break;
        case 0x33:
            kprint((char*) ",");
            break;
        case 0x34:
            kprint((char*) ".");
            break;
        case 0x35:
            kprint((char*) "/");
            break;
        case 0x36:
            kprint((char*) "Rshift");
            break;
        case 0x37:
            kprint((char*) "Keypad *");
            break;
        case 0x38:
            kprint((char*) "LAlt");
            break;
        case 0x39:
            kprint((char*) "Spc");
            break;
        default:
            /* 'keyup' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                kprint((char*) "Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                kprint((char*) "key up ");
                printLetter(scancode - 0x80);
            } else kprint((char*) "Unknown key up");
            break;
    }
}
