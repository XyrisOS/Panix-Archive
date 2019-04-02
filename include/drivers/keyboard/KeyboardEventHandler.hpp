#ifndef KEYBOARD_EVENT_HANDLER_HPP
#define KEYBOARD_EVENT_HANDLER_HPP

class KeyboardEventHandler {
    public:
        KeyboardEventHandler();

        virtual void onKeyDown(char c);
        virtual void onKeyUp(char c);
};

#endif /* KEYBOARD_EVENT_HANDLER_HPP */