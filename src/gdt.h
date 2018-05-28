//  Global Descriptor Table for the EDIX kernel.
//  gdt.h
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef gdt_h
#define gdt_h
#include "types.h"
#include "kprint.h"

class GlobalDescriptorTable {
public:
    // Declare Segment Descriptor Subclass
    class SegmentDescriptor {
    public:

        /**
         * Segment Descriptor constructor
         * @param base Address base bits
         * @param limit Address limit bits
         * @param flags Address flags
         */
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);

        /**
         * Returns the memory address base bits
         * @return memory address base bits as a 32 bit integer
         */
        uint32_t Base();

        /**
         * Returns the memory address limit bits
         * @return memory address limit bits as a 32 bit integer
         */
        uint32_t Limit();
    private:
        // Class variables
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t limit_hi_flags;
        uint8_t base_vhi;

    } __attribute__ ((packed));

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
     * @return Value of the Code Segment Selector as a 16 bit integer
     */
    uint16_t CodeSegmentSelector();

    /**
     * Returns the value of the Data Segment Selector
     * @return Value of the Data Segment Selector as a 16 bit integer
     */
    uint16_t DataSegmentSelector();
};

#endif /* gdt_h */