#ifndef __TEST_H__
#define __TEST_H__

#include "errcode.h"

#define ERR_REQUEST             1
#define ERR_CLIENT              2
#define ERR_NETWORK             3
#define ERR_SERVER              4

#define ERR_NORMAL_BASE         10
#define ERR_NOMEM       (ERR_NORMAL_BASE + 0)
#define ERR_NODEV       (ERR_NORMAL_BASE + 1)

GLOBAL_ERR_MSG_INIT(error, 10);
GLOBAL_ERR_MSG_INIT(normal, 10);


#define _ERR_GET_MSG(code)   \
    (( 0 <= code && code < 10) ? __ERR_GET_MSG(error, code) : \
     (10 <= code && code < 20) ? __ERR_GET_MSG(normal, code - ERR_NORMAL_BASE): \
     NULL)

#define ERR_GET_MSG(code) \
    ((code < 0) ? _ERR_GET_MSG(-code) : _ERR_GET_MSG(code))
#endif /* __TEST_H__ */