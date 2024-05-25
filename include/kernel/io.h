#ifndef _IO_H
#define _IO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <kernel/pic.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif // !_IO_H
