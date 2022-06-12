#include "alloc.h"

uint8_t memory_pages[NUM_PAGES];
uint16_t alloced_pages;

void alloc_init()
{
    alloced_pages = 0;

    for (int i = 0; i < NUM_PAGES; i++) {
        memory_pages[i] = 0;
    }
}

uint64_t *page_zalloc(int pages)
{
    uint64_t *ptr = page_alloc(pages);

    for (int i = 0; i < pages * PAGE_SIZE; i++) {
        ptr[i] = 0;
    }

    return ptr;
}

uint64_t *page_alloc(int pages)
{
    for (int i = 0; i < NUM_PAGES; i++) {
        if (memory_pages[i] == PAGE_USED) {
            continue;
        }

        if (memory_pages[i] == PAGE_UNUSED) {
            for (int j = 0; j < pages; j++) {
                if (memory_pages[i + j] != PAGE_UNUSED) {
                    return NULL;
                }
            }

            for (int j = 0; j < pages; j++) {
                memory_pages[i + j] = PAGE_USED;
                alloced_pages++;
            }

            memory_pages[i + (pages - 1)] = PAGE_LAST;
            return (void *) ((uint64_t) kernel_heap_start + (i * PAGE_SIZE));
        }
    }

    return NULL;
}

int page_free(void *addr)
{
    int index = ((uint64_t) addr - (uint64_t) kernel_heap_start) / PAGE_SIZE;

    while (index < NUM_PAGES) {
        if (memory_pages[index] == PAGE_LAST) {
            memory_pages[index] = PAGE_UNUSED;
            alloced_pages--;
            return 1;
        } else {
            memory_pages[index] = PAGE_UNUSED;
            alloced_pages--;
        }

        index++;
    }

    return 0;
}
