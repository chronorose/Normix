#pragma once
#include "stdlib.h"
#include "types.h"

#define NROWS 25
#define NCOLS 80
#define BUFFER (0xb8000)
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
    int xstart, ystart, xend, yend;
} printer_t;

printer_t printer_init(unsigned char xstart, unsigned char ystart, unsigned char xend, unsigned char yend);
void global_printer_init();

void vga_print_char(printer_t *printer, char s);
void vga_print_string(printer_t *printer, char *str);
void vga_clear_screen(printer_t *printer);

void print(printer_t *printer, char *fmt, ...);

void advance(printer_t *printer);

void printi(printer_t *printer, int d, int base);
void newline(printer_t *printer);
void scroll(printer_t *printer);
