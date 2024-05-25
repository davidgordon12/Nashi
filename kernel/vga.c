#include <kernel/vga.h>
#include <kernel/keyboard.h>
#include <kernel/io.h>

uint16_t* buffer = (uint16_t*)0xB8000;

size_t row = 0; size_t column = 0;

const uint8_t color = (VGA_COLOR_WHITE | VGA_COLOR_BLUE << 4);

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}


void vga_init() {
	for(uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		buffer[i] = ' ' | color << 8;
	row = 0;
	column = 0;
	update_cursor(column, row);
}

void vga_scroll() {
	for(uint16_t i = 0; i < 24*80; ++i) {
		buffer[i] = buffer[i+80];
	}
	for(uint16_t i = 24*80; i < 25*80; ++i) {
		buffer[i] = ' ' | color << 8;
	}
	row = 24;
	column = 0;
}

void vga_delete() {
	uint16_t pos = (row * VGA_WIDTH + column);
	if(pos <= 0) return;

	buffer[pos-1] = ' ' | color << 8;
	column--;

	if(column == -1) {
		column = 79;
		row--;
	}

	update_cursor(column, row);
}

void vga_putch(char c) {
	if(column >= 80) {
		row++;
		column = 0;
	}

	if(row >= 25) {
		vga_scroll();
	}

	if(c == '\n') {
		row++;
		column = 0;

		if(row >= 25) {
			vga_scroll();
		}
	} else {
		buffer[row * VGA_WIDTH + column] = c | color << 8;
		column++;
	}

	update_cursor(column, row);
}
