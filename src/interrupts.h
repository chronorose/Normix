#pragma once
#include "types.h"

typedef enum {
    INTERRUPT_GATE = 0xE,
    TRAP_GATE = 0xF,
} GATE_TYPE;

#pragma pack(push, 1)

typedef struct {
    u16 offset_low;
    u16 segselector;
    u32 nargs : 5;
    u32 unused0 : 3;
    u32 gate_type : 4;
    u32 unused1 : 1;
    u32 dpl : 2;
    u32 existance_bit : 1;
    u16 offset_high;
} gate_descriptor_t;

typedef struct {
    u16 idt_sz;
    u32 idt_addr;
} idt_descriptor_t;

#pragma pack(pop)

typedef struct {
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;

    u16 gs;
    u16 gs_pd;

    u16 fs;
    u16 fs_pd;

    u16 es;
    u16 es_pd;

    u16 ds;
    u16 ds_pd;

    u32 vector;
    u32 err_code;

    u32 eip;
    u16 cs;
    u16 cs_pd;
    u32 eflags;

    u32 esp_opt;
    u16 ss_opt;
    u16 ss_opt_pd;
} ctx_t;

void kernel_panic(char *msg, int vector);
void idt_setup();
