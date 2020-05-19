/**
 * @file GlobalDescriptorTable.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief The Global Descriptor Table (GDT) is specific to the IA32 architecture.
 * It contains entries telling the CPU about memory segments.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP
#define PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP

#include <types.hpp>

class GlobalDescriptorTable {
    public:
        // Code/Data Segment Descriptor
        class SegmentDescriptor {
            private:
                // These are descriptors in the GDT that have S=1. Bit 3 of "type" indicates whether it's (0) Data or (1) Code.
                // See https://wiki.osdev.org/Descriptors#Code.2FData_Segment_Descriptors for details on code & data segments.
                uint16_t limit_lo;  // Limit
                uint16_t base_lo;   // Base
                uint8_t base_hi;    // Base
                uint8_t type;       // Type
                uint8_t limit;      // Bits 0..3: limit, Bits 4..7: additional data/code attributes
                uint8_t base_vhi;   // Base
                
            public:
                /**
                 * @brief Construct a new Segment Descriptor object
                 * 
                 * @param base Segment base value
                 * @param limit Segment limit value
                 * @param type Segment type (code or data)
                 */
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                /**
                 * @brief Constructs a new GDT base
                 * 
                 * @return uint32_t 
                 */
                uint32_t Base();
                /**
                 * @brief Returns the base limit
                 * 
                 * @return uint32_t Limit value
                 */
                uint32_t Limit();
        } __attribute__((packed));

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:
        GlobalDescriptorTable();
        /**
         * @brief Constructs a new code segment
         * 
         * @return uint16_t 
         */
        uint16_t CodeSegmentSelector();
        /**
         * @brief Constructs a new data segment
         * 
         * @return uint16_t 
         */
        uint16_t DataSegmentSelector();
};

#endif /* PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP */