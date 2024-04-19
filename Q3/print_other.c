#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/pid.h>
#include <linux/sched.h>

/* Variable to hold value passed to Module */
int myPID = 0;

//Variable to hold the names of different process states
char *process_state[65] = { [0 ... 64] = "UNKNOWN_STATE"};

/* Stores argument */
module_param(myPID, int, 0);

/* Prints info about the given process and its parent processes */
int print_given_process(int givenPID){

	/* Struct that points to the given process */
	struct task_struct *given_task;

	/* Get the process specified by the given PID */
	given_task = pid_task(find_vpid(givenPID), PIDTYPE_PID);

        /* Fills array with known process states */
        process_state[0] = "TASK_RUNNING";
        process_state[1] = "TASK_INTERRUPTIBLE";
        process_state[2] = "TASK_UNINTERRUPTIBLE";
        process_state[4] = "TASK_STOPPED";
        process_state[8] = "TASK_TRACED";
        process_state[16] = "EXIT_ZOMBIE";
        process_state[32] = "EXIT_DEAD";
        process_state[64] = "TASK_NONINTERACTIVE";

	/* While the given process is not 'init' */
	while(given_task->pid != 1){

		/* Print info about the given process */
		printk("Given process information:\n");
        	printk("Name: %s\n", given_task->comm);
        	printk("ID: %d\n", given_task->pid);
        	printk("State: %s\n", process_state[ given_task->state ]);

		/* Traverse through parents */
		given_task = given_task->parent;

	}

	/* Print info about 'init' */
        printk("Given process information:\n");
        printk("Name: %s\n", given_task->comm);
        printk("ID: %d\n", given_task->pid);
        printk("State: %s\n", process_state[ given_task->state ]);
	return 0;
}

int my_init_module(void){
	printk(KERN_INFO "Hello world!\n");
	print_given_process(myPID);
	return 0;
}

void my_cleanup_module(void){
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
