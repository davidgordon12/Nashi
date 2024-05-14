CC =i686-elf-gcc
AS = nasm

LIBC=\
libc/stdio/printf.o \
libc/stdio/putchar.o \
libc/stdio/puts.o \
libc/stdlib/abort.o \
libc/string/memcmp.o \
libc/string/memcpy.o \
libc/string/memmove.o \
libc/string/memset.o \
libc/string/strlen.o \

OBJS = kernel/kernel.o kernel/boot.o kernel/vga.o kernel/io.o

CCFLAGS = -c -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS = -f elf
LDFLAGS = -T linker.ld -o nashi.bin -ffreestanding -O2 -nostdlib $(OBJS) $(LIBC) -lgcc

all: kernel

kernel: $(OBJS) $(LIBC)
	$(CC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

boot:
	cp nashi.bin isodir/boot
	grub2-mkrescue -o nashi.iso isodir
	qemu-system-i386 -cdrom nashi.iso

clean:
	rm -rf isodir/nashi.bin nashi.iso nashi.bin kernel/*.o libc/stdio/*.o libc/stdlib/*.o libc/string/*.o
