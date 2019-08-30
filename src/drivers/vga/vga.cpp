#include <drivers/vga/vga.hpp>

VideoGraphicsArray::VideoGraphicsArray() : 
    miscPort(0x3C2),
    crtcIndexPort(0x3D4),
    crtcDataPort(0x3D5),
    sequencerIndexPort(0x3C4),
    sequencerDataPort(0x3C5),
    graphicsControllerIndexPort(0x3CE),
    graphicsControllerDataPort(0x3CF),
    attributeControllerIndexPort(0x3C0),
    attributeControllerReadPort(0x3C1),
    attributeControllerWritePort(0x3C0),
    attributeControllerResetPort(0x3DA)
{
    //
}

VideoGraphicsArray::~VideoGraphicsArray() {
    
}