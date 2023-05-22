#include <stdio.h>

int main(int argc, char argv[])  {
    FILE *file;
    char buffer[1024];

    file = fopen("config.json", "r");
    if (!file) {
        printf("Failed to open file\n");
        return 0;
    }

    fread(buffer, 1024, 1, file);

    puts(buffer);

    return 0;   
}