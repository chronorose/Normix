#pragma once
#include "types.h"

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1
#define DUMMY_PORT 0x80

typedef enum {
    IRQ_TIMER = 0x1,
    IRQ_KBD = 0x2,
    IRQ_SLAVE = 0x3,
} IRQ;

void pic_init(void);

void unmask(byte_t irq);
void unmask_all(void);
void mask(byte_t irq);
void mask_all(void);
