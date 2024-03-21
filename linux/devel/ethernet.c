
#include <linux/init.h>
#include <linux/module.h>

#include <linux/random.h>

#define MODNAME     "Ethernet"

struct mac_addr {
    unsigned char  oui_flags;
    unsigned short oui_id;
    unsigned char  eui_flags;
    unsigned short eui_id;
};

#define ETH_MAC_OUI_LOCAL       (0x1 << 7)
#define ETH_MAC_OUI_MULTI       (0x1 << 0)
#define ETH_MAC_OUI_FLAGS_MASK       0xFF


static void eth_mac_dump(struct mac_addr * addr) {
    char *p = (char *)addr;

    printk("Ethernet MAC Address = %02X:%02X:%02X:%02X:%02X:%02X", 
        *(p + 0), *(p + 1), *(p + 2), *(p + 3), *(p + 4), *(p + 5));
    printk(" local address: %s", (addr->oui_flags & ETH_MAC_OUI_LOCAL) ? "true" : "false");
    printk(" multi address: %s", (addr->oui_flags & ETH_MAC_OUI_MULTI) ? "true" : "false");
    printk("\n");
}


static void eth_mac_random_address(struct mac_addr *addr, bool multi) {
    char *buf = (char *)addr;
    
    get_random_bytes(buf, sizeof(*addr));
    
    addr->oui_flags = 0x00;

    addr->oui_flags |= ETH_MAC_OUI_LOCAL;

    if (multi)
        addr->oui_flags |= ETH_MAC_OUI_MULTI;
    else
        addr->oui_flags &= (~ETH_MAC_OUI_MULTI) & ETH_MAC_OUI_FLAGS_MASK;
}

static int devel_ethernet_init (void)
{
    struct mac_addr *addr, addr1;
    char macaddr[] = {0xF2, 0x02, 0x03, 0x04, 0x05, 0x06};
    eth_mac_random_address(&addr1, false);


    printk("load %s kernel module\n", MODNAME);

    addr = (struct mac_addr *)macaddr;
    eth_mac_dump(addr);
    eth_mac_dump(&addr1);

	
    //	
    return 0;
}

module_init(devel_ethernet_init);


static void devel_ethernet_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);
}

module_exit(devel_ethernet_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);


