/*
      vga.c - Video
*/

/* include */
#include "vga.h"
#include <asm/io.h>
#include <util/memutil.h>
#include <util/string.h>
#include <include/colors.h>
#include <include/vga_memory.h>

/* variaveis */
unsigned char *vga_mem;
unsigned int vga_current_color = COLOR_GREY; // cor do texto padrao
unsigned int vga_width = 80; // 80 colunas
unsigned int vga_height = 25; // 25 linhas
unsigned int vga_current_x = 0; // posicao X
unsigned int vga_current_y = 0; // posicao Y
unsigned int vga_current_offset = 0;
unsigned int __vga_noscroll = 0;

/* iniciar */
void vga_init(void) {
    vga_mem = (unsigned char *) VGA_MEM;
}

/* scroll */
void vga_scroll(void) {
    // Somente se estiver na ultima linha ou __vga_noscroll desativado
    if (vga_current_y < 25 || __vga_noscroll == 1)
       return;

    // Copiar
    unsigned int x;
    for (x=0;x<vga_height;x++) {
        unsigned int offset_destino = vga_width * x * 2; // Linha anterior
        unsigned int offset_fonte = vga_width * (x+1) * 2; // Linha
        unsigned int y;
        for (y=0;y<(vga_width*2);y++) {
            unsigned pos_fonte = offset_fonte+y;
            unsigned pos_destino = offset_destino+y;
            vga_mem[pos_destino] = vga_mem[pos_fonte];
        }
    }

    vga_setposition(vga_current_x, (vga_height-1));
}

/* setar cor */
void vga_setcolor(unsigned int foreground, unsigned int background) {
    vga_current_color = (background << 4) | (foreground & 0x0F);
}

/* setar posicao */
void vga_setposition(unsigned int x, unsigned int y) {
    vga_current_x = x;
    vga_current_y = y;
    vga_current_offset = (vga_current_y * vga_width * 2) + (vga_current_x*2);
    __vga_movecursor();
}

/* mover cursor - asm */
void __vga_movecursor(void) {
    unsigned int temp;
    
    temp = vga_current_y * vga_width + vga_current_x;
    
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}

/* limpar tela */
void vga_cls(void) {
    vga_current_offset = 0;
    vga_current_x = 0;
    vga_current_y = 0;
    unsigned int x;
    for (x=0;x<(vga_width*vga_height*2);x++) {
        __vga_noscroll = 1;
        putc(' ');
    }
    __vga_noscroll = 0;
    vga_current_offset = 0;
    vga_current_x = 0;
    vga_current_y = 0;
}

/* imprimir caracter */
void putc(const char c) {
    // backspace
    if ((int) c == 8) {
       vga_current_x--;
       vga_current_offset=vga_current_offset-2;
       vga_scroll();
       __vga_movecursor();
       vga_mem[vga_current_offset] = ' ';
       return;
    }
    
    // nova linha
    if (c == 0x0A || vga_current_x == vga_width) {
       vga_current_y++;
       vga_current_x=0;
       vga_setposition(vga_current_x, vga_current_y);
       vga_scroll();
       return;
    }

    vga_mem[vga_current_offset] = c;
    vga_current_offset++;
    vga_mem[vga_current_offset] = vga_current_color;
    vga_current_offset++;
    
    vga_current_x++;
    vga_setposition(vga_current_x, vga_current_y);
    vga_scroll();
}

/* putcx */
void putcx(const char *m, unsigned int len) {
   int i;
   for (i=0;i<len;i++) {
       putc(*m);
       m++;
   }
}

/* Format a string and print it on the screen, just like the libc
   function printf.  */
void printf(char *format, ...)
{
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;
  
  while ((c = *format++) != 0)
    {
      if (c != '%')
	putc(c);
      else
	{
	  char *p;
	  
	  c = *format++;
	  switch (c)
	    {
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
		putc(*p++);
              }
	      break;

	    default:
              putc(*((int*) arg++));
	      break;
	    }
	}
    }
}

/* printf_hex */
void printf_hex(unsigned int n) {
   int tmp;
   
   printf("0x");
   char noZeros = 1;
   
   int i;
   for (i = 28; i > 0; i-=4) {
       tmp = (n >> i) & 0xF;
       if (tmp == 0 && noZeros != 0) {
          continue;
       }
       
       if (tmp >= 0xA) {
          noZeros = 0;
          putc(tmp-0xA+'a');
       } else {
          noZeros = 0;
          putc(tmp+'0');
       }
   }
   
   tmp = n & 0xF;
   if (tmp >= 0xA) {
      putc(tmp-0xA+'a');
   } else {
      putc(tmp+'0');
   }
}
