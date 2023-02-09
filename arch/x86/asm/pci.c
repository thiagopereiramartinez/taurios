/*
    PCI
*/

#include "pci.h"
#include <asm/io.h>
#include <util/scanf.h>
#include <driver/video/vga.h>

/* descritor de classes */
char *pci_class_description[] = {
       "Device was built prior definition of the class code field",
       "Mass Storage Controller",
       "Network Controller",
       "Display Controller",
       "Multimedia Controller",
       "Memory Controller",
       "Bridge Device",
       "Simple Communication Controllers",
       "Base System Peripherals",
       "Input Devices",
       "Docking Stations",
       "Processors",
       "Serial Bus Controllers",
       "Wireless Controllers",
       "Intelligent I/O Controllers",
       "Satellite Communication Controllers",
       "Encryption/Decryption Controllers",
       "Data Acquisition and Signal Processing Controllers",
       "Reserved",
       "Unknown"
};

/* pci_config_read */
unsigned short pci_config_read(unsigned short bus, unsigned short slot, unsigned short func, unsigned short offset) {
   unsigned long address;
   unsigned long lbus = (unsigned long) bus;
   unsigned long lslot = (unsigned long) slot;
   unsigned long lfunc = (unsigned long) func;
   unsigned short tmp = 0;
   
   /* create configuration address */
   address = (unsigned long) ((lbus << 16) | (lslot << 11) | (lfunc << 8) |
             (offset &0xfc) | ((int) 0x80000000));
             
   /* write out the address */
   outl(0xCF8, address);
   
   /* read in the data */
   /* (offset & 2) * 9) = 0 will choose the first word of the 32 bits register */
   tmp = (unsigned short)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
   return (tmp);
}

/* pci_config_device */
void pci_config_device(pci_device *device) {
   short bus = device->bus;
   short slot = device->slot;
   
   device->vendor_id = pci_config_read(bus, slot, 0, 0);
   device->device_id = pci_config_read(bus, slot, 0, 2);
   
   device->command = pci_config_read(bus, slot, 4, 0);
   device->status = pci_config_read(bus, slot, 4, 2);
   
   device->revision_id = pci_config_read(bus, slot, 8, 0) & 0xFF;
   device->prog_if = pci_config_read(bus, slot, 8, 0) >> 8;
   device->subclass = pci_config_read(bus, slot, 8, 2) & 0xFF;
   device->class = pci_config_read(bus, slot, 8, 0) >> 8;

   device->cache_line_size = pci_config_read(bus, slot, 0x0C, 0) & 0xFF;
   device->latency_timer = pci_config_read(bus, slot, 0x0C, 0) >> 8;
   device->header_type = pci_config_read(bus, slot, 0x0C, 2) & 0xFF;
   device->BIST = pci_config_read(bus, slot, 0x0C, 2) >> 8;

   device->BAR0 = (pci_config_read(bus, slot, 0x10, 2) << 16) | pci_config_read(bus, slot, 0x10, 0);
   device->BAR1 = (pci_config_read(bus, slot, 0x14, 2) << 16) | pci_config_read(bus, slot, 0x14, 0);
   device->BAR2 = (pci_config_read(bus, slot, 0x18, 2) << 16) | pci_config_read(bus, slot, 0x18, 0);
   device->BAR3 = (pci_config_read(bus, slot, 0x1C, 2) << 16) | pci_config_read(bus, slot, 0x1C, 0);
   device->BAR4 = (pci_config_read(bus, slot, 0x20, 2) << 16) | pci_config_read(bus, slot, 0x20, 0);
   device->BAR5 = (pci_config_read(bus, slot, 0x24, 2) << 16) | pci_config_read(bus, slot, 0x24, 0);
   
   device->card_bus = (pci_config_read(bus, slot, 0x28, 2) << 16) | pci_config_read(bus, slot, 0x28, 0);

   device->subsystem_vendor = pci_config_read(bus, slot, 0x2C, 0);
   device->subsystem_id = pci_config_read(bus, slot, 0x2C, 2);

   device->expansion_rom_base_address = (pci_config_read(bus, slot, 0x30, 2) << 16) | pci_config_read(bus, slot, 0x30, 0);

   device->capabilities_pointer = (pci_config_read(bus, slot, 0x34, 0)) & 0xFF;

   device->interrupt_line = pci_config_read(bus, slot, 0x3C, 0) & 0xFF;
   device->interrupt_pin = pci_config_read(bus, slot, 0x3C, 0) >> 8;
   device->min_grant = pci_config_read(bus, slot, 0x3C, 2) & 0xFF;
   device->max_latency = pci_config_read(bus, slot, 0x3C, 2) >> 8;
}

/* pci_test_device */
unsigned int pci_test_device(pci_device *device) {
   if (device->class == 0xFF)
      return 0;
   else
      return 1;
}

/* pci_show */
void pci_show(pci_device *device) {
   printf("PCI: bus=%d slot=%d\n", device->bus, device->slot);
   printf("     Class[%d]: %s\n", device->class, pci_class_description[(int)device->class]);
   printf("     Subclass[%d]: \n", device->subclass);
   printf("     ProgIF: %d\n", device->prog_if);
   printf("     Vendor ID: %d\n", device->vendor_id);
   printf("     Device ID: %d\n", device->device_id);
   printf("     Header type: %d\n", device->header_type);
   printf("\n");
}

/* pci_ls */
void pci_ls(void) {
   short bus;
   short slot;
   for (bus=0;bus<256;bus++) {
       for (slot=0;slot<32;slot++) {
           pci_device device;
           device.bus = bus;
           device.slot = slot;
           pci_config_device(&device);
           if (! pci_test_device(&device))
              continue;
           pci_show(&device);
           pause();
       }
   }
}
