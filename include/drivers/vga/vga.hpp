#ifndef VGA_HPP
#define VGA_HPP

#include <types.hpp>
#include <cpu/Port/Port.hpp>
#include <drivers/Driver.hpp>

class VideoGraphicsArray {
    protected:
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

        void writeRegisters(uint8_t* registers);
        uint8_t* getFrameBufferSegment();
        virtual uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b);

    public:
        VideoGraphicsArray();
        ~VideoGraphicsArray();

        virtual bool supportsMode(uint32_t width, uint32_t height, uint32_t depth);
        virtual bool setMode(uint32_t width, uint32_t height, uint32_t depth);
        virtual void setPixel(uint8_t x, uint8_t y, uint8_t depth);
        virtual void setPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
};

#endif /* VGA_HPP */