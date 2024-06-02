#ifndef _KMALLOC_H
#define _KMALLOC_H

#include <stddef.h>

void* kmalloc(size_t size);
void* kmalloc_a(size_t size, size_t align);
void* kmalloc_p(size_t size, size_t* addr);
void* kmalloc_ap(size_t size, size_t align, size_t* addr);

#endif // !_KMALLOC_H
