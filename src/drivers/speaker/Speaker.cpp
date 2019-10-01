/**
 * @file Speaker.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <drivers/speaker/Speaker.hpp>

Speaker::Speaker() {
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
    writeByte(SPEAKER_COMMAND_PORT, 0xB6);
    writeByte(SPEAKER_DATA_PORT_2, div & 0xFF);
    writeByte(SPEAKER_DATA_PORT_2, div >> 8);

    writeByte(SPEAKER_DATA_PORT_1, (readByte(SPEAKER_DATA_PORT_1) | 3));
}

void Speaker::stopSound() {
    writeByte(SPEAKER_DATA_PORT_1, (readByte(SPEAKER_DATA_PORT_1) & ~3));
}

void Speaker::beep(uint32_t freq, uint32_t dur) {
    playSound(freq);
    //delay(dur);
    stopSound();
}