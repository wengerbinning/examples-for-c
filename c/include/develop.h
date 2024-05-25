#ifndef __DEVELOP_H__
#define __DEVELOP_H__

#define devel_error(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define devel_warning(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define devel_notice(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define devel_note(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define devel_debug(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define error    devel_error
#define warning  devel_warning
#define notice   devel_notice
#define note     devel_note
#define debug    devel_debug

#endif /* __DEVELOP_H__ */
