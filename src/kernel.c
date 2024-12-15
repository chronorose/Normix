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

void foo() {
    // for (u32 pd = 0x80300; pd < 0x80C10; pd += 4) {
    //     u32 x = *((u32 *) pd);
    //     print("pde index %x: pte index %x flags: %x\n", pd, (x >> 12) << 12, (x << 20) >> 20);
    //     return;
    //     for (int i = 0 ; i < 10000; i++) {
    //     }
    // }
    for (u32 virt = 0xC0000000; virt < 0xC0400000; virt += 0x1000) {
        u32 pdindex = virt >> 22;
        u32 ptindex = virt >> 12 & 0x03FF;

        // virt = 0xc0000800;
        // u32 *pd = (u32 *) 0x80000;
        // u32 *pt = (u32 *) 0x81000 + (0x400 * pdindex);
        // u32 shit = pd[pdindex + 768];
        // print("pte addr %x flags %x\n", shit >> 22, shit & 0x7);
        // return;

        // print("Virt: %u, phys: %x\n", virt, (pt[ptindex] & ~0xFFF) + (virt & 0xFFF));
        // return;
        // for (int i = 0; i < 100000; i++) {
        // }
    }
}

void kmain(void) {
    printer_init();
    alloc_init();
    idt_setup();
    pic_init();
    foo();
    _sti();
    for (;;) {
        another_task();
        experiment();
    }
}
