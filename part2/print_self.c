#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

/* Variable to hold the names of different process states */
char *process_state[65] = { [0 ... 64] = "UNKNOWN_STATE"};

/* Print process info for self and parents */
int print_self_and_parents(void){
    /* Use the Task struct task_struct */ 
    /* The current macro points to the currently 
       running process' task struct */
    struct task_struct *task = current;

    /* Map numeric state with known process string 
       states */
    process_state[0] = "TASK_RUNNING";
    process_state[1] = "TASK_INTERRUPTIBLE";
    process_state[2] = "TASK_UNINTERRUPTIBLE";
    process_state[4] = "TASK_STOPPED";
    process_state[8] = "TASK_TRACED";
    process_state[16] = "EXIT_ZOMBIE";
    process_state[32] = "EXIT_DEAD";
    process_state[64] = "TASK_NONINTERACTIVE";

    /* Print info for the current process */
    printk("Current process information:\n");
    printk("Name: %s\n", task->comm); /* comm has process name */
    printk("ID: %d\n", task->pid);
    printk("State: %s\n", process_state[ task->state ]);

    /* Traverse through parents */
    /* Only continue until reaching init whose PID == 1*/
    while (task->pid != 1){
        struct task_struct *prevTask = task;
        task = task->parent; /* Traverse through parents */

        /* Print process info */
        printk("Current process information (parent of %s):\n", prevTask->comm);
        printk("Name: %s\n", task->comm); /* comm has process name */
        printk("ID: %d\n", task->pid);
        printk("State: %s\n", process_state[ task->state ]);
    }

    return 0;
}

int pself_init_module(void){
    printk(KERN_INFO "Initializing print_self kernel module...\n");
    print_self_and_parents();
    return 0;
}

void pself_cleanup_module(void){
    printk(KERN_INFO "Goodbye!\n");
}

module_init(pself_init_module);
module_exit(pself_cleanup_module);

MODULE_LICENSE("GPL");
