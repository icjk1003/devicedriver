#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "ioctl_test.h"

#define MAJOR_DEV_NAME "/dev/ioctl_test_dev"

int main(int argc, char** argv)
{
	int fd;
	ioctl_test_info led_info;

	fd = open(MAJOR_DEV_NAME, O_RDWR);

	if(fd < 0)
	{
		printf(MAJOR_DEV_NAME " open error\n");

		exit(1);
	}

	led_info.pin = 18;

	ioctl(fd, IOCTL_TEST_GPIO_OUTPUT, &led_info);

	ioctl(fd, IOCTL_TEST_LED_ON, &led_info);
	ioctl(fd, IOCTL_TEST_LED_STATE, &led_info);
	printf("%d\n", led_info.state);
	sleep(5);

	ioctl(fd, IOCTL_TEST_LED_OFF, &led_info);
	ioctl(fd, IOCTL_TEST_LED_STATE, &led_info);
	printf("%d\n", led_info.state);
	sleep(5);

	close(fd);

	return 0;
}
