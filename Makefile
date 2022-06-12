CC:=riscv64-unknown-elf-gcc
CFLAGS:=-Wall -Wextra -pedantic -g -std=c11 -nostdlib -ffreestanding -mcmodel=medany -ftree-ter
BINARY:=oxyde

CORE_OBJECTS=core/boot.o core/start.o core/alloc.o core/mm.o core/uart.o
CORE_LINKING:=-Tcore/link.ld

all: $(BINARY)

$(BINARY): objects
	$(CC) $(CFLAGS) $(CORE_LINKING) $(CORE_OBJECTS) -o $(BINARY)

objects:
	@make -C core

qemu: $(BINARY)
	@qemu-system-riscv64 -monitor stdio -machine virt -bios none -kernel $(BINARY)

.PHONY: clean
clean:
	@rm -v -rf $(BINARY)
	@make -C core clean
