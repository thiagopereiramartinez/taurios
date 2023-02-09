/*
    floppy - disquete
*/

#include <asm/io.h>
#include <driver/video/vga.h>

/* floppy_detect */
void floppy_detect(void) {
    unsigned char c;
    outb(0x70, 0x10);
    c = inb(0x71);
    
    unsigned char a, b;
    a = c >> 4;
    b = c & 0xF;
    
    char *drive_type[6] = {
        "No floppy drive",
        "360kb 5.25in floppy drive",
        "1.2mb 5.25in floppy drive",
        "720kb 3.5in",
        "1.44mb 3.5in",
        "2.88mb 3.5in"
    };
    
    printf("Floppy drive A is an: %s\n", drive_type[a]);
    printf("Floppy drive B is an: %s\n", drive_type[b]);
}
