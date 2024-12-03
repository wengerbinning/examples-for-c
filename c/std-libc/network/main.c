#include <stdio.h>
#include <regex.h>
#include <string.h>
/*

IP Range: 192.168.0.1-192.168.0.100

ipaddr: 192.168.0.1
ipmask: 192.168.0.1/24
iprange 0: 192.168.10.0-255
iprange 1: 192.168.10.1 - 192.168.10.100
subnet: 192.168.0.0/24
submask: 255.255.255.0


    for (i = 0; prov_except_regex[i]; i++) {
        regcomp(&regex, prov_except_regex[i], REG_EXTENDED);
        if (0 == regexec(&regex, str, nmatch, pmatch, 0)) {
            value |= 0x1 << i;
            regfree(&regex);
            break;
        }
        regfree(&regex);

 */


// 256

// 8 8 8 8


struct ipmap {
    struct ipmap *prev, *next;
    int idx, map;
};

struct subnet {
    int addr, mask;
    int idx1, idx2, idx3, idx4;
    struct ipmap cur;

    struct ipmap *static_pool, *active_pool;
    // struct ipmap *reserv_pool, *forbid_pool;
};

/* ipaddr_t */
#define IP2STR_ZERO
#define IPFMT0 "%hhu.%hhu.%hhu.%hhu"
#define _IPOFST(addr, n) *((const unsigned char *)addr + n)
#define IP2STR(a) _IPOFST(a, 3),_IPOFST(a, 2),_IPOFST(a, 1),_IPOFST(a, 0)

#define SUBNETFMT0 "%hhu.%hhu.%hhu.%hhu/%hhu"

#define SUBNET2STR(subnet)

#define BIT(n)          1UL << n
#define MASK(m, n)

int submask(int mask) {
    return 1 << (32 - mask) -1;
}

int main (int argc, char *argv) {
    // regex_t regex;
    // size_t nmatch = 3;
    // regmatch_t pmatch[3];
    // char *pattern = "([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3})/[(0-9){1,2}]";

    // char buffer[64] = "192.168.0.0/24";
    // char *buf;
    // buf = buffer;
    // regcomp(&regex, pattern, REG_EXTENDED);
    // if (0 == regexec(&regex, buf, nmatch, pmatch, 0)) {
    //     // memset(buf + pmatch[0].rm_eo, 0, 1);
    //     printf("%s", buf + pmatch[0].rm_so);
    // }
    // regfree(&regex);

    struct subnet subnet;

    // char addr[] = {0, 1, 4, 2};
    int addr = 25;
    int idx, map;
    subnet.addr = 0x01010101;
    subnet.mask = 24;

    addr = submask(24);

    subnet.idx4 = 192;
    subnet.idx3 = 168;
    subnet.idx2 = 0;
    subnet.idx1 = 0;
    subnet.map = 0xFFFFFFFF;

    idx = (subnet.idx1) + (subnet.idx2 * 8) + (subnet.idx3 * 256 * 8) +
        (subnet.idx4 * 256 * 256 * 8);
    map = subnet.map;

    for (int i = 0; i < 32; i++) {
        if ((1 << i) & map) {
            addr = (idx * 32) + i;
            printf ("%08x " IPFMT0 " %2u\n", addr, IP2STR(&addr), addr);
        }
    }



    addr = subnet.idx * 8;

    // printf (IPFMT0"\n", IP2STR(&addr));



    return 0;
}
