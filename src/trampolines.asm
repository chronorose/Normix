global collect_ctx
global trampoline_0x20
extern interrupt_handler

trampoline_0x20:
    push 0x00
    push 0x20
    jmp collect_ctx

collect_ctx:
    push ds
    push es
    push fs
    push gs
    pusha
    push esp
    call interrupt_handler
