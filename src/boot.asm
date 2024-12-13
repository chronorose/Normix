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
    dd 0xf802

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
lgdt [0xf81a]
;lgdt [gdt_descriptor]

mov eax, cr4
or ax, 3 << 9 ; sse flags
mov cr4, eax

mov eax, cr0
or eax, 3 
;and ax, 0xFFFB ; enable fpu
mov cr0, eax

jmp CODE_SEG:0xf895
;jmp CODE_SEG:trampolin

[BITS 32]

trampolin:
    mov eax, DATA_SEG 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0xf800
; somewhere here we should start initializing our mr. paging.

mov ecx, 0 ; pages index.
mov ebx, tables ; tables address.
mov esi, 1024
mov edx, 0
fill_pd:
  mov eax, ebx 
  or eax, 7
  mov [directory + edx * 4], eax
  inc edx
  mov edi, 1024 
fill_pt:
  mov eax, ecx 
  shl eax, 12
  or eax, 7
  mov [ebx], eax
  inc ecx
  add ebx, 4
  dec edi
  jnz fill_pt
  dec esi
  jnz fill_pd

  mov ebx, tables
  add ebx, 0x300000
  mov ecx, 15
  mov edi, 2048
fill_shittable:
  mov eax, ecx
  shl eax, 12
  or eax, 7
  mov [ebx], eax
  inc ecx
  add ebx, 4
  dec edi
  jnz fill_shittable

;  mov edx, 0 ; number of directory we want to map our kernel into
;relocate_first_table:


;  mov ebx, tables
;  mov ecx, 15 ; we turn off first 15 pages. 
;  mov edx, 0
;turn_off:
;  mov eax, edx
;  shl eax, 12
;  or eax, 7
;  xor eax, 1
;  mov [ebx], eax
;  add ebx, 4
;  inc edx
;  dec ecx
;  jnz turn_off



funny_things:
  mov eax, directory
  mov cr3, eax
  mov eax, cr0
  or eax, (1 << 31)
  mov cr0, eax

  call kmain
jmp $

global lidt_load
lidt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

global inter
inter:
    int 0x0 
    ret

global _sti
_sti:
    sti
    ret

global _cli
_cli:
    cli
    ret

global _inb
_inb:
    mov dx, word [esp + 4]
    in al, dx
    ret

global _outb
_outb:
    mov al, byte [esp + 8]
    mov dx, word [esp + 4]
    out dx, al
    ret


directory equ 0x80000
tables equ 0x82000

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
