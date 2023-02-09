/*
    string
*/

/* copiar string */
void strcpy(const char *source, char *destination);

/* copiar string com tamanho determinado */
void strcpyx(const char *source, char *destination, unsigned int num);

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal.  */
void itoa (char *buf, int base, int d);

/* strcmp - comparar strings */
int strcmp(const char *a, const char *b);

/* strcmpx - comparar strings (limitado) */
int strcmpx(const char *a, const char *b, unsigned char size);

/* strclear - limpa string */
void strclear(char *a);

/* strlen - tamanho da string */
int strlen(const char *a);

/* split */
void strsplit(const char *msg, char *src, unsigned char delimiter, unsigned int offset);

/* retornar numero de caracteres encontrado */
unsigned int strfoc(const char *source, unsigned char c);

/* preencher restante de uma string */
void strfill(char *dest, char c, int size);

/* strupper - letra maiuscula */
void strupper(char *msg);

/* strlower - letra minuscula */
void strlower(char *msg);

/* strtrim - limpa espacos no inicio e fim da string */
void strtrim(char *str);

/* strconcat - concatenar string */
void strconcat(char *dest, char *format, ...);

