#ifndef __RETURN_MESSAGE_H__
#define __RETURN_MESSAGE_H__

#define ABS(code)   ((code < 0) ? (-code) : code)

/* Normal Return Code */
#define DEFAULT_NORMSG "Unknown status"
#define NOR_MSG(name)   _NOR_MSG(name)
#define _NOR_MSG(name)  (normsg_ ## name)

#define __NOR_SET_MSG(name, code, msg)  NOR_MSG(name)[code] = msg
#define __NOR_GET_MSG(name, code) \
    (NOR_MSG(name)[code]) ? (NOR_MSG(name)[code]) : DEFAULT_NORMSG

#define _STAT_NOR_MSG_INIT(name)  const char *_NOR_MSG(name)[]
#define STATIC_NOR_MSG_INIT(name)  static _STAT_NOR_MSG_INIT (name)
#define _GLOB_NOR_MSG_INIT(name, cnt) const char *NOR_MSG(name)[cnt]
#define GLOBAL_NOR_MSG_INIT(name, cnt) extern _GLOB_NOR_MSG_INIT (name, cnt)

#define NOR_MSG_SET(code, msg) [code] = msg
#define NOR_MSG_SIZE(name)  (sizeof(NOR_MSG(name)) / sizeof(char *))

#define _NOR_SET_MSG(name, code, msg) \
    (ABS(code) < NOR_MSG_SIZE(name) ? __NOR_SET_MSG(name, ABS(code), msg))
#define _NOR_GET_MSG(name, code) \
    (ABS(code) < NOR_MSG_SIZE(name) ? \
        __NOR_GET_MSG(name, ABS(code)) : DEFAULT_NORMSG)

/* Error Return Code */
#define DEFAULT_ERRMSG "Unknown error"
#define ERR_MSG(name)   _ERR_MSG(name)
#define _ERR_MSG(name)  (errmsg_ ## name)

#define __ERR_SET_MSG(name, code, msg)  ERR_MSG(name)[code] = msg
#define __ERR_GET_MSG(name, code) \
    (ERR_MSG(name)[code]) ? (ERR_MSG(name)[code]) : DEFAULT_ERRMSG

#define _STAT_ERR_MSG_INIT(name) const char *_ERR_MSG(name)[]
#define STATIC_ERR_MSG_INIT(name) static _STAT_ERR_MSG_INIT (name)
#define _GLOB_ERR_MSG_INIT(name, cnt) const char *ERR_MSG(name)[cnt]
#define GLOBAL_ERR_MSG_INIT(name, cnt) extern _GLOB_ERR_MSG_INIT (name, cnt)

#define ERR_MSG_SET(code, msg)  [code] = msg
#define ERR_MSG_SIZE(name)  (sizeof(ERR_MSG(name)) / sizeof(char *))

#define _ERR_SET_MSG(name, code, msg) \
    (ABS(code) < ERR_MSG_SIZE(name) ? __ERR_SET_MSG(name, ABS(code), msg))
#define _ERR_GET_MSG(name, code) \
    (ABS(code) < ERR_MSG_SIZE(name) ? \
        __ERR_GET_MSG(name, ABS(code)) : DEFAULT_ERRMSG)

/* General Return Code */
#define _RET_SET_MSG(name, code, msg) \
    ((code < 0) ? _ERR_SET_MSG(name, code, msg) : _NOR_SET_MSG(name, code, msg))
#define _RET_GET_MSG(name, code) \
    ((code < 0) ? _ERR_GET_MSG(name, code) : _NOR_GET_MSG(name, code))

#define ERRCODE(code)   (-code)
#define NORCODE(code)   ( code)


/** Genernal Return Code Message API
 ******************************************************************************
 Error Return Code Message

  * STATIC_ERR_MSG_INIT(name)
  * GLOBAL_ERR_MSG_INIT(name, count)
  * ERR_MSG_SET(code, message)

  * _ERR_SET_MSG(name, code, message)
  * _ERR_GET_MSG(name, code)

 Normal Status Returen Code Message

  * STATIC_NOR_MSG_INIT(name)
  * GLOBAL_NOR_MSG_INIT(name, count)
  * ERR_NOR_SET(code, message)

  * _NOR_SET_MSG(name, code, message)
  * _NOR_GET_MSG(name, code)

 General Return Code Message

  * _RET_SET_MSG(name, code, message)
  * _RET_GET_MSG(name, code)

 For Example A:

  > test.h
  >> GLOBAL_ERR_MSG_INIT(test, 10);
  >> GLOBAL_NOR_MSG_INIT(test, 10);
  >>
  >> #define ERR_GET_MSG(code) _ERR_GET_MSG(test, code)
  >> #define NOR_GET_MSG(code) _NOR_GET_MSG(test, code)
  >> #define RET_GET_MSG(code) _RET_GET_MSG(test, code)
  > test.c
  >> GLOBAL_ERR_MSG_INIT(test, 10) = {
  >>     ERR_MSG_SET(1, "parameter error"),
  >> };
  >>
  >> GLOBAL_NOR_MSG_INIT(test, 10) = {
  >>     ERR_NOR_SET(1, "Need send message"),
  >> };

 For Example B:

   > test.h
   >> STATIC_ERR_MSG_INIT(test) = {
   >>   ERR_MSG_SET(1, "Parameter error"),
   >> };
   >> STATIC_NOR_MSG_INIT(test) = {
   >>   ERR_NOR_SET(1, "Need send message"),
   >> };
   >>
   >> #define ERR_GET_MSG(code) _ERR_GET_MSG(test, code)
   >> #define NOR_GET_MSG(code) _NOR_GET_MSG(test, code)
   >> #define RET_GET_MSG(code) _RET_GET_MSG(test, code)

 *************************************************************************** */

#endif /* __RETURN_MESSAGE_H__ */
