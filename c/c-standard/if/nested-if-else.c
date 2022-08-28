#include <stdio.h>

int main(int argc, char *argv[]) {
    

    if (argc < 0) {
        printf("[ERROR] find error\n"); 
    } else
        if (argc == 0) {
            printf("Command is %s\n", argv[0]);
        } else {
            for (int i=0; i < argc; i++) {
                printf("[%02d]\t %s\n", i, argv[i]);
            }
        }
    
    return 0;
}
