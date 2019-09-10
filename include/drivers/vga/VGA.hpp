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
        Port8Bit miscPort;
        Port8Bit crtcIndexPort;
        Port8Bit crtcDataPort;
        Port8Bit sequencerIndexPort;
        Port8Bit sequencerDataPort;
        Port8Bit graphicsControllerIndexPort;
        Port8Bit graphicsControllerDataPort;
        Port8Bit attributeControllerIndexPort;
        Port8Bit attributeControllerReadPort;
        Port8Bit attributeControllerWritePort;
        Port8Bit attributeControllerResetPort;

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
        virtual void setPixel(uint8_t x, uint8_t y, uint8_t depth);
        virtual void setPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
        virtual void fillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
};

#endif /* PANIX_VGA_HPP */