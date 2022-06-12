#ifndef RISCV_H_
#define RISCV_H_

#include "types.h"

#define PMP_R (1L << 0)
#define PMP_W (1L << 1)
#define PMP_X (1L << 2)
#define PMP_MATCH_NAPOT (3L << 3)

__attribute__((always_inline)) inline void w_pmpcfg0(uint64_t value)
{
    __asm__ volatile ("csrrw x0, pmpcfg0, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_pmpaddr0(uint64_t value)
{
    __asm__ volatile ("csrrw x0, pmpaddr0, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_satp(uint64_t value)
{
    __asm__ volatile ("csrrw x0, satp, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_mstatus(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mstatus, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_sstatus(uint64_t value)
{
    __asm__ volatile ("csrrw x0, sstatus, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_mepc(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mepc, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_sepc(uint64_t value)
{
    __asm__ volatile ("csrrw x0, sepc, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void w_mtvec(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mtvec, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void mret()
{
    __asm__ volatile ("mret");
}

__attribute__((always_inline)) inline void sret()
{
    __asm__ volatile ("sret");
}

__attribute__((always_inline)) inline uint64_t r_mstatus()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mstatus" : "=r"(value));
    return value;
}

__attribute__((always_inline)) inline uint64_t r_mepc()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mepc" : "=r"(value));
    return value;
}

__attribute__((always_inline)) inline uint64_t r_mcause()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mcause" : "=r"(value));
    return value;
}

#endif // RISCV_H_
