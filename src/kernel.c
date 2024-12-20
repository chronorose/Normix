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

u32 *foo(u32 *virt) {
    u32 *pdir = (u32 *) 0xc0100000;
    u32 *ptable = (u32 *) 0xc0101000;

    u32 pdindex = (u32) virt >> 22;
    u32 ptindex = (u32) virt >> 12 & 0x03FF;

    print("%x %x\n", pdindex, ptindex);

    u32 *pt = ((u32 *) ptable) + (0x400 * pdindex);
    return (u32 *) (pt[ptindex] & ~0xFFF) + ((u32) virt & 0xFFF);
}

void turn_off_pages() {
    u32 *pd = (u32 *) 0xc0100000;
    u32 *pt = (u32 *) 0xc0101000;
    // u32 *pt = (u32 *) 0x00101000;
    for (u32 pti = 0; pti < 15; pti++) {
        pt[pti] &= ~0x1;
    }
    // for (;;)
    //     ;
    // u32 xx = *x;
}

void kmain(void) {
    printer_init();
    alloc_init();
    // foo();
    idt_setup();
    turn_off_pages();
    pic_init();
    _sti();
    for (;;) {
        // another_task();
        // experiment();
    }
}
