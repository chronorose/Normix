#include "pager.h"

#include "alloc.h"
#include "printer.h"

/*
 * this is for 1-1 page translation.
 * very basic stuff. we just enable everything with all permissions and sheise.
 * ЧТО-ТО ТУТ НЕ ТАК.
 */

extern void do_paging(pd_entry *pd);

void disable_first_pages(pd_entry *pd) {
    pt_entry *pt = (pt_entry *) (((unsigned int) pd[0].pt_address) << 12);
    for (int i = 0; i < DISABLED_PAGES; i++) {
        pt->present = 0;
    }
}

/*void finish_paging() {*/
/*    pd_entry *pd = (pd_entry *) 0x80000;*/
/*    for (int i = 769; i < )*/
/*}*/

pt_entry *createPT(u32 index) {
    pt_entry *pt = (pt_entry *) kernel_malloc_aligned(sizeof(pt_entry) * PAGES_AMOUNT, ALIGNMENT);
    for (u32 i = 0; i < PAGES_AMOUNT; i++) {
        pt[i].present = 1;
        pt[i].rw = 1;
        pt[i].user_supervisor = 1;
        pt[i].frame_address = ((index * PAGES_AMOUNT + i) * PAGE) >> 12;
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
        pd[i].pt_address = ((u32) pt) >> 12; // have to check if it's gonna be alright.
    }
    return pd;
}

void paging_setup() {
    pd_entry *pd = createPD();
    do_paging(pd);
}
