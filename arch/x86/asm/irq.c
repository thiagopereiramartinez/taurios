/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Translated by: Mauro J. Sch�tz (maurojoel@gmail.com)
*  Desc: Interrupt Request management
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include "irq.h"
#include "io.h"

/* Est�s s�o ISRs pr�prias que apontam para nosso tratamento especial de IRQ
*  ao inv�s da fun��o regular 'fault_handler' */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* Este arranjo � realmente um arranjo de ponteiros de fun��o. N�s usamos
*  estes para tratar de um IRQ de costume para um IRQ dado */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* Este instala um tratador de IRQ de costume para um IRQ dado */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* Este limpa o tratador para um IRQ dado */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/* Normalmente, IRQs 0 at� 7 s�o mapeados para as entradas 8 at� 15. Este
*  � um problema no modo protegido, porque a entrada IDT 8 � uma
*  Double Fault! Sem remapeamento, a todo tempo que o IRQ0 dispara,
*  voc� obter� uma Exce��o Double Fault, que N�O � realmente
*  o que queremos. N�s enviamos para o Controle Program�vel de
*  Interrup��es (PICs - tamb�m chamado de 8259's) o comando
*  para fazer IRQ0 at� 15 ser remapeado para as entradas IDT 32 at�
*  47 */
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

/* N�s primeiramente remapeamos o controle de interrup��es, e ent�o instalamos
*  os ISRs apropriados para as entradas corretas na IDT. Este � justamente
*  parecido com a instala��o dos tratamentos de exce��es */
void irq_install()
{
    irq_remap();

    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);

    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Cada dos ISRs de IRQ apontam para esta fun��o, em vez do
*  'fault_handler' em 'isrs.c'. O Controlador de IRQ necessita
*  ser avisado quando voc� est� pronto para servi-lo ent�o, assim
*  voc� precisa enviar quando um comando "Fim da Interrup��o" (0x20).
*  H� dois chips 8259: O primeiro existe em 0x20, o segundo
*  existe em 0xA0. Se o segundo controlador (um IRQ de 8 at�
*  15) obt�m uma interrup��o, voc� precisa reconhecer a
*  interrup��o de AMBOS controladores, de outro modo, voc� somente envia
*  um comando FDI (End of Interrupt (EOI)) para o primeiro controlador. 
*  Se voc� n�o enviar um FDI, voc� n�o obter� mais IRQs */
extern void irq_handler(struct regs *r)
{
    /* Este � um ponteiro de fun��o vazio */
    void (*handler)(struct regs *r);

    /* Procura se n�s temos um tratamento comum para rodar este
    *  IRQ, e ent�o finalmente, roda-lo */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* Se a entrada IDT que foi invocada � maior que 40
    *  (significando IRQ8 - 15), ent�o n�s devemos enviar um FDI para
    *  o controlador slave */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* Em qualquer caso, n�s deveremos enviar um FDI para o controlador
    *  de interrup��es master tamb�m */
    outb(0x20, 0x20);
}

/* IRQ Enabled */
int irq_enabled()
{
    int f;
    asm volatile ( "pushf\n\t"
                   "popl %0"
                   : "=g"(f) );
    return f & ( 1 << 9 );
}
