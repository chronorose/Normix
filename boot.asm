[BITS 16]

mov ax, 0x7C0
mov ds, ax

cli
mov ss, ax
xor sp, sp
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

xor cx, cx

mov ax, [CODE_ADDR]
mov es, ax

mov ax, [BUFF_ADDR]
mov ds, ax

cloop:
    xor dx, dx
    mov bx, 1
    push cx
    hloop:
        push dx

        mov ah, 0x2
        mov al, 18
        mov ch, cl ; moving cylinder iterator in ch
        mov cl, 1

        mov dh, dl

        call disk_to_buffer

        pop dx
        
        add bx, 0x2400
        inc dx
        cmp dx, 2
        jl hloop

    mov cx, 0x2400
    mov si, 1
    call buffer_to_cs

    pop cx

    inc cx
    cmp cx, 21
    jl cloop

; -------------------

; Loading remaining 6 KB

mov ah, 0x2
mov al, 12
mov ch, 21
mov cl, 1
xor dh, dh
call disk_to_buffer

mov cx, 0xC00
mov si, 1
call buffer_to_cs

xor bp, bp
;mov cx, 0x1800
mov cx, 0x200
mov bx, 0xe800

mov ax, 0x7000
mov es, ax

xor ax, ax
l3:
    mov ah, 0xE
    mov al, byte [es:bx]
    int 0x10

    ;mov al, byte [es:bx]
    ;add bp, ax

    inc bx
    loop l3

loop:
    jmp loop

msg db "Hello, World!", 0

CODE_ADDR dw 0x2000
BUFF_ADDR dw 0x1000

xchg_ds_es:
    push si
    push di

    mov si, es
    mov di, ds
    xchg si, di
    mov es, si
    mov ds, di

    pop di
    pop si
    ret

buffer_to_cs:
    _loop:
        movsw

        cmp di, 0
        jnz skip
        mov ax, es
        add ax, 0x1000
        mov es, ax
        
        skip:
            loop _loop
    ret

disk_to_buffer:
    call xchg_ds_es
    int 0x13
    call xchg_ds_es
    ret

times  510 - ($ - $$) db 0
dw 0xaa55
