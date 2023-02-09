/*
      Manipulador da VGA
      Autor: Thiago Pereira Martinez
      Data: 27/09/2013
*/

#include "vga.h"
#include <asm/io.h>
#include <util/string.h>
#include <colors.h>

/* variaveis */
unsigned char *video = (unsigned char *)VGA_MEM_OFFSET; // memória de video
unsigned int offset; // offset da memoria
unsigned short background = COLOR_BLACK; // cor de fundo
unsigned short foreground = COLOR_GRAY_LIGHT; // cor da letra
unsigned short row = 0;
unsigned short col = 0;

// flags
unsigned int flag_update_cursor = 1;

/* vga_putc - imprimir caracter */
void vga_putc(unsigned char c) {
   // imprimir caracter
   video[offset++] = c;
   
   // imprimir atributos
   video[offset++] = (background << 4) | foreground;
   
   // atualizar cursor
   if (! flag_update_cursor)
      return;
   vga_updatecursor();
}

/* vga_printf - imprimir string */
void vga_printf(char *format, ...) {
    char **arg = (char **) &format;
    int c;
    char buf[20];
      
    arg++;
        
    while ((c = *format++) != 0) {
         if (c != '%')
            vga_putc(c);   
         else { 
            char *p;
            c = *format++;
            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                   itoa (buf, c, *((int *) arg++));
                   p = buf;
                   goto string;
                   break;
                   
                case 's':
                   p = *arg++;
                   if (! p)
                      p = "(null)";
                      
                string:
                   while (*p) {
                      vga_putc(*p++);
                   }
                   break;
                   
                default:
                   vga_putc(*((int*) arg++));
                   break;
            }
         }
    }
}

/* vga_printfx - imprimir valor em hexadecimal */
void vga_printfx(unsigned int n) {
   int tmp;
   
   vga_printf("0x");
   char noZeros = 1;
   
   int i;
   for (i = 28; i > 0; i-=4) {
       tmp = (n >> i) & 0xF;  
       if (tmp == 0 && noZeros != 0) {
          continue;
       }
        
       if (tmp >= 0xA) {
          noZeros = 0;  
          vga_putc(tmp-0xA+'a');
       } else {
          noZeros = 0;
          vga_putc(tmp+'0');
       }
   }
    
   tmp = n & 0xF;
   if (tmp >= 0xA) {
      vga_putc(tmp-0xA+'a');
   } else {
      vga_putc(tmp+'0');
   }
}

/* vga_updatecursor - atualizar cursor */
void vga_updatecursor() {
   // definir linha e coluna atual à partir do offset
   if (offset == 0) {
      row = 0;
      col = 0;
   } else { // caso o offset for zero, nao fazer divisao por zero para nao gerar uma excessao
      row = (offset/2)/VGA_NUM_ROWS;
      col = (offset/2)-(VGA_NUM_ROWS*row);
   }

   // posicao   
   unsigned short position=(row*VGA_NUM_COLS) + col;
   
   // cursor LOW port to vga INDEX register
   outb(0x3D4, 0x0F);
   outb(0x3D5, (unsigned char)(position&0xFF));
   // cursor HIGH port to vga INDEX register
   outb(0x3D4, 0x0E);
   outb(0x3D5, (unsigned char)((position>>8)&0xFF));
}

/* vga_cls - limpar tela */
void vga_cls() {
    flag_update_cursor = 0; // nao atualizar cursor
    offset = 0; // retornar ao offset zero
    
    // imprimir espacos em toda tela
    int x = 0;
    for (;x<(VGA_NUM_COLS*(VGA_NUM_ROWS+1));x++) {
        vga_putc(' ');
    }
    
    // retornar o cursor e offset para inicio
    flag_update_cursor = 1;
    offset = 0;
    vga_updatecursor();
}

/* vga_setcolor - setar cor de fundo e texto */
void vga_setcolor(short foreground_color, short background_color) {
    // cor do texto
    if (foreground_color != COLOR_DEFAULT) {
       foreground = foreground_color;
    }

    // cor de fundo
    if (background_color != COLOR_DEFAULT) {
       background = background_color;
    }

}
