/* include */
#include <asm/idt.h>
#include <driver/video/vga.h>
#include <include/colors.h>
#include <include/regs.h>

/* Est�s s�o prot�tipos de fun��es de toda as tratamentos de
*  exce��es: As primeiras 32 entradas na IDT s�o reservadas
*  pela Intel, e s�o designadas para interrup��es de servi�os! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* Este � um simples arranjo de string. Que cont�m as mensagens que
*  correspondem para cada e toda exce��o. N�s obtemos a mensagem
*  correta acessando por:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* Est� � uma fun��o muito repetitiva... n�o � dif�cil, �
*  somente aborrecedor. Como voc� pode ver, n�s atribu�mos as 32 entradas
*  na IDT para as primeiras 32 ISRs. N�s n�o podemos usar um la�o for
*  para este, porque n�o a caminho de se obter os nomes das fun��es
*  que correspondem para cada entrada. N�s atribu�mos as flags de
*  entrada para 0x8E. Fazer que a entrada esteja presente, est�
*  rodando em ring 0 (n�vel kernel), e que os 5 bits inferiores
*  estejam atribu�dos para o requerido '14', que � representado por 'E' 
*  em hexadecimal. */
void isr_install()
{
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);

    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);

    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);

    idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}

/* kernel_panic */
void kernel_panic(unsigned int int_no) {
    vga_setcolor(COLOR_RED, COLOR_BLACK);
    printf("\nKernel Panic: %s Exception\nSystem stopped.\n", exception_messages[int_no]);
    for (;;); // Parar o sistema
}

/* page_fault */
void page_fault(int err_code) {
    unsigned int fault;
    asm volatile("mov %%cr0, %0" : : "r"(fault));
    
    int present = !(err_code & 0x1);
    int rw = err_code & 0x2;
    int us = err_code & 0x4;
    int reserved = err_code &0x8;
    int id = err_code & 0x10;

    unsigned char *exception[] = {
        "present",
        "read-only",
        "user-mode",
        "reserved",
        "unknown"
    };

    vga_setcolor(COLOR_RED, COLOR_BLACK);
    printf("\nKernel Panic: %s Exception (%s) at ", exception_messages[14], exception[present ? 0 : rw ? 1 : us ? 2 : reserved ? 3 : 4]);
    printf_hex(fault);
    printf("\nSystem stopped.\n");
    for (;;); // Parar o sistema
}

/* error_message */
void error_message(unsigned int int_no) {
    printf("%s Exception.\n", exception_messages[int_no]);
    // Parar por nao saber ficar em loop (DEPRECATED)
    vga_setcolor(COLOR_RED, COLOR_BLACK);
    printf("DEPRECATED: Not continue code. System stopped.\n");
    for (;;);
}


/* Todas nossas exce��es tratadas pelas Rotinas de Servi�o de Interrup��o v�o
*  apontar para esta fun��o. Este vai nos dizer qual exce��o tem
*  ocorrido! Diretamente agora, n�s simplesmente vamos parar o sistema pelo usando um
*  la�o sem fim. Todas ISRs desabilitam interrup��es enquanto estes est�o sendo
*  servidos como um mecanismo de 'tranca' para prevenir que um IRQ
*  ocorra e perdendo as estruturas de dados do kernel */
void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
       switch(r->int_no) {
          case 0: error_message(0);break; // Division by zero
          case 1: error_message(1);break; // Debug
          case 2: kernel_panic(2);break; // Non Maskable Interrupt
          case 3: error_message(3);break; // Breakpoint
          case 4: kernel_panic(4);break; // Into Detected Overflow
          case 5: error_message(5);break; // Out of Bounds
          case 6: kernel_panic(6);break; // Invalid Opcode
          case 7: kernel_panic(7);break; // No Coprocessor
          case 8: kernel_panic(8);break; // Double Fault
          case 9: kernel_panic(9);break; // Coprocessor Segment Overrun
          case 10: kernel_panic(10);break; // Bad TSS
          case 11: kernel_panic(11);break; // Segment Not Present
          case 12: kernel_panic(12);break; // Stack Fault
          case 13: error_message(13);break; // General Protection Fault
          case 14: page_fault(r->err_code);break; // Page Fault
          case 15: kernel_panic(15);break; // Unknown Interrupt
          case 16: kernel_panic(16);break; // Coprocessor Fault
          case 17: kernel_panic(17);break; // Alignment Check
          case 18: kernel_panic(18);break; // Machine Check
          default: kernel_panic(r->int_no);break; // Others
       }
    }
}
