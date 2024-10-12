[BITS 16]

; clear interrupt-enable flag
cli
cld

mov sp, 0x7C00 
mov ax, 0x7c0
mov ds, ax
mov ax, [gdt_code]
mov ax, [gdt_data]

;; this is the sacred code of omnissiah
;; do not touch it under no circumstances

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
    mov ax, ds
    mov si, es
    mov ds, si
    mov es, ax
    xor si, si
    xor di, di
    mov ax, 0x2400
WBL:
    movsw
    dec ax 
    jnz WBL
    mov ax, es 
    add ax, 0x480
    mov ds, ax
    dec bp
    jnz RCLP

;; sacred code of omnissiah has ended. you may touch further
mov ax, 0xf80
mov ds, ax
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:trampolin + 0xf800
[BITS 32]
trampolin:
    mov eax, DATA_SEG 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0xf800
    jmp CODE_SEG:0xfa00

; stop instruction execution
hlt

GLOBAL sayhi

sayhi:
    mov byte [es:0xb8000], 0
    mov byte [es:0xb8f9e],'i'
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
    dd gdt_start + 0xf800

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
