


#### NMI

非可屏蔽中断: 即使在内核代码中设置了屏蔽所有中断的时候，NMI也是不可以被屏蔽的。

kernel线程 < 时钟中断 < NMI中断

#### Soft Lockup

指CPU被内核代码占据，以至于无法执行其它进程。其原理是为每一个CPU分配一个定时执行的内核线程：`[watchdog/x]`;
如果该线程在设定的时间内没有被执行则发生了Soft Lockup。

watchdog/x是SCHED_FIFO实时进程， 优先级为最高的99， 


/proc/sys/kernel/watchdog
/proc/sys/kernel/watchdog_cpumask
/proc/sys/kernel/watchdog_thresh

/proc/sys/kernel/softlockup_all_cpu_backtrace
/proc/sys/kernel/softlockup_panic

symbol table

* watchdog_threads







* <https://blog.csdn.net/whatday/article/details/88016972>


#### Hard Lockup

CPU不仅无法执行其它进程，而且不再响应中断。

/proc/sys/kernel/nmi_watchdog
/proc/sys/kernel/hardlockup_panic


symbol table

* watchdog_overflow_callback