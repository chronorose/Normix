#include "process.h"

typedef struct process_t process_t;

static int nextpid = 1;

void proc_init(process_t *p, void *startup) {
    byte_t *stack = (byte_t *) kernel_malloc_aligned(PROC_STACK_SZ + 1, 16);
    if (!stack) {
        kernel_panic("Not enough memory to allocate\n", 0x0);
    }
    ctx_t *ctx = (ctx_t *) kernel_calloc(1, sizeof(ctx_t));
    if (!ctx) {
        kernel_panic("Not enough memory to allocate\n", 0x0);
    }
    ctx->cs = 0x8;
    ctx->ds = 0x10;
    ctx->eip = (u32) startup;
    ctx->esp = ((u32) stack) + PROC_STACK_SZ;
    p->ctx = ctx;
    p->stack_begin = (byte_t *) ((u32) stack);
}
