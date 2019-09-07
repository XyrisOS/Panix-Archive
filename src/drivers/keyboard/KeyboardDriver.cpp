#include <drivers/keyboard/KeyboardDriver.hpp>

const char scancodeAscii[] = {
    '\0', '`', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\0', '?',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\0', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '\0', '\0',
    '\0', ' '
};
const char scancodeName[64][16] = {
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
    kprint("Activating keyboard event handler\n");
}

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp)
{
    uint8_t scancode = dataPort.read();
    if (keyboardEventHandler == nullptr) {
        return esp;
    }
    // If a scancode is pressed down
    if (scancode < 0x80) {
        // 
        if (scancode == UP_ARROW && strlen(lastCommand) > 0) {
            while (lengthOfCurrentCommand > 0) {
                keyboardEventHandler->backspace();
                --lengthOfCurrentCommand;
            }
            strcpy(lastCommand, keyBuffer);
            lengthOfCurrentCommand = strlen(lastCommand);
            kprint(lastCommand);
            return esp;
        }
        if (scancode > SCANCODE_MAX) {
            return esp;
        }
        if (scancode == BACKSPACE) {
            if (lengthOfCurrentCommand > 0) {
                --lengthOfCurrentCommand;
                backspace(keyBuffer);
                keyboardEventHandler->backspace();
            }
        }
        if (scancode == ENTER) {
            kprint("\n");
            // TODO: Find a way to get this to the shell
            if (this->console != nullptr) {
                this->console->handleShellInput(keyBuffer);
            }
            if (lengthOfCurrentCommand >= 256) {
                lengthOfCurrentCommand = 255;
            }
            keyBuffer[lengthOfCurrentCommand] = '\0';
            strcpy(keyBuffer, lastCommand);
            lengthOfCurrentCommand = 0;
            keyBuffer[0] = '\0';
        }
        if (scancode == RIGHT_SHIFT || scancode == LEFT_SHIFT) {
            keyboardEventHandler->setShiftKey(true);
        }
        else {
            // Print the key to the screen
            char key = scancodeAscii[(int) scancode];
            keyboardEventHandler->onKeyDown(key);
            // Append the letter to the buffer
            char str[2] = {key, '\0'};
            append(keyBuffer, key);
            ++lengthOfCurrentCommand;
        }
    // Else the scancode is released.
    } else {
        switch(scancode)
        {
            case 0xAA: keyboardEventHandler->setShiftKey(false); break;
            case 0xB6: keyboardEventHandler->setShiftKey(false); break;
            default:
                // Don't handle on scancode up.
                break;
        }
    }

    return esp;
}

void KeyboardDriver::setConsole(shell* sh) {
    this->console = sh;
}