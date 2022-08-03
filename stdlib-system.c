#include <stdlib.h>
// snprintf
#include <stdio.h>
// getpid
#include <unistd.h>

int main(int argc, char **argv) {
    char buffer[64] = {0};
    
    snprintf(buffer, sizeof(buffer), "mkdir -p /tmp/process/%d", getpid());

    system(buffer);
    
    return 0;
}