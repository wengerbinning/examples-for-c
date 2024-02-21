#include<stdio.h>
#include<unistd.h>

int main(int argc, const char *argv[]) {
    pid_t pid = 0;

    pid = fork();

    if( pid == 0 ) {
        execl("/usr/bin/pwd", "/usr/bin/pwd", NULL);
    }

    printf("%d\n",pid);

    return 0;
}
