/*
    Global Descriptor Table
*/

/* include */
#include "gdt.h"

/* Nossa GDT, com 3 entradas, e finalmente nosso ponteiro especial de GDT */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* Este � uma fun��o do start.asm. N�s usamos este para apropriadamente
*  recarregar os novo registradores de segmento */
extern void gdt_flush();

/* Atribui um descritor na Tabela de Descritores Global */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    /* Atribui o endere�o do descritor base */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
                
    /* Atribui os limites do descritor */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
                            
    /* Finalmente, atribui as flags de granularidade e de acesso */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
                                        
/* Precisa ser chamado por main. Este vai atribuir o ponteiro especial
*  GDT, atribui as primeiras 3 entradas na nossa GDT, e ent�o
*  finalmente chama gdt_flush() em nosso arquivo assembly
*  para chamar o processador dizendo onde nossa nova GDT est� e atualizar os
*  novos registradores de segmento */
void gdt_install() {
    /* Atribui o ponteiro GDT e limite */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (int) &gdt;

    /* Nosso descritor NULO (NULL) */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* A segunda entrada � nosso Segmento de C�digo (Code Segment). O endere�o base
    *  � 0, o limite � 4GBytes, este usa granularidade de 4KByte,
    *  usa opcodes de 32-bit, e � um descritor de Segmento de C�digo.
    *  Por favor checar a tabela acima no tutorial
    *  para ver o que exatamente o que cada valor significa */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    /* A terceira entrada � nosso Segmento de Dados (Data Segment). Este � EXATAMENTE
    *  igual ao nosso segmento de c�digo, mas o tipo de descritor neste
    *  byte de entrada diz que este � um Segmento de Dados */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    /* User mode code segment */
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    /* User mode data segment */
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    /* Descarta a antiga GDT e instala as novas mudan�as! */
    gdt_flush();
}
