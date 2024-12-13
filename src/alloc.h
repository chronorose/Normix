#pragma once

#include "types.h"

#define HEAP_BEGIN ((byte_t *) 0x480000)
#define HEAP_END ((byte_t *) 0x1000000)

void alloc_init();
byte_t *kernel_malloc(u32 size);
byte_t *kernel_calloc(u32 nmemb, u32 size);
byte_t *kernel_realloc(void *ptr, u32 size);
byte_t *kernel_malloc_aligned(u32 size, int align);
