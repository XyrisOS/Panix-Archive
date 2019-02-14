---
title: 'Installation / Virtualization'

layout: nil
---

### How to Run Panix

Currently Panix is run using QEMU in kernel mode with the pre-compiled `panix.raw` file provided in the repository.

If you want to run Panix for yourself, download `kernel.bin` in the build/ folder and run the following command:

`qemu-system-i386 -kernel <path-to-kernel.bin>`

Additionally, Panix runs in Virtualbox 5 using `panix.iso` with the following settings:

- OS Type: Other/Unknown (32-bit)
- Memory: 64 MB
- Boot Medium: ISO (no HDD)
- All other settings are set to the default for the OS Type
