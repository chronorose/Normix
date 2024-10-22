#include "stdlib.h"

#define ALLOCATOR 0x100000

char* ptr = (char*)ALLOCATOR;

/*typedef struct _list {*/
/*    struct _list* next;*/
/*} list;*/
/**/
/*void init_pga() {*/
/**/
/*    for (; ptr < (char*)0x400000; ptr += sizeof(list)) {*/
/**/
/*    }*/
/*}*/

void* kmalloc(unsigned int size) {
    void* ret = ptr; 
    ptr += size; 
    return ret;
}

void* kcalloc(unsigned int amount, unsigned int size) {
    void* ret = ptr;
    kmemset(ptr, 0, size * amount);
    return ret;
}

// realloc doesnt exist yet
// i thought about it and it probably won't exist for some time yet
/*void* krealloc(void* old_ptr, unsigned int size) {*/
/**/
/*    return 0;*/
/*}*/

//ye and free too
/*void kfree(void* ptr) {*/
/**/
/*}*/
