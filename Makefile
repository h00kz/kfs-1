CP := cp
RM := rm -rf
MKDIR := mkdir -pv

BIN = kernel.bin
CFG = grub.cfg
ISO_PATH := iso
BOOT_PATH := $(ISO_PATH)/boot
GRUB_PATH := $(BOOT_PATH)/grub

.PHONY: all
all: bootloader kernel linker iso
	@echo Make has completed.

bootloader: start.asm
	nasm -f elf32 start.asm -o boot.o

kernel: kernel.c
	gcc -m32 -c kernel.c -o kernel.o -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

linker: linker.ld boot.o kernel.o
	ld -m elf_i386 -T linker.ld -o kernel.bin boot.o kernel.o

iso: kernel
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o my-kernel.iso $(ISO_PATH)

.PHONY: clean
clean:
	$(RM) *.o $(BIN) *iso