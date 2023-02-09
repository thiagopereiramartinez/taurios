/*
    IDE
*/

#include "ide.h"
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/pci.h>
#include <asm/timer.h>
#include <driver/video/vga.h>

#define sleep(x)          timer_sleep_cicles(x)

/* variaveis */
unsigned int ide_irq_invoked = 0;
unsigned char ide_buf[2048] = {0};
ide_device ide_devices[4];
ide_channel channels[2];

/* IRQ */
void ide_handler(struct regs *r) {
   ide_irq_invoked = 1;
};

/* ide_install */
void ide_install(void) {
   irq_install_handler(14, ide_handler);
   irq_install_handler(15, ide_handler);
}

/* ide_initialize */
void ide_initialize(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3, unsigned int BAR4) {
    int j, k, count = 0;

    // 1- Detect I/O Ports which interface IDE Controller:
    channels[ATA_PRIMARY  ].base  = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
    channels[ATA_PRIMARY  ].ctrl  = (BAR1 & 0xFFFFFFFC) + 0x3F4 * (!BAR1);
    channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
    channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x374 * (!BAR3);
    channels[ATA_PRIMARY  ].bus_master = (BAR4 & 0xFFFFFFFC) + 0; // Bus Master IDE
    channels[ATA_SECONDARY].bus_master = (BAR4 & 0xFFFFFFFC) + 8; // Bus Master IDE
    
    // 2- Disable IRQs:
    ide_write(ATA_PRIMARY  , ATA_REG_CONTROL, 2);
    ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);
    
    // 3- Detect ATA-ATAPI Devices:
    int i;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++) {
            unsigned char err = 0, type = IDE_ATA, status;
            ide_devices[count].reserved = 0; // Assuming that no drive here.

            // (I) Select Drive:
            ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4)); // Select Drive.
            sleep(1); // Wait 1ms for drive select to work.

            // (II) Send ATA Identify Command:
            ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
            sleep(1); // This function should be implemented in your OS. which waits for 1 ms.
                      // it is based on System Timer Device Driver.

            // (III) Polling:
            if (ide_read(i, ATA_REG_STATUS) == 0) continue; // If Status = 0, No Device.
            while(1) {
               status = ide_read(i, ATA_REG_STATUS);
               if ((status & ATA_SR_ERR)) {err = 1; break;} // If Err, Device is not ATA.
               if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) break; // Everything is right.
            }
            // (IV) Probe for ATAPI Devices:
            if (err != 0) {
               unsigned char cl = ide_read(i, ATA_REG_LBA1);
               unsigned char ch = ide_read(i, ATA_REG_LBA2);
               if (cl == 0x14 && ch ==0xEB)
                  type = IDE_ATAPI;
               else if (cl == 0x69 && ch == 0x96)
                  type = IDE_ATAPI;
               else
                  continue; // Unknown Type (may not be a device).
               ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
               sleep(1);
            }
            // (V) Read Identification Space of the Device:
//            ide_read_buffer(i, ATA_REG_DATA, (unsigned int) ide_buf, 128);
            // (VI) Read Device Parameters:
            ide_devices[count].reserved     = 1;
            ide_devices[count].type         = type;
            ide_devices[count].channel      = i;
            ide_devices[count].drive        = j;
            ide_devices[count].signature    = *((unsigned short *)(ide_buf + ATA_IDENT_DEVICETYPE));
            ide_devices[count].capabilities = *((unsigned short *)(ide_buf + ATA_IDENT_CAPABILITIES));
            ide_devices[count].command_sets  = *((unsigned int *)(ide_buf + ATA_IDENT_COMMANDSETS));
            // (VII) Get Size:
            if (ide_devices[count].command_sets & (1 << 26))
               // Device uses 48-Bit Addressing:
               ide_devices[count].size   = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA_EXT));
            else
               // Device uses CHS or 28-bit Addressing:
               ide_devices[count].size   = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA));
           // (VIII) String indicates model of device (like Western Digital HDD and SONY DVD-RW...):
           for (k = 0; k < 40; k += 2) {
               ide_devices[count].model[k] = ide_buf[ATA_IDENT_MODEL + k + 1];
               ide_devices[count].model[k + 1] = ide_buf[ATA_IDENT_MODEL + k];
           }
           ide_devices[count].model[40] = 0; // Terminate String.
           count++;
           
 
       // 4- Print Summary:
       for (i = 0; i < 4; i++)
           if (ide_devices[i].reserved == 1) {
              printf(" Found %s Drive %dGB - %s\n",
                    (const char *[]){"ATA", "ATAPI"}[ide_devices[i].type],         /* Type */
                     ide_devices[i].size, // / 1024 / 1024 / 2,               /* Size */
                     ide_devices[i].model);
           }
    }
}

/* ide_read */
unsigned char ide_read(unsigned char channel, unsigned char reg) {
   unsigned char result;
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      result = inb(channels[channel].base + reg - 0x00);
   else if (reg < 0x0C)
      result = inb(channels[channel].base  + reg - 0x06);
   else if (reg < 0x0E)
      result = inb(channels[channel].ctrl  + reg - 0x0A);
   else if (reg < 0x16)
      result = inb(channels[channel].bus_master + reg - 0x0E);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
   return result;
}

/* ide_write */
void ide_write(unsigned char channel, unsigned char reg, unsigned char data) {
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      outb(channels[channel].base  + reg - 0x00, data);
   else if (reg < 0x0C)
      outb(channels[channel].base  + reg - 0x06, data);
   else if (reg < 0x0E)
      outb(channels[channel].ctrl  + reg - 0x0A, data);
   else if (reg < 0x16)
      outb(channels[channel].bus_master + reg - 0x0E, data);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

/* ide_wait */
void ide_wait(void) {
   while (! ide_irq_invoked);
   ide_irq_invoked = 0;
}

/* ide_detect */
void ide_detect(void) {

}
