#! /bin/bash

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

make kernel
 
cp sysroot/boot/nashi.bin isodir/boot/myos.bin
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "nashi" {
	multiboot /boot/nashi.bin
}
EOF

make boot
