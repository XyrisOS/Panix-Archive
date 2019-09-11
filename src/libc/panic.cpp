#include <libc/stdio.hpp>
#include <drivers/speaker/Speaker.hpp>

// This is a freaking massive array. It definitely makes panicking slower.
// It also eats up a significant chunk of the kernel memory since it's not
// dynamic, so maybe we need to come back to this eventually?
const char exceptionDescriptions[33][16] = {
    "Divide-By-Zero", "Debugging", "Non-Maskable", "Breakpoint",
    "Overflow", "Out Bound Range", "Invalid Opcode", "Device Not Avbl",
    "Double Fault", "Co-CPU Overrun", "Invalid TSS", "Sgmnt !Present",
    "Seg Fault", "Protection Flt", "Page Fault", "RESERVED",
    "Floating Pnt", "Alignment Check", "Machine Check", "SIMD Flt Pnt",
    "Virtualization", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "Security Excptn", "RESERVED", "Triple Fault", "FPU Error"
};

void panic(int exception) {
    Speaker speaker = Speaker();
    speaker.playSound(880);
    clearScreen();
    printPanicScreen();
    char* panicCode = (char*) "UNHANDLED EXCEPTION 0x00 - ";
    char* hex = (char*) "0123456789ABCDEF";
    panicCode[22] = hex[(exception >> 4) & 0xF];
    panicCode[23] = hex[exception & 0xF];
    kprint(panicCode);
    kprint(exceptionDescriptions[exception]);
    asm("hlt");
}

