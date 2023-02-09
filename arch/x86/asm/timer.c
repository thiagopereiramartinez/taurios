/*
    Timer (PIT)
*/
#include <asm/irq.h>
#include <driver/video/vga.h>

/* contador */
long int timer_tick = 0;
long int timer_temp = 0;

/* tratamento da IRQ */
void timer_handler(struct regs *r) {
   // incrementar contador
   timer_tick++;
   timer_temp++;
}

/* sleep */
void timer_sleep(int seconds) {
   int seconds_temp = 0;
   for (;seconds_temp<seconds;seconds_temp++) {
       timer_temp = 1;
       while ( (timer_temp % 18) != 0) {}
   }
}

/* sleep 500ms */
void timer_sleep_500ms(int cicles) {
   int seconds_temp = 0;
   for (;seconds_temp<cicles;seconds_temp++) {
       timer_temp = 1;
       while ( (timer_temp % 9) != 0) {}
   }
}

/* sleep cicles */
void timer_sleep_cicles(int cicles) {
   timer_temp = 0;
   while (timer_temp != cicles) {}
}

/* instalar */
void timer_install(void) {
    irq_install_handler(0, timer_handler);
}
