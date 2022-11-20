#include <stdio.h>

#include "binary.h"


int test_binary (int a, int b, int mask) {

	if(CMP_LES_THAN(a, b, mask)) {
		printf(" A(0x%04X) is less than B(0x%04X) in the mask(0x%04X) range\n", a, b, mask);
	} else if (CMP_EQU(a, b, mask)) {
		printf(" A(0x%04X) is equal to B(0x%04X) in the mask(0x%04X) range\n", a, b, mask);
	} else if (CMP_GRE_THAN(a, b, mask)) {
		printf(" A(0x%04X) is greater to B(0x%04X) in the mask(0x%04X) range\n", a, b, mask);
	} else {
		printf("[ERROR] Found a error condition A (0x%04X), B(0x%04X), mask(0x%04X)\n", a, b, mask);
	}

	/*
	if (TEST_BITS_CHANGES(1, a, b)) {
		printf("There is some flag bits is set: 0x%04X to 0x%04X -> 0x%04X\n", a, b, CMP_SET_BITS(a,b));
	}

	if (TEST_BITS_CHANGES(0, a, b)) {
		printf("There is some flag bits is unset: 0x%04X to 0x%04X -> 0x%04X\n", a, b, CMP_UNSET_BITS(a,b));
	}

	if (TEST_BITS_SAMA(1, a, b)) {
		printf("All flag bits is same 1, 0x%04X and 0x%04X\n", a, b);
	}

	if (TEST_BITS_SAMA(0, a, b)) {
		printf("All flag bits is same 0, 0x%04X and 0x%04X\n", a, b);
	}
	*/
	printf("%04X\n", GET_BITS_SAME(0, a, b));

	return 0;
}


int main (int argc, char *argv[]) {
	int i, j, mask = 0x00F0;

	for (i = 0; i < 0x00F0F; i++) {
		for (j = 0; j < 0x000F; j++) {
			test_binary(i, j, mask);
		}
	}

	return 0;
}
