#include "stdlib.h"
void memset(void *dst, int c, int n) {
    while (n--)
        *((char*)dst++) = c;
}
void *memmove(void *dst, void *src, int n) {
    // TODO: make overlapping memory areas
    for (int i = 0; i < n; i++) {
        *((char*)dst + i) = *((char*)src + i);
    }
    return dst;
}
