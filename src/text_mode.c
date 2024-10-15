#include "text_mode.h"

#define VIDEO 0xb8000

typedef char* va_list;
#define va_start(xs, x) ({(xs) = (char*)(&x + 1);})
#define va_arg(xs, type) ({type l = (type)(*((type*)xs)); xs += sizeof(type); l;})

typedef struct {
    unsigned int x;
    unsigned int y;
} Cursor;

static Cursor cursor = (Cursor){0, 0};

static char ntoc[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static void set_cursor(int x, int y) {
    cursor.x = x;
    cursor.y = y;
}

static void inc_cursor() {
    cursor.x++;
    if (cursor.x >= 80) {
        cursor.x = 0;
        cursor.y++;
    }
    if (cursor.y >= 25) {
        scroll();
        cursor.y = 24;
    }
}

static void newline() {
    cursor.y++;
    cursor.x = 0;
    if (cursor.y >= 25) {
        scroll();
        cursor.y = 24;
    }
}

void fprint(char* fmt, ...) {
    va_list xs;
    xs = va_start(xs, fmt);
    while (*fmt) {
        char s = *fmt;
        switch (s) {
            case '%':
                if (!(*(fmt + 1))) {
                    vga_print_char(s);
                } 
                char spec = *(fmt + 1);
                switch (spec) {
                    case 'd':
                        {
                            vga_print_udec(va_arg(xs, int));
                            fmt++;
                        }
                        break;
                    case 'x':
                        {
                            vga_print_uhex(va_arg(xs, int));
                            fmt++;
                        }
                        break;
                    case 's':
                        {
                        vga_print_str(va_arg(xs, char*));
                        fmt++;
                        }
                        break;
                    case 'f':
                        vga_print_float(va_arg(xs, float), 2);
                        fmt++;
                        break;
                    case '%':
                        vga_print_char(s);
                        fmt++;
                        break;
                }
                break;
            case '\n':
                newline();
                break;
            default:
                vga_print_char(*fmt);
                break;
        }
        fmt++;
    }
}

void print_gl(int x, int y, char ch, char fg, char bg) {
    *(((short int*)VIDEO) + x + y * 80) = ch + (fg << 8) + (bg << 12);
}

void print(char ch, char fg, char bg) {
    *(((short int*)VIDEO) + cursor.x + cursor.y * 80) = ch + (fg << 8) + (bg << 12);
    inc_cursor();
}

void scroll() {
    kmemmove(((short int*)VIDEO), ((short int*)VIDEO + 80) , 80 * 48);
    for (int i = 0; i < 80; i++) {
        print_gl(i, 24, 0, 0, 0);
    }
}

static void vga_print_rev(char* str, unsigned int counter) {
    for (; counter > 0; --counter) {
        print(str[counter - 1], 0xb, 0);
    }
}

void vga_print_char(char symbol) {
    print(symbol, 0xb, 0);
}

void vga_print_uhex(unsigned int num) {
    char to_print[12] = {0}; 
    unsigned int counter = 0;
    while (num > 0) {
        to_print[counter++] = ntoc[num & 0xF];
        num >>= 4;
    }
    to_print[counter] = 0;
    vga_print_rev(to_print, counter);
}

void vga_print_udec(unsigned int num) {
    char to_print[12] = {0}; 
    unsigned int counter = 0;
    while (num > 0) {
        to_print[counter++] = ntoc[num % 10];
        num /= 10;
    }
    to_print[counter] = 0;
    vga_print_rev(to_print, counter);
}

void vga_print_float(float num, int precision) {
    int n = (int)num;
    vga_print_udec(n);
    vga_print_char('.');
    while (precision > 0) {
        num = (num - n) * 10;
        n = (int) num;
        vga_print_char(ntoc[n]);
        --precision;
    }
}


void vga_print_str(char* str) {
    while(*str) {
        print(*str++, 0xb, 0);
    }
}

void vga_clear_screen() {
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            print_gl(i, j, 0, 0, 0);
        }
    }
}

void init_printer() {
    vga_clear_screen();
    set_cursor(0, 0);
}
