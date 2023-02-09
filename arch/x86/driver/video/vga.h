/*
      Prototipos do vga.c
*/

/* iniciar */
void vga_init(void);

/* scrool */
void vga_scroll(void);

/* setar cor */
void vga_setcolor(unsigned int foreground, unsigned int background);

/* setar posicao - deprecated */
void vga_setposition(unsigned int x, unsigned int y);

/* mover cursor - asm */
void __vga_movecursor(void);

/* limpar tela */
void vga_cls(void);

/* imprimir caracter */
void putc(const char c);

/* imprimir string */
void printf(char *format, ...);

/* printf_hex */
void printf_hex(unsigned int n);

/* vga_putcx */
void putcx(const char *m, unsigned int len);
