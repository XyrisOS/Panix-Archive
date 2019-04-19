#include <drivers/keyboard/KeyboardEventHandler.hpp>

KeyboardEventHandler::KeyboardEventHandler() {}

void KeyboardEventHandler::backspace() {
    char backspaceString[] = { (char) 0x08, '\0' };
    printf(backspaceString);
}

void KeyboardEventHandler::setShiftKey(bool isShiftPressed) {
    isShiftEnabled = isShiftPressed;
}

void KeyboardEventHandler::onKeyDown(char c) {
    // If the shift key boolean is enabled, print the capitol version
    if (isShiftEnabled) {
        char str[2] = {c, '\0'};
        const char* cStr = toUpper(str);
        printf(cStr);
    } else {
        const char str[2] = {c, '\0'};
        printf(str);
    }
}

void KeyboardEventHandler::onKeyUp(char c) {
    // Need to check if the shift key has been released
}