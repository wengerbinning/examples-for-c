#include <stdio.h>


typedef struct deivce {
    unsigned int flags;
} device_t;


#define DEVF_ATTR_OFST           8
#define DEVF_ATTR_MASK  0x0000FFFF
#define ATTR2DEVF(a) (((a) << DEVF_ATTR_OFST) & DEVF_ATTR_MASK)
#define DEVF2ATTR(f) (((f) & DEVF_ATTR_MASK) >> DEVF_ATTR_OFST)
#define DEV_GET_ATTR(dev) DEVF2ATTR(dev->flags)
#define DEV_SET_ATTR(dev, a)       (dev->flags |=  ATTR2DEVF(a))
#define DEV_UNSET_ATTR(dev, a)     (dev->flags &= ~ATTR2DEVF(a))
#define DEV_CHECK_ATTR(dev, a) (1 && (dev->flags & ATTR2DEVF(a)))

/* Device Type */
#define DEVF_TYPE_OFST          16
#define DEVF_TYPE_MASK  0x00FF0000
#define TYPE2DEVF(t) (((t) << DEVF_TYPE_OFST) & DEVF_TYPE_MASK)
#define DEVF2TYPE(f) (((f) & DEVF_TYPE_MASK) >> DEVF_TYPE_OFST)
#define DEV_GET_TYPE(dev) DEVF2TYPE(dev->flags)
#define DEV_SET_TYPE(dev, a)       (dev->flags |=  TYPE2DEVF(a))
#define IMG_UNSET_TYPE(dev, a)     (dev->flags &= ~TYPE2DEVF(a))
#define DEV_CHECK_TYPE(dev, a) (1 && (dev->flags & TYPE2DEVF(a)))

#define DEV_NETWORK    (0x01 << 0)
#define DEV_ROUTER     (0x01 << 1)
#define DEV_SWITCH     (0x01 << 2)

int main (int argc, char *argv[]) {
    device_t device, *dev = &device;
    printf("device flags: 0x%08X\n", dev->flags);

    DEV_SET_TYPE(dev,DEV_ROUTER);

    printf("device flags: 0x%08X\n", dev->flags);
    printf("device attr:  0x%04X\n", DEV_GET_A                                                                          TTR(dev));

    printf("device type:  0x%04X\n", DEV_GET_TYPE(dev));
}