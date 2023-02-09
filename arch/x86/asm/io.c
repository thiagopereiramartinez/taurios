/*
   Operacoes de entrada e saida
*/

#include "io.h"

/* outb */
extern void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

/* inb */
extern unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* outl */
extern void outl(unsigned short port, unsigned long val) {
    asm volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

/* inl */
extern unsigned long inl(unsigned short port) {
    unsigned long ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* out */
extern void out(unsigned short port, unsigned short val) {
    asm volatile("out %0, %1" : : "a"(val), "Nd"(port));
}

/* in */
extern unsigned short in(unsigned short port) {
    unsigned long ret;
    asm volatile("in %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* outw */
extern void outw(unsigned short port, unsigned short val) {
    asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

/* inw */
extern unsigned short inw(unsigned short port) {
    unsigned short ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* io_wait */
extern void io_wait(void) {
    asm volatile("jmp 1f\n\t"
                 "1:jmp 2f\n\t"
                 "2:");
}
