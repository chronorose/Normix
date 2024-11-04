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
void kernel_panic(char *msg, int vector);
void idt_setup();
