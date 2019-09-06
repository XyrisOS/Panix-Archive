#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <types.hpp>
#include <cpu/gdt/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <drivers/DriverManager.hpp>
#include <drivers/keyboard/KeyboardDriver.hpp>
#include <drivers/mouse/MouseDriver.hpp>
#include <drivers/pci/PCI.hpp>
#include <drivers/vga/VGA.hpp>
#include <drivers/speaker/Speaker.hpp>
#include <libc/tty.hpp>
#include <kernel/shell/shell.hpp>

#endif /* KERNEL_HPP */