#ifndef __RETURN_CODE_H__
#define __RETURN_CODE_H__

/* Normal Return Code */
#define NOR_MSG(name)                   _NOR_MSG(name)
#define _NOR_MSG(name)                  (normsg_ ## name)
#define __NOR_SET_MSG(name, code, msg)  NOR_MSG(name)[code] = msg
#define __NOR_GET_MSG(name, code)       NOR_MSG(name)[code]

#define __STAT_NOR_MSG_INIT(name)      const char *_NOR_MSG(name)[]
#define STATIC_NOR_MSG_INIT(name)      static __STAT_NOR_MSG_INIT (name)
#define __GLOB_NOR_MSG_INIT(name, cnt) const char *NOR_MSG(name)[cnt]
#define GLOBAL_NOR_MSG_INIT(name, cnt) extern __GLOB_NOR_MSG_INIT (name, cnt)
#define NOR_MSG_SET(code, msg)         [code] = msg

/* Error Return Code */
#define ERR_MSG(name)                   _ERR_MSG(name)
#define _ERR_MSG(name)                  (errmsg_ ## name)
#define __ERR_SET_MSG(name, code, msg)  ERR_MSG(name)[code] = msg
#define __ERR_GET_MSG(name, code)       ERR_MSG(name)[code]

#define __STAT_ERR_MSG_INIT(name)      const char *_ERR_MSG(name)[]
#define STATIC_ERR_MSG_INIT(name)      static __STAT_ERR_MSG_INIT (name)
#define __GLOB_ERR_MSG_INIT(name, cnt) const char *ERR_MSG(name)[cnt]
#define GLOBAL_ERR_MSG_INIT(name, cnt) extern __GLOB_ERR_MSG_INIT (name, cnt)
#define ERR_MSG_SET(code, msg)         [code] = msg

/* Return Code */
#define __RET_SET_MSG(name, code, msg) \
    ((code < 0) ? \
        __ERR_SET_MSG(name, -(code), msg) : __NOR_SET_MSG(name, code, msg))
#define __RET_GET_MSG(name, code) \
    ((code < 0) ? __ERR_GET_MSG(name, -(code)) : __NOR_GET_MSG(name, code msg))

#endif /* __RETURN_CODE_H__ */