#ifndef PANIX_KEYBOARD_SHELL_EVENT_HANDLER
#define PANIX_KEYBOARD_SHELL_EVENT_HANDLER

#include <types.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>

class ShellKeyboardEventHandler : public KeyboardEventHandler {
    private:
        bool isShiftEnabled;
    public:
        ShellKeyboardEventHandler();
        void setShiftKey(bool isShiftPressed);
        void onKeyDown(char c);
        void onKeyUp(char c);
        void backspace();
};

#endif /* PANIX_KEYBOARD_SHELL_EVENT_HANDLER */