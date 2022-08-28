#include <stdio.h>
#include <getopt.h>

#include "debug.h"

int main(int argc, char **argv) {
    int opt, index;
    struct option long_options[] = {
        {"version",     no_argument,       0, 0},
        {"help",        no_argument,       0, 0},
        {"interface",   required_argument, 0, 0},
        {"file",        optional_argument, 0, 0},
        {0,             0,                 0, 0},
    };

    while ((opt = getopt_long(argc, argv, "HIV", long_options, &index)) != -1) {
        debug(DEBUG_LEVEL_B, "index: %d, opt: %d", index, opt);
        switch (opt) {
            case 0:
                if (long_options[index].has_arg == no_argument) {
                    info(INFO_LEVEL_B, "name: %s", long_options[index].name);
                } else {
                    info(INFO_LEVEL_B, "name: %s, value: %s", long_options[index].name, optarg);
                }
                break;
            case 'I':
                info(INFO_LEVEL_B, "name: %c, value: %s",opt, optarg);
                break;
            default:
                error(ERROR_LEVEL_A, "parse arguments is error");
        }
    }



        


    return 0;
}
