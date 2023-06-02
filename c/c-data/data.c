#include <stdio.h>

int ip_checksum(void *p) {
    unsigned int checksum = 0;
    unsigned short value;

    unsigned char *tmp = p;
    for (int i = 0; i < 20; i+=2) {
        value = (*(tmp+i) << 8) + (*(tmp + i + 1));
        printf("%04X ", value);
        checksum += value;
   }

   checksum = 0xFFFF - (((checksum >> 16) & 0xFFFF) + (checksum & 0xFFFF));

   printf("\n %04X\n", 0xFFFF - checksum);
}



int main(int agrc, char *argv[]) {
    unsigned char frame[]= {0x45, 0x00, 0x00, 0x34, 0x92, 0x62, 0x40, 0x00, 0x40, 0x06, 0x00, 0x00, 0x0a ,0x64, 0x00, 0x0a, 0x23, 0xf7, 0xa4, 0x37};

    ip_checksum(frame);


    return 0;
}