CC:=riscv64-unknown-elf-gcc
CFLAGS:=-Wall -Wextra -pedantic -g -std=c11 -nostdlib -ffreestanding -mcmodel=medany -ftree-ter
AS:=riscv64-unknown-elf-as
AFLAGS:=
SOURCES:=boot.S start.c uart.c mm.c alloc.c
OBJECTS:=$(SOURCES:.c=.o)

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $.S
	$(AS) $(AFLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -v -rf $(OBJECTS)
