#pragma once

#include "alloc.h"

/*
 * this is for 1-1 page translation.
 */
;

void paging_setup();

#pragma pack(push, 1)

typedef struct {
    u32 present : 1;
    u32 rw : 1;
    u32 user_supervisor : 1;
    u32 cache_control : 3;
    u32 cc_or_available : 1;
    u32 page_size : 1;
    u32 available : 4;
    u32 pt_address : 20;
} pd_entry;

typedef struct {
    u32 present : 1;
    u32 rw : 1;
    u32 user_supervisor : 1;
    u32 cc : 6;
    u32 available : 3;
    u32 frame_address : 20;
} pt_entry;

#pragma pack(pop)
