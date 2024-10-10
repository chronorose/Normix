[BITS 16]

cli
xor ax, ax
mov ss, ax
mov sp, 0x7C00
sti
cld

; Loading kernel

mov ax, 0x2000
mov es, ax

mov si, 6
xor bx, bx
xor dh, dh
mov cl, 0x1
mov ah, 0x2
mov al, 0x1

l2:
    push ax
    int 0x13
    pop ax

    add bx, 0x200
    jnc skip
    mov di, es
    add di, 0x1000
    mov es, di
    dec si
    jz end
skip:
    inc cl
    cmp cl, 19
    jl l2
    mov cl, 1
    xor dh, 1
    jnz l2
    inc ch
    jmp l2
end:

loop:
    jmp loop

times  510 - ($ - $$) db 0
dw 0xaa55
