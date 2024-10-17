#ifdef TEXT
#include "text_mode.h"

void text_mode() {
    vga_clear_screen();
    /*for (int i = 0; i < 30; i++) {*/
    /*    for (int j = 0; j < i; j++) {*/
    /*        fprint(" ");*/
    /*    }*/
    /*    fprint("%d\n", i);*/
    /*}*/
    vga_print_float(sqrt(100.), 2);
    /*for (int i = 0; i < 1200; i++) {*/
    /*    vga_print_str(" ");*/
    /*    vga_print_udec(i);*/
    /*}*/
    /*int num = (int)sqrt(100);*/
    /*vga_print_float(sqrt(36.), 2);*/
    /*vga_print_float(sqrt(100), 2);*/
}
#endif

#ifdef GRAPHICS 
#include "graphics_mode.h"
#include "font_render.h"

void graphics_mode() {
    render('a');
    /*fill_rect(10, 10, 100, 100, 3);*/

    /*for (int y = 0; y < 200; y += 2) {*/
    /*    for (int x = 0; x < 320; x += 2) {*/
    /*        put(x, y, 13);*/
    /*    }*/
    /*}*/
}
#endif

void kmain() {
#ifdef TEXT
    text_mode();
#endif
#ifdef GRAPHICS
    graphics_mode();
#endif
    for(;;);
}
