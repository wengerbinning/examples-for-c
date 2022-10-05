#ifndef __ERROR_H__
#define __ERROR_H__

#define ERROR_LEVEL_MASK    0xFF
#define ERROR_LEVEL_A       1
#define ERROR_LEVEL_B       2
#define ERROR_LEVEL_C       3


#define error(level, fmt, ...) \
    printf("[%02d ERROR] "fmt"\n",level, ##__VA_ARGS__)

#endif /* __ERROR_H__ */
