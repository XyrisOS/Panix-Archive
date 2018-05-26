//  Global Descriptor Table for the EDIX kernel.
//  gdt.h
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef gdt_h
#define gdt_h

#include "types.h"
#include "segdescriptor.h"

class GlobalDescriptorTable {
    public:
        // Segment Descriptors
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint16_t CodeSegmentSelector();
        uint16_t DataSegmentSelector();
};

#endif /* gdt_h */