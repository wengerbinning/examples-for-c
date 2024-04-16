#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv) {
    int i;
    char buf[1024] = {0};

    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    readlink("/proc/self/fd/0", buf, sizeof(buf));
    printf("stdin : %s\n", buf);

    memset(buf, 0, sizeof(buf));
    readlink("/proc/self/fd/1", buf, sizeof(buf));
    printf("stdout: %s\n", buf);

    memset(buf, 0, sizeof(buf));
    readlink("/proc/self/fd/2", buf, sizeof(buf));
    printf("stderr: %s\n", buf);

    

    return 0;
}