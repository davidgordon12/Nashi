#! /bin/bash

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "nashi" {
	multiboot /boot/nashi.bin
}
EOF

make kernel
make boot
