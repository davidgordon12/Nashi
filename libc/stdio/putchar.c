#include <stdio.h>
#include <kernel/vga.h>
 
int putchar(int ic) {
	char c = (char) ic;
	vga_write(&c);
	return ic;
}
