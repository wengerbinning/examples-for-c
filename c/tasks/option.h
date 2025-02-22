#ifndef __OPTION_H__
#define __OPTION_H__

typedef struct context {
    char *cmdline;
} context_t;

#ifndef OPTIONAPI
static struct context context;
#endif


int parse_options (context_t *ctx, int argc, char *argv[]);

#endif /* __OPTION_H__ */