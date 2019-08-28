#include <drivers/keyboard/KeyboardEventHandler.hpp>

KeyboardEventHandler::KeyboardEventHandler() {}

void KeyboardEventHandler::backspace() {
    char backspace[] = { (char) 0x08, '\0' };
    kprint(backspace);
}

void KeyboardEventHandler::setShiftKey(bool isShiftPressed) {
    isShiftEnabled = isShiftPressed;
}

void KeyboardEventHandler::onKeyDown(char c) {
    // If the shift key boolean is enabled, print the capital version if not a space
    if (isShiftEnabled && c != ' ') {
        char str[2] = {c, '\0'};
        const char* cStr;
        // Handle special characters
        switch (c) {
            case '1': kprint("!"); break;
            case '2': kprint("@"); break;
            case '3': kprint("#"); break;
            case '4': kprint("$"); break;
            case '5': kprint("%"); break;
            case '6': kprint("^"); break;
            case '7': kprint("&"); break;
            case '8': kprint("*"); break;
            case '9': kprint("("); break;
            case '0': kprint(")"); break;
            case '-': kprint("_"); break;
            case '=': kprint("+"); break;
            case '/': kprint("?"); break;
            case '.': kprint(">"); break;
            case ',': kprint("<"); break;
            default:
                cStr = toUpper(str);
                kprint(cStr);
                break;
        }
    // print the lowercase version
    } else {
        const char str[2] = {c, '\0'};
        kprint(str);
    }
}

void KeyboardEventHandler::onKeyUp(char c) {
    // Need to check if the shift key has been released
}