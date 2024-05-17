#ifndef _ISR_H
#define _ISR_H

#include <stdint.h>

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct registers {
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
};

// An interrupt handler. It is a pointer to a function which takes a pointer 
// to a structure containing register values.
typedef void (*interrupt_handler)(struct registers*);

// Allows us to register an interrupt handler.
void register_interrupt_handler (uint8_t n, interrupt_handler h);

#endif // !_ISR_H
