###############################################
# COMPILADOR DOS ARQUIVOS DE FUNCOES ASM      #
###############################################

# COMPILADORES
CC=gcc
ASMC=nasm

# PARAMETROS DE COMPILACAO
ASMFLAGS=-f elf32
CFLAGS=-Wall -g -c -I .. -I ../include -I ../../../include
LDFLAGS=-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector

# FONTES
SRC_C=$(wildcard *.c)
SRC_ASM=$(wildcard *.S)
OBJ_C=$(SRC_C:.c=.o)
OBJ_ASM=$(SRC_ASM:.S=.o)

# COMPILACAO
all: build

build: $(OBJ_ASM) $(OBJ_C)

%.o: %.c
	@echo "		[CC]	$@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	
%.o: %.S
	@echo "		[ASM]	$@"
	@$(ASMC) $(ASMFLAGS) -o $@ $<

clean:
	@rm -f *.o
