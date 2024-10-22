#include "stdlib.h"

void kmemmove(void* dest, const void* src, int count) {
    char* d = dest;
    const char* s = src;
    while (count) {
        *d++ = *s++;
        count--;
    }
}

void kmemset(void* s, int c, unsigned int n) {
    char* ch = s;
    for (int i = 0; i < n; i++) {
        *ch++ = c;
    }
}

int max(int a1, int a2) {
    return a1 > a2 ? a1 : a2;
}
