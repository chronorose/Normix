#include "printer.h"
extern printer_t printer;
void kernel_entry(void) {
    printer_init();
    // print("%s %s: %d %h\n", "Hello", "world", 42, 42);
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < i; j++) {
            print(" ");
          }
      print("%d\n", i);
    }
    for(;;) ;
}
