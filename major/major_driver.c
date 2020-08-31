#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>		// file_operations
#include <linux/uaccess.h>	// copy_to_user()
#include <linux/slab.h>		// kmalloc()
#define MAJOR_DEV_NAME	"major_dev"
#define MAJOR_DEV_NUM	200

static int major_open(struct inode *inode, struct file *file)
{
	printk("major_open\n");

	return 0;
}

static ssize_t major_close(struct inode *inode, struct file *file)
{
	printk("major_close\n");

	return 0;
}

static ssize_t major_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
	int err;
	char *buff;

	buff = kmalloc(count, GFP_KERNEL);

	if(buff == NULL)
	{
		printk("malloc error\n");

		return 0;
	}

	sprintf(buff, "KERNEL DATA");

	err = copy_to_user(buf, buff, count);

	if(err != 0)
	{
		printk("copy_to_user error\n");

		kfree(buff);

		return err;
	}

	printk("major_read -> count: %d, f_pos: %lld\n", count, *f_pos);

	kfree(buff);

	return 0;
}

static ssize_t major_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	char *buff;
	int err;

	buff = kmalloc(count, GFP_KERNEL);

	if(buff == NULL)
	{
		printk("kmalloc error\n");

		return 0;
	}

	err = copy_from_user(buff, buf, count);

	if(err != 0)
	{
		printk("copy_from_user error\n");

		kfree(buff);

		return err;
	}


	printk("major_write -> buff: %s, count: %d, f_pos: %lld\n", buff, count, *f_pos);

	kfree(buff);

	return 0;
}

struct file_operations major_fops = {
.owner = THIS_MODULE,
.open = major_open,
.release = major_close,
.read = major_read,
.write = major_write,
};

int major_init(void)
{
	int err;

	printk("major_init\n");

	err = register_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME, &major_fops);

	if(err < 0)
	{
		printk("register_chrdev error\n");

		return err;
	}

	return 0;
}

void major_exit(void)
{
	printk("major_exit\n");

	unregister_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME);
}

module_init(major_init);
module_exit(major_exit);

MODULE_AUTHOR("icjk1003@gmail.com");
MODULE_LICENSE("GPL");

