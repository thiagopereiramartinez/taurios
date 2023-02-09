/*
    ler teclado
*/

#define ECHO_NORMAL           0
#define ECHO_HIDE             1
#define ECHO_SECURE           2

#define NO_SKIP               0
#define AUTO_SKIP             1

/* scanf */
void scanf(char *str, int size, int echo, int skip);

/* scanfinterrupt - interrompe ao receber sinal */
char scanfinterrupt(char *str, int size, char *signal, int echo, int skip);

/* pause */
void pause(void);
