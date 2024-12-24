#pragma once

#include "alloc.h"
#include "interrupts.h"
#include "printer.h"

#define PROC_STACK_SZ 0x1000 // 4 KiB stack

struct process_t {
    u32 pid;
    ctx_t *ctx;
    byte_t *stack_begin;
    printer_t *printer;
};

void proc_init(struct process_t *p, void *startup);
