#ifndef KEYBOARD_EVENT_HANDLER_HPP
#define KEYBOARD_EVENT_HANDLER_HPP

class KeyboardEventHandler {
    public:
        KeyboardEventHandler();

        virtual void onKeyDown(char);
        virtual void onKeyUp(char);
};

#endif /* KEYBOARD_EVENT_HANDLER_HPP */