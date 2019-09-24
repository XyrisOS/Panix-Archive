#include <drivers/keyboard/KeyboardEventHandler.hpp>
// TODO: Can we just delete this file? I don't think we have to have a matching source file since
// the KeyboardEventHandler is just an interface.
KeyboardEventHandler::KeyboardEventHandler() {
    // Stubbed
}

void KeyboardEventHandler::backspace() {
    // Stubbed    
}

void KeyboardEventHandler::setShiftKey(bool isShiftPressed) {
    // Stubbed
}

void KeyboardEventHandler::onKeyDown(char c) {
    // Stubbed
}

void KeyboardEventHandler::onKeyUp(char c) {
    // Stubbed
}

void KeyboardEventHandler::handleScancode(uint8_t code) {
    // Stubbed
}