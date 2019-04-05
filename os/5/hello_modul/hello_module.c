#include <linux/kernel.h>
#include <linux/module.h>

int hello_module_init(void)
{
	printk(KERN_EMERG "Hello Module~! I'm Kernel\n");
	return 0;
}

void hello_module_cleanup(void)
{
	printk("<0>Bye Module~! \n"); //print kernel kernel print(linux/kernel.h)
}

module_init(hello_module_init); //insmod
module_exit(hello_module_cleanup); //rmmod

MODULE_LICENSE("GPL");
