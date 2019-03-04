# $@ = target file
# $< = first dependency
# $^ = all dependencies

CXX_SOURCES = $(wildcard src/kernel/*.cpp src/kernel/util/*.cpp src/drivers/*.cpp src/drivers/*/*.cpp src/cpu/*.cpp src/cpu/*/*.cpp src/libc/*.cpp src/libc/*/*.cpp)
HEADERS = $(wildcard src/kernel/*.h src/kernel/util/*.h src/drivers/*.h src/drivers/*/*.h src/cpu/*.h src/cpu/*/*.h src/libc/*.h src/libc/*/*.h)

# Nice syntax for file extension replacement
CXX_OBJ = ${CXX_SOURCES:.cpp=.o src/cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
# Installing i386-elf-binutils using brew on macOS fixes
# the need for a custom cross compiler
CXX = i386-elf-gcc
GDB = i386-elf-gdb

CXX_FLAGS = -fno-pie -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -lstdc++ -std=c++17

# First rule is run by default
dist/panix.raw: src/boot/boot32.bin src/kernel/kernel.bin
	mkdir -p dist
	cat $^ > $@

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
src/kernel/kernel.bin: src/boot/32bit/kernel_entry.o ${CXX_OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: src/boot/32bit/kernel_entry.o ${CXX_OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: dist/panix.raw
	@ echo Booting from disk...
	qemu-system-i386 $< -boot c

run_from_disk: dist/panix.raw
	@ echo Booting from disk...
	qemu-system-i386 $< -boot c

run_from_floppy: dist/panix.raw
	@ echo Booting from floppy...
	qemu-system-i386 -fda $<

dist: dist/panix.raw
	@ echo Building VDI image of Panix...
	@ qemu-img convert -f raw -O vdi dist/panix.raw dist/panix.vdi
	@ echo Done building VDI image of Panix!

	@ echo "\nBuilding VMDK image of Panix..."
	@ qemu-img convert -f raw -O vmdk dist/panix.raw dist/panix.vmdk
	@ echo Done building VMDK image of Panix!

# Open the connection to qemu and load our kernel-object file with symbols
debug: dist/panix.raw kernel.elf
	@ echo Booting from floppy...
	qemu-system-i386 -s -fda $< &
	@ echo Setting up GDB with qemu...
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .cpp
%.o: %.cpp ${HEADERS}
	${CXX} ${CXX_FLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	@ echo Cleaning root directory...
	@ rm -rf *.bin *.dis *.o dist/panix.raw *.elf
	
	@ echo Cleaning boot directories...
	@ rm -rf src/boot/*.bin src/boot/*.o 
	@ rm -rf src/boot/32bit/*.bin src/boot/32bit/*.o
	
	@ echo Cleaning cpu directories...
	@ rm -rf src/cpu/*.bin src/cpu/*.o
	@ rm -rf src/cpu/*/*.bin src/cpu/*/*.o
	
	@ echo Cleaning driver directories...
	@ rm -rf src/drivers/*.bin src/drivers/*.o
	@ rm -rf src/drivers/*/*.bin src/drivers/*/*.o
	
	@ echo Cleaning kernel directory...
	@ rm -rf src/kernel/*.bin src/kernel/*.o
	
	@ echo Cleaning libc directories...
	@ rm -rf src/libc/*.bin src/libc/*.o
	@ rm -rf src/libc/*.bin src/libc/*/*.o

	@ echo "\nDone cleaning!"

clean-docs:
	@ echo Cleaning old documentation...
	@ find docs/ ! -name CNAME ! -name robots.txt -type f -delete
	@ echo "\nDone cleaning documentation!"

.PHONY: docs
docs: 
	@ echo Generating documentation...
	@ doxygen ./doxygen.config
	@ echo "\nDone generating documentation!"