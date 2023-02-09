# COMPILADORES E LINKER
CC=gcc -m32
ASM=nasm
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

# PARAMETROS DE COMPILACAO
ASMFLAGS=-f elf
CFLAGS=-Wall -c
LDFLAGS=-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector
INCLUDE=-I ../../..

# PARAMETROS DO SISTEMA OPERACIONAL
CONFIG_FILE=../../../.config
OS_NAME=`cat $(CONFIG_FILE) | grep OS_NAME | cut -f 2 -d "="`
OS_VERSION=`cat $(CONFIG_FILE) | grep OS_VERSION | cut -f 2 -d "="`
OS_DIST=`cat $(CONFIG_FILE) | grep OS_DIST | cut -f 2 -d "="`

# COMPILACAO - ALL
all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) -o $@ $<

clean:
	@rm -f *.o
