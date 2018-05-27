CXX = g++
AS = as
CPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -std=c++11
ASPARAMS = --32
LDPARAMS = -melf_i386

SRC = src
OBJ = obj
BUILD = build

EXECUTABLE = kernel.bin
ISO = edix.iso
LINKER = linker.ld

objects = loader.o kernel.o kprint.o term.o gdt.o segdescriptor.o port.o

%.o: $(SRC)/%.cpp
	$(CXX) $(CPPPARAMS) -c -o $@ $<
%.o: $(SRC)/%.s
	$(AS) $(ASPARAMS) -o $@ $<

$(EXECUTABLE): $(LINKER) $(objects)
	ld $(LDPARAMS) -T $< -o $(BUILD)/$@ $(objects)

install: $(EXECUTABLE)
	sudo cp $< /boot/$(EXECUTABLE)

.PHONY: clean
clean:
	rm -rf $(objects) $(BUILD)/$(EXECUTABLE) $(BUILD)/$(ISO)

$(ISO): $(EXECUTABLE)
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $(BUILD)/$< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "EDIX Kernel" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(BUILD)/$@ iso
	rm -rf iso
	
run: $(EXECUTABLE)
	qemu-system-i386 -kernel $(EXECUTABLE)
	# Virtualbox --startvm EDIX &
