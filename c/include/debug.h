#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define ERROR_LEVEL_MASK    0xFF
#define ERROR_LEVEL_A       1
#define ERROR_LEVEL_B       2
#define ERROR_LEVEL_C       3

#define WARNNING_LEVEL_MASK 0xFF
#define WARNNING_LEVEL_A    1
#define WARNNING_LEVEL_B    2
#define WARNNING_LEVEL_C    3

#define INFO_LEVEL_MASK     0xFF
#define INFO_LEVEL_A        1
#define INFO_LEVEL_B        2
#define INFO_LEVEL_C        3

#if defined(DEBUG)
#define DEBUG_LEVEL_MASK    0xFF
#define DEBUG_LEVEL_A       1
#define DEBUG_LEVEL_B       2
#define DEBUG_LEVEL_C       3
#endif /* DEBUG */

#define error(level, fmt, ...) \
    printf("[%02d ERROR] "fmt"\n",level, ##__VA_ARGS__)

#define warnning(level, fmt, ...) \
    printf("[%02d WARNNING] "fmt"\n",level, ##__VA_ARGS__)

#define info(level, fmt, ...) \
    printf("[%02d INFO] "fmt"\n", level, ##__VA_ARGS__)

#if defined(DEBUG)
#define debug(level, fmt, ...) \
    printf("[%02d DEBUG] "fmt"\n",level, ##__VA_ARGS__)
#else
#define debug(level, fmt, ...) do {} while(0)
#endif /* DEBUG */

#endif /* __DEBUG_H__ */

