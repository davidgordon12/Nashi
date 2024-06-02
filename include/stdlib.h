#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

__attribute__((__noreturn__))
void abort(void);
void* malloc(size_t size);

#endif
