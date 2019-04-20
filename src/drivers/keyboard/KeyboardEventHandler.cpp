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
    // If the shift key boolean is enabled, print the capital version if not a space
    if (isShiftEnabled && c != ' ') {
        char str[2] = {c, '\0'};
        const char* cStr;
        // Handle special characters
        switch (c) {
            case '1': printf("!"); break;
            case '2': printf("@"); break;
            case '3': printf("#"); break;
            case '4': printf("$"); break;
            case '5': printf("%"); break;
            case '6': printf("^"); break;
            case '7': printf("&"); break;
            case '8': printf("*"); break;
            case '9': printf("("); break;
            case '0': printf(")"); break;
            case '-': printf("_"); break;
            case '=': printf("+"); break;
            case '/': printf("?"); break;
            case '.': printf(">"); break;
            case ',': printf("<"); break;
            default:
                cStr = toUpper(str);
                printf(cStr);
                break;
        }
    // print the lowercase version
    } else {
        const char str[2] = {c, '\0'};
        printf(str);
    }
}

void KeyboardEventHandler::onKeyUp(char c) {
    // Need to check if the shift key has been released
}