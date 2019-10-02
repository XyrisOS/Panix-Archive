/**
 * @file VGA.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <drivers/vga/VGA.hpp>

VideoGraphicsArray::VideoGraphicsArray() {
    // Stubbed
}

VideoGraphicsArray::~VideoGraphicsArray() {
    // Stubbed
}

void VideoGraphicsArray::writeRegisters(uint8_t* registers) {
    //  misc
    writeByte(MISC_PORT, *(registers++));

    // sequencer
    for (uint8_t i = 0; i < 5; i++) {
        writeByte(SEQUENCER_INDEX_PORT, i);
        writeByte(SEQUENCER_DATA_PORT, *(registers++));
    }

    // cathode ray tube controller (CRTC)
    writeByte(CRTC_INDEX_PORT, 0x03);
    writeByte(CRTC_DATA_PORT, (readByte(CRTC_DATA_PORT) | 0x80));
    writeByte(CRTC_INDEX_PORT, 0x11);
    writeByte(CRTC_DATA_PORT, (readByte(CRTC_DATA_PORT) & ~0x80));

    registers[0x03] = registers[0x03] | 0x80;
    registers[0x11] = registers[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++) {
        writeByte(CRTC_INDEX_PORT, i);
        writeByte(CRTC_DATA_PORT, *(registers++));
    }

    // graphics controller
    for(uint8_t i = 0; i < 9; i++) {
        writeByte(GRAPHICS_CONTROLLER_INDEX_PORT, i);
        writeByte(GRAPHICS_CONTROLLER_DATA_PORT, *(registers++));
    }

    // attribute controller
    for(uint8_t i = 0; i < 21; i++) {
        readByte(ATTRIBUTE_CONTROLLER_RESET_PORT);
        writeByte(ATTRIBUTE_CONTROLLER_INDEX_PORT, i);
        writeByte(ATTRIBUTE_CONTROLLER_WRITE_PORT, *(registers++));
    }

    readByte(ATTRIBUTE_CONTROLLER_RESET_PORT);
    writeByte(ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}

bool VideoGraphicsArray::supportsMode(uint32_t width, uint32_t height, uint32_t colordepth) {
    return width == 320 && height == 200 && colordepth == 8;
}

bool VideoGraphicsArray::setMode(uint32_t width, uint32_t height, uint32_t colordepth)
{
    if (!supportsMode(width, height, colordepth)) {
        return false;
    }

    unsigned char g_320x200x256[] = {
        /* MISC */
            0x63,
        /* SEQ */
            0x03, 0x01, 0x0F, 0x00, 0x0E,
        /* CRTC */
            0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
            0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
            0xFF,
        /* GC */
            0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
            0xFF,
        /* AC */
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x41, 0x00, 0x0F, 0x00, 0x00
    };

    writeRegisters(g_320x200x256);
    return true;
}

uint8_t* VideoGraphicsArray::getFrameBufferSegment() {
    writeByte(GRAPHICS_CONTROLLER_INDEX_PORT, 0x06);
    uint8_t segmentNumber = readByte(GRAPHICS_CONTROLLER_DATA_PORT) & (3<<2);
    switch(segmentNumber) {
        default:
        case 0<<2:
            return (uint8_t*)0x00000;
        case 1<<2:
            return (uint8_t*)0xA0000;
        case 2<<2:
            return (uint8_t*)0xB0000;
        case 3<<2:
            return (uint8_t*)0xB8000;
    }
}

uint8_t VideoGraphicsArray::getColorIndex(uint8_t r, uint8_t g, uint8_t b) {
    if (r == 0x00 && g == 0x00 && b == 0x00) return 0x00; // black
    if (r == 0x00 && g == 0x00 && b == 0xA8) return 0x01; // blue
    if (r == 0x00 && g == 0xA8 && b == 0x00) return 0x02; // green
    if (r == 0xA8 && g == 0x00 && b == 0x00) return 0x04; // red
    if (r == 0xFF && g == 0xFF && b == 0xFF) return 0x3F; // white
    return 0x00;
}

void VideoGraphicsArray::setPixel(int32_t x, int32_t y, uint8_t depth) {
    if (x < 0 || 320 <= x || y < 0 || 200 <= y) {
        return;
    }
    uint8_t* pixelAddress = getFrameBufferSegment() + 320 * y + x;
    *pixelAddress = depth;
}

void VideoGraphicsArray::setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) {
    setPixel(x, y, getColorIndex(r,g,b));
}

void VideoGraphicsArray::fillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b) {
    for (int32_t i = y; i < y + h; i++) {
        for (int32_t j = x; j < x + w; j++) {
            setPixel(j, i, r, g, b);
        }
    }
}