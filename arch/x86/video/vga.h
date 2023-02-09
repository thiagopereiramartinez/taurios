/*
      Manipulador da VGA
      Autor: Thiago Pereira Martinez
      Data: 27/09/2013
*/

#ifndef _H_VGA
#define _H_VGA

#define VGA_MEM_OFFSET                        0xB8000
#define VGA_NUM_COLS                          80
#define VGA_NUM_ROWS                          24

/*
 * assinatura de metodos
 */

/* vga_putc - imprimir caracter */
void vga_putc(unsigned char c);

/* vga_printf - imprimir string */
void vga_printf(char *format, ...);

/* vga_printfx - imprimir valor em hexadecimal */
void vga_printfx(unsigned int n);

/* vga_updatecursor - atualizar cursor */
void vga_updatecursor();

/* vga_cls - limpar tela */
void vga_cls();

/* vga_setcolor - setar cor de fundo e texto */
void vga_setcolor(short background_color, short foreground_color);

#endif /* _H_VGA */
