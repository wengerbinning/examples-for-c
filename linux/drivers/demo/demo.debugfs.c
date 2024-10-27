


static int base_dump (struct seq_file *m, void *private) {
	struct demo *demo = m->private;

	seq_printf(m, "# Demo Base %p    \n", mtk->base1);

	return 0;
}


static int base_open (struct inode *inode, struct file *file) {
	return single_open(file, base_dump, inode->i_private);
}

static const struct file_operations base_fops = {
	.owner = THIS_MODULE,
	.open = base_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int demo_debugfs_init (struct demo *demo) {
	struct dentry *root;

    root = debugfs_create_dir("mediatek", NULL);
    demo->debugfs_root = root;

	debugfs_create_file("base", S_IRUGO, root, demo, &base_fops);

	return 0;
}

void demo_debugfs_exit (struct mediatek *mtk) {
	debugfs_remove_recursive(mtk->debugfs_root);
}
