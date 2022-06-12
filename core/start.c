#include "uart.h"
#include "alloc.h"
#include "mm.h"

void init()
{
    uart_init(); // Init serial communication
    uart_print_str("Booting\n\r");

    alloc_init(); // Init memory allocator
    mm_init(); // Init memory management (paging)
}

void kmain()
{
    uart_print_str("Initialization completed\n\r");
    for (;;);
}
