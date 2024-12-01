#include "pic.h"

extern byte_t _inb(u16 port);
extern void _outb(u16 port, byte_t data);

byte_t inb(u16 port) {
    return _inb(port);
}

void outb(u16 port, byte_t data) {
    _outb(port, data);
}

/**
 * pic_send_byte:
 * Sends data on PIC and byte 0xFF on DUMMY_PORT to make a delay.
 */
void pic_send_byte(u16 port, byte_t data) {
    outb(port, data);
    outb(DUMMY_PORT, 0xFF);
}

void pic_init(void) {
    byte_t icw1 = 0b00010001;
    byte_t icw4 = 0b00000001;

#define ICWS_N 4
    byte_t icws[][ICWS_N] = {
        {icw1,
         MASTER_MAP_START, // icw2_master
         0b00000100,       // icw3_master
         icw4},
        {icw1,
         SLAVE_MAP_START, // icw2_slave
         0x2,             // icw3_slave
         icw4}};

    for (int port = MASTER_COMMAND, i = 0; port <= SLAVE_COMMAND; port += (SLAVE_COMMAND - MASTER_COMMAND), i++) {
        pic_send_byte(port, icws[i][0]);
        for (int j = 1; j < ICWS_N; j++) {
            pic_send_byte(port + 1, icws[i][j]);
        }
    }
    pic_mask_all();
    // pic_unmask(IRQ_TIMER);
    // pic_unmask(IRQ_KBD);

    /**
     * Drivers setup
     */
    // kbd_init();
}

void pic_send_eoi(byte_t irq) {
    if (irq < MASTER_MAP_START || irq > SLAVE_MAP_END) {
        return;
    }
    if (SLAVE_MAP_START <= irq) {
        pic_send_byte(SLAVE_COMMAND, PIC_EOI);
    }
    pic_send_byte(MASTER_COMMAND, PIC_EOI);
}

void pic_unmask(byte_t irq) {
    pic_send_byte(MASTER_DATA, inb(MASTER_DATA) & ~(1 << irq));
}

void pic_unmask_all(void) {
    pic_send_byte(MASTER_DATA, 0);
}

void pic_mask(byte_t irq) {
    pic_send_byte(MASTER_DATA, inb(MASTER_DATA) | (1 << irq));
}

void pic_mask_all(void) {
    pic_send_byte(MASTER_DATA, inb(MASTER_DATA) | 0xFF);
}
