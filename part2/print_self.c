#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

/* Print process info for self and parents */
int print_self_and_parents(void){
    /* Use the Task struct task_struct */ 
    /* The current macro points to the currently 
       running process' task struct */
    struct task_struct *task = current;

    /* Print info for the current process */
    /* Since this is used twice I think it could be its own 
       function but maybe that can be for later */
    printk("Current process information:\n");
    printk("Name: %s\n", task->comm); /* comm has process name */
    printk("ID: %d\n", task->PID);
    printk("State: %ld\n", task->state);

    /* Traverse through parents */
    /* Only continue until reaching init whose PID == 1*/
    while (task->pid != 1){
        task = task->parent; /* Traverse through parents */

        /* Print process info */
        printk("Current process information:\n");
        printk("Name: %s\n", task->comm); /* comm has process name */
        printk("ID: %d\n", task->PID);
        printk("State: %ld\n", task->state);
    }

    return 0;
}

int init_module(void){
    printk(KERN_INFO "Initializing print_self kernel module...\n");
    print_self_and_parents()
    return 0;
}

void cleanup_module(void){
    printk(KERN_INFO "Goodbye!\n");
}

module_init(init_module);
module_exit(cleanup_module);

MODULE_LICENSE("GPL");