/*
    stdio
*/

#include "../driver/video/vga.h"
#include "../driver/input/scanf.h"

/* printf */
#define printf(x, ...)             vga_printf(x, ...)

/* putc */
#define putc(x)                    vga_putc(x)

/* cls */
#define cls                        vga_cls

/* setcolor */
#define setcolor(a, b)             vga_setcolor(a, b)

/* putcx */
#define putcx(a, b)                vga_putcx(a, b)
