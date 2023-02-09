/*
    ler teclado
*/

#include "scanf.h"
#include <asm/io.h>
#include <asm/keyboard.h>
#include <driver/video/vga.h>
#include <util/string.h>

/* scanf */
void scanf(char *str, int size, int echo, int skip) {
    unsigned int x=0;
    while (1) {
        if (x >= size && skip == AUTO_SKIP)
           break;
    
        while (keyboard_readchar() == 0) {}
           
        // Tecla enter
        if ((int) keyboard_readchar() == 10) {
           putc(keyboard_readchar());
           keyboard_clean();
           return;
        }

        // Backspace
        if ((int) keyboard_readchar() == 8 && x > 0) {
           str--;
           *str = '\0';
           x--;
           if (echo == ECHO_NORMAL || echo == ECHO_SECURE)
              putc(keyboard_readchar());
           keyboard_clean();
           continue;
        }

        // backspace        
        if ((int) keyboard_readchar() == 8 && x == 0) {
           keyboard_clean();
           continue;
        }
        
        /* parar de ler teclado (exceto ENTER e BACKSPACE) se limite foi
           alcancado e o SKIP estiver desativado */
        if (x >= size && skip == NO_SKIP) {
           keyboard_clean();
           continue;
        }
        
        x++;
        if (echo == ECHO_NORMAL)
           putc(keyboard_readchar());
        if (echo == ECHO_SECURE)
           putc('*');
        *str++=keyboard_readchar();
        keyboard_clean();
    }
}

/* scanfinterrupt - interrompe ao receber sinal */
char scanfinterrupt(char *str, int size, char *signal, int echo, int skip) {
    unsigned int x=0;
    char *tmp = signal;
    char c;
    while (1) {
        if (x >= size && skip == AUTO_SKIP)
           break;
    
        while (keyboard_readchar() == 0 && keyboard_readcode() == 0) {}
        
        // Sinal
        signal = tmp;
        int i=0;
        for (;i<strlen(signal);i++) {
            if (keyboard_readcode() == signal[i])
               goto fim;
        }
        
        // Tecla enter
        if ((int) keyboard_readchar() == 10) {
           putc(keyboard_readchar());
           keyboard_clean();
           return 10;
        }

        // Backspace
        if ((int) keyboard_readchar() == 8 && x > 0) {
           str--;
           *str = '\0';
           x--;
           if (echo == ECHO_NORMAL || echo == ECHO_SECURE)
              putc(keyboard_readchar());
           keyboard_clean();
           continue;
        }

        // backspace        
        if ((int) keyboard_readchar() == 8 && x == 0) {
           keyboard_clean();
           continue;
        }
        
        /* parar de ler teclado (exceto ENTER e BACKSPACE) se limite foi
           alcancado e o SKIP estiver desativado */
        if (x >= size && skip == NO_SKIP) {
           keyboard_clean();
           continue;
        }
        
        /* caracteres */
        if (keyboard_readchar() == 0)
           continue;
        
        x++;
        if (echo == ECHO_NORMAL)
           putc(keyboard_readchar());
        if (echo == ECHO_SECURE)
           putc('*');
        *str++=keyboard_readchar();
        keyboard_clean();
    }
    fim:
        c = keyboard_readcode();
        keyboard_clean();
        return c;
}

/* pause */
void pause(void) {
   char p;
   scanf(&p, 1, ECHO_HIDE, AUTO_SKIP);
}
