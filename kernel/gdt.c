#include <kernel/gdt.h>
#include <stdint.h>

extern void gdt_flush(uint32_t);

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdtr;

void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= granularity & 0xF0;
   gdt_entries[num].access      = access;
}

void gdt_init()
{
    gdtr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdtr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdtr);
}
