/*
    alloc
*/

/* malloc */
void *malloc(unsigned int size) {
   char c;
   char *pc = &c;
   char *tmp = pc;
   int x = 0;
   for (;x<size;x++)
       *pc++='\0';
   return (void *) tmp;
}

