#!/bin/bash
echo "Testing bootsector binary file..."
qemu-system-x86_64 -fda ../build/boot_sect.bin 2> boot_sect_test.error.out
