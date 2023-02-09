/*
   form - formulario
*/

#include <driver/video/vga.h>
#include <driver/video/ui/paint.h>
#include <include/colors.h>
#include <util/string.h>

/* form_draw */
void form_draw(char *title, char *menu) {
   // Limpar tela
//   paint_init(COLOR_GREY, COLOR_BLUE);
//   paint_fill_all();

   // Imprimir titulo   
   vga_setposition(0, 0);
   vga_setcolor(COLOR_RED, COLOR_GREY);
   int tmp = (80 - strlen(title)) / 2;
   int x;
   for (x=0;x<tmp;x++) {
       putc(' ');
   }
   
   printf(title);
   int tmp2 = 80 - tmp - strlen(title);
   for (x=0;x<tmp2;x++) {
       putc(' ');
   }
   
   // Imprimir menu
   vga_setposition(0, 24);
   vga_setcolor(COLOR_BLUE, COLOR_GREY);
   int h = 0;
   int tmp3 = 0;
   while (*menu) {
   
      // Ligar highlight
      if (*menu == '|' && h == 0) {
         h = 1;
         vga_setcolor(COLOR_RED, COLOR_GREY);
         menu++;
         continue;
      }
      
      // Desligar highlight
      if (*menu == '|' && h == 1) {
         h = 0;
         vga_setcolor(COLOR_BLUE, COLOR_GREY);
         menu++;
         continue;
      }
      
      // Imprimir texto
      putc(*menu);
      menu++;
      tmp3++;
      
      // Sair se ja foi impresso 80 caracteres
      if (tmp3 >= 80)
         break;
   }
   
   // Preencher com espaco, caso o menu for menor que 80 caracteres
   int tmp4;
   for (tmp4=0;tmp4<(80-tmp3);tmp4++) {
      putc(' ');
   }
   
   // Mover para o topo do formulario e restaurar cor
   vga_setcolor(COLOR_GREY, COLOR_BLUE);
   vga_setposition(1, 0);
}
