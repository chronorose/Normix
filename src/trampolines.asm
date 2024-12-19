global collect_ctx
global get_eflags
global experiment
global do_paging
extern interrupt_handler

do_paging:
  mov eax, [esp + 4]  ; address of page directory
  mov cr3, eax   
  mov eax, cr0
  or eax, (1 << 31)
  mov cr0, eax
  ret

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

global syscall_test
syscall_test:
  mov eax, 69
  int 0x33
  ret

get_eflags:
    pushfd 
    pop eax
    ret
