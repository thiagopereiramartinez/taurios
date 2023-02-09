/*
    paint.c - Desenho de interface no modo texto (80x25x16)
*/

#include "paint.h"
#include <driver/video/vga.h>

/* paint_init */
void paint_init(unsigned int foreground, unsigned int background) {
   vga_init();
   vga_cls();
   vga_setcolor(foreground, background);
   vga_setposition(0,0);   
}

/* fill_all */
void paint_fill_all(void) {
   vga_cls();
   vga_setposition(0,0);   
}

/* paint_draw_line */
void paint_draw_line(unsigned int posx, unsigned int posy, unsigned int size, char c) {
   vga_setposition(posx, posy);
   int x;
   for (x=0;x<size;x++)
       putc(c);
}

/* paint_draw_rect */
void paint_draw_rect(const unsigned int xv1, const unsigned int yv1, const unsigned int xv2, const unsigned int yv2, const unsigned int xv3, const unsigned int yv3, const unsigned int xv4, const unsigned int yv4, const unsigned int border) {
   // especifica a bordar (simples, ou dupla): padrao simples
   char c = 196;
   char v1 = 218;
   char v2 = 191;
   char v3 = 192;
   char v4 = 217;
   char a = 179;
   if (border == 2) {
      c = 205;
      v1 = 201;
      v2 = 187;
      v3 = 200;
      v4 = 188;
      a = 186;
   }

   paint_putc(xv1, yv1, v1);
   paint_draw_line((xv1+1), yv1, (xv2 - xv1 - 2), c);
   paint_putc((xv2-1), yv2, v2);
   
   int x;
   for (x=1;x<(yv3 - yv1 - 2);x++) {
       paint_putc(xv1, (yv1+x), a);
       paint_draw_line((xv1+1), (yv1+x), (xv2 - xv1 -2), ' ');
       paint_putc(xv2-1, (yv2+x), a);
   }

   paint_putc(xv3, (yv3-2), v3);
   paint_draw_line((xv3+1), (yv3-2), (xv4 - xv3 - 2), c);
   paint_putc((xv4-1), (yv4-2), v4);
   
}

/* paint_putc */
void paint_putc(unsigned int posx, unsigned int posy, char c) {
   vga_setposition(posx, posy);
   putc(c);
}

/* paint_printf */
void paint_printf(unsigned int posx, unsigned int posy, char c) {
   vga_setposition(posx, posy);
   putc(c);
}
