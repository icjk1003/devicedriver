obj-m := ioctl_test_driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:  ioctl_test_app ioctl_test_driver

ioctl_test_app:
	gcc -o $@ ioctl_test_app.c
ioctl_test_driver:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm ioctl_test_app

