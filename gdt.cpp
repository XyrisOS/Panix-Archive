//  Global Descriptor Table for the EDIX kernel.
//  gdt.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "gdt.h"

/**
 * Constructor for the Global Descriptor Table (GDT)
 * @param nullSegmentSelector - Null Mememory Segment Selector
 * @param unusedSegmentSelector - Unused Memory Segment Selector
 * @param codeSegmentSelector - Executable-Memory Segment Selector
 * @param dataSegmentSelector - Data-in-Memory Segment Selector
 */
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

/**
 * Destructor for the GlobalDescriptorTable class
 */
GlobalDescriptorTable::~GlobalDescriptorTable() {
    //
}

/**
 * Returns the value of the Code Segment Selector
 */
uint16_t GlobalDescriptorTable::CodeSegmentSelector() {
    return (uint8_t *)&codeSegmentSelector - (uint8_t *)this;
}

/**
 * Returns the value of the Data Segment Selector
 */
uint16_t GlobalDescriptorTable::DataSegmentSelector() {
    return (uint8_t *)&dataSegmentSelector - (uint8_t *)this;
}
