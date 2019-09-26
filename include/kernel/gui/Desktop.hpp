/**
 * @file Desktop.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_GUI_DESKTOP_HPP
#define PANIX_GUI_DESKTOP_HPP

#include <types.hpp>
#include <kernel/gui/Widget.hpp>
#include <drivers/mouse/MouseEventHandler.hpp>

class Desktop : public CompositeWidget, public MouseEventHandler {
    protected:
        uint32_t mouseX;
        uint32_t mouseY;
    public:
        Desktop(int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b);
        ~Desktop();

        void onActivate();
        void Draw(GraphicsContext* gc);
        void onMouseDown(uint8_t button);
        void onMouseUp(uint8_t button);
        void onMouseMove(int x, int y);
};

#endif /* PANIX_GUI_DESKTOP_HPP */