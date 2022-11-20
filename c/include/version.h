#ifndef __VERSION_H__
#define __VERSION_H__

typedef unsigned int version_t;

#define __VER(x)	(x & 0xFF)

/* major version */
#define VER_MAJOR_OFFSET	24
#define VER_MAJOR_MASK		0xFF000000
/* minor version */
#define VER_MINOR_OFFSET	16
#define VER_MINOR_MASK		0x00FF0000
/* released version */
#define VER_RELEASED_OFFSET	 8
#define VER_RELEASED_MASK	0x0000FF00
/* patch version */
#define VER_PATCH_OFFSET	 0
#define VER_PATCH_MASK		0x000000FF

#define VERSION(x, y, z, n)   (version_t) 	\
	((__VER(x) << VER_MAJOR_OFFSET) | 		\
	 (__VER(y) << VER_MINOR_OFFSET) |		\
	 (__VER(z) << VER_RELEASED_OFFSET) |	\
	 (__VER(n) << VER_PATCH_OFFSET))

#define VER_MAJOR(ver)		((((version_t) ver) & VER_MAJOR_MASK) >> VER_MAJOR_OFFSET)
#define VER_MINOR(ver)		((((version_t) ver) & VER_MINOR_MASK) >> VER_MINOR_OFFSET)
#define VER_RELEASED(ver)	((((version_t) ver) & VER_RELEASED_MASK) >> VER_RELEASED_OFFSET)
#define VER_PATCH(ver)		((((version_t) ver) & VER_PATCH_MASK) >> VER_PATCH_OFFSET)


#endif /* __VERSION_H__ */
