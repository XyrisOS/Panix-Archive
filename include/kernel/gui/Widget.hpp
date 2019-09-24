#ifndef PANIX_GUI_WIDGET_HPP
#define PANIX_GUI_WIDGET_HPP

#include <types.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <kernel/gui/GraphicsContext.hpp>

class Widget : public KeyboardEventHandler {
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
        virtual bool containsCoordinate(int32_t x, int32_t y);
        virtual void onMouseDown(int32_t x, int32_t y, uint8_t button);
        virtual void onMouseUp(int32_t x, int32_t y, uint8_t button);
        virtual void onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY);
        virtual void onKeyDown(char c);
        virtual void onKeyUp(char c);
        virtual void handleScancode(uint8_t code);
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
        virtual bool addChild(Widget* child);
        virtual void draw(GraphicsContext* gc);
        virtual void onMouseDown(int32_t x, int32_t y, uint8_t button);
        virtual void onMouseUp(int32_t x, int32_t y, uint8_t button);
        virtual void onMouseMove(int32_t oldX, int32_t oldY, int32_t newX, int32_t newY);
        virtual void onKeyDown(char c);
        virtual void onKeyUp(char c);
        virtual void handleScancode(uint8_t code);
};

#endif /* PANIX_GUI_WIDGET_HPP */