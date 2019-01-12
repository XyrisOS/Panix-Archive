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
LINKER = $(addprefix src/, linker.ld)

objects = $(addprefix obj/, loader.o kernel.o kprint.o term.o gdt.o segdescriptor.o port.o interruptstubs.o interruptmanager.o keyboard.o)
#objects := $(wildcard $(OBJ)/*.o)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CPPPARAMS) -c -o $@ $<
$(OBJ)/%.o: $(SRC)/%.s
	mkdir -p $(OBJ)
	$(AS) $(ASPARAMS) -o $@ $<

$(EXECUTABLE): $(LINKER) $(objects)
	ld $(LDPARAMS) -T $< -o $(BUILD)/$@ $(objects)

install: $(BUILD)/$(EXECUTABLE)
	sudo cp $< /boot/$(EXECUTABLE)

.PHONY: clean
clean:
	rm -rf $(OBJ)/*.o $(BUILD)/$(EXECUTABLE)

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
	qemu-system-i386 -kernel $(addprefix $(BUILD)/, $(EXECUTABLE))
	# Virtualbox --startvm EDIX &
