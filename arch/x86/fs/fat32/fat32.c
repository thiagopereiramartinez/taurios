/*
    FAT32 - File Allocation Table (32)
*/

#include "fat32.h"
#include <fs/mbr.h>
#include <driver/video/vga.h>
#include <driver/hdd/hdd.h>
#include <util/scanf.h>
#include <util/alloc.h>
#include <util/string.h>
#include <include/colors.h>

/* variaveis */
mbr lmbr;
fat32_volume_id f_volume_id[4];
fat32_entry entry[128];
int fat32_nivel = 0;
int current_cluster = 0;

/* fat32_init */
unsigned int fat32_init(int drive, unsigned int partition) {
   /* ler mbr */
   mbr_read(&lmbr, drive);
   if (lmbr.partition[partition].type == 0) { // no partition
      return 0;
   }
   if (lmbr.partition[partition].type != 0x0b && lmbr.partition[partition].type != 0x0c) {
      printf("No valid FAT32 partition in %d.\n", partition);
      return 0;
   }
   
   /* ler volume id */
   char buffer[512];
   hdd_read28(drive, lmbr.partition[partition].lba_begin, &buffer[0]);

   //atribuir valores   
   fat32_volume_id *fv_id = &f_volume_id[partition];
   strcpyx(&buffer[0x03], &(fv_id->OEM_name[0]), 8);
   fv_id->media = buffer[21];
   fv_id->sectors_per_track = (buffer[25] << 8) | buffer[24];
   fv_id->num_heads = (buffer[27] << 8) | buffer[26];
   fv_id->hidden_sectors = (buffer[31] << 24) | (buffer[30] << 16) | (buffer[29] << 8) | buffer[28];
   fv_id->num_driver = buffer[36];
   fv_id->volume_id = (buffer[70] << 24) | (buffer[69] << 16) | (buffer[68] << 8) | buffer[67];
   strcpyx(&buffer[71], &(fv_id->volume_label[0]), 11);
   fv_id->bytes_per_sector = (buffer[0x0C] << 8) | buffer[0x0B];
   fv_id->sectors_per_cluster = (unsigned char) buffer[0x0D];
   fv_id->sectors_reserved = (unsigned char) (buffer[0x0F] << 8) | (unsigned char) buffer[0x0E];
   fv_id->number_fats = (unsigned char) buffer[0x10];
   fv_id->sectors_per_fat = (buffer[0x27] << 24) | (buffer[0x26] << 16) | (buffer[0x25] << 8) | (unsigned char) buffer[0x24];
   fv_id->root_directory_first_cluster = ((unsigned char) buffer[0x2F] << 24) | (unsigned char) (buffer[0x2E] << 16) |(unsigned char) (buffer[0x2D] << 8) | (unsigned char) buffer[0x2C];
   fv_id->signature = (unsigned char) (buffer[0x1FF] << 8) | (unsigned char) buffer[0x1FE];
   fv_id->fat_begin_lba = lmbr.partition[partition].lba_begin + fv_id->sectors_reserved;
   fv_id->cluster_begin_lba = lmbr.partition[partition].lba_begin + fv_id->sectors_reserved + (fv_id->number_fats * fv_id->sectors_per_fat);
   
   // testar bytes por setores
   if (fv_id->bytes_per_sector <= 0) {
      printf("FAT bytes per sector invalid.\n");
      return 0;
   }
   
   fv_id->root_dir_sectors = ( ( ( (buffer[18] << 8) | buffer[17]) * 32) + (fv_id->bytes_per_sector - 1)) / fv_id->bytes_per_sector;
   fv_id->first_data_sector = fv_id->sectors_reserved + (fv_id->number_fats * fv_id->sectors_per_fat) + fv_id->root_dir_sectors;
   
   
   // testar assinatura
   if (buffer[0x1FE] != 85 || buffer[0x1FF] != -86) {
      printf("FAT signature invalid (%d %d). Drive: %d Partition:%d\n", buffer[0x1FE], buffer[0x1FF], drive, partition);
      return 0;
   }
   
   // testar FAT
   if (fv_id->bytes_per_sector != 512) {
      printf("Error: Bytes per Sector invalid.\n");
      return 0;
   }
   
   if (fv_id->number_fats != 2) {
      printf("Error: Number FAT's invalid.\n");
      return 0;
   }

   // Ler entradas do cluster do root
   current_cluster = fv_id->root_directory_first_cluster;
   
   /* retorna sucesso */
   printf("FAT in partition %d initialized\n", partition);
/*   printf("     Volume ID: %d\n", fv_id->volume_id);
   printf("     Volume Label: %s\n", fv_id->volume_label);
   printf("     OEM: %s\n", fv_id->OEM_name);
   printf("     Byter per sector: %d\n", fv_id->bytes_per_sector);
   printf("     Sectors per cluster: %d\n", fv_id->sectors_per_cluster);
   printf("     Sectors reserved: %d\n", fv_id->sectors_reserved);
   printf("     Number FAT's: %d\n", fv_id->number_fats);
   printf("     Sectors per FAT: %d\n", fv_id->sectors_per_fat);
   printf("     Root Directory First Cluster: %d\n", fv_id->root_directory_first_cluster);
   printf("     FAT begin LBA: %d\n", fv_id->fat_begin_lba);
   printf("     Cluster begin LBA: %d\n", fv_id->cluster_begin_lba); */
   return 1;
}

