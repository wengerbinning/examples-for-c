#ifndef __DEVEL_H__
#define __DEVEL_H__

#define devel_error(code, fmt, ...)       printf(fmt"\n", ## __VA_ARGS__)
#define devel_warning(code, fmt, ...)     printf(fmt"\n", ## __VA_ARGS__)
#define devel_notice(code, fmt, ...)      printf(fmt"\n", ## __VA_ARGS__)
#define devel_note(code, ...)             printf(fmt"\n", ## __VA_ARGS__)
#define devel_debug(code, ...)            printf(fmt"\n", ## __VA_ARGS__)

#define error    devel_error
#define warning  devel_warning
#define notice   devel_notice
#define note     devel_note
#define debug    devel_debug

#endif /* __DEVEL_H__ */
