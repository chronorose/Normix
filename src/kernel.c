#include "alloc.h"
#include "interrupts.h"
#include "pic.h"
#include "printer.h"

extern printer_t printer;
extern void inter();
extern void _sti();
extern void experiment();

void kmain(void) {
    printer_init();
    alloc_init();
    idt_setup();
    pic_init();
    experiment();
    // _sti();
    for (;;)
        ;
}
