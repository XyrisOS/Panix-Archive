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

#include "segdescriptor.h"

SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags) {
    uint8_t * target = (uint8_t *)this;

    // If the limit is less than 16 bits
    if (limit <= 65536) {
        // 16 bit address space
        target[6] = 0x40;
    } else {
        // 32 bit address space
        // If the last 12 bits are not all 1
        if ((limit & 0xFFF) != 0xFFF) {
            // Set the limit to the limit shifted by 12 - 1
            limit = ((limit >> 12) - 1);
        } else {
            // Else shift the limit by 12
            limit = (limit >> 12);
        }
        target[6] = 0xC0;
    }
    // Encode the address limit parameter
    target[0] = (limit & 0xFF);         // LSB of the limit
    target[1] = ((limit >> 8) & 0xFF);  // Shift 8 bits and set
    target[6] |= (limit >> 16) & 0xF;   // Set the lower 4 bits of the target due to 1/2 byte
    // Encode the address base parameter
    target[2] = (base & 0xFF);
    target[3] = ((base >> 8) & 0xFF);
    target[4] = ((base >> 16) & 0xFF);
    target[7] = ((base >> 24) & 0xFF);
    // Set the access rights (type)
    target[5] = flags;
    kprint_status(true, "SegmentDescriptor");
}

uint32_t SegmentDescriptor::Base() {
    uint8_t * target = (uint8_t *)this;
    uint32_t result = target[7];
    // Shift the bits to get to the base value
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    // Return base value
    return result;
}

uint32_t SegmentDescriptor::Limit() {
    uint8_t * target = (uint8_t *)this;
    uint32_t result = target[6] & 0xF;      // Take the lower 4 bits of the shared byte
    // Shift the bits to get the limit value
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];
    // Shift by 12 and get the limit value
    if ((target[6] & 0xC0) == 0xC0) {
        result = (result << 12) | 0xFFF;    // Shift if target[6] has been set to 0xC0
    }
    // Return the limit value
    return result;
}