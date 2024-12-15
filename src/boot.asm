[BITS 16]

jmp _start

gdt_start:
    dq 0x0
gdt_code:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x9A, 0xCF, 0x0
gdt_data:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x92, 0xCF, 0x0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd _gdt_start

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
lgdt [_gdt_descriptor]

mov eax, cr0
or eax, 1 
or eax, 3 
and ax, 0xFFFB
mov cr0, eax
mov eax, cr4
or ax, 3 << 9
mov cr4, eax

jmp CODE_SEG:_trampoline

[BITS 32]
trampoline:
    mov eax, DATA_SEG 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0xf800

prep_pd:
    mov esi, pdir1
    mov edi, ptable1
    mov ecx, 1024
.begin:
    mov eax, edi
    and eax, ~0xfff
    mov [esi], edi
    add esi, 0x4
    add edi, 0x1000
    loop .begin
.end:
    or byte [pdir1], flags
    or byte [pdir1 + 4], flags
id: ; identity map for 4.8 MiB of kernel
    mov ecx, 1024 + 128
    mov esi, ptable1
    xor edi, edi
.begin:
    mov eax, edi
    and eax, ~0xfff
    or eax, 0x7
    mov [esi], eax
    add esi, 0x4
    add edi, 0x1000
    loop .begin
hhk:
    or byte [pdir768], flags
    or byte [pdir768 + 4], flags

    mov ecx, 1024 + 128
    mov esi, ptable768
    xor edi, edi
.begin
    mov eax, edi
    and eax, ~0xfff
    or eax, 0x7
    mov [esi], eax
    add esi, 4
    add edi, 0x1000
    loop .begin

enable_paging:
    mov eax, pdir1
    mov cr3, eax
    mov eax, cr0
    or eax, (1 << 31)
    mov cr0, eax

call kmain

jmp $

pdir1 equ 0x80000
pdir768 equ (pdir1 + 768 * 4)

ptable1 equ 0x81000
ptable768 equ (ptable1 + 768 * 1024 * 4)

flags equ 0b111000000111
pse_flags equ flags | 0b10000111


CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_gdt_descriptor equ 0xf81a
_gdt_start equ  0xf802
_trampoline equ 0xf89c

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
