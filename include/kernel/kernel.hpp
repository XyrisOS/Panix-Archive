/**
 * @file kernel.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_KERNEL_HPP
#define PANIX_KERNEL_HPP
// LibC
#include <common/types.hpp>
#include <libc/tty.hpp>
// CPU
#include <cpu/gdt/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
// Drivers
#include <drivers/DriverManager.hpp>
#include <drivers/keyboard/KeyboardDriver.hpp>
#include <drivers/mouse/MouseDriver.hpp>
#include <drivers/pci/PCI.hpp>
#include <drivers/vga/VGA.hpp>
#include <drivers/speaker/Speaker.hpp>
#include <drivers/timer/Timer.hpp>
#include <drivers/rtc/RTC.hpp>
// Graphical Interface
#include <kernel/gui/Desktop.hpp>
#include <kernel/gui/Window.hpp>
// Kernel Helpers
#include <kernel/shell/shell.hpp>
#include <kernel/shell/ShellKeyboardEventHandler.hpp>
#include <kernel/shell/ShellMouseEventHandler.hpp>

TaskManager* kernelTaskManager;
InterruptManager* kernelInterruptManager;
DriverManager* kernelDriverManager;

extern "C" void callConstructors();
extern "C" void kernelMain(const void* multiboot_structure, uint32_t multiboot_magic);
void startShellAsProcess();

#endif /* PANIX_KERNEL_HPP */