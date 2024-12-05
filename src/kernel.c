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

void kmain(void) {
    printer_init();
    alloc_init();
    idt_setup();
    pic_init();
    _sti();
    for (;;) {
        another_task();
        experiment();
    }
}
