/*
    Driver HDD
*/

/* controlador */
#define HDD_CTRL_PRIMARY         0xA0
#define HDD_CTRL_SECONDARY       0xB0

/* driver */
#define HDD_DRIVE_PRIMARY        0x1F0
#define HDD_DRIVE_SECONDARY      0x170

/* operacao */
#define HDD_SECTOR_READ          0x20
#define HDD_SECTOR_READ48        0x24
#define HDD_SECTOR_WRITE         0x30
#define HDD_SECTOR_WRITE48       0x34

/* hdd_detect */
void hdd_detect();

/* hdd_test_drive */
unsigned int hdd_test_drive(int drive, int echo);

/* hdd_lba28_read_sector */
void hdd_lba28_read_sector(int drive, int lba, char *buffer);
#define hdd_read28(a,b,c)                  hdd_lba28_read_sector(a,b,c);

/* hdd_lba28_write_sector */
void hdd_lba28_write_sector(int drive, int lba, char *buffer);
#define hdd_write28(a,b,c)                  hdd_lba28_write_sector(a,b,c);


