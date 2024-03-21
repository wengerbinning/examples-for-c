#include <linux/init.h>
#include <linux/module.h>

#include <linux/time.h>

#define MODNAME     "Time"



static int devel_dump_machine_up_time(void) {
    struct timeval tv;

    do_gettimeofday(&tv);

    printk("second: %ld, microseconds: %ld\n", tv.tv_sec, tv.tv_usec);

    return 0;
}



static int devel_time_init (void)
{
    printk("load %s kernel module\n", MODNAME);

    devel_dump_machine_up_time();

    return 0;
}

module_init(devel_time_init);


static void devel_time_exit (void)
{
	printk("remove %s kernel module\n", MODNAME);
}

module_exit(devel_time_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
