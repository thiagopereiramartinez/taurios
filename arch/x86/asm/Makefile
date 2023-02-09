# COMPILADORES E LINKER
CC=gcc -m32
ASM=nasm

#SOURCE
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
SRC_ASM=$(wildcard *.s)
OBJ_ASM=$(SRC_ASM:.s=.o)

# PARAMETROS DE COMPILACAO
ASMFLAGS=-f elf
CFLAGS=-c
LDFLAGS=-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector
INCLUDE=-I ..

# PARAMETROS DO SISTEMA OPERACIONAL
CONFIG_FILE=../../../.config
OS_NAME=`cat $(CONFIG_FILE) | grep OS_NAME | cut -f 2 -d "="`
OS_VERSION=`cat $(CONFIG_FILE) | grep OS_VERSION | cut -f 2 -d "="`
OS_DIST=`cat $(CONFIG_FILE) | grep OS_DIST | cut -f 2 -d "="`

# COMPILACAO - ALL
all: build

build: $(OBJ_ASM) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) -o $@ $<
	
%.o: %.s
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	@rm -f *.o
