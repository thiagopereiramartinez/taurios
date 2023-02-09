; Carrega a IDT definida como '_idtp' dentro do processador.
; Este é declarado em C como 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret
