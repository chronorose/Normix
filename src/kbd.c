#include "kbd.h"

typedef struct {
    u8 pressed;
    char buffer[KBD_BUFFER_SZ];
    u8 rptr; // char that should be read from buffer
    u8 wptr; // char that should be written from buffer
} kbd_t;

static kbd_t kbd;

void kbd_init() {
    kbd.rptr = kbd.wptr = kbd.pressed = 0;
    memset(kbd.buffer, 0, KBD_BUFFER_SZ);
}

static byte_t read_scan_code(void) {
    return inb(KBD_PORT);
}

char read_ascii_char(void) {
    byte_t scan_code = read_scan_code();
    return scan_code;
}

void kbd_handler(void) {
    char c = read_ascii_char();
    if (c != (kbd.pressed | 0x80)) {
        kbd.pressed = c;
        kbd.buffer[kbd.wptr++] = kbd.pressed;
    }
    /*print("%x", kbd.buffer[kbd.rptr++]);*/
}
