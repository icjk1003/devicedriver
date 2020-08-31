obj-m := minor_driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default: minor_app minor_driver

minor_app:
	gcc -o $@ minor_app.c
minor_driver:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm minor_app
