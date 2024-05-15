#include "kernel/idt.h"
#include <kernel/vga.h>
#include <kernel/gdt.h>
#include <stdio.h>

void kernel_main() {
    vga_init();
    printf("VGA Driver Initialized..!\n");
    gdt_init();
    printf("GDT Initialized..!\n");
    idt_init();
    printf("IDT Initialized..!\n");
    asm volatile("int $0xA");
    asm volatile("int $0xB");
    asm volatile("int $0xC");
    asm volatile("int $0xD");
    asm volatile("int $0xE");
    asm volatile("int $0xF");
}
