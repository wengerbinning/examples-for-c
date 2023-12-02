#include "version.h"

int vercode;


int ver_major (int ver) {
    int version = ver & VERSION_MASK;
    int major = (version & VER_MAJOR_MASK) >> VER_MAJOR_OFST;
    return major;
}

int ver_major (int ver) {
    int version = ver & VERSION_MASK;
    int minor = (version & VER_MINOR_MASK) >> VER_MINOR_OFST;
    return minor;
}

int version(int major, int minor) {
    int version = 0;
    version |= (minor & VER_MINOR_MASK) << VER_MINOR_OFST;
    version |= (major & VER_MAJOR_MASK) << VER_MAJOR_OFST;
}