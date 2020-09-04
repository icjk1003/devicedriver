#define IOCTL_TEST_MAGIC	't'

typedef struct
{
	int pin;
	int state;
} __attribute__((packed)) ioctl_test_info;

#define IOCTL_TEST_GPIO_INPUT	_IO(IOCTL_TEST_MAGIC, 0)
#define IOCTL_TEST_GPIO_OUTPUT	_IO(IOCTL_TEST_MAGIC, 1)
#define IOCTL_TEST_LED_ON	_IO(IOCTL_TEST_MAGIC, 2)
#define IOCTL_TEST_LED_OFF	_IO(IOCTL_TEST_MAGIC, 3)
#define IOCTL_TEST_LED_STATE	_IO(IOCTL_TEST_MAGIC, 4)

#define IOCTL_TEST_MAX_NR	5
