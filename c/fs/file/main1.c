#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define VER_FIELD_MASK  0xFF
#define VER_MAJOR_OFST    24
#define VER_MINOR_OFST    16
#define VER_PHASE_OFST     8
#define VER_PATCH_OFST     0

#define VER_MAJOR(n)     ((n >> VER_MAJOR_OFST) & VER_FIELD_MASK)
#define VER_MINOR(n)     ((n >> VER_MINOR_OFST) & VER_FIELD_MASK)
#define VER_PHASE(n)     ((n >> VER_PHASE_OFST) & VER_FIELD_MASK)
#define VER_PATCH(n)     ((n >> VER_PATCH_OFST) & VER_FIELD_MASK)

#define VERSTR(n) VER_MAJOR(n),VER_MINOR(n), VER_PHASE(n), VER_PATCH(n)


int main (int argc, char *argv[]) {

    printf("");
    return 0;
}

