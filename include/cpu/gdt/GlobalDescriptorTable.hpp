/**
 * @file GlobalDescriptorTable.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP
#define PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP

#include <common/types.hpp>

class GlobalDescriptorTable {
    public:
        class SegmentDescriptor {
            private:
                uint16_t limit_lo;
                uint16_t base_lo;
                uint8_t base_hi;
                uint8_t type;
                uint8_t limit_hi;
                uint8_t base_vhi;
                
            public:
                /**
                 * @brief Construct a new Segment Descriptor object
                 * 
                 * @param base 
                 * @param limit 
                 * @param type 
                 */
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                /**
                 * @brief 
                 * 
                 * @return uint32_t 
                 */
                uint32_t Base();
                /**
                 * @brief 
                 * 
                 * @return uint32_t 
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
         * @brief 
         * 
         * @return uint16_t 
         */
        uint16_t CodeSegmentSelector();
        /**
         * @brief 
         * 
         * @return uint16_t 
         */
        uint16_t DataSegmentSelector();
};

#endif /* PANIX_GLOBAL_DESCRIPTOR_TABLE_HPP */