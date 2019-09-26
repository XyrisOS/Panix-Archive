/**
 * @file ShellMouseEventHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_MOUSE_SHELL_EVENT_HANDLER
#define PANIX_MOUSE_SHELL_EVENT_HANDLER

#include <types.hpp>
#include <drivers/mouse/MouseEventHandler.hpp>

class ShellMouseEventHandler : public MouseEventHandler {
    private:
        int8_t x;
        int8_t y;
    public:
        ShellMouseEventHandler();
        void onMouseDown(uint8_t button);
        void onMouseUp(uint8_t button);
        void onActivate();
        void onMouseMove(int xoffset, int yoffset);
};

#endif /* PANIX_MOUSE_SHELL_EVENT_HANDLER */