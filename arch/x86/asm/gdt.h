/*
    Global Descriptor Table
*/

/* Define uma entrada GDT. Nós dizemos packed (empacotado), porque isto previne o
*  compilador de por coisas pensando ser melhores: Previne
*  compilação "otimizada" por empacotamento */
struct gdt_entry {
   unsigned short limit_low;
   unsigned short base_low;
   unsigned char base_middle;
   unsigned char access;
   unsigned char granularity;
   unsigned char base_high;
} __attribute__((packed));

/* Ponteiro especial que inclui o limite: O máximo de bytes
*  tomados pela GDT, menos 1. Outra vez, este PRECISA ser packed (empacotado) */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
        

/* gdt_install */
void gdt_install();

/* gdt_set_gate */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

