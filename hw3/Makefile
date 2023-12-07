obj-m += kfetch_mod_312551169.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	insmod kfetch_mod_312551169.ko

unload:
	rmmod kfetch_mod_312551169

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
