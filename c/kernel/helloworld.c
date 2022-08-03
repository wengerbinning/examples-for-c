#include <linux/init.h>
#include <linux/module.h>

static int helloworld_init(void)
{
	printk(KERN_ALERT "load hello world kernel module\n");
	return 0;
}
module_init(helloworld_init);


static void helloworld_exit(void)
{
	printk(KERN_ALERT "remove hello world kernel module\n");
}
module_exit(helloworld_exit);


MODULE_DESCRIPTION("This is a demo Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");


