#ifndef __VERSION_H__
#define __VERSION_H__

int vercode;

#define VERSION_MASK   0xFF
#define VER_MAJOR_OFST    4
#define VER_MAJOR_MASK 0xF0
#define VER_MINOR_OFST    0
#define VER_MINOR_MASK 0x0F

int ver_major (int ver);
int ver_minor (int ver);

int version(int major, int minor);


#endif /* __VERSION_H__ */