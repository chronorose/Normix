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
        put(i, 19, 0);
    }
}

void render(char letter) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 7; j++) {
            if (font[letter][i][j]) {
                put(j, i, 0x2);
            }
        }
    }
}

void render_letter(char l) {
    render(l);
    cursor.x++;
    if (cursor.x >= 39) {
        cursor.y++;
        cursor.x = 0;
    }
    if (cursor.y >= 20) {
        gscroll();
        cursor.y = 19;
    }
}
