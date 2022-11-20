#include <stdio.h>

#include "version.h"

int test_version(version_t ver);

int main(int argc, char *argv[]) {
	for (int i = 0; i < 2; i++) {
		for(int j = 0; j < 5; j++) {
			printf(" current x: %d, y: %d, z: 0, n: 0\n", i, j);
			test_version(VERSION(i, j, 0, 0));
		}
	}

	return 0;
}


int test_version(version_t ver) {
		
	printf("current ver: 0x%08X, major 0x%08X, minor 0x%08X, released 0x%08X, patch 0x%08X; ", ver, VER_MAJOR(ver), VER_MINOR(ver), VER_RELEASED(ver), VER_PATCH(ver));
	printf("version string: v%d.%d.%d.%d\n",VER_MAJOR(ver), VER_MINOR(ver), VER_RELEASED(ver), VER_PATCH(ver));
	
	return 0;
}
