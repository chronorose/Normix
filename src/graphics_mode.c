#include "graphics_mode.h"

#define VIDEO 0xa0000

volatile unsigned char* video = (unsigned char*) VIDEO;

void put(int x, int y, unsigned char color) {
    video[x + y * 320] = color;
}

void rect(int x1, int y1, int x2, int y2, unsigned char color) {
    if (x1 > x2) SWAP(x1, x2, int);
    if (y1 > y2) SWAP(y1, y2, int);
    for (int i = x1; i < x2; i++) put(i, y1, color);
    for (int i = x1; i < x2; i++) put(i, y2, color);
    for (int i = y1; i < y2; i++) put(x1, i, color);
    for (int i = y1; i < y2; i++) put(x2, i, color);
}

void fill_rect(int x1, int y1, int x2, int y2, unsigned char color) {
    if (x1 > x2) SWAP(x1, x2, int);
    if (y1 > y2) SWAP(y1, y2, int);
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            put(j, i, color);
        }
    }
}

int sq(int x) {
    return x * x;
}

float distance(int x1, int y1, int x2, int y2) {
    return sqrt(sq((x2 - x1)) + sq((y2 - y1)));
}

void line(int x1, int y1, int x2, int y2, unsigned char color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int D = 2 * dy - dx;
    int y = y1;
    for (int i = x1; i < x2; i++) {
        /*put(i, y);*/
    }
}
