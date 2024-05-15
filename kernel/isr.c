#include <kernel/isr.h>
#include <stdio.h>

void isr_handler(struct registers* regs) {
   printf("Received interrupt: %d\n", regs->int_no);
}
