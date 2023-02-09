/*
    Paginacao
*/

#include "paging.h"
#include <boot/multiboot.h>
#include <driver/video/vga.h>
#include <include/colors.h>

/* variaveis */
extern multiboot_info_t *mbd;
multiboot_info_t *boot_info = (multiboot_info_t *) &mbd;

unsigned long total_mem;
unsigned int *page_directory = 0;
unsigned int *page_table = 0;

/* iniciar pagina */
void init_paging() {
   unsigned int addr;

   // ler total de memoria fisica   
   if (mbd->flags & 0x02) {
      total_mem = (mbd->mem_upper)*1024;
   } else {
      vga_setcolor(COLOR_RED, COLOR_BLACK);
      printf("Kernel Panic: Error reading multiboot informations.\nSystem stopped.\n");
      for(;;); // Loop infinito
   }
   printf("Total memory: %dMB (%d bytes)\n", (total_mem/1024/1024), total_mem);
   
   //return; // deprecated
   
   // Preencher memoria
   page_directory = (unsigned int *) mbd->mmap_addr;
   page_table = (unsigned int *) (page_directory + 0x1000);
   
   unsigned long address = 0;
   unsigned int i;
   
   // map the first 4MB of memory
   for (i=0;i<1024;i++) {
      page_table[i] = address | 3;
      address += 4096;
   }
   
   // Fill the first entry of the page directory
   page_directory[0] = (unsigned int) page_table;
   page_directory[0] = page_directory[0] | 3;
   
   for (i=1;i<1024;i++) {
       page_directory[i] = 0 | 2;
   }
   
   // Enable
   asm volatile("mov %0, %%cr3" :: "r"(page_directory));
   unsigned int cr0;
   asm volatile("mov %%cr0, %0" : "=r"(cr0));
   cr0 |= 0x80000000;
   asm volatile("mov %0, %%cr0" :: "r"(cr0));
   printf("Paginado.\n");
   
}
