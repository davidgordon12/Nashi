#include <kernel/vga.h>
#include <stdio.h>

void kernel_main() {
    vga_init();
    printf("VGA Driver Initialized..!");
}
