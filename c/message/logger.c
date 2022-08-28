#include <time.h>

#define ERROR -1
#define INFO 0
#define DEBUG 1
#define WARNING 2

struct event {
    long timestamp;
    int e_type;
    char *message;
    void *e_data;
};

int logger(int e_type, const char *message)
