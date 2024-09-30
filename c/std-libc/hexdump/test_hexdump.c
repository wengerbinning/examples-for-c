#include "hexdump.h"

int main(int agrc, char *argv[]) {
    char buffer[1024];

    hexdump(buffer, sizeof(buffer));
    return 0;
}