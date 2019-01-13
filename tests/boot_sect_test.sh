#!/bin/bash
echo "Testing bootsector binary file..."
qemu-system-x86_64 -fda ../build/boot_sect.bin
