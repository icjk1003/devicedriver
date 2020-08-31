obj-m := major_driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default: major_app major_driver

major_app:
	gcc -o $@ major_app.c
major_driver:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm major_app
