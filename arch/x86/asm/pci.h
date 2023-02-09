/*
    PCI
*/

/* class codes */
#define DEVICE_CLASS_BUILD_PRIOR_DEFINITION              0x00
#define DEVICE_CLASS_MASS_STORAGE_CONTROLLER             0x01
#define DEVICE_CLASS_NETWORK_CONTROLLER                  0x02
#define DEVICE_CLASS_DISPLAY_CONTROLLER                  0x03
#define DEVICE_CLASS_MULTIMEDIA_CONTROLLER               0x04
#define DEVICE_CLASS_MEMORY_CONTROLLER                   0x05
#define DEVICE_CLASS_BRIDGE                              0x06
#define DEVICE_CLASS_SIMPLE_COMMUNICATION_CONTROLLERS    0x07
#define DEVICE_CLASS_BASE_SYSTEM_PERIPHERALS             0x08
#define DEVICE_CLASS_INPUT_DEVICES                       0x09
#define DEVICE_CLASS_DOCKING_STATIONS                    0x0A
#define DEVICE_CLASS_PROCESSORS                          0x0B
#define DEVICE_CLASS_SERIAL_BUS_CONTROLLERS              0x0C
#define DEVICE_CLASS_WIRELESS_CONTROLLERS                0x0D
#define DEVICE_CLASS_INTELLIGENT_IO_CONTROLLERS          0x0E
#define DEVICE_CLASS_SATELLITE_COMMUNICATION_CONTROLLERS 0x0F
#define DEVICE_CLASS_ENCRYPTION_DECRYPTION_CONTROLLERS   0x10
#define DEVICE_CLASS_DATA_ACQUISITION_AND_SIGNAL_CTRL    0x11
#define DEVICE_CLASS_NOT_DEFINED_CLASS                   0xFF

/* sub-class code */
#define DEVICE_SUBCLASS_OTHERS                           0x00
#define DEVICE_SUBCLASS_VGA_COMPATIBLE_DEVICE            0x01
#define DEVICE_SUBCLASS_SCSI_BUS_CONTROLLER              0x00
#define DEVICE_SUBCLASS_IDE_CONTROLLER                   0x01
#define DEVICE_SUBCLASS_FLOPPY_DISK_CONTROLLER           0x02
#define DEVICE_SUBCLASS_IPI_BUS_CONTROLLER               0x03
#define DEVICE_SUBCLASS_RAID_CONTROLLER                  0x04
#define DEVICE_SUBCLASS_ATA_CONTROLLER                   0x05
#define DEVICE_SUBCLASS_SERIAL_ATA                       0x06
#define DEVICE_SUBCLASS_OTHERS_MASS_STORAGE              0x80
#define DEVICE_SUBCLASS_ETHERNET_CONTROLLER              0x00
#define DEVICE_SUBCLASS_TOKEN_RING_CONTROLLER            0x01
#define DEVICE_SUBCLASS_FDDI_CONTROLLER                  0x02
#define DEVICE_SUBCLASS_ATM_CONTROLLER                   0x03
#define DEVICE_SUBCLASS_ISDN_CONTROLLER                  0x04
#define DEVICE_SUBCLASS_WORLDFIP_CONTROLLER              0x05
#define DEVICE_SUBCLASS_PICGM_MULTICOMPUTING             0x06
#define DEVICE_SUBCLASS_OTHERS_NETWORK_CONTROLLER        0x80
#define DEVICE_SUBCLASS_VGA_COMPATIBLE_CONTROLLER        0x00
#define DEVICE_SUBCLASS_XGA_CONTROLLER                   0x01
#define DEVICE_SUBCLASS_3D_CONTROLLER                    0x02
#define DEVICE_SUBCLASS_OTHER_DISPLAY_CONTROLLER         0x80
#define DEVICE_SUBCLASS_VIDEO_DEVICE                     0x00
#define DEVICE_SUBCLASS_AUDIO_DEVICE                     0x01
#define DEVICE_SUBCLASS_COMPUTER_TELEPHONY_DEVICE        0x02
#define DEVICE_SUBCLASS_OTHERS_MULTIMEDIA_DEVICE         0x80
#define DEVICE_SUBCLASS_RAM_CONTROLLER                   0x00
#define DEVICE_SUBCLASS_FLASH_CONTROLLER                 0x01
#define DEVICE_SUBCLASS_OTHERS_MEMORY_CONTROLLER         0x80
#define DEVICE_SUBCLASS_HOST_BRIDGE                      0x00
#define DEVICE_SUBCLASS_ISA_BRIDGE                       0x01
#define DEVICE_SUBCLASS_EISA_BRIDGE                      0x02
#define DEVICE_SUBCLASS_MCA_BRIDGE                       0x03

/* pci_device */
typedef struct pci_device {
    short bus;
    short slot;
    short device_id;
    short vendor_id;
    short status;
    short command;
    unsigned char class;
    unsigned char subclass;
    char prog_if;
    char revision_id;
    char BIST;
    char header_type;
    char latency_timer;
    char cache_line_size;
    int BAR0;
    int BAR1;
    int BAR2;
    int BAR3;
    int BAR4;
    int BAR5;
    int card_bus;
    short subsystem_id;
    short subsystem_vendor;
    int expansion_rom_base_address;
    struct {
        short s1_reserved1;
        char s1_reserved2;
    } reserved1;
    char capabilities_pointer;
    int reserved;
    char max_latency;
    char min_grant;
    char interrupt_pin;
    char interrupt_line;
} pci_device;

/* pci_config_read */
unsigned short pci_config_read(unsigned short bus, unsigned short slot, unsigned short func, unsigned short offset);

/* pci_config_device */
void pci_config_device(pci_device *device);

/* pci_test_device */
unsigned int pci_test_device(pci_device *device);

/* pci_show */
void pci_show(pci_device *device);

/* pci_ls */
void pci_ls(void);

