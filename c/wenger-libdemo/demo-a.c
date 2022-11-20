#include <stdio.h>
#include <stdarg.h>

int demo_println_a (const char *fmt, ...) {
	char buffer[1024];
	va_list valist;

	printf("# run %s in dmeo A\n", __func__);
	
	va_start(valist, fmt);
	vsprintf(buffer, fmt, valist);
	va_end(valist);

    printf("%s\n", buffer);
 
 	return 0;
}
