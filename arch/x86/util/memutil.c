/*
   Utilitarios
*/

/* include */
#include "memutil.h"

/* memcpy */
void *memcpy(void *dest, const void *src, int count) {
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

/* memset */
void *memset(void *dest, char val, int count) {
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

/* memsetw */
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

