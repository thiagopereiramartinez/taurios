/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Translated by: Mauro J. Sch�tz (maurojoel@gmail.com)
*  Desc: Keyboard driver
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include "keyboard.h"
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/power.h>
#include <driver/video/vga.h>
#include <include/colors.h>

/* variaveis */
char caps_lock = 0;
unsigned int paused = 0;

/* caracter corrente */
char char_current;

/* scancode corrente */
char scancode_current;

/* KBDUS � o Layout de Teclado dos EUA. Este � uma tabela de scancode
*  usado para o layout padr�o do teclado dos EUA. Eu tenho adicionado alguns
*  coment�rios para voc� ter uma id�ia de que tecla � qual, ainda
*  que Eu atribui este �ndice do arranjo para 0. Voc� pode mudar para voc� usar
*  qualquer que voc� deseja usando um macro, se voc� quiser! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Tecla enter */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Shift esquerdo */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Shift direito */
  '*',
    0,	/* Alt */
  ' ',	/* Barra de espa�o */
    0,	/* Caps lock */
    0,	/* tecla 59 - F1 ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Tecla Home */
    0,	/* Seta para cima */
    0,	/* Page Up */
  '-',
    0,	/* Seta esquerda */
    0,
    0,	/* Seta direita */
  '+',
    0,	/* tecla 79 - End */
    0,	/* Seta para baixo */
    0,	/* Page Down */
    0,	/* Tecla Insert */
    0,	/* Tecla Delete */
    0,   0,   0,
    0,	/* Tecla F11 */
    0,	/* Tecla F12 */
    0,	/* Todas as outras teclas s�o indefinidas */
};

/* Trata a interrup��o do teclado */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* L� do buffer de dados do teclado */
    scancode = inb(0x60);

    /* mover valores para variaveis */
    scancode_current = scancode;
    
    /* verificar se o sistema esta rodando */
    if (scancode == VK_F1) {
       vga_setcolor(COLOR_YELLOW, COLOR_BLACK);
       printf("System is alive.\n");
       vga_setcolor(COLOR_GREY, COLOR_BLACK);
    }
    
    /* caps lock */
    if (scancode == VK_CAPS_LOCK) {
       if (caps_lock == 0)
          caps_lock = 1;
       else
          caps_lock = 0;
    }
        
    /* esc - reboot */
    if (scancode == VK_ESC) {
       reboot();
       return;
    }

    /* Se o bit de topo do byte que n�s lemos do teclado � atribuido,
    *  que por meio deste uma tecla foi justamente realizada */
    if (scancode & 0x80)
    {
        return;
        /* Voc� pode usar este um para ver se um usu�rio realizou as
        *  teclas shift, alt, ou control... */
    }
    else
    {
        /* Aqui, uma tecla foi justamente pressionada. Por favor note que se voc�
        *  segura um tecla, voc� obter� repetidas interrup��es de teclas
        *  pressionadas. */

        /* Justamente para mostrar que este trabalha, n�s vamos traduzir
        *  o scancode do teclado para valores ASCII, e ent�o
        *  mostrar este na tela. Voc� pode ser criativo e
        *  usar algumas flags para ver se um shift � pressionado e usar um
        *  layout diferente, ou voc� pode adicionar outras 128 entradas
        *  ao layout acima para corresponder ao 'shift' pressionado.
        *  Se o shift � segurado pode-se usar uma grande tabela de procura,
        *  voc� dever� adicionar 128 para o scancode quando voc� procurar por isto */
//        vga_putc(kbdus[scancode]);

        /* mover caracter lido para variavel */
        char_current = kbdus[scancode];
        
        /* caracteres maiusculos */
        if (caps_lock == 1 && char_current >= 97 && char_current <= 122) {
           char_current = char_current - 32;
        }

    }
}

/* Instala o tratamento do teclado no IRQ1 */
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}

/* obter letra */
char keyboard_readchar(void) {
    return char_current;
}

/* obter codigo */
char keyboard_readcode(void) {
    return scancode_current;
}

/* limpar dados */
void keyboard_clean(void) {
    char_current=0;
    scancode_current=0;
}
