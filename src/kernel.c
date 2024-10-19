#include "printer.h"
extern printer_t printer;
void kernel_entry(void) {
    printer_init();
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i; j++) {
            print(" ");
          }
      print("%d\n", i);
    }
    for(;;) ;
}
