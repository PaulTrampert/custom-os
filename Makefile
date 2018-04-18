# $@ = target file
# $< = first dependency
# $^ = all dependencies
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# File extension replacement
OBJ = $(C_SOURCES:.c=.o)

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

# -g: Use debugging symbols in gcc
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32


# First rule is the one executed when no parameters are fed to the Makefile
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: boot/kernel_entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# For debugging
kernel.elf: boot/kernel_entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin & $(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile it from its .c
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean: 
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o