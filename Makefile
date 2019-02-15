# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c src/cpu/*.c src/libc/*.c)
HEADERS = $(wildcard src/kernel/*.h src/drivers/*.h src/cpu/*.h src/libc/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o} #src/cpu/interrupt.o

# Change this if your cross-compiler is somewhere else
# Installing i386-elf-binutils using brew on macOS fixes
# the need for a custom cross compiler
CC = i386-elf-gcc
GDB = i386-elf-gdb

# -g: Use debugging symbols in gcc
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32

# First rule is run by default
dist/panix.raw: src/boot/boot32.bin src/kernel/kernel.bin
	mkdir -p dist
	cat $^ > $@

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
src/kernel/kernel.bin: src/boot/32bit/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: src/boot/32bit/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: dist/panix.raw
	qemu-system-i386 -s -fda $< &
	#qemu-system-i386 $< -boot c

# Gets a disk read error
run_from_disk: dist/panix.raw
	qemu-system-i386 $< -boot c

run_from_floppy: dist/panix.raw
	qemu-system-i386 -fda $<

# Open the connection to qemu and load our kernel-object file with symbols
debug: dist/panix.raw kernel.elf
	qemu-system-i386 -s -fda $< &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o dist/panix.raw *.elf
	rm -rf src/boot/*.bin src/boot/*.o src/cpu/*.bin src/cpu/*.o src/drivers/*.bin src/drivers/*.o src/kernel/*.bin src/kernel/*.o
