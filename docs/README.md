# EDIX
EDIX (pronounced "edd-eks" | "edd-iks") is a basic operating system I am designing for my own, personal education. After taking CS-3310 (Operating Systems) at my university, I thought it would be a good idea to try to write my own. I am doing this through the use of various tutorials, websites like OSDev.org, and my own knowledge of C++ and OS structures.

### What does EDIX stand for?
Just as UNIX used to be UNICS (Uniplexed Information Computing System), EDIX is properly EDICS (Educational Information Computing System).</br>
The name is "shortened" to EDIX to stick with the long established *\*nix* naming convention.

### Progress Report (Updated when appropriate)
  - EDIX officially has interrupt support thanks to [wyoos](http://wyoos.org/) (Write Your Own Operating System).

### Download
Download the EDIX kernel by clicking the download link below:\
[Download](https://github.com/Kfeavel/edix/raw/master/build/kernel.bin) (13 KB)

### Installation
Currently EDIX is run using QEMU in kernel mode with the pre-compiled `kernel.bin` file provided in the repository.\
If you want to run EDIX for yourself, download `kernel.bin` in the build/ folder and run the following command:\
`qemu-system-i386 -kernel <path-to-kernel.bin>`\
Additionally, EDIX runs in Virtualbox 5 using `edix.iso` with the following settings:
  - OS Type: Other/Unknown (32-bit)
  - Memory: 64 MB
  - Boot Medium: ISO (no HDD)
  - All other settings are set to the default for the OS Type

### Screenshot
![](https://github.com/Kfeavel/edix/blob/master/current.png?raw=true)
