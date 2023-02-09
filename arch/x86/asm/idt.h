/*
   Interrupt Descriptor Table
*/

/* Define uma entrada IDT */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Nosso segmento do kernel vai aqui! */
    unsigned char always0;     /* Este vai ser sempre ser atribuído para 0! */
    unsigned char flags;       /* Conjunto usando a tabela acima! */
    unsigned short base_hi;
} __attribute__((packed));
                    
struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Este existe em 'start.asm', e é usado para carregar nossa IDT */
extern void idt_load();

/* Use está função para atribuir uma entrada na IDT. Bem simples
*  do que brincar com a GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

/* Instala a IDT */
void idt_install();

