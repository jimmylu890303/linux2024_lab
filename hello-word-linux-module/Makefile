obj-m := hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *.mod.cmd *.mod
