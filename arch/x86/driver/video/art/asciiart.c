/*
   ASCII Art
*/

/* include */
#include <driver/video/vga.h>
#include <driver/video/art/asciiart.h>

/* mostrar arte */
void asciiart_display(art_img *ai) {
   int l=0;
   int c=0;
   int i=0;
   for (;l<24;l++) {
       for (;c<80;c++) {
           vga_setposition(ai->pix_img[i].x_img, ai->pix_img[i].y_img);
           putc(ai->pix_img[i].c_img);
           i++;
       }
       c=0;
   }
}
