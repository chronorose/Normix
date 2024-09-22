[BITS 16]

; clear interrupt-enable flag
cli
mov ax, 0x7C0
mov ss, ax
xor sp, sp
mov ah, 0xe
mov si, msg
cld

loop:
  ; read byte from ss:si into al, si++
  ss lodsb
  ; ah = 0xe (display char), al = char
  int 0x10
  ; subtracting and setting flags
  test al, al
  jnz loop

; stop instruction execution
hlt

msg:
  db 'Hello, World!', 0

; generate zero bytes to size 510
times  510 - ($ - $$) db 0
dw 0xaa55
