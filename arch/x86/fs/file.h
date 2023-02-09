/*
    File
*/

/* file */
typedef struct FILE {
   char file_name[8];
   char type;
   unsigned long file_size;
   unsigned long fat32_cluster;
} FILE;

/* fopen */
FILE fopen(const char *filename);

/* fread */
int fread(FILE *fp, char *data);

