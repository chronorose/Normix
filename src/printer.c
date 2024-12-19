#include "printer.h"
printer_t global_printer;

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

printer_t printer_init(unsigned char xstart, unsigned char ystart, unsigned char xend, unsigned char yend) {
    printer_t new_printer;
    new_printer.xstart = xstart;
    new_printer.xend = xend;
    new_printer.ystart = ystart;
    new_printer.yend = yend;
    new_printer.x = xstart;
    new_printer.y = ystart;
    new_printer.frgrnd = DEF_FRGRND;
    new_printer.bckgrnd = DEF_BCKGRND;
    vga_clear_screen(&new_printer);
    return new_printer;
}

void global_printer_init() {
    global_printer.xstart = 0;
    global_printer.xend = NCOLS;
    global_printer.ystart = 0;
    global_printer.yend = NROWS;
    global_printer.frgrnd = DEF_FRGRND;
    global_printer.bckgrnd = DEF_BCKGRND;
    vga_clear_screen(&global_printer);
}

void scroll(printer_t *printer) {
    memmove((void *) XY_TO_ADDR(printer->xstart, printer->ystart),
            (void *) XY_TO_ADDR(printer->xstart, printer->ystart + 1),
            (printer->yend - printer->ystart) * (printer->xend - printer->xstart - 1) * 2);
    memset(XY_TO_ADDR(printer->xstart, printer->yend - 1), 0, (printer->yend - printer->ystart) * 2);
}

/*#define XY_TO_ADDR(x, y) ((u16 *) BUFFER + ((y) * 80 + (x)))*/

void advance(printer_t *printer) {
    (printer->x)++;
    if (printer->x >= printer->xend) {
        printer->x = printer->xstart;
        printer->y++;
    }
    if (printer->y >= printer->yend) {
        scroll(printer); // remake scroll.
        printer->y = printer->yend - 1;
    }
}

void vga_print_char(printer_t *printer, char s) {
    *(XY_TO_ADDR(printer->x + printer->xstart, printer->y + printer->ystart)) = SYMBOL(
        s,
        printer->bckgrnd,
        printer->frgrnd);
    advance(printer);
}

void vga_clear_screen(printer_t *printer) {
    memset(XY_TO_ADDR(printer->xstart, printer->ystart), 0,
           (printer->xend - printer->xstart) * (printer->yend - printer->ystart) * 2);
}

void vga_print_string(printer_t *printer, char *str) {
    while (*str) {
        vga_print_char(printer, *str);
        /*advance(x, y);*/
        str++;
    }
}

void print(printer_t *printer, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    while (*fmt) {
        char ch = *fmt;
        switch (ch) {
            case '%':
                switch (*(++fmt)) {
                    case 'd':
                        printi(printer, va_arg(ap, int), 10);
                        break;
                    case 'x':
                        printi(printer, va_arg(ap, int), 16);
                        break;
                    case 's':
                        vga_print_string(printer, va_arg(ap, char *));
                        break;
                    case 'c':
                        vga_print_char(printer, va_arg(ap, char));
                        advance(printer);
                        break;
                }
                break;
            case '\n':
                newline(printer);
                break;
            default:
                vga_print_char(printer, ch);
                advance(printer);
                break;
        }
        fmt++;
    }
    va_end(ap);
    return;
}

void printi(printer_t *printer, int value, int base) {
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
        vga_print_char(printer, bffr[j]);
        advance(printer);
    }
}

void newline(printer_t *printer) {
    printer->x = printer->xstart;
    printer->y++;
    if (printer->y >= printer->yend) {
        scroll(printer);
        printer->y = printer->yend - 1;
    }
}
