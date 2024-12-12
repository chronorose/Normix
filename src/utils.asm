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
