#include <kernel/gui/Widget.hpp>

Widget::Widget(Widget *parent, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
}

Widget::~Widget() {

}

void Widget::getFocus(Widget* widget) {
    if (this->parent != 0) {
        this->parent->getFocus(widget);
    }
}

void Widget::modelToScreen(int32_t &x, int32_t &y) {
    if (parent != 0) {
        this->parent->modelToScreen(x, y);
    }
    x += this->x;
    y += this->y;
}

void Widget::draw(GraphicsContext* gc) {
    int drawX = 0;
    int drawY = 0;
    modelToScreen(drawX, drawY);
    gc->fillRect(drawX, drawY, this->w, this->h, this->r, this->g, this->b);
}

void Widget::onMouseDown(int32_t x, int32_t y) {

}

void Widget::onMouseUp(int32_t x, int32_t y) {

}

void Widget::onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY) {

}

void Widget::onKeyDown(int32_t x, int32_t y) {

}

void Widget::onKeyUp(int32_t x, int32_t y) {

}
