#ifndef __DEMO_H__
#define __DEMO_H__

#include <stdio.h>

#define println(fmt, ...)	printf(fmt"\n",##__VA_ARGS__)

int demo_println (const char *fmt, ...); 

#endif /* __DEMO_H__ */
