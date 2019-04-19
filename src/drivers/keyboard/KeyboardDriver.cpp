#include <drivers/keyboard/KeyboardDriver.hpp>

KeyboardDriver::KeyboardDriver(InterruptManager* interruptManager, KeyboardEventHandler* keyboardEventHandler) 
    : InterruptHandler(interruptManager, 0x21), 
      dataPort(0x60), 
      commandPort(0x64) {
    this->keyboardEventHandler = keyboardEventHandler;
}

KeyboardDriver::~KeyboardDriver() {}

void KeyboardDriver::activate() {
    while(commandPort.read() & 0x1) {
        dataPort.read();
    }
    commandPort.write(0xae); // activate interrupts
    commandPort.write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataPort.read() | 1) & ~0x10;
    commandPort.write(0x60); // command 0x60 = set controller command byte
    dataPort.write(status);
    dataPort.write(0xf4);
    printf("Activating keyboard event handler\n");
}

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp)
{
    uint8_t key = dataPort.read();
    if (keyboardEventHandler == nullptr) {
        return esp;
    }
    if (key < 0x80) {
        // Key is pressed. Call switch.
        switch(key)
        {
            case 0x02: keyboardEventHandler->onKeyDown('1'); break;
            case 0x03: keyboardEventHandler->onKeyDown('2'); break;
            case 0x04: keyboardEventHandler->onKeyDown('3'); break;
            case 0x05: keyboardEventHandler->onKeyDown('4'); break;
            case 0x06: keyboardEventHandler->onKeyDown('5'); break;
            case 0x07: keyboardEventHandler->onKeyDown('6'); break;
            case 0x08: keyboardEventHandler->onKeyDown('7'); break;
            case 0x09: keyboardEventHandler->onKeyDown('8'); break;
            case 0x0A: keyboardEventHandler->onKeyDown('9'); break;
            case 0x0B: keyboardEventHandler->onKeyDown('0'); break;

            case 0x10: keyboardEventHandler->onKeyDown('q'); break;
            case 0x11: keyboardEventHandler->onKeyDown('w'); break;
            case 0x12: keyboardEventHandler->onKeyDown('e'); break;
            case 0x13: keyboardEventHandler->onKeyDown('r'); break;
            case 0x14: keyboardEventHandler->onKeyDown('t'); break;
            case 0x15: keyboardEventHandler->onKeyDown('y'); break;
            case 0x16: keyboardEventHandler->onKeyDown('u'); break;
            case 0x17: keyboardEventHandler->onKeyDown('i'); break;
            case 0x18: keyboardEventHandler->onKeyDown('o'); break;
            case 0x19: keyboardEventHandler->onKeyDown('p'); break;

            case 0x1E: keyboardEventHandler->onKeyDown('a'); break;
            case 0x1F: keyboardEventHandler->onKeyDown('s'); break;
            case 0x20: keyboardEventHandler->onKeyDown('d'); break;
            case 0x21: keyboardEventHandler->onKeyDown('f'); break;
            case 0x22: keyboardEventHandler->onKeyDown('g'); break;
            case 0x23: keyboardEventHandler->onKeyDown('h'); break;
            case 0x24: keyboardEventHandler->onKeyDown('j'); break;
            case 0x25: keyboardEventHandler->onKeyDown('k'); break;
            case 0x26: keyboardEventHandler->onKeyDown('l'); break;

            case 0x2C: keyboardEventHandler->onKeyDown('z'); break;
            case 0x2D: keyboardEventHandler->onKeyDown('x'); break;
            case 0x2E: keyboardEventHandler->onKeyDown('c'); break;
            case 0x2F: keyboardEventHandler->onKeyDown('v'); break;
            case 0x30: keyboardEventHandler->onKeyDown('b'); break;
            case 0x31: keyboardEventHandler->onKeyDown('n'); break;
            case 0x32: keyboardEventHandler->onKeyDown('m'); break;
            case 0x33: keyboardEventHandler->onKeyDown(','); break;
            case 0x34: keyboardEventHandler->onKeyDown('.'); break;
            case 0x35: keyboardEventHandler->onKeyDown('-'); break;

            case 0x36: keyboardEventHandler->setShiftKey(true);
            case 0x2A: keyboardEventHandler->setShiftKey(true);

            case 0x0E: keyboardEventHandler->backspace(); break;

            case 0x1C: keyboardEventHandler->onKeyDown('\n'); break;
            case 0x39: keyboardEventHandler->onKeyDown(' '); break;

            default:
            {
                char* foo = "KEYBOARD 0x00 ";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0xF];
                foo[12] = hex[key & 0xF];
                printf(foo);
                break;
            }
        }
    } else {
        // Key is released. Call switch.
        switch(key) {

            case 0xAA: keyboardEventHandler->setShiftKey(false);
            case 0xB6: keyboardEventHandler->setShiftKey(false);
            /*
            default:
            {
                char* foo = "RELEASE 0x00 ";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0xF];
                foo[12] = hex[key & 0xF];
                printf(foo);
                break;
            }
            */
            default:
                break;
        }
    }

    return esp;
}