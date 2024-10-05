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

; buffer location starts at (linear) 0x801
mov ax, [BUFF_LOCATION]
mov es, ax
mov bx, 1

; new code starts at (linear) 0x20000
mov ax, [CODE_LOCATION]
mov ds, ax
xor di, di

xor si, si ; loop counter

xor sp, sp

; cylinders loop
c_loop:
    mov bx, 1

    ; write (c, 0, 1)
    mov ah, 0x2
    mov al, 18  ; sectors

    mov cx, si  ; something like 'mov ch, si'
    shl cx, 8
    mov cl, 1

    xor dh, dh
    int 0x13

    ; advance buffer offset on 9 KB
    add bx, 0x2400
    ;add bx, 0x4800

    ; write (c, 1, 1) TODO: remove copypaste
    mov ah, 0x2
    mov al, 18  ; sectors

    mov cx, si  ; something like 'mov ch, si'
    shl cx, 8
    mov cl, 1

    inc dh
    int 0x13

    ; restore buffer offset
    mov bx, 1
    ; mov cx, 0x2400
    mov cx, 0x1200
    cpy_frm_bfr:
        mov word ax, [es:bx]
        mov word [ds:di], ax

        add bx, 2
        add di, 2

        jnz skip

        advance_ds:
            mov ax, ds
            add ax, 0x1000
            mov ds, ax
            inc sp ; for debugging purposes

        skip:
            loop cpy_frm_bfr

    inc si
    cmp si, 22  ; 21 - number of cylinders to cover 384 Kbytes
    ;cmp si, 21  ; 21 - number of cylinders to cover 384 Kbytes
    jne c_loop

mov ax, [CODE_LOCATION]
mov ds, ax

xor bp, bp
mov cx, 1024
mov bx, 512 ; offset

xor ax, ax
l3:
    mov ah, 0xE
    mov al, byte [ds:bx]
    add bp, ax
    int 0x10

    mov ah, byte [ds:bx]
    add bp, ax

    inc bx
    loop l3

loop:
    jmp loop

msg db "Hello, World!", 0
CODE_LOCATION dw 0x2000
BUFF_LOCATION dw 0x80

times  510 - ($ - $$) db 0
dw 0xaa55
