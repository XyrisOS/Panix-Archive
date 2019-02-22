#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define low16(address) (uint16_t)((address) & 0xFFFF)
#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif /* TYPES_H */