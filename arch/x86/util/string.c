/*
    string
*/

#include "string.h"
#include <driver/video/vga.h>

/* copiar string */
void strcpy(const char *source, char *destination) {
   while (*source != 0) {
       *destination++=*source++;
   }
}

/* retornar numero de caracteres encontrado */
unsigned int strfoc(const char *source, unsigned char c) {
   unsigned int foc=0;
   while (*source != 0) {
       if (*source == c)
          foc++;
       source++;
   }
   return foc;
}

/* preencher restante de uma string */
void strfill(char *dest, char c, int size) {
   if (strlen(dest) >= size)
      return;
      
   int i = 0;
   dest += (size+strlen(dest)); // Nao me pergunte o porque disso, mas assim
                                // funciona !!! ;D
   for (;i<=(size - strlen(dest));i++) {
       *dest-- = c;
   }
}

/* copiar string com tamanho determinado */
void strcpyx(const char *source, char *destination, unsigned int num) {
   int i=0;
   for (;i<num;i++) {
       *destination++=*source++;   
   }
}

/* split */
void strsplit(const char *msg, char *src, unsigned char delimiter, unsigned int offset) {
   int x=0;
   char c = -1;
   while ((c = *msg++) != 0) {
       if (x == offset) {
          if (c == delimiter) {
             break;
          }
          *src++ = c;
       }
       if (c == delimiter) {
          x++;
       }
   }
}

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal.  */
void itoa (char *buf, int base, int d)
{
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
  
  /* If %d is specified and D is minus, put `-' in the head.  */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;

  /* Divide UD by DIVISOR until UD == 0.  */
  do
    {
      int remainder = ud % divisor;
      
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);

  /* Terminate BUF.  */
  *p = 0;
  
  /* Reverse BUF.  */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

/* strlen - tamanho da string */
int strlen(const char *a) {
    int len = 0;
    while (*a) {
       len++;
       a++;
    }
    return len;
}

/* strcmp - comparar strings */
int strcmp(const char *a, const char *b) {
    if (strlen(a) != strlen(b))
       return 0;
       
    if (strlen(a) == 0)
       return 1;

    while (*a) {
       if (*a != *b)
          return 0;
       a++;
       b++;
    }
    
    return 1;
}

/* strcmpx - comparar strings (limitado) */
int strcmpx(const char *a, const char *b, unsigned char size) {
    if (strlen(a) != strlen(b))
       return 0;
       
    if (strlen(a) == 0)
       return 1;

    while (*a || size != 0) {
       if (*a != *b)
          return 0;
       a++;
       b++;
       size--;
    }
    
    return 1;
}

/* strupper - letra maiuscula */
void strupper(char *msg) {
    while (*msg) {
       if (*msg >= 97 && *msg <=122) {
          *msg = *msg - 32;
       }
       msg++;
    }
}

/* strlower - letra minuscula */
void strlower(char *msg) {
    while (*msg) {
       if (*msg >= 65 && *msg <=90) {
          *msg = *msg + 32;
       }
       msg++;
    }
}

/* strclear - limpa string */
void strclear(char *a) {
    while (*a) {
       *a++ = '\0';
    }
}

/* strtrim - limpa espacos no inicio e fim da string */
void strtrim(char *str) {
    int i = strlen(str)-1, j=0;
    str += i;
    for (;j<i;j++) {
        if (*str == ' ') {
           *str = '\0';
        } else {
           break;
        }
        str--;
    }
}

/* strconcat - concatenar string */
void strconcat(char *dest, char *format, ...)
{
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;
  
  while ((c = *format++) != 0)
    {
      if (c != '%')
	*dest++ = c;
      else
	{
	  char *p;
	  
	  c = *format++;
	  switch (c)
	    {
	    case 'd':
	    case 'u':
	    case 'x':
	      itoa (buf, c, *((int *) arg++));
	      p = buf;
	      goto string;
	      break;

	    case 's':
	      p = *arg++;
	      if (! p)
		p = "(null)";

	    string:
	      while (*p)
		*dest++ = *p++;
	      break;

	    default:
	      *dest++ = *((int *) arg++);
	      break;
	    }
	}
    }

}

