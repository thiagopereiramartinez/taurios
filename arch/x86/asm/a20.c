/*
   A20
*/

#include "a20.h"
#include <driver/video/vga.h>

/* enable */
void a20_enable(void) {
   __a20_enable();
}

/* test */
void a20_test(void) {
   __a20_test();
}

/* enabled */
extern void a20_enabled(void) {
   printf("A20: Enabled\n");
}

/* disabled */
extern void a20_disabled(void) {
   printf("A20: Disabled\n");
}
