#ifndef __VERSION_H__
#define __VERSION_H__

#define VER_NUM_SIZE            8 /* 8bit: 0 ~ 255 */
#define VER_NUM_MAX             ((1 << VER_NUM_SIZE) - 1)

#define VER_MAJOR_OFFSET        (3 * VER_NUM_SIZE)
#define VER_MINOR_OFFSET        (2 * VER_NUM_SIZE)
#define VER_RELEASE_OFFSET      (1 * VER_NUM_SIZE)
#define VER_PATH_OFFSET         (0 * VER_NUM_SIZE)

#define VER_MAJOR_MASK          (VER_NUM_MAX << VER_MAJOR_OFFSET)
#define VER_MINOR_MASK          (VER_NUM_MAX << VER_MINOR_OFFSET)
#define VER_RELEASE_MASK        (VER_NUM_MAX << VER_RELEASE_OFFSET)
#define VER_PATH_MASK           (VER_NUM_MAX << VER_PATH_OFFSET)

#define VER_MASK                (VER_MAJOR_MASK | VER_MINOR_MASK | VER_RELEASE_MASK | VER_PATH_MASK )

#define VERSION(x, y, z, n) ((x << VER_MAJOR_OFFSET | y << VER_MINOR_OFFSET |  \
                              z << VER_RELEASE_OFFSET | n << VER_PATH_OFFSET))

#define VER_MAJOR(version)      ((version & VER_MAJOR_MASK) >> VER_MAJOR_OFFSET)
#define VER_MINOR(version) 	    ((version & VER_MINOR_MASK) >> VER_MINOR_OFFSET)
#define VER_RELEASE(version)    ((version & VER_RELEASE_MASK) >> VER_RELEASE_OFFSET)
#define VER_PATCH(version)	    ((version & VER_PATH_MASK) >>  VER_PATH_OFFSET)


typedef unsigned int version_t;

#endif /* __VERSION_H__ */