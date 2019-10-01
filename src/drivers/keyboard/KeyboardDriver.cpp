/**
 * @file KeyboardDriver.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <drivers/keyboard/KeyboardDriver.hpp>

// Any non-ASCII keys should have '\0'
const char scancodeAscii[] = {
    '\0', '`', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\0', '?',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', '\0', 'a', 's',
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
    : InterruptHandler(interruptManager, 0x21) {
    this->keyboardEventHandler = keyboardEventHandler;
}

KeyboardDriver::~KeyboardDriver() {}

void KeyboardDriver::activate() {
    while(readByte(KEYBOARD_COMMAND_PORT) & 0x1) {
        readByte(KEYBOARD_DATA_PORT);
    }
    writeByte(KEYBOARD_COMMAND_PORT, 0xae); // activate interrupts
    writeByte(KEYBOARD_COMMAND_PORT, 0x20); // command 0x20 = read controller command byte
    uint8_t status = (readByte(KEYBOARD_DATA_PORT) | 1) & ~0x10;
    writeByte(KEYBOARD_COMMAND_PORT, 0x60); // command 0x60 = set controller command byte
    writeByte(KEYBOARD_DATA_PORT, status);
    writeByte(KEYBOARD_DATA_PORT, 0xf4);
    kprint("Activating keyboard event handler\n");
}

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp) {
    uint8_t scancode = readByte(KEYBOARD_DATA_PORT);
    if (keyboardEventHandler == nullptr) {
        return esp;
    }
    // If a scancode is pressed down
    if (scancode < 0x80) {
        if (scancode > SCANCODE_MAX) {
            return esp;
        }
        if (scancode == BACKSPACE) {
            keyboardEventHandler->backspace();
        }
        else {
            // Print the key to the screen
            char key = scancodeAscii[(int) scancode];
            // If there is no ascii code when we've done all other checks then
            // hand it off to the event handler. This might need to be checked
            // if any weird keyboard bugs come up in the future.
            if (key == '\0') {
                keyboardEventHandler->handleScancode(scancode);
            }
            keyboardEventHandler->onKeyDown(key);
        }
    // Else the scancode is released.
    } else {
        keyboardEventHandler->handleScancode(scancode);
    }

    return esp;
}

void KeyboardDriver::setHandler(KeyboardEventHandler *handler) {
    this->keyboardEventHandler = handler;
}

char* KeyboardDriver::getDriverTypeTag() {
    return "KEYBOARD";
}