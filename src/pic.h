#pragma once
#include "types.h"

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define MASTER_MAP_START 0x20
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1
#define SLAVE_MAP_START 0x28
#define SLAVE_MAP_END (SLAVE_MAP_START + 7)
#define DUMMY_PORT 0x80
#define PIC_EOI 0x20

typedef enum {
    IRQ_TIMER = 0x1,
    IRQ_KBD = 0x2,
    IRQ_SLAVE = 0x4,
} IRQ;

void pic_init(void);
void pic_send_eoi(byte_t irq);

void pic_send_byte(u16 port, byte_t data);

byte_t inb(u16 port);
void outb(u16 port, byte_t data);

void pic_unmask(byte_t irq);
void pic_unmask_all(void);
void pic_mask(byte_t irq);
void pic_mask_all(void);
