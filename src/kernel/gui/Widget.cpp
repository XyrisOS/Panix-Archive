/**
 * @file Widget.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <kernel/gui/Widget.hpp>

#pragma mark Widget

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
    // Stubbed
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

bool Widget::containsCoordinate(int32_t x, int32_t y) {
    return this->x <= x && x < this->x + this->w
        && this->y <= y && y < this->y + this->h;
}

void Widget::onMouseDown(int32_t x, int32_t y, uint8_t button) {
    if (isFocusable) {
        getFocus(this);
    }
}

void Widget::onMouseUp(int32_t x, int32_t y, uint8_t button) {
    // Stubbed
}

void Widget::onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY) {
    // Stubbed
}

void Widget::onKeyDown(char c) {
    // Stubbed
}

void Widget::onKeyUp(char c) {
    // Stubbed
}

void Widget::handleScancode(uint8_t code) {
    // Stubbed
}

#pragma mark CompositeWidget

CompositeWidget::CompositeWidget(Widget *parent, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b) 
: Widget(parent, x,y,w,h, r,g,b) 
{
    childWithFocus = 0;
    childCount = 0;
}

CompositeWidget::~CompositeWidget() {
    // Stubbed
}

void CompositeWidget::getFocus(Widget* widget) {
    this->childWithFocus = widget;
    if (this->parent != 0) {
        this->parent->getFocus(this);
    }
}

bool CompositeWidget::addChild(Widget* child) {
    if (childCount >= 100) {
        return false;
    }
    children[childCount++] = child;
    return true;
}

void CompositeWidget::draw(GraphicsContext* gc) {
    Widget::draw(gc);
    for (int i = childCount - 1; i >= 0; --i) {
        children[i]->draw(gc);
    }
}

void CompositeWidget::onMouseDown(int32_t x, int32_t y, uint8_t button) {
    for(int i = 0; i < childCount; ++i) {
        if(children[i]->containsCoordinate(x - this->x, y - this->y)) {
            children[i]->onMouseDown(x - this->x, y - this->y, button);
            break;
        }
    }
}

void CompositeWidget::onMouseUp(int32_t x, int32_t y, uint8_t button) {
    for(int i = 0; i < childCount; ++i) {
        if(children[i]->containsCoordinate(x - this->x, y - this->y)) {
            children[i]->onMouseUp(x - this->x, y - this->y, button);
            break;
        }
    }
}

void CompositeWidget::onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY) {
    int firstchild = -1;
    for(int i = 0; i < childCount; ++i) {
        if(children[i]->containsCoordinate(oldX - this->x, oldY - this->y)) {
            children[i]->onMouseMove(oldX - this->x, oldY - this->y, newX - this->x, newY - this->y);
            firstchild = i;
            break;
        }
    }

    for(int i = 0; i < childCount; ++i) {
        if(children[i]->containsCoordinate(newX - this->x, newY - this->y))
        {
            if(firstchild != i)
                children[i]->onMouseMove(oldX - this->x, oldY - this->y, newX - this->x, newY - this->y);
            break;
        }
    }
}

void CompositeWidget::onKeyDown(char c) {
    if(childWithFocus != 0) {
        childWithFocus->onKeyDown(c);
    }
}

void CompositeWidget::onKeyUp(char c) {
    if(childWithFocus != 0) {
        childWithFocus->onKeyUp(c);
    }
}

void CompositeWidget::handleScancode(uint8_t code) {
    // Stubbed
}