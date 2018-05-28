//  Global Descriptor Table for the EDIX kernel.
//  gdt.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "gdt.h"

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags) {
    uint8_t * target = (uint8_t *)this;

    // If the limit is less than 16 bits
    if (limit <= 65536) {
        target[6] = 0x40;
    } else {
        // If the last 12 bits are not all 1
        if ((limit & 0xFFF) != 0xFFF) {
            // Set the limit to the limit shifted by 12 - 1
            limit = (limit >> 12) - 1;
        } else {
            // Else shift the limit by 12
            limit = (limit >> 12);
        }
        target[6] = 0xC0;
    }
    //
    target[0] = (limit & 0xFF); // LSB of the limit
    target[1] = ((limit >> 8) & 0xFF); // Shift 8 bits and set
    target[6] |= (limit >> 16) & 0xF; // Set the lower 4 bits of the target due to 1/2 byte
    //
    target[2] = (base & 0xFF);
    target[3] = ((base >> 8) & 0xFF);
    target[4] = ((base >> 16) & 0xFF);
    target[7] = ((base >> 24) & 0xFF);
    // Set the access rights
    target[5] = flags;
    kprint_status(true, "SegmentDescriptor");
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base() {
    uint8_t * target = (uint8_t *)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit() {
    uint8_t * target = (uint8_t *)this;
    uint32_t result = target[6] & 0xF; // Take the lower 4 bits of the shared byte
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if ((target[6] & 0xC0) == 0xC0) {
        result = (result << 12) | 0xFFF; // Shift if target[6] has been set to 0xC0
    }

    return result;
}

GlobalDescriptorTable::GlobalDescriptorTable() :
nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0, 64*1024*1024, 0x9A),
dataSegmentSelector(0, 64*1024*1024, 0x92) {
    // Initialize the GDT by calling the asm commands
    uint32_t i[2];
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    i[1] = (uint32_t)this;
    // Call asm load gdt command
    asm volatile("lgdt (%0)" : : "p" (((uint8_t *) i) + 2));
    kprint_status(true, "GlobalDescriptorTableService");
}

GlobalDescriptorTable::~GlobalDescriptorTable() {
    //
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector() {
    return (uint8_t *)&codeSegmentSelector - (uint8_t *)this;
}

uint16_t GlobalDescriptorTable::DataSegmentSelector() {
    return (uint8_t *)&dataSegmentSelector - (uint8_t *)this;
}
