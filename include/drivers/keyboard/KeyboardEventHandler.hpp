#ifndef KEYBOARD_EVENT_HANDLER_HPP
#define KEYBOARD_EVENT_HANDLER_HPP

#include <libc/ctype.hpp>
#include <libc/printf.hpp>
#include <libc/tty.hpp>

class KeyboardEventHandler {
    private:
        bool isShiftEnabled;
    public:
        KeyboardEventHandler();
        virtual void setShiftKey(bool isShiftPressed);
        virtual void onKeyDown(char c);
        virtual void onKeyUp(char c);
        virtual void backspace();
};

#endif /* KEYBOARD_EVENT_HANDLER_HPP */