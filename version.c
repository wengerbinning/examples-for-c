#include <stdio.h>


#define VER_MAJOR(version) 	((version & 0xFF000000) >> 24)
#define VER_MINOR(version) 	((version & 0x00FF0000) >> 16)
#define VER_RELEASE(version)    ((version & 0x0000FF00) >>  8)
#define VER_PATCH(version)	(version & 0x000000FF)

int main(int argc, char *argv[]) {
    int version = 0x08040201;

    printf("Major Version : %d\n", VER_MAJOR(version));
    printf("Minor Version : %d\n", VER_MINOR(version));
    printf("Release Version : %d\n", VER_RELEASE(version));
    printf("Path Version : %d\n", VER_PATCH(version));
    return 0;
}



