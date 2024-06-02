#include <stdint.h>
#include <kernel/kmalloc.h>

extern size_t kernelend;

void* kmalloc(size_t size) {
   uint32_t tmp = kernelend;
   kernelend += size;
   return (void*)tmp;
}

void* kmalloc_a(size_t size, size_t align) {
   if (align == 1 && (kernelend & 0x00000FFF)) { // If the address is not already page-aligned
      kernelend &= 0xFFFFF000;
      kernelend += 0x1000;
   }
   uint32_t tmp = kernelend;
   kernelend += size;
   return (void*)tmp;
}

void* kmalloc_p(size_t size, size_t* addr) {
   if(addr) {
      *addr = kernelend;     
   }
   uint32_t tmp = kernelend;
   kernelend += size;
   return (void*)tmp;
}

void* kmalloc_ap(size_t size, size_t align, size_t* addr) {
   if (align == 1 && (kernelend & 0x00000FFF)) { // If the address is not already page-aligned
      kernelend &= 0xFFFFF000;
      kernelend += 0x1000;
   }
   if(addr) {
      *addr = kernelend;     
   }
   uint32_t tmp = kernelend;
   kernelend += size;
   return (void*)tmp;
}
