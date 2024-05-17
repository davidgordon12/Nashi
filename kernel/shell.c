#include <stdio.h>
#include <kernel/keyboard.h>
#include <kernel/shell.h>

void shell() {
   for(;;)
   {
      char c = keyboard_getchar();
      // If we hit a modifer key, don't try and print it. After hitting enter, redraw our "cursor" ($)
      if (c)
	 printf("%c", c);
   }  
}
