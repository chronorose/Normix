[BITS 16]

cli
cld

mov sp, 0x7C00 

read_cylinder:
    mov ax, 0xF80
    mov ds, ax
    mov bp, 25
    xor cx, cx
    mov ss, cx
    xor dh, dh
RCLP:
    mov ax, 0x7E0
    mov es, ax
    xor bx, bx
read_sectors:
    mov al, 0x12 
    mov ah, 0x2
    mov cl, 0x1
    int 0x13 
    jc read_sectors
    add bx, 0x2400
    xor dh, 1
    jnz read_sectors
    inc ch
write_buf:
    call swap_segments
    xor si, si
    xor di, di
    mov ax, 0x2400
.WBL:
    movsw
    dec ax 
    jnz .WBL
    mov ax, es 
    add ax, 0x480
    mov ds, ax
    dec bp
    jnz RCLP

hlt

swap_segments:
    mov ax, ds
    mov si, es
    mov ds, si
    mov es, ax
    ret

msg db 'Hello, World!', 0
times  510 - ($-$$) db 0
dw 0xaa55
