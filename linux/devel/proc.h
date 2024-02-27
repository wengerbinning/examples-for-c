#ifndef __DEVEL_PROC_H__
#define __DEVEL_PROC_H__

struct proc_dir_entry *devel_root;

struct proc_dir_entry *devel_proc_mkdir (const char *name);
void devel_proc_remove (struct proc_dir_entry * pde);

int proc_init (void);
void proc_exit (void);

#endif /* __DEVEL_PROC_H__ */