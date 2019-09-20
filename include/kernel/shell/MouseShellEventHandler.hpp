#ifndef PANIX_MOUSE_SHELL_EVENT_HANDLER
#define PANIX_MOUSE_SHELL_EVENT_HANDLER

#include <types.hpp>
#include <drivers/mouse/MouseEventHandler.hpp>

class MouseShellEventHandler : public MouseEventHandler {
    private:
        int8_t x;
        int8_t y;
    public:
        MouseShellEventHandler();
        void onMouseDown(uint8_t button);
        void onMouseUp(uint8_t button);
        void onActivate();
        void onMouseMove(int xoffset, int yoffset);
};

#endif /* PANIX_MOUSE_SHELL_EVENT_HANDLER */