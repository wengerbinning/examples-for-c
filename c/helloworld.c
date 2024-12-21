#include <stdio.h>

int main (int argc, char *argv[]) {

	printf("Hello, World!\n");

	int chunk = 4;
	int devsize = 56;
	int erasecount;

	int i, blk;

	int offset = 4;
	int size = 52;

	printf("block: %d (x %d = %d) <= %d\n", devsize/chunk, chunk, (devsize/chunk)*chunk, devsize );


    for (i = 0; i < devsize/chunk; i++) {
        size_t eofst, esize;

		eofst = i * chunk;
		esize = eofst + chunk;

        if (eofst < offset)
            continue;

        if (size && ((offset + size) < esize)) {
            break;
        }



		printf("%02d: offset = %2d, chunk = %d; %d %d\n", i, eofst, chunk, esize				, offset + size);

        // erase.start = ofst;
        // erase.length = mtd.erasesize;
        // if (ioctl(fd, MEMERASE, &erase) < 0) {
        //     prov_error(0, "failed to erase block %ld (0x%08x)!", blk, i);
        // }
    }

	return 0;
}




