/*
   Prototipos das operacoes de entrada e saida
*/

/* outb */
extern void outb(unsigned short port, unsigned char val);

/* inb */
extern unsigned char inb(unsigned short port);

/* outl */
extern void outl(unsigned short port, unsigned long val);

/* inl */
extern unsigned long inl(unsigned short port);

/* out */
extern void out(unsigned short port, unsigned short val);

/* in */
extern unsigned short in(unsigned short port);

/* outw */
extern void outw(unsigned short port, unsigned short val);

/* inw */
extern unsigned short inw(unsigned short port);

/* io_wait */
extern void io_wait(void);
