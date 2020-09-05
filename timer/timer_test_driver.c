#include <linux/module.h>
#include <linux/io.h>
#include <linux/timer.h>

#include "timer_test_gpio.h"

#define DELAY_TIME_MSEC		(1*HZ/10)

struct timer_list timer;

void led_on_off(struct timer_list *timer)
{
	if(GPIO_GET(GPIO_LED) == 0)
	{
		GPIO_SET(GPIO_LED);
	}
	else
	{
		GPIO_CLR(GPIO_LED);
	}

	mod_timer(timer, get_jiffies_64() + DELAY_TIME_MSEC);
}

void kernel_timer_register(void)
{
	timer_setup(&timer, led_on_off, 0);
	timer.expires = get_jiffies_64() + DELAY_TIME_MSEC;
	add_timer(&timer);
}

int timer_test_init(void)
{
	void *map;

	printk("timer_test_init\n");

	map = ioremap(GPIO_BASE, GPIO_SIZE);

	if(!map)
	{
		printk("ioremap error\n");

		return -EBUSY;
	}

	gpio = (volatile unsigned int *)map;

	GPIO_OUT(GPIO_LED);

	kernel_timer_register();

	return 0;
}

void timer_test_exit(void)
{
	printk("timer_test_exit\n");

	GPIO_CLR(GPIO_LED);

	del_timer(&timer);
}

module_init(timer_test_init);
module_exit(timer_test_exit);

MODULE_AUTHOR("icjk1003@gmail.com");
MODULE_LICENSE("GPL");
