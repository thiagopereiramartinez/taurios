/*
    Timer (PIT)
*/

/* tratamento da IRQ */
void timer_handler(struct regs *r);

/* instalar */
void timer_install(void);

/* sleep */
void timer_sleep(int seconds);

/* sleep 500ms */
void timer_sleep_500ms(int cicles);

/* sleep cicles */
void timer_sleep_cicles(int cicles);


