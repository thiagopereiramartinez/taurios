/*
    Paginacao
*/

/* pagina */
typedef union u_page {
   unsigned long l_page;
   struct {
       unsigned int present: 1; // Page present in memory
       unsigned int rw: 1; // Read-Only if clear, Read-Write if set
       unsigned int user: 1; // Supervisor level only if 0
       unsigned int write_through: 1; // Write Through
       unsigned int cache: 1; // Cache Disabled
       unsigned int accessed: 1; // Has the page been accessed since last refresh ?
       unsigned int dirty: 1; // Has the page been written to since last refresh ?
       unsigned int unused: 1; // Not used
       unsigned int global: 1; // Global
       unsigned int unused2: 3; // Not Unused
       unsigned int frame: 20; // Frame address (shifted right 12 bits)
   } page;
} page_t;

/* tabela de paginas */
typedef struct page_table {
   page_t pages[1024];
} page_table_t;

/* paging_init */
void init_paging(void);

