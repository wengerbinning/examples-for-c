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


struct ip_address {
    int addr, mask;
};



/* ipaddr_t */

#define IPFMT0 "%hhu.%hhu.%hhu.%hhu"
#define _IPOFST(addr, n) *((unsigned char *)addr + n)
#define IP2STR(a) _IPOFST(a, 3),_IPOFST(a, 2),_IPOFST(a, 1),_IPOFST(a, 0)



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


    struct ip_address ip;

    // char addr[] = {0, 1, 4, 2};
    int addr = 25;



    printf (IPFMT0"\n", IP2STR(&addr));


    return 0;
}

