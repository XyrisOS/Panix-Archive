#include <drivers/keyboard/KeyboardEventHandler.hpp>

KeyboardEventHandler::KeyboardEventHandler() {}

void KeyboardEventHandler::backspace() {
    
}

void KeyboardEventHandler::onKeyDown(char c) {
    const char str[2] = {c, '\0'};
    printf(str);
}

void KeyboardEventHandler::onKeyUp(char c) {}