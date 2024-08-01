#include <stdio.h>

#include "errcode.h"
#include "test.h"

int test() {
    int code = ERR_REQUEST;
    // ERR_SET_MSG(error, ERR_REQUEST, "hello");
    printf("error: %d (%s)\n", code, ERR_GET_MSG(code));

    return 0;
}