#ifndef MOUSE_EVENT_HANDLER_HPP
#define MOUSE_EVENT_HANDLER_HPP

#include <types.hpp>
#include <libc/kprint.hpp>

class MouseEventHandler {
    private:
        int8_t x;
        int8_t y;
    public:
        /**
         * @brief Construct a new Mouse Event Handler object
         * 
         */
        MouseEventHandler();
        /**
         * @brief 
         * 
         */
        virtual void onActivate();
        /**
         * @brief 
         * 
         * @param button 
         */
        virtual void onMouseDown(uint8_t button);
        /**
         * @brief 
         * 
         * @param button 
         */
        virtual void onMouseUp(uint8_t button);
        /**
         * @brief 
         * 
         * @param x 
         * @param y 
         */
        virtual void onMouseMove(int x, int y);
};

#endif /* MOUSE_EVENT_HANDLER_HPP */