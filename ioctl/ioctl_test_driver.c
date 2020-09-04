#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/io.h>

#include "ioctl_test.h"
#include "ioctl_test_gpio.h"

#define MAJOR_DEV_NAME	"ioctl_test_dev"
#define MAJOR_DEV_NUM	200

static int ioctl_test_open(struct inode *inode, struct file *file)
{
	void *map;

	printk("ioctl_test_open\n");

	map = ioremap(GPIO_BASE, GPIO_SIZE);

	if(!map)
	{
		printk("ioremapp error\n");

		return -EBUSY;
	}

	gpio =  map;

	return 0;
}

static ssize_t ioctl_test_close(struct inode *inode, struct file *file)
{
	printk("ioctl_test_close\n");

	if(gpio)
	{
		iounmap(gpio);
	}

	return 0;
}

static long ioctl_test_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int err, size;

	ioctl_test_info led_info;

	printk("ioctl_test_ioctl\n");



	if(_IOC_TYPE(cmd) != IOCTL_TEST_MAGIC)
	{
		return -EINVAL;
	}

	if(_IOC_NR(cmd) >= IOCTL_TEST_MAX_NR)
	{
		return -EINVAL;
	}

	size = _IOC_SIZE(cmd);

	if(size)
	{
		err = 0;

		if(_IOC_DIR(cmd) & _IOC_READ)
		{
			err = access_ok(VERIFY_WRITE, (void *) arg, size);
		}
		else if(_IOC_DIR(cmd) & _IOC_WRITE)
		{
			err = access_ok(VERIFY_READ, (void *) arg, size);
		}

		if(!err)
		{
			return err;
		}
	}


	switch(cmd)
	{
		case IOCTL_TEST_GPIO_INPUT:
			err = copy_from_user(&led_info, (const void *)arg, sizeof(led_info));

			if(err)
			{
				printk("copy_from_user error\n");

				return err;
			}

			GPIO_IN(led_info.pin);

			break;

		case IOCTL_TEST_GPIO_OUTPUT:
			err = copy_from_user(&led_info, (const void *)arg, sizeof(led_info));

                        if(err)
			{
				printk("copy_from_user error\n");

				return err;
			}

			GPIO_OUT(led_info.pin);

			break;

		case IOCTL_TEST_LED_ON:
			err = copy_from_user(&led_info, (const void *)arg, sizeof(led_info));

                        if(err)
			{
				printk("copy_from_user error\n");

				return err;
			}

			GPIO_SET(led_info.pin);

			break;

		case IOCTL_TEST_LED_OFF:
			err = copy_from_user(&led_info, (const void *)arg, sizeof(led_info));

                        if(err)
			{
				printk("copy_from_user error\n");

				return err;
			}

			GPIO_CLR(led_info.pin);

			break;

		case IOCTL_TEST_LED_STATE:
			err = copy_from_user(&led_info, (const void *)arg, sizeof(led_info));

                        if(err)
			{
				printk("copy_from_user error\n");

				return err;
			}

			led_info.state = GPIO_GET(led_info.pin);

			err = copy_to_user((void *)arg, &led_info, sizeof(led_info));

                        if(err)
			{
				printk("copy_to_user error\n");

				return err;
			}

			break;
	}

	return 0;
}

struct file_operations ioctl_test_fops = {
.owner = THIS_MODULE,
.open = ioctl_test_open,
.release = ioctl_test_close,
.unlocked_ioctl = ioctl_test_ioctl,
};

int ioctl_test_init(void)
{
	int err;

	printk("ioctl_test_init\n");

	err = register_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME, &ioctl_test_fops);

	if(err < 0)
	{
		printk("register_chrdev error\n");

		return err;
	}

	return 0;
}

void ioctl_test_exit(void)
{
	printk("ioctl_test_exit\n");

	unregister_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME);
}

module_init(ioctl_test_init);
module_exit(ioctl_test_exit);

MODULE_AUTHOR("icjk1003@gmail.com");
MODULE_LICENSE("GPL");
