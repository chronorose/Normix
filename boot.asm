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
; mov di, 1

xor bp, bp ; loop counter
; xor si, si
xor di, di

; cylinders loop
c_loop:
    ; head loop
    h_loop:
        mov ah, 0x2
        mov al, 18  ; sectors

        mov cx, bp  ; something like 'mov ch, bp'
        shl cx, 8
        mov cl, 1

        push dx

        shl dx, 8
        ; mov dh, 0
        int 0x13

        pop dx

        ; xchg es, ds
        mov ax, es
        mov cx, ds
        mov ds, ax
        mov es, cx

        ; mov di, 1
        mov si, 1
        
        ; 0x1200 = 4608
        mov cx, 0x1200
        ; to copy 9 KB from buffer to dst 
        ; we need to movsw 9 * 1024 / 2 times
        cpy_frm_bffr:
            movsw
            loop cpy_frm_bffr

        ; xchg es, ds
        mov ax, es
        mov cx, ds
        mov ds, ax
        mov es, cx

        inc dx
        cmp dx, 2
        jl h_loop

    inc bp
    cmp bp, 21  ; 21 - number of cylinders to cover 384 Kbytes
    ;jne c_loop

xor bp, bp
mov cx, 512
mov bx, 1024 ; offset

l3:
    mov ah, 0xE
    mov al, byte [ds:bx]
    ;add bp, ax
    int 0x10

    inc bx
    loop l3

loop:
    jmp loop

msg db "Hello, World!", 0
CODE_LOCATION dw 0x2000
BUFF_LOCATION dw 0x80

times  510 - ($ - $$) db 0
dw 0xaa55
