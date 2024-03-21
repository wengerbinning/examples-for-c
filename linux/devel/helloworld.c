#include <linux/init.h>
#include <linux/module.h>

#define MODNAME     "Hello, World!"

static int helloworld_init (void)
{
    printk("load %s kernel module\n", MODNAME);

    return 0;
}

module_init(helloworld_init);


static void helloworld_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);
}

module_exit(helloworld_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
