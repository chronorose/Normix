#include "pager.h"

void turn_off_pages() {
    u32 *pd = (u32 *) 0xc0100000;
    u32 *pt = (u32 *) 0xc0101000;
    for (u32 pti = 0; pti < 15; pti++) {
        pt[pti] &= ~0x1;
    }
}

u32 *virt_to_phys(u32 *virt) {
    u32 *pdir = (u32 *) 0xc0100000;
    u32 *ptable = (u32 *) 0xc0101000;

    u32 pdindex = (u32) virt >> 22;
    u32 ptindex = (u32) virt >> 12 & 0x03FF;

    u32 *pt = ((u32 *) ptable) + (0x400 * pdindex);
    return (u32 *) (pt[ptindex] & ~0xFFF) + ((u32) virt & 0xFFF);
}
