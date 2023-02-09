/*
    form_inicial - formulario inicial
*/

#include <driver/video/vga.h>
#include <driver/video/ui/form.h>
#include <driver/video/ui/paint.h>
#include <driver/video/art/asciiart.h>
#include <include/colors.h>

// logo
#include <driver/video/art/src/logo/logo.h>

/* prototipos */
void __form_inicial_quadro(void);

/* ui_init */
void form_inicial_init(void) {
   paint_init(COLOR_GREY, COLOR_BLUE); // setar cor
   paint_fill_all(); // limpar tela

   // Logo
   asciiart_display(get_art_Logo());
   
   __form_inicial_quadro(); // desenhar quadro
}

/* __form_inicial_quadro */
void __form_inicial_quadro(void) {
   form_draw("SISTEMA ALPHA 1.0", "|C|ONTINUAR |R|EINICIAR |S|AIR");
   for(;;);
}
