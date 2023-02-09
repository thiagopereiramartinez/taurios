/*
    Obter data e hora
*/

/* iniciar variaveis */
void datetime_init(void);

/* obter dia */
int datetime_day(void);

/* obter mes */
int datetime_month(void);

/* obter ano */
int datetime_year(void);

/* obter horas */
int datetime_hours(void);

/* obter minutos */
int datetime_minutes(void);

/* obter seconds */
int datetime_seconds(void);

/* obter week */
int datetime_week(void);

/* obter dia da semana por extenso */
void datetime_str_week(char *str);

/* obter dia da semana por extenso reduzido */
void datetime_str_week_short(char *str);

/* obter mes por extenso */
void datetime_str_month(char *str);

/* obter mes por extenso reduzido */
void datetime_str_month_sort(char *str);


