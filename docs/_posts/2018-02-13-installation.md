---
title: 'Installation / Virtualization'

layout: nil
---

### How to Run Panix

Currently Panix is run using QEMU in kernel mode with the pre-compiled `panix.raw` file provided in the repository.
If you want to run Panix for yourself, download `kernel.bin` in the dist folder and run the following command:
`qemu-system-i386 -kernel <path-to-kernel.bin>`
Virtualbox support will eventually be added when an iso is compiled.
