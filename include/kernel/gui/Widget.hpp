#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <types.hpp>
#include <kernel/gui/GraphicsContext.hpp>

class Widget {
    protected:
        // Parent widget
        Widget* parent;
        // Location information
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        // Color information
        uint8_t r;
        uint8_t g;
        uint8_t b;
        // Focus information
        bool isFocusable;
    public:
        Widget(Widget *parent, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
        ~Widget();

        virtual void getFocus(Widget* widget);
        virtual void modelToScreen(int32_t &x, int32_t &y);
        virtual void draw(GraphicsContext* gc);
        virtual void onMouseDown(int32_t x, int32_t y);
        virtual void onMouseUp(int32_t x, int32_t y);
        virtual void onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY);
        virtual void onKeyDown(int32_t x, int32_t y);
        virtual void onKeyUp(int32_t x, int32_t y);

};

class CompositeWidget : public Widget {
    private:
        Widget* children[100];
        int childCount;
        Widget* childWithFocus;
    public:
        CompositeWidget(Widget *parent, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
        ~CompositeWidget();

        virtual void getFocus(Widget* widget);
        virtual void modelToScreen(int32_t &x, int32_t &y);
        virtual void draw(GraphicsContext* gc);
        virtual void onMouseDown(int32_t x, int32_t y);
        virtual void onMouseUp(int32_t x, int32_t y);
        virtual void onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY);
        virtual void onKeyDown(int32_t x, int32_t y);
        virtual void onKeyUp(int32_t x, int32_t y);

};

#endif /* WIDGET_HPP */