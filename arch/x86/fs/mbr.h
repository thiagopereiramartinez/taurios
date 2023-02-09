/*
    Master Boot Record
*/

/* estrutura da mbr */
typedef struct mbr {
    struct {
       char boot_flag;
       char chs_begin[3];
       char type;
       char chs_end[3];
       unsigned long lba_begin;
       unsigned long number_sectors;
    } partition[4];
    char signature1;
    char signature2;
} __attribute__((packed)) mbr;

/* mbr_read */
void mbr_read(mbr *lmbr, int drive);
