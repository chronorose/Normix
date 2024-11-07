#include "alloc.h"
#include "pic.h"
#include "printer.h"
#include "interrupts.h"

extern printer_t printer;
extern void inter();
extern void _sti();

void kmain(void) {
    printer_init();
    alloc_init();
    idt_setup();
    pic_init();
    // inter();
    // _sti();
    for (;;) ;
}
