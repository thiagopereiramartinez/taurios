# COMPILADORES E LINKER
CC=gcc -m32
ASM=nasm

# PARAMETROS DE COMPILACAO
ASMFLAGS=-f elf
CFLAGS=-Wall -c
LDFLAGS=-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector
INCLUDE=-I ..

# PARAMETROS DO SISTEMA OPERACIONAL
CONFIG_FILE=../../../.config
OS_NAME=`cat $(CONFIG_FILE) | grep OS_NAME | cut -f 2 -d "="`
OS_VERSION=`cat $(CONFIG_FILE) | grep OS_VERSION | cut -f 2 -d "="`
OS_DIST=`cat $(CONFIG_FILE) | grep OS_DIST | cut -f 2 -d "="`

# COMPILACAO - ALL
all: build

build:
	@cd video && $(MAKE)
	@cd sound && $(MAKE)
	@cd hdd && $(MAKE)
	@cd ide && $(MAKE)
	@cd floppy && $(MAKE)

clean:
	@cd video && $(MAKE) clean
	@cd sound && $(MAKE) clean
	@cd hdd && $(MAKE) clean
	@cd ide && $(MAKE) clean
	@cd floppy && $(MAKE) clean
