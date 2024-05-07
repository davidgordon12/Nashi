#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/nashi.kernel isodir/boot/nashi.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "nashi" {
	multiboot /boot/nashi.kernel
}
EOF
grub2-mkrescue -o nashi.iso isodir
