/*
    Mouse
*/

/* Instala o tratamento do teclado no IRQ1 */
void mouse_install();

/* obter codigo */
char mouse_readcode(void);

/* limpar dados */
void mouse_clean(void);
