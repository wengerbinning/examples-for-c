#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("Hello, World!\n");

	return 0;
}


#if defined(CONFIG_DEBUG) || defined(CONFIG_VERBOSE)
int hexdump(void *ptr, unsigned int size) {
	return 0;
}
#endif /* CONFIG_DEBUG */
