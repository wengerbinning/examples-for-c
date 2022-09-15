// vim: set ts=4
#include <stdio.h>

#define AUTHOR	"Wenger Binning"

int main() {
	printf("string size %ld, length %ld, content: %s\n", sizeof(AUTHOR),strlen(AUTHOR), AUTHOR);

	return 0;
}
