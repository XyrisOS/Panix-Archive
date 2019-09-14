#ifndef PANIX_KERNEL_HPP
#define PANIX_KERNEL_HPP

// LibC
#include <types.hpp>
#include <libc/tty.hpp>
// CPU
#include <cpu/timer/Timer.hpp>
#include <cpu/gdt/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
// Drivers
#include <drivers/DriverManager.hpp>
#include <drivers/keyboard/KeyboardDriver.hpp>
#include <drivers/mouse/MouseDriver.hpp>
#include <drivers/pci/PCI.hpp>
#include <drivers/vga/VGA.hpp>
#include <drivers/speaker/Speaker.hpp>
#include <drivers/rtc/RTC.hpp>
// Kernel Helpers
#include <kernel/shell/shell.hpp>

#endif /* PANIX_KERNEL_HPP */