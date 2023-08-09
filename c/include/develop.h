#ifndef __DEVELOP_H__
#define __DEVELOP_H__

#define error(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define warning(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define info(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)

#define debug(fmt, ...) \
	printf(fmt"\n", ## __VA_ARGS__)


#define content(fmt, ...) \
	printf(fmt, ## __VA_ARGS__)

#endif /* __DEVELOP_H__ */
