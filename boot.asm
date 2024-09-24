[BITS 16]

mov ax, 0x7C0
mov ds, ax

cli
mov ss, ax
xor sp, sp
sti

mov cl, 0xD
mov bx, msg

l1:
    mov ah, 0xE
    mov al, byte [bx]
    int 0x10

    inc bx
    loop l1

loop:
    jmp loop

msg db "Hello, World!", 0

times  510 - ($ - $$) db 0
dw 0xaa55
