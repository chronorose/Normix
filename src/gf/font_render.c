#include "graphics_mode.h"
#include "stdlib.h"

extern char font[128][9][7];

typedef struct {
    unsigned short x;
    unsigned short y;
} Cursor;

Cursor cursor = {0, 0};

void gscroll() {
    kmemmove(((short int*)VIDEO), ((short int*)VIDEO + 40), 40 * 18);
    for (int i = 0; i < 20; i++) {
        put(i, 190, 0);
    }
}

void lfcheck() {
    if (cursor.x + 7 >= 320) {
        cursor.y += 9;
        cursor.x = 0;
    }
    if (cursor.y >= 200) {
        gscroll();
        cursor.y = 190;
    }
}

void inc_cursor() {
    cursor.x += 7;
    lfcheck();
}

void render(char letter) {
    lfcheck();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 7; j++) {
            if (font[letter][i][j]) {
                put(cursor.x + j, cursor.y + i, 0x3);
            }
        }
    }
    inc_cursor();
}

void render_letter(char l) {
    render(l);
}
