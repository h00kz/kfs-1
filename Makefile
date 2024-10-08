CP 			=	cp
RM 			=	rm -rf
MKDIR 		=	mkdir -pv

NASM		=	nasm
CC			=	gcc
LD			=	ld

CFLAGS		=	-m32 -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

BIN 		=	kernel.bin
CFG 		=	grub.cfg
ISO_PATH 	=	iso
BOOT_PATH 	=	$(ISO_PATH)/boot
GRUB_PATH 	=	$(BOOT_PATH)/grub

SRCS		=	$(wildcard kernel/*.c)
SRCS		+=	$(wildcard kernel/**/*.c)
SRCS        +=  $(wildcard lib/**/*.c)
BOOT		=	kernel/boot/start.asm
BOOT_OBJ	=	kernel/boot/start.o
GDT			=	$(wildcard kernel/*dt/*.asm)
LINKER		=	linker.ld
OBJS		=	$(patsubst %.asm,%.o,$(GDT))
OBJS		+=	$(patsubst %.c,%.o,$(SRCS))

.PHONY: all clean bootloader linker iso

all: bootloader $(OBJS) linker iso
	@echo Make has completed.

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@ 

%.o: %.asm
	$(NASM) -f elf32 $< -o $@

bootloader: $(BOOT)		
	$(NASM) -f elf32 $(BOOT) -o $(BOOT_OBJ)

linker: $(LINKER) $(BOOT_OBJ) $(OBJS)
	$(LD) -m elf_i386 -T $(LINKER) -o $(BIN) $(BOOT_OBJ) $(OBJS)

iso:
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o my-kernel.iso $(ISO_PATH)

run:
	qemu-system-i386 -cdrom my-kernel.iso

re: clean all run

clean:
	$(RM) kernel/boot/start.o $(OBJS) $(BIN) my-kernel.iso $(ISO_PATH)