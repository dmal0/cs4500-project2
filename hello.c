//#include <linux/module.h>

//int init_module(void) {
//   printk(KERN_INFO "Hello world!\n");
//    return 0;
//}

//void cleanup_module(void) {
//    printk(KERN_INFO "Goodbye world!\n");
//}

//module_init(init_module);
//module_exit(cleanup_module);

//MODULE_LICENSE("GPL");
//
#include <linux/module.h>
#include <linux/kernel.h>

int my_init_module(void){
	printk(KERN_INFO "Hello world!\n");
	return 0;
}

void my_cleanup_module(void){
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
