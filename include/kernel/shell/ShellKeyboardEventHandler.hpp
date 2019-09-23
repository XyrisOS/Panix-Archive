#ifndef PANIX_KEYBOARD_SHELL_EVENT_HANDLER
#define PANIX_KEYBOARD_SHELL_EVENT_HANDLER

#include <types.hpp>
#include <libc/string.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <kernel/shell/shell.hpp>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define UP_ARROW 0x48

class ShellKeyboardEventHandler : public KeyboardEventHandler {
    private:
        bool isShiftEnabled;
        Shell* console;
        char keyBuffer[256] = "\0";
        char lastCommand[256] = "\0";
        uint16_t lengthOfCurrentCommand = 0;
    public:
        ShellKeyboardEventHandler();
        void handleScancode(uint8_t scancode);
        void setShiftKey(bool isShiftPressed);
        void onKeyDown(char c);
        void onKeyUp(char c);
        void backspace();
        void setConsole(Shell* console);
};

#endif /* PANIX_KEYBOARD_SHELL_EVENT_HANDLER */