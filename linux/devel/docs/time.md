

```c
typedef long          __kernel_long_t;

typedef __kernel_long_t       __kernel_time_t;
typedef __kernel_long_t       __kernel_suseconds_t

#ifndef _STRUCT_TIMESPEC
#define _STRUCT_TIMESPEC
struct timespec {
	__kernel_time_t	tv_sec;			/* seconds */
	long		tv_nsec;		/* nanoseconds */
};
#endif

struct timeval {
	__kernel_time_t		tv_sec;		/* seconds */
	__kernel_suseconds_t	tv_usec;	/* microseconds */
};
```