#include "alloc.h"
#include "interrupts.h"
#include "pic.h"
#include "printer.h"

extern printer_t printer;
extern void inter();
extern void _sti();
extern void _cli();
extern void experiment();
extern void collect_ctx();

void another_task() {
    for (int i = 0; i < 100000; i++) {
    }
    print("another task\n");
}

void turn_off_pages() {
    u32 *pd = (u32 *) 0xc0080000;
    u32 *pt = (u32 *) 0xc0081000;
    for (u32 pti = 0; pti < 15; pti++) {
        pt[pti] = 0;
    }
    u32 *x = (u32 *)0x0;
    u32 xx = *x;
    // print("%x\n", pd[0]);
    // pd[0] = 0;
    // pd[1] = 0;
}

void kmain(void) {
    printer_init();
    turn_off_pages();
    alloc_init();
    idt_setup();
    pic_init();
    _sti();
    for (;;) {
        // another_task();
        // experiment();
    }
}
