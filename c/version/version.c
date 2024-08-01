#include "version.h"

int vercode;

unsigned int ver_major (unsigned int ver) {
    return (ver >> VER_MAJOR_OFST) & VER_FIELD_MASK;
}

unsigned int ver_minor (unsigned int ver) {
    return (ver >> VER_MINOR_OFST) & VER_FIELD_MASK;
}

unsigned int ver_phase (unsigned int ver) {
    return (ver >> VER_PHASE_OFST) & VER_FIELD_MASK;
}

unsigned int ver_patch (unsigned int ver) {
    return (ver >> VER_PATCH_OFST) & VER_FIELD_MASK;
}

unsigned int version (unsigned int major, unsigned int minor,
    unsigned int phase, unsigned int patch)
{
    unsigned int version = 0;

    version |= ((major & VER_FIELD_MASK) << VER_MAJOR_OFST);
    version |= ((minor & VER_FIELD_MASK) << VER_MINOR_OFST);
    version |= ((phase & VER_FIELD_MASK) << VER_PHASE_OFST);
    version |= ((patch & VER_FIELD_MASK) << VER_PATCH_OFST);

    return version;
}