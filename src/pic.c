#include "pic.h"

extern byte_t _inb(u16 port);
extern void _outb(u16 port, byte_t data);

static byte_t inb(u16 port) {
    return _inb(port);
}

static void outb(u16 port, byte_t data) {
    _outb(port, data);
    _outb(DUMMY_PORT, 0xFF);
}

void pic_init(void) {
    byte_t icw1 = 0b00010001;
    byte_t icw4 = 0b00000001;

#define ICWS_N 4
    byte_t icws[][ICWS_N] = {
        {icw1,
         0x20,       // icw2_master
         0b00000100, // icw3_master
         icw4},
        {icw1,
         0x28,       // icw2_slave
         0x2,        // icw3_slave
         icw4}};

    for (int port = MASTER_COMMAND, i = 0; port <= SLAVE_COMMAND; port += (SLAVE_COMMAND - MASTER_COMMAND), i++) {
        outb(port, icws[i][0]);
        for (int j = 1; j < ICWS_N; j++) {
            outb(port + 1, icws[i][j]);
        }
    }
}


void unmask(byte_t irq) {
    outb(MASTER_DATA, inb(MASTER_DATA) & ~irq);
}
void unmask_all(void) {
    outb(MASTER_DATA, inb(MASTER_DATA) & 0xFF);
}
void mask(byte_t irq) {
    outb(MASTER_DATA, inb(MASTER_DATA) & (0xFF - irq)); 
}
void mask_all(void) {
    outb(MASTER_DATA, inb(MASTER_DATA) | 0xFF);
}
