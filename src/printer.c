#include "printer.h"
printer_t printer;

const char itoc[] = {
    [0] = '0',
    [1] = '1',
    [2] = '2',
    [3] = '3',
    [4] = '4',
    [5] = '5',
    [6] = '6',
    [7] = '7',
    [8] = '8',
    [9] = '9',
    [10] = 'a',
    [11] = 'b',
    [12] = 'c',
    [13] = 'd',
    [14] = 'e',
    [15] = 'f',
};

void printer_init(void) {
    printer.x = 0;
    printer.y = 0;
    printer.frgrnd = DEF_FRGRND;
    printer.bckgrnd = DEF_BCKGRND;
    vga_clear_screen();
}

void scroll(void) {
    memmove((void *) BUFFER, (void *) ((u16 *) BUFFER + NCOLS), NCOLS * (NROWS - 1) * 2);
    memset(XY_TO_ADDR(0, NROWS - 1), 0, NCOLS * 2);
}

void advance(int *x, int *y) {
    (*x)++;
    if (*x >= NCOLS) {
        *x = 0;
        (*y)++;
    }
    if (*y >= NROWS) {
        scroll();
        *y = NROWS - 1;
    }
}

void vga_print_char(char s, int x, int y) {
    *(XY_TO_ADDR(x, y)) = SYMBOL(
        s,
        printer.bckgrnd,
        printer.frgrnd);
}

void vga_clear_screen(void) {
    memset((void *) BUFFER, 0, NCOLS * NROWS * 2);
}

void vga_print_string(char *str, int *x, int *y) {
    while (*str) {
        vga_print_char(*str, *x, *y);
        advance(x, y);
        str++;
    }
}

void print(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    while (*fmt) {
        char ch = *fmt;
        switch (ch) {
            case '%':
                switch (*(++fmt)) {
                    case 'd':
                        printi(va_arg(ap, int), 10);
                        break;
                    case 'x':
                        printi(va_arg(ap, int), 16);
                        break;
                    case 's':
                        vga_print_string(va_arg(ap, char *), &printer.x, &printer.y);
                        break;
                    case 'c':
                        vga_print_char(va_arg(ap, char), printer.x, printer.y);
                        advance(&printer.x, &printer.y);
                        break;
                }
                break;
            case '\n':
                newline();
                break;
            default:
                vga_print_char(ch, printer.x, printer.y);
                advance(&printer.x, &printer.y);
                break;
        }
        fmt++;
    }
    va_end(ap);
    return;
}

void printi(int value, int base) {
    char bffr[12] = {0};
    int i = 11;
    int neg = 0;
    if (value < 0) {
        neg = 1;
        value = -value;
    }

    do {
        bffr[i--] = itoc[value % base];
    } while (value /= base);

    if (base == 16) {
        bffr[i--] = 'x';
        bffr[i--] = '0';
    }
    if (neg) {
        bffr[i--] = '-';
    }
    for (int j = i + 1; j < 12; j++) {
        vga_print_char(bffr[j], printer.x, printer.y);
        advance(&printer.x, &printer.y);
    }
}

void newline() {
    printer.x = 0;
    printer.y++;
    if (printer.y >= NROWS) {
        scroll();
        printer.y = NROWS - 1;
    }
}
