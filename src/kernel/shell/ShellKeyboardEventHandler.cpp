#include <kernel/shell/ShellKeyboardEventHandler.hpp>

ShellKeyboardEventHandler::ShellKeyboardEventHandler() : 
KeyboardEventHandler()
{
    
}

void ShellKeyboardEventHandler::handleScancode(uint8_t scancode) {
    // Handle the shift key
    if (scancode == RIGHT_SHIFT || scancode == LEFT_SHIFT) {
        setShiftKey(true);
    } else if (scancode == 0xAA || scancode == 0xB6) {
        setShiftKey(false);
    }
    // Handle the up arrow for last command
    if (scancode == UP_ARROW && strlen(lastCommand) > 0) {
        while (lengthOfCurrentCommand > 0) {
            backspace();
            --lengthOfCurrentCommand;
        }
        strcpy(lastCommand, keyBuffer);
        lengthOfCurrentCommand = strlen(lastCommand);
        kprint(lastCommand);
    }
}

void ShellKeyboardEventHandler::backspace() {
    if (lengthOfCurrentCommand > 0) {
        --lengthOfCurrentCommand;
        backspaceString(keyBuffer);
        char backspace[] = { (char) 0x08, '\0' };
        kprint(backspace);
    }
}

void ShellKeyboardEventHandler::setShiftKey(bool isShiftPressed) {
    isShiftEnabled = isShiftPressed;
}

void ShellKeyboardEventHandler::onKeyDown(char c) {
    // If we get a newline
    if (c == '\n') {
        kprint("\n");
        // Add a null char to the end and copy
        keyBuffer[lengthOfCurrentCommand] = '\0';
        strcpy(keyBuffer, lastCommand);
        lengthOfCurrentCommand = 0;
        keyBuffer[0] = '\0';
        if (this->console != nullptr) {
            this->console->handleShellInput(lastCommand);
        }
        if (lengthOfCurrentCommand >= 256) {
            lengthOfCurrentCommand = 255;
        }
        return;
    }
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
            case '[': kprint("{"); break;
            case ']': kprint("}"); break;

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
    // Append the letter to the buffer
    // Move this into the handler
    char str[2] = {c, '\0'};
    append(keyBuffer, c);
    ++lengthOfCurrentCommand;
}

void ShellKeyboardEventHandler::onKeyUp(char c) {
    // Need to check if the shift key has been released
}

void ShellKeyboardEventHandler::setConsole(shell* console) {
    this->console = console;
}