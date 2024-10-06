[BITS 16]

cli
mov ax, 0x7C0
mov ss, ax 
;mov ds, ax
xor sp, sp
xor al, al
mov ah, dl
call read_cylinder

cld
mov ah, 0xe
mov si, msg 

loop:
    es lodsb
    int 0x10
    test al, al
    jnz loop

hlt
load_kernel:
    push bp
    mov bp, 18 
    mov cx, 0x7E0 
    mov ax, 0x1000
.LKL:
    push dx
    mov ah, dl
    mov al, bp ; cylinder number
    call read_cylinder
    inc bp

; ds should point at 0x7E0
; es should point at where the copy should happen
; for example if we want to copy full cylinder from buffer to 0x10000
; then ds should be at 0x7E0, es should be at 0x1000.
; amount of bytes we are supposed to write should come as argument.
write_from_buf:
    pop dx
    pop cx
    push si 
    push di
    xor si, si
    xor di, di
.WFBL:
    movsb
    dec cx
    test cx, cx
    jnz .WFBL
    pop di
    pop si
    push dx
    ret
; al has to have cylinder number
; ah has to have drive number 
read_cylinder:
    push bx
    xor bx, bx
    mov ch, al
    mov dl, ah
    mov ax, 0x7E0
    mov es, ax
    mov al, 0x12
    mov ah, 0x2
    xor dh, dh
    mov cl, 1
.RCL:
    int 0x13
    add bx, 0x2400
    xor dh, 0x1
    jnz .RCL
    pop bx
    ret

msg db 'Hello, World!', 0
times  510 - ($-$$) db 0
dw 0xaa55
