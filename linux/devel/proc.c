
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#include <linux/init.h>
#include <linux/module.h>

#include "devel.h"

#define MODNAME "DEVEL PROC"

static struct proc_dir_entry * devel_proc_root;

struct proc_dir_entry *devel_proc_mkdir (const char *name)
{
    if (name && devel_proc_root)
        return proc_mkdir(name, devel_proc_root);
    else
        return NULL;
}
EXPORT_SYMBOL_GPL(devel_proc_mkdir);


void devel_proc_remove (struct proc_dir_entry * pde) {
    if (pde)
        proc_remove(pde);
}
EXPORT_SYMBOL_GPL(devel_proc_remove);

//

static void * version_seq_start (struct seq_file *s, loff_t *pos)
{
    if (*pos > 0) 
        return NULL;
    else
        return VERSION;
}

static void * version_seq_next (struct seq_file *s, void *v, loff_t *pos)
{
    (*pos)++;
    return version_seq_start(s, pos);
}

static void version_seq_stop (struct seq_file *s, void *v)
{
    return;
} 

static int version_seq_show (struct seq_file *s, void *v)
{
    seq_printf(s, "v%s\n", (char *)v);

    return 0;
}

static struct seq_operations version_seq_ops = {
    .start = version_seq_start,
    .next  = version_seq_next,
    .stop  = version_seq_stop,
    .show  = version_seq_show
};

static int devel_proc_open (struct inode *inode, struct file *file)
{
    return seq_open(file, &version_seq_ops);
}

static struct file_operations version_proc_fops = {
        .owner = THIS_MODULE,
        .open = devel_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = seq_release
};

//

int devel_proc_init(void) {
    devel_proc_root = proc_mkdir("devel", NULL);

    //
    proc_create("version", 0666, devel_proc_root, &version_proc_fops);

    return 0;
}

module_init(devel_proc_init);

void devel_proc_exit (void) {

    if (devel_proc_root)
        proc_remove(devel_proc_root);

    return;
}


module_exit(devel_proc_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
