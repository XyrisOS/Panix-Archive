#ifndef MOUSE_EVENT_HANDLER_HPP
#define MOUSE_EVENT_HANDLER_HPP

#include <types.hpp>
#include <libc/printf.hpp>

class MouseEventHandler {
    private:
        int8_t x;
        int8_t y;
    public:
        MouseEventHandler();

        virtual void onActivate();
        virtual void onMouseDown(uint8_t button);
        virtual void onMouseUp(uint8_t button);
        virtual void onMouseMove(int x, int y);
};

#endif /* MOUSE_EVENT_HANDLER_HPP */