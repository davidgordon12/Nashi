#include "vga.h"

void kernel_main() {
	vga_init();
	vga_write("Hello kernel");
}
