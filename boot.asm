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

mov ax, [CODE_ADDR]
mov es, ax

mov ax, [BUFF_ADDR]
mov ds, ax

xor cx, cx
xor di, di
xor bp, bp
cloop:

    push ax
    push cx
    mov ah, 0xE
    add cl, 0x30
    mov al, cl
    int 0x10
    pop cx
    pop ax

    mov bx, 1
    xor dh, dh
    push cx ; ?
    write_head:
        push cx
        mov ah, 0x2
        mov al, 18
        mov ch, cl
        mov cl, 1
        xor dh, 0
        call disk_to_buffer
        pop cx

        push cx
        push dx
        mov dx, 0x2400 ; nbytes
        mov si, 1
        call buffer_to_cs
        pop dx
        pop cx

        ;add bx, 0x2400
        inc bp
        xor dh, 1
        jnz write_head
    pop cx ; ?
    inc cx
    cmp cx, 49
    jl cloop

; -------------------

;jmp $
; pmemsave 0x10001 0x6E000 out.mem
; Loading remaining 7 KB

mov ah, 0x2
mov al, 12
mov ch, 21
mov cl, 1
xor dh, dh
mov bx, 1
call disk_to_buffer

mov cx, 0xC00
mov si, 1
call buffer_to_cs

xor bp, bp
mov cx, 1024
mov bx, 0xe800

mov ax, 0x7000
mov es, ax

xor ax, ax
l3:
    mov ah, 0xE
    mov al, byte [es:bx]
    int 0x10

    xor ax, ax
    mov al, byte [es:bx]
    add bp, ax

    inc bx
    loop l3

loop:
    jmp loop

msg db "Hello, World!", 0

CODE_ADDR dw 0x1000
BUFF_ADDR dw 0x7E0

xchg_ds_es:
    mov dx, es
    mov cx, ds
    mov es, cx
    mov ds, dx
    ret

buffer_to_cs:
    mov cx, dx
    shr cx, 1
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
    push dx
    push cx
    call xchg_ds_es
    pop cx
    pop dx

    int 0x13

    push dx
    push cx
    call xchg_ds_es
    pop cx
    pop dx
    ret

times  510 - ($ - $$) db 0
dw 0xaa55
