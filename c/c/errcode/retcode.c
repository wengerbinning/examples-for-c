
#include "test.h"

__GLOB_ERR_MSG_INIT(error, 10) = {
    ERR_MSG_SET(ERR_REQUEST, "request error"),
    ERR_MSG_SET(ERR_CLIENT,   "client error"),
    ERR_MSG_SET(ERR_NETWORK, "network error"),
    ERR_MSG_SET(ERR_SERVER,   "server error"),
};

__GLOB_ERR_MSG_INIT(normal, 10) = {
    ERR_MSG_SET(0, "no memory"),
    ERR_MSG_SET(1, "no device"),
};