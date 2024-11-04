#ifndef __NORMIX_GRAPHICS__
#define __NORMIX_GRAPHICS__

#include "stdlib.h"

#define VIDEO 0xa0000

void put(int x, int y, unsigned char color);

void rect(int x1, int y1, int x2, int y2, unsigned char color);
void fill_rect(int x1, int y1, int x2, int y2, unsigned char color);

#endif
