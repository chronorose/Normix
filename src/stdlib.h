#pragma once
typedef void* va_list;
#define va_start(ap, parmN) (ap = &parmN)
#define va_arg(ap, T) (ap += sizeof(T), *((T*)ap))
#define va_end(ap) ap = (void*)0
void memset(void *dst, int c, int n);
void *memmove(void *dst, void *src, int n);
