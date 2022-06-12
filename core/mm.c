#include "mm.h"

uint64_t *kernel_page_table;
void kmain();

void mm_init()
{
    kernel_page_table = (uint64_t *) page_zalloc(1);

    mm_map(kernel_page_table, 0x10000000, 0x10000000, 1, 0, 0);

    for (uint64_t addr = 0x80000000; addr < 0x80100000; addr += 0x1000) {
        mm_map(kernel_page_table, addr, addr, 1, 1, 0);
    }

    w_pmpaddr0((~0L) >> 10);
    w_pmpcfg0(PMP_R | PMP_W | PMP_X | PMP_MATCH_NAPOT);
    w_satp((uint64_t) (0x8L << 60 | ((uint64_t) kernel_page_table) >> 12));
    w_mstatus((1 << 11) | (1 << 5) | (1 << 3));
    w_mepc((uint64_t) &kmain);
    mret();
}

uint64_t mm_map(uint64_t *page_table, uint64_t virt, uint64_t phys, int write, int exec, int user)
{
    uint64_t vpn[3];
    uint64_t *pte;
    uint64_t *alloced_page;

    vpn[2] = VPN2(virt);
    vpn[1] = VPN1(virt);
    vpn[0] = VPN0(virt);

    pte = page_table;

    if (!PTE_IS_VALID(pte[vpn[2]])) {
        alloced_page = page_zalloc(1);
        pte[vpn[2]] = (((uint64_t) alloced_page) >> 2) | PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[1]])) {
        alloced_page = page_zalloc(1);
        pte[vpn[1]] = (((uint64_t) alloced_page) >> 2) | PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[0]])) {
        pte[vpn[0]] = (phys >> 2) | PTE_READ | PTE_VALID;

        if (write) pte[vpn[0]] |= PTE_WRITE;
        if (exec)  pte[vpn[0]] |= PTE_EXEC;
        if (user)  pte[vpn[0]] |= PTE_USER;

        return pte[vpn[0]];
    }

    return 0;
}
