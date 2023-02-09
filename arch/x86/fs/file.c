/*
   File
*/

#include "file.h"
#include <fs/fat32/fat32.h>
#include <fs/filesystem.h>
#include <util/alloc.h>
#include <util/string.h>

/* fopen */
FILE fopen(const char *filename) {
   // Ler entrada
   FILE fp;
   fat32_entry entry;
   int r = fat32_find_entry(fs_get_cur_driver(), fs_get_cur_partition(), &entry, filename, FAT32_ATTRIB_ARCHIVE);
   if (r == 0)
      return fp;
      
   // atribuir valores
   strcpyx(entry.file_name, fp.file_name, 8);
   fp.type = 0xb;
   fp.file_size = entry.size_file;
   fp.fat32_cluster = (entry.high_cluster << 16) | entry.low_cluster;
   
   // retornar
   return fp;
}

/* fread */
int fread(FILE *fp, char *data) {
   if (fp->fat32_cluster <= 0)
      return 0;
      
   data = (char *)malloc(sizeof(char)*fp->file_size);
   return fat32_get_file(fs_get_cur_driver(), fs_get_cur_partition(), fp->fat32_cluster, data);
}
