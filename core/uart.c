#include "uart.h"

#include "uart.h"

void uart_init()
{
    uint32_t lcr = (1 << 0) | (1 << 1);
    uint16_t divisor = 592;
    uint8_t divisor_least = divisor & 0xff;
    uint8_t divisor_most = divisor >> 8;

    *((unsigned char *) 0x10000000 + 3) = lcr;
    *((unsigned char *) 0x10000000 + 2) = 1 << 0;
    *((unsigned char *) 0x10000000 + 1) = 1 << 0;
    *((unsigned char *) 0x10000000 + 3) = lcr | 1 << 7;
    *((unsigned char *) 0x10000000 + 0) = divisor_least;
    *((unsigned char *) 0x10000000 + 1) = divisor_most;
    *((unsigned char *) 0x10000000 + 3) = lcr;
}

void uart_print_char(const char c)
{
    *((unsigned char *)0x10000000) = c;
}

void uart_print_newline()
{
    uart_print_char('\r');
    uart_print_char('\n');
}

void uart_print_str(const char *str)
{
    for ( ; *str; str++) {
        uart_print_char(*str);
    }
}

void uart_print_int(int num)
{
    int a = num;

    if (num < 0) {
        uart_print_char('-');
        num = -num;
    }

    if (num > 9) uart_print_int(num/10);

    uart_print_char('0' + (a % 10));
}

void uart_print_u64(uint64_t num)
{
    uint64_t a = num;
    if (num > 9) uart_print_u64(num/10);
    uart_print_char('0' + (a % 10));
}

void uart_print_u64_nl(uint64_t num)
{
    uart_print_u64(num);
    uart_print_str("\r\n");
}

void uart_print_u64_bin(uint64_t num)
{
    uint64_t a = num;
    if (num > 1) uart_print_u64_bin(num/2);
    uart_print_char('0' + (a % 2));
}

void uart_print_u64_hex(uint64_t num)
{
    uint64_t a = num;
    if (num > 15) uart_print_u64_hex(num / 16);

    uint64_t n = a % 16;
    if (n <= 9)  uart_print_char('0' + n);
    if (n == 10) uart_print_char('a');
    if (n == 11) uart_print_char('b');
    if (n == 12) uart_print_char('c');
    if (n == 13) uart_print_char('d');
    if (n == 14) uart_print_char('e');
    if (n == 15) uart_print_char('f');
}

void uart_print_u64_hex_nl(uint64_t num)
{
    uart_print_u64_hex(num);
    uart_print_newline();
}
