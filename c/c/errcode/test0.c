#include <stdio.h>

#include "errcode.h"
#include "test.h"

int test();

int main() {
    int code = -ERR_NODEV;
    // ERR_SET_MSG(error, ERR_REQUEST, "hello");
    printf("error: %d (%s)\n", code, ERR_GET_MSG(code));
    test();
    return 0;
}