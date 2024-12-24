#include "stdlib.h"

#include "alloc.h"
#include "interrupts.h"
#include "process.h"
#include "scheduler.h"

static int nextpid = 1;

void memset(void *dst, int c, int n) {
    while (n--)
        *((byte_t *) dst++) = c;
}

void *memmove(void *dst, void *src, int n) {
    if (!dst || !src) {
        return (void *) 0;
    }
    char *cdst = (byte_t *) dst;
    char *csrc = (byte_t *) src;
    if (dst <= src) {
        while (n--) {
            *cdst++ = *csrc++;
        }
    } else {
        cdst += n - 1;
        csrc += n - 1;
        while (n--) {
            *cdst-- = *csrc--;
        }
    }
    return dst;
}

u32 proc_spawn(void *startup) {
    process_t *p = (process_t *) kernel_malloc(sizeof(process_t));
    if (!p) {
        kernel_panic("proc_spawn heap allocation error", 0x0);
    }
    proc_init(p, startup);
    p->pid = nextpid;
    sched_add_task(p);
    return nextpid++;
}
