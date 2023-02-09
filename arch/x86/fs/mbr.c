/*
    Master Boot Record
*/

#include "mbr.h"
#include <driver/hdd/hdd.h>
#include <driver/video/vga.h>
#include <util/string.h>

/* mbr_read */
void mbr_read(mbr *lmbr, int drive) {
   if (! hdd_test_drive(drive, 0))
      return;
   char buffer[512];
   hdd_read28(drive, 0, &buffer[0]); // Ler a MBR
   
   // Atribuir valores
   lmbr->partition[0].boot_flag = buffer[446];
   lmbr->partition[0].chs_begin[0] = buffer[447];
   lmbr->partition[0].chs_begin[1] = buffer[448];
   lmbr->partition[0].chs_begin[2] = buffer[449];
   lmbr->partition[0].type = buffer[450];
   lmbr->partition[0].chs_end[0] = buffer[451];
   lmbr->partition[0].chs_end[1] = buffer[452];
   lmbr->partition[0].chs_end[2] = buffer[453];
   lmbr->partition[0].lba_begin = (buffer[457] << 24) | (buffer[456] << 16) | (buffer[455] << 8) | buffer[454];
   lmbr->partition[0].number_sectors = (unsigned char) (buffer[461] << 24) | (unsigned char) (buffer[460] << 16) | (unsigned char) (buffer[459] << 8) | (unsigned char) buffer[458];

   lmbr->partition[1].boot_flag = buffer[462];
   lmbr->partition[1].chs_begin[0] = buffer[463];
   lmbr->partition[1].chs_begin[1] = buffer[464];
   lmbr->partition[1].chs_begin[2] = buffer[465];
   lmbr->partition[1].type = buffer[466];
   lmbr->partition[1].chs_end[0] = buffer[467];
   lmbr->partition[1].chs_end[1] = buffer[468];
   lmbr->partition[1].chs_end[2] = buffer[469];
   lmbr->partition[1].lba_begin = (buffer[473] << 24) | (buffer[472] << 16) | (buffer[471] << 8)| buffer[470];
   lmbr->partition[1].number_sectors = (buffer[477] << 24) | (buffer[476] << 16) | (buffer[475] << 8)| buffer[474];

   lmbr->partition[2].boot_flag = buffer[478];
   lmbr->partition[2].chs_begin[0] = buffer[479];
   lmbr->partition[2].chs_begin[1] = buffer[480];
   lmbr->partition[2].chs_begin[2] = buffer[481];
   lmbr->partition[2].type = buffer[482];
   lmbr->partition[2].chs_end[0] = buffer[483];
   lmbr->partition[2].chs_end[1] = buffer[484];
   lmbr->partition[2].chs_end[2] = buffer[485];
   lmbr->partition[2].lba_begin = (buffer[489] << 24) | (buffer[488] << 16) | (buffer[487] << 8)| buffer[486];
   lmbr->partition[2].number_sectors = (buffer[493] << 24) | (buffer[492] << 16) | (buffer[491] << 8)| buffer[490];

   lmbr->partition[3].boot_flag = buffer[494];
   lmbr->partition[3].chs_begin[0] = buffer[495];
   lmbr->partition[3].chs_begin[1] = buffer[496];
   lmbr->partition[3].chs_begin[2] = buffer[497];
   lmbr->partition[3].type = buffer[498];
   lmbr->partition[3].chs_end[0] = buffer[499];
   lmbr->partition[3].chs_end[1] = buffer[500];
   lmbr->partition[3].chs_end[2] = buffer[501];
   lmbr->partition[3].lba_begin = (buffer[505] << 24) | (buffer[504] << 16) | (buffer[503] << 8)| buffer[502];
   lmbr->partition[3].number_sectors = (buffer[509] << 24) | (buffer[508] << 16) | (buffer[507] << 8)| buffer[506];

   lmbr->signature1 = buffer[510];
   lmbr->signature2 = buffer[511];

}
