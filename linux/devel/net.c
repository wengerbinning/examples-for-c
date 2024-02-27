#include <linux/init.h>
#include <linux/module.h>

#include <linux/string.h>

#include <linux/netdevice.h>

#include <linux/if_bridge.h>

#include <net/dsa.h>

#include "devel.h"
#include "proc.h"


#define MODNAME     "Network"

static struct proc_dir_entry * net_root;

static int net_init (void)
{
    struct net *net;
    struct net_device *dev;

    printk("load %s kernel module\n", MODNAME);


    //
    net_root = devel_proc_mkdir("net");
	
    //
    printk("NETWORK NAMESPACE TABLE:\n");
    for_each_net(net) {
        printk(" NETWORK NAMESPACE: ifindex = %d (0x%p)\n", net->ifindex, net);
    }

    //
    printk("DEFAULT NETWORK NAMESPACE: ifindex = %d (0x%p)\n",init_net.ifindex, &init_net);
    for_each_netdev(&init_net, dev) {
        printk(" NETWORK DEVICE: %s, index = %d \n", dev->name, dev->ifindex);
        printk("   PRESENT FLAG: %-5s, UP FLAG: %-5s, LINK FLAG: %-5s, PENDING FLAG: %-5s, DORMANT FLAG: %-5s", 
            (test_bit(__LINK_STATE_PRESENT, &dev->state)? "true" : "false"), 
            (test_bit(__LINK_STATE_START, &dev->state)? "true" : "false"), 
            (test_bit(__LINK_STATE_NOCARRIER, &dev->state)? "false" : "true"), 
            (test_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state)? "true" : "false"), 
            (test_bit(__LINK_STATE_DORMANT, &dev->state)? "true" : "false"));
        
        if (!strcmp("lo",dev->name)) 
            continue;

        if (IFF_802_1Q_VLAN && dev->priv_flags) {
            printk("TYPE: 8021Q\n");
        } 
        if (IFF_EBRIDGE && dev->priv_flags) {
            unsigned short pvid;
            // struct net_bridge *br;
            printk("TYPE: BIRDGE\n");

            br_vlan_get_pvid(dev, &pvid);
            // br = netdev_priv(dev);

            printk("bridge pvid: %d\n", pvid);

        }

        if (IFF_BRIDGE_PORT && dev->priv_flags) {
            printk("TYPE: BIRDGE PORT\n");
        }

        //
        printk("DSA DEVICE: %s\n", netdev_uses_dsa(dev) ? "true" : "false");
        
        printk("\n");
    }

    return 0;
}

module_init(net_init);


static void net_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);

    //
    devel_proc_remove(net_root);

}

module_exit(net_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);