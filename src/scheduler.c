#include "scheduler.h"

#include "alloc.h"
#include "interrupts.h"
#include "process.h"

scheduler_t *scheduler;
extern void kmain();

static void spawn_master() {
    process_t *master = (process_t *) kernel_malloc(sizeof(process_t));
    if (!master) {
        kernel_panic("spawn_master heap allocation error\n", 0x0);
    }

    ctx_t *ctx = (ctx_t *) kernel_calloc(1, sizeof(ctx_t));
    if (!ctx) {
        kernel_panic("Not enough memory to allocate\n", 0x0);
    }
    master->ctx = ctx;
    task *t = (task *) kernel_malloc(sizeof(task));
    if (!t) {
        kernel_panic("sched_add_task heap allocation error\n", 0x0);
    }
    t->val = master;
    scheduler->master = t;
}

void sched_init() {
    scheduler = (scheduler_t *) kernel_malloc(sizeof(scheduler_t));
    if (!scheduler) {
        kernel_panic("sched_init heap allocation error\n", 0x0);
    }
    scheduler->tail = scheduler->curr = 0;
    spawn_master();
}

void sched_add_task(process_t *p) {
    task *t = (task *) kernel_malloc(sizeof(task));
    if (!t) {
        kernel_panic("sched_add_task heap allocation error\n", 0x0);
    }
    t->val = p;
    if (!scheduler->curr && !scheduler->tail) {
        scheduler->tail = t;
        t->next = t;
    } else {
        t->next = scheduler->tail->next;
        scheduler->tail->next = t;
        scheduler->tail = t;
    }
    // print("curr: %d tail: %d tail->next: %d\n", scheduler->curr->val->pid, scheduler->tail->val->pid, scheduler->tail->next->val->pid);
    void *dst = (void *) (p->ctx->esp - sizeof(ctx_t));
    p->ctx->esp -= sizeof(ctx_t);
    memmove(dst, p->ctx, sizeof(ctx_t));
}

void sched_switch(ctx_t *from) {
    if (!scheduler->curr) {
        *scheduler->master->val->ctx = *from;
        // scheduler->master->ret = (u32) from;
        // ctx_print(scheduler->master->val->ctx);
        // for (;;)
        //     ;
        if (scheduler->tail) {
            scheduler->curr = scheduler->tail->next;
            print("curr %d\n", scheduler->curr->val->pid);
        }
    } else {
        *scheduler->curr->val->ctx = *from;
        // scheduler->curr->ret = (u32) from;
        scheduler->curr = scheduler->curr->next;
        print("from %d to %d\n", scheduler->curr->val->pid, scheduler->curr->next->val->pid);
    }
}

u32 get_curr_task_esp() {
    // print("%u\n", !scheduler->curr ? scheduler->master->val->ctx->esp : scheduler->curr->val->ctx->esp);
    // return !scheduler->curr ? scheduler->master->val->ctx->esp : scheduler->curr->val->ctx->esp;
    return !scheduler->curr ? scheduler->master->ret : scheduler->curr->ret;
}

void tasks_print() {
    task *it = scheduler->curr;
    while (it) {
        print("%d ", it->val->pid);
        for (int i = 0; i < 100000; i++) {
        }
        it = it->next;
    }
}
