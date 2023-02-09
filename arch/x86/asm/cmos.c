/*
    CMOS
*/
#include <asm/irq.h>
#include <asm/io.h>
#include <driver/video/vga.h>

/* estrutura do cmos */
struct str_cmos {	
   unsigned int seconds;
   unsigned int minutes;
   unsigned int hours;
   unsigned int week;
   unsigned int day;
   unsigned int month;
   unsigned int year;
   unsigned int century;
   unsigned int status_a;
   unsigned int status_b;
};

struct str_cmos cmos_current;

/* preparar */
void cmos_prepare(void) {
   /* obter valores */
   outb(0x70, 0x00); // segundos
   cmos_current.seconds = inb(0x71);

   outb(0x70, 0x02); // minutos
   cmos_current.minutes = inb(0x71);

   outb(0x70, 0x04); // horas
   cmos_current.hours = inb(0x71);

   outb(0x70, 0x06); // dia da semana
   cmos_current.week = inb(0x71);

   outb(0x70, 0x07); // dia do mes
   cmos_current.day = inb(0x71);

   outb(0x70, 0x08); // mes
   cmos_current.month = inb(0x71);

   outb(0x70, 0x09); // ano
   cmos_current.year = inb(0x71);

   outb(0x70, 0x32); // century
   cmos_current.century = inb(0x71);

   outb(0x70, 0x0A); // status A
   cmos_current.status_a = inb(0x71);

   outb(0x70, 0x0B); // status B
   cmos_current.status_b = inb(0x71);
   
   /* ajustar dados */
   cmos_current.seconds = (cmos_current.seconds & 0x0F) + ((cmos_current.seconds / 16) * 10);
   cmos_current.minutes = (cmos_current.minutes & 0x0F) + ((cmos_current.minutes / 16) * 10);
   cmos_current.hours = ( (cmos_current.hours & 0x0F) + (((cmos_current.hours & 0x70) / 16) * 10) ) | (cmos_current.hours & 0x80);
   cmos_current.day = (cmos_current.day & 0x0F) + ((cmos_current.day / 16) * 10);
   cmos_current.month = (cmos_current.month & 0x0F) + ((cmos_current.month / 16) * 10);
   cmos_current.year = (cmos_current.year & 0x0F) + ((cmos_current.year / 16) * 10);   
}

/* tratamento da IRQ */
void cmos_handler(struct regs *r) {
    cmos_prepare();
}

/* instalar */
void cmos_install(void) {
    irq_install_handler(8, cmos_handler);
}

/* obter cmos */
struct str_cmos cmos_getdata() {
    return cmos_current;
}
