[BITS 16]

mov ah, 0xE
mov al, 65
int 0x10

loop:
    mov ax, 420 
    jmp loop
    

times 510 - ($ - $$) db 0
dw 0xAA55
