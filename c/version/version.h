#ifndef __VERSION_H__
#define __VERSION_H__

int vercode;

#define VER_FIELD_MASK  0xFF
#define VER_MAJOR_OFST    24
#define VER_MINOR_OFST    16
#define VER_PHASE_OFST     8
#define VER_PATCH_OFST     0

#define VER_MAJOR(ver)  ((ver >> VER_MAJOR_OFST) & VER_FIELD_MASK)
#define VER_MINOR(ver)  ((ver >> VER_MINOR_OFST) & VER_FIELD_MASK)
#define VER_PHASE(ver)  ((ver >> VER_PHASE_OFST) & VER_FIELD_MASK)
#define VER_PATCH(ver)  ((ver >> VER_PATCH_OFST) & VER_FIELD_MASK)

#define VERSION(a, b, m, n) \
    ((a & VER_FIELD_MASK << VER_MAJOR_OFST) | \
     (b & VER_FIELD_MASK << VER_MINOR_OFST) | \
     (m & VER_FIELD_MASK << VER_PHASE_OFST) | \
     (n & VER_FIELD_MASK << VER_PATCH_OFST))

unsigned int ver_major (unsigned int ver);
unsigned int ver_minor (unsigned int ver);
unsigned int ver_phase (unsigned int ver);
unsigned int ver_patch (unsigned int ver);

unsigned int version (
    unsigned int major, unsigned int minor,
    unsigned int phase, unsigned int patch);


#endif /* __VERSION_H__ */