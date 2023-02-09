/*
    Console de comandos
*/

/* Parametros do sistema operacional */
#ifndef OS_NAME
   #error OS_NAME not specified
#endif

#ifndef OS_VERSION
   #error OS_VERSION not specified
#endif

#ifndef OS_DIST
   #error OS_DIST not specified
#endif

/* include */
#include "console.h"
#include <asm/power.h>
#include <asm/pci.h>
#include <driver/hdd/hdd.h>
#include <driver/video/vga.h>
#include <fs/filesystem.h>
#include <fs/file.h>
#include <fs/fat32/fat32.h>
#include <util/datetime.h>
#include <util/string.h>
#include <util/scanf.h>

/* variaveis */
char comando[50];
char pcomando[50][50];
char login[20]="root";
char senha[20];
char last_comando[512][50];
int current_command = 0;
int teste = 0;

/* iniciar console */
void console_init(void) {
    printf("\n%s %s v%s - Console\n\n", OS_NAME, OS_DIST, OS_VERSION);
    
    console_getcommand();
    
    /* pegar usuario */
    for (;;) {
        strclear(&login[0]);
        strclear(&senha[0]);
        printf("\nLogin: ");
        scanf(&login[0], 20, ECHO_NORMAL, NO_SKIP);

        /* pegar senha */
        printf("Password: ");
        scanf(&senha[0], 20, ECHO_SECURE, NO_SKIP);
    
        /* testar usuario */
        if (! strcmp(login, "root")) {
           printf("Invalid user '%s'.\n", login);
           continue;
        }

        /* testar senha */
        if (! strcmp(senha, "patosdeminas")) {
           printf("Invalid password.\n");
           continue;
        }
        
        break;
    }
    printf("\n");
    console_getcommand();
}

/* console_getcommand */
void console_getcommand(void) {
   while (1) {
      strclear(&comando[0]);
      int k=0;
      for (;k<50;k++)
          strclear(&pcomando[k][0]);
      printf("%s@%s: ", login, fs_pwd());
          
      scanf(&comando[0], 50, ECHO_NORMAL, NO_SKIP);
      
      // separar parametros
      int param = strfoc(comando, ' ')-1;
      int i;
      if (param >= -1) {
         if (param == -1)
            param = 1;
         if (param == 0)
            param = 2;
            
         for (i=0;i<param;i++) {
            strsplit(comando, pcomando[i], ' ', i);
         }
      }
      
      // executar comando
      __console_command_process();
   }
}

/* __console_command_process */
void __console_command_process(void) {
   /* vazio */
   if (strlen(comando) == 0)
      return;

   /* 'login' ou 'exit' */
   if (strcmp(comando, "login")) {
      console_init();
      return;
   }

   if (strcmp(comando, "exit")) {
      console_init();
      return;
   }
   
   /* mostrar data e hora */
   if (strcmp(comando, "date")) {
      datetime_init();
      char a[15], b[15];
      strclear(&a[0]);
      strclear(&b[0]);
      datetime_str_week(&a[0]);
      datetime_str_month(&b[0]);
      printf("%s, %s %d, %d to %d:%d:%d\n", a, b, datetime_day(), (2000+datetime_year()), datetime_hours(), datetime_minutes(), datetime_seconds());
      return;
   }
   
   /* limpar tela */
   if (strcmp(comando, "cls")) {
      vga_cls();
      return;
   }
   
   /* reiniciar */
   if (strcmp(comando, "reboot")) {
      reboot();
      return;
   }
   
   /* desligar (DEPRECATED) */
   if (strcmp(comando, "halt")) {
      halt();
      return;
   }
   
   /* lspci */
   if (strcmp(comando, "lspci")) {
      pci_ls();
      return;
   }
   
   /* cd */
   if (strcmp(pcomando[0], "cd")) {
      fs_cd(fs_get_cur_driver(), fs_get_cur_partition(), &pcomando[1][0]);
      return;
   }

   /* cat */
   if (strcmp(pcomando[0], "cat")) {
      fs_cat(fs_get_cur_driver(), fs_get_cur_partition(), &pcomando[1][0], (unsigned char *) 0x00);
      return;
   }

   /* tail */
   if (strcmp(pcomando[0], "tail")) {
      strfill(pcomando[1], ' ', 8);
      unsigned char c = 0xFA;
      fs_cat(fs_get_cur_driver(), fs_get_cur_partition(), &pcomando[1][0], &c);
      return;
   }
   
   if (strcmp(pcomando[0], "teste")) {
      int x = 2;
      x = x / 0;
   }

   /* ls */
   if (strcmp(comando, "ls")) {
      const char param;
      fs_ls(fs_get_cur_driver(), fs_get_cur_partition(), &param);
      return;
   }
   
   /* l */
   if (strcmp(comando, "l")) {
      const char param = 0xFF;
      fs_ls(fs_get_cur_driver(), fs_get_cur_partition(), &param);
      return;
   }
   
   /* regs */
   if (strcmp(comando, "regs")) {
      int eax,ebx,ecx,edx,esi,edi,esp,ebp,ds,es,fs,gs,cs,ss;
      asm volatile("mov %%eax, %0" : "=r"(eax));
      asm volatile("mov %%ebx, %0" : "=r"(ebx));
      asm volatile("mov %%ecx, %0" : "=r"(ecx));
      asm volatile("mov %%edx, %0" : "=r"(edx));
      asm volatile("mov %%esi, %0" : "=r"(esi));
      asm volatile("mov %%edi, %0" : "=r"(edi));
      asm volatile("mov %%ebp, %0" : "=r"(ebp));
      asm volatile("mov %%esp, %0" : "=r"(esp));
      asm volatile("mov %%ds, %0" : "=r"(ds));
      asm volatile("mov %%es, %0" : "=r"(es));
      asm volatile("mov %%fs, %0" : "=r"(fs));
      asm volatile("mov %%gs, %0" : "=r"(gs));
      asm volatile("mov %%ss, %0" : "=r"(ss));
      asm volatile("mov %%cs, %0" : "=r"(cs));
      
      printf("EAX=");
      printf_hex(eax);
      printf("   EBX=");
      printf_hex(ebx);
      printf("   ECX=");
      printf_hex(ecx);
      printf("   EDX=");
      printf_hex(edx);
      printf("\nESI=");
      printf_hex(esi);
      printf("   EDI=");
      printf_hex(edi);
      printf("   ESP=");
      printf_hex(esp);
      printf("   EBP=");
      printf_hex(ebp);
      printf("\nDS=");
      printf_hex(ds);
      printf("   ES=");
      printf_hex(es);
      printf("   FS=");
      printf_hex(fs);
      printf("   SS=");
      printf_hex(ss);
      printf("   CS=");
      printf_hex(cs);
      printf("\n");
      return;
   }
   
   /* teste */
   if (strcmp(comando, "teste")) {
      for (;;);
   }
   
   /******/   
   printf("Command '%s' not found.\n", pcomando[0]);
   
}
