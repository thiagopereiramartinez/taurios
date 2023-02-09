/*
    Driver HDD
*/

#include "hdd.h"
#include <asm/io.h>
#include <asm/timer.h>
#include <fs/mbr.h>
#include <fs/filesystem.h>
#include <driver/video/vga.h>

/* hdd_detect */
void hdd_detect() {
   // Detectar controlador primario
   outb(0x1F6, HDD_CTRL_PRIMARY); // Enviar para a porta
   timer_sleep_cicles(1); // Esperar um ciclo do timer
   char tmp = inb(0x1F7); // Ler valor
   if (tmp & 0x40) {
      printf("Controller HDD[0] detected.\n");
   }
   // Detectar controlador secundario
   outb(0x1F6, HDD_CTRL_SECONDARY); // Enviar para a porta
   timer_sleep_cicles(1); // Esperar um ciclo do timer
   char tmp2 = inb(0x1F7); // Ler valor
   if (tmp2 & 0x40) {
      printf("Controller HDD[1] detected.\n");
   }

   // HDD primario
   hdd_test_drive(HDD_DRIVE_PRIMARY, 1);

   // HDD secundario
   hdd_test_drive(HDD_DRIVE_SECONDARY, 1);

}

/* hdd_test_drive */
unsigned int hdd_test_drive(int drive, int echo) {
   char *ordem[3] = {"[0]", "[1]", "[unknown]"};
/*   char *type[5] = {"Parallel ATA Packet Interface (PATAPI)", 
                    "Serial ATA Packet Interface (SATAPI)",
                    "Parallel ATA (PATA)",
                    "Serial ATA (SATA)",
                    "unknown"}; */
                    
   // Testar
   outb(drive | 3, 0x04);
   if (inb(drive | 3) == 0x04) {
      if (echo) {
         printf("HDD%s detected.\n", ordem[drive == HDD_DRIVE_PRIMARY ? 0 :
                                               drive == HDD_DRIVE_SECONDARY ? 1 : 2]);
         // Ler MBR
         if (drive == HDD_DRIVE_PRIMARY) {
            int i,j=0;
            mbr lmbr;
            mbr_read(&lmbr, drive);
            for (i=0;i<4;i++) {
                if (lmbr.partition[i].type == 0) {
                   continue;
                }
                printf("     Partition[%d]:\n", i);
                printf("          Type: %s\n", fs_type_description(lmbr.partition[i].type));
                j++;
            }
            if (!j)
               printf("     No partitions found.\n");
            if ( lmbr.signature1 != 85 || lmbr.signature2 != -86 )
               printf("     Invalid boot signature [%d][%d].\n", lmbr.signature1, lmbr.signature2);
         }
      }
      return 1;
   }
   
   return 0;
}

/* hdd_lba28_read_sector */
void hdd_lba28_read_sector(int drive, int lba, char *buffer) {
   // Testar driver
   if (! hdd_test_drive(drive, 0)) {
      printf("Driver[%s] not found.\n", drive);
      return;
   }

   // Enviar comando de leitura
   outb(drive | 1, 0x00);
   outb(drive | 2, 0x01);
   outb(drive | 3, (char) lba);
   outb(drive | 4, (char) (lba >> 8));
   outb(drive | 5, (char) (lba >> 16));
   outb(drive | 6, 0xE0 | (drive << 4) | ((lba >> 24) & 0x0F));
   outb(drive | 7, HDD_SECTOR_READ);

   // Esperar disco
   while (!(inb(drive | 7) & 0x08));
   
   // Escreve no buffer os dados lido
   short i=0;
   short temp=0;
   while (i < 256) {
      temp = inw(drive);
      buffer[i*2] = (char) temp;
      buffer[(i*2)+1] = (char) (temp >> 8);
      i++;
   }
}

/* hdd_lba28_write_sector */
void hdd_lba28_write_sector(int drive, int lba, char *buffer) {
   // Testar driver
   if (! hdd_test_drive(drive, 0)) {
      printf("Driver primary not found.\n");
      return;
   }
   
   // Enviar comando de gravacao
   outb(drive | 1, 0x00);
   outb(drive | 2, 0x01);
   outb(drive | 3, (char) lba);
   outb(drive | 4, (char) (lba >> 8));
   outb(drive | 5, (char) (lba >> 16));
   outb(drive | 6, 0xE0 | (drive << 4) | ((lba >> 24) & 0x0F));
   outb(drive | 7, HDD_SECTOR_WRITE);
   
   // Esperar disco
   while (!(inb(drive | 7) & 0x08));
   
   // Grava no disco os dados do buffer
   short i=0;
   short temp=0;
   for (i=0;i<256;i++) {
      temp = buffer[8+i*2] | (buffer[8+i*2+1] << 8);
      outw(drive, temp);
   }
}
