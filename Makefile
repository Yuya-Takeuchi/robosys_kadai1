obj-m := myled.o

myled.ko: myled.c
	make -C /user/src/linux-headers-'uname -r' M='pwd' V=1 modules

clean:
	make -C /user/src/linux-headers-'uname -r' M='pwd' V=1 clean
