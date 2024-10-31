#include "stdlib.h"
void memset(void *dst, int c, int n) {
    while (n--)
        *((byte_t*)dst++) = c;
}
void *memmove(void *dst, void *src, int n) {
    for (int i = 0; i < n; i++) {
        *((byte_t*)dst + i) = *((byte_t*)src + i);
    }
    return dst;
}
