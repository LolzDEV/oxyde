#ifndef MM_H_
#define MM_H_

#include "alloc.h"
#include "types.h"
#include "riscv.h"

#define PTE_SIZE    8
#define PTE_ENTRIES PAGE_SIZE / PTE_SIZE
#define PTE_VALID   1
#define PTE_READ    (1 << 1)
#define PTE_WRITE   (1 << 2)
#define PTE_EXEC    (1 << 3)
#define PTE_USER    (1 << 4)

#define PTE_IS_VALID(x) (x & 0x1)
#define PPN(x)          (((x >> 28) & 0x3ffffff) | ((x >> 19) & 0x1ff) | ((x >> 10) & 0x1ff)) >> 12
#define VPN0(x)         (x >> 12) & 0x1ff
#define VPN1(x)         (x >> 21) & 0x1ff
#define VPN2(x)         (x >> 30) & 0x1ff

void mm_init();
uint64_t mm_map(uint64_t *page_table, uint64_t virt, uint64_t phys, int write, int exec, int user);

#endif // MM_H_
