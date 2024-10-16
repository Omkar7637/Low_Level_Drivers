
obj-m := i2c_lcd.o

i2c_lcd.ko: i2c_lcd.c
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/nilesh/linux/bbb-linux M=`pwd` modules
	
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/nilesh/linux/bbb-linux M=`pwd` clean

deploy: i2c_lcd.ko
	scp i2c_lcd.ko debian@192.168.7.2:~/nilesh/

.PHONY: deploy clean

