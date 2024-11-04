#include "stdlib.h"

void memset(void *dst, int c, int n) {
  while (n--)
    *((byte_t *)dst++) = c;
}
void *memmove(void *dst, void *src, int n) {
  if (!dst || !src) {
    return (void *)0;
  }
  char *cdst = (byte_t *)dst;
  char *csrc = (byte_t *)src;
  if (dst <= src) {
    while (n--) {
      *cdst++ = *csrc++;
    }
  } else {
    cdst += n - 1;
    csrc += n - 1;
    while (n--) {
      *cdst-- = *csrc--;
    }
  }
  return dst;
}
