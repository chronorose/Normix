#pragma once
#include "alloc.h"
#include "interrupts.h"
#include "pic.h"
#include "process.h"
#include "stdlib.h"

#define PROC_N 4

typedef struct process_t process_t;

typedef struct task {
    u32 ret;
    process_t *val;
    struct task *next;
} task;

typedef struct {
    task *curr;
    task *tail;
    task *master;
} scheduler_t;

void sched_init();
void sched_add_task(process_t *p);
void sched_switch(ctx_t *from);
u32 get_curr_task_esp();
void tasks_print();
