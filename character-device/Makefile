obj-m += cdd.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	gcc -o test-cdd test-cdd.c

test:
	sudo insmod cdd.ko
	sudo ./test-cdd
	sudo rmmod cdd

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *.mod.cmd *.mod test-cdd
