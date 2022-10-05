#include <stdio.h>

#include "version.h"

version_t version = VERSION(233,0,0,1);

int main(int argc, char *argv[]) {
    printf("version_t format: <major>.<minor>.<release>.<path>\n");
    printf("Version number size %u bit (%u ~ %u)\n", VER_NUM_SIZE, 0, VER_NUM_MAX);
    printf("Current Version %x， Max Version %x\n", version, VER_MASK);
    printf("Major Version : %d\n", VER_MAJOR(version));
    printf("Minor Version : %d\n", VER_MINOR(version));
    printf("Release Version : %d\n", VER_RELEASE(version));
    printf("Path Version : %d\n", VER_PATCH(version));

    return 0;
}



