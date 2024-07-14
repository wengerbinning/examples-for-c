#include <stdio.h>

#include "errcode.h"


int main() {
    int code = ERR_REQUEST;
    ERROR_SET_MSG(ERR_REQUEST, "hello");
    printf("error: %d (%s)\n", code, ERROR_GET_MSG(code));

    return 0;
}