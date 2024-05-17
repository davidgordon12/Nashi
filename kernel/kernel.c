#include <stdio.h>
#include <kernel/keyboard.h>
#include <kernel/pic.h>
#include <kernel/idt.h>
#include <kernel/vga.h>
#include <kernel/gdt.h>

void kernel_main() {
    vga_init();
    printf("VGA Driver Initialized..!\n");
    gdt_init();
    printf("GDT Initialized..!\n");
    idt_init();
    printf("IDT Initialized..!\n");
    init_pic(50);
    printf("PIC Initialized..!\n");
}