/* fat32_lba_addr */
unsigned long fat32_lba_addr(unsigned int partition, unsigned long cluster) {
   return f_volume_id[partition].cluster_begin_lba + ( (cluster-2) * f_volume_id[partition].sectors_per_cluster);
}

/* fat32_get_volume_id */
fat32_volume_id *fat32_get_volume_id(unsigned int partition) {
   return &f_volume_id[partition];
}

/* fat32_set_entry */
void fat32_set_entry(const char *buffer, fat32_entry *t_entry) {
   strcpyx(&buffer[0], t_entry->file_name, 8);
   strcpyx(&buffer[8], t_entry->file_ext, 3);
   t_entry->u_attrib.attrib = buffer[11];
   t_entry->create_dec_seg = buffer[13];
   t_entry->create_time = (buffer[15] << 8) | buffer[14];
   t_entry->create_date = (buffer[17] << 8) | buffer[16];
   t_entry->last_access_date = (buffer[19] << 8) | buffer[18];
   t_entry->high_cluster = (buffer[21] << 8) | buffer[20];
   t_entry->last_modification_time = (buffer[23] << 8) | buffer[22];
   t_entry->last_modification_date = (buffer[25] << 8) | buffer[24];
   t_entry->low_cluster = (buffer[27] << 8) | buffer[26];
   t_entry->size_file = (buffer[31] << 24) | (buffer[30] << 16) | (buffer[29] << 8) | buffer[28];
   
   strlower(t_entry->file_name);
   strlower(t_entry->file_ext);
}

/* fat32_read_entry */
void fat32_read_entry(unsigned int drive, unsigned int partition, unsigned long cluster) {
   // Ler todos setores do cluster, atribuindo suas respectivas entradas
   int i,j=0;
   for (i=0;i<f_volume_id[partition].sectors_per_cluster;i++) {
       char buffer[512];
       
       // ler cluster
       hdd_read28(drive, fat32_lba_addr(partition, cluster)+i, &buffer[0]);

       // Atribuir valores
       int x=0;
       for (;x<16;x++) {
           fat32_set_entry(&buffer[0+(32*x)], &entry[j]);
           j++;
       }
   }
}

/* fat32_read_fat */
unsigned int fat32_read_fat(unsigned int drive, unsigned int partition, unsigned long cluster) {
   // Ler setor da FAT
   char buffer[512];
   unsigned int fat_offset = cluster * 4;
   unsigned int fat_sector = f_volume_id[partition].fat_begin_lba + (fat_offset / f_volume_id[partition].bytes_per_sector);
   unsigned int ent_offset = fat_offset % 512;
       
   // ler setor da FAT
   hdd_read28(drive, fat_sector, &buffer[0]);

   // Retornar proximo cluster
   unsigned int table_value = *(unsigned int*)&buffer[ent_offset] & 0xFFFFFFF;
   return table_value;
}

