#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"
#include "develop.h"

char path[] = "packet";

// FIXME: malloc size need free.
char *read_packet (const char *path) {
    FILE *fp;
    int len;
    void *buf;

    fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    

    info("Found file size %dB", len);

    buf = (char  *) malloc(len);
    debug("Malloc %d size, size: %d ", len, sizeof(buf));
    
    fseek(fp, 0, SEEK_SET);
    fread(buf, len, 1, fp);

    hexdump(buf, len);

    fclose(fp);

    return buf;
}




int hexdump (void *ptr, int size) {
    int i;
    char *p;

    content("Print %d bytes data >>> ", size);
    
    for (i = 0; i < size; i++) {
        p = (char *)(ptr + i);
        if ((i % 16) == 0) {
            content("\n0x%04X: %02X", i, *p);
        } else if ((i % 2) == 0) {
            content(" %02X", *p);
        } else {
            content("%02X", *p);
        }
    }
    info("\nover");

    return 0;
}