#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include <stdbool.h>

struct context {
    
    FILE *stream;
    int form_count;

    char *content_boundary;
    char *content_length;
};



struct form {
    size_t offset;
};

#define STREAM_TXT "data.txt"
#define STREAM_BIN "data.bin"



#define CONTENT_BOUNDARY  "@@@@"

#define STRCMP(s1, s2) (0 == strncmp(s1, s2, strlen(s2)))


#endif /* __IOSTREAM_H__ */