#include "alloc.h"
#include "interrupts.h"
#include "pager.h"
#include "pic.h"
#include "printer.h"

extern printer_t printer;
extern void inter();
extern void _sti();
extern void _cli();
extern void experiment();
extern void collect_ctx();
extern void syscall_test();

/*void another_task() {*/
/*    for (int i = 0; i < 100000; i++) {*/
/*    }*/
/*    print("another task\n");*/
/*}*/

void kmain(void) {
    global_printer_init();
    printer_t printer = printer_init(30, 0, 40, 40);
    for (int i = 0; i < 10; i++) {
        print(&printer, "hello sir!");
    }
    /*alloc_init();*/
    /*disable_first_pages((pd_entry *) (KERNEL_PAGE_DIRECTORY));*/
    /*idt_setup();*/
    /*pic_init();*/
    /*int kek = *((int *) 0x8);*/
    /*syscall_test();*/
    /*_sti();*/
    /*for (;;) {*/
    /*    another_task();*/
    /*    experiment();*/
    /*}*/
}
