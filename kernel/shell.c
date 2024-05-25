#include <stdio.h>
#include <kernel/shell.h>
#include <kernel/keyboard.h>
#include <kernel/vga.h>
#include <kernel/pic.h>

void shell() {
   timer_wait(50);
   printf("Welcome to Nashi!");
   timer_wait(50);
   vga_init();
   printf("$ ");
   for(;;)
   {
      char c = keyboard_getchar();
      // If we hit a modifer key, don't try and print it. After hitting enter, redraw our "cursor" ($)
      if(c == '\b') {
	 vga_delete();
      }
      else if(c == '\n') {
	 printf("\n$ ");
      }
      else if(c) {
	 printf("%c", c);
      }
   }  
}
