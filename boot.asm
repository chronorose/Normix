[BITS 16]

mov ax, 0x7C0
mov es, ax
mov ds, ax
mov bp, msg

mov ax, 0x7
int 0x10

mov ah, 0x13
mov bl, 0x1 
mov al, 1
mov cx, [msg_length]

int 0x10

hlt

msg db 'Hello, World!'
msg_length dw $-msg
msg_x dw 0
msg_y dw 0

times  510 - ($-$$) db 0
dw 0xaa55
