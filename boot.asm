[BITS 16]

cli; clear interrupt-enable flag
cld; clear derection flag, if df = 0 string ooperations increment

mov sp, 0x7C00 

read_cylinder:
    mov ax, 0xF80
    mov ds, ax; data segment
    mov bp, 25; count of cylinders
    xor cx, cx; cylinder and sector
    mov ss, cx
    xor dh, dh; number of head
RCLP:
    mov ax, 0x7E0
    mov es, ax; buffer es::bx
    xor bx, bx
read_sectors:
    mov al, 0x12; count of reading sectors
    mov ah, 0x2; function - read sectors from driver
    mov cl, 0x1; number of sector
    int 0x13
    jc read_sectors; c-flag if was error
    add bx, 0x2400
    xor dh, 1; next head
    jnz read_sectors; second iteration if dh = 0
    inc ch; next number of cylinder
write_buf:
    call swap_segments; swap ds and es
    xor si, si
    xor di, di
    mov ax, 0x2400
.WBL:
    movsw; move word(2 bytes) from address ds:si to es:di (from buffer to data)
    dec ax 
    jnz .WBL
    mov ax, es 
    add ax, 0x480
    mov ds, ax; shift by 18 kb
    dec bp
    jnz RCLP

hlt; stop instruction execution

swap_segments:; swap ds and es
    mov ax, ds
    mov si, es
    mov ds, si
    mov es, ax
    ret

msg db 'Hello, World!', 0

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
