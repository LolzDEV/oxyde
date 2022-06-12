#ifndef UART_H_
#define UART_H_

#include "types.h"

void uart_init();
void uart_print_char(const char c);
void uart_print_newline();
void uart_print_str(const char *str);
void uart_print_int(int num);
void uart_print_u64(uint64_t num);
void uart_print_u64_bin(uint64_t num);
void uart_print_u64_nl(uint64_t num);
void uart_print_u64_hex(uint64_t num);
void uart_print_u64_hex_nl(uint64_t num);

#endif // UART_H_
