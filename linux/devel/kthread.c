#include <linux/init.h>
#include <linux/module.h>

#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/kthread.h>
#include <linux/delay.h>


#define MODNAME     "kernel thread"

static struct task_struct *task;



char *tran_policy(unsigned int policy)
{
	char *cp;

	switch (policy) {
	case 0:
		cp = "SCHED_NORMAL";
		break;
	case 1:
		cp = "SCHED_FIFO";
		break;
	case 2:
		cp = "SCHED_RR ";
		break;
	case 3:
		cp = "SCHED_BATCH";
		break;
	case 5:
		cp = "SCHED_IDLE";
		break;
	case 0x40000000:
		cp = "SCHED_RESET_ON_FORK";
		break;
	default:
		cp = "unknown";
	}

	return cp;
}

char *tran_state(volatile long state)
{
	char *s = NULL;

	switch (state) {
	case 0:
		s = "TASK_RUNNING";
		break;

	case 1:
		s = "TASK_INTERRUPTIBLE";
		break;

	case 2:
		s = "TASK_UNINTERRUPTIBLE";
		break;
	case 4:
		s = "__TASK_STOPPED";
		break;
	case 8:
		s = "__TASK_TRACED";
		break;
	case 16:
		s = "EXIT_ZOMBIE";
		break;
	case 32:
		s = "EXIT_DEAD";
		break;
	case 64:
		s = "TASK_DEAD";
		break;
	case 128:
		s = "TASK_WAKEKILL";
		break;
	case 256:
		s = "TASK_WAKING";
		break;
	case 512:
		s = "TASK_PARKED";
		break;
	default:
		s = "unknown";
		break;
	}

	return s;
}




static int task_dump(struct task_struct *task) {
     pr_info("[%6d] CPU = %d, type = %6s, prio = %3d, nice = %3d, policy = %s, state = %s, name = %s\n", 
            task->pid, task_cpu(task), (task->mm ? "User" : "Kernel"),
            task->normal_prio, task_nice(task),
            tran_policy(task->policy), tran_state(task->state),
            task->comm);
    
    return 0;
}

static int kthread_func (void *data) {
   

    while (!kthread_should_stop()) {
        task_dump(current);
        mdelay(1000);
        


        //
        yield();
    }
    return 0;
}



static int devel_kthread_init (void)
{
    struct task_struct *p;
    printk("load %s kernel module\n", MODNAME);

    for_each_process(p) {
        task_dump(p);
    }

    task = kthread_run(kthread_func, NULL, "devel_kthread");
    
    //	
    return 0;
}

module_init(devel_kthread_init);


static void devel_kthread_exit (void)
{

	printk("remove %s kernel module\n", MODNAME);

    if (task) {
        pr_info("stop %s[%d] kthread\n", task->comm, task->pid);
        kthread_stop(task);
    }        
        
}

module_exit(devel_kthread_exit);

MODULE_DESCRIPTION("This is a develop Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);