/* fat32_cd */
int fat32_cd(unsigned int drive, unsigned partition, const char *ldir_name) {
   fat32_entry lentry;
   int r = fat32_find_entry(drive, partition, &lentry, ldir_name, FAT32_ATTRIB_DIRECTORY);
   if (r == 0)
      return 0;
   
   // testar se eh o ".." indicando para o diretorio root
   if (lentry.file_name[0] == '.' && lentry.file_name[1] == '.' && fat32_nivel == 1) {
      lentry.high_cluster = 0;
      lentry.low_cluster = 2;
   }

   // ir ao diretorio
   current_cluster = (lentry.high_cluster << 16) | lentry.low_cluster;
   
   // nivel
   if (ldir_name[0] == '.' && ldir_name[1] == '.') {
      fat32_nivel--;
   } else if (ldir_name[0] == '.' && ldir_name[1] != '.') {
   } else {
      fat32_nivel++;
   }
   
   return 1;
}

/* fat32_rm */
void fat32_rm(unsigned int drive, unsigned partition, const char *ldir_name) {

}

/* fat32_ls */
void fat32_ls(unsigned int drive, unsigned partition, const char *param) {
   // Modo completo
   int completo = 0;
   if (param[0] == -1) {
      completo = 1;
   }
   
   // Ler diretorio
   int cluster = current_cluster;
   int k=0;
   while (1) {
       fat32_read_entry(drive, partition, cluster);
       // Listar
       int i=0,j=0;
       for (;i<128;i++) {

           // Testar a entrada eh de um diretorio ou arquivo
           if (entry[i].u_attrib.attrib != FAT32_ATTRIB_DIRECTORY && entry[i].u_attrib.attrib != FAT32_ATTRIB_ARCHIVE) {
              continue;
           }

           // Testar se eh fim de diretorio
           if (entry[i].file_name[0] == 0x0) {
              break;
           }

           // Testar se nao esta apagado
           if (entry[i].file_name[0] == 0xFFFFFFE5) {
              continue;
           }
       
           // Arquivo oculto
           if (entry[i].u_attrib.s_attrib.hidden == 1 && completo == 0)
              continue;
       
           // Testar se eh oculto (comecar com '.')
           if (entry[i].file_name[0] == '.' && completo == 0)
              continue;
              
           // Testar se eh um arquivo ELF
           int elf = 0;
           char buffer[512];
           hdd_read28(drive, fat32_lba_addr(partition, (entry[i].high_cluster << 16) | entry[i].low_cluster), &buffer[0]);
           if (buffer[0] == 0x7F && buffer[1] == 0x45 && buffer[2] == 0x4c && buffer[3] == 0x46)
              elf = 1;
          
           // Cor azul para diretorio
           if (entry[i].u_attrib.attrib == FAT32_ATTRIB_DIRECTORY)
              vga_setcolor(COLOR_BLUE, COLOR_BLACK);
       
           // Cor branco para arquivos
           if (entry[i].u_attrib.attrib == FAT32_ATTRIB_ARCHIVE)
              vga_setcolor(COLOR_GREY, COLOR_BLACK);
              
           // Cor verde para arquivos ELF
           if (elf)
              vga_setcolor(COLOR_GREEN, COLOR_BLACK);
          
           // Mostrar nome
           char fn_nome[20];
           strcpyx(entry[i].file_name, fn_nome, 8);
       
          // Espacamento - 5 entradas por linha - modo simples
          if (completo == 0) {
             // Modo de listagem simples
             putcx(fn_nome, 8);
             j++;
             k++;
             if (j <= 4) {
                printf("         ");
             } else {
                printf("\n");
                j = 0;
             }
          } else {
             // Modo de listagem completa
             printf("Cluster: %d - Size: %dBytes --> %s\n", (entry[i].high_cluster << 16) | entry[i].low_cluster, entry[i].size_file, fn_nome);
             k++;
          }
       }
       // Ler proximo cluster da FAT
       cluster = fat32_read_fat(drive, partition, cluster);
       
       // Fim da cadeia
       if (cluster == 0xFFFFFF8 || cluster == 0xFFFFFFF)
          break;
   }
   if (k > 0) {
      vga_setcolor(COLOR_GREY, COLOR_BLACK);
      if ((k % 5) != 0)
         printf("\n");
   }
}

