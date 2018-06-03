/*
 * Copyright (C) 2018 Keeton Feavel, Solar Pepper Studios
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* mgr) :
InterruptHandler(0x21, mgr), data(0x60), command(0x64) {
    // Wait until key is released to record keystrikes
    while (command.read() & 0x1) {
        uint8_t read = data.read();
    }
    command.write(0xAE);    // activate PIC keyboard interrupts (command 0xAE)
    command.write(0x20);    // return current state
    // Set rightmost bit to 1 to set new state and clear 5th bit
    uint8_t status = ((data.read() | 1) & ~0x10); 
    command.write(0x60);    // Inform keyboard to change current state
    command.write(status);  // write back changed current state
    
    data.write(0xF4);       // Activate keyboard
    // Print instantiation message
    kprint_status(true, "KeyboardDriver");
}

KeyboardDriver::~KeyboardDriver() {
    
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    // Fetch keystrike
    uint8_t key = data.read();
    
    // Set interrupt message char array
    char foo [] = "KEYBOARD 0x00 ";
    char hex [] = "0123456789ABCDEF";
    // Print interrupt message as an error
    foo[11] = hex[(key >> 4) & 0xF];
    foo[12] = hex[key & 0xF];
    kprint(foo);
    
    return esp;
}