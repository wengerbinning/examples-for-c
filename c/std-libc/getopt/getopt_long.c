#include <stdio.h>
#include <getopt.h>

#include "develop.h"

struct param_t {
    char verbose;
};

enum options_idx {
    OPT_HELP,
    OPT_VERISON,

    __OPT_MAX
};

static char short_options[] = "hvV";
static struct option long_options[__OPT_MAX] = {
    [OPT_HELP] =    {"help",    no_argument, 0, 0},
    [OPT_VERISON] = {"version", no_argument, 0, 0},
};


int parse_long_options (const struct option *opt, int idx, struct param_t *param) {
    switch (idx) {
    case OPT_HELP:
        info("handling long option help");
        break;
    case OPT_VERISON:
        info("handling long option version");
        break;
    default:
        warnning("Unknown handling this option: --%s", opt[idx].name);
    }
}

int main (int argc, char *argv[]) {
    int opt, idx;
    struct param_t param;

    while ((opt = getopt_long(argc, argv, short_options, long_options, &idx)) != -1) {
        switch (opt) {
        /* Handing long options. */
        case 0:
            parse_long_options(long_options, idx, &param);
            break;
        
        /* Handling short options. */
        case 'h':
            info("handling short option help");
            break;
        case 'V':
            info("handling short option version");
            break;
        /* Handle invalid option. */
        case '?':
        /* Handle unknown valid option. */
        default:
            warnning("Unknown handling this option: -%c", opt);
        }
    } 

    return 0;
}

