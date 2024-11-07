#pragma once
#include "pic.h"
#include "stdlib.h"
#include "printer.h"

#define KBD_PORT 0x60
#define KBD_BUFFER_SZ 256

char read_ascii_char(void);
void kbd_init(void);
void kbd_handler(void);
