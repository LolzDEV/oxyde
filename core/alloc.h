#ifndef ALLOC_H_
#define ALLOC_H_

#include "types.h"

#define PAGE_UNUSED    0
#define PAGE_USED      1
#define PAGE_LAST      2
#define NUM_PAGES   1024
#define PAGE_SIZE   4096

extern uint64_t kernel_heap_start[];

void alloc_init();
uint64_t *page_alloc(int pages);
uint64_t *page_zalloc(int pages);
int page_free(void *addr);

#endif // ALLOC_H_
