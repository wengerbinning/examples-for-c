#include <stdio.h>
#include <regex.h>


#include "content-type.h"



#define STRCMP(s1, s2) (0 == strncmp(s1, s2, strlen(s2)))







int main(int argc, char *argv[]) {
    int i = 0;
    int content;
    char *buf;
    char *charset, *boundary;



    printf("# paremeter %d\n", argc);
    // printf("charset: %s\n", charset);
    for (i = 0; i < argc; i++) {
        buf = argv[i];
        charset = NULL, boundary=NULL;
        content = content_type_parse(buf, &charset, &boundary);
        printf("%d %s -- %d\n", i, buf, content);
        if (charset)
            printf("charset: %s\n", charset);

        if (boundary)
            printf("boundary: %s\n", boundary);
    }

    return 0;
}