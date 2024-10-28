#pragma once
typedef void *va_list;
#define va_start(ap, parmN) (ap = (char *)&(parmN) + sizeof(parmN))
#define va_arg(ap, T) (ap += sizeof(T), *((T *)(ap - sizeof(T))))
#define va_end(ap) ap = (void *)0
void memset(void *dst, int c, int n);
void *memmove(void *dst, void *src, int n);
