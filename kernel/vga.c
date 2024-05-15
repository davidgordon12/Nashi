#include <kernel/vga.h>
#include <kernel/io.h>

uint16_t* buffer = (uint16_t*)0xB8000;

size_t row = 0; size_t column = 0;

const uint8_t color = (VGA_COLOR_WHITE | VGA_COLOR_BLUE << 4);

void vga_init() {
	for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		buffer[i] = ' ' | color << 8;
}

void vga_putch(char c) {
	buffer[row * VGA_WIDTH + column] = c | color << 8;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_write(char* string) {
	size_t i = 0;
	while(string[i] != '\0')
	{
		if(string[i] == '\n' || column > VGA_WIDTH) {
			row++;
			column = 0;
		}
		else {
			vga_putch(string[i]);
			column++;
		}
		i++;
	}

	update_cursor(column, row);
}

