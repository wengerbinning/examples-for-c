#include <stdio.h>
#include <string.h>

typedef union dev_mac {
    char addr[6];
    struct {
        char oui[3];
        char eui[3];
    };
} dev_mac_t;

#define PROC_DEV_MAC_FILE  "device.txt"



#define MACFMT0 "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"      /* Example: c074ada1b2c3      */
#define MACFMT1 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx" /* Example: c0:74:ad:a1:b2:c3 */
#define MACFMT2 "%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"      /* Example: C074ADA1B2C3      */
#define MACFMT3 "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX" /* Example: C0:74:AD:A1:B2:C3 */
#define _STR2MAC(m) &(m)[0], &(m)[1], &(m)[2], &(m)[3], &(m)[4], &(m)[5]
#define _MAC2STR(m)  (m)[0],  (m)[1],  (m)[2],  (m)[3],  (m)[4],  (m)[5]
#define STR2MAC(mac) _STR2MAC((unsigned char *)(mac))
#define MAC2STR(mac) _MAC2STR((unsigned char *)(mac))

//=============================================================================
int utils_get_cur_dev_mac(dev_mac_t *mac)
//=============================================================================
{
    int len;
    FILE *fp;
    char buffer[16 + 1] = {0};

    if (!mac)
        return -1;

    memset(mac, 0, sizeof(dev_mac_t));
    if (!(fp = fopen(PROC_DEV_MAC_FILE, "r" ))) {
        return -1;
    }
    if ((len = fread(buffer, 1, 16, fp)) < 0) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    /**/
    sscanf(buffer, MACFMT1,  STR2MAC(mac->addr));
    return 0;
}



int main(int argc, char *argv[]) {
    int ret;
    dev_mac_t mac = {01};

     printf("MAC:" MACFMT3 "\n", MAC2STR(mac.addr));

    ret = utils_get_cur_dev_mac(&mac);


    printf("return: %d, MAC:" MACFMT3 "\n", ret, MAC2STR(mac.addr));

}