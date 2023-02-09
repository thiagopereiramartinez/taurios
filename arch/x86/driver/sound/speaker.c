/*
    PC Speaker
*/

#include "speaker.h"
#include <asm/io.h>
#include <asm/timer.h>

/* play sound */
void play_sound(int frequence) {
   int div = 1193180 / frequence;
   int tmp;
   
   // Set the PIT to the desired frequence
   outb(0x43, 0xb6);
   outb(0x42, (int) div);
   outb(0x42, (int) (div >> 8));
   
   // And play the sound using the PC speaker
   tmp = inb(0x61);
   if (tmp != (tmp | 3)) {
      outb(0x61, tmp | 3);
   }
}

/* no sound */
void nosound() {
   int tmp = (inb(0x61) & 0xFC);
   outb(0x61, tmp);
}

/* beep */
void beep() {
   play_sound(1000);
   timer_sleep_500ms(1);
   nosound();
}
