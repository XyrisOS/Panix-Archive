/**
 * @file Window.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_GUI_WINDOW_HPP
#define PANIX_GUI_WINDOW_HPP

#include <common/types.hpp>
#include <kernel/gui/Widget.hpp>

class Window : public CompositeWidget {
    protected:
        bool isBeingDragged;
    public:
        Window(Widget* parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b);
        ~Window();
        void onMouseDown(int32_t x, int32_t y, uint8_t button);
        void onMouseUp(int32_t x, int32_t y, uint8_t button);
        void onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY);
};

#endif /* PANIX_GUI_WINDOW_HPP */