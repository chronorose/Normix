global collect_ctx
global trampoline_0x20
global trampoline_0x2a
global get_eflags
global experiment
extern interrupt_handler

collect_ctx:
    push ds
    push es
    push fs
    push gs
    pusha
    push esp
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    call interrupt_handler
    add esp, 4
    popa
    pop gs
    pop fs
    pop es
    pop ds
    add esp, 8
    iretd

experiment:
    mov eax, 1
    mov ecx, 2
    mov edx, 3
    mov ebx, 4
    mov esi, 5
    mov edi, 6
    mov ebp, 7
    int 42
    ret

get_eflags:
    pushfd 
    pop eax
    ret
