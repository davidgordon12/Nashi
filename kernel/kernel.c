#include <stdio.h>
#include <kernel/shell.h>
#include <kernel/keyboard.h>
#include <kernel/pic.h>
#include <kernel/idt.h>
#include <kernel/vga.h>
#include <kernel/gdt.h>

void kernel_main() {
    vga_init();
    printf("[Nashi]: VGA Driver Initialized..!\n");
    gdt_init();
    printf("[Nashi]: GDT Initialized..!\n");
    idt_init();
    asm volatile ("int $0x03");
    printf("[Nashi]: IDT Initialized..!\n");
    pic_init(20);
    printf("[Nashi]: PIC Initialized..!\n");
    keyboard_init();
    printf("[Nashi]: Keyboard Driver Initialized..!\n");
    enable_interrupts();
    #define shell_mode
    shell();
}
