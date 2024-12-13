#pragma once
#include "interrupts.h"
#include "types.h"

#define MAX(x, y) ((x) < (y) ? (y) : (x))

#define ASSERTION(expr) ((expr) || kernel_panic("assertion failed", 0))

typedef byte_t *va_list;
#define va_start(ap, parmN) (ap = (byte_t *) (&(parmN)) + sizeof(parmN))
#define va_arg(ap, T)                   \
    (ap += MAX(sizeof(u32), sizeof(T)), \
     *((T *) (ap - MAX(sizeof(u32), sizeof(T)))))
#define va_end(ap) ap = (void *) 0

void memset(void *dst, int c, int n);
void *memmove(void *dst, void *src, int n);
