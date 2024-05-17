#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

void init_pic(uint32_t freq);
void send_eoi(uint8_t irq);
void remap_pic();

#endif
