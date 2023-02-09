/*
    Obter data e hora
*/

#include <asm/cmos.h>
#include <util/string.h>

/* variavel de dados */
struct str_cmos s_datetime;

/* iniciar variaveis */
void datetime_init(void) {
   cmos_prepare();
   s_datetime = cmos_getdata();
}

/* obter dia */
int datetime_day(void) {
   return s_datetime.day;
}

/* obter mes */
int datetime_month(void) {
   return s_datetime.month;
}

/* obter ano */
int datetime_year(void) {
   return s_datetime.year;
}

/* obter horas */
int datetime_hours(void) {
   return s_datetime.hours;
}

/* obter minutos */
int datetime_minutes(void) {
   return s_datetime.minutes;
}

/* obter seconds */
int datetime_seconds(void) {
   return s_datetime.seconds;
}

/* obter week */
int datetime_week(void) {
   return s_datetime.week;
}

/* obter dia da semana por extenso */
void datetime_str_week(char *str) {
   switch(s_datetime.week) {
       case 1: strcpy("Sunday", str);break;
       case 2: strcpy("Monday", str);break;
       case 3: strcpy("Tuesday", str);break;
       case 4: strcpy("Wednesday", str);break;
       case 5: strcpy("Thursday", str);break;
       case 6: strcpy("Friday", str);break;
       case 7: strcpy("Saturday", str);break;
       default: strcpy("(none)", str);break;
   }
}

/* obter dia da semana por extenso reduzido */
void datetime_str_week_short(char *str) {
   switch(s_datetime.week) {
       case 1: strcpy("Sun", str);break;
       case 2: strcpy("Mon", str);break;
       case 3: strcpy("Tue", str);break;
       case 4: strcpy("Wed", str);break;
       case 5: strcpy("Thu", str);break;
       case 6: strcpy("Fri", str);break;
       case 7: strcpy("Sat", str);break;
       default: strcpy("non", str);break;
   }
}

/* obter mes por extenso */
void datetime_str_month(char *str) {
   switch(s_datetime.month) {
       case 1: strcpy("January", str);break;
       case 2: strcpy("February", str);break;
       case 3: strcpy("March", str);break;
       case 4: strcpy("April", str);break;
       case 5: strcpy("May", str);break;
       case 6: strcpy("June", str);break;
       case 7: strcpy("July", str);break;
       case 8: strcpy("August", str);break;
       case 9: strcpy("September", str);break;
       case 10: strcpy("October", str);break;
       case 11: strcpy("November", str);break;
       case 12: strcpy("December", str);break;
       default: strcpy("(none)", str);break;
   }
}

/* obter mes por extenso reduzido */
void datetime_str_month_sort(char *str) {
   switch(s_datetime.month) {
       case 1: strcpy("Jan", str);break;
       case 2: strcpy("Feb", str);break;
       case 3: strcpy("Mar", str);break;
       case 4: strcpy("Apr", str);break;
       case 5: strcpy("May", str);break;
       case 6: strcpy("Jun", str);break;
       case 7: strcpy("Jul", str);break;
       case 8: strcpy("Aug", str);break;
       case 9: strcpy("Sep", str);break;
       case 10: strcpy("Oct", str);break;
       case 11: strcpy("Nov", str);break;
       case 12: strcpy("Dec", str);break;
       default: strcpy("non", str);break;
   }
}


