/**
 * @file Window.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <kernel/gui/Window.hpp>

Window::Window(Widget* parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b)
: CompositeWidget(parent, x, y, w, h,r, g, b)
{
    isBeingDragged = false;
}

Window::~Window() {
    // Stubbed
}

void Window::onMouseDown(int32_t x, int32_t y, uint8_t button) {
    isBeingDragged = (button == 1);
    CompositeWidget::onMouseDown(x, y, button);
}

void Window::onMouseUp(int32_t x, int32_t y, uint8_t button) {
    isBeingDragged = false;
    CompositeWidget::onMouseUp(x, y, button);
}

void Window::onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY) {
    if(isBeingDragged) {
        this->x += newX - oldX;
        this->y += newY - oldY;
    }
    CompositeWidget::onMouseMove(oldX, oldY, newX, newY);
}
