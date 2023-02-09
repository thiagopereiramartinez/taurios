# COMPILADORES E LINKER
CC=gcc -m32
ASM=nasm

# DIRETORIOS
DIR_BOOT=arch/x86/boot
DIR_ASM=arch/x86/asm
DIR_UTIL=arch/x86/util
DIR_FS=arch/x86/fs
DIR_DRIVER=arch/x86/driver

# PARAMETROS DE COMPILACAO
CFLAGS=-Wall
LDFLAGS=-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector
INCLUDE=arch/x86/include

# PARAMETROS DO SISTEMA OPERACIONAL
OS_NAME=`cat .config | grep OS_NAME | cut -f 2 -d "="`
OS_DIST=`cat .config | grep OS_DIST | cut -f 2 -d "="`
OS_VERSION=`cat .config | grep OS_VERSION | cut -f 2 -d "="`

# COMPILACAO - ALL
all: build mkdist

build:
	@cd $(DIR_BOOT) && $(MAKE)
	@cd $(DIR_ASM) && $(MAKE)
	@cd $(DIR_UTIL) && $(MAKE)
	@cd $(DIR_FS) && $(MAKE)
	@cd $(DIR_DRIVER) && $(MAKE)

mkdist:
	ld -m elf_i386 -T $(DIR_BOOT)/linker.ld -o dist/kernel/$(OS_NAME)-$(OS_DIST)_$(OS_VERSION)_x86.bin \
	    $(DIR_BOOT)/loader.o \
	    $(DIR_BOOT)/main.o \
	    $(DIR_ASM)/gdt.o \
	    $(DIR_ASM)/gdt_asm.o \
	    $(DIR_ASM)/idt.o \
	    $(DIR_ASM)/idt_asm.o \
	    $(DIR_ASM)/isr.o \
	    $(DIR_ASM)/isr_asm.o \
	    $(DIR_ASM)/irq.o \
	    $(DIR_ASM)/irq_asm.o \
	    $(DIR_ASM)/a20.o \
	    $(DIR_ASM)/a20_asm.o \
	    $(DIR_ASM)/keyboard.o \
	    $(DIR_ASM)/mouse.o \
	    $(DIR_ASM)/paging.o \
	    $(DIR_ASM)/io.o \
	    $(DIR_ASM)/cpudet.o \
	    $(DIR_ASM)/timer.o \
	    $(DIR_ASM)/cmos.o \
	    $(DIR_ASM)/power.o \
	    $(DIR_ASM)/pci.o \
	    $(DIR_BOOT)/console.o \
	    $(DIR_DRIVER)/video/vga.o \
	    $(DIR_DRIVER)/video/art/asciiart.o \
	    $(DIR_DRIVER)/video/ui/paint.o \
	    $(DIR_DRIVER)/video/ui/form.o \
	    $(DIR_DRIVER)/video/ui/form_inicial.o \
	    $(DIR_DRIVER)/sound/speaker.o \
	    $(DIR_DRIVER)/hdd/hdd.o \
	    $(DIR_DRIVER)/ide/ide.o \
	    $(DIR_DRIVER)/floppy/floppy.o \
	    $(DIR_FS)/mbr.o \
	    $(DIR_FS)/filesystem.o \
	    $(DIR_FS)/file.o \
	    $(DIR_FS)/fat32/fat32.o \
	    $(DIR_UTIL)/alloc.o \
	    $(DIR_UTIL)/memutil.o \
	    $(DIR_UTIL)/string.o \
	    $(DIR_UTIL)/scanf.o \
	    $(DIR_UTIL)/datetime.o

	cd dist/iso/src && cp ../../kernel/*.bin boot/kernel
	cd dist/iso/src && \
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ../kernel.iso .
	    
emu:
	qemu -hda /dev/sdb -kernel dist/kernel/$(OS_NAME)-$(OS_DIST)_$(OS_VERSION)_x86.bin

debug:
	qemu -s -S -hda /dev/sdb -kernel dist/kernel/$(OS_NAME)-$(OS_DIST)_$(OS_VERSION)_x86.bin & gdb

clean:
	@rm -f *.bin
	@cd $(DIR_BOOT) && $(MAKE) clean
	@cd $(DIR_ASM) && $(MAKE) clean
	@cd $(DIR_UTIL) && $(MAKE) clean
	@cd $(DIR_FS) && $(MAKE) clean
	@cd $(DIR_DRIVER) && $(MAKE) clean
	@rm -f dist/iso/*.iso
	@rm -f dist/iso/src/boot/kernel
	@rm -f dist/kernel/*

