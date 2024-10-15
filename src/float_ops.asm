[BITS 32]

; this is helper file, calling various assembly instructions from C
GLOBAL sqrt
section .text
; takes an argument 
sqrt:
    fld dword [esp + 4]
    fsqrt
    ret

cos:
    fld dword [esp + 4]
    fcos
    ret

sin:
    fld dword [esp + 4]
    fsin
    ret
