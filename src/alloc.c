#include "alloc.h"

#include "stdlib.h"

typedef struct {
    byte_t *current;
} allocator_context_t;

allocator_context_t alloc_cntxt;

void alloc_init() {
    alloc_cntxt.current = HEAP_BEGIN;
}

byte_t *kernel_malloc(u32 size) {
    if (alloc_cntxt.current + size > HEAP_END) {
        return 0;
    }
    byte_t *addr = alloc_cntxt.current;
    alloc_cntxt.current += size;
    return addr;
}

byte_t *kernel_calloc(u32 nmemb, u32 size) {
    byte_t *addr = kernel_malloc(nmemb * size);
    if (!addr) {
        return 0;
    }
    memset(addr, 0, nmemb);
    return addr;
}

byte_t *kernel_realloc(void *ptr, u32 size) {
    byte_t *new_addr = kernel_malloc(size);
    if (!new_addr) {
        return 0;
    }
    memmove(new_addr, ptr, size);
    return new_addr;
}
