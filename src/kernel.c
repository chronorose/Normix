#ifdef TEXT
#include "text_mode.h"
#include "idt.h"

extern void say(void);
extern void inter(void);

void text_mode() {
    error("cringe");
    fprint("%d %d %f %s", 12, 13, (float)34.3, "hoi");
    vga_clear_screen();
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i; j++) {
            fprint(" ");
        }
        fprint("%d\n", i);
    }
    vga_clear_screen();
    gen_idt();
    /*inter();*/
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i; j++) {
            fprint(" ");
        }
        fprint("%d\n", i);
    }
}
#endif

#ifdef GRAPHICS 
#include "graphics_mode.h"
#include "font_render.h"

void graphics_mode() {
    for(int i = 0; i < 60; i++) {
        render('a');
    }
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
