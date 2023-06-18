#include <stdio.h>

extern int version(const char *prog) __attribute__((weak));


int main (int argc, char *argv[]) {

	if (version)
		version(argv[0]);
	
	return 0;
}
