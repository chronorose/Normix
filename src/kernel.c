#include "printer.h"
#include "alloc.h"
#include "trampolines.h"

extern printer_t printer;
extern void inter();
extern void _sti();

void kernel_entry(void) {
    printer_init();
    alloc_init();
    idt_setup();
    // print("%c %c %c %d %x ", 'x', 'o', 'y', 55, 42);
    // int x = 12 / 0;
    // inter();
    // _sti();
    for(;;) ;
}
