#include <linux/init.h>
#include <linux/module.h>

#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/if_link.h>

#include <linux/proc_fs.h>




#include "devel.h"
#include "proc.h"

#define MODNAME     "skb send"

static struct proc_dir_entry *skb_root;
static struct proc_dir_entry *skb_send_entry;

static struct proc_dir_entry *skb_tx_packets_entry;
static struct proc_dir_entry *skb_tx_bytes_entry;

static struct skb_struct {
    bool enabled;
    struct rtnl_link_stats64 stats;
} devel_skb;

struct data {
    unsigned int id;
    char name[14];
};

static struct task_struct *skb_tx_task;


static int skb_send_one (void) {

    struct sk_buff *skb;

    skb = alloc_skb(ETH_HLEN, GFP_ATOMIC);

    skb_reserve(skb, 20 + 4 + ETH_HLEN);

    // DATA
    {
        struct data *data;
        pr_devel("--- DATA LENGTH: %ld ---\n", sizeof(struct data));
        data = skb_put(skb, sizeof(*data));
        data->id = 0xAA;
        memcpy(data->name, "ABCEDFG", 7);
        skb->data_len = sizeof(*data);
    }
    
    // INTERNET(v4)
    {
        struct iphdr *iph;
        unsigned int addr = 0x00;
    
        pr_devel(" --- INTERNET(v4) HEADER LENGTH: (%ld) ---\n", sizeof(struct iphdr));
        
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
    }

    // 8021Q
    {
        struct vlan_hdr *vhdr;
        
        pr_devel(" --- VLAN HEADER LENGTH: (%ld) ---\n", sizeof(struct vlan_hdr));

        vhdr = skb_push(skb, sizeof(*vhdr));
        vhdr->h_vlan_TCI = 1;
        vhdr->h_vlan_encapsulated_proto = htons(ETH_P_IP);
    }

    // ETHERNET
    {
        struct net_device *dev;
        struct ethhdr *ehdr;
        unsigned char dst_mac[] = {0x80, 0x92, 0x9D, 0xF9, 0x5D, 0x3D};
        unsigned char src_mac[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

        pr_devel(" --- ETHERNET HEADER LENGTH: %d(%ld) ---\n", ETH_HLEN, sizeof(struct ethhdr));
        
        ehdr = skb_push(skb, sizeof(*ehdr));
        memcpy(ehdr->h_dest, dst_mac, 6);
        memcpy(ehdr->h_source, src_mac, 6);
        
        //eth_hdr->h_proto = htons(ETH_P_IP);
        ehdr->h_proto = htons(ETH_P_8021Q);

        skb->protocol = htons(ETH_P_8021Q);

        // skb->pkt_type = PACKET_HOST;
        skb->pkt_type = PACKET_OTHERHOST;

        dev = dev_get_by_name(&init_net, "eth1");
        if (dev) {
            skb->dev = dev;
            pr_devel("Set device %s\n", dev->name);
            dev_put(dev);
        }
        
    }

    pr_devel(" --- SKB DUMP INFO ---\n");

    //skb_dump(KERN_WARNING, skb, true);

    pr_devel(" --- PACKET INFO ---\n");
    pr_devel("packet type: %d, protocol: 0x%X\n", skb->pkt_type, ntohs(skb->protocol));
    pr_devel("len = %d, data len = %d\n", skb->len, skb->data_len);
    pr_devel("mac len = %d, hdr len = %d\n", skb->mac_len, skb->hdr_len);


    devel_skb.stats.tx_packets++;
    devel_skb.stats.tx_bytes += skb->len;

    

    kfree_skb(skb);
    return 0;
}

// ========================================================================= //

static int kthread_skb_send (void *data) {

    while (!kthread_should_stop()) {
        //
        skb_send_one();
        
        //
        //mdelay(1000);

        yield();
    }

    return 0;
}

// ========================================================================= //

static int skb_send_open (struct inode *inode, struct file *filp) {
    //pr_info("Open skb_open file\n");
    return 0;
}

static ssize_t skb_send_read (struct file *file, 
    char __user *buffer, size_t count, loff_t *ppos)
{
    int val, len = 0;

    len = snprintf(buffer, count, "# enable skb_send\n");

    if (devel_skb.enabled)
        val = 1;
    else
        val = 0;

    len += snprintf((buffer + len), (count - len), "%d\n", val);


    if (*ppos != 0)
        return 0;
    else
        return len;
}

static ssize_t skb_send_write (struct file *file,  
    const char __user *buffer, size_t count, loff_t *ppos)
{
    int val;

    sscanf(buffer, "%d", &val);

    if (val) {
        devel_skb.enabled = true;
        if (skb_tx_task) 
            wake_up_process(skb_tx_task);
    } else {
        devel_skb.enabled = false;
        if (skb_tx_task)
            kthread_stop(skb_tx_task);
    }

    return count;
}

static int skb_send_release (struct inode *inode, struct file *filp) {
    // pr_info("Release skb_open file\n");
    return 0;
}

static const struct file_operations skb_send_fops = {
	.owner		= THIS_MODULE,
	.open		= skb_send_open,
	.read		= skb_send_read,
    .write		= skb_send_write,
	.llseek		= no_llseek,
	.release	= skb_send_release,
};

// ------------------------------------------------------------------------- //

static ssize_t skb_tx_packets_read (struct file *file, 
    char __user *buffer, size_t count, loff_t *ppos)
{
    int len = 0;

    len  = snprintf(buffer, count, "# skb_send tx packets\n");
    len += snprintf((buffer + len), (count - len), "%lld\n", devel_skb.stats.tx_packets);


    if (*ppos != 0)
        return 0;
    else
        return len;
}

static const struct file_operations skb_tx_packets_fops = {
	.owner		= THIS_MODULE,
	.read		= skb_tx_packets_read,
	.llseek		= no_llseek,
};

// ------------------------------------------------------------------------- //

static ssize_t skb_tx_bytes_read (struct file *file, 
    char __user *buffer, size_t count, loff_t *ppos)
{
    int len = 0;

    len  = snprintf(buffer, count, "# skb_send tx packets\n");
    len += snprintf((buffer + len), (count - len), "%lld\n", devel_skb.stats.tx_bytes);


    if (*ppos != 0)
        return 0;
    else
        return len;
}

static const struct file_operations skb_tx_bytes_fops = {
	.owner		= THIS_MODULE,
	.read		= skb_tx_bytes_read,
	.llseek		= no_llseek,
};

// ------------------------------------------------------------------------- //

static int skb_proc_init (struct proc_dir_entry *dir) {

    skb_send_entry = proc_create("skb_send", 0644, dir, &skb_send_fops);

    //
    skb_tx_packets_entry = proc_create("tx_packets", 0444, dir, &skb_tx_packets_fops);
    skb_tx_bytes_entry   = proc_create("tx_bytes",   0444, dir, &skb_tx_bytes_fops);

    return 0;
}

// static void skb_proc_exit (void) {
//     if (skb_send_entry)
//         proc_remove(skb_send_entry);
// }


// ========================================================================= //

static int skb_send_init (void)
{
    printk("load %s kernel module\n", MODNAME);

    //
    skb_root = devel_proc_mkdir("skb");

    //
    skb_proc_init(skb_root);

    //
    skb_tx_task = kthread_create(kthread_skb_send, NULL, "devel-skb_send");

    return 0;
}

module_init(skb_send_init);


static void skb_send_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);

    //
    if (skb_root)
        devel_proc_remove(skb_root);

    //
    //skb_proc_exit();

    //



}

module_exit(skb_send_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
