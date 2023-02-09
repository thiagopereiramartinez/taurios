/*
    Sistema de Arquivos
*/

#define FS_TYPE_EMPTY                       0x00
#define FS_TYPE_FAT12                       0x01
#define FS_TYPE_XENIX_ROOT                  0x02
#define FS_TYPE_XENIX_USR                   0x03
#define FS_TYPE_FAT16_LESS_32M              0x04
#define FS_TYPE_EXTENDED                    0x05
#define FS_TYPE_FAT16                       0x06
#define FS_TYPE_HPFS_NTFS_EXFAT             0x07
#define FS_TYPE_AIX                         0x08
#define FS_TYPE_AIX_BOOTABLE                0x09
#define FS_TYPE_OS2_BOOT_MANAGER            0x0A
#define FS_TYPE_FAT32                       0x0B
#define FS_TYPE_FAT32_LBA                   0x0C
#define FS_TYPE_FAT16_LBA                   0x0E
#define FS_TYPE_EXT_LBA                     0x0F
#define FS_TYPE_OPUS                        0x10
#define FS_TYPE_HIDDEN_FAT12                0x11
#define FS_TYPE_COMPAQ_DIAGNOSTIC           0x12
#define FS_TYPE_HIDDEN_FAT16_LESS_32M       0x14
#define FS_TYPE_HIDDEN_FAT16                0x16
#define FS_TYPE_HIDDEN_HPFS_NTFS_EXFAT      0x17
#define FS_TYPE_AST_SMARTSLEEP              0x18
#define FS_TYPE_HIDDEN_FAT32                0x1B
#define FS_TYPE_HIDDEN_FAT32_LBA            0x1C
#define FS_TYPE_HIDDEN_FAT16_LBA            0x1E
#define FS_TYPE_NEC_DOS                     0x24
#define FS_TYPE_HIDDEN_NTFS_WINRE           0x27
/* ... */
#define FS_TYPE_LINUX_SWAP                  0xFFFFFF82
#define FS_TYPE_LINUX                       0xFFFFFF83

/* fs_mount */
unsigned int fs_mount(unsigned int drive, unsigned int partition);

/* fs_select */
void fs_select(unsigned int drive, unsigned int partition);

/* fs_get_cur_driver */
unsigned int fs_get_cur_driver(void);

/* fs_get_cur_partition */
unsigned int fs_get_cur_partition(void);

/* fs_cd */
unsigned int fs_cd(unsigned int drive, unsigned int partition, char *dir);

/* fs_ls */
unsigned int fs_ls(unsigned int drive, unsigned int partition, const char *param);

/* fs_pwd */
char *fs_pwd(void);

/* fs_cat */
unsigned int fs_cat(unsigned int drive, unsigned int partition, char *dir, const unsigned char *param);

/* fs_set_cur_pwd */
void fs_set_cur_pwd(char *lpwd);

/* fs_type_description */
char *fs_type_description(int type);

