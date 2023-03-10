; Este vai atribuir nossos novos registradores de segmento. N? precisaremos
; somente
; fazer algo especial para atribuir CS. N?s faremos o que ? chamado de
; um salto longo. Um salto que inclui um segmento assim como um offset.
; Este ? declarado em C como 'extern void gdt_flush();'
global gdt_flush     ; Permite ao c?digo C juntar este
extern gp            ; Diz que '_gp' est? em outro arquivo
gdt_flush:
    lgdt [gp]         ; Carrega GDT com nosso ponteiro especial 'gp'
    mov ax, 0x10      ; 0x10 ? o offset na GDT para nosso segmento de dados
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush2   ; 0x08 ? o offset para nosso segmento de c?digo: Salto longo!

flush2:
    ret               ; Retorna para o c?digo C!
