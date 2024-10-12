[BITS 16]

cli; clear interrupt-enable flag
cld; clear derection flag, if df = 0 string ooperations increment

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
WBL:
    movsw; move word(2 bytes) from address ds:si to es:di (from buffer to data)
    dec ax 
    jnz WBL
    mov ax, es 
    add ax, 0x480
    mov ds, ax; shift by 18 kb
    dec bp
    jnz RCLP

cli
mov ax, 0x7C0
mov ds, ax
lgdt [gdt_descriptor]

mov eax, cr0
or al, 1
mov cr0, eax

jmp CODE_SEG:protected_mode_trampoline + 0x7C00

[BITS 32]

protected_mode_trampoline:

    mov ax, DATA_SEG
    mov ds, ax
    mov ss ,ax
    mov es ,ax
    mov fs ,ax
    mov gs ,ax

    mov esp, 0xFA00
    jmp CODE_SEG:0xFA00

swap_segments:; swap ds and es
    mov ax, ds
    mov si, es
    mov ds, si
    mov es, ax
    ret

gdt_start:
    dq 0x0
    gdt_code:
        db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x9A, 0xCF, 0x0
    gdt_data:
        db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x92, 0xCF, 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start + 0xF800

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
times  510 - ($-$$) db 0
dw 0xAA55
