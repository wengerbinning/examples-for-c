#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "develop.h"

struct param_t {
	char *prog;
	int verbose;
	int server;
	char interface[128];
	char address[64];
};

enum options_idx {
	OPT_HELP,
	OPT_VERISON,
	/* Common option */
	OPT_VERBOSE,
	OPT_INTEFACE,
	OPT_BIND,
	OPT_PORT,
	/* Server option */
	OPT_SERVER,
	/* Client option */
	OPT_PARALLEL,

	__OPT_MAX
};

static char prog_name[] ="socket";
static char short_options[] = "b:hi:psvPV";
static struct option long_options[__OPT_MAX] = {
	[OPT_HELP]     = {"help",       no_argument,       0, 0},
	[OPT_VERISON]  = {"version",    no_argument,       0, 0},
	[OPT_VERBOSE]  = {"verbose",    optional_argument, 0, 0},
	[OPT_INTEFACE] = {"interface",  required_argument, 0, 0},
	[OPT_PORT]     = {"port",       required_argument, 0, 0},
	[OPT_BIND]     = {"bind",       required_argument, 0, 0},
	[OPT_SERVER]   = {"server",     no_argument,       0, 0},
	[OPT_PARALLEL] = {"parallel",   required_argument, 0, 0},
};

int help (const char *prog);
int version (const char *prog);
int dump_param (const struct param_t *param);

static inline int parse_long_options (const struct option *opt, int idx, struct param_t *param) {
	switch (idx) {
	case OPT_HELP:
		help(prog_name);
		return 0;

	case OPT_VERISON:
		version(prog_name);
		return 0;
	
	case OPT_INTEFACE:
		strncpy(param->interface, optarg, sizeof(param->interface));
		break;
	case OPT_SERVER:
		param->server = 1;
		break;

	default:
		warning("Unknown handling this option: --%s", opt[idx].name);
	}
}

int main (int argc, char *argv[]) {
	int opt, idx;
	struct param_t param;
	char buffer[64];

	if (argc <= 1) {
		help(argv[0]);
		return 0;
	}

	while ((opt = getopt_long(argc, argv, short_options, long_options, &idx)) != -1) {
		switch (opt) {
		/* Handing long options. */
		case 0:
			parse_long_options(long_options, idx, &param);
			break;

		/* Handling short options. */
		case 'b':
			strncpy(param.address, optarg, sizeof(param.address));
			break;
		case 'h':
			help(argv[0]);
			return 0;

		case 'i':
			strncpy(param.interface, optarg, sizeof(param.interface));
			break;
		case 's':
			param.server = 1;
			break;
		case 'V':
			version(argv[0]);
			return 0;

		/* Handle invalid option. */
		case '?':
		/* Handle unknown valid option. */
		default:
			warning("Unknown handling this option: -%c", opt);
			help(argv[0]);
			return 0;
		}
	} 

	dump_param(&param);

    pf_packet_packet_all(param.interface);




	return 0;
}



int help (const char *prog) {
	info("%s - This is a network debug tools.\n", prog);
	info("Usage: %s [OPTIONS]\n", prog);
	info("\nOptions:\n");
	info("\t-h, --help                  \tDisplay help information and exit");
	info("\t-i, --interface INTERFACE   \tBind interface");
	info("\t-v, --verbose               \tPrint detial inforation");
	info("\t-V, --version               \tDisplay version information and exit");
	return 0;
}

int version (const char *prog) {
	info("%s Version v0.0.0.1", prog);
	return 0;
}

int dump_param (const struct param_t *param) {
	debug("Display param value:");
	info("\tinterface: %s", param->interface);
	info("\tserver : %d", param->server);
	return 0;
}