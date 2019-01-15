#!/bin/bash
echo "Testing bootsector binary file..."
qemu-system-x86_64 -fda ../build/boot32.bin 2> boot32.error.out
