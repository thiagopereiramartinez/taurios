/*
   Interrupt Descriptor Table
*/

#include "idt.h"
#include <asm/io.h>
#include <util/memutil.h>

/* Declara uma IDT de 256 entradas. Embora n�s unicamente usaremos as
*  primeiras 32 entrada neste tutorial, o resto existe como um bit
*  de uma armadilha. Se qualquer entrada IDT est� batendo, isto normalmente
*  vai causar uma exce��o "Interrup��o Intrat�vel". Qualquer descritor
*  para que o bit de 'presen�a' esteja limpo (0) vai gerar uma
*  exce��o "Interrup��o Intrat�vel" */
struct idt_entry idt[256];
struct idt_ptr idtp;
                            
/* Este existe em 'start.asm', e � usado para carregar nossa IDT */
extern void idt_load();

/* Use est� fun��o para atribuir uma entrada na IDT. Bem simples
*  do que brincar com a GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    /* A endere�o base da rotina de interrup��o */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* O segmento ou 'seletor' que est� entrada IDT vai usar
    *  � atribuido aqui, junto com quaisquer flags de acesso */
    idt[num].sel = sel;   
    idt[num].always0 = 0;
    idt[num].flags = flags;
}
                    
/* Instala a IDT */
void idt_install() {
    /* Atribui o ponteiro especial IDT, justamente como em 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (int) &idt;

    /* Limpa o IDT inteiro, inicializando-o com zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Adicione qualquer ISRs novas para a IDT aqui usando idt_set_gate */

    /* Aponta o registro interno do processador para a nova IDT */
    idt_load();
}
