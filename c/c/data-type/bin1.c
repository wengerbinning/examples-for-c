#include <stdio.h>
#include <stdlib.h>



unsigned int mask(unsigned int ofst, unsigned int bits) {
    unsigned int i, max, mask = 0;
    max = (32 < (ofst + bits)) ? 32 : (ofst + bits);
    for (i = 0; i < max - 1; i++) {
        mask |= (ofst < max - i) ? 0x1 : 0x0;
        mask = mask << 1;
    }
    if (!ofst) mask |= 0x1;
    return mask;
}

unsigned int mask2bits (unsigned int mask) {
    unsigned int ofst = 0, bits = 0;

    while (mask) {
        (bits || (mask & 0x1)) ? bits++ : ofst++;
        mask = mask >> 1;
    }

    return bits;
}


unsigned int mask2ofst (unsigned int mask) {
    unsigned int ofst = 0, bits = 0;

    while (mask) {
        (bits || (mask & 0x1)) ? bits++ : ofst++;
        mask = mask >> 1;
    }

    return ofst;
}

int main (int argc, char *argv[]) {
    int a, b;

    if (!argv[1])
        return 0;

    a = mask2ofst(atoi(argv[1]));
    b = mask2bits(atoi(argv[1]));

    printf("mask %08X, ofst: %d, bits: %d, mask: %08X\n", atoi(argv[1]), a, b, mask(a, b));

    return 0;
}