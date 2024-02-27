#include <linux/init.h>
#include <linux/module.h>

#include <linux/skbuff.h>

#include <linux/ip.h>

#include "devel.h"
#include "proc.h"

#define MODNAME     "skb send"

static struct proc_dir_entry * skb_root;


struct devel_proto {
    int a, b;
};



int skb_send(void) {
    struct sk_buff *skb;
    struct devel_proto *devel;
    struct iphdr *iph;
    struct ethhdr *eth_hdr;
    unsigned int addr = 0x00;
    unsigned char dst_mac[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    unsigned char src_mac[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    skb = alloc_skb(ETH_HLEN + 64, GFP_ATOMIC);

    skb_reserve(skb, ETH_HLEN + 20);



    // INTERNET(v4)
    printk(" --- INTERNET(v4) HEADER LENGTH: (%ld) ---\n", sizeof(struct iphdr));
    iph = skb_push(skb, sizeof(*iph));

    iph->version = 4;
    iph->ihl = sizeof(struct iphdr) >> 2;
    iph->tos = 0;
    iph->tot_len = htons(0x30);
    iph->id = 1;
    iph->frag_off = 0;
    iph->ttl = 0x80;
    iph->protocol = 0x11;
    iph->saddr = htonl(addr + 1);
    iph->daddr = htonl(addr);
    iph->check = 0;
    // iph->check = ip_fast_csum(skb->nh.iph, skb->nh.iph->ihl);

    // 8021Q



    // ETHERNET
    printk(" --- ETHERNET HEADER LENGTH: %d(%ld) ---\n", ETH_HLEN, sizeof(struct ethhdr));
    eth_hdr = skb_push(skb, sizeof(*eth_hdr));
    memcpy(eth_hdr->h_dest, dst_mac, 6);
    memcpy(eth_hdr->h_source, src_mac, 6);

    // eth_hdr->h_proto = htons(ETH_P_IP);
    eth_hdr->h_proto = htons(ETH_P_8021Q);

        skb->protocol = htons(ETH_P_8021Q);
    skb->pkt_type = PACKET_HOST;


    // DATA
    devel = skb_put(skb, sizeof(*devel));

    devel->a = 0xFFFF;

     printk(" --- SKB DUMP INFO ---\n");

    skb_dump(KERN_WARNING, skb, true);

    printk(" --- PACKET INFO ---\n");
    printk("packet type: %d, protocol: %d\n", skb->pkt_type, skb->protocol);
    printk("len = %d, data len = %d\n", skb->len, skb->data_len);
    printk("mac len = %d, hdr len = %d\n", skb->mac_len, skb->hdr_len);



    kfree_skb(skb);
    return 0;
}

//

static int skb_send_init (void)
{
    printk("load %s kernel module\n", MODNAME);

    //
    skb_root = devel_proc_mkdir("skb");
	
    //
    skb_send();

    //
	
    return 0;
}

module_init(skb_send_init);


static void skb_send_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);

    //
    devel_proc_remove(skb_root);

}

module_exit(skb_send_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
