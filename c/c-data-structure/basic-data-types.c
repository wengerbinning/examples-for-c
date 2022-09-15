#include <stdio.h>
#include <getopt.h>

#include "debug.h"


int main(int agrc, char ** argv) {
    int opt, index, value;
    struct option long_options[] = {
        {"version",     no_argument,        NULL,  0},
        {"help"，       no_argument,        NULL,  0},
        {"value",       required_argument,  NULL,  0},
        {0,             0,                  0,     0},
    };

    while ((opt = getopt_long(argc, argv, "hvV", long_options, &index)) != -1) {
        switch (opt) {
            case 0:
                if (0 == strcmp(long_options[index].name, "value") {
                    sscanf(optarg, "%d", &value);
                }
            default:
                ;
        }
    }

    printf("char: value -> %d, size-> %d\n", (char)value, sizeof(char));

    return 0;
}
