#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv) {

    system("./environment");

    return 0;
}