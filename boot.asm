[BITS 16]

cli
mov sp, 0x7C0
mov ss, sp 

mov ah, 0xe
mov si, msg

loop:
    ss lodsb
    int 0x10
    test al, al
    jnz loop

hlt

msg db 'Hello, World!', 0

times  510 - ($-$$) db 0
dw 0xaa55

