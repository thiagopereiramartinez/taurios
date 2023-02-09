/*
    power
*/

#include <asm/io.h>
#include <asm/timer.h>
#include <driver/video/vga.h>
#include <driver/sound/speaker.h>
#include <include/colors.h>

/* reiniciar */
void reboot() {
   // Mensagem
   vga_setcolor(COLOR_RED, COLOR_BLACK);
   printf("Rebooting system...\n");
   beep();
   timer_sleep(1);
   
   __asm__ __volatile__ ("cli" : : : "memory");
   __asm__ __volatile__ ("cli" : : : "memory");
   
   outb(0x64, 0xFE);
   __asm__ __volatile__ ("cli\n hlt");
}

/* desligar */
void halt() {
   // Mensagem
   vga_setcolor(COLOR_RED, COLOR_BLACK);
   printf("Halting system...\n");
   beep();
   timer_sleep(1);
   
   __asm__ __volatile__ ("cli" : : : "memory");
   __asm__ __volatile__ ("cli" : : : "memory");
   
   out(0x64, 0xFE);
   __asm__ __volatile__ ("cli\n hlt");
}


