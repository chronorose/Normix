#include "one_to_one_pager.h"

#include "alloc.h"
#include "printer.h"

/*
 * this is for 1-1 page translation.
 * very basic stuff. we just enable everything with all permissions and sheise.
 */

#define PT_AMOUNT 1024
#define PAGES_AMOUNT 1024
#define PAGE 0x1000
#define ALIGNMENT 0x1000
#define ALIGNMENT_BIG 0x2000000

extern void do_paging(pd_entry *pd);
extern void do_paging_big(pd_big_entry *pd);

pt_entry *createPT(u32 index) {
    pt_entry *pt = (pt_entry *) kernel_malloc_aligned(sizeof(pt_entry) * PAGES_AMOUNT, ALIGNMENT);
    for (u32 i = 0; i < PAGES_AMOUNT; i++) {
        pt[i].present = 1;
        pt[i].rw = 1;
        pt[i].user_supervisor = 1;
        pt[i].frame_address = index * PAGES_AMOUNT + i;
    }
    return pt;
}

pd_entry *createPD() {
    pd_entry *pd = (pd_entry *) kernel_malloc_aligned(sizeof(void *) * PT_AMOUNT, ALIGNMENT);
    for (u32 i = 0; i < PT_AMOUNT; i++) {
        pd[i].present = 1;
        pd[i].rw = 1;
        pd[i].user_supervisor = 1;
        pd[i].page_size = 0;
        pt_entry *pt = createPT(i);
        pd[i].pt_address = ((u32) pt) >> 12;
    }
    return pd;
}

pd_big_entry *createPDBig() {
    pd_big_entry *pd = (pd_big_entry *) kernel_malloc_aligned(sizeof(void *) * PT_AMOUNT, ALIGNMENT);
    for (u32 i = 0; i < PT_AMOUNT; i++) {
        pd[i].present = 1;
        pd[i].rw = 1;
        pd[i].user_supervisor = 1;
        pd[i].page_size = 1;
        pd[i].frame_adress1 = i;
    }
    return pd;
}

void paging_setup() {
    //pd_entry *pd = createPD();
    //do_paging(pd);
    pd_big_entry *pd = createPDBig();
    do_paging_big(pd);
}
