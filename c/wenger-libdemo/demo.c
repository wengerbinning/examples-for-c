#include <stdio.h>
#include <stdarg.h>

int demo_println (const char *fmt, ...) {
	char buffer[1024];
	va_list valist;
	
	va_start(valist, fmt);
	vsprintf(buffer, fmt, valist);
	va_end(valist);

    printf("%s\n", buffer);
 
 	return 0;
}
