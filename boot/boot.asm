[BITS 16]

global _start
extern kmain

section .text
_start:
; clear interrupt-enable flag
cli
cld

mov sp, 0x7C00 

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

init_video:
    fninit
    mov ah, 0x0
%ifdef TEXT
    mov al, 0x3 ; this is where either 0x3(text mode) or 0x13(graphics mode) go
%endif
%ifdef GRAPHICS
    mov al, 0x13
%endif
    int 0x10


;; sacred code of omnissiah has ended. you may touch further
xor ax, ax
mov ds, ax
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1 
;or eax, 3 
;and ax, 0xFFFB
mov cr0, eax
;mov eax, cr4
;or ax, 3 << 9
;mov cr4, eax

jmp CODE_SEG:trampolin ;+ 0xf800
[BITS 32]
trampolin:
    mov eax, DATA_SEG 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0xf800
    call kmain

jmp $

gdt_start:
    dq 0x0
gdt_code:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x9A, 0xCF, 0x0
gdt_data:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x92, 0xCF, 0x0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start ;+ 0xf800

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
