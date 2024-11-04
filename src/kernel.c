#include "alloc.h"
#include "printer.h"
#include "trampolines.h"

extern printer_t printer;
extern void inter();
extern void _sti();

void kmain(void) {
  printer_init();
  alloc_init();
  idt_setup();
  print("hello");
  for (;;)
    ;
}
