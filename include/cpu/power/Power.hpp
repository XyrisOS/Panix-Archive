#ifndef PANIX_CPU_POWER
#define PANIX_CPU_POWER

#include <common/types.hpp>
#include <cpu/port/Port.hpp>

/**
 * @brief Reboots the computer by hammering the CPU reset pin.
 * 
 * @return int Returns a -1 if the reboot failed.
 */
int reboot();
/**
 * @brief Shutsdown the computer by calling the BIOS shutdown interrupt.
 * This function currently does not work and instead just panics the kernel.
 * This is likely due to the fact that the interrupt 0x25 is out the range
 * we handle in the InterruptManager. This should be looked into.
 * 
 * @return int Returns a -1 if the shutdown failed.
 */
int shutdown();

#endif /* PANIX_CPU_POWER */