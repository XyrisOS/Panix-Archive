/**
 * @file VGA.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_VGA_HPP
#define PANIX_VGA_HPP

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <drivers/Driver.hpp>

class VideoGraphicsArray {
    protected:
        /**
         * @brief These ports are single byte (8 bit) ports
         * which access the display VGA controller. The specification
         * for VGA and all of these ports can be found on the OSDev
         * Wiki at wiki.osdev.org
         * 
         */
        PortByte miscPort;
        PortByte crtcIndexPort;
        PortByte crtcDataPort;
        PortByte sequencerIndexPort;
        PortByte sequencerDataPort;
        PortByte graphicsControllerIndexPort;
        PortByte graphicsControllerDataPort;
        PortByte attributeControllerIndexPort;
        PortByte attributeControllerReadPort;
        PortByte attributeControllerWritePort;
        PortByte attributeControllerResetPort;

        /**
         * @brief Writes the VGA registers
         * 
         * @param registers registers address
         */
        void writeRegisters(uint8_t* registers);
        /**
         * @brief Get the Frame Buffer Segment object
         * 
         * @return uint8_t* Pointer to the frame buffer segment
         */
        uint8_t* getFrameBufferSegment();
        /**
         * @brief Get the Color Index of an RGB code
         * 
         * @param r Red value
         * @param g Green value
         * @param b Blue value
         * @return uint8_t color index
         */
        virtual uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b);

    public:
        /**
         * @brief Construct a new Video Graphics Array object
         * 
         */
        VideoGraphicsArray();
        /**
         * @brief Destroy the Video Graphics Array object
         * 
         */
        ~VideoGraphicsArray();

        virtual bool supportsMode(uint32_t width, uint32_t height, uint32_t depth);
        virtual bool setMode(uint32_t width, uint32_t height, uint32_t depth);
        virtual void setPixel(int32_t x, int32_t y, uint8_t depth);
        virtual void setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);
        virtual void fillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
};

#endif /* PANIX_VGA_HPP */