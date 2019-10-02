#include <cpu/power/Power.hpp>

int reboot() {
    uint8_t good = 0x02;
    while (good & 0x02) {
        good = readByte(0x64);
    }
    writeByte(0x64, 0xFE);
    asm("hlt");
    return -1;
}

int shutdown() {
    // Call bochs shutdown
    writeWord(0xB004, 0x2000);
    // Call QEMU shutdown
    writeWord(0x6004, 0x2000);
    // Call Virtualbox shutdown
    writeWord(0x4004, 0x3400);
    // If those failed, try the actual shutdown
    // Call our assembly shutdown code
    asm("mov $0x1000, %ax");
    asm("mov %ss, %ax");
    asm("mov $0xf000, %sp");
    asm("mov $0x5307, %ax");
    asm("mov $0x0001, %bx");
    asm("mov $0x0003, %cx");
    asm("int $0x15");
    asm("ret");
    return -1;
}