/* fat32_show_cluster */
void fat32_show_cluster(unsigned int drive, unsigned int partition, int cluster, unsigned int tail) {
   int i=0;
   for (;i<4;i++) {
       char buffer[512];
       hdd_read28(drive, fat32_lba_addr(partition, cluster)+i, &buffer[0]);
       printf(buffer);
       if (tail == 1)
          pause();
       break;
   }
}

/* fat32_cat */
int fat32_cat(unsigned int drive, unsigned partition, const char *lfile_name, const unsigned char *param) {

   // Modo tail - le 512bytes e pausa
   int tail = 0;
   if (*param == 0xFA)
      tail = 1;

   // Procurar entrada
   fat32_entry lentry;
   int r = fat32_find_entry(drive, partition, &lentry, lfile_name, FAT32_ATTRIB_ARCHIVE);
   if (r == 0)
      return 0;
   
   // Ler resto do arquivo procurando pela FAT
   int f_cluster = (lentry.high_cluster << 16) | lentry.low_cluster;
   while (1) {
       // ir ao arquivo
       fat32_show_cluster(drive, partition, f_cluster, tail);
   
       // Ler proximo cluster pela FAT
       f_cluster = fat32_read_fat(drive, partition, f_cluster);
       
       // Testar fim da cadeia de clusters
       if (f_cluster == 0xFFFFFF8 || f_cluster == 0xFFFFFFF)
          break;
   }

   printf("\n");   
   return 1;
}

/* fat32_get_file_entry */
int fat32_find_entry(unsigned int drive, unsigned partition, fat32_entry *lentry, const char *lfile_name, char attrib) {
   // Nome do arquivo
   char file_name[8];
   strcpyx(lfile_name, file_name, 8);
   strfill(file_name, ' ', 8);
   
   /* procurar nas entradas o arquivo */
   int i=0,j=0;
   int cluster = current_cluster;
   while (1) {
       fat32_read_entry(drive, partition, cluster);
       for (i=0;i<128;i++) {
           // Testar tipo
           if (entry[i].u_attrib.attrib != attrib)
              continue;

           // testar nome
           if (entry[i].file_name[0] == file_name[0] &&
              entry[i].file_name[1] == file_name[1] &&
              entry[i].file_name[2] == file_name[2] &&
              entry[i].file_name[3] == file_name[3] &&
              entry[i].file_name[4] == file_name[4] &&
              entry[i].file_name[5] == file_name[5] &&
              entry[i].file_name[6] == file_name[6] &&
              entry[i].file_name[7] == file_name[7]) {
              j++;
              goto sair;
           }
       }
       // Ler cadeia de clusters da FAT
       cluster = fat32_read_fat(drive, partition, cluster);
       if (cluster == 0xFFFFFF8 || cluster == 0xFFFFFFF)
          break;
   }
   sair:
   
   // nenhum encontrado
   if (j == 0) {
      strtrim(file_name);
      char *n_type[] = {"File", "Directory", "Unknown"};
      printf("%s '%s' not found.\n", n_type[attrib == FAT32_ATTRIB_ARCHIVE ? 0 : attrib == FAT32_ATTRIB_DIRECTORY ? 1 : 2], file_name);
      return 0;
   }
   
   // retornar entrada
   *lentry = entry[i];
   return 1;
}

/* fat32_get_file */
int fat32_get_file(unsigned int drive, unsigned int partition, long cluster, char *data) {
   if (cluster <= 0)
      return 0;

   // ir ao arquivo
   int i=0;
   for (;i<4;i++) {
       hdd_read28(drive, fat32_lba_addr(partition, cluster)+i, &data[512*i]);
   }
   
   // Ler resto do arquivo procurando pela FAT
   while (1) {
       // Ler proximo cluster pela FAT
       cluster = fat32_read_fat(drive, partition, cluster);
       
       // Testar fim da cadeia de clusters
       if (cluster == 0xFFFFFF8 || cluster == 0xFFFFFFF)
          break;
      
       // Mostrar cluster
       int j=0;
       for (;j<4;j++) {
           i++;
           hdd_read28(drive, fat32_lba_addr(partition, cluster)+j, &data[512*i]);
       }
   
   }
   
   return 1;
}

