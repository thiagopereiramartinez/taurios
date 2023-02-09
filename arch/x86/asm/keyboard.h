/*
    Keyboard
*/

/* definicoes */
#define RELEASE_KEY(x)               (0xFFFFFF80 | x)

#define VK_ESC                       0x01
#define VK_F1                        0x3B
#define VK_F2                        0x3C
#define VK_F3                        0x3D
#define VK_F4                        0x3E
#define VK_F5                        0x3F
#define VK_F6                        0x40
#define VK_F7                        0x41
#define VK_F8                        0x42
#define VK_F9                        0x43
#define VK_F10                       0x44
#define VK_F11                       0x57
#define VK_F12                       0x58
#define VK_PAUSE                     0x45
#define VK_PRT_SC                    0x37
#define VK_INSERT                    0x52
#define VK_DELETE                    0x53
#define VK_HOME                      0x47
#define VK_PAGE_UP                   0x49
#define VK_PAGE_DOWN                 0x51
#define VK_END                       0x4F
#define VK_CTRL                      0x1D
#define VK_SUPER                     0x5B
#define VK_ALT                       0x38
#define VK_SHIFT_LEFT                0x2A
#define VK_SHIFT_RIGHT               0x36
#define VK_POPUP                     0x5D
#define VK_CAPS_LOCK                 0xBA
#define VK_SHIFT_RIGHT               0x36
#define VK_SHIFT_RIGHT               0x36
#define VK_TAB                       0x0F
#define VK_BACKSPACE                 0x0E
#define VK_ENTER                     0x1C
#define VK_UP                        0x48
#define VK_DOWN                      0x50
#define VK_LEFT                      0x4B
#define VK_RIGHT                     0x4D
#define VK_APOSTROPHE                0x29
#define VK_1                         0x02
#define VK_2                         0x03
#define VK_3                         0x04
#define VK_4                         0x05
#define VK_5                         0x06
#define VK_6                         0x07
#define VK_7                         0x08
#define VK_8                         0x09
#define VK_9                         0x0A
#define VK_0                         0x0B
#define VK_MINUS                     0x0C
#define VK_EQUALS                    0x0D
#define VK_Q                         0x10
#define VK_W                         0x11
#define VK_E                         0x12
#define VK_R                         0x13
#define VK_T                         0x14
#define VK_Y                         0x15
#define VK_U                         0x16
#define VK_I                         0x17
#define VK_O                         0x18
#define VK_P                         0x19
#define VK_ACCENT                    0x1A
#define VK_OPEN_COCHETE              0x1B
#define VK_A                         0x1E
#define VK_S                         0x1F
#define VK_D                         0x20
#define VK_F                         0x21
#define VK_G                         0x22
#define VK_H                         0x23
#define VK_J                         0x24
#define VK_K                         0x25
#define VK_L                         0x26
#define VK_CEDILLA                   0x27
#define VK_TILDE                     0x28
#define VK_CLOSE_COCHETE             0x2B
#define VK_Z                         0x2C
#define VK_X                         0x2D
#define VK_C                         0x2E
#define VK_V                         0x2F
#define VK_B                         0x30
#define VK_N                         0x31
#define VK_M                         0x32
#define VK_COMMA                     0x33
#define VK_POINT                     0x34
#define VK_SEMICOLON                 0x35
#define VK_SPACE                     0x39
#define VK_BAR_LEFT                  0x56

/* Instala o tratamento do teclado no IRQ1 */
void keyboard_install();

/* obter letra */
char keyboard_readchar(void);

/* obter codigo */
char keyboard_readcode(void);

/* limpar dados */
void keyboard_clean(void);
