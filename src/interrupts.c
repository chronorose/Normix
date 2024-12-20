#include "interrupts.h"

#include "alloc.h"
#include "pic.h"
#include "printer.h"

extern void collect_ctx();
extern u32 get_eflags();
extern void _sti();
extern void _cli();

int glob = 0;
int glob1 = 0;

void kernel_panic(char *msg, int vector) {
    print(msg, vector);
    for (;;)
        ;
}

trampoline_no_err *tramp_gen_without_err_code(unsigned char ivector) {
    trampoline_no_err *tr = (trampoline_no_err *) kernel_malloc(sizeof(trampoline_no_err));
    tr->push = PUSH_BYTE_INSTRUCTION;
    tr->ivector = ivector;
    tr->j = JUMP_RELATIVE_4BYTES_INSTRUCTION;
    tr->handler_addr = -((unsigned int) tr - (unsigned int) collect_ctx) - sizeof(trampoline_no_err);
    return tr;
}

trampoline *tramp_gen(unsigned char ivector) {
    trampoline *tr = (trampoline *) kernel_malloc(sizeof(trampoline));
    tr->push = PUSH_BYTE_INSTRUCTION;
    tr->err_code = 0x0;
    tr->push2 = PUSH_BYTE_INSTRUCTION;
    tr->ivector = ivector;
    tr->j = JUMP_RELATIVE_4BYTES_INSTRUCTION;
    tr->handler_addr = -((unsigned int) tr - (unsigned int) collect_ctx) - sizeof(trampoline);
    return tr;
}

byte_t *generate_trampoline(unsigned char ivector) {
    byte_t *ret = 0x0;
    switch (ivector) {
        case 0xa:
        case 0xb:
        case 0xC:
        case 0xd:
        case 0xe:
        case 0x11:
        case 0x15:
        case 0x1D:
        case 0x1E:
            ret = (byte_t *) tramp_gen_without_err_code(ivector);
            break;
        default:
            ret = (byte_t *) tramp_gen(ivector);
            break;
    }
    return ret;
}

static void panic_handler(int vector) {
    kernel_panic("unhandled interrupt %x", vector);
}

void timer_handler(ctx_t *ctx) {
    print("TIMER\n");
    // print("0x20: %d\n", glob++);
    // for (int i = 0; i < 10000; i++) {
    // }
    _sti();
    pic_send_eoi(ctx->vector);
}

void page_fault_handler(ctx_t *ctx) {
    print("PAGE FAULT!\n");
    for (;;);
}

void interrupt_handler(ctx_t *ctx) {
    switch (ctx->vector) {
        case 0xE:
            page_fault_handler(ctx);
            break;
        case 0x20:
            timer_handler(ctx);
            break;
        case 0x2a:
            _sti();
            break;
        default:
            panic_handler(ctx->vector);
    }
}

extern void lidt_load(void *ptr);

void idt_setup() {
    u32 idt_sz = IDT_SIZE;
    gate_descriptor_t *idt =
        (gate_descriptor_t *) kernel_malloc(idt_sz * sizeof(gate_descriptor_t));

    if (!idt) {
        print("Not enough memory to allocate idt\n");
        return;
    }

    for (int i = 0; i < idt_sz; i++) {
        gate_descriptor_t gd;
        byte_t *handler = (byte_t *) generate_trampoline(i);
        gd.offset_low = (u16) handler;
        gd.segselector = 0x8;
        gd.nargs = 0x0;
        gd.unused0 = 0x0;
        gd.gate_type = (i < 0x20) ? TRAP_GATE : INTERRUPT_GATE;
        gd.unused1 = 0x0;
        gd.dpl = 0x0;
        gd.existance_bit = 1;
        gd.offset_high = (u16) (((u32) handler) >> 16);
        idt[i] = gd;
    }
    idt_descriptor_t idtd = {.idt_sz = idt_sz * sizeof(gate_descriptor_t) - 1,
                             .idt_addr = (u32) idt};
    lidt_load(&idtd);
}

void ctx_print(ctx_t *ctx) {
    char *msg = "Kernel panic: unhandled interrupt %x, interrupted process context:\neax = %x, ecx = %x, edx = %x, ebx = %x, esp = %x, ebp = %x, esi = %x, edi = %x, ds = %x, es = %x, fs = %x, gs = %x, cs = %x, eip = %x\neflags (interrupted) = %x eflags (current) = %x, error code = %x";
    print(msg, ctx->vector, ctx->eax, ctx->ecx, ctx->edx, ctx->ebx, ctx->esp, ctx->ebp, ctx->esi, ctx->edi, ctx->ds, ctx->es, ctx->fs, ctx->gs, ctx->cs, ctx->eip, ctx->eflags, get_eflags(), ctx->err_code);
}
