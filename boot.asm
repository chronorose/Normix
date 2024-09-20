[BITS 16]

cli
mov ax, 0x7C0
mov ss, ax 
xor sp, sp
mov ah, 0xe
mov si, msg
cld

loop:
    ss lodsb
    int 0x10
    test al, al
    jnz loop

hlt

msg db 'Hello, World!', 0
times  510 - ($-$$) db 0
dw 0xaa55

