CC = i686-elf-gcc
LD = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -lgcc -ffreestanding -O2 -nostdlib 

OBJECTS = kernel/kernel.o kernel/boot.o

all: qemu

kernel: $(OBJECTS)
	mkdir -p bin
	mv $(OBJECTS) bin
	$(LD) $(LDFLAGS) bin/*.o -o nashi.bin

buildimg: kernel
	mv nashi.bin isodir/boot
	grub2-mkrescue -o nashi.iso isodir

qemu: buildimg
	qemu-system-i386 -cdrom nashi.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -r isodir/boot/nashi.bin nashi.iso bin
