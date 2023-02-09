/*
    Principal - Inicio do Kernel
*/

/* Parametros do sistema operacional */
#ifndef OS_NAME
   #error OS_NAME not specified
#endif

#ifndef OS_VERSION
   #error OS_VERSION not specified
#endif

#ifndef OS_DIST
   #error OS_DIST not specified
#endif

/* include */
#include "main.h"
#include <boot/multiboot.h>
#include <asm/io.h>
#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/isr.h>
#include <asm/irq.h>
#include <asm/a20.h>
#include <asm/paging.h>
#include <asm/timer.h>
#include <asm/cpudet.h>
#include <asm/cmos.h>
#include <asm/keyboard.h>
#include <asm/mouse.h>
#include <fs/filesystem.h>
#include <driver/video/vga.h>
#include <driver/hdd/hdd.h>
#include <driver/floppy/floppy.h>
#include <boot/console.h>
#include <util/datetime.h>
#include <util/string.h>

/* variaveis */
unsigned int magic;
multiboot_info_t *mbd;

/* INICIO */
void _cmain(multiboot_info_t *lmbd, unsigned int b_magic) {
    // Instalar o GDT
    gdt_install();

    // Instalar o IDT
    idt_install();

    // Instalar o ISR
    isr_install();
    
    // Instalar o IRQ
    irq_install();    
    
    /*******************/
    __asm__ __volatile__("sti");
    magic = b_magic;
    mbd = lmbd;

    // Instalar teclado
    keyboard_install();
    
    // Instalar mouse
    mouse_install();
    
    // Iniciar o video
    vga_init();
    vga_cls();
    
    // Instalar timer
    timer_install();
    
    // Instalar CMOS
    cmos_install();
    
    // Ativar A20
    a20_enable();

    // Habilitar paginacao
    init_paging(); // Desativado - Altamente deprecado
    
    // Mostra informacoes
    information();
    
    // Iniciar FS
    main_fs_init();
    
    // Entra no console
    console_init();
    
    // Fim
    for (;;);    
}

/* Iniciar FS */
void main_fs_init(void) {
    // Montar o primario
    int i=0,j=0;
    for (;i<4;i++) {
        int r = fs_mount(HDD_DRIVE_PRIMARY, i);
        if (r > 0 && j == 0) {
           fs_select(HDD_DRIVE_PRIMARY, i); // Selecionar a primeira particao
           j = 1;
        }
    }
}

/* Mostrar informacoes */
void information(void) {
    // Testa se IRQ esta instalado
    if (irq_enabled()) {
       printf("IRQ: Enabled\n");
    } else {
       printf("IRQ: Disabled\n");
       printf("Fatal Error: IRQ disabled. Please, reboot you computer.\n");
       for(;;);
    }

    // Informacoes da CPU
    detect_cpu();    
    
    // Detectar HD
    hdd_detect();
    
    // Informacoes de disquete
//    floppy_detect();    
}
