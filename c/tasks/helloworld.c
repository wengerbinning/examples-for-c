#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
    while(1) {
        char *buf = malloc(512);
        printf("init\n");
        sleep(10);
        free(buf);
        printf("exit\n");
        sleep(10);
    }
    return 0;
}