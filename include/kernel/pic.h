#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

void timer_wait(uint16_t tick_count);
void pic_init(uint32_t freq);
void send_eoi(uint8_t irq);
void remap_pic();

#endif
