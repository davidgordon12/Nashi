#include "kernel/io.h"
#include <kernel/isr.h>
#include <kernel/pic.h>
#include <stdio.h>

interrupt_handler interrupt_handlers[256];

void isr_handler(struct registers* regs) {
   printf("Received interrupt: 0x%X\n", regs->int_no);
}

void irq_handler(struct registers* regs) {
   if(interrupt_handlers[regs->int_no] != 0) {
      interrupt_handlers[regs->int_no](regs);
   }

   if(regs->int_no >= 40) {
      outb(0xA0, 0x20);
   }

   outb(0x20, 0x20);
} 
void register_interrupt_handler (uint8_t n, interrupt_handler h) {
   interrupt_handlers[n] = h;
}
