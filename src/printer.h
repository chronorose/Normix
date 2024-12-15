#pragma once
#include "stdlib.h"
#include "types.h"

#define NROWS 25
#define NCOLS 80
#define BUFFER (0xc00b8000)
#define XY_TO_ADDR(x, y) ((u16 *) BUFFER + ((y) * 80 + (x)))
#define DEF_FRGRND (WHITE)
#define DEF_BCKGRND (BLACK)

#define SYMBOL(ch, b, f) ((b << 12) | (f << 8) | (ch))

typedef enum {
    BLACK = 0x0,
    GREEN = 0x2,
    CYAN = 0x3,
    WHITE = 0xF,
} color_t;

typedef struct {
    int x, y;
    char frgrnd, bckgrnd;
} printer_t;

void printer_init(void);

void vga_print_char(char s, int x, int y);
void vga_print_string(char *str, int *x, int *y);
void vga_clear_screen(void);

void print(char *fmt, ...);

void advance(int *x, int *y);

void printi(int d, int base);
void printu(u32 d, int base);
void newline();
void scroll();
