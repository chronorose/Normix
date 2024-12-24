#include "alloc.h"
#include "interrupts.h"
#include "pic.h"
#include "printer.h"
#include "scheduler.h"

extern void inter();
extern void _sti();
extern void _cli();

void another_task() {
    for (int i = 0; i < 100000; i++) {
    }
    print("another task\n");
}

void p1_entry() {
    for (;;) {
        print("Hello from p1\n");
    }
}

void p2_entry() {
    for (;;) {
        print("Hello from p2\n");
    }
}

void p3_entry() {
    for (;;) {
        print("Hello from p3\n");
    }
}

void p4_entry() {
    for (;;) {
        print("Hello from p4\n");
    }
}

void foo() {
    u32 p1 = proc_spawn(p1_entry);
    u32 p2 = proc_spawn(p2_entry);
    u32 p3 = proc_spawn(p3_entry);
    u32 p4 = proc_spawn(p4_entry);
}

void kmain(void) {
    printer_init();
    alloc_init();
    idt_setup();
    pic_init();
    sched_init();
    _sti();
    // foo();
    // inter();
    for (;;) {
        // another_task();
    }
}
