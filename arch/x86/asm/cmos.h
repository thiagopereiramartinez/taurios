/*
    CMOS
*/

/* estrutura do cmos */
struct str_cmos {	
   unsigned int seconds;
   unsigned int minutes;
   unsigned int hours;
   unsigned int week;
   unsigned int day;
   unsigned int month;
   unsigned int year;
   unsigned int century;
   unsigned int status_a;
   unsigned int status_b;
};

/* tratamento da IRQ */
void cmos_handler(struct regs *r);

/* instalar */
void cmos_install(void);

/* preparar */
void cmos_prepare(void);

/* obter cmos */
struct str_cmos cmos_getdata();

