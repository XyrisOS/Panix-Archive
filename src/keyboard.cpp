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

KeyboardDriver::KeyboardDriver(InterruptManager * mgr) :
InterruptHandler(0x21, mgr), data(0x60), command(0x64) {
    // Wait until key is released to record keystrikes
    while (command.read() & 0x1) {
        uint8_t read = data.read();
    }
    command.write(0xAE); // activate PIC keyboard interrupts (command 0xAE)
    command.write(0x20); // return current state
    // Set rightmost bit to 1 to set new state and clear 5th bit
    uint8_t status = ((data.read() | 1) & ~0x10);
    command.write(0x60); // Inform keyboard to change current state

    data.write(status); // write back changed current state
    data.write(0xF4);   // Activate keyboard
    // Print instantiation message
    kprint_status(true, "KeyboardDriver");
}

KeyboardDriver::~KeyboardDriver() {

}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    // Fetch keystrike
    uint8_t key = data.read();
    // Print appropriate key.
    // TODO: Handle shift key
    if (key < 0x80) {
        switch (key) {
            case 0x02: kprint("1");
                break;
            case 0x03: kprint("2");
                break;
            case 0x04: kprint("3");
                break;
            case 0x05: kprint("4");
                break;
            case 0x06: kprint("5");
                break;
            case 0x07: kprint("6");
                break;
            case 0x08: kprint("7");
                break;
            case 0x09: kprint("8");
                break;
            case 0x0A: kprint("9");
                break;
            case 0x0B: kprint("0");
                break;

            case 0x10: kprint("q");
                break;
            case 0x11: kprint("w");
                break;
            case 0x12: kprint("e");
                break;
            case 0x13: kprint("r");
                break;
            case 0x14: kprint("t");
                break;
            case 0x15: kprint("z");
                break;
            case 0x16: kprint("u");
                break;
            case 0x17: kprint("i");
                break;
            case 0x18: kprint("o");
                break;
            case 0x19: kprint("p");
                break;

            case 0x1E: kprint("a");
                break;
            case 0x1F: kprint("s");
                break;
            case 0x20: kprint("d");
                break;
            case 0x21: kprint("f");
                break;
            case 0x22: kprint("g");
                break;
            case 0x23: kprint("h");
                break;
            case 0x24: kprint("j");
                break;
            case 0x25: kprint("k");
                break;
            case 0x26: kprint("l");
                break;

            case 0x2C: kprint("y");
                break;
            case 0x2D: kprint("x");
                break;
            case 0x2E: kprint("c");
                break;
            case 0x2F: kprint("v");
                break;
            case 0x30: kprint("b");
                break;
            case 0x31: kprint("n");
                break;
            case 0x32: kprint("m");
                break;
            case 0x33: kprint(",");
                break;
            case 0x34: kprint(".");
                break;
            case 0x35: kprint("-");
                break;

            case 0x1C: kprint("\n");
                break;
            case 0x39: kprint(" ");
                break;

            default:
            {
                // Set interrupt message char array
                char foo [] = "KEYBOARD 0x00 ";
                char hex [] = "0123456789ABCDEF";
                // Print interrupt message as an error
                foo[11] = hex[(key >> 4) & 0xF];
                foo[12] = hex[key & 0xF];
                kprint(foo);
                break;
            }
        }
    }
    return esp;
}