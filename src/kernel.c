#include "stdlib.h"
#define VIDEO 0xb8000

void print(int x, int y, char ch, char fg, char bg) {
    *(((short int*)VIDEO) + x + y * 80) = ch + (fg << 8) + (bg << 12);
}

void scroll() {
    kmemmove(((short int*)VIDEO), ((short int*)VIDEO + 80) , 80 * 48);
    for (int i = 0; i < 80; i++) {
        print(i, 24, 0, 0, 0);
    }
}

void vga_print_char(char symbol, int x, int y) {
    print(x, y, symbol, 0xb, 0);
}

void vga_print_str(char* str, int x, int y) {
    while(*str) {
        if (x >= 80) {
            y++;
            x = 0;
        }
        if (y >= 25) {
            scroll();
            y -= 1;
        }
        print(x++, y, *str++, 0xb, 0);
    }
}

void vga_clear_screen() {
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            print(i, j, 0, 0, 0);
        }
    }
    scroll();
}

void kmain() {
    vga_clear_screen();
    int x = 0;
    int y = 0;
    vga_print_str("long string", 0, 0);
    for(;;);
}
