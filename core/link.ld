OUTPUT_ARCH(riscv)
ENTRY(entry)

SECTIONS
{
    . = 0x80000000;
    .text : {
        KEEP(*(.entry))
        *(.text)
    }
    . = ALIGN(0x1000);
    .data : { *(.data) *(.rodata) }
    . = ALIGN(0x1000);
    .bss  : { *(.bss) *(.sbss) }

    . = 0x800FFFFF;
    PROVIDE(stack_top = .);

    . = 0x80100000;
    PROVIDE(kernel_heap_start = .);
}
