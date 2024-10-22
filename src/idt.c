#include "allocator.h"
#include "text_mode.h"
#define IDT_SIZE 256

extern void* tramplins[IDT_SIZE];
extern void lidt_load(void* addr);

#pragma pack(push, 1)
typedef struct {
    unsigned short size;
    unsigned int addr;
} IDTD;

typedef struct {
    unsigned short off1;
    unsigned short sel;
    unsigned char zero;
    unsigned char attrs;
    unsigned short off2;
} IDTEntry;
#pragma pack(pop)

void idt_sd(IDTEntry* idt, unsigned char n, void* gate, unsigned short flags) {
    IDTEntry* idte = (idt + n);
    idte->off1 = (unsigned int)gate & 0xffff;
    idte->sel = 0x8;
    idte->off2 = ((unsigned int)gate >> 16);
    idte->zero = 0;
    idte->attrs = flags;
}

void gen_idt() {
    IDTEntry* idt = kmalloc(sizeof(IDTEntry) * IDT_SIZE);
    IDTD idtd;
    idtd.addr = (unsigned int) idt;
    idtd.size = sizeof(IDTEntry) * IDT_SIZE - 1;

    for (int i = 0; i < 256; i++) {
        idt_sd(idt, i, tramplins[i], 0x8e);
    }
    lidt_load(&idtd);
}
