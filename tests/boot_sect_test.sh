#!/bin/bash
echo "Testing bootsector binary file..."
qemu-system-x86_64 ../build/boot_sect.bin -boot c
