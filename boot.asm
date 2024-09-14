[BITS 16]

cli
mov ax, 0x7C0
mov sp, ax 
mov es, ax
mov ds, ax
xor ax, ax
mov ss, ax
mov bp, msg
sti

mov ah, 0x13
mov bl, 0x1
mov al, 1
mov cx, msg_length
mov dh, 16 
mov dl, 0 
int 0x10

loop:
    jmp loop

msg db 'Hello, World!'
msg_length equ $-msg

times  510 - ($-$$) db 0
dw 0xaa55
