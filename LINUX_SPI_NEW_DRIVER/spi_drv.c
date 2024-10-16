#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

static struct spi_board_info spi_device_info = {
    .modalias = "desd-spidev",       // Name of the device driver to bind to
    .max_speed_hz = 1000000,    // Max SPI clock speed in Hz
    .bus_num = 1,               // SPI bus number
    .chip_select = 0,           // Chip select line
    .mode = SPI_MODE_0,         // SPI mode (0, 1, 2, 3)
};

static int spi_device_probe(struct spi_device *spi) {
    pr_info("SPI device %s probed\n", spi->modalias);
    // Perform device initialization
    // allocate device number
    // create device class and device file
    // init cdev (with fops) and add it in kernel
    return 0;
}

static int spi_device_remove(struct spi_device *spi) {
    pr_info("SPI device %s removed\n", spi->modalias);
    // delete cdev from kernel
    // destroy device file and device class
    // release device number
    // Perform device cleanup
    return 0;
}

static struct spi_driver spi_device_driver = {
    .driver = {
        .name = "desd-spidev",     // Must match the modalias of spi_board_info
        .owner = THIS_MODULE,
    },
    .probe = spi_device_probe,
    .remove = spi_device_remove,
};

static int __init spi_device_init(void) {
    struct spi_master *master;
    struct spi_device *spi_device;
    int ret;

    master = spi_busnum_to_master(spi_device_info.bus_num);
    if (!master) {
        pr_err("Failed to find SPI master\n");
        return -ENODEV;
    }

    spi_device = spi_new_device(master, &spi_device_info);
    if (!spi_device) {
        pr_err("Failed to create SPI device\n");
        return -ENODEV;
    }

    ret = spi_register_driver(&spi_device_driver);
    if (ret < 0) {
        spi_unregister_device(spi_device);
        pr_err("Failed to register SPI driver\n");
        return ret;
    }

    pr_info("SPI device and driver registered successfully\n");
    return 0;
}

static void __exit spi_device_exit(void) {
    spi_unregister_driver(&spi_device_driver);
    pr_info("SPI device driver unregistered\n");
}

module_init(spi_device_init);
module_exit(spi_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMKAR KASHID");
MODULE_DESCRIPTION("A simple device driver - SPI Slave Protocol Driver");
