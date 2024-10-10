[BITS 16]

mov ax, 0x7C0
mov ds, ax

cli
xor ax, ax
mov ss, ax
mov sp, 0x7C00
sti
cld

; Printing 'Hello world!'

mov cl, 0xD
mov bx, msg

l1:
    mov ah, 0xE
    mov al, byte [bx]
    int 0x10

    inc bx
    loop l1

; Loading kernel

mov ax, [CODE_ADDR]
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

msg db "Hello, World!", 0
CODE_ADDR dw 0x2000

times  510 - ($ - $$) db 0
dw 0xaa55
