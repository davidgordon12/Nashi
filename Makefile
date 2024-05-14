CC =i686-elf-gcc
AS = nasm

OBJS = kernel/kernel.o kernel/boot.o kernel/vga.o kernel/io.o

CCFLAGS = -c -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS = -f elf
LDFLAGS = -T linker.ld -o nashi.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

all: kernel

kernel: $(OBJS)
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
	rm -rf isodir/nashi.bin nashi.iso kernel/*.o
