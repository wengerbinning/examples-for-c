#include <stdio.h>

#define DEBUG

#if defined(DEBUG) && defined(DEBUG_LEVEL)
#define debug(level,fmt, ...)                                                 \
do {                                                                          \
    if (level >= DEBUG_LEVEL) {                                               \
        printf("[ DEBUG %d ] "fmt"\n", level, ##__VA_ARGS__);                 \
    }                                                                         \
} while(0)

#elif defined(DEBUG) && !defined(DEBUG_LEVEL)
#define debug(level, fmt, ...)                                                \
do {                                                                          \
    printf("[ DEBUG %d ] "fmt"\n", level, ##__VA_ARGS__);                     \
} while(0)  

#else
#define debug(level, fmt, ...) do {} while(0)   

#endif





int main(int argc,char *argv[]) {
    
    debug(3,"run in %s", __func__);


    debug(4, "return form %s", __func__);
    return 0;
}
