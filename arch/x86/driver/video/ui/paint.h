/*
    paint - Desenho de interface no modo texto (80x25x16)
*/

/* paint_init */
void paint_init(unsigned int foreground, unsigned int background);

/* fill_all */
void paint_fill_all(void);

/* paint_draw_line */
void paint_draw_line(unsigned int posx, unsigned int posy, unsigned int size, char c);

/* paint_draw_rect */
void paint_draw_rect(unsigned int xv1, unsigned int yv1, unsigned int xv2, unsigned int yv2, unsigned int xv3, unsigned int yv3, unsigned int xv4, unsigned int yv4, unsigned int border);

/* paint_putc */
void paint_putc(unsigned int posx, unsigned int posy, char c);


