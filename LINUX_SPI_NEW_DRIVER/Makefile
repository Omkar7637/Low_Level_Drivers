
obj-m := spi_drv.o

spi_drv.ko: spi_drv.c
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/nilesh/linux/bbb-linux M=`pwd` modules
	
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/nilesh/linux/bbb-linux M=`pwd` clean

deploy: spi_drv.ko
	scp spi_drv.ko debian@192.168.7.2:~/nilesh/

.PHONY: deploy clean

