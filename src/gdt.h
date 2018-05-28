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
#include "kprint.h"

class GlobalDescriptorTable {
public:
    // Segment Descriptors
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

    /**
     * Constructor for the Global Descriptor Table (GDT)
     * @param nullSegmentSelector - Null Mememory Segment Selector
     * @param unusedSegmentSelector - Unused Memory Segment Selector
     * @param codeSegmentSelector - Executable-Memory Segment Selector
     * @param dataSegmentSelector - Data-in-Memory Segment Selector
     */
    GlobalDescriptorTable();
    
    /**
     * Global Descriptor Table deconstructor
     */
    ~GlobalDescriptorTable();
    
    /**
     * Returns the value of the Code Segment Selector
     * @return 
     */
    uint16_t CodeSegmentSelector();
    
    /**
     * Returns the value of the Data Segment Selector
     * @return 
     */
    uint16_t DataSegmentSelector();
};

#endif /* gdt_h */