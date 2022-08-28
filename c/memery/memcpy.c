#include <stdio.h>

int main(int argc, char *argv[]) {
    char str[128] = {0};
    
    memcpy(str, "12345i\03232", 127);
    printf("(%d[%d])%s\n", sizeof(str), strlen(str), str);

    return 0;
}
