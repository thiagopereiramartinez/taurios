/* 
    Mouse
*/
#include "mouse.h"
#include <asm/io.h>
#include <asm/irq.h>
#include <driver/video/vga.h>

/* variaveis */

/* scancode corrente */
char scancode_current;

/* Trata a interrupção do teclado */
void mouse_handler(struct regs *r)
{
    unsigned char scancode;

    /* Lê do buffer de dados do teclado */
    scancode = inb(0x60);

    /* mover valores para variaveis */
    scancode_current = scancode;
    
    printf("{");
    printf_hex(scancode);
    printf("} ");
    
}

/* Instala o tratamento do teclado no IRQ12 */
void mouse_install()
{
    irq_install_handler(12, mouse_handler);
}

/* obter codigo */
char mouse_readcode(void) {
    return scancode_current;
}

/* limpar dados */
void mouse_clean(void) {
    scancode_current=0;
}
