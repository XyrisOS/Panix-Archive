#ifndef KEYBOARD_EVENT_HANDLER_HPP
#define KEYBOARD_EVENT_HANDLER_HPP

#include <libc/printf.hpp>
#include <libc/tty.hpp>

class KeyboardEventHandler {
    public:
        KeyboardEventHandler();

        virtual void onKeyDown(char c);
        virtual void onKeyUp(char c);
        virtual void backspace();
};

#endif /* KEYBOARD_EVENT_HANDLER_HPP */