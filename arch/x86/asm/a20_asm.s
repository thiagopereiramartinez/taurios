; ativar a20
global __a20_enable
global __a20_test
extern a20_enabled
extern a20_disabled

__a20_enable:
    in al, 0x92
    test al, 2
    jnz __a20_after
    or al, 2
    and al, 0xFE
    out 0x92, al

__a20_after:
    ret

__a20_test:
    ret
 
__a20_enabled:
    call a20_enabled
 
    ret

__a20_disabled:
    call a20_disabled
 
    ret

