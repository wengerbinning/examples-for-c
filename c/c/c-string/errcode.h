#ifndef __ERRCODE_H__
#define __ERRCODE_H__

#define ERROR_MSG(name) (error_ ## name)
#define _ERROR_SET_MSG(name, code, msg) \
    ERROR_MSG(name)[code] = msg
#define _ERROR_GET_MSG(name, code) \
    ERROR_MSG(name)[code]

#define ERROR_MSG_INIT(name, size) \
    static const char *ERROR_MSG(name)[]
#define ERROR_MSG_SET(code, msg) [code] = msg

#define ERR_REQUEST             1
#define ERR_CLIENT              2
#define ERR_NETWORK             3
#define ERR_SERVER              4

ERROR_MSG_INIT(error) = {
    ERROR_MSG_SET(ERR_REQUEST, "request error"),
    ERROR_MSG_SET(ERR_CLIENT,   "client error"),
    ERROR_MSG_SET(ERR_NETWORK, "network error"),
    ERROR_MSG_SET(ERR_SERVER,   "server error"),
};

#define ERROR_SET_MSG(code , msg)   _ERROR_SET_MSG(error, code, msg)
#define ERROR_GET_MSG(code)         _ERROR_GET_MSG(error, code)





#endif /* __ERRCODE_H__ */