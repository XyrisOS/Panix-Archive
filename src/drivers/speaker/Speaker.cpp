#include <drivers/speaker/Speaker.hpp>

Speaker::Speaker() : 
    port42(0x42), 
    port43(0x43), 
    port61(0x61)
{
    // Stubbbed
}

Speaker::~Speaker() {
    // Stubbed
}

void Speaker::activate() {
    stopSound();
    kprint("Activating speaker driver...\n");
}

void Speaker::playSound(uint32_t freqeuncy) {
    //Set the PIT to the desired frequency
    div = 1193180 / freqeuncy;
    port43.write(0xB6);
    port42.write(div & 0xFF);
    port42.write(div >> 8);

    port61.write(port61.read() | 3);
}

void Speaker::stopSound() {
    port61.write(port61.read() & ~3);
}

void Speaker::beep(uint32_t freq, uint32_t dur) {
    playSound(freq);
    //delay(dur);
    stopSound();
}