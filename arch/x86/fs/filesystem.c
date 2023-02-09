/*
   Sistema de Arquivos
*/

#include "filesystem.h"
#include <fs/mbr.h>
#include <fs/fat32/fat32.h>
#include <driver/hdd/hdd.h>
#include <driver/video/vga.h>
#include <util/string.h>

/* variaveis */
unsigned int fs_cur_drive = 0;
unsigned int fs_cur_partition = 0;
char fs_cur_pwd[200];

/* fs_mount */
unsigned int fs_mount(unsigned int drive, unsigned int partition) {
   /* ler MBR para determinar o tipo do FS */
   mbr lmbr;
   mbr_read(&lmbr, drive);
   
   if (lmbr.partition[partition].type == 0)
      return 0;
   
   /* FAT32 */
   if (lmbr.partition[partition].type == FS_TYPE_FAT32 ||
      lmbr.partition[partition].type == FS_TYPE_FAT32_LBA) {
      return fat32_init(drive, partition);
   }

   /* Nao suportado */
   printf("Filesystem '%s' not supported.\n", fs_type_description(lmbr.partition[partition].type));
   return 0;
}

/* fs_select */
void fs_select(unsigned int drive, unsigned int partition) {
   fs_cur_drive = drive;
   fs_cur_partition = partition;
   int id_drive = (drive == HDD_DRIVE_PRIMARY) ? 0 : (drive == HDD_DRIVE_SECONDARY) ? 1 : 9;
   char lpwd[20];
   if (drive == HDD_DRIVE_PRIMARY || drive == HDD_DRIVE_SECONDARY) {
      strconcat(lpwd, "(%s%d,%d):~#/", "hdd", id_drive, partition);
      fs_set_cur_pwd(lpwd);
   }
}

/* fs_get_cur_driver */
unsigned int fs_get_cur_driver(void) {
   return fs_cur_drive;
}

/* fs_get_cur_partition */
unsigned int fs_get_cur_partition(void) {
   return fs_cur_partition;
}

/* fs_cd */
unsigned int fs_cd(unsigned int drive, unsigned int partition, char *dir) {
   /* ler MBR para determinar o tipo do FS */
   mbr lmbr;
   mbr_read(&lmbr, drive);
   
   if (lmbr.partition[partition].type == 0)
      return 0;
   
   /* FAT32 */
   if (lmbr.partition[partition].type == FS_TYPE_FAT32 ||
      lmbr.partition[partition].type == FS_TYPE_FAT32_LBA) {
      strfill(dir, ' ', 8);
      int r = fat32_cd(drive, partition, dir);
      if (r == 1) {
         strtrim(dir);
         strconcat(fs_cur_pwd, "%s%s/", fs_cur_pwd, dir);
      }
      return 1;
   }

   /* Nao suportado */
   printf("Filesystem '%s' not supported.\n", fs_type_description(lmbr.partition[partition].type));
   return 0;
}

/* fs_cat */
unsigned int fs_cat(unsigned int drive, unsigned int partition, char *file, const unsigned char *param) {
   /* ler MBR para determinar o tipo do FS */
   mbr lmbr;
   mbr_read(&lmbr, drive);
   
   if (lmbr.partition[partition].type == 0)
      return 0;
   
   /* FAT32 */
   if (lmbr.partition[partition].type == FS_TYPE_FAT32 ||
      lmbr.partition[partition].type == FS_TYPE_FAT32_LBA) {
      strfill(file, ' ', 8);
      fat32_cat(drive, partition, file, param);
      return 1;
   }

   /* Nao suportado */
   printf("Filesystem '%s' not supported.\n", fs_type_description(lmbr.partition[partition].type));
   return 0;
}

/* fs_ls */
unsigned int fs_ls(unsigned int drive, unsigned int partition, const char *param) {
   /* ler MBR para determinar o tipo do FS */
   mbr lmbr;
   mbr_read(&lmbr, drive);
   
   if (lmbr.partition[partition].type == 0)
      return 0;
   
   /* FAT32 */
   if (lmbr.partition[partition].type == FS_TYPE_FAT32 ||
      lmbr.partition[partition].type == FS_TYPE_FAT32_LBA) {
      fat32_ls(drive, partition, param);
      return 1;
   }

   /* Nao suportado */
   printf("Filesystem '%s' not supported.\n", fs_type_description(lmbr.partition[partition].type));
   return 0;
}

/* fs_pwd */
char *fs_pwd(void) {
    return fs_cur_pwd;
}

/* fs_set_cur_pwd */
void fs_set_cur_pwd(char *lpwd) {
   strclear(fs_cur_pwd);
   strcpy(lpwd, fs_cur_pwd);
}

/* fs_type_description */
char *fs_type_description(int type) {
    switch(type) {
        case FS_TYPE_EMPTY: return "Empty";break;
        case FS_TYPE_FAT12: return "FAT 12";break;
        case FS_TYPE_XENIX_ROOT: return "XENIX root";break;
        case FS_TYPE_XENIX_USR: return "XENIX usr";break;
        case FS_TYPE_FAT16_LESS_32M: return "FAT16 < 32M";break;
        case FS_TYPE_EXTENDED: return "Extended";break;
        case FS_TYPE_FAT16: return "FAT16";break;
        case FS_TYPE_HPFS_NTFS_EXFAT: return "HPFS/NTFS/exFAT";break;
        case FS_TYPE_AIX: return "AIX";break;
        case FS_TYPE_AIX_BOOTABLE: return "AIX bootable";break;
        case FS_TYPE_OS2_BOOT_MANAGER: return "OS/2 boot manager";break;
        case FS_TYPE_FAT32: return "FAT 32";break;
        case FS_TYPE_FAT32_LBA: return "FAT 32 (LBA)";break;
        case FS_TYPE_FAT16_LBA: return "FAT 16 (LBA)";break;
        case FS_TYPE_EXT_LBA: return "EXT (LBA)";break;
        case FS_TYPE_OPUS: return "OPUS";break;
        case FS_TYPE_HIDDEN_FAT12: return "FAT 12";break;
        case FS_TYPE_COMPAQ_DIAGNOSTIC: return "Compaq diagnostic";break;
        case FS_TYPE_HIDDEN_FAT16_LESS_32M: return "Hidden FAT 16 < 32M";break;
        case FS_TYPE_HIDDEN_FAT16: return "Hidden FAT 16";break;
        case FS_TYPE_HIDDEN_HPFS_NTFS_EXFAT: return "Hidden HPFS/NTFS/exFAT";break;
        case FS_TYPE_AST_SMARTSLEEP: return "AST SmartSleep";break;
        case FS_TYPE_HIDDEN_FAT32: return "Hidden FAT 32";break;
        case FS_TYPE_HIDDEN_FAT32_LBA: return "Hidden FAT 32 (LBA)";break;
        case FS_TYPE_HIDDEN_FAT16_LBA: return "Hidden FAT 16 (LBA)";break;
        case FS_TYPE_NEC_DOS: return "NEC DOS";break;
        case FS_TYPE_HIDDEN_NTFS_WINRE: return "Hidden NTFS WinRE";break;
        case FS_TYPE_LINUX_SWAP: return "Linux Swap";break;
        case FS_TYPE_LINUX: return "Linux";break;
        default: return "unknown";break;
    }
}

