/*
    FAT32 - File Allocation Table (32)
*/

/* atributos do arquivo */
#define FAT32_ATTRIB_READONLY         0x01
#define FAT32_ATTRIB_HIDDEN           0x02
#define FAT32_ATTRIB_SYSTEM           0x04
#define FAT32_ATTRIB_VOLUME_ID         0x08
#define FAT32_ATTRIB_DIRECTORY        0x10
#define FAT32_ATTRIB_ARCHIVE          0x20

/* fat32_volume_id */
typedef struct fat32_volume_id {
   char OEM_name[8];
   char media;
   unsigned short sectors_per_track;
   unsigned short num_heads;
   unsigned long hidden_sectors;
   unsigned char num_driver;
   unsigned long volume_id;
   char volume_label[11];
   unsigned short bytes_per_sector;
   unsigned char sectors_per_cluster;
   unsigned short sectors_reserved;
   unsigned char number_fats;
   unsigned long sectors_per_fat;
   unsigned long root_directory_first_cluster;
   unsigned long fat_begin_lba;
   unsigned long cluster_begin_lba;
   unsigned long root_dir_sectors;
   unsigned long first_data_sector;
   unsigned short signature;
} fat32_volume_id;

/* fat32_entry */
typedef struct fat32_entry {
   char file_name[8];
   char file_ext[3];
   union {
      unsigned char attrib;
      struct {
         int read_only : 1;
         int hidden : 1;
         int system : 1;
         int volume_label : 1;
         int directory : 1;
         int archive : 1;
         int reserved : 2;
      } s_attrib;
   } u_attrib;
   char reservedNT;
   unsigned char create_dec_seg;
   unsigned short create_time;
   unsigned short create_date;
   unsigned short last_access_date;
   unsigned short high_cluster;
   unsigned short last_modification_time;
   unsigned short last_modification_date;
   unsigned short low_cluster;
   unsigned long size_file;
} __attribute__((packed)) fat32_entry;

/* fat32_init */
unsigned int fat32_init(int drive, unsigned int partition);

/* fat32_lba_addr */
unsigned long fat32_lba_addr(unsigned int partition, unsigned long cluster);

/* fat32_get_volume_id */
fat32_volume_id *fat32_get_volume_id(unsigned int partition);

/* fat32_ls */
void fat32_ls(unsigned int drive, unsigned partition, const char *param);

/* fat32_set_entry */
void fat32_set_entry(const char *buffer, fat32_entry *t_entry);

/* fat32_read_entry */
void fat32_read_entry(unsigned int drive, unsigned int partition, unsigned long cluster);

/* fat32_cd */
int fat32_cd(unsigned int drive, unsigned partition, const char *ldir_name);

/* fat32_rm */
void fat32_rm(unsigned int drive, unsigned partition, const char *ldir_name);

/* fat32_cat */
int fat32_cat(unsigned int drive, unsigned partition, const char *lfile_name, const unsigned char *param);

/* fat32_show_cluster */
void fat32_show_cluster(unsigned int drive, unsigned int partition, int cluster, unsigned int tail);

/* fat32_read_fat */
unsigned int fat32_read_fat(unsigned int drive, unsigned int partition, unsigned long cluster);

/* fat32_get_file_entry */
int fat32_find_entry(unsigned int drive, unsigned partition, fat32_entry *lentry, const char *lfile_name, char attrib);

/* fat32_get_file */
int fat32_get_file(unsigned int drive, unsigned int partition, long cluster, char *data);

