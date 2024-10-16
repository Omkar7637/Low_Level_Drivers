#include<linux/module.h>
#include"export.h"

static __init int import_init(void)
{
	printk(KERN_INFO "%s : import_init() : init is started\n", THIS_MODULE->name);
	my_function();
	my_var = 20;
	printk(KERN_INFO "%s : import_init() : init is completed\n", THIS_MODULE->name);
	return 0;
}


static __exit void import_exit(void)
{
	printk(KERN_INFO "%s : import_exit() : exit is started\n", THIS_MODULE->name);
	my_function();
	printk(KERN_INFO "%s : import_exit() : exit is completed\n", THIS_MODULE->name);
}

module_init(import_init);
module_exit(import_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMKAR KASHID");
MODULE_DESCRIPTION("This is dependent module");

















