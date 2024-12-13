#include "alloc.h"
#include "interrupts.h"
#include "one_to_one_pager.h"
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

void kmain(void) {
    printer_init();
    alloc_init();
    /*paging_setup();*/
    idt_setup();
    pic_init();
    int kek = *((int *) 0x8);
    _sti();
    for (;;) {
        another_task();
        experiment();
    }
